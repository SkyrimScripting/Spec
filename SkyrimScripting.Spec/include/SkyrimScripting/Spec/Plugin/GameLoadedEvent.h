#pragma once

#include <RE/Skyrim.h>

#include <atomic>

#include "SkyrimScripting/Spec/Config.h"
#include "SkyrimScripting/Spec/Plugin/TestRunEvent.h"

namespace SkyrimScripting::Spec::Plugin {

    class CellFullyLoadedEventSink : public RE::BSTEventSink<RE::TESCellFullyLoadedEvent> {
        CellFullyLoadedEventSink() = default;
        ~CellFullyLoadedEventSink() = default;
        CellFullyLoadedEventSink(const CellFullyLoadedEventSink&) = delete;
        CellFullyLoadedEventSink(CellFullyLoadedEventSink&&) = delete;
        CellFullyLoadedEventSink& operator=(const CellFullyLoadedEventSink&) = delete;
        CellFullyLoadedEventSink& operator=(CellFullyLoadedEventSink&&) = delete;
        std::atomic<bool> loaded = false;

    public:
        static CellFullyLoadedEventSink& GetSingleton() {
            static CellFullyLoadedEventSink singleton;
            return singleton;
        }

        RE::BSEventNotifyControl ProcessEvent(const RE::TESCellFullyLoadedEvent*,
                                              RE::BSTEventSource<RE::TESCellFullyLoadedEvent>*) override {
            if (!loaded.exchange(true)) {
                std::cout << "Runnings SpecRunGameStart tests" << std::endl;
                Config::TestCaseRunFunction(GetTestFilterForEvent(TestRunEvent::GameStarted));
                if (Config::ExitGameAfterSpecs) {
                    std::cout << "Exiting Skyrim." << std::endl;
                    SKSE::WinAPI::TerminateProcess(SKSE::WinAPI::GetCurrentProcess(), EXIT_SUCCESS);
                }
            }
            return RE::BSEventNotifyControl::kContinue;
        }
    };
}
