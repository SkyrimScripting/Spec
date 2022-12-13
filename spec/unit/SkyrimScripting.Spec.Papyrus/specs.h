#pragma once

#define define_specs(...) go_bandit(__VA_ARGS__)

int main(int argc, char* argv[]) {
#if defined(SPECS_DISABLE_LOGGING)
    spdlog::set_level(spdlog::level::off);
#endif

    // gnarly. blech.
    auto reporterArgument = "--reporter=spec";
    int new_argc = argc + 2;
    char** new_argv = new char*[new_argc];
    new_argv[argc + 1] = nullptr;
    for (int ii = 0; ii < argc; ++ii) new_argv[ii] = argv[ii];
    new_argv[argc] = new char[strlen(reporterArgument) + 1];
    strcpy(new_argv[argc], reporterArgument);

    return bandit::run(new_argc, new_argv);
}