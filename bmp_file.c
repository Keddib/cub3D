#include "header.h"

void int_to_rgb(t_all *all, unsigned int color)
{
	all->rgb.r = color / 65536;
	color -= all->rgb.r * 65536;
	all->rgb.g = color / 256;
	all->rgb.b = color % 256;
}

void save_bmp(t_all *all)
{
	int fd = open("img.bmp", O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	if (fd == -1)
		return;
	write(fd, g_bmp.header, 54);
	write(fd, g_bmp.buffer, g_bmp.image_size);
	close(fd);
	free(g_bmp.buffer);
	ft_exit(0, all);
}

int create_bmp(t_all *all)
{
    unsigned int width = all->win.width;
    unsigned int height = all->win.height;
    g_bmp.bits_ppixel = 24;
    g_bmp.row_bytes = (unsigned int)(((g_bmp.bits_ppixel * (unsigned int)all->win.width + 31) / 32) * 4);
    g_bmp.image_size = g_bmp.row_bytes * all->win.height;
    g_bmp.pixel_data_offset = 54;
    g_bmp.header_size = 40;
    g_bmp.file_size = 54 + g_bmp.image_size;
    g_bmp.planes = 1;
    bzero(g_bmp.header, 54);
    memcpy(g_bmp.header, &"BM", 2);
    memcpy(g_bmp.header + 2, &g_bmp.file_size, 4);
    memcpy(g_bmp.header + 10, &g_bmp.pixel_data_offset, 4);
    memcpy(g_bmp.header + 14, &g_bmp.header_size, 4);
    memcpy(g_bmp.header + 18, &width, 4);
    memcpy(g_bmp.header + 22, &height, 4);
    memcpy(g_bmp.header + 26, &g_bmp.planes, 2);
    memcpy(g_bmp.header + 28, &g_bmp.bits_ppixel, 2);
    memcpy(g_bmp.header + 34, &g_bmp.image_size, 4);
    g_bmp.buffer = malloc(g_bmp.image_size);
    return (0);
}