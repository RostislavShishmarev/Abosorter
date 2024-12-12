#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abonent.h"
#include "../const.h"

ErrorCode input_abofile(const char* filename, const char mode, Aboarray* aboarray) {
	FILE* file = stdin;

	int end_of_input = 0;

	if (filename != NULL) {
		printf("%s\n", filename);
		file = fopen(filename, "r");
		if (file = NULL) {
			perror("Can`t open file\n");
			return ERR_IO;
		}
		printf("Successfully open\n");
	}
			
	switch (mode) {
		case TXT_MODE:
			Abonent abo_buffer[ARR_BUFSIZ] = {0};
			
			int n_buf_abonents = 0;
			
			char str_buffer[81] = {0};
			int len = 0;

			char* string = NULL;
			char* name = NULL;

			int n_strings = 0;

			do {
				// Get file string

				string = NULL;
				len = 0;

				do {
					int res = fscanf(file, "%80[^\n]", str_buffer);

					if (res <= 0) {
						scanf("%*c");

						if (res == -1) {
							end_of_input = 1;
						}
						break;
					}

					int add_len = strlen(str_buffer);

					string = realloc(string, (len + add_len + 1) * sizeof(char));

					if (string == NULL) {
						fprintf(stderr, ERRMEM_MSG);
						return ERR_MEM;
					}

					memcpy(string + len, str_buffer, add_len * sizeof(char));

					len += add_len;

				} while (1);

				if (end_of_input == 1) {
					break;
				}

				n_strings += 1;
	
				if (string == NULL) {
					fprintf(stderr, "Can`t read string %d\n", n_strings);
					continue;
				}

				string[len] = CHAR_END;

				// Get name parameter

				char* name_word = strtok(string, CHARS_SEP);
				
				if (name_word == NULL) {
					fprintf(stderr, "Can`t find name field on string %d\n", n_strings);
					free(string);
					continue;
				}

				int name_word_len = strlen(name_word);

				name = malloc((name_word_len + 1) * sizeof(char));

				if (name == NULL) {
					fprintf(stderr, "%s. Place: field name for string %d\n", ERRMEM_MSG, n_strings);
					free(string);
					continue;
				}

				memcpy(name, name_word, name_word_len * sizeof(char));
				name[name_word_len] = CHAR_END;

				// Get phone parameter
				
				char* phone_word = strtok(NULL, CHARS_SEP);

				if (phone_word == NULL) {
					fprintf(stderr, "Can`t find phone field on string %d\n", n_strings);
					free(string);
					free(name);
					continue;
				}

				int phone_word_len = strlen(phone_word);

				char phone[PHONE_LEN + 1] = {0};

				if (check_phone(phone_word) == 0) {
					fprintf(stderr, "Wrong format of phone field on string %d\n", n_strings);
					free(string);
					free(name);
					continue;
				}

				memcpy(phone, phone_word, phone_word_len * sizeof(char));
				phone[phone_word_len] = CHAR_END;

				// Get call time parameter
				
				char* call_time_word = strtok(NULL, CHARS_SEP);

				if (call_time_word == NULL) {
					fprintf(stderr, "Can`t find call time field on string %d\n", n_strings);
					free(string);
					free(name);
					continue;
				}

				int call_time = atoi(call_time_word);

				if (call_time == 0) {
					fprintf(stderr, "Wrong format of call time field on string %d\n", n_strings);
					free(string);
					free(name);
					continue;
				}

				// Init abonent

				abo_buffer[n_buf_abonents] = init_abonent(name, phone, call_time);
				n_buf_abonents += 1;

				if (n_buf_abonents >= ARR_BUFSIZ) {
					n_buf_abonents = 0;

					(*aboarray).array = realloc((*aboarray).array, ((*aboarray).size + ARR_BUFSIZ) * sizeof(Abonent));
					if ((*aboarray).array == NULL) {
						fprintf(stderr, ERRMEM_MSG);
						free(string);
						free(name);
						return ERR_MEM;
					}
					memcpy((*aboarray).array + (*aboarray).size, abo_buffer, ARR_BUFSIZ * sizeof(Abonent));
					(*aboarray).size += ARR_BUFSIZ;
				}

			} while (1);

			if (string != NULL) {
				free(string);
			}

			if (n_buf_abonents == 0) {
				break;
			}

			(*aboarray).array = realloc((*aboarray).array, ((*aboarray).size + n_buf_abonents) * sizeof(Abonent));
			if ((*aboarray).array == NULL) {
				fprintf(stderr, ERRMEM_MSG);
				free(name);
				return ERR_MEM;
			}
			memcpy((*aboarray).array + (*aboarray).size, abo_buffer, n_buf_abonents * sizeof(Abonent));
			(*aboarray).size += n_buf_abonents;
			break;
		case BIN_MODE:
			break;
		default:
			return ERR_ARGS;
	}

	fclose(file);

	return ERR_OK;
}

ErrorCode output_abofile(const char* filename, const char mode, const Aboarray aboarray) {
	FILE* file = stdout;

	int end_of_input = 0;

	if (filename != NULL) {
		file = fopen(filename, "w");
	}
			
	switch (mode) {
		case TXT_MODE:
			print_aboarray(file, aboarray);
			break;
		case BIN_MODE:
			break;
	}
	return ERR_OK;
}

