.info
  .source "Specification.psc"
  .modifyTime 1668225880
  .compileTime 1668225882
  .user "mrowr"
  .computer "MROWR"
.endInfo
.userFlagsRef
  .flag conditional 1
  .flag hidden 0
.endUserFlagsRef
.objectTable
  .object Specification Actor
    .userFlags 0
    .docString ""
    .autoState 
    .variableTable
    .endVariableTable
    .propertyTable
    .endPropertyTable
    .stateTable
      .state
        .function GetState
          .userFlags 0
          .docString "Function that returns the current state"
          .return String
          .paramTable
          .endParamTable
          .localTable
          .endLocalTable
          .code
            RETURN ::state
          .endCode
        .endFunction
        .function GotoState
          .userFlags 0
          .docString "Function that switches this object to the specified state"
          .return None
          .paramTable
            .param newState String
          .endParamTable
          .localTable
            .local ::NoneVar None
          .endLocalTable
          .code
            CALLMETHOD onEndState self ::NoneVar
            ASSIGN ::state newState
            CALLMETHOD onBeginState self ::NoneVar
          .endCode
        .endFunction
        .function OnInit 
          .userFlags 0
          .docString ""
          .return NONE
          .paramTable
          .endParamTable
          .localTable
            .local ::nonevar none
          .endLocalTable
          .code
            CALLMETHOD Print self ::nonevar "Hello world! 1" ;@line 4
            CALLMETHOD Print self ::nonevar "Hello world! 2" ;@line 5
            CALLMETHOD Print self ::nonevar "Hello world! 3" ;@line 6
            CALLMETHOD Print self ::nonevar "Hello world! 4" ;@line 7
            CALLMETHOD Print self ::nonevar "Hello world! 5" ;@line 8
            CALLMETHOD Print self ::nonevar "Hello world! 6" ;@line 9
            CALLMETHOD Print self ::nonevar "Hello world! 7" ;@line 10
            CALLMETHOD Print self ::nonevar "Hello world! 8" ;@line 11
          .endCode
        .endFunction
        .function Print native 
          .userFlags 0
          .docString ""
          .return NONE
          .paramTable
            .param text string
          .endParamTable
        .endFunction
      .endState
    .endStateTable
  .endObject
.endObjectTable