#include "abonent/abonent.h"
#include "abonent/io.h"
#include "sorts/sorts.h"

int main(int argc, char **argv) {
	int command = 0;
	char *input_mode = NULL;
	char *output_mode = NULL;

	while ((command = getopt(argc, argv, "i:o:")) != -1) {
		switch (command) {
			case 'i':
				input_mode = optarg;
				break;
			case 'o':
				output_mode = optarg;
				break;

	return 0;
}

