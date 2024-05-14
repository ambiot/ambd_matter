#ifndef PLATFORM_STDLIB_MATTER_H
#define PLATFORM_STDLIB_MATTER_H

#if defined(CONFIG_PLATFORM_8721D)

#include <sys/time.h>
#include <assert.h>

extern char * _strtok_r( char *s , const char *delim , char **lasts);
extern int _nanosleep( const struct timespec * rqtp, struct timespec * rmtp );
extern int _vTaskDelay( const TickType_t xTicksToDelay );
extern time_t _time( time_t * tloc );

#ifndef false
    #define false   0
#endif

#ifndef true
    #define true    1
#endif

#ifndef strtok_r
    #define strtok_r(s, delim, lasts)	  _strtok_r (s, delim, lasts)
#endif

#ifndef usleep
    #define usleep(x)    _vTaskDelay(x)
#endif

#ifndef nanosleep
    #define nanosleep    _nanosleep
#endif

#ifndef in_addr_t
    typedef __uint32_t in_addr_t;
#endif

#ifdef strtok
    #undef strtok
#endif

#ifdef strtol
    #undef strtol
#endif

#ifdef rand
    #undef rand
#endif

#ifdef srand
    #undef srand
#endif

#ifdef IN
    #undef IN
#endif

#ifdef vsnprintf
	#undef vsnprintf
#endif

#ifdef memcpy
	#undef memcpy
#endif

#ifdef memset
	#undef memset
#endif

#ifdef strcmp
	#undef strcmp
#endif

#ifdef strncpy
	#undef strncpy
#endif

#ifdef strlen
	#undef strlen
#endif

#endif /* CONFIG_PLATFORM_XXXX */

#endif // PLATFORM_STDLIB_MATTER_H
