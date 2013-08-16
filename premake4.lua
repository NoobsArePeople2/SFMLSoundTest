-- See "paths.lua.sample" for instructions on creating the file.
dofile ("paths.lua")

NAME  = "SFML_Sound_Test"
LINKS = {}
if os.is("macosx") then

    KIND             = "WindowedApp"
    LINKS            = { "tgui", "sfml-audio.framework", "sfml-graphics.framework", "sfml-window.framework", "sfml-system.framework", "CoreFoundation.framework" }
    PLATFORMS        = { "x32" }
    BUILD_OPTS       = "-std=c++11 -stdlib=libc++"
    DEBUG_BUILD_OPTS = {}
    LINK_OPTS        = "-stdlib=libc++"
    DEFINES          = ""

elseif os.is("windows") then

    KIND             = "ConsoleApp"
    LINKS            = { "tgui-s-d", "sfml-audio-s-d", "sfml-graphics-s-d", "sfml-window-s-d", "sfml-system-s-d" }
    PLATFORMS        = {}
    BUILD_OPTS       = "-std=c++0x"
    DEBUG_BUILD_OPTS = "-g"
    LINK_OPTS        = ""
    DEFINES          = "SFML_STATIC"

end

solution(NAME)
  configurations { "Debug", "Release" }

  project(NAME)
    kind(KIND)
    language "C++"
    files { "**.h", "**.cpp", "**.hpp", "**.c", "**.ttf", "**.ogg", "**.wav", "**.png", "**.txt" }
    links(LINKS)
    libdirs(LIB_DIRS)
    includedirs(INC_DIRS)
    buildoptions(BUILD_OPTS)
    linkoptions(LINK_OPTS)
    defines(DEFINES)
    platforms(PLATFORMS)

    configuration "Debug"
        buildoptions(DEBUG_BUILD_OPTS)

    configuration "Release"
