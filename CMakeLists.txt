cmake_minimum_required(VERSION 3.25)

project(SkyrimScripting.Spec.AllProjects VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

# Set <DEPLOY_ROOT> to set the path of a mod to deploy files to.
# Defaults to the value of environment variable SKYRIM_MODS_FOLDER
set(DEPLOY_ROOT "$ENV{SKYRIM_MODS_FOLDER}")
# The SKSE plugin files will be writen to <DEPLOY_ROOT>/<PROJECT_NAME>/SKSE/Plugins
# set(DEPLOY_ROOT "C:/some/path/to/mod/path") # <--- uncomment line to customize

find_package(CommonLibSSE CONFIG REQUIRED)

add_subdirectory(SkyrimScripting.Spec)
add_subdirectory(SkyrimScripting.Spec.Papyrus)
add_subdirectory(Examples)
add_subdirectory(spec)
