scriptName SpecExample_Global_Spec hidden
{Example of a test with all global functions!}

; PyTest inspired dependency injection - maybe later!
; ObjectReference function Setup_Something()
; endFunction
; ObjectReference function Setup_SomethingElse()
; endFunction
; function Test(ObjectReference something, ObjectReference somethingElse)
; endFunction

function Setup() global
endFunction

function TearDown() global
endFunction

function TestShouldPass() global
endFunction

function TestShouldFail() global
endFunction

function JustCallTheSpecHelper() global
    Debug.MessageBox("HELLO?")
    Utility.Wait(5)
    ; SkySpecRunnerSpecHelper.EventHappened("Hello, one event!")
    ; SkySpecRunnerSpecHelper.EventHappened("Also, another event!")
endFunction
