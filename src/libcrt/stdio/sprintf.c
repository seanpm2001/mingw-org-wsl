/**
 * @file sprintf.c
 * @copy 2012 MinGW.org project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/*
 * Provides an implementation of the "sprintf" function, conforming
 * generally to C99 and SUSv3/POSIX specifications, with extensions
 * to support Microsoft's non-standard format specifications.  This
 * is included in libmingwex.a, whence it may replace the Microsoft
 * function of the same name.
 *
 * This implementation of "sprintf" will normally be invoked by calling
 * "__mingw_sprintf()" in preference to a direct reference to "sprintf()"
 * itself; this leaves the MSVCRT implementation as the default, which
 * will be deployed when user code invokes "sprint()".  Users who then
 * wish to use this implementation may either call "__mingw_sprintf()"
 * directly, or may use conditional preprocessor defines, to redirect
 * references to "sprintf()" to "__mingw_sprintf()".
 *
 * Compiling this module with "-D INSTALL_AS_DEFAULT" will change this
 * recommended convention, such that references to "sprintf()" in user
 * code will ALWAYS be redirected to "__mingw_sprintf()"; if this option
 * is adopted, then users wishing to use the MSVCRT implementation of
 * "sprintf()" will be forced to use a "back-door" mechanism to do so.
 * Such a "back-door" mechanism is provided with MinGW, allowing the
 * MSVCRT implementation to be called as "__msvcrt_sprintf()"; however,
 * since users may not expect this behaviour, a standard libmingwex.a
 * installation does not employ this option.
 */
#include <stdio.h>
#include <stdarg.h>

#include "pformat.h"

int __cdecl __sprintf (char *, const char *, ...) __MINGW_NOTHROW;

#ifdef INSTALL_AS_DEFAULT
/*
 * This implementation is to become the default for calls to sprintf();
 * establish the alias to make this so, forcing users to use the back-door
 * __msvcrt_sprintf() reference, to access the original MSVCRT function.
 */
int __cdecl __mingw_alias(sprintf) (char *, const char *, ...) __MINGW_NOTHROW;

#endif

int __cdecl __sprintf( char *buf, const char *fmt, ... )
{
  register int retval;
  va_list argv; va_start( argv, fmt );
  buf[retval = __pformat( PFORMAT_NOLIMIT, buf, 0, fmt, argv )] = '\0';
  va_end( argv );
  return retval;
}

/* $RCSfile: sprintf.c,v $Revision: 1.1 $: end of file */
