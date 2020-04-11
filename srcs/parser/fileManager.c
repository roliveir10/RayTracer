#include <fcntl.h>
#include <unistd.h>
#include "rt.h"

static char			*read_file(int fd)
{
	int			ret;
	char			*file;
	char			buff[1024];

	file = ft_strnew(1);
	while ((ret = read(fd, buff, 1023)) > 0)
	{
		buff[ret] = '\0';
		file = ft_strjoinf(file, buff);
	}
	close(fd);
	return (file);
}

char				*open_file(char *argv)
{
	int			fd;

	if ((fd = open(argv, O_RDONLY)) == -1)
	{
		dprintf(2, "can not open: %s for reading\n", argv);
		return (0);
	}
	return (read_file(fd));
}
