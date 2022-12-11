scriptName SpecExample_Global_Spec hidden
{Example of a test with all global functions!}

function TestSomething() global
    Debug.Trace("[SPEC] Called TestSomething")
endFunction

function TestSomethingElse() global
    Debug.Trace("[SPEC] Called TestSomethingElse")
endFunction

function Foo() global
endFunction

function Bar() global
endFunction
