#ifndef READ_CONFIG_H
#define READ_CONFIG_H

#define DATATYPE_STR 1
#define DATATYPE_INT 2

struct config_opt {
	char *opt_name;
	void *value;
	int datatype;
};

int read_config(char *, struct config_opt *);

#endif /* READ_CONFIG_H */
