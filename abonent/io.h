#ifndef IO_H
#define IO_H

#include "../const.h"
#include "abonent.h"

ErrorCode input_abofile(const char*, const char, Abonent**);
ErrorCode output_abofile(const char*, const char, const Abonent*);

#endif

