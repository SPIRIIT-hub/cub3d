#include "../headers/cub3d.h"

unsigned char	*create_bitmap_file_header(int file_size)
{
	static unsigned char	file_header[] = {
		0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};

	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(14 + 40);
	return (file_header);
}

unsigned char	*create_bitmap_info_header(t_rc *rc)
{
	static unsigned char	info_header[] = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0,
		0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
	};

	info_header[0] = (unsigned char)(40);
	info_header[4] = (unsigned char)(rc->pars->Rx >> 0);
	info_header[5] = (unsigned char)(rc->pars->Rx >> 8);
	info_header[6] = (unsigned char)(rc->pars->Rx >> 16);
	info_header[7] = (unsigned char)(rc->pars->Rx >> 24);
	info_header[8] = (unsigned char)(rc->pars->Ry >> 0);
	info_header[9] = (unsigned char)(rc->pars->Ry >> 8);
	info_header[10] = (unsigned char)(rc->pars->Ry >> 16);
	info_header[11] = (unsigned char)(rc->pars->Ry >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(rc->bits_per_pixel);
	return (info_header);
}

void	write_img(int fd, t_rc *rc)
{
	int		x;
	int		y;

	x = rc->pars->Ry;
	while (x-- > 0)
	{
		y = -1;
		while (++y < rc->pars->Rx)
			write(fd, rc->addr + (x * rc->line_length + y * (rc->bits_per_pixel / 8)) \
			, rc->bits_per_pixel / 8);
	}
}

void	save_bmp(const char *filename, t_rc *rc)
{
	int		fd;
	int		img_size;
	int		file_size;

	img_size = rc->pars->Rx * 4 * rc->pars->Ry;
	file_size = img_size + (40 + 14);
	close(open(filename, O_RDONLY | O_CREAT, S_IRWXU));
	fd = open(filename, O_RDWR);
	if (fd < 0)
	{
		printf("Error\n");
		wrdestroy();
		exit(0);
	}
	write(fd, create_bitmap_file_header(file_size), 14);
	write(fd, create_bitmap_info_header(rc), 40);
	write_img(fd, rc);
	close(fd);
	printf("Image generated!!\n");
	wrdestroy();
	exit(0);
}
