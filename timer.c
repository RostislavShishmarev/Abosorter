#define _GNU_SOURCE

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "abonent/abonent.h"
#include "abonent/compares.h"
#include "sorts/sorts.h"
#include "const/const.h"

int main(int argc, char **argv) {
	// Init variables
	
	int command = 0;

	int step_size = STEP_SIZE;
	int n_arrays_in_step = N_ARRAYS_IN_STEPS;
	int n_steps = N_STEPS;

	int reverse_sort = 0;

	char *field = CALL_TIME_FIELD;
	char *sort_type = QUICK_TYPE;

	int (*compare_func)(const void *, const void *, void *);
	void (*sort_func)(void*, size_t, size_t, int (*)(const void *, const void *, void *), void*);

	int print_generated_data = 0;

	// Get opts

	while ((command = getopt(argc, argv, TIMER_OPTS)) != -1) {
		switch (command) {
			case 's':
				step_size = atoi(optarg);
				break;
			case 'n':
				n_steps = atoi(optarg);
				break;
			case 'e':
				n_arrays_in_step = atoi(optarg);
				break;
			case 'r':
				reverse_sort = 1;
				break;
			case 'a':
				sort_type = optarg;
				break;
			case 'f':
				field = optarg;
				break;
			case 'p':
				print_generated_data = 1;
				break;
			case '?':
				return 1;
			default:
				abort();
		}
	}
	
	// Parse opts
	
	if (step_size <= 0) {
		fprintf(stderr, "Step size (number of elements) (arg -s) must be integer > 0\n");
		return 1;
	}
	if (n_steps <= 0) {
		fprintf(stderr, "Number of steps (arg -n) must be integer > 0\n");
		return 1;
	}
	if (n_arrays_in_step <= 0) {
		fprintf(stderr, "Number of generating arrays in each step (arg -e) must be integer > 0\n");
		return 1;
	}

	if (strcmp(NAME_FIELD, field) == 0) {
		compare_func = compare_name;
	} else if (strcmp(PHONE_FIELD, field) == 0) {
		compare_func = compare_phone;
	} else if (strcmp(CALL_TIME_FIELD, field) == 0) {
		compare_func = compare_call_time;
	} else {
		fprintf(stderr, "Unknown sort field: %s\n", field);
		return 1;
	}

	char sort_mode;
	if (reverse_sort == 1) {
		sort_mode = REVERSE_MODE;
	} else {
		sort_mode = NORMAL_MODE;
	}

	if (strcmp(QUICK_TYPE, sort_type) == 0) {
		sort_func = qsort_r;
	} else if (strcmp(GNOME_TYPE, sort_type) == 0) {
		sort_func = gnome_sort;
	} else if (strcmp(DSELECT_TYPE, sort_type) == 0) {
		sort_func = dselect_sort;
	} else {
		fprintf(stderr, "Unknown sort type: %s\n", sort_type);
		return 1;
	}

	// Messages

	printf("Sort algorythm: %s\nSort field: %s\n\n", sort_type, field);
	if (reverse_sort == 1) {
		printf("Reversed sort\n\n");
	}
	printf("Steps number: %d; Step size: %d; Number of arrays in step: %d\n\n", n_steps, step_size, n_arrays_in_step);


	// Generate and count

	srand(time(NULL));

	int current_array_len = step_size;

	for (int i1 = 0; i1 < n_steps; i1++) {
		double full_time = 0;

		for (int i2 = 0; i2 < n_arrays_in_step; i2++) {
			
			// Generate

			Aboarray aboarray = {malloc(current_array_len * sizeof(Abonent)), 0};

			if (aboarray.array == NULL) {
				fprintf(stderr, ERRMEM_MSG);
				return 1;
			}

			for (int j = 0; j < current_array_len; j++) {
				Abonent abonent = {};
				ErrorCode res = generate_abonent(&abonent);
				if (res != ERR_OK) {
					fprintf(stderr, "Error during generating random data\n");
					free_aboarray(aboarray);
					return 1;
				}
				(aboarray.array)[j] = abonent;
				aboarray.size += 1;
				
				if (print_generated_data == 1) {	
					print_abonent(stdout, abonent);
				}
			}
	
			// Sort
			
			clock_t begin = clock();
		
			sort_func(aboarray.array, aboarray.size, sizeof(Abonent), compare_func, &sort_mode);

			clock_t end = clock();

			full_time += (double)(end - begin) * 1000.0 / CLOCKS_PER_SEC;

			free_aboarray(aboarray);
		}

		printf("%d\t%lf\n", current_array_len, full_time / n_arrays_in_step);

		current_array_len += step_size;
	}

	return 0;
}

