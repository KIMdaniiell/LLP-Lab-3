#include "../include/image_file_io.h"


bool open_file(FILE** file_ptr, char const * file_name, char const* mode) {
	*file_ptr = fopen(file_name, mode);
	return *file_ptr;
}

bool close_file(FILE** file_ptr) {
	if (fclose(*file_ptr) == 0) {
		return true;	
	} else {
		return false;
	}
}
