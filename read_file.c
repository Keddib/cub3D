/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 09:45:37 by keddib            #+#    #+#             */
/*   Updated: 2020/10/23 23:22:09 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
int this file I read the map info from any afile must be .cub
I have to initize these variebles :
 - window.width
 - window.height
 - window.num_cols
 - window.num_rows
 - window.array
 - player.x
 - player.y
 - player.rotation.angle
*/
#include "header.h"

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
    if (j == 0 || (j == window.num_cols - 1))
        ft_exit(2);
    else if (i == (window.num_rows - 1))
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

int check_line(char *line, int *map_found)
{
    int i = 0;
    char **splited_line;
    int cols;
    if (line[0] == '\n')
        return 0;
    splited_line = ft_split(line, ' ', &cols);
    if (strcmp(splited_line[0], "R") == 0)
    {
        if (cols > 3 || cols < 3)
            ft_exit(2);
        window.width = ft_atoi(splited_line[1]);
        window.height = ft_atoi(splited_line[2]);
    }
    else if (strcmp(splited_line[0], "NO") == 0)
    {
        if (cols > 2 || cols < 2)
            ft_exit(2);
    }
    else if (strcmp(splited_line[0], "SO") == 0)
    {
        if (cols > 2 || cols < 2)
            ft_exit(2);
    }
    else if (strcmp(splited_line[0], "WE") == 0)
    {
        if (cols > 2 || cols < 2)
            ft_exit(2);
    }
    else if (strcmp(splited_line[0], "EA") == 0)
    {
        if (cols > 2 || cols < 2)
            ft_exit(2);
    }
    else if (strcmp(splited_line[0], "S") == 0)
    {
        if (cols > 2 || cols < 2)
            ft_exit(2);
    }
    else if (strcmp(splited_line[0], "F") == 0)
    {
        if (cols > 2 || cols < 2)
            ft_exit(2);
    }
    else if (strcmp(splited_line[0], "C") == 0)
    {
        if (cols > 2 || cols < 2)
            ft_exit(2);
    }
    else if (str_containe(splited_line, cols))
        *map_found = 1;
    else
        ft_exit(2);
    ft_free(splited_line, cols);
    return 0;
}

void read_file(char *path)
{
    int fd;
    char *line;
    char *strmap;
    int map_found;

    map_found = 0;
    strmap = NULL;
    fd = open(path, O_RDONLY);
    window.chr = 0;
    if (fd == -1)
        ft_exit(1);
    window.num_rows = 0;
    while (get_next_line(fd, &line))
    {
        if (map_found == 0)
            check_line(line, &map_found);
        if (map_found == 1)
        {
            if (line[0] == '\n')
                ft_exit(2);
            else if (line[0] == '0')
                ft_exit(2);
            window.num_rows = (ft_strlen(line) > window.num_rows) ? ft_strlen(line) - 1 : window.num_rows;
            strmap = ft_strjoin(strmap, line, 0);
        }
        free(line);
    }
    strmap = ft_strjoin(strmap, line, 0);
    window.array = ft_split(strmap, '\n', &window.num_cols);
    free(line);
    free(strmap);
    check_error();
}
