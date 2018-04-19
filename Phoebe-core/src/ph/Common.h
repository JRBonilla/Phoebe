#pragma once

#ifdef _WIN32
#ifdef PHOEBE_DLL
#define PHOEBE_API __declspec(dllexport)
#else
#define PHOEBE_API __declspec(dllimport)
#endif
#endif

#ifdef _MSC_VER
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline __attribute__((always_inline))
#endif

#define BIT(num) (1 << num)