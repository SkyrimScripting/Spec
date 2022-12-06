#pragma once

bool TypeExists(const std::string& typeName) {
	return RE::BSScript::Internal::VirtualMachine::GetSingleton()->TypeIsValid(typeName);
}

RE::BSScript::ObjectTypeInfo* GetTypeInfo(const std::string& typeName) {
	auto* vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
	RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo> out;
	vm->GetScriptObjectType(typeName, out);
	return out.get();
}
