#pragma once

#ifdef _WIN32
#ifdef PHOENIX_DLL
#define PHOENIX_API __declspec(dllexport)
#else
#define PHOENIX_API __declspec(dllimport)
#endif
#endif

#ifdef _MSC_VER
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline __attribute__((always_inline))
#endif