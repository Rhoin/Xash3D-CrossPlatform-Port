#ifndef _BUILD_DEFS_H_
#define _BUILD_DEFS_H_

#ifdef _MSC_VER
#define XASH_COMPLIER_VISUAL
#endif

#ifdef __GNUC__
#define XASH_COMPLIER_GNUC
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define XASH_WINDOWS
#endif

#if defined(__APPLE__) || defined(MACOSX)
#define XASH_MACOSX
#endif

#if !defined(XASH_MACOSX) && !defined(XASH_WINDOWS)
#define XASH_UNIX //Not only linux.See README
#endif


#endif //_BUILD_DEFS_H_
