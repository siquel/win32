--
-- Copyright (c) 2017 Jani Niemelä.
-- License: https://github.com/siquel/win32/blob/master/LICENSE
--

WIN32_DIR = path.getabsolute("..")
local WIN32_BUILD_DIR = path.join(WIN32_DIR, ".build")
local WIN32_THIRD_PARTY_DIR = path.join(WIN32_DIR, "3rdparty")

solution "win32"
	configurations {
		"Debug",
		"Release"
	}

	platforms {
		"x64"
	}

	language "C++"

	configuration "Debug"
		defines {
			"HOTSWAP_DEBUG=1"
		}

	configuration {}

dofile("toolchain.lua")
if not toolchain(WIN32_BUILD_DIR, WIN32_THIRD_PARTY_DIR) then
    return
end

project "win32"
	kind "WindowedApp"

	files {
		path.join(WIN32_DIR, "src/**.cpp"),
		path.join(WIN32_DIR, "src/**.h")
	}

	flags {
	    "WinMain"
	}

	includedirs {
		path.join(WIN32_DIR, "src")
	}

	strip()

-- Because VS does not want to edit files when debugging
solution "hotswap"
	configurations {
		"Debug",
		"Release"
	}

	platforms {
		"x64"
	}

	language "C++"

	configuration "Debug"
		defines {
			"HOTSWAP_DEBUG=1"
		}

	configuration {}

dofile("toolchain.lua")
if not toolchain(WIN32_BUILD_DIR, WIN32_THIRD_PARTY_DIR) then
	return
end

project "hotswap"
	kind "SharedLib"

	files {
		path.join(WIN32_DIR, "hotswap/**.cpp"),
		path.join(WIN32_DIR, "hotswap/**.h")
	}

	includedirs {
		path.join(WIN32_DIR, "src")
	}