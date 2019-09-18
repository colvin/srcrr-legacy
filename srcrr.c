/*
 * srcrr
 * Copyright (c) 2019, Colvin Wellborn
 */

#define _GNU_SOURCE
#include <dirent.h>
#include <err.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define VERSION "1.0.1"

#define SOURCE_FILE_MAX 3

void	usage(void);
char	*walk_dir(char *);
void	emit(char *);

const char *progname;
char *srcpath;
char *request;
char *source_files[SOURCE_FILE_MAX];
int source_file_cnt = 0;

int vflag = 0;
int lflag = 0;
int Sflag = 0;
int Uflag = 0;
int Pflag = 0;

int
main(int argc, char *argv[])
{
	progname = argv[0];

	int ch;

	while ((ch = getopt(argc, argv, "hVvlSUP")) != -1) {
		switch(ch) {
		case 'h':
			usage();
			exit(0);
		case 'V':
			printf("srcrr version %s\n", VERSION);
			exit(0);
		case 'v':
			vflag = 1;
			break;
		case 'l':
			lflag = 1;
			break;
		case 'S':
			Sflag = 1;
			break;
		case 'U':
			Uflag = 1;
			break;
		case 'P':
			Pflag = 1;
			break;
		}
	}

	request = argv[optind];
	if ((!lflag) && (request == NULL)) {
		usage();
		exit(1);
	}

	if (!Sflag)
		source_files[source_file_cnt++] = "/etc/srcrrrc";

	if (!Uflag)
		source_files[source_file_cnt++] = "$HOME/.srcrrrc";

	if (!Pflag)
		source_files[source_file_cnt++] = ".srcrrrc";

	srcpath = getenv("SRCPATH");
	if (srcpath == NULL)
		return (1);

	char *elem, *proj;
	for (elem = strtok(srcpath, ":"); elem != NULL; elem = strtok(NULL, ":")) {
		if ((proj = walk_dir(elem)) != NULL) {
			emit(proj);
			free(proj);
			return (0);
		}
	}

	return (0);
}

void
usage(void)
{
	fprintf(stderr, "usage: %s [-vSUP] PROJECT_NAME\n", progname);
	fprintf(stderr, "       %s -l\n", progname);
	fprintf(stderr, "       %s -V\n", progname);
	fprintf(stderr, "       %s -h\n", progname);
}

char *
walk_dir(char *path)
{
	DIR *dh;
	struct dirent *ent;
	char *proj = NULL;

	if ((dh = opendir(path)) == NULL) {
		if (vflag) fprintf(stderr, "** failed to open directory %s: %s\n", path, strerror(errno));
		return (NULL);
	}

	while ((ent = readdir(dh)) != NULL) {
		if (lflag) {
			if ((strcmp(ent->d_name, ".") == 0) || ((strcmp(ent->d_name, "..")) == 0))
			    continue;
			printf("%s\n", ent->d_name);
			continue;
		}

		if (strcmp(ent->d_name, request) == 0) {
			if (asprintf(&proj, "%s/%s", path, ent->d_name) == -1)
				exit(1); // out of memory
			closedir(dh);
			return (proj);
		}
	}

	closedir(dh);
	return (NULL);
}

void
emit(char *proj)
{
	printf("cd %s ;\n", proj);
	if (source_file_cnt) {
		printf("for i in ");
		for (int i = 0; i < source_file_cnt; i++) {
			printf(" %s", source_files[i]);
		}
		printf(" ;\n");
		printf("do\n");
		printf("\ttest -f $i && . $i ;\n");
		printf("done\n");
	}
}
