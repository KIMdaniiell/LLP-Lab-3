#include "../include/bmp_io.h"

static bool header_is_type_valid (struct bmp_header const* header);
static bool header_is_size_valid (struct bmp_header const* header);
static struct bmp_header header_construst(uint32_t height, uint32_t width);

enum convertation_result from_bmp( FILE* input_file, struct image* img ) {
    struct bmp_header header = {0};
    if (!fread(&header, sizeof(struct bmp_header), 1, input_file)) {
	return HEADER_READ_FAIL;
    }
    if (!header_is_type_valid(&header) ) {
	return INVALID_HEADER_TYPE;
    }
    if (!header_is_size_valid(&header) ) {
	return INVALID_HEADER_SIZE_PARAMETERS;
    }
    *img = image_create(header.biWidth, header.biHeight);
    if ((img->width == 0) || (img->height == 0))  {
	return IMAGE_OBJECT_CREATION_FAIL;
    }
    size_t bmp_padding = (4 - (sizeof(struct pixel)*header.biWidth) % 4) % 4 ;
    fseek(input_file, header.bOffBits, SEEK_SET);
    
    for (size_t height_cnt = 0; height_cnt < img->height; height_cnt++) {
	if (fread(&img->data[height_cnt*(img->width)], sizeof(struct pixel), img->width, input_file) != img->width) {
		image_reset(img);
		return BITS_READ_FAIL;
	}
	fseek(input_file, bmp_padding, SEEK_CUR);
    }
    return CONVERTATION_SUCCESS;
}

enum convertation_result to_bmp( FILE* output_file, struct image const* img ) {
    struct bmp_header header = {0};
    header = header_construst(img->height, img->width);
    if (!fwrite(&header, sizeof(struct bmp_header), 1, output_file)) {
	return HEADER_WRITE_FAIL;
    }
    size_t bmp_padding = (4 - (sizeof(struct pixel)*header.biWidth) % 4) % 4 ;
    fseek(output_file, header.bOffBits, SEEK_SET);
    for (size_t height_cnt = 0; height_cnt < img->height; height_cnt++) {
	if (!fwrite(&img->data[height_cnt*(img->width)], sizeof(struct pixel), img->width, output_file)) {
	    return BITS_WRITE_FAIL;
	}
	fseek(output_file, bmp_padding, SEEK_CUR);
    }
    return CONVERTATION_SUCCESS;
}

static bool header_is_type_valid (struct bmp_header const* header) {
    return header->bfType == HEADER_BF_TYPE;
}

static bool header_is_size_valid (struct bmp_header const* header) {
    return (header->biWidth > 0) && (header->biHeight > 0);
}

static struct bmp_header header_construst(uint32_t height, uint32_t width) {
    return (struct bmp_header) {
	.bfType = HEADER_BF_TYPE,
	.bfileSize = sizeof (struct bmp_header) + (height + width)*sizeof(struct pixel) + height*((4 - (sizeof(struct pixel)*width) % 4) % 4),
	.bOffBits = HEADER_OFF_BITS,
	.biSize = HEADER_BI_SIZE,
	.bfReserved = HEADER_BF_RESERVED,
	.biWidth = width,
	.biHeight = height,
	.biPlanes = HEADER_BI_PLANES,
	.biBitCount = HEADER_BI_BIT_COUNT,
	.biCompression = HEADER_BI_COMPRESSION,
	.biSizeImage = (sizeof (struct bmp_header)
			 + (height + width)*sizeof(struct pixel)
			 + height*((4 - (sizeof(struct pixel)*width) % 4) % 4))
			 - HEADER_OFF_BITS,
	.biXPelsPerMeter = HEADER_BI_X_PPM,
	.biYPelsPerMeter = HEADER_BI_Y_PPM,
	.biClrUsed = HEADER_CLR_USED,
	.biClrImportant = HEADER_CLR_IMP
     };
}



