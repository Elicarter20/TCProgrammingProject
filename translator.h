
#ifndef TRANSLATOR_H
#define TRANSLATOR_H



#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/socket.h> /* socket definitions */
#include <sys/types.h> /* socket types */
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

char* get_values(char* input);
int check_file(char* input);
char* change_type(char* values, char* tf);
int do_write(char* trans, char* target);

#endif /* TRANSLATOR_H */
