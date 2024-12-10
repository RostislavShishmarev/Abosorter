#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abonent.h"
#include "../const.h"

ErrorCode input_abofile(const char* filename, const char mode, Aboarray* aboarray) {
	int code = 0;
	int len = 0;
	int i = 2;

	int name_len = 0;
	char* name = NULL;
	char phone[16] = {};
	int call_time = 0;
	
	FILE* file = stdin;

	if (filename != NULL) {
		file = fopen(filename, "w");
	}
			
	switch (mode) {
		case TXT_MODE:
			code = fscanf(file, "%d\n", &len);
			if (code != 1) {
				return ERR_IO;
			}

			(*aboarray).size = len;

			(*aboarray).array = realloc((*aboarray).array, sizeof(Abonent) * len);

			do {
				i += 1;

				if (i - 1 >= len) {
					break;
				}

				code = fscanf(file, "%d", &name_len);

				if (code == -1) {
					break;
				}

				if (name_len == 0) {
					fprintf(stderr, "Error on reading string %d: name len must be > 0\n", i);
					continue;
				}


				name = malloc(sizeof(char) * (name_len + 1));

				code = fscanf(file, ";%s;%16s;%d\n", name, phone, &call_time);

				if (code == -1) {
					break;
				}

				if (code != 3) {
					fprintf(stderr, "Error on reading string %d\n", i);
					continue;
				}

				Abonent abonent = init_abonent(name, phone, call_time);

				(*aboarray).array[i - 2] = abonent;
			} while (1);

			break;
		case BIN_MODE:
			break;
		default:
			return ERR_ARGS;
	}

	return ERR_OK;
}

ErrorCode output_abofile(const char* filename, const char mode, const Aboarray aboarray) {
}

