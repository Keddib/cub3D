/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:50:47 by keddib            #+#    #+#             */
/*   Updated: 2020/10/24 23:35:35 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int bsave_ts(char **bsave, char **line)
{
	char *p;
	char *temp;

	temp = NULL;
	if (*bsave)
	{
		if ((p = ft_memchr(*bsave + 1, '\n', BUFFER_SIZE)))
		{
			*line = ft_substr(*bsave, 1, p - *bsave);
			temp = *bsave;
			*bsave = ft_strdup(p);
			free(temp);
			return (1);
		}
		*line = ft_substr(*bsave, 1, BUFFER_SIZE);
		temp = *bsave;
		if (temp)
			free(temp);
		*bsave = NULL;
	}
	return (0);
}

int get_next_line(int fd, char **line)
{
	int i;
	char *buff;
	static char *bsave;

	*line = NULL;
	if ((i = bsave_ts(&bsave, line)) == 1)
		return (1);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while ((i = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[i] = 0x00;
		if ((bsave = ft_memchr(buff, '\n', BUFFER_SIZE)))
		{
			*line = ft_strjoin(*line, ft_substr(buff, 0, (bsave + 1) - buff), 1);
			bsave = ft_substr(buff, bsave - buff, i);
			free(buff);
			return (1);
		}
		*line = ft_strjoin(*line, buff, 0);
	}
	if (*line == NULL)
		*line = ft_strdup("");
	free(buff);
	return (i > 0 ? 1 : i);
}