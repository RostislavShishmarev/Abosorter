#ifndef CONST_H
#define CONST_H

#define OPTS "i:o:"
#define BIN_MODE_STRING "bin"
#define NOFILE_STRING "-"

#define TXT_MODE 't'
#define BIN_MODE 'b'

#define CHAR_END '\0'
#define CHARS_SEP ";"

#define STR_BUFSIZ 80
#define ARR_BUFSIZ 5

#define PHONE_LEN 16

#define ERRMEM_MSG "Memory error, abort program"

typedef enum {
	ERR_OK = 0,
	ERR_MEM = 1,
	ERR_ARGS = 2,
	ERR_IO = 3,
	ERR_SKIP = 4,
} ErrorCode;

void total_free(char**);

#endif

