#include "bmp_import.h"
#include <stdio.h>

void					print_header(t_bmp_header *h, t_bmp_info *i)
{
	printf("magic:\t%d\nsize:\t%d\nreserved1:\t%d\nreserved2:\t%d\noffset:\t%d\n\n", h->magic, h->size, h->reserved1, h->reserved2, h->offset);
	printf("size:\t%d\nwidth:\t%d\nheight:\t%d\nplanes:\t%d\nbits:\t%d\ncompression:\t%d\nimage_size:\t%d\nxresolution:\t%d\nyresolution:\t%d\nncolours:\t%d\nimportant_colours:\t%d\n", i->size, i->width, i->height, i->planes, i->bits, i->compression, i->image_size, i->xresolution, i->yresolution, i->ncolours, i->important_colours);
}

void					print_bmp(unsigned char *bmp, int size)
{
	int					i =0;

	while (i < size)
	{
		printf("%d\t%d\t%d\n", bmp[i], bmp[i+1], bmp[i+2]);
		i += 3;
	}
}

float			*import_bmp_file(char *filename, int*w, int*h)
{
	FILE				*file;
	t_bmp_header		header;
	t_bmp_info			info;
	unsigned char		*bitmapImage;
	float				*outImage;
	unsigned int		i;

	printf("size of header: %lu\n", sizeof(t_bmp_header));
	printf("size of info  : %lu\n", sizeof(t_bmp_info));

	if (!(file = fopen(filename, "rb")))
		return (NULL);
	fread(&header, sizeof(unsigned char), sizeof(t_bmp_header), file);
	fread(&info, sizeof(unsigned char), sizeof(t_bmp_info), file);

	*h = info.height;
	*w = info.width;
	fseek(file, header.offset, SEEK_SET);

	bitmapImage = (unsigned char*)malloc(info.image_size);
	outImage = (float *)malloc(sizeof(float) * info.image_size);
	if (!bitmapImage || !outImage)
	{
		free(bitmapImage);
		free(outImage);
		fclose(file);
		return (NULL);
	}

	fread(bitmapImage, sizeof(unsigned char), info.image_size, file);
	if (!bitmapImage)
	{
		fclose(file);
		return (NULL);
	}

	i = 0;
	while (i < info.image_size)
	{
		outImage[i] = bitmapImage[i + 2] / 255.0;
		outImage[i + 1] = bitmapImage[i + 1] / 255.0;
		outImage[i + 2] = bitmapImage[i] / 255.0;

		//tempRGB = bitmapImage[i];
		//bitmapImage[i] = bitmapImage[i + 2];
		//bitmapImage[i + 2] = tempRGB;
		i += 3;
	}

	fclose(file);
	print_header(&header, &info);
//	print_bmp(bitmapImage, info.image_size);
	return (outImage);
}
