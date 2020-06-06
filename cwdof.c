#include <sys/types.h>
#include <sys/sysctl.h>
#include <err.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN(x) (sizeof (x) / sizeof (x[0]))

static char *cwdof(pid_t);
static void usage(void);

/* print current working directory of given pid */
int
main(int argc, char *argv[])
{
	pid_t pid;
	const char *errstr;
	char *path;

	argc--;
	argv++;

	if (argc != 1)
		usage();

	pid = strtonum(*argv, 1, LLONG_MAX, &errstr);
	if (!isdigit(**argv) || errstr != NULL)
		errx(EXIT_FAILURE, "Improper pid");

	if ((path = cwdof(pid)) == NULL)
		err(EXIT_FAILURE, NULL);

	printf("%s\n", path);

	return EXIT_SUCCESS;
}

/* return current working directory of pid */
static char *
cwdof(pid_t pid)
{
	static char path[PATH_MAX];
	size_t len = sizeof path;
	int name[] = {CTL_KERN, KERN_PROC_CWD, pid};

	if (sysctl(name, LEN(name), path, &len, NULL, 0) == -1)
		return NULL;

	return path;
}

/* show usage */
static void
usage(void)
{
	(void) fprintf(stderr, "usage: %s pid\n", getprogname());
	exit(EXIT_FAILURE);
}
