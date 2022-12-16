scriptName SkySpec_Demo_Global_Spec

function Test_Something() global
    SkySpec.Assert(false, "Kabook 1")
endFunction

function Test_Something_Else() global
    SkySpec.Assert(false, "Kabook 2")
endFunction
