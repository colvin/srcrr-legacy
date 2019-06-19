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

void	usage(void);
char	*walk_dir(char *);
void	emit(char *);

const char *progname;
char *srcpath;
char *request;

int vflag = 0;
int lflag = 0;

int
main(int argc, char *argv[])
{
	progname = argv[0];

	int ch;

	while ((ch = getopt(argc, argv, "vhl")) != -1) {
		switch(ch) {
		case 'h':
			usage();
			exit(0);
		case 'v':
			vflag = 1;
			break;
		case 'l':
			lflag = 1;
			break;
		}
	}

	request = argv[optind];
	if ((!lflag) && (request == NULL)) {
		usage();
		exit(1);
	}

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
	printf("usage: %s [-vh] PROJECT\n", progname);
	printf("       %s -l\n", progname);
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
	printf("cd %s ; test -f .srcrrrc && . .srcrrrc\n", proj);
}
