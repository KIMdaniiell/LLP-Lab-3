#include "bmp_io.h"
#include "image_file_io.h"
#include "transforms.h"

#include <stdio.h>


int main( int argc, char** argv ) {
    FILE* input_file;
    FILE* output_file;
    struct image image_prisine;
    struct image image_modified;
    if (argc!=3){
	puts("[ERROR] Argument number is not correct!");
	return 1;
    }
    

    if (!open_file(&input_file,argv[1],"rb")) {
	puts("[ERROR] Failed to open input file!");
	printf("\t Input file name was [%s]",argv[1]);
	printf("\t Output file name was [%s]",argv[2]);
	return 1;
    }
    puts("INPUT FILE OPPENED...");

    if (!from_bmp(input_file,&image_prisine)) {
	puts("[ERROR] Failed to deserializer formated image file!");
	return 1;
    }
    puts("INPUT DESERIALISED...");

    if (!close_file(&input_file)) {
	puts("[ERROR] Failed to close input file!");
	return 1;
    }
    puts("INPUT FILE CLOSED...");
    
    if (!rotate_image(&image_modified,image_prisine)) {
	puts("[ERROR] Failed to modify the image!");
	return 1;
    }
    puts("IMAGE ROTATED...");
    image_reset(&image_prisine);

    if (!open_file(&output_file,argv[2],"wb")) {
	puts("[ERROR] Failed to open output file!");
	return 1;
    }
    puts("OUTPUT FILE OPPENED...");
    if (!to_bmp(output_file,&image_modified)) {
	puts("[ERROR] Failed to serializer formated image file!");
	return 1;
    }
    puts("OUTPUT SERIALISED...");
    image_reset(&image_modified);
    if (!close_file(&output_file)) {
	puts("[ERROR] Failed to close output file!");
	return 1;
    }
    puts("OUTPUT FILE CLOSED...");
}

