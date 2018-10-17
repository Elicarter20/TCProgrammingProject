
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

#define FORMAT_ONE_TYPE 0
#define FORMAT_TWO_TYPE 1
#define FORMAT_ONE_NUM_SIZE 2 // bytes
#define FORMAT_TWO_NUM_SIZE 5 // characters
#define FORMAT_ONE_AMOUNT_SIZE 1 // bytes
#define FORMAT_TWO_AMOUNT_SIZE 3 // bytes
#define NO_BYTES_READ -1
#define SUCCESS_MESSAGE "Success"
#define ERROR_MESSAGE "Format error"
#define NO_FLAGS 0
#define NO_TRANSLATION 0
#define FORMAT_ONE_TO_TWO 1
#define FORMAT_TWO_TO_ONE 2
#define SWAP_FORMATS 3
#define OUTPUT_FOLDER "../testData/";

char* get_values(char* input);
int check_file(char* input);
char* change_type(char* values, char* tf);


#endif /* TRANSLATOR_H */