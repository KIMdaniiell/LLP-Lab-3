#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <stdint.h>
#include <stdlib.h>

struct image {
    uint64_t width, height;
    struct pixel* data;
};

struct pixel {
    uint8_t b, g, r;
};


struct image image_create(uint32_t width, uint32_t height );

void image_reset( struct image* img);

#endif
