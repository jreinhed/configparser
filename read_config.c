#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "read_config.h"

/*
 * Find an option in the opts array.
 * Arguments:
 * 	opt - Option name to look for
 * 	opts - Array of options
 * Returns place in array if found, 0 otherwise.
 */
int find_opt(char *opt, struct config_opt *opts)
{
	int n = 0;
	while (opts[n].opt_name != NULL) {
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

	if (file == NULL)
		return -1;

	while (fgets(line, 2048, file) != NULL) {
		/* TODO: Allow in-line comments */
		if (line[0] == '#' || line[0] == '\n')
			continue;

		if ((opt = strtok(line, "=")) != NULL) {
			strip_whitespace(&opt);
			printf("opt=%s\n", opt);
			int n = find_opt(opt, opts);

			/* Ignore unknown options */
			if (n < 0) {
				continue;
			}
			
			val = strtok(NULL, "\n");
			strip_whitespace(&val);
			printf("val=%s\n", val);

			int datatype = opts[n].datatype;

			if (datatype == DATATYPE_STRING) {
				char **p = opts[n].value;
				strcpy(*p, val);
			} else if (datatype == DATATYPE_INT) {
				int *p = opts[n].value;
				*p = strtol(val, NULL, 0);
			}
		}
	}
	fclose(file);
	return 0;
}