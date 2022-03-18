#include "../include/image.h"

struct image image_create(uint32_t width, uint32_t height ) {
    struct image img = {0};
    img.data = malloc ( height*width * sizeof(struct pixel) );
    if (img.data) {
	img.height = height;
        img.width = width;
    }
    return img;
}

void image_reset( struct image* img) {
    img->width = 0;
    img->height = 0;
    free(img->data);
}
