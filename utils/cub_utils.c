/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wolfey <wolfey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:50:26 by keddib            #+#    #+#             */
/*   Updated: 2020/03/31 05:44:32 by wolfey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

size_t		ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *sub;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if ((start + len) > ft_strlen(s))
		return (ft_strdup(s + start));
	else
	{
		sub = malloc(len + 1);
		if (!sub)
			return (NULL);
		ft_strlcpy(sub, s + start, len + 1);
	}
	return (sub);
}

char		*ft_strdup(const char *s1)
{
	char	*cpy;
	int		len;
	int		i;

	len = ft_strlen(s1);
	cpy = malloc(sizeof(char) * len + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char		*ft_strjoin(char const *s1, char const *s2, int z)
{
	char		*result;
	size_t		i;
	size_t		j;

	if (s1 == NULL)
		s1 = ft_strdup("");
	if (!(result = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1)))
		return (NULL);
	i = 0;
	if (i < (ft_strlen(s1) + ft_strlen(s2)))
	{
		while (s1[i])
		{
			result[i] = s1[i];
			i++;
		}
		j = 0;
		while (s2[j])
			result[i++] = s2[j++];
	}
	result[i] = '\0';
	free((char*)s1);
	if (z == 1)
		free((char*)s2);
	return ((char*)result);
}

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;

	i = 0;
	if (!dst || !src || !size)
		return (ft_strlen(src));
	while (i < (size - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}