#ifndef _BUILD_DEFS_H_
#define _BUILD_DEFS_H_

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define XASH_WINDOWS
#endif

#if defined(__APPLE__) || defined(MACOSX)
#define XASH_MACOSX
#endif

#if !defined(XASH_MACOSX) && !defined(XASH_WINDOWS)
#define XASH_LINUX
#endif


#endif //_BUILD_DEFS_H_
