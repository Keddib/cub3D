/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 09:45:37 by keddib            #+#    #+#             */
/*   Updated: 2020/10/24 23:41:35 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
int this file I read the map info from any afile must be .cub
I have to initize these variebles :
 - window.width XDONEX
 - window.height XDONEX
 - window.cols XDONEX
 - window.rows XDONEX
 - window.array XDONEX
 - player.x
 - player.y
 - player.rotation.angle
*/
#include "header.h"

int change_rgb(char *s)
{
    char **lines;
    int cols;
    int color;
    lines = ft_split(s, ',', &cols);
    if (cols != 3)
    {
        ft_free(lines, cols);
        ft_exit(2);
    }
    color = 65536 * ft_atoi(lines[0]) + 256 * ft_atoi(lines[1]);
    color += ft_atoi(lines[2]);
    ft_free(lines, cols);
    return (color);
}

int str_containe(char **s, int n)
{
    int i;
    int j;
    int yes;

    i = 0;
    while (i < n)
    {
        j = 0;
        while (s[i][j])
        {
            if (s[i][j] == '1' || s[i][j] == ' ' || s[i][j] == '\n')
                yes = 1;
            else
                return (0);
            j++;
        }
        i++;
    }
    return (yes);
}

int ft_strcmp(const char *s1, const char *s2)
{
    size_t i;
    unsigned char *s;
    unsigned char *z;

    s = (unsigned char *)s1;
    z = (unsigned char *)s2;
    if (!s1 && !s2)
        return (0);
    i = 0;
    while (s[i] != '\0' || z[i] != '\0')
    {
        if (s[i] - z[i] != 0)
            return (s[i] - z[i]);
        i++;
    }
    return (*s1 - *s2);
}

static void check_char(char c)
{
    if (c != '1' && c != '0' && c != '2' && c != 'W' &&
        c != 'N' && c != 'S' && c != 'E' && c != ' ')
        ft_exit(2);
    if ((c == 'N' || c == 'W' || c == 'S' || c == 'E') && window.chr == 1)
        ft_exit(3);
    if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
        window.chr = 1;
}

static void check_array(int j, int i)
{
    if (window.array[j][i] == 'N' || window.array[j][i] == 'W' ||
        window.array[j][i] == 'E' || window.array[j][i] == 'S')
    {
        player.x = i * TILE_SIZE;
        player.y = j * TILE_SIZE;
        if (window.array[j][i] == 'S')
            player.rotation_angle = M_PI / 2;
        else if (window.array[j][i] == 'N')
            player.rotation_angle = M_PI * 1.5;
    }
    if (j == 0 || (j == window.cols - 1))
        ft_exit(2);
    else if (i == (window.rows - 1))
        ft_exit(2);
    else if (window.array[j + 1][i] == ' ' || window.array[j - 1][i] == ' ')

        ft_exit(2);
    else if (window.array[j][i + 1] == ' ' || window.array[j][i - 1] == ' ')
        ft_exit(2);
}

static int check_error()
{
    int i;
    int j;

    j = 0;
    while (window.array[j])
    {
        i = 0;
        while (window.array[j][i])
        {
            if (window.array[j][i] == '0' || window.array[j][i] == 'N' ||
                window.array[j][i] == 'W' || window.array[j][i] == '2' ||
                window.array[j][i] == 'E' || window.array[j][i] == 'S')
                check_array(j, i);
            check_char(window.array[j][i]);
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
        window.width = ft_atoi(splited_line[1]);
        window.height = ft_atoi(splited_line[2]);
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
    window.chr = 0;
    if (fd == -1)
        ft_exit(1);
    window.rows = 0;
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
            window.rows = (len > window.rows) ? len - 1 : window.rows;
            strmap = ft_strjoin(strmap, line, 0);
        }
        free(line);
    }
    if (elems.map_found == 0)
        ft_exit(2);
    strmap = ft_strjoin(strmap, line, 0);
    free(line);
    window.array = ft_split(strmap, '\n', &window.cols);
    free(strmap);
    check_error();
}
