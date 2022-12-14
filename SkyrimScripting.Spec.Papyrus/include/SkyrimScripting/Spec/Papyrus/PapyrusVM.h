#pragma once

#include <optional>

#include "SkyrimScripting/Spec/Papyrus/Internal/PapyrusVMImpl.h"
#include "SkyrimScripting/Spec/Papyrus/Test/MockPapyrusVM.h"

namespace SkyrimScripting::Spec::Papyrus {

    bool USE_MOCK_VM = false;

    namespace {
        std::optional<Test::MockPapyrusVM> MockPapyrusVMInstance;
        std::optional<Internal::PapyrusVMImpl> PapyrusVMImplInstance;

        IPapyrusVM& GetMock() {
            if (!MockPapyrusVMInstance) MockPapyrusVMInstance.emplace();
            return MockPapyrusVMInstance.value();
        }

        IPapyrusVM& GetReal() {
            if (!PapyrusVMImplInstance) PapyrusVMImplInstance.emplace();
            return PapyrusVMImplInstance.value();
        }
    }

    IPapyrusVM& GetPapyrusVM() {
        if (USE_MOCK_VM)
            return GetMock();
        else
            return GetReal();
    }
}