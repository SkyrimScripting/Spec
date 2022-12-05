#pragma once

#undef GetObject

namespace SkyrimScripting::Spec::Implementation::PapyrusInterface {

    void Specification_Print(RE::BSScript::Internal::VirtualMachine*, const RE::VMStackID stackID, RE::Actor*, std::string text) {
        auto scriptName = RE::BSScript::Internal::VirtualMachine::GetSingleton()->allRunningStacks.find(stackID)->second->top->previousFrame->self.GetObject()->GetTypeInfo()->GetName();
        TestOutput::GetSingleton().Output(std::format("[{}] {}", scriptName, text));
    }

    void SkySpecification_RunAsSkySpecification(RE::BSScript::Internal::VirtualMachine*, const RE::VMStackID stackID, RE::TESForm*) {

        auto* vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
        auto* top = vm->allRunningStacks.find(stackID)->second->top;
        auto* previous = top->previousFrame;

        logger::info("Top IP: {}", top->instructionPointer);
        logger::info("Previous IP: {}", previous->instructionPointer);

        uint32_t topLine;
        top->owningFunction->TranslateIPToLineNumber(top->instructionPointer, topLine);
        logger::info("Top line number: {}", topLine);

        uint32_t previousLine;
        previous->owningFunction->TranslateIPToLineNumber(previous->instructionPointer, previousLine);
        logger::info("previous line number: {}", previousLine);

        vm->TraceStack("Wassup? TRACE TRACE TRACE", stackID);



        // // ///
        // // logger::info("Can I get the line of code where you called this native function from?");
        // // uint32_t line;
        // // frame->owningFunction->TranslateIPToLineNumber(frame->instructionPointer, line);
        // // logger::info("The line number: {}", line);

        // // ///
        // // logger::info("Make it a ScriptFunction?");
        // // auto* fn = skyrim_cast<RE::BSScript::Internal::ScriptFunction*>(frame->owningFunction.get());
        // // if (fn) {
        // //     logger::info("FN");
        // //     uint32_t line3;
        // //     fn->TranslateIPToLineNumber(frame->instructionPointer, line3);
        // //     logger::info("Line no? {}", line3);
        // // } else {
        // //     logger::info("no FN!");
        // // }

        // ///
        // logger::info("TOP?");
        // uint32_t line2;
        // top->owningFunction->TranslateIPToLineNumber(top->instructionPointer, line2);
        // logger::info("The line number: {}", line2);

        // //
        // auto* parentInfo = typeInfo->GetParent();
        // if (parentInfo) {
        //     logger::info("Parent: {}", parentInfo->GetName());
        // }
        
        // auto functionCount = typeInfo->GetNumMemberFuncs();
        // logger::info("{} functions on this type", functionCount);
        // if (functionCount) {
        //     uint32_t i = 0;
        //     auto* functions = typeInfo->GetMemberFuncIter();
        //     while (i < functionCount) {
        //         auto function = functions[i].func;
        //         logger::info("Function: {}", function->GetName().c_str());

        //         logger::info("Type name: {}", function->GetObjectTypeName());

        //         // logger::info("pad0c? {}", function->pad0C); // meh, mostly 0 vut some 352 and some 353, no f'n clue
        //         // logger::info("DecRef: {}", function->DecRef()); // is this override stuff? OnInit: 2, all else: 1
        //         // logger::info("Can be called from tasklets: {}", function->CanBeCalledFromTasklets()); // all true
        //         // logger::info("Flags: {}", function->GetUserFlags()); // all 0
        //         // logger::info("Source: {}", function->GetSourceFilename()); // anonymized

        //         // function->TranslateIPToLineNumber

        //         // function->GetFunctionType()
        //         // RE::BSScript::IFunction::FunctionType:: <--- getter, setter, normal
        //         i++;
        //     }
        // }
    }

    bool BIND(RE::BSScript::IVirtualMachine* vm) {
        vm->RegisterFunction("Print", "Specification", Specification_Print);
        vm->RegisterFunction("RunAsSkySpecification", "SkySpecification", SkySpecification_RunAsSkySpecification);
        return true;
    }
}
