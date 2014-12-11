#ifndef TINYLOG_H
#define TINYLOG_H
#include <stdio.h>
#include <time.h>
/* simple log wrapper for c
 * Author: hardy.liu at foxmail dot com
 */
/*********************************************************
#include "tinylog.h"
API:
tlog_debug(format, ...)
tlog_info(format, ...)
tlog_warn(format, ...)
tlog_error(format, ...)
tlog_fatal(format, ...)

Usage:
gcc -o app xxx.c -DTINYLOG -DTL_LEVEL=TL_DEBUG -DTL_PREFIX=7

TL_LEVEL:
TL_DEBUG-->TL_INFO-->TL_WARN-->TL_ERROR-->TL_FATAL
LEFT <=====================================> RIGHT

TL_PREFIX:

MODE:	|	TL_FILE	|	TL_TIME	|	TL_FUNC	|	TL_NONE	|
VALUE:	|	4		|		2	|	1		|	0		|
TL_PREFIX = SUM(VALUE)

eg. select TL_TIME and TL_FUNC
VALUE =		2		+		1	:	-DTL_PREFIX=3
************************************************************/


/* Debug level
 * Default: WARN
 */
#define TL_DEBUG	4
#define TL_INFO		3
#define TL_WARN		2
#define TL_ERROR	1
#define TL_FATAL	0

#ifndef TL_LEVEL
#define TL_LEVEL	TL_WARN
#endif

/* Output channel: stdout or stderr
 * Default channel is stderr
 */
#ifndef TL_OUT
#define TL_OUT	stderr
#endif

/* TL_PREFIX VALUE */
#define TL_NONE		0
#define TL_FUNC		1
#define TL_TIME		2
#define TL_FILE		4

/* Default TL_PREFIX */
#ifndef TL_PREFIX
#define TL_PREFIX	(TL_TIME)
#endif

#if TL_PREFIX == 3
#define TEST	%s:%d
#else
#define TEST	""

#endif
#if (TL_PREFIX & TL_TIME)	!=	0
#define FMT_TIME	"%02d-%02d %02d:%02d:%02d "
#define ARG_TIME	,tm->tm_mon, tm->tm_mday,\
					tm->tm_hour, tm->tm_min, tm->tm_sec

#define INIT_TIME	time_t t;struct tm *tm; time(&t); tm = localtime(&t);
#else
#define FMT_TIME	""
#define ARG_TIME
#define INIT_TIME
#endif

#if (TL_PREFIX & TL_FILE)	!=	0
#define FMT_FILE	"%s:%d"
#define ARG_FILE	,__FILE__,__LINE__

#ifndef BRACKET
#define BRACKET
#endif
#else
#define FMT_FILE	""
#define ARG_FILE

#endif

#if (TL_PREFIX & TL_FUNC)	!=	0
/* if print file then print spacing */
#if (TL_PREFIX & TL_FILE)	!=	0
#define FMT_FUNC	"%s|"
#else
#define FMT_FUNC	"%s"
#endif
/* end if*/
#define ARG_FUNC	,__FUNCTION__
#ifndef BRACKET
#define BRACKET
#endif
#else
#define FMT_FUNC	""
#define ARG_FUNC
#endif

#if defined(BRACKET)
#define BRACKET_LEFT	" ["
#define BRACKET_RIGHT	"]: "
#else
#define BRACKET_LEFT	""
#define BRACKET_RIGHT	": "
#endif

#ifdef TINYLOG
#define tinylog(level, format, ...)											\
	do {																	\
		INIT_TIME															\
		if (level <= TL_LEVEL) {											\
			fprintf(TL_OUT, FMT_TIME "%s" BRACKET_LEFT FMT_FUNC FMT_FILE	\
				BRACKET_RIGHT format"\n" ARG_TIME ,((char *)#level + 3)		\
				ARG_FUNC ARG_FILE, ##__VA_ARGS__);							\
		}																	\
	} while (0)
#else
#define tinylog(level, format, ...)
#endif

#define tlog_debug(format, ...)	tinylog(TL_DEBUG, format, ##__VA_ARGS__)
#define tlog_info(format, ...)	tinylog(TL_INFO, format, ##__VA_ARGS__)
#define tlog_warn(format, ...)	tinylog(TL_WARN, format, ##__VA_ARGS__)
#define tlog_error(format, ...)	tinylog(TL_ERROR, format, ##__VA_ARGS__)
#define tlog_fatal(format, ...)	tinylog(TL_FATAL, format, ##__VA_ARGS__)

#endif
