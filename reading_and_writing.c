#include <stdio.h>
#include <stdlib.h> //for error calling exit()
#include <string.h>

#define SIZE 32


int bin_test()
{
  int output[SIZE];
  int c;
  int x =0;

  printf("Type hex (l/c) digits, 0 to end: ");
  while (x < SIZE)
  {
    scanf("%2x", &c);
    output[x] = (int)c;
    if (c==0) break;
    x++;
  }
  printf("\n%d\n", output);
  return(0);


}

int main(int argc, char *argv[]) {
  // get command line input
  // printf("%s\n", argv[1]);
  // open file and read file
  //int t = bin_test();

  FILE *fp;
  FILE *wp;
  char c;
  char* s;
  float hex_counter = 0;

  fp = fopen(argv[1], "r");
  wp = fopen(argv[2], "w+");
  while(1) { 
	 c = fgetc(fp);

	 if (feof(fp)){
	   printf("%c", '\n');
  	break;
	 }
  hex_counter++;
  printf("%c", c);

	fputc(c, wp);	//writes to file
  }

  printf("%s", "Bytes: ");
  printf("%f\n", hex_counter/2);
//close file pointers
  fclose(fp);
  fclose(wp);
  printf("Wrote successfully");
   return(0);
}
