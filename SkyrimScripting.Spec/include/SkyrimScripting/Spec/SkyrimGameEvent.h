#pragma once

#include <string>

namespace SkyrimScripting::Spec {

    // TODO change this to an enum class - can a char* or std::string be the value type?

    namespace SkyrimGameEvent {
        enum Kind { Immediate, PluginsLoaded, ModsLoaded, GameStarted };
    }

    std::string GetSpecFilterTextForSkyrimEvent(SkyrimGameEvent::Kind event) {
        switch (event) {
            case SkyrimGameEvent::Immediate:
                return "SpecRunImmediate";
            case SkyrimGameEvent::PluginsLoaded:
                return "SpecRunPluginsLoaded";
            case SkyrimGameEvent::ModsLoaded:
                return "SpecRunModsLoaded";
            case SkyrimGameEvent::GameStarted:
                return "SpecRunGameStart";
            default:
                return {};
        }
    }
}
