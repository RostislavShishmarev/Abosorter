#ifndef CONST_H
#define CONST_H

#define OPTS "i:o:"
#define BIN_MODE_STRING "bin"
#define NOFILE_STRING "-"

#define STD_MODE 's'
#define TXT_MODE 't'
#define BIN_MODE 'b'

typedef enum {
	ERR_OK = 0,
	ERR_MEM = 1,
	ERR_ARGS = 2,
	ERR_IO = 3,
	ERR_SKIP = 4,
} ErrorCode;

#endif

