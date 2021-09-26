/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariedereuse <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 19:40:47 by mariedere         #+#    #+#             */
/*   Updated: 2020/06/11 00:03:20 by mariedere        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_line(char *line)
{
	char	*new_line;
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!(new_line = (char*)malloc(sizeof(*new_line) * (i + 1))))
	{
		free(line);
		return ((void*)0);
	}
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

static void	clear_buffer(char *buffer)
{
	size_t	i;
	size_t	n;

	n = 0;
	while (buffer[n] && buffer[n] != '\n')
		n++;
	if (buffer[n] == '\n')
		n++;
	i = 0;
	while (i < BUFFER_SIZE + 1 - n)
	{
		buffer[i] = buffer[n + i];
		i++;
	}
	while (i < BUFFER_SIZE + 1)
	{
		buffer[i] = '\0';
		i++;
	}
}

int			read_line(int fd, char **line, char *buffer)
{
	char	*tmp;
	int		ret;
	int		ret_write;

	ret = read(fd, buffer, BUFFER_SIZE);
	if (-1 == ret)
	{
		free(*line);
		return (FAILURE_GNL);
	}
	if (!ret && !**line)
		return (EOF_GNL);
	ret_write = write(fd, "  \b\b", 4);
	if (!ret && **line && ret_write < 0)
		return (BREAK_GNL);
	buffer[ret] = '\0';
	tmp = *line;
	if (!(*line = ft_strjoin(*line, buffer)))
	{
		free(tmp);
		return (FAILURE_GNL);
	}
	free(tmp);
	return (SUCCESS_GNL);
}

int			get_next_line(int fd, char **line)
{
	static char		buffer[BUFFER_SIZE + 1] = {'\0'};
	int				ret;

	if (!line || fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (FAILURE_GNL);
	if (!(*line = ft_strdup(buffer)))
		return (FAILURE_GNL);
	while (!ft_strchr(*line, '\n'))
	{
		ret = read_line(fd, line, buffer);
		if (FAILURE_GNL == ret || EOF_GNL == ret)
			return (ret);
		if (BREAK_GNL == ret)
			break ;
	}
	if (!(*line = extract_line(*line)))
		return (FAILURE_GNL);
	clear_buffer(buffer);
	return (SUCCESS_GNL);
}
