/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 09:45:37 by keddib            #+#    #+#             */
/*   Updated: 2020/10/25 23:31:48 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
in this file I read the map info from any afile must be .cub
I have to initize these variebles :
 - g_window.width XDONEX
 - g_window.height XDONEX
 - g_window.cols XDONEX
 - g_window.rows XDONEX
 - g_window.array XDONEX
 - g_player.x     XDONEX
 - g_player.y     XDONEX
 - g_player.rotation.angle XDONEX
*/
#include "header.h"

static void check_char(char c)
{
    if (c != '1' && c != '0' && c != '2' && c != 'W' &&
        c != 'N' && c != 'S' && c != 'E' && c != ' ')
        ft_exit(2);
    if ((c == 'N' || c == 'W' || c == 'S' || c == 'E') && g_window.chr == 1)
        ft_exit(3);
    if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
        g_window.chr = 1;
}

static void check_array(int j, int i)
{
    if (g_window.array[j][i] == 'N' || g_window.array[j][i] == 'W' ||
        g_window.array[j][i] == 'E' || g_window.array[j][i] == 'S')
    {
        g_player.x = (i * TILE_SIZE) + (TILE_SIZE / 2);
        g_player.y = (j * TILE_SIZE) + (TILE_SIZE / 2);
        if (g_window.array[j][i] == 'S')
            g_player.rotation_angle = M_PI / 2;
        else if (g_window.array[j][i] == 'N')
            g_player.rotation_angle = M_PI * 1.5;
        else if (g_window.array[j][i] == 'E')
            g_player.rotation_angle = M_PI * 0;
        else if (g_window.array[j][i] == 'W')
            g_player.rotation_angle = M_PI * 1;
    }
    if (j == 0 || (j == g_window.cols - 1))
        ft_exit(2);
    else if (i == (g_window.rows - 1))
        ft_exit(2);
    else if (g_window.array[j + 1][i] == ' ' || g_window.array[j - 1][i] == ' ')

        ft_exit(2);
    else if (g_window.array[j][i + 1] == ' ' || g_window.array[j][i - 1] == ' ')
        ft_exit(2);
}

static int check_error()
{
    int i;
    int j;

    j = 0;
    g_window.chr = 0;
    while (g_window.array[j])
    {
        i = 0;
        while (g_window.array[j][i])
        {
            if (g_window.array[j][i] == '0' || g_window.array[j][i] == 'N' ||
                g_window.array[j][i] == 'W' || g_window.array[j][i] == '2' ||
                g_window.array[j][i] == 'E' || g_window.array[j][i] == 'S')
                check_array(j, i);
            check_char(g_window.array[j][i]);
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

int check_line(char *line, t_file *elems, t_texture *tex)
{
    char **splited_line;
    int cols;
    if (line[0] == '\n')
        return 0;
    splited_line = ft_split(line, ' ', &cols);
    if (strcmp(splited_line[0], "R") == 0)
    {
        if (cols > 3 || cols < 3 || elems->r == 1)
            ft_exit(2);
        g_window.width = ft_atoi(splited_line[1]);
        g_window.height = ft_atoi(splited_line[2]);
        elems->counter += 1;
        elems->r = 1;
    }
    else if ((cols > 2 || cols < 2) && !str_containe(splited_line, cols))
        ft_exit(2);
    else if (strcmp(splited_line[0], "NO") == 0)
    {
        if (elems->no == 1)
            ft_exit(2);
        tex->file[0] = ft_path(splited_line[1]);
        elems->counter += 1;
        elems->no = 1;
    }
    else if (strcmp(splited_line[0], "SO") == 0)
    {
        if (elems->so == 1)
            ft_exit(2);
        tex->file[1] = ft_path(splited_line[1]);
        elems->counter += 1;
        elems->no = 1;
    }
    else if (strcmp(splited_line[0], "WE") == 0)
    {
        if (elems->we == 1)
            ft_exit(2);
        tex->file[2] = ft_path(splited_line[1]);
        elems->counter += 1;
        elems->no = 1;
    }
    else if (strcmp(splited_line[0], "EA") == 0)
    {
        if (elems->ea == 1)
            ft_exit(2);
        tex->file[3] = ft_path(splited_line[1]);
        elems->counter += 1;
        elems->no = 1;
    }
    else if (strcmp(splited_line[0], "S") == 0)
    {
        if (elems->s == 1)
            ft_exit(2);
        elems->counter += 1;
        elems->no = 1;
    }
    else if (strcmp(splited_line[0], "F") == 0)
    {
        if (elems->f == 1)
            ft_exit(2);
        tex->floor = change_rgb(splited_line[1]);
        elems->counter += 1;
        elems->no = 1;
    }
    else if (strcmp(splited_line[0], "C") == 0)
    {
        if (elems->c == 1)
            ft_exit(2);
        tex->ciel = change_rgb(splited_line[1]);
        elems->counter += 1;
        elems->no = 1;
    }
    else if (str_containe(splited_line, cols))
        elems->map_found = 1;
    else
        ft_exit(2);
    ft_free(splited_line, cols);
    return 0;
}

void read_file(char *path, t_texture *tex)
{
    int fd;
    char *line;
    char *strmap;
    t_file elems;

    elems.counter = 0;
    elems.map_found = 0;
    elems.c = 0;
    elems.f = 0;
    elems.ea = 0;
    elems.no = 0;
    elems.r = 0;
    elems.s = 0;
    elems.so = 0;
    elems.we = 0;
    strmap = NULL;
    fd = open(path, O_RDONLY);
    g_window.chr = 0;
    if (fd == -1)
        ft_exit(1);
    g_window.rows = 0;
    while (get_next_line(fd, &line))
    {
        if (elems.map_found == 0)
            check_line(line, &elems, tex);
        if (elems.map_found == 1)
        {
            int len = 0;
            len = ft_strlen(line);
            if (line[0] == '\n' || elems.counter != 8)
            {
                ft_exit(2);
                free(line);
            }
            else if (line[0] == '0' || line[len - 2] == '0')
            {
                ft_exit(2);
                free(line);
            }
            g_window.rows = (len > g_window.rows) ? len - 1 : g_window.rows;
            strmap = ft_strjoin(strmap, line, 0);
        }
        free(line);
    }
    if (elems.map_found == 0)
        ft_exit(2);
    strmap = ft_strjoin(strmap, line, 0);
    free(line);
    g_window.array = ft_split(strmap, '\n', &g_window.cols);
    free(strmap);
    check_error();
    if (g_window.chr == 0)
        ft_exit(2);
}
