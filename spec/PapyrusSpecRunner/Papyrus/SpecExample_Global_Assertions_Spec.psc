scriptName SpecExample_Global_Assertions_Spec
{
    Tests for global assertions
}

function Test_That_Makes_Some_Assertions()
    SkySpec.Assert(false, "This is false!")
    SkySpec.Assert(true, "This is true!")
endFunction
