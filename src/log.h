/**
* Copyright (c) 2017 rxi
*
* This library is free software; you can redistribute it and/or modify it
* under the terms of the MIT license. See `log.c` for details.
*/

#ifndef LOG_H
#define LOG_H
#include "stdafx.h"
#include <stdio.h>
#include <stdarg.h>

#define LOG_VERSION "0.1.0"
#define LOG_USE_COLOR

typedef void(*log_LockFn)(void *udata, int lock);

enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };

#define log_trace(msg,...) log_log(LOG_TRACE, _T(__FILE__), __LINE__, _T(msg), ##__VA_ARGS__)
#define log_debug(msg,...) log_log(LOG_DEBUG, _T(__FILE__), __LINE__, _T(msg), ##__VA_ARGS__)
#define log_info(msg,...)  log_log(LOG_INFO,  _T(__FILE__), __LINE__, _T(msg), ##__VA_ARGS__)
#define log_warn(msg,...)  log_log(LOG_WARN,  _T(__FILE__), __LINE__, _T(msg), ##__VA_ARGS__)
#define log_error(msg,...) log_log(LOG_ERROR, _T(__FILE__), __LINE__, _T(msg), ##__VA_ARGS__)
#define log_fatal(msg,...) log_log(LOG_FATAL, _T(__FILE__, __LINE__, _T(msg), ##__VA_ARGS__)

void log_set_udata(void *udata);
void log_set_lock(log_LockFn fn);
void log_set_fp(FILE *fp);
void log_set_level(int level);
void log_set_quiet(int enable);

void log_log(int level, const TCHAR *file, int line, const TCHAR *fmt, ...);

#endif
