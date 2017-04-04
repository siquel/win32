--
-- Copyright (c) 2017 Jani Niemelä.
-- License: https://github.com/siquel/win32/blob/master/LICENSE
--

-- Adapted from Branimir Karadžić's toolchain.lua (https://github.com/bkaradzic/bx)

function toolchain(build_dir, lib_dir)
    newoption {
        trigger = "gcc",
        value   = "GCC",
        description = "Choose GCC flavor",
        allowed = {
            { "linux-gcc", "Linux GCC compiler" },
            { "linux-clang", "Linux Clang compiler" },
            { "asmjs", "Emscripten/asm.js" }
        }
    }

    if (_ACTION == nil) then return false end

    location(path.join(build_dir, "projects", _ACTION))

    if _ACTION == "clean" then
        os.rmdir(BUILD_DIR)
    end

    if _ACTION == "gmake" then
        if nil == _OPTIONS["gcc"] then
            print("Choose a GCC flavor!")
            os.exit(1)
        end

        if "linux-gcc" == _OPTIONS["gcc"] then
            location(path.join(build_dir, "projects", _ACTION .. "-linux"))
        elseif "linux-clang" == _OPTIONS["gcc"] then
            premake.gcc.cc  = "clang"
            premake.gcc.cxx = "clang++"
            premake.gcc.ar  = "ar"
            location(path.join(build_dir, "projects", _ACTION .. "-linux-clang"))

        elseif "asmjs" == _OPTIONS["gcc"] then

            if not os.getenv("EMSCRIPTEN") then
                print("Set EMSCRIPTEN enviroment variable.")
            end

            premake.gcc.cc   = "\"$(EMSCRIPTEN)/emcc\""
            premake.gcc.cxx  = "\"$(EMSCRIPTEN)/em++\""
            premake.gcc.ar   = "\"$(EMSCRIPTEN)/emar\""
            premake.gcc.llvm = true
            location (path.join(build_dir, "projects", _ACTION .. "-asmjs"))
        end
    end

    flags {
        "NoPCH",
        "NativeWChar",
        "NoRTTI",
        "NoExceptions",
        "NoEditAndContinue",
        "NoFramePointer",
        "Symbols",
        "ExtraWarnings",
    }
    -- force PRIuXX etc. to be visible in C++ builds
    defines {
        "__STDC_LIMIT_MACROS",
        "__STDC_FORMAT_MACROS",
        "__STDC_CONSTANT_MACROS",
    }

    configuration { "Debug" }
        targetsuffix "Debug"
        defines { "_DEBUG" }

    configuration { "Release" }
        flags {
            "OptimizeSpeed",
            "NoBufferSecurityCheck"
        }
        defines {
            "NDEBUG"
        }
        targetsuffix "Release"

    configuration { "vs*" }
        includedirs {
            path.join(JN_DIR, "include/compat/msvc")
        }
        defines {
            "_WIN32",
            "_HAS_EXCEPTIONS=0",
            "_HAS_ITERATOR_DEBUGGING=0",
            "_SCL_SECURE=0",
            "_SECURE_SCL=0",
            "_SCL_SECURE_NO_WARNINGS",
            "_CRT_SECURE_NO_WARNINGS",
            "_CRT_SECURE_NO_DEPRECATE",
        }

        linkoptions {
            "/ignore:4221", -- LNK4221: This object file does not define any previously undefined public symbols, so it will not be used by any link operation that consumes this library
        }

    configuration { "x32", "vs*" }
        targetdir (path.join(build_dir, "win32_" .. _ACTION, "bin"))
        objdir    (path.join(build_dir, "win32_" .. _ACTION, "obj"))
        libdirs {
            path.join(lib_dir, "lib/win32_" .. _ACTION),
        }

    configuration { "x64", "vs*" }
        defines { "_WIN64" }
        targetdir (path.join(build_dir, "win64_" .. _ACTION, "bin"))
        objdir    (path.join(build_dir, "win64_" .. _ACTION, "obj"))
        libdirs {
            path.join(lib_dir, "lib/win64_" .. _ACTION),
        }

    configuration { "linux-gcc*", "x32" }
        targetdir (path.join(build_dir, "linux32_gcc/bin"))
        objdir    (path.join(build_dir, "linux32_gcc/obj"))
        libdirs {
            path.join(lib_dir, "lib/linux32_gcc")
        }
        buildoptions {
            "-m32",
        }

    configuration { "linux-gcc*", "x64" }
        targetdir (path.join(build_dir, "linux64_gcc/bin"))
        objdir    (path.join(build_dir, "linux64_gcc/obj"))
        libdirs {
            path.join(lib_dir, "lib/linux64_gcc")
        }
        buildoptions {
            "-m64",
        }

    configuration { "linux-clang", "x32" }
        targetdir (path.join(build_dir, "linux32_clang/bin"))
        objdir    (path.join(build_dir, "linux32_clang/obj"))
        libdirs {
            path.join(lib_dir, "lib/linux32_clang")
        }
        buildoptions {
            "-m32",
        }

    configuration { "linux-clang", "x64" }
        targetdir (path.join(build_dir, "linux64_clang/bin"))
        objdir    (path.join(build_dir, "linux64_clang/obj"))
        libdirs {
            path.join(lib_dir, "lib/linux64_clang")
        }
        buildoptions {
            "-m64",
        }

    configuration { "asmjs" }
        targetdir (path.join(build_dir, "asmjs/bin"))
        objdir (path.join(build_dir, "asmjs/obj"))
        libdirs { path.join(lib_dir, "lib/asmjs") }
        buildoptions {
            "-i\"system$(EMSCRIPTEN)/system/include\"",
            "-i\"system$(EMSCRIPTEN)/system/include/libc\"",
            "-Wunused-value",
            "-Wundef",
        }

    configuration {}
    return true
end

function strip()
    configuration { "linux-*", "Release" }
        postbuildcommands {
            "$(SILENT) echo Stripping symbols.",
            "$(SILENT) strip -s \"$(TARGET)\""
        }

    configuration { "asmjs" }
        postbuildcommands {
            "$(SILENT) echo Running asmjs finalize.",
            "$(SILENT) \"$(EMSCRIPTEN)/emcc\" -O2 "
--              .. "-s EMTERPRETIFY=1 "
--              .. "-s EMTERPRETIFY_ASYNC=1 "
            .. "-s TOTAL_MEMORY=268435456 "
            .. "-s USE_SDL=2 "
--          .. "-s ALLOW_MEMORY_GROWTH=1 "
--          .. "-s USE_WEBGL2=1 "
            .. "--memory-init-file 1 "
            .. "\"$(TARGET)\" -o \"$(TARGET)\".html "
--          .. "--preload-file ../../../examples/runtime@/"
        }

        configuration {} -- reset configuration
end
