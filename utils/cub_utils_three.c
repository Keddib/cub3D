/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 06:16:37 by keddib            #+#    #+#             */
/*   Updated: 2020/11/09 06:38:57 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*ft_path(const char *s)
{
	char	*cpy;
	int		len;
	int		i;

	len = ft_strlen(s);
	cpy = malloc(sizeof(char) * len + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (s[i] == '\n')
		{
			cpy[i] = '\0';
			return (cpy);
		}
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

int		ft_close(t_all *all)
{
	ft_exit(0, all);
	return (0);
}

void	check_suffix(char *s, char *cub, t_all *all)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	i -= 1;
	while (cub[j])
	{
		if (s[i] == cub[j])
			i--;
		else
			ft_exit(9, all);
		j++;
	}
}

void	check_arguments(t_all *all)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (all->param2)
	{
		if (ft_strcmp("--save", all->param2) == 0)
			all->save = 1;
		else
			ft_exit(1, all);
	}
	if (!all->param1 || strlen(all->param1) <= 4)
		ft_exit(1, all);
	check_suffix(all->param1, "buc.", all);
}

int		sprite_color(t_all *all, t_sprite sprite, int i, int j)
{
	int color;

	color = all->tex.data[4][(unsigned int)(all->tex.width *
				(all->tex.height * j / (int)(sprite.size)) +
					(all->tex.width * i / (int)sprite.size))];
	return (color);
}
