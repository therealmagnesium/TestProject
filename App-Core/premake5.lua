local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project("App-Core")
kind("StaticLib")
language("C++")
cppdialect("C++17")

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../build/" .. outputdir .. "/%{prj.name}")

files({
    "source/**.h",
    "source/**.cpp",
})

includedirs({
    "source",
    "../vendor/raylib/include",
    "../vendor/imgui/include",
    "../vendor/tmx/include",
})

libdirs({
    "../vendor/raylib/lib",
    "../vendor/imgui/lib",
    "../vendor/tmx/lib",
})

links({
    "raylib",
    "imgui",
    "tmx",
    "z",
    "xml2",
})

filter("system:Unix")
system("linux")
systemversion("latest")
defines({
    "PLATFORM_LINUX",
})

filter({ "configurations:Debug" })
defines("DEBUG")
symbols("on")

filter({ "configurations:Release" })
defines("RELEASE")
optimize("on")

filter({ "configurations:Dist" })
defines("DIST")
optimize("on")
