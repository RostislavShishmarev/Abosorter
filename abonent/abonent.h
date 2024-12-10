#ifndef ABONENT_H
#define ABONENT_H

#include <stdio.h>

typedef struct {
	char* name;
	char phone[16];
	int call_time;
} Abonent;

typedef struct {
	Abonent* array;
	int size;
	int capacity;
} Aboarray;

Abonent init_abonent(char*, char[16], int);
void clear_abonent(Abonent);
int check_phone(char[16]);
void print_abonent(FILE*, Abonent);
void print_aboarray(FILE*, Aboarray);

#endif

