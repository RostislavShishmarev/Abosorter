#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "abonent.h"

Abonent init_abonent(char* name, char phone[16], int call_time) {
	Abonent abonent;

	abonent.name = name;
	abonent.call_time = call_time;
	memcpy(abonent.phone, phone, sizeof(char) * 16);

	return abonent;
}

void del_abonent(Abonent abonent) {
	free(abonent.name);
}

int check_phone(char phone[16]) {
	return 1;
}

void print_abonent(FILE* file, Abonent abonent) {
	fprintf(file, "%ld;%s;%s;%d\n", strlen(abonent.name), abonent.name, abonent.phone, abonent.call_time);
}

void print_aboarray(FILE* file, Aboarray aboarray) {
	for (int i = 0; i < aboarray.size; ++i) {
		print_abonent(file, aboarray.array[i]);
	}
}

