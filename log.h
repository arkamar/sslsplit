/*
 * SSLsplit - transparent and scalable SSL/TLS interception
 * Copyright (c) 2009-2013, Daniel Roethlisberger <daniel@roe.ch>
 * All rights reserved.
 * http://www.roe.ch/SSLsplit
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LOG_H
#define LOG_H

#include "opts.h"
#include "logger.h"
#include "attrib.h"

int log_err_printf(const char *, ...) PRINTF(1,2);
void log_err_mode(int);
#define LOG_ERR_MODE_STDERR 0
#define LOG_ERR_MODE_SYSLOG 1

int log_dbg_printf(const char *, ...) PRINTF(1,2);
int log_dbg_print_free(char *);
int log_dbg_write_free(void *, size_t);
void log_dbg_mode(int);
#define LOG_DBG_MODE_NONE 0
#define LOG_DBG_MODE_ERRLOG 1

extern logger_t *connect_log;
#define log_connect_printf(fmt, ...) \
        logger_printf(connect_log, -1, (fmt), __VA_ARGS__)
#define log_connect_print(s) \
        logger_print(connect_log, -1, (s))
#define log_connect_write(buf, sz) \
        logger_write(connect_log, -1, (buf), (sz))
#define log_connect_print_free(s) \
        logger_print_freebuf(connect_log, -1, (s))
#define log_connect_write_free(buf, sz) \
        logger_write_freebuf(connect_log, -1, (buf), (sz))

typedef struct log_content_ctx {
	int open;
	char *basedir;
	int fd;
	char *header_in;
	char *header_out;
} log_content_ctx_t;
void log_content_open(log_content_ctx_t *, char *, char *) NONNULL();
void log_content_submit(log_content_ctx_t *, logbuf_t *, int) NONNULL();
void log_content_close(log_content_ctx_t *) NONNULL();

int log_preinit(opts_t *) NONNULL() WUNRES;
int log_init(opts_t *) NONNULL() WUNRES;
void log_fini(void);

#endif /* !LOG_H */

/* vim: set noet ft=c: */
