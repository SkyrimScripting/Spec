#pragma once

#include "SkyrimScripting/Spec/Implementation/Logging.h"
#include "SkyrimScripting/Spec/Implementation/EventHandler.h"
#include "SkyrimScripting/Spec/Implementation/PapyrusInterface.h"

namespace SkyrimScripting::Spec::Implementation {

    void Startup(const SKSE::LoadInterface* skse) {
        InitializeLog();
        logger::info("Initialize");
        SKSE::Init(skse);
        SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* event){
            if (event->type == SKSE::MessagingInterface::kDataLoaded) {
                logger::info("Listening for events");
                ListenForEvents();
                logger::info("Loading Papyrus Interface");
                SKSE::GetPapyrusInterface()->Register(PapyrusInterface::BIND);
            }
        });
    }
}
