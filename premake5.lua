workspace "gentracer"
    architecture "x86_64"
    configurations { "Debug", "Release" }
    startproject "gentracer"

-- ImGui static library project
project "imgui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    
    targetdir "bin/%{cfg.buildcfg}"
    objdir "int/%{cfg.buildcfg}/imgui"
    
    files
    {
        "external/imgui/*.cpp",
        "external/imgui/*.h",
        "external/imgui/backends/imgui_impl_glfw.cpp",
        "external/imgui/backends/imgui_impl_glfw.h",
        "external/imgui/backends/imgui_impl_opengl3.cpp",
        "external/imgui/backends/imgui_impl_opengl3.h"
    }
    
    includedirs
    {
        "external/imgui",
        "external/stb",
        "/usr/include"  -- for GLFW headers
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

-- gentracer (main project)
project "gentracer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    
    targetdir "bin/%{cfg.buildcfg}"
    objdir "int/%{cfg.buildcfg}/gentracer"
    
    files { "src/**.h", "src/**.cpp" }
    
    includedirs 
    { 
        "external/imgui",
        "external/stb",
        "/usr/include"  -- for GLFW headers
    }
    
    links 
    { 
        "imgui",  -- Link against our ImGui static library
        "spdlog", 
        "fmt", 
        "glfw", 
        "GLEW", 
        "GL" 
    }
    
    defines { "SPDLOG_FMT_EXTERNAL" }
    
    -- Make sure gentracer depends on imgui being built first
    dependson { "imgui" }
    
    filter "system:windows"
        systemversion "latest"
        
    filter "system:linux"
        defines {
            "GLM_FORCE_INTRINSICS",
            "GLM_FORCE_SIMD_AVX2",
            "GLM_FORCE_RADIANS",
            "GLM_ENABLE_EXPERIMENTAL"
        } 
        
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
