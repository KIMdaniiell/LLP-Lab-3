#ifndef _BMP_IO_H_
#define _BMP_IO_H_

#include "image.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define HEADER_BF_TYPE 0x4D42
#define HEADER_OFF_BITS 54
#define HEADER_BI_SIZE 40
#define HEADER_BI_PLANES 1
#define HEADER_BI_BIT_COUNT 24
#define HEADER_BI_X_PPM 2834
#define HEADER_BI_Y_PPM 2834
#define HEADER_CLR_USED 0
#define HEADER_CLR_IMP 0
#define HEADER_BF_RESERVED 0
#define HEADER_BI_COMPRESSION 0

enum convertation_result {
	HEADER_READ_FAIL,
	HEADER_WRITE_FAIL,
	INVALID_HEADER_TYPE,
	INVALID_HEADER_SIZE_PARAMETERS,
	BITS_READ_FAIL,
	BITS_WRITE_FAIL,
	READ_INVALID_HEADER,
	IMAGE_OBJECT_CREATION_FAIL,
	CONVERTATION_SUCCESS		
};

struct __attribute__((packed)) bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};


enum convertation_result from_bmp( FILE* input_file, struct image* img );

enum convertation_result to_bmp( FILE* output_file, struct image const* img );

#endif
