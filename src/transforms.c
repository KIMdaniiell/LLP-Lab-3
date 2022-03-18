#include "../include/transforms.h"

bool rotate_image( struct image* image_rotated, struct image const image_prisine) {
    size_t height_cnt;
    size_t width_cnt;
    *image_rotated = image_create(image_prisine.height, image_prisine.width);
    for (height_cnt = 0; height_cnt < image_prisine.height; height_cnt++) {
	for (width_cnt = 0; width_cnt < image_prisine.width; width_cnt++) {
		image_rotated->data[  width_cnt*image_prisine.height + (image_prisine.height -1 - height_cnt)  ] = 
			image_prisine.data[height_cnt*image_prisine.width + width_cnt];
        }
    }
    return true;	
}
