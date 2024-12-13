#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abonent.h"
#include "../const/const.h"

ErrorCode input_abofile(const char* filename, const char mode, Aboarray* aboarray) {
	FILE* file = stdin;
	
	switch (mode) {
		case TXT_MODE:
			// Open file
	
			if (filename != NULL) {
				file = fopen(filename, "r");
				if (file == NULL) {
					fprintf(stderr, "Can`t open file %s\n", filename);
					return ERR_IO;
				}
			}

			// Init variables

			Abonent abo_buffer[ARR_BUFSIZ] = {0};
			
			int n_buf_abonents = 0;
			size_t n_strings = 0;
			int end_of_input = 0;
			
			char str_buffer[81] = {0};

			char* string = NULL;
			char* name = NULL;

			do {
				// Get file string
				
				if (string != NULL) {
					total_free(&string);
				}

				int len = 0;

				do {
					int res = fscanf(file, "%80[^\n]", str_buffer);

					if (res <= 0) {
						fscanf(file, "%*c");

						if (res == -1) {
							end_of_input = 1;
						}
						break;
					}

					int add_len = strlen(str_buffer);

					string = realloc(string, (len + add_len + 1) * sizeof(char));

					if (string == NULL) {
						fprintf(stderr, ERRMEM_MSG);
						fclose(file);
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
					fprintf(stderr, "Can`t read string %ld\n", n_strings);
					continue;
				}

				string[len] = CHAR_END;

				// Get name parameter

				char* name_word = strtok(string, CHARS_SEP);
				
				if (name_word == NULL) {
					fprintf(stderr, "Can`t find name field on string %ld\n", n_strings);
					total_free(&string);
					continue;
				}

				int name_word_len = strlen(name_word);

				name = malloc((name_word_len + 1) * sizeof(char));

				if (name == NULL) {
					fprintf(stderr, "%s. Place: field name for string %ld\n", ERRMEM_MSG, n_strings);
					total_free(&string);
					continue;
				}

				memcpy(name, name_word, name_word_len * sizeof(char));
				name[name_word_len] = CHAR_END;

				// Get phone parameter
				
				char* phone_word = strtok(NULL, CHARS_SEP);

				if (phone_word == NULL) {
					fprintf(stderr, "Can`t find phone field on string %ld\n", n_strings);
					total_free(&string);
					total_free(&name);
					continue;
				}

				int phone_word_len = strlen(phone_word);

				char phone[PHONE_LEN + 1] = {0};

				if (check_phone(phone_word) == 0) {
					fprintf(stderr, "Wrong format of phone field on string %ld\n", n_strings);
					total_free(&string);
					total_free(&name);
					continue;
				}

				memcpy(phone, phone_word, phone_word_len * sizeof(char));
				phone[phone_word_len] = CHAR_END;

				// Get call time parameter
				
				char* call_time_word = strtok(NULL, CHARS_SEP);

				if (call_time_word == NULL) {
					fprintf(stderr, "Can`t find call time field on string %ld\n", n_strings);
					total_free(&string);
					total_free(&name);
					continue;
				}

				time_t call_time = (time_t)atoi(call_time_word);

				if (call_time == 0) {
					fprintf(stderr, "Wrong format of call time field on string %ld\n", n_strings);
					total_free(&string);
					total_free(&name);
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
						total_free(&string);
						total_free(&name);
						fclose(file);
						return ERR_MEM;
					}
					memcpy((*aboarray).array + (*aboarray).size, abo_buffer, ARR_BUFSIZ * sizeof(Abonent));
					(*aboarray).size += ARR_BUFSIZ;
				}

			} while (1);

			if (string != NULL) {
				total_free(&string);
			}

			if (n_buf_abonents == 0) {
				break;
			}

			(*aboarray).array = realloc((*aboarray).array, ((*aboarray).size + n_buf_abonents) * sizeof(Abonent));
			if ((*aboarray).array == NULL) {
				fprintf(stderr, ERRMEM_MSG);
				total_free(&name);
				fclose(file);
				return ERR_MEM;
			}
			memcpy((*aboarray).array + (*aboarray).size, abo_buffer, n_buf_abonents * sizeof(Abonent));
			(*aboarray).size += n_buf_abonents;
			break;
		case BIN_MODE:
			// Open file
	
			if (filename != NULL) {
				file = fopen(filename, "rb");
				if (file == NULL) {
					fprintf(stderr, "Can`t open file %s\n", filename);
					return ERR_IO;
				}
			}

			// Init variables

			size_t res = 0;
			size_t aboarray_len = 0;

			// Init aboarray
			
			res = fread(&aboarray_len, sizeof(size_t), 1, file);

			if (res != 1) {
				fprintf(stderr, "Can`t read number of aboarray elements\n");
				fclose(file);
				return ERR_IO;
			}

			(*aboarray).array = malloc(aboarray_len * sizeof(Abonent));

			if ((*aboarray).array == NULL) {
				fprintf(stderr, ERRMEM_MSG);
				fclose(file);
				return ERR_MEM;
			}

			for (size_t i = 0; i < aboarray_len; ++i) {
				// Get name parameter

				size_t name_len = 0;

				res = fread(&name_len, sizeof(size_t), 1, file);

				if (res != 1) {
					fprintf(stderr, "Can`t read name len of abonent %ld\n", i + 1);
					fclose(file);
					return ERR_IO;
				}

				if (name_len == 0) {
					fprintf(stderr, "Incorrect name len of abonent %ld\n", i + 1);
					fclose(file);
					return ERR_IO;
				}

				char* name = malloc(sizeof(char) * (name_len + 1));

				if (name == NULL) {
					fprintf(stderr, ERRMEM_MSG);
					fclose(file);
					return ERR_MEM;
				}

				res = fread(name, sizeof(char), name_len, file);

				if (res != name_len) {
					fprintf(stderr, "Can`t read name len of abonent %ld\n", i + 1);
					fclose(file);
					total_free(&name);
					return ERR_IO;
				}

				name[name_len] = CHAR_END;

				// Get phone parameter

				size_t phone_len = 0;

				res = fread(&phone_len, sizeof(size_t), 1, file);

				if (res != 1) {
					fprintf(stderr, "Can`t read phone len of abonent %ld\n", i + 1);
					fclose(file);
					total_free(&name);
					return ERR_IO;
				}

				if (phone_len > PHONE_LEN || phone_len == 0) {
					fprintf(stderr, "Incorrect phone len of abonent %ld\n", i + 1);
					fclose(file);
					total_free(&name);
					return ERR_IO;
				}

				char phone[PHONE_LEN + 1] = {0};

				res = fread(phone, sizeof(char), phone_len, file);
				
				if (res != phone_len) {
					fprintf(stderr, "Can`t read phone of abonent %ld\n", i + 1);
					fclose(file);
					total_free(&name);
					return ERR_IO;
				}

				phone[phone_len] = CHAR_END;

				if (check_phone(phone) != 1) {
					fprintf(stderr, "Incorrect phone of abonent %ld\n", i + 1);
					fclose(file);
					total_free(&name);
					return ERR_IO;
				}

				// Get call time parameter

				time_t call_time = 0;

				res = fread(&call_time, sizeof(time_t), 1, file);

				if (res != 1) {
					fprintf(stderr, "Can`t read call time of abonent %ld\n", i + 1);
					fclose(file);
					total_free(&name);
					return ERR_IO;
				}

				// Init abonent
				
				Abonent abonent = init_abonent(name, phone, call_time);

				(*aboarray).array[(*aboarray).size] = abonent;

				(*aboarray).size += 1;
			}

			break;
		default:
			return ERR_ARGS;
	}

	fclose(file);

	return ERR_OK;
}

ErrorCode output_abofile(const char* filename, const char mode, const Aboarray aboarray) {
	FILE* file = stdout;

	switch (mode) {
		case TXT_MODE:
			if (filename != NULL) {
				file = fopen(filename, "w");
				if (file == NULL) {
					fprintf(stderr, "Can`t open file %s\n", filename);
					return ERR_IO;
				}
			}

			print_aboarray(file, aboarray);

			break;
		case BIN_MODE:
			size_t res = 0;

			if (filename != NULL) {
				file = fopen(filename, "wb");
				if (file == NULL) {
					fprintf(stderr, "Can`t open file %s\n", filename);
					return ERR_IO;
				}
			}

			res = fwrite(&aboarray.size, sizeof(size_t), 1, file);

			if (res != 1) {
				fprintf(stderr, "Can`t write number of aboarray elements\n");
				fclose(file);
				return ERR_IO;
			}

			for (size_t i = 0; i < aboarray.size; ++i) {
				Abonent abonent = (aboarray.array)[i];
				
				size_t name_len = strlen(abonent.name);
				res = fwrite(&name_len, sizeof(size_t), 1, file);

				if (res != 1) {
					fprintf(stderr, "Can`t write name len of abonent %ld\n", i + 1);
					fclose(file);
					return ERR_IO;
				}

				res = fwrite(abonent.name, sizeof(char), name_len, file);

				if (res != name_len) {
					fprintf(stderr, "Can`t write name of abonent %ld\n", i + 1);
					fclose(file);
					return ERR_IO;
				}

				size_t phone_len = strlen(abonent.phone);
				res = fwrite(&phone_len, sizeof(size_t), 1, file);

				if (res != 1) {
					fprintf(stderr, "Can`t write phone len of abonent %ld\n", i + 1);
					fclose(file);
					return ERR_IO;
				}

				res = fwrite(abonent.phone, sizeof(char), phone_len, file);

				if (res != phone_len) {
					fprintf(stderr, "Can`t write phone of abonent %ld\n", i + 1);
					fclose(file);
					return ERR_IO;
				}

				res = fwrite(&(abonent.call_time), sizeof(time_t), 1, file);

				if (res != 1) {
					fprintf(stderr, "Can`t write call time of abonent %ld\n", i + 1);
					fclose(file);
					return ERR_IO;
				}
			}		
			break;
	}

	fclose(file);
	return ERR_OK;
}

