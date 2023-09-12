/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokklee <seokklee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:47:06 by seokklee          #+#    #+#             */
/*   Updated: 2023/09/12 18:20:28 by seokklee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_line(int fd, char **backup, char *buffer);
size_t	ft_find_nl_idx(char *backup_fd);
char	*ft_seperate(int fd, char **backup);
char	*ft_eof(int fd, char **backup);

char	*get_next_line(int fd)
{
	static char	*backup[OPEN_MAX];
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!backup[fd])
	{
		backup[fd] = ft_strdup("");
		if (!backup[fd])
			return (0);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(backup[fd]);
		backup[fd] = NULL;
		return (NULL);
	}
	line = ft_get_line(fd, backup, buffer);
	free(buffer);
	buffer = NULL;
	if (!backup[fd])
		free(backup[fd]);
	return (line);
}

char	*ft_get_line(int fd, char **backup, char *buffer)
{
	ssize_t	read_size;
	char	*line;

	read_size = 1;
	while (!ft_strchr(backup[fd], '\n') && read_size)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 0)
		{
			free(backup[fd]);
			backup[fd] = NULL;
			return (NULL);
		}
		buffer[read_size] = '\0';
		backup[fd] = ft_strjoin_gnl(backup[fd], buffer);
		if (!backup[fd])
			return (NULL);
	}
	if (ft_strchr(backup[fd], '\n'))
		line = ft_seperate(fd, backup);
	else
		line = ft_eof(fd, backup);
	return (line);
}

char	*ft_seperate(int fd, char **backup)
{
	size_t	idx;
	char	*tmp;
	char	*line;

	idx = ft_find_nl_idx(backup[fd]);
	line = ft_substr(backup[fd], 0, idx + 1);
	if (!line)
	{
		free(backup[fd]);
		backup[fd] = NULL;
		return (NULL);
	}
	tmp = backup[fd];
	backup[fd] = ft_strdup(&(backup[fd])[idx + 1]);
	free(tmp);
	if (!backup[fd])
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*ft_eof(int fd, char **backup)
{
	char	*line;

	line = ft_strdup(backup[fd]);
	free(backup[fd]);
	backup[fd] = NULL;
	if (!line || !*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

size_t	ft_find_nl_idx(char *backup_fd)
{
	size_t	idx;

	idx = 0;
	if (!backup_fd)
		return (0);
	while (backup_fd[idx] != '\n')
		idx++;
	return (idx);
}
