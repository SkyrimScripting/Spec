#include "SkyrimScripting/Spec/Implementation/Startup.h"

namespace SkyrimScripting::Spec::Implementation {

    SKSEPluginLoad(const SKSE::LoadInterface* skse) {
        Startup(skse);
        return true;
    }
}
