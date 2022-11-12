#pragma once

#include "SkyrimScripting/Spec/Implementation/TestOutput.h"

namespace SkyrimScripting::Spec::Implementation {

    class EventHandler : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
        EventHandler() = default;

        RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent* event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*) override {
            if (event->opening) {
                if (event->menuName == "Main Menu")
                    TestOutput::GetSingleton().Clear();
                else if (event->menuName == "Console")
                    TestOutput::GetSingleton().ConsoleOpen();
            }
            return RE::BSEventNotifyControl::kContinue;
        }

    public:
        EventHandler(const EventHandler&) = delete;
        EventHandler &operator=(const EventHandler&) = delete;
        static EventHandler& GetSingleton() {
            static EventHandler sink;
            return sink;
        }
    };

    static void ListenForEvents() {
        const auto source = RE::UI::GetSingleton()->GetEventSource<RE::MenuOpenCloseEvent>();
        source->AddEventSink(&EventHandler::GetSingleton());
    }
}
