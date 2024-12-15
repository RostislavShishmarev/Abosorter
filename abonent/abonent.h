#ifndef ABONENT_H
#define ABONENT_H

#include <stdio.h>

#include "../const/const.h"

typedef struct {
	char* name;
	char phone[PHONE_LEN + 1];
	time_t call_time;
} Abonent;

typedef struct {
	Abonent* array;
	size_t size;
} Aboarray;

Abonent init_abonent(char*, char[PHONE_LEN + 1], time_t);
void clear_abonent(Abonent);
int check_phone(char*);
void print_abonent(FILE*, Abonent);
ErrorCode generate_abonent(Abonent*);
void print_aboarray(FILE*, Aboarray);
void free_aboarray(Aboarray);

#endif

