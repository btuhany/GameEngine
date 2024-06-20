workspace "GameEngine"
    architecture "x86"

    configurations 
    { 
        "DebugStaticLibrary"
    }

outputdir = "%{cfg.buildcfg}-&{cfg.system}-%{cfg.architecture}"
project "GameEngine"
    location "OpenGLGameEngine"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin/" ..outputdir.. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }
    include
    {
        "%{prj.name}/ExternalLibs/GLEW/include;$(SolutionDir)/"
        "%{prj.name}/ExternalLibs/GLM;$(SolutionDir)/"
        "%{prj.name}/ExternalLibs/GLFW/include;$(SolutionDir)/"
        "%{prj.name}/ExternalLibs/ASSIMP/include;$(SolutionDir)/"
        "%{prj.name}/ExternalLibs/STB_IMAGE;$(SolutionDir)/"
        "%{prj.name}/ExternalLibs/SPDLOG/spdlog-1.x/include;"
    }
    filter "system:windows"