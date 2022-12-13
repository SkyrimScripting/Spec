#pragma once

#include "SpecHelper.h"

// clang-format off
define_specs([](){
    describe("some specs", [](){
        it("should run!", [](){
            AssertThat(69, Equals(420));
        });
    });
});
// clang-format on
