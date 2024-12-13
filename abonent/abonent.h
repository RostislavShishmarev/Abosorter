#ifndef ABONENT_H
#define ABONENT_H

#include <stdio.h>

typedef struct {
	char* name;
	char phone[16];
	time_t call_time;
} Abonent;

typedef struct {
	Abonent* array;
	int size;
} Aboarray;

Abonent init_abonent(char*, char[16], time_t);
void clear_abonent(Abonent);
int check_phone(char[16]);
void print_abonent(FILE*, Abonent);
void print_aboarray(FILE*, Aboarray);
void free_aboarray(Aboarray);

#endif

