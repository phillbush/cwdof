#include <sys/types.h>
#include <sys/sysctl.h>

#include <err.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	size_t len;
	pid_t pid;
	const char *errstr;
	char path[PATH_MAX];

	if (pledge("stdio ps", NULL) == -1)
		err(1, "pledge");
	if (argc != 2) {
		(void)fprintf(stderr, "usage: %s pid\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	pid = strtonum(argv[1], 1, LLONG_MAX, &errstr);
	if (errstr != NULL)
		errc(EXIT_FAILURE, EINVAL, "%s", argv[1]);
	len = PATH_MAX;
	if (sysctl((int []){CTL_KERN, KERN_PROC_CWD, pid}, 3, path, &len, NULL, 0) == -1)
		err(1, "sysctl");
	(void)printf("%s\n", path);
	return EXIT_SUCCESS;
}
