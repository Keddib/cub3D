/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 09:45:37 by keddib            #+#    #+#             */
/*   Updated: 2020/10/21 19:44:45 by keddib           ###   ########.fr       */
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

// int check_line(char *line)
// {
//     int i = 0;
//     while (line[i])
//     {
//         if (line[i] == ' ')
//             i++;
//         if (line[i] == 'R' && line[i + 1] == ' ')
//             window.width = ft_atoi(line + i);
//     }
// }

void read_file(char *path)
{
    int fd;
    char *line;
    char *strmap;

    strmap = NULL;
    fd = open(path, O_RDONLY);
    window.chr = 0;
    if (fd == -1)
        ft_exit(1);
    window.num_rows = 0;
    while (get_next_line(fd, &line))
    {
        // check_line(line);
        if (line[0] == 'R')
        {
            window.width = ft_atoi(line + 1);
            window.height = ft_atoi(line + ft_len(line, ' '));
        }
        else if (line[0] == '1' || line[0] == ' ')
        {
            if (line[0] == '\n')
                ft_exit(2);
            window.num_rows = (ft_strlen(line) > window.num_rows) ? ft_strlen(line) - 1 : window.num_rows;
            strmap = ft_strjoin(strmap, line, 0);
        }
        else if (line[0] == '0')
            ft_exit(2);
        free(line);
    }
    strmap = ft_strjoin(strmap, line, 0);
    window.array = ft_split(strmap, '\n');
    for (int i = 0; i < window.num_cols; i++)
        printf("%s\n", window.array[i]);
    free(line);
    free(strmap);
    check_error();
}
