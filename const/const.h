#ifndef CONST_H
#define CONST_H

#define SORTER_OPTS "i:o:rna:f:"
#define TIMER_OPTS "s:n:e:ra:f:"
#define BIN_MODE_STRING "bin"
#define TXT_MODE_STRING "txt"
#define NOFILE_STRING "-"

#define TXT_MODE 't'
#define BIN_MODE 'b'

#define CHAR_END '\0'
#define CHARS_SEP ";"

#define STR_BUFSIZ 80
#define ARR_BUFSIZ 5

#define PHONE_LEN 16

#define ERRMEM_MSG "Memory error, abort program"

#define DIGITS "0123456789"

#define NAME_FIELD "name"
#define PHONE_FIELD "phone"
#define CALL_TIME_FIELD "time"

#define GNOME_TYPE "gnome"
#define DSELECT_TYPE "dselect"
#define QUICK_TYPE "quick"

#define REVERSE_MODE 'r'
#define NORMAL_MODE 'n'

#define STEP_SIZE 100
#define N_STEPS 100
#define N_ARRAYS_IN_STEPS 10

#define MAX_NAME_LEN 30

typedef enum {
	ERR_OK = 0,
	ERR_MEM = 1,
	ERR_ARGS = 2,
	ERR_IO = 3,
	ERR_SKIP = 4,
} ErrorCode;

void total_free(char**);

#endif

