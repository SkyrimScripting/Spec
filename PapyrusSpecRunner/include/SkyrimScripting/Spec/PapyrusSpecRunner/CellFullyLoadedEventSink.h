#pragma once

#include <RE/Skyrim.h>

#include <atomic>
#include <functional>

namespace SkyrimScripting::Spec::PapyrusSpecRunner {

    class CellFullyLoadedEventSink : public RE::BSTEventSink<RE::TESCellFullyLoadedEvent> {
        std::function<void()> callback;
        std::atomic<bool> loaded = false;

    public:
        explicit CellFullyLoadedEventSink(std::function<void()> callback) : callback(callback) {}

        RE::BSEventNotifyControl ProcessEvent(const RE::TESCellFullyLoadedEvent*,
                                              RE::BSTEventSource<RE::TESCellFullyLoadedEvent>*) override {
            if (!loaded.exchange(true)) callback();
            return RE::BSEventNotifyControl::kContinue;
        }
    };
}
