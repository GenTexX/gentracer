workspace "gentracer"
    architecture "x86_64"
    configurations { "Debug", "Release" }
    startproject "gentracer"

project "gentracer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "int/%{cfg.buildcfg}"

    files { "src/**.h", "src/**.cpp" }

    includedirs { "/usr/include" }

    --libdirs { "vendor/SDL2/lib" }  -- Adjust this based on your OS
    links { "spdlog", "fmt" }  -- both are required
    defines { "SPDLOG_FMT_EXTERNAL" }
    

    filter "system:windows"
        systemversion "latest"
        --links { "SDL2.lib", "SDL2main.lib" }

    filter "system:linux"
       defines {
            "GLM_FORCE_INTRINSICS",
            "GLM_FORCE_SIMD_AVX2",
            "GLM_FORCE_RADIANS",
            "GLM_ENABLE_EXPERIMENTAL"
        } 
        --links { "SDL2", "SDL2main", "SDL2_image", "m" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
