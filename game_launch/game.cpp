/*
game.cpp -- executable to run Xash Engine
Copyright (C) 2011 Uncle Mike

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/


#include "build_defs.h"
#if defined(XASH_WINDOWS)
#include <windows.h>
#elif defined(XASH_MACOSX)
//
//
//
#else
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <dlfcn.h>
#define TRUE  1
#define FALSE 0
#endif

#define GAME_PATH	"valve"	// default dir to start from

typedef void (*pfnChangeGame)( const char *progname );
typedef int (*pfnInit)( const char *progname, int bChangeGame, pfnChangeGame func );
typedef void (*pfnShutdown)( void );

pfnInit Host_Main;
pfnShutdown Host_Shutdown = NULL;
char szGameDir[128]; // safe place to keep gamedir
void *handle;

#ifdef XASH_WINDOWS
#define XASH_DLIB_NAME "xash.dll"
#elif XASH_MACOSX
#define XASH_DLIB_NAME "xash.dylib"
#else
#define XASH_DLIB_NAME "xash.so"
#endif

void Sys_Error( const char *errorstring )
{
#	if defined(XASH_WINDOWS)

	MessageBox( NULL, errorstring, "Xash Error", MB_OK|MB_SETFOREGROUND|MB_ICONSTOP );
	
#	elif defined(XASH_MACOSX)
	//
	//
	//
#	else
	Display *d;
	Window w;
	XEvent e;
	int s;
 
	d = XOpenDisplay(NULL);
	if (d == NULL) {
      fprintf(stderr, "Xash Error: %s\n",errorstring);
      exit(1);
	}
	
	s = DefaultScreen(d);
	XFontStruct *font = XLoadQueryFont(d, "fixed");
	w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 
	XTextWidth(font, errorstring, strlen(errorstring)) + 20, 100, 1,
                           BlackPixel(d, s), WhitePixel(d, s));
	XStoreName(d, w, "Xash Error");
	XSelectInput(d, w, ExposureMask | KeyPressMask);
	XMapWindow(d, w);
	XSetFont(d, DefaultGC(d,s), font->fid);
	while (1) {
      XNextEvent(d, &e);
      if (e.type == Expose) {
         XDrawString(d, w, DefaultGC(d, s), 10, 50, errorstring, strlen(errorstring));
      }
      if (e.type == KeyPress)
         break;
	}
 
	XUnloadFont(d, font->fid);
	XCloseDisplay(d);
#	endif
	exit( 1 );
}

void *dylLoad(const char *dl)
{
#	ifdef XASH_WINDOWS
	return (void*)LoadLibrary(XASH_DLIB_NAME);
#	else
	return dlopen(XASH_DLIB_NAME,RTLD_NOW);
#	endif
}

void *dylsym(const char *sym, void *handle)
{
#	ifdef XASH_WINDOWS
	return (void*)GetProcAddress((HINSTANCE)handle, sym);
#	else
	return dlsym(handle, sym);
#	endif
}

void dylUnload(void *handle)
{
#	ifdef XASH_WINDOWS
	FreeLibrary((HINSTANCE)handle);
#	else
	dlclose(handle);
#	endif
}

void Sys_LoadEngine( void )
{
	std::string err;
	if(( handle = dylLoad(XASH_DLIB_NAME)) == NULL )
	{
		err = "Unable to load the ";
		err += XASH_DLIB_NAME;
		Sys_Error( err.c_str() );
	}

	if(( Host_Main = (pfnInit)dylsym( "Host_Main", handle )) == NULL )
	{
		err = XASH_DLIB_NAME; 
		err += " missed 'Host_Main' export";
		Sys_Error( err.c_str() );
	}

	// this is non-fatal for us but change game will not working
	Host_Shutdown = (pfnShutdown)dylsym( "Host_Shutdown", handle );
}

void Sys_UnloadEngine( void )
{
	if( Host_Shutdown ) Host_Shutdown( );
	if( handle ) dylUnload( handle );
}

void Sys_ChangeGame( const char *progname )
{
	if( !progname || !progname[0] ) Sys_Error( "Sys_ChangeGame: NULL gamedir" );
	if( Host_Shutdown == NULL ) Sys_Error( "Sys_ChangeGame: missed 'Host_Shutdown' export\n" );
	strncpy( szGameDir, progname, sizeof( szGameDir ) - 1 );

	Sys_UnloadEngine ();
	Sys_LoadEngine ();
	
	Host_Main( szGameDir, TRUE, ( Host_Shutdown != NULL ) ? Sys_ChangeGame : NULL );
}
#ifdef XASH_WINDOWS
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
#else
int main(int argc, char **argv)
#endif
{
	Sys_LoadEngine();

	return Host_Main( GAME_PATH, FALSE, ( Host_Shutdown != NULL ) ? Sys_ChangeGame : NULL );
}
