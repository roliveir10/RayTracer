#include "libft.h"
#include <unistd.h>

int			ft_readFile(int fd, char **file, size_t max)
{
	int		ret
	char		buffer[BUFF_SIZE + 1];
	char		*tmp;
	size_t		length = 0;

	*file = ft_strnew(1);
	buffer[BUFF_SIZE] = '\0';
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0) && (length += result < max)
	{
		tmp = *file;
		if (result < BUFF_SIZE)
			buffer[result] = '\0';
		file = ft_strjoinf(tmp, buffer);
	}
	if (ret < 0)
	{
		if (*file)
			free(*file);
		return (0);
	}
	return (1);
}
