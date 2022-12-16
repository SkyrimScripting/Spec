#pragma once

#include <any>
#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace SkyrimScripting::Spec::Papyrus {

    class IPapyrusVM {
    public:
        virtual std::vector<std::string> GetGlobalFunctionNames(const std::string& scriptName) = 0;
        virtual void InvokeGlobalFunction(const std::string& scriptName, const std::string& functionName,
                                          std::optional<std::function<void()>>) = 0;
        // virtual std::string GetGlobalFunctionReturnType(const std::string& scriptName,
        //                                                 const std::string& functionName) = 0;
        // virtual void InvokeGlobalFunction(const std::string& scriptName, const std::string& functionName,
        //                                   std::function<void(std::any)> resultCallback) = 0;
        // virtual std::vector<std::string> GetInstanceFunctionNames(const std::string& scriptName) = 0;
        // virtual std::string GetInstanceFunctionReturnType(const std::string& scriptName,
        //                                                   const std::string& functionName) = 0;
        // virtual void InvokeInstanceFunction(const std::string& scriptName, const std::string& functionName,
        //                                     std::function<void(std::any)> resultCallback) = 0;
    };
}