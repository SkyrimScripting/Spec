scriptName SpecExample_Spec_xxx extends Specification
{Example of a test extending Specification!}

function Setup()
endFunction

function TearDown()
endFunction

function TestShouldPass()
endFunction

function TestShouldFail()
endFunction

function JustCallTheSpecHelper()
    SkySpecRunnerSpecHelper.EventHappened("Hello from instance! " + self)
endFunction
