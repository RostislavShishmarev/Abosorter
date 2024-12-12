#include <stdlib.h>

void total_free(char** ptr) {
	free(*ptr);
	*ptr = NULL;
}
