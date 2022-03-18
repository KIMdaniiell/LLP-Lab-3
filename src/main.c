#include "bmp_io.h"
#include "file_io.h"
#include "transforms.h"

#include <stdio.h>

static const char* error_messages[] = {
	[HEADER_READ_FAIL] = "HEADER_READ_FAIL",
	[HEADER_WRITE_FAIL] = "HEADER_WRITE_FAIL",
	[INVALID_HEADER_TYPE] = "INVALID_HEADER_TYPE",
	[INVALID_HEADER_SIZE_PARAMETERS] = "INVALID_HEADER_SIZE_PARAMETERS",
	[BITS_READ_FAIL] = "BITS_READ_FAIL",
	[BITS_WRITE_FAIL] = "BITS_WRITE_FAIL",
	[READ_INVALID_HEADER] = "READ_INVALID_HEADER",
	[IMAGE_OBJECT_CREATION_FAIL] = "IMAGE_OBJECT_CREATION_FAIL",
	[CONVERTATION_SUCCESS] = "CONVERTATION_SUCCESS"
};

static void print_error (enum convertation_result result);

int main( int argc, char** argv ) {
    FILE* input_file;
    FILE* output_file;
    struct image image_prisine;
    struct image image_modified;
    
    enum convertation_result result;

    if (argc!=3){
	puts("[ERROR] Argument number is not correct!");
	return 1;
    }
    

    if (!open_file(&input_file,argv[1],"rb")) {
	puts("[ERROR] Failed to open input file!");
	return 1;
    }
    result = from_bmp(input_file,&image_prisine);
    if (result != CONVERTATION_SUCCESS) {
	print_error(result);
	return 1;
    }
    if (!close_file(&input_file)) {
	puts("[ERROR] Failed to close input file!");
	return 1;
    }
    
    
    if (!rotate_image(&image_modified,image_prisine)) {
	puts("[ERROR] Failed to modify the image!");
	return 1;
    }
    image_reset(&image_prisine);
    if (!open_file(&output_file,argv[2],"wb")) {
	puts("[ERROR] Failed to open output file!");
	return 1;
    }
    result = to_bmp(output_file,&image_modified);
    if (result != CONVERTATION_SUCCESS) {
	print_error(result);
	return 1;
    }
    image_reset(&image_modified);
    if (!close_file(&output_file)) {
	puts("[ERROR] Failed to close output file!");
	return 1;
    }
   
    return 0;
}


static void print_error (enum convertation_result result) {
	fprintf(stderr,"[ERRPR] %s\n", error_messages[result]);
}
