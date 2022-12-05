scriptName Example_Spec extends SkySpec
{foooo bar}

Actor property Player auto

string property SomeValue auto
{hello}

event OnSetup()
    {it goes in here}

endEvent

event OnTeardown()

endEvent

function It_Should_Do_Something()
    ; Expect._Bool(true)
    ; Expect.Actor()
endFunction

function Should_Do_Something_Else()

endFunction

function _HelperFunctionForSomething()
    ; I am not a test!
endFunction
