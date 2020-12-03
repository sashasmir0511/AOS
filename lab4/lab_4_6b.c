#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int		main()
{
	char buf[512];
	int f, l;

	write(0, "before open fifo\n", 17);
	if ((f = open("fifo", O_WRONLY)) == -1)
	{
		perror("fifo: ");
		exit(1);
	}
	write(0, "after open fifo\n", 16);
	while ((l = read(0, buf, sizeof(buf))) > 0)
		write(f, buf, l);
	close(f);
	exit(0);

}
