#include "bmp_import.h"

static void				free_bmp(t_bmp_file *bmp)
{
	free(bmp->img);
	fclose(bmp->file);
}

static float			*read_colors(t_bmp_file *bmp)
{
	float				*out_img;

	bmp->img = (unsigned char*)malloc(bmp->info.image_size);
	out_img = (float *)malloc(sizeof(float) * bmp->info.image_size);
	if (!(bmp->img) || !out_img)
	{
		free(out_img);
		free_bmp(bmp);
		return (NULL);
	}
	fread(bmp->img, sizeof(unsigned char), bmp->info.image_size, bmp->file);
	if (!(bmp->img))
	{
		free_bmp(bmp);
		return (NULL);
	}
	return (out_img);
}

float					*import_bmp_file(char *filename, int *w, int *h)
{
	t_bmp_file			bmp;
	float				*out_img;
	unsigned int		i;

	if (!(bmp.file = fopen(filename, "rb")))
		return (NULL);
	fread(&(bmp.header), sizeof(unsigned char), sizeof(t_bmp_header), bmp.file);
	fread(&(bmp.info), sizeof(unsigned char), sizeof(t_bmp_info), bmp.file);
	fseek(bmp.file, bmp.header.offset, SEEK_SET);
	*h = bmp.info.height;
	*w = bmp.info.width;
	if (!(out_img = read_colors(&bmp)))
		return (NULL);
	i = 0;
	while (i < bmp.info.image_size)
	{
		out_img[i] = bmp.img[i + 2] / 255.0;
		out_img[i + 1] = bmp.img[i + 1] / 255.0;
		out_img[i + 2] = bmp.img[i] / 255.0;
		i += 3;
	}
	free_bmp(&bmp);
	return (out_img);
}
