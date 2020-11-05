/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 09:45:37 by keddib            #+#    #+#             */
/*   Updated: 2020/11/02 04:12:30 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
in this file I read the map info from any afile must be .cub
I have to initize these variebles :
 - all->win.width XDONEX
 - all->win.height XDONEX
 - all->win.cols XDONEX
 - all->win.rows XDONEX
 - all->win.array XDONEX
 - all->fpp.x     XDONEX
 - all->fpp.y     XDONEX
 - all->fpp.rotation.angle XDONEX
*/
#include "header.h"

static void check_char(char c, t_all *all)
{
    if (c != '1' && c != '0' && c != '2' && c != 'W' &&
        c != 'N' && c != 'S' && c != 'E' && c != ' ')
        ft_exit(2, all);
    if ((c == 'N' || c == 'W' || c == 'S' || c == 'E') && all->win.chr == 1)
        ft_exit(3, all);
    if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
        all->win.chr = 1;
}

static void check_array(int j, int i, t_all *all)
{
    if (all->win.array[j][i] == 'N' || all->win.array[j][i] == 'W' ||
        all->win.array[j][i] == 'E' || all->win.array[j][i] == 'S')
    {
        all->fpp.x = (i * TILE_SIZE) + (TILE_SIZE / 2);
        all->fpp.y = (j * TILE_SIZE) + (TILE_SIZE / 2);
        if (all->win.array[j][i] == 'S')
            all->fpp.rotation_angle = M_PI / 2;
        else if (all->win.array[j][i] == 'N')
            all->fpp.rotation_angle = M_PI * 1.5;
        else if (all->win.array[j][i] == 'E')
            all->fpp.rotation_angle = M_PI * 0;
        else if (all->win.array[j][i] == 'W')
            all->fpp.rotation_angle = M_PI * 1;
    }
    if (all->win.array[j][i] == '2')
        all->num_sprt += 1;
    if (j == 0 || (j == all->win.cols - 1))
        ft_exit(2, all);
    else if (i == (all->win.rows - 1))
        ft_exit(2, all);
    else if (all->win.array[j + 1][i] == ' ' || all->win.array[j - 1][i] == ' ')

        ft_exit(2, all);
    else if (all->win.array[j][i + 1] == ' ' || all->win.array[j][i - 1] == ' ')
        ft_exit(2, all);
}

static int check_error(t_all *all)
{
    int i;
    int j;

    j = 0;
    all->win.chr = 0;
    while (all->win.array[j])
    {
        i = 0;
        while (all->win.array[j][i])
        {
            if (all->win.array[j][i] == '0' || all->win.array[j][i] == 'N' ||
                all->win.array[j][i] == 'W' || all->win.array[j][i] == '2' ||
                all->win.array[j][i] == 'E' || all->win.array[j][i] == 'S')
                check_array(j, i, all);
            check_char(all->win.array[j][i], all);
            i++;
        }
        j++;
    }
    return (0);
}

char *ft_path(const char *s)
{
    char *cpy;
    int len;
    int i;

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

int check_line(char *line, t_all *all)
{
    char **splited_line;
    int cols;
    if (line[0] == '\n')
        return 0;
    splited_line = ft_split(line, ' ', &cols);
    if (ft_strcmp(splited_line[0], "R") == 0)
    {
        if (cols > 3 || cols < 3 || all->file.r == 1)
            ft_exit(2, all);
        all->win.width = ft_atoi(splited_line[1]);
        all->win.height = ft_atoi(splited_line[2]);
        all->file.counter += 1;
        all->file.r = 1;
    }
    else if ((cols > 2 || cols < 2) && !str_containe(splited_line, cols))
        ft_exit(2, all);
    else if (ft_strcmp(splited_line[0], "NO") == 0)
    {
        if (all->file.no == 1)
            ft_exit(2, all);
        all->tex.file[0] = ft_path(splited_line[1]);
        all->file.counter += 1;
        all->file.no = 1;
    }
    else if (ft_strcmp(splited_line[0], "SO") == 0)
    {
        if (all->file.so == 1)
            ft_exit(2, all);
        all->tex.file[1] = ft_path(splited_line[1]);
        all->file.counter += 1;
        all->file.no = 1;
    }
    else if (ft_strcmp(splited_line[0], "WE") == 0)
    {
        if (all->file.we == 1)
            ft_exit(2, all);
        all->tex.file[2] = ft_path(splited_line[1]);
        all->file.counter += 1;
        all->file.no = 1;
    }
    else if (ft_strcmp(splited_line[0], "EA") == 0)
    {
        if (all->file.ea == 1)
            ft_exit(2, all);
        all->tex.file[3] = ft_path(splited_line[1]);
        all->file.counter += 1;
        all->file.no = 1;
    }
    else if (ft_strcmp(splited_line[0], "S") == 0)
    {
        if (all->file.s == 1)
            ft_exit(2, all);
        all->tex.file[4] = ft_path(splited_line[1]);
        all->file.counter += 1;
        all->file.no = 1;
    }
    else if (ft_strcmp(splited_line[0], "F") == 0)
    {
        if (all->file.f == 1)
            ft_exit(2, all);
        all->tex.floor = change_rgb(splited_line[1], all);
        all->file.counter += 1;
        all->file.no = 1;
    }
    else if (ft_strcmp(splited_line[0], "C") == 0)
    {
        if (all->file.c == 1)
            ft_exit(2, all);
        all->tex.ciel = change_rgb(splited_line[1], all);
        all->file.counter += 1;
        all->file.no = 1;
    }
    else if (str_containe(splited_line, cols))
        all->file.map_found = 1;
    else
        ft_exit(2, all);
    ft_free(splited_line, cols);
    return 0;
}

void read_file(char *path, t_all *all)
{
    int fd;
    char *line;
    char *strmap;
    all->file.counter = 0;
    all->file.map_found = 0;
    all->file.c = 0;
    all->file.f = 0;
    all->file.ea = 0;
    all->file.no = 0;
    all->file.r = 0;
    all->file.s = 0;
    all->file.so = 0;
    all->file.we = 0;
    all->win.chr = 0;
    all->win.rows = 0;
    all->num_sprt = 0;
    strmap = NULL;
    fd = open(path, O_RDONLY);
    if (fd == -1)
        ft_exit(1, all);
    while (get_next_line(fd, &line))
    {
        if (all->file.map_found == 0)
            check_line(line, all);
        if (all->file.map_found == 1)
        {
            int len = 0;
            len = ft_strlen(line);
            if (line[0] == '\n' || all->file.counter != 8)
            {
                ft_exit(2, all);
                free(line);
            }
            else if (line[0] == '0' || line[len - 2] == '0')
            {
                ft_exit(2, all);
                free(line);
            }
            all->win.rows = (len > all->win.rows) ? len - 1 : all->win.rows;
            strmap = ft_strjoin(strmap, line, 0);
        }
        free(line);
    }
    if (all->file.map_found == 0)
        ft_exit(2, all);
    strmap = ft_strjoin(strmap, line, 0);
    free(line);
    all->win.array = ft_split(strmap, '\n', &all->win.cols);
    free(strmap);
    check_error(all);
    if (all->win.chr == 0)
        ft_exit(2, all);
}
