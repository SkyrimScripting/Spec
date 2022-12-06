scriptName SkySpec hidden
{Global Papyrus functions to support SkyrimScripting Spec}

; IsInstalled()
; GetVersion()

bool function Assert(bool condition, string failureMessage = "") global native
{...}

; TODO move me to SkyrimScripting.String
;      ... after this project exists so we can test it!
string function Sprintf() global native
{...}

; TODO move me to SkyrimScripting.Log
;      ... after this project exists so we can test it!
string function Log() global native
{...}
