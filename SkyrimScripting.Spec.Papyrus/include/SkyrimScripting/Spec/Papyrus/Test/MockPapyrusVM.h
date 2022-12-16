#pragma once

#include "SkyrimScripting/Spec/Papyrus/IPapyrusVM.h"

namespace SkyrimScripting::Spec::Papyrus::Test {

    class MockPapyrusVM : public IPapyrusVM {
        std::vector<std::string> GetGlobalFunctionNames(const std::string&) override { return {}; }
        void InvokeGlobalFunction(const std::string&, const std::string&,
                                  std::optional<std::function<void()>>) override {}
    };
}
