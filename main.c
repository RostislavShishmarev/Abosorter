#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "abonent/abonent.h"
#include "abonent/io.h"
#include "sorts/sorts.h"
#include "const/const.h"

int main(int argc, char **argv) {
	ErrorCode code = ERR_OK;
	int command = 0;

	char *input_mode = NULL;
	char *input_filename = NULL;

	char *output_mode = NULL;
	char *output_filename = NULL;

	while ((command = getopt(argc, argv, OPTS)) != -1) {
		switch (command) {
			case 'i':
				input_mode = optarg;
				break;
			case 'o':
				output_mode = optarg;
				break;
			case '?':
				if (index(OPTS, optopt) != NULL) {
					fprintf(stderr, "Option -%c requires an argument\n", optopt);
				} else if (isprint(optopt)) {
					fprintf(stderr, "Unknown option `-%c`\n", optopt);
				} else {
					fprintf(stderr, "Unknown option character `\\x%x`\n", optopt);
				}
				return 1;
			default:
				abort();
		}
	}

	if (argc >= optind + 1 && strcmp(argv[optind], NOFILE_STRING) != 0) {
		input_filename = argv[optind];
	}
	if (argc >= optind + 2 && strcmp(argv[optind + 1], NOFILE_STRING) != 0) {
		output_filename = argv[optind + 1];
		
	}	

	// printf("%s, %s\n", input_mode, output_mode);
	// printf("%s, %s\n", input_filename, output_filename);

	char i_mode;
	if (input_mode == NULL) {
		i_mode = TXT_MODE;
	} else if (strcmp(BIN_MODE_STRING, input_mode) == 0) {
		i_mode = BIN_MODE;
	} else {
		fprintf(stderr, "Unknown file mode: %s\n", input_mode);
		return 1;
	}

	char o_mode;
	if (output_mode == NULL) {
		o_mode = TXT_MODE;
	} else if (strcmp(BIN_MODE_STRING, output_mode) == 0) {
		o_mode = BIN_MODE;
	} else {
		fprintf(stderr, "Unknown file mode: %s\n", output_mode);
		return 1;
	}

	// Input

	Aboarray aboarray = {NULL, 0};

	code = input_abofile(input_filename, i_mode, &aboarray);

	if (code != ERR_OK) {
		fprintf(stderr, "Error during input data\n");
	}

	// Sort
	

	// Output

	code = output_abofile(output_filename, o_mode, aboarray);

	if (code != ERR_OK) {
		fprintf(stderr, "Error during output data\n");
	}
	
	// Free
	
	free_aboarray(aboarray);

	return 0;
}

