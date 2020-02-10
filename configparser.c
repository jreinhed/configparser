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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "configparser.h"

/*
 * Find an option in the opts array.
 * Arguments:
 * 	opt - Option name to look for
 * 	opts - Array of options
 * Returns place in array if found, -1 otherwise.
 */
int find_opt(char *opt, struct config_opt *opts)
{
	int n = 0;
	while (opts[n].opt_name != NULL) {
		/* Ignore already processed options */
		if (opts[n].processed == 1) {
			n++;
			continue;
		}

		if (strcmp(opt, opts[n].opt_name) == 0)
			return n;
		else
			n++;
	}

	return -1;
}

/*
 * Strip leading and trailing whitespace from str.
 * Modifies str!
 */
void strip_whitespace(char **str)
{
	while (isspace(**str)) {
		(*str)++;
	}

	char *end = strchr(*str, '\0') - 1;

	while (isspace(*end)) {
		end--;
	}
	*(end+1) = '\0';
}

/*
 * Parse config file.
 * Arguments:
 * 	filename - name of config file
 * 	opts - pointer to array of options
 * Returns zero if successful, negative number otherwise.
 */
int read_config(char *filename, struct config_opt *opts)
{
	char line[2048];
	char *opt, *val;
	FILE *file = fopen(filename, "r");

	if (file == NULL || opts == NULL)
		return -1;

	while (fgets(line, 2048, file) != NULL) {
		if (line[0] == '#' || line[0] == '\n')
			continue;

		if ((opt = strtok(line, "=")) != NULL) {
			strip_whitespace(&opt);
			int n = find_opt(opt, opts);

			/* Ignore unknown options */
			if (n < 0) {
				continue;
			}
			
			val = strtok(NULL, "\n");
			strip_whitespace(&val);

			int datatype = opts[n].datatype;

			if (datatype == DATATYPE_STR) {
				char **p = opts[n].value;
				strcpy(*p, val);
			} else if (datatype == DATATYPE_INT) {
				int *p = opts[n].value;
				*p = strtol(val, NULL, 0);
			} else if (datatype == DATATYPE_FLOAT) {
				float *p = opts[n].value;
				*p = strtof(val, NULL);
			} else if (datatype == DATATYPE_DOUBLE) {
				double *p = opts[n].value;
				*p = strtod(val, NULL);
			}

			opts[n].processed = 1;
		}
	}
	fclose(file);
	return 0;
}
