/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:16:36 by pibouill          #+#    #+#             */
/*   Updated: 2024/01/29 13:16:41 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*clean_stash(char *stash)
{
	char	*cleaned_stash;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] && stash[i] == '\n')
		i++;
	if (stash[i] == 0)
	{
		free(stash);
		return (NULL);
	}
	cleaned_stash = malloc(sizeof(char) * (ft_strlen(stash) - i) + 1);
	if (cleaned_stash == NULL)
		return (NULL);
	j = 0;
	while (stash[i])
		cleaned_stash[j++] = stash[i++];
	cleaned_stash[j] = '\0';
	free(stash);
	return (cleaned_stash);
}

char	*read_to_stash(char *stash, int fd)
{
	ssize_t	readed;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	readed = 1;
	while (readed != 0 && !ft_strchr(stash, '\n'))
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[readed] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*stash_to_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (stash[i] == 0)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * i + 2);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[FD_LIMIT];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FD_LIMIT)
		return (NULL);
	stash[fd] = read_to_stash(stash[fd], fd);
	if (stash[fd] == NULL)
		return (NULL);
	line = stash_to_line(stash[fd]);
	stash[fd] = clean_stash(stash[fd]);
	return (line);
}

// Nasty but works (kinda)
//
//int	main(int ac, char **av)
//{
//	int		fd[3];
//    char	*line[3];
//	(void)ac;
//    fd[0] = open(av[1], O_RDWR);
//	fd[1] = open(av[2], O_RDWR);
//	fd[2] = open(av[3], O_RDWR);
//    while (line[0] != NULL && line[1] != NULL && line[2] != NULL)
//    {
//        line[0] = get_next_line(fd[0]);
//        line[1] = get_next_line(fd[1]);
//        line[2] = get_next_line(fd[2]);
//
//		printf("first call:%s\n", line[0]);
//		printf("first call:%s\n", line[1]);
//		printf("first call:%s\n", line[2]);
//        line[0] = get_next_line(fd[0]);
//        line[1] = get_next_line(fd[1]);
//        line[2] = get_next_line(fd[2]);
//		printf("second call:%s\n", line[0]);
//		printf("second call:%s\n", line[1]);
//		printf("second call:%s\n", line[2]);
//        free(line[0]);
//        free(line[1]);
//        free(line[2]);
//    }
//    return (0);
//}
