/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkim <nkim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:42:11 by nkim              #+#    #+#             */
/*   Updated: 2021/07/06 20:23:38 by nkim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #include <stdio.h>
// #include <fcntl.h>

void	*ft_memset(void *dst, int value, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*((char *)dst + i) = value;
		i++;
	}
	return (dst);
}

void	manage_line(char **line, char **file_rest)
{
	char *next_sp;
	char *tmp;

	next_sp = ft_strchr(*line, '\n');
	tmp = ft_strndup(*line, next_sp - *line);	
	if (*file_rest)
	{
		free(*file_rest);
		*file_rest = NULL;
	}
	*file_rest = ft_strndup(next_sp + 1, ft_strlen(next_sp + 1));
	free(*line);
	*line = NULL;
	*line = tmp;
}

void set_buffer_line(char *buffer, char **file_rest, char **line)
{
	ft_memset(buffer, 0, BUFFER_SIZE + 1);
	if (*file_rest)
	{
		ft_memccpy(buffer, *file_rest, 0, ft_strlen(*file_rest));
		free(*file_rest);
		*file_rest = NULL;
	}
	*line = ft_strndup(buffer, ft_strlen(buffer));
}

int		get_next_line(int fd, char **line)
{
	static char	*file_rest[256];
	char		buffer[BUFFER_SIZE + 1];
	char *tmp;
	int	r_bytes;

	// exception 처리
	if (fd < 0 || fd >= 256 || BUFFER_SIZE <= 0 || !line)
		return -1;

	// ft_memset(buffer, 0, BUFFER_SIZE + 1);
	// *line = NULL;
	// if (file_rest[fd])
	// {
	// 	ft_memccpy(buffer, file_rest[fd], 0, ft_strlen(file_rest[fd]));
	// 	free_ptr(&file_rest[fd]);
	// }
	// if (!*line)
	// 	*line = ft_strndup(buffer, ft_strlen(buffer));
	set_buffer_line(&buffer[0], &file_rest[fd], line);

	// buffer 에 line feed 가 있는지 계속 확인하면서 while 문을 돈다
	while (!(ft_strchr(buffer, '\n')))
	{		
		ft_memset(buffer, 0, BUFFER_SIZE);
		r_bytes = read(fd, buffer, BUFFER_SIZE);
		if (r_bytes == -1)
			return -1;
		else if (r_bytes == 0)
			return 0;
		tmp = *line;
		*line = ft_strjoin(*line, buffer);
		free(tmp);
	}
	manage_line(line, &(file_rest[fd]));
	return 1;
}

// int main(void)
// {
//     int fd = open("fuck.txt", O_RDONLY);
//     char *tmp;
//     int res;

//     while ((res = get_next_line(fd, &tmp)) > 0)
//     {
//         printf("%2d-%s\n", res, tmp);
//     }
//     printf("%2d-%s\n", res, tmp);
//     // printf("res : %d\n", res);
// }