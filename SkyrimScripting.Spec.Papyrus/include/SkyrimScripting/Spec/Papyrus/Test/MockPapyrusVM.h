#pragma once

#include "SkyrimScripting/Spec/Papyrus/IPapyrusVM.h"

namespace SkyrimScripting::Spec::Papyrus::Test {

    class MockPapyrusVM : public IPapyrusVM {
        std::vector<std::string> GetGlobalFunctionNames(const std::string&) override { return {}; }
    };
}
