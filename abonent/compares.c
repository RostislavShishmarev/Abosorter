#include <string.h>
#include <stdlib.h>

#include "abonent.h"

int compare_name(const void* ptr1, const void* ptr2, void* arg) {
	Abonent abo1 = *(const Abonent *)ptr1;
	Abonent abo2 = *(const Abonent *)ptr2;

	char mode = *(char*)arg;

	int res = strcmp(abo1.name, abo2.name);
	
	if (mode == REVERSE_MODE) {
		res *= -1;
	}

	return res;
}

int compare_phone(const void* ptr1, const void* ptr2, void* arg) {
	Abonent abo1 = *(const Abonent *)ptr1;
	Abonent abo2 = *(const Abonent *)ptr2;

	char mode = *(char*)arg;

	char* phone1 = abo1.phone;
	char* phone2 = abo2.phone;

	if (phone1[0] == '+') {
		phone1 += 1;
	}
	if (phone2[0] == '+') {
		phone2 += 1;
	}

	int res = strcmp(phone1, phone2);
	
	if (mode == REVERSE_MODE) {
		res *= -1;
	}

	return res;
}

int compare_call_time(const void* ptr1, const void* ptr2, void* arg) {
	Abonent abo1 = *(const Abonent *)ptr1;
	Abonent abo2 = *(const Abonent *)ptr2;

	char mode = *(char*)arg;

	int res = (int)(abo1.call_time - abo2.call_time);
	
	if (mode == REVERSE_MODE) {
		res *= -1;
	}

	return res;
}

