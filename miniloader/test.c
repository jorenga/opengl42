#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define BUFLEN		4096

void				f_puts(char* s)
{
	int				len = strlen(s);

	write(1, s, len);
}

void                printT(unsigned long int t)
{
	int             m, s, ms, us;

	m = (t / 60000000);
	s = (t / 1000000) % 60;
	ms = (t / 1000) % 1000;
	us = t % 1000;
	printf("Parsing time: %dm%ds%dms%dus\n", m, s, ms, us);
}

void		realloc_cat(char** src, char* str, int size)
{
	char*	s;
	int		i = 0;
	int		len = strlen(*src);

	f_puts("1\n");
	s = (char*)malloc(sizeof(char) * (len + size + 1));
	f_puts("2\n");
	while (*src[i] != '\0')
	{
	f_puts("\ta\n");
		s[i] = *src[i];
	f_puts("\tb\n");
		i++;
	}
	f_puts("3\n");
	i =  0;
	while (i < size)
	{
		s[i + len] = str[i];
		i++;
	}
	f_puts("4\n");
	s[i + len] = '\0';
	f_puts("5\n");
	free(*src);
	*src = s;
	f_puts("6\n");
}

char*			fileToBuf(char* filename)
{
	char		buf[BUFLEN];
	int			fd = open(filename, O_RDONLY);
	int			ret;
	char*		src;

	src = (char*)malloc(sizeof(char));
	*src = '\0';
	while ((ret = read(fd, buf, BUFLEN)) != 0)
	{
	//	printf("read %d bytes:\n[%s]\n\t*  --  *\n", ret, buf);
		realloc_cat(&src, buf, ret);
		f_puts(src);
		f_puts("\n");
	}
	return (src);
}

int			main(int ac, char** av)
{
	struct timeval		start, end;
	unsigned long int	t, s, e;
	char*				src;

	if (ac != 2)
		return (0);
	gettimeofday(&start, NULL);
	src = fileToBuf(av[1]);
	gettimeofday(&end, NULL);

	printf("%s\n", src);

	s = start.tv_sec * 1000000 + start.tv_usec;
	e = end.tv_sec * 1000000 + end.tv_usec;
	t = e - s;
	printT(t);
	return (0);
}
