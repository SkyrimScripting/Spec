#pragma once

#include <functional>
#include <future>

bool TypeExists(const std::string& typeName) {
    return RE::BSScript::Internal::VirtualMachine::GetSingleton()->TypeIsValid(typeName);
}

RE::BSScript::ObjectTypeInfo* GetTypeInfo(const std::string& typeName) {
    auto* vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
    RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo> out;
    vm->GetScriptObjectType(typeName, out);
    return out.get();
}

class FunctionCallback : public RE::BSScript::IStackCallbackFunctor {
    std::function<void()> callback;
    void operator()(RE::BSScript::Variable result) override { callback(); }
    bool CanSave() const override { return false; }
    void SetObject(const RE::BSTSmartPointer<RE::BSScript::Object>&) override {}

public:
    FunctionCallback(std::function<void()> callback) : callback(callback) {}
};

void InvokeGlobalFunctionNoArgs(const std::string& scriptName, const std::string& functionName) {
    auto* vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
    std::promise<void> result;
    auto callback = FunctionCallback([&result]() {
        std::cout << "CALLBACK CALLED!" << std::endl;
        result.set_value();
    });

    auto arguments = RE::BSScript::ZeroFunctionArguments();
    RE::BSTSmartPointer<RE::BSScript::IStackCallbackFunctor> callbackPtr(&callback);

    // Can we make it block with <future> somehow????
    std::future<void> future = result.get_future();

    // This is non-blocking, need to wait for callbackPtr
    // Meaning...
    // Unfortunately, none of the C++ testing frameworks from what I can tell
    // are particularly good at asyncronous tests. Not yet.
    // Hmm.
    vm->DispatchStaticCall(scriptName, functionName, &arguments, callbackPtr);

    // Will this wait... ?
    // future.get();
    // Waits but nothing happens :(
}
