#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/random.h>

#include "abonent.h"
#include "../const/const.h"

Abonent init_abonent(char* name, char phone[PHONE_LEN + 1], time_t call_time) {
	Abonent abonent;

	abonent.name = name;
	abonent.call_time = call_time;
	memcpy(abonent.phone, phone, sizeof(char) * 16);
	(abonent.phone)[strlen(phone)] = CHAR_END;

	return abonent;
}

void del_abonent(Abonent abonent) {
	free(abonent.name);
}

int check_phone(char* phone) {
	size_t len = (size_t)strlen(phone);

	if (len > PHONE_LEN) {
		return 0;
	}

	if (phone[0] == '+') {
		phone += 1;
		len -= 1;
	}

	if (strspn(phone, DIGITS) != len) {
		return 0;
	}

	return 1;
}

void print_abonent(FILE* file, Abonent abonent) {
	fprintf(file, "%s;%s;%ld\n", abonent.name, abonent.phone, abonent.call_time);
}

ErrorCode generate_abonent(Abonent* abonent) {
	// Generate name
	
	int name_len = rand() % MAX_NAME_LEN + 1;

	(*abonent).name = malloc((name_len + 1) * sizeof(char));

	if ((*abonent).name == NULL) {
		return ERR_MEM;
	}

	ssize_t res_size = getrandom((*abonent).name, name_len, GRND_NONBLOCK);

	if (res_size < name_len) {
		free((*abonent).name);
		return ERR_IO;
	}

	(*abonent).name[name_len] = CHAR_END;

	// Generate phone
	
	int start_index = 0;
	int add_plus = rand() % 2;

	if (add_plus == 1) {
		(*abonent).phone[0] = '+';
		start_index = 1;
	}

	for (int i = start_index; i < PHONE_LEN; i++) {
		(*abonent).phone[i] = DIGITS[rand() % 10];
	}

	(*abonent).phone[PHONE_LEN] = CHAR_END;

	// Generate call time

	(*abonent).call_time = (time_t)rand();

	return ERR_OK;
}

void print_aboarray(FILE* file, Aboarray aboarray) {
	if (aboarray.size == 0) {
		fprintf(file, "No data\n\n");
		return;
	}
	
	for (size_t i = 0; i < aboarray.size; ++i) {
		print_abonent(file, aboarray.array[i]);
	}
}

void free_aboarray(Aboarray aboarray) {
	if (aboarray.size == 0) {
		return;
	}
	
	for (size_t i = 0; i < aboarray.size; ++i) {
		del_abonent(aboarray.array[i]);
	}

	free(aboarray.array);
}

