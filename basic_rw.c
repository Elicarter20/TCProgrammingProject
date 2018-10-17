#include <stdio.h>
#include <stdlib.h> //for error calling exit()
#include <string.h>
#include "translator.h"
#define MAX_STRING 1024

int main(int argc, char *argv[]) {
  printf("testing environment GO!\n");
  char input_file_path[MAX_STRING] = "../PracProj/test.txt";
  char type_format[MAX_STRING] = "3"; 
  char target_file_path[MAX_STRING] = "here.txt";
  int t = check_file(input_file_path);
  if (t == 1)
  {
    exit(0);
  }
  char* res = control(input_file_path,type_format,target_file_path);
  char* ret = type(res, type_format);
  //printf("Final Result: %s\n",res);
  return(0);
}
