#pragma once

#if !defined(HOTSWAP_DEBUG)
#   define HOTSWAP_DEBUG 0
#endif

#define HOTSWAP_PLATFORM_WIN32 0
#define HOTSWAP_COMPILER_MSVC 0

#if defined(_WIN32)
#   undef HOTSWAP_PLATFORM_WIN32
#   define HOTSWAP_PLATFORM_WIN32 1
#else
#   error "unsupported platform"
#endif

#if defined(_MSC_VER)
#   undef HOTSWAP_COMPILER_MSVC
#   define HOTSWAP_COMPILER_MSVC _MSC_VER
#endif