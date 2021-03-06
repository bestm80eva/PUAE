 /*
  * PUAE - The portable Amiga emulator
  *
  * Standard write_log that writes to the console or to a file.
  *
  * Copyright 2001 Bernd Schmidt
  * Copyright 2006 Richard Drummond
  */
#include "sysconfig.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>

#include "uae_string.h"
#include "uae_types.h"
#include "writelog.h"

static FILE *logfile;

/*
 * By default write-log and friends access the stderr stream.
 * This function allows you to specify a file to be used for logging
 * instead.
 *
 * Call with NULL to close a previously opened log file.
 */
void set_logfile (const char *logfile_name)
{
    if (logfile_name && strlen (logfile_name)) {
	FILE *newfile = fopen (logfile_name, "w");

	if (newfile)
	    logfile = newfile;
    } else {
		if (logfile) {
		    fclose (logfile);

		    logfile = 0;
		}
    }
}

void write_log (const char *fmt, ...)
{
    va_list ap;
    va_start (ap, fmt);
#ifdef HAVE_VFPRINTF
    vfprintf (logfile ? logfile : stderr, fmt, ap);
#else
    /* Technique stolen from GCC.  */
    {
	int x1, x2, x3, x4, x5, x6, x7, x8;
	x1 = va_arg (ap, int);
	x2 = va_arg (ap, int);
	x3 = va_arg (ap, int);
	x4 = va_arg (ap, int);
	x5 = va_arg (ap, int);
	x6 = va_arg (ap, int);
	x7 = va_arg (ap, int);
	x8 = va_arg (ap, int);
	fprintf (logfile ? logfile : stderr, fmt, x1, x2, x3, x4, x5, x6, x7, x8);
    }
#endif
}

#ifdef JIT
void jit_abort (const char *fmt, ...)
{
    va_list ap;
    va_start (ap, fmt);
#ifdef HAVE_VFPRINTF
    vfprintf (logfile ? logfile : stderr, fmt, ap);
#else
    /* Technique stolen from GCC.  */
    {
	int x1, x2, x3, x4, x5, x6, x7, x8;
	x1 = va_arg (ap, int);
	x2 = va_arg (ap, int);
	x3 = va_arg (ap, int);
	x4 = va_arg (ap, int);
	x5 = va_arg (ap, int);
	x6 = va_arg (ap, int);
	x7 = va_arg (ap, int);
	x8 = va_arg (ap, int);
	fprintf (logfile ? logfile : stderr, fmt, x1, x2, x3, x4, x5, x6, x7, x8);
    }
#endif
	uae_reset(1);
}
#endif

void flush_log (void)
{
    fflush (logfile ? logfile : stderr);
}

// Write Debug Log
void write_dlog (const char *format, ...)
{

}

static char *console_buffer;
static int console_buffer_size;

char *setconsolemode (char *buffer, int maxlen)
{
        char *ret = NULL;
        if (buffer) {
                console_buffer = buffer;
                console_buffer_size = maxlen;
        } else {
                ret = console_buffer;
                console_buffer = NULL;
        }
        return ret;
}
