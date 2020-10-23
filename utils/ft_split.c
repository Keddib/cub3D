/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 18:47:58 by keddib            #+#    #+#             */
/*   Updated: 2020/10/23 19:16:22 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int count_words(const char *s, char c, int *cols)
{
	int i;
	int inw;
	int ls;

	i = 0;
	inw = 0;
	ls = 0;
	while ((size_t)i <= ft_strlen(s))
	{
		if (s[i] == c || s[i] == '\0')
		{
			if (inw == 0)
			{
				i++;
				continue;
			}
			ls++;
			inw = 0;
		}
		else
			inw = 1;
		i++;
	}
	*cols = ls;
	return (ls);
}

static int count_char(const char *s, char c)
{
	int len;

	len = 0;
	while (s[len] != c && s[len])
	{
		len++;
	}
	return (len);
}

void *ft_free(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

char **ft_split(char const *s, char c, int *cols)
{
	char **arr;
	int p;
	int i;
	int j;

	if (!s)
		return (NULL);
	p = count_words(s, c, cols);
	arr = malloc((p + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < p)
	{
		while (s[i] == c)
			i++;
		arr[j] = ft_substr(s, i, count_char(s + i, c));
		if (!arr[j])
			return (ft_free(arr, (j - 1)));
		j++;
		i = i + count_char(s + i, c);
	}
	arr[j] = NULL;
	return (arr);
}
