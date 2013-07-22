//Types for engine

#ifndef _TYPES_H_
#define _TYPES_H_

#ifdef __cplusplus
#define CHECK_IF_CPP() (extern "C" {)
#define END_CHECK_IF_CPP() (})
#else
#define CHECK_IF_CPP()
#define END_CHECK_IF_CPP()
#endif

CHECK_IF_CPP()




#ifdef XASH_COMPLIER_GNUC
#include <stdint.h>
typedef enum
{
	TRUE 	= 0x1,
	FALSE 	= 0x0
}BOOL;

typedef void* PVOID;
typedef PVOID LPVOID;
typedef PVOID HWND;
typedef PVOID HANDLE;
typedef PVOID HINSTANCE;

typedef uint8_t BYTE;
typedef char CHAR;
typedef char LPSTR;
typedef const char* LPCSTR;
typedef long LONG;

#define _stdcall
#define __cdecl __attribute__((__cdecl__))
#define _inline inline
#define BI_RGB 0
#define MAX_PATHLEN 256

#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Winvalid-offsetof"
#pragma GCC diagnostic ignored "-Wconversion-null"
#pragma GCC diagnostic ignored "-Wswitch"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wparentheses"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#pragma GCC diagnostic ignored "-Wformat-extra-args"
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Waddress"
#pragma GCC diagnostic ignored "-Wunused-value"
#pragma GCC diagnostic ignored "-Wtype-limits"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

// disable some warnings
#ifdef XASH_COMPLIER_VISUAL
#pragma warning(disable : 4244)	// MIPS
#pragma warning(disable : 4018)	// signed/unsigned mismatch
#pragma warning(disable : 4305)	// truncation from const double to float
#pragma warning(disable : 4115)	// named type definition in parentheses
#pragma warning(disable : 4100)	// unreferenced formal parameter
#pragma warning(disable : 4127)	// conditional expression is constant
#pragma warning(disable : 4057)	// differs in indirection to slightly different base types
#pragma warning(disable : 4201)	// nonstandard extension used
#pragma warning(disable : 4706)	// assignment within conditional expression
#pragma warning(disable : 4054)	// type cast' : from function pointer
#pragma warning(disable : 4310)	// cast truncates constant value
#endif



#define MAX_STRING		256	// generic string
#define MAX_INFO_STRING	256	// infostrings are transmitted across network
#define MAX_SYSPATH		1024	// system filepath
#define MAX_MODS		512	// environment games that engine can keep visible

#ifdef XASH_COMPLIER_VISUAL
#define EXPORT		__declspec( dllexport )
#elif defined(XASH_COMPLIER_GNUC)
#define EXPORT
#endif

typedef unsigned long	dword;
typedef unsigned int	uint;
typedef char		string[MAX_STRING];
typedef long		fs_offset_t;
typedef struct file_s	file_t;		// normal file
typedef struct wfile_s	wfile_t;		// wad file
typedef struct stream_s	stream_t;		// sound stream for background music playing


END_CHECK_IF_CPP()

#endif /*_TYPES_H_*/
