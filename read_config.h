/*
 * Copyright (c) 2019 Johan Reinhed <jreinhed@protonmail.com>
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef READ_CONFIG_H
#define READ_CONFIG_H

#define DATATYPE_STR    1
#define DATATYPE_INT    2
#define DATATYPE_FLOAT  3
#define DATATYPE_DOUBLE 4

struct config_opt {
	char *opt_name;
	void *value;
	int datatype;
};

/*
 * Parse config file.
 * Arguments:
 * 	filename - name of config file
 * 	opts - pointer to array of options
 * Returns zero if successful, negative number otherwise.
 */
int read_config(char *, struct config_opt *);

#endif /* READ_CONFIG_H */
