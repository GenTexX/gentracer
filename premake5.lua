workspace "gentracer"
    architecture "x86_64"
    configurations { "Debug", "Release" }
    startproject "gentracer"

project "gentracer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    files { "src/**.h", "src/**.cpp" }

    includedirs { "vendor/SDL2/include" }

    --libdirs { "vendor/SDL2/lib" }  -- Adjust this based on your OS
    --links { "SDL2", "SDL2main" }

    filter "system:windows"
        systemversion "latest"
        --links { "SDL2.lib", "SDL2main.lib" }

    --filter "system:linux"
        --links { "SDL2", "SDL2main", "SDL2_image", "m" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
