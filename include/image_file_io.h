#ifndef _IMAGE_FILE_IO_H_
#define _IMAGE_FILE_IO_H_

#include <stdbool.h>
#include <stdio.h>

bool open_file(FILE** file_ptr, char const * file_name, char const* mode);

bool close_file(FILE** file_ptr);

#endif
