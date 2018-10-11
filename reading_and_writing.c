#include <stdio.h>
#include <stdlib.h> //for error calling exit()
#include <string.h>
#include <math.h>

#define SIZE 32
#define MAX_STRING 1000

int hex_convert(char* s)
{
	//printf("\nInput: %s", s);
	char amt[MAX_STRING] ="";
	for (int i =0; i < strlen(s); i++)
	{
		//printf("\n%c", s[i]);
		if(s[i] == '0')
		{
			strcat(amt, "0000");
			continue;
		}
		if(s[i] == '1')
		{
			strcat(amt, "0001");
			continue;
		}
		if(s[i] == '2')
		{
			strcat(amt, "0010");
			continue;
		}
		if(s[i] == '3')
		{
			strcat(amt, "0011");
			continue;
		}
		if(s[i] == '4')
		{
			strcat(amt, "0100");
			continue;

		}
		if(s[i] == '5')
		{
			strcat(amt, "0101");
			continue;
		}
		if(s[i] == '6')
		{
			strcat(amt, "0110");
			continue;
		}
		if(s[i] == '7')
		{
			strcat(amt, "0111");
			continue;
		}
		if(s[i] == '8')
		{
			strcat(amt, "1000");
			continue;
		}
		if(s[i] == '9')
		{
			strcat(amt, "1001");
			continue;
		}
		if(s[i] == 'A' || s[i] == 'a')
		{
			strcat(amt, "1010");
			continue;
		}
		if(s[i] == 'B'|| s[i] == 'b')
		{
			strcat(amt, "1011");
			continue;
		}
		if(s[i] == 'C'|| s[i] == 'c')
		{
			strcat(amt, "1100");
			continue;
		}
		if(s[i] == 'D'|| s[i] == 'd')
		{
			strcat(amt, "1101");
			continue;
		}
		if(s[i] == 'E'|| s[i] == 'e')
		{
			strcat(amt, "1110");
			continue;
		}
		if(s[i] == 'F'|| s[i] == 'f')
		{
			strcat(amt, "1111");
			continue;
		}
		else
		{
			printf("\nInvalid hex character: %c", s[i]);
			exit(0);
		}
	}
  //printf("\nBinary: %s\n",amt);	
	int final = 0;
	int index = 0;
	for (int i = strlen(amt)-1; i > 0; i--)
	{
		//printf("\nCurrent: %d", index);	
		if (amt[i] == '1')
		{
			//printf("\nIndex: %d",i);	
			final = final + pow(2, index);
		}
		index++;
	}
	//printf("\nDecimal: %d\n", final);	
	return final;
}

int ascii_convert(char* s)
{
  printf("\n\nInput:%s", s);
	char amt[MAX_STRING] ="";
  printf("\n%d", strlen(s));
	for (int i = 1; i < strlen(s); i=i+2)
	{
		//printf("\n%c", s[i]);
		if(s[i] == '0')
		{
			strcat(amt, "0");
			continue;
		}
		if(s[i] == '1')
		{
			strcat(amt, "1");
			continue;
		}
		if(s[i] == '2')
		{
			strcat(amt, "2");
			continue;
		}
		if(s[i] == '3')
		{
			strcat(amt, "3");
			continue;
		}
		if(s[i] == '4')
		{
			strcat(amt, "4");
			continue;

		}
		if(s[i] == '5')
		{
			strcat(amt, "5");
			continue;
		}
		if(s[i] == '6')
		{
			strcat(amt, "6");
			continue;
		}
		if(s[i] == '7')
		{
			strcat(amt, "7");
			continue;
		}
		if(s[i] == '8')
		{
			strcat(amt, "8");
			continue;
		}
		if(s[i] == '9')
		{
			strcat(amt, "9");
			continue;
		}
		if(s[i]=='c')
		{
			//printf("\nBinary: %s\n",amt);	
			return atoi(amt);
		}
		else
		{
			printf("\nInvalid ascii character: %c", s[i]);
			exit(0);
		}
	}
  printf("\nBinary: %s\n",amt);	
	return atoi(amt);
}
int type_convert(char* s)
{
	//printf("Values: %s", s);
	if (s[0] != '0' || s[1] != '0' && s[1] !='1')
	{
		printf("\n Unknown Type \n");
		exit(0);
	}
	if (s[1] == '0')
	{
		//printf("\nIs Type 0\n");
		return 0;
	}
	if (s[1] == '1')
	{
		//printf("\nIs Type 1\n");
		return 1;
	}
}

int main(int argc, char *argv[]) {
	// get command line input 
	// printf("%s\n", argv[1]);
	// open file and read file
	//int t = bin_test();

	FILE *fp;
	FILE *wp;
	char s[MAX_STRING] = "";
	char c[2] = "\0";
	int type;
	int type_counter = 2;
	int amount = 0;
	int  num_counter = 0;
	int hex_ascii_switch = 0;
	int comma_sep = 0;
	int ascii_reset = 1;
	fp = fopen(argv[1], "r");
	wp = fopen(argv[2], "w+");

while(1)
{
	while (type_counter>0)
	{
		if (ascii_reset == 0)
  	{
  		c[0] = '0';
  		ascii_reset = 1;
  	}
  	else
  	{
  		c[0] = fgetc(fp);
  	}

		if (strcmp(c, " ") == 0 || strcmp(c,"\n") == 0)
		{
			continue;
		}
		if (feof(fp)){
			printf("\nReached end of file");
			break;
	 }
	 	strcat(s,c);
		printf("string: %s\n",s);	
		type_counter--;
	}
	type = type_convert(s);
	printf("\n\nType: %d", type);
	if (type == 0)
	{
		amount = 2;
		num_counter = 4;
		hex_ascii_switch = 0;
	}
	else
	{
		amount = 6;
		hex_ascii_switch = 1;
		num_counter = 5;

	}
  memset(s,0,sizeof(s));	
  while (amount > 0)
	{
		c[0] = fgetc(fp);
		if (strcmp(c, " ") == 0 || strcmp(c,"\n") == 0)
		{
			continue;
		}
		if (feof(fp)){
			printf("\nReached end of file");
			break;
	 }
	 	strcat(s,c);
		amount--;
	}
	int act_amount = 0;

	if (hex_ascii_switch == 0)
	{
		 act_amount = hex_convert(s);
	}
	else 
	{
		  act_amount = ascii_convert(s);
	}

  printf("\nAmount: %d\n", act_amount);
	memset(s,0,sizeof(s));	

	int char_counter = 0;
	int value = 0;
  while (act_amount > 0)
  {
  	c[0] = fgetc(fp);

		if (strcmp(c, " ") == 0 || c[0] == '\n') //?FIX THIS NEWLINE
		{
			continue;
		}
		if (feof(fp)){
			printf("\nGot number: %s", s);
	 		value = ascii_convert(s);
    	printf("\n %d,", value);
	 		act_amount--;
	  	memset(s,0,sizeof(s));	//resets string
	  //printf("\nAmount: %d,", act_amount);
			printf("\nReached end of file");
			break;
	 }
	 char_counter++;
	 printf("\n---%c",c[0]);
	 strcat(s,c);


   //printf("\nChars: %d", char_counter);

   //hex check
  if(hex_ascii_switch==0)
  {
	 if(char_counter == num_counter) // when have (types's) num characters
	 {
		value = hex_convert(s);
	 	printf("\n%d,", value);
	 	char_counter = 0;   // reset counter
	 	act_amount--;        // decrese number amount
	 	memset(s,0,sizeof(s));	//resets string
	 // printf("\nAmount: %d,", act_amount);
	 }
	}
	else
	{
	 if(c[0] == 'c' ) //hOW ENTER 
	 {
	 	//printf("\nGot number: %s", s);
	 	value = ascii_convert(s);
    printf("\n%d,", value);
	 	act_amount--;
	  memset(s,0,sizeof(s));	//resets string
	 // printf("\nAmount: %d", act_amount);
	 }
	 if (c[0] == '0' && s[strlen(s)] != '3')
	 {
	 	//printf("Need reset");
	 	ascii_reset = 0;
	 	//printf("\nGot number: %s", s);
	 	value = ascii_convert(s);
    printf("%d,", value);
	 	act_amount--;
	  memset(s,0,sizeof(s));	//resets string
	  //printf("\nAmount: %d", act_amount);
	 }
	}
  }
  type_counter = 2;
}

	fclose(fp);	//close file pointers
	fclose(wp);
	printf("\nWrote successfully\n");
	 return(0);
}
