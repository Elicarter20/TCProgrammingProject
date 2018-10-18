
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

char* get_values(char* contents);
char* change_type(char* values, char* tf);
int do_write(char* trans, char* target);
int check_file(char* contents);

#endif /* TRANSLATOR_H */
