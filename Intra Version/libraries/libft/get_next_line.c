/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:52:31 by uviana-a          #+#    #+#             */
/*   Updated: 2023/06/13 23:08:19 by uviana-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_get_remainder(char *line_to_clean)
{
	char	*remainder;
	int		i;
	int		j;

	i = 0;
	while (line_to_clean[i] && line_to_clean[i] != '\n')
		i++;
	if (!line_to_clean[i])
	{
		free(line_to_clean);
		return (NULL);
	}
	remainder = malloc(sizeof(char) * (ft_strlen_gnl(line_to_clean) - i + 1));
	if (!remainder)
		return (NULL);
	i++;
	j = 0;
	while (line_to_clean[i])
		remainder[j++] = line_to_clean[i++];
	remainder[j] = '\0';
	free (line_to_clean);
	return (remainder);
}

static	char	*ft_clean_line(char *line_to_clean)
{
	char	*line_cleaned;
	int		i;

	i = 0;
	if (!line_to_clean[i])
		return (NULL);
	while (line_to_clean[i] != '\0' && line_to_clean[i] != '\n')
		i++;
	line_cleaned = malloc(sizeof(char) * i + 2);
	if (!line_cleaned)
		return (NULL);
	i = 0;
	while (line_to_clean[i] && line_to_clean[i] != '\n')
	{
		line_cleaned[i] = line_to_clean[i];
		i++;
	}
	if (line_to_clean[i] == '\n')
	{
		line_cleaned[i] = line_to_clean[i];
		i++;
	}
	line_cleaned[i] = '\0';
	return (line_cleaned);
}

static char	*ft_get_content(int fd, char *line_to_clean)
{
	char	*buffer_content;
	int		bytes_read;

	buffer_content = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer_content)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr_mod(line_to_clean, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer_content, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (buffer_content);
			free (line_to_clean);
			return (NULL);
		}
		buffer_content[bytes_read] = '\0';
		line_to_clean = ft_strjoin_mod(line_to_clean, buffer_content);
	}
	free (buffer_content);
	return (line_to_clean);
}

char	*get_next_line(int fd)
{
	static char	*line_to_clean;
	char		*line_cleaned;

	if (BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	line_to_clean = ft_get_content(fd, line_to_clean);
	if (!line_to_clean)
		return (NULL);
	line_cleaned = ft_clean_line(line_to_clean);
	line_to_clean = ft_get_remainder(line_to_clean);
	return (line_cleaned);
}
