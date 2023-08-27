workspace "CoC"
  architecture "x64"

  configurations {
    "Release",
    "Debug"
  }
  

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "CoC"
  location "CoC"
  kind "ConsoleApp"
  language "c++"

  targetdir("bin/" .. outputdir .. "/%{prj.name}")
  objdir("bin/int/" .. outputdir .. "/%{prj.name}")

  files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
  }

  includedirs
  {
    "%{prj.name}/src/vendor/nlohmann-json"
  }

  filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"