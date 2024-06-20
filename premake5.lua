workspace "GameEngine"
    architecture "x86"

    configurations 
    { 
        "DebugStaticLibrary"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

filter "configurations:DebugStaticLibrary"
buildoptions         
{
    "/sdl",
    "/MDd"
}

project "GameEngine"
    location "OpenGLGameEngine/GameEngine"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin/" ..outputdir.. "/%{prj.name}")

    files
    {
        "OpenGLGameEngine/GameEngine/src/**.h",
        "OpenGLGameEngine/GameEngine/src/**.cpp",
        "OpenGLGameEngine/GameEngine/**.dll"
    }
    includedirs
    {
        "ExternalLibs/GLEW/include;",
        "ExternalLibs/GLM;",
        "ExternalLibs/GLFW/include;",
        "ExternalLibs/ASSIMP/include;",
        "ExternalLibs/STB_IMAGE;",
        "ExternalLibs/SPDLOG/spdlog-1.x/include;"
    }
    libdirs
    {
       "ExternalLibs/GLEW/lib/Release/Win32",
       "ExternalLibs/GLFW/lib-vc2022",
       "ExternalLibs/ASSIMP/lib"
    }
    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "GAME_ENGINE_WINDOWS",
            "WIN32",
            "_DEBUG",
            "_CONSOLE"
        }

    filter "DebugStaticLibrary"
        defines "DEBUG_STATIC"
        symbols "On"

   
project "DemoScene3D"
    location "OpenGLGameEngine/DemoScene3D"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin/" ..outputdir.. "/%{prj.name}")

    files
    {
        "OpenGLGameEngine/DemoScene3D/src/**.h",
        "OpenGLGameEngine/DemoScene3D/src/**.cpp",
        "OpenGLGameEngine/DemoScene3D/**.dll"
    }
    includedirs
    {
        "OpenGLGameEngine/GameEngine/src",
        "ExternalLibs/GLEW/include;",
        "ExternalLibs/GLM;",
        "ExternalLibs/GLFW/include;",
        "ExternalLibs/ASSIMP/include;",
        "ExternalLibs/STB_IMAGE;",
        "ExternalLibs/SPDLOG/spdlog-1.x/include;"
    }
    libdirs
    {
       "ExternalLibs/GLEW/lib/Release/Win32",
       "ExternalLibs/GLFW/lib-vc2022",
       "ExternalLibs/ASSIMP/lib"
    }
    links
    {
        "opengl32.lib",
        "glew32.lib",
        "glfw3.lib",
        "assimp-vc143-mt.lib",
        "GameEngine"
    }
    dependson
    {
        "GameEngine"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        defines
        {
            "GAME_ENGINE_WINDOWS",
            "WIN32",
            "_DEBUG",
            "_CONSOLE"
        }

    filter "DebugStaticLibrary"
        defines "DEBUG_STATIC"
        symbols "On"
        runtime "Debug"


