#include <stdio.h>
#include <stdlib.h> //for error calling exit()
#include <string.h>
int main(int argc, char *argv[]) {
  // get command line input
  // printf("%s\n", argv[1]);
  // open file and read file
  FILE *fp;
  FILE *wp;
  char c;
  fp = fopen(argv[1], "r");
  wp = fopen(argv[2], "w+");
  while(1) { 
	 c = fgetc(fp);
	 if (feof(fp)){
		break;
	 }
 	//printf("%c", c);
	fputc(c, wp);	
  }

//close file pointers
  fclose(fp);
  fclose(wp);
  printf("Wrote successfully");
   return(0);
}
