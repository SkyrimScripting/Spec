#pragma once

#include <RE/Skyrim.h>

#include <atomic>
#include <functional>

#include "SkyrimScripting/Spec/Papyrus/Logger.h"
#include "SkyrimScripting/Spec/Papyrus/TestEnvironment.h"

namespace SkyrimScripting::Spec::Papyrus {

    class GameSession {
        class GameStartedEventListener : public RE::BSTEventSink<RE::TESCellFullyLoadedEvent> {
            std::function<void()> _callback;

        public:
            void SetCallback(std::function<void()> callback) { _callback = callback; }
            RE::BSEventNotifyControl ProcessEvent(const RE::TESCellFullyLoadedEvent*,
                                                  RE::BSTEventSource<RE::TESCellFullyLoadedEvent>* source) override {
                logger::trace("GameStartedEventListener.ProcessEvent called");
                _callback();
                source->RemoveEventSink(this);
                return RE::BSEventNotifyControl::kContinue;  // TODO what is kStop for?
            }
        };

        GameSession() = default;
        ~GameSession() = default;
        GameSession(const GameSession&) = delete;
        GameSession(GameSession&&) = delete;
        GameSession& operator=(const GameSession&) = delete;
        GameSession& operator=(GameSession&&) = delete;
        std::atomic<bool> _initialized;
        std::atomic<bool> _specsHaveBeenRun;
        TestEnvironment _testEnvironment;
        GameStartedEventListener _gameStartedEventListener;

    public:
        static GameSession& GetSingleton() {
            static GameSession singleton;
            return singleton;
        }

        void RunSpecs() {
            _testEnvironment.Initialize();
            _testEnvironment.RunSpecs();
        }

        void RunSpecsIfNotAlreadyRun() {
            if (!_specsHaveBeenRun.exchange(true)) RunSpecs();
        }

        void ListenForGameStart() {
            logger::info("Listening for game to start!");
            _gameStartedEventListener.SetCallback([&]() { RunSpecsIfNotAlreadyRun(); });
            RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink<RE::TESCellFullyLoadedEvent>(
                &_gameStartedEventListener);
        }

        void Initialize() {
            if (!_initialized.exchange(true)) ListenForGameStart();
        }
    };
}
