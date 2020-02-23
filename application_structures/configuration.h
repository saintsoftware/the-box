
//------------------------------------------------------------------
// Config
//------------------------------------------------------------------

/// Enable static fonts
/**
	This will prevent the creation of a font index, so font drawing 
	will be slightly slower.  Unless you are on a memory constrained 
	system, you will probably prefer to leave this on.
*/
// #define EZD_STATIC_FONTS

/// Define if you do not have string.h
// #define EZD_NO_MEMCPY

/// Define if you do not have malloc, calloc, and free, 
/**
	ezd_flood_file() will not work.
*/
// #define EZD_NO_ALLOCATION

/// If you have no file handling routines
/**
	ezd_save() will not work
*/
// #define EZD_NO_FILES

/// If you do not have math.h.  Sorry, you won't get circles
/**
	ezd_circle() and ezd_arc() will not work
*/
// #define EZD_NO_MATH

// Debugging
#if defined( _DEBUG )
#	define EZD_DEBUG
#endif

//------------------------------------------------------------------
// Internal config
//------------------------------------------------------------------

#if !defined( EZD_NO_FILES )
#	include <stdio.h>
#endif

// malloc, calloc, free
#if !defined( EZD_NO_ALLOCATION )
#	if !defined( EZD_NO_STDLIB )
#		include <stdlib.h>
#	else
		// No debug functions without stdlib
#		undef EZD_DEBUG
#	endif
#	if !defined( EZD_malloc )
#		define EZD_malloc malloc
#	endif
#	if !defined( EZD_calloc )
#		define EZD_calloc calloc
#	endif
#	if !defined( EZD_free )
#		define EZD_free free
#	endif
#else
	// Must use static fonts if no allocation routines
#	define EZD_STATIC_FONTS
	// Assume our debug functions won't work either
#	undef EZD_DEBUG
#endif

// sin(), cos()
#if !defined( EZD_NO_MATH )
#	include <math.h>
#endif

// memcpy() and memset() substitutes
#if defined( EZD_NO_MEMCPY )
#	define EZD_MEMCPY ezd_memcpy
#	define EZD_MEMSET ezd_memset

static void ezd_memcpy( char *pDst, const char *pSrc, int sz )
{	
	while ( 0 < sz-- )
		*(char*)pDst++ = *(char*)pSrc++;
}
static void ezd_memset( char *pDst, int v, int sz )
{	
	while ( 0 < sz-- )
		*(char*)pDst++ = (char)v;
}
#else
#	include <string.h>
#	define EZD_MEMCPY memcpy
#	define EZD_MEMSET memset
#endif

#if defined( EZD_DEBUG )
#	define _MSG( m ) printf( "\n%s(%d): %s() : %s\n", __FILE__, __LINE__, __FUNCTION__, m )
#	define _SHOW( f, ... ) printf( "\n%s(%d): %s() : " f "\n", __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__ )
#	define _ERR( r, m ) ( _MSG( m ), r )
#else
#	define _MSG( m )
#	define _SHOW( ... )
#	define _ERR( r, m ) ( r )
#endif