/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejolyn <ejolyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:51:51 by ejolyn            #+#    #+#             */
/*   Updated: 2020/11/17 11:39:35 by ejolyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	const char *s2;

	s2 = s;
	while (*s)
		s++;
	return (s - s2);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char *copy;

	copy = s;
	while (n--)
		*copy++ = '\0';
}

char	*check_trunk(char **line, char *truncated)
{
	char *pointer_copy;
	int counter;

	counter = 0;
	pointer_copy = NULL;
	if (truncated && truncated[0] != 0)
	{
		if ((pointer_copy = ft_strchr(truncated, '\n')))
		{
			*pointer_copy = '\0';
			*line = ft_strdup(truncated);
			ft_strlcpy(truncated, ++pointer_copy, BUFFER_SIZE);
		}
		else
		{
			*line = ft_strdup(truncated);
			free(truncated);
			//ft_bzero(truncated, ft_strlen(truncated));
		}
	}
	else
		*line = ft_strdup("");
	return (pointer_copy);
}

int		get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE + 1];
	int				reading_bytes;
	static char		*truncated;
	char			*pointer_n;
	int				flag_n;
	
	flag_n = 1;
	pointer_n = check_trunk(line, truncated);
	while (flag_n && !(pointer_n) && (reading_bytes = read(fd, buf, BUFFER_SIZE)))
	{
		if ((pointer_n = ft_strchr(buf, '\n')))
		{
			*pointer_n = '\0';
			flag_n = 0;
			truncated = ft_strdup(++pointer_n);
		}
		buf[reading_bytes] = '\0';
		*line = ft_strjoin(*line, buf);
	}
	if (reading_bytes > 0 || (ft_strchr(truncated, '\n') != NULL))
		return (1);
	else
		return (0);
}

// int		main(void)
// {
// 	int		fd;
// 	char	*line;
// 	fd = open("/Users/ejolyn/projects/get_next_line/test.txt", O_RDONLY);
// 	while (get_next_line(fd, &line) == 0)
// 	 	printf("%s\n\n", line);
// 	return (0);
// }
