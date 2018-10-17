
#include <stdio.h>
#include <stdlib.h> //for error calling exit()
#include <string.h>
#include <math.h>
#include "translator.h"
#define SIZE 32
#define MAX_STRING 1024


//if 0, do no translation!
//if 1, tranlsate only type 0s
//if 2, translate only type 1s
//if 3, translate both
// (\x2)01,225,39(\x3)(\x2)11,24(\x3)(\x4)



int hex_convert(char* s)
{
  //printf("\nValue Input: %s\n", s);
	char amt[MAX_STRING] ="";
	for (int i =0; i < strlen(s); i++)
	{
		////printf("\n%c", s[i]);
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
			//printf("\nInvalid hex character: %c", s[i]);
			exit(0);
		}
	}
 // printf("\nBinary: %s\n",amt);	
	int final = 0;
	int index = 0;
	for (int i = strlen(amt)-1; i >= 0; i--)
	{
		//printf("\nCurrent: %d", index);	
		if (amt[i] == '1')
		{
			////printf("\nIndex: %d",i);
			final = final + pow(2, index);
		}
		index++;
	}
	//printf("\nDecimal: %d\n", final);	
	return final;
}

int ascii_convert(char* s)
{
  //printf("\nValue Input:%s", s);
	char amt[MAX_STRING] ="";
  //printf("\n%d", strlen(s));
	for (int i = 1; i < strlen(s); i=i+2)
	{
		////printf("\n%c", s[i]);
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
			////printf("\nBinary: %s\n",amt);	
			return atoi(amt);
		}
		else
		{
			//printf("\nInvalid ascii character: %c", s[i]);
			exit(0);
		}
	}
  //printf("\nBinary: %s\n",amt);	
	return atoi(amt);
}
int type_convert(char* s)
{
	////printf("Values: %s", s);
	if (s[0] != '0' || s[1] != '0' && s[1] !='1')
	{
		//printf("\n Unknown Type \n");
		exit(0);
	}
	if (s[1] == '0')
	{
		////printf("\nIs Type 0\n");
		return 0;
	}
	if (s[1] == '1')
	{
		////printf("\nIs Type 1\n");
		return 1;
	}
}

char* get_values(char* input) {
    printf("Arguments: %s\n",input );
	FILE *fp;
	char s[MAX_STRING] = "";
	char append[MAX_STRING] = "";
 	static char ret[MAX_STRING]="";
	char c[2] = "\0";
	char b[3] = "\0";
	int type;
	int type_counter = 2;
	int amount = 0;
	int  num_counter = 0;
	int hex_ascii_switch = 0;
	int ascii_reset = 1;
	fp = fopen(input, "r");

while(1)
{
	strcat(ret,"\x2"); // start delimeter for result
	while (type_counter>0)
	{
		if (ascii_reset == 0)
  	{
  //		printf("\nDoing Reset\n");
  //		printf("\n Type[0]: %s", b);
  //		printf("\nType[1]: %s", c);
  	//strcpy(c,d);
  		ascii_reset = 1;
  		strcat(s,b);
  		 // c[0] = fgetc(fp);

  		 strcat(s,c);
  		 type_counter = type_counter - 2;

  	}
  	else
  	{

  		c[0] = fgetc(fp);
	  // printf("\n---%c",c[0]);

		if (strcmp(c, " ") == 0 ||  strcmp(c,"\r")==0 || strcmp(c,"\n")==0)
		{
			continue;
		}
		if (feof(fp)){
			printf("\nReached end of file 1");
			strcat(ret,"\x3");
			strcat(ret,"\x4");
			memset(s,0,sizeof(s));

			fclose(fp);	//close file pointers
		//	printf("\nBUFFER: %s\n: ", ret);
			printf("\nWrote successfully\n");
	 		return ret;
	 }
	 	strcat(s,c);
		type_counter--;
		  	}
	}
	

   printf("\nType String: %s\n",s);	

	type = type_convert(s);
	if (type == 0)
	{
		amount = 2; // # of bytes in amount
		num_counter = 4;// # of chars per num
		hex_ascii_switch = 0;
	}
	if (type == 1)
	{
		amount = 6; // # of bytes in amount
		hex_ascii_switch = 1;
	}
  memset(s,0,sizeof(s));	
  while (amount > 0)
	{
		c[0] = fgetc(fp);
		if (strcmp(c, " ") == 0 ||  strcmp(c,"\r")==0 || strcmp(c,"\n")==0)
		{
			continue;
		}
		if (feof(fp)){
			printf("\nReached end of file 2");
			memset(s,0,sizeof(s));
			strcat(ret,"\x3");
			strcat(ret,"\x4");
			fclose(fp);	//close file pointers
		//printf("\nBUFFER: %s\n: ", ret);
			printf("\nWrote successfully\n");
		 	return ret;
	 }
	 	strcat(s,c);
	 	//printf("\nstring: %s\n",s);	
		amount--;
	}
 	//printf("\nAmount String: %s",s);	
	int act_amount = 0;
	if (hex_ascii_switch == 0)
	{
		 act_amount = hex_convert(s);
	}
	else 
	{
		  act_amount = ascii_convert(s);
	}

    //printf("\nActual Amount: %d\n", act_amount);
    //printf("\n 0%d ", act_amount);	
    sprintf(append,"%d",type); // put the int into a string
    strcat(ret, append);
    //strcat(ret, "-");
    sprintf(append,"%d",act_amount); // put the int into a string
    strcat(ret, append);
    strcat(ret, ",");

	memset(s,0,sizeof(s));	

	int char_counter = 0;
	int value = 0;
	int curr = 0;
	if(act_amount == 0)
	{
		strcat(ret, "\x3");
	}
  while (act_amount > 0)
  {
  	if (ascii_reset == 0)
  	{
  		//strcpy(c,d);
  	//	printf("\nDoing ascii value reset -- wrong prediciton\n");
  //			printf("\n before[0]: %s\n", b);
  	//	printf("current[0]: %s\n", c);	
  		//strcat(s,b);
  		//strcat(s,c);
  		ascii_reset = 1;
  	}
  	else
  	{
  		c[0] = fgetc(fp);
  	}

		if (strcmp(c, " ") == 0 || strcmp(c,"\r")==0 || strcmp(c,"\n")==0) //?FIX THIS NEWLINE
		{
			continue;
		}

		if (feof(fp))
		{
	 		value = ascii_convert(s);
    	    //printf("%d", value);
			sprintf(append,"%d",value); // put the int into a string
    		strcat(ret, append);
    		strcat(ret,"\x3"); // end delimeter for result
			strcat(ret,"\x4"); // end delimeter for all output
	 		act_amount--;
	  	    memset(s,0,sizeof(s));
			printf("\nReached end of file 3");
			fclose(fp);	//close file pointers
			//printf("\nBUFFER:\n %s\n: ", ret);
			printf("\nWrote successfully\n");
	 		return ret;
	 }

	 char_counter++;
//	 printf("\n---%c",c[0]);
	 strcat(s,c);
	 curr++;


   ////printf("\nChars: %d", char_counter);

   //hex check
  if(hex_ascii_switch==0)
  {
	 if(char_counter == num_counter) // when have (types 0's) num characters
	 {
	    //printf("\nValue: %s\n",s);	
		value = hex_convert(s);
	 	//printf("%d,", value);
  		sprintf(append,"%d",value); // put the int into a string
    	strcat(ret, append);
	 	char_counter = 0;   // reset counter
	 	act_amount--;        // decrese number amount
	 	if(act_amount==0)
	 	{
	 		strcat(ret,"\x3");
	 	}
	 	else
	 	{
	 		strcat(ret, ",");

	 	}
	 	memset(s,0,sizeof(s));	//resets string
	 	//printf("\ndecrease amount: %d\n", act_amount);
	 }
	}
	else
	{
	 if(c[0] == 'c' ) //hOW ENTER 
	 {
	 	printf("\nGot number: %s", s);
	 	value = ascii_convert(s);
	 	  printf("\nConverted: %d", value);
    	//printf("%d,", value);
      sprintf(append,"%d",value); // put the int into a string
    	strcat(ret, append);
		strcat(ret, ",");

	 	act_amount--;
	  memset(s,0,sizeof(s));	//resets string
	 	printf("\nAmount: %d", act_amount);
	 }
	 if (c[0] == '0'  && s[strlen(s)-2] != '3')
	 {
	 	//printf("\nPrints ONCEEEE: %c\n",  s[strlen(s)-2]);

	 	strcpy(b,c);//copy whats before
	 	c[0] =fgetc(fp); // get next character and check if is continu
	 	//printf("\nReading: %s\n",c);
	 	ascii_reset = 0;
		if (strcmp(c,"\r")==0 || strcmp(c,"\n")==0)
		{
				 //printf("\nJumping Line\n");

		  c[0] = fgetc(fp);
		  c[0] = fgetc(fp);
			//printf("\nSkip to reading: %s\n",c );
		}
		if (strcmp(c," ")==0)
		{
		  c[0] = fgetc(fp);
			//printf("\nSkip to reading: %s\n",c );
		}
    //printf("Needs reset: %s", c);
	 	if (strcmp(c,"1")==0 || strcmp(c,"0")==0)//if is end of ASCII, translate
	 	{
	 	value = ascii_convert(s);
    	//printf("%d", value);
    	sprintf(append,"%d",value); // put the int into a string
    	strcat(ret, append);
		strcat(ret, "\x3");
	 	act_amount--;
	  	memset(s,0,sizeof(s));	
	  	//printf("\nEnd of ASCII\n");
	 	}
	
	 }
	}
  }
  type_counter = 2;
 }
}
 char* int2bin(int n)
 {		//source https://www.quora.com/Is-there-a-function-in-C-that-converts-an-integer-into-bits
        // determine the number of bits needed ("sizeof" returns bytes)
        int nbits = sizeof(n) * 8;
        char *s = malloc(nbits+1);  // +1 for '\0' terminator
        s[nbits] = '\0';
        // forcing evaluation as an unsigned value prevents complications
        // with negative numbers at the left-most bit
        unsigned int u = *(unsigned int*)&n;
        int i;
        unsigned int mask = 1 << (nbits-1); // fill in values right-to-left
        for (i = 0; i < nbits; i++, mask >>= 1)
            s[i] = ((u & mask) != 0) + '0';
        return s;
 }

char* bin2hex(char* bin)
{
//	printf("Starting bin: %s\n",bin);
	static char hex[MAX_STRING]="";
	char append[MAX_STRING] = "";
	char c[2] = "\0";	
	int chunk = 4;
	int skip_4 = 4;
	int i = 0;
 	for (; i <strlen(bin)+1; i++)
	{
		if (chunk == 0)
		{
			//printf("Append: %s\n", append);
			if(skip_4 > 0)
			{
				skip_4--;
				chunk = 4;
				memset(append,0,sizeof(append));	
				memset(c,0,sizeof(c));	
			}
			if (strcmp(append,"0000")==0)
			{
				char* key = "0";
				strcat(hex,key);
			}
			if (strcmp(append,"0001")==0)
			{
				char* key = "1";
				strcat(hex,key);
			}
			if (strcmp(append,"0010")==0)
			{
				char* key = "2";
				strcat(hex,key);
			}
			if (strcmp(append,"0011")==0)
			{
				char* key = "3";
				strcat(hex,key);
			}
			if (strcmp(append,"0100")==0)
			{
				char* key = "4";
				strcat(hex,key);
			}
			if (strcmp(append,"0101")==0)
			{
				char* key = "5";
				strcat(hex,key);
			}
			if (strcmp(append,"0110")==0)
			{
				char* key = "6";
				strcat(hex,key);
			}
			if (strcmp(append,"0111")==0)
			{
				char* key = "7";
				strcat(hex,key);
			}
			if (strcmp(append,"1000")==0)
			{
				char* key = "8";
				strcat(hex,key);
			}
			if (strcmp(append,"1001")==0)
			{
				char* key = "9";
				strcat(hex,key);
			}
			if (strcmp(append,"1010")==0)
			{
				char* key = "a";
				strcat(hex,key);
			}
			if (strcmp(append,"1011")==0)
			{
				char* key = "b";
				strcat(hex,key);
			}
			if (strcmp(append,"1100")==0)
			{
				char* key = "c";
				strcat(hex,key);
			}
			if (strcmp(append,"1101")==0)
			{
				char* key = "d";
				strcat(hex,key);
			}
			if (strcmp(append,"1110")==0)
			{
				char* key = "e";
				strcat(hex,key);
			}
			if (strcmp(append,"1111")==0)
			{
				char* key = "f";
				strcat(hex,key);
			}
			memset(append,0,sizeof(append));	
			memset(c,0,sizeof(c));	
			chunk = 4;
		}
		c[0] = bin[i];
		strcat(append,c);
		chunk--;
	}
	return hex;
}

char* ToTypeZero(char* set)
{
	//printf("	TypeZero!: %s\n\n", set);
	int base = 2;
	static char sub[MAX_STRING]="";
	char append[MAX_STRING] = "";
	char c[2] = "\0";
	int i = 1;
	c[0]=set[i];
	if(strcmp(c,"0")==0)
	{
		//printf("	Is empty");
		strcpy(sub,"0000");
		memset(append,0,sizeof(append));	
		memset(c,0,sizeof(c));	
		return sub;
	}
	while(1)
	{
		if (set[i] == '\x3')
		{
			//printf("Num input: %s\n", append);
			char* hex = bin2hex(int2bin(atoi(append)));
			//printf("My hex--: %s\n\n", hex);
			strcat(sub, hex);
			memset(hex,0,sizeof(hex));	
			memset(append,0,sizeof(append));	
			memset(c,0,sizeof(c));	
			break;
		}
		if (set[i] == ',')
		{
			//printf("Num input: %s\n", append);
			char* hex = bin2hex(int2bin(atoi(append)));
			//printf("My hex--: %s\n", hex);
			strcat(sub, hex);
			memset(hex,0,sizeof(hex));	
			memset(append,0,sizeof(append));	
			memset(c,0,sizeof(c));	
			i++;
			continue;
		}	
		c[0] = set[i];
		strcat(append,c);
		i++;
	}
	return sub;
}

char* num2ascii(char* num)
{
	//printf("Num input: %s\n", num);
	static char ascii[MAX_STRING]="";
	char c[2] = "\0";	
	int i = 0;
	for(; i <strlen(num);i++)
	{
		//printf("%c\n",num[i]);
		c[0] = num[i];
		if (strcmp(c, "0")==0)
		{
			strcat(ascii,"30");
		}
		if (strcmp(c, "1")==0)
		{
			strcat(ascii,"31");
		}
		if (strcmp(c, "2")==0)
		{
			strcat(ascii,"32");
		}
		if (strcmp(c, "3")==0)
		{
			strcat(ascii,"33");
		}
		if (strcmp(c, "4")==0)
		{
			strcat(ascii,"34");
		}
		if (strcmp(c, "5")==0)
		{
			strcat(ascii,"35");
		}
		if (strcmp(c, "6")==0)
		{
			strcat(ascii,"36");
		}
		if (strcmp(c, "7")==0)
		{
			strcat(ascii,"37");
		}
		if (strcmp(c, "8")==0)
		{
			strcat(ascii,"38");
		}
		if (strcmp(c, "9")==0)
		{
			strcat(ascii,"39");
		}
		//memset(c,0,sizeof(c));	
	}
	return ascii;
}
char* SetTyping(char* first)
{
	//printf("	Set Typing Arg: %s\n\n", first);
	static char type[MAX_STRING]="";
	char append[MAX_STRING] = "";
	char c[2] = "\0";
	strcat(type, "01");
	for (int i = 1; i<strlen(first); i++)	
	{
		c[0] = first[i];
		//printf("	curr:%c   %s\n",c[0], type);
		if (strcmp(c, "0")==0)
		{
			strcat(append,"30");
		}
		if (strcmp(c, "1")==0)
		{
			strcat(append,"31");
		}
		if (strcmp(c, "2")==0)
		{
			strcat(append,"32");
		}
		if (strcmp(c, "3")==0)
		{
			strcat(append,"33");
		}
		if (strcmp(c, "4")==0)
		{
			strcat(append,"34");
		}
		if (strcmp(c, "5")==0)
		{
			strcat(append,"35");
		}
		if (strcmp(c, "6")==0)
		{
			strcat(append,"36");
		}
		if (strcmp(c, "7")==0)
		{
			strcat(append,"37");
		}
		if (strcmp(c, "8")==0)
		{
			strcat(append,"38");
		}
		if (strcmp(c, "9")==0)
		{
			strcat(append,"39");
		}
	}
	if (strlen(append) == 2)
	{
		//printf("	Only 1 digit: %s \n", append);
		c[0] = first[1];
		if (strcmp(c, "0")==0)
		{
			strcat(type,"303030");
		}
		if (strcmp(c, "1")==0)
		{
			strcat(type,"303031");
		}
		if (strcmp(c, "2")==0)
		{
			strcat(type,"303032");
		}
		if (strcmp(c, "3")==0)
		{
			strcat(type,"303033");
		}
		if (strcmp(c, "4")==0)
		{
			strcat(type,"303034");
		}
		if (strcmp(c, "5")==0)
		{
			strcat(type,"303035");
		}
		if (strcmp(c, "6")==0)
		{
			strcat(type,"303036");
		}
		if (strcmp(c, "7")==0)
		{
			strcat(type,"303037");
		}
		if (strcmp(c, "8")==0)
		{
			strcat(type,"303038");
		}
		if (strcmp(c, "9")==0)
		{
			strcat(type,"303039");
		}
	}
	if (strlen(append) == 4)
	{
		//printf("	Only 2 digit: %s \n", append);
		c[0] = first[1];
		if (strcmp(c, "0")==0)
		{
			strcat(type,"3030");
		}
		if (strcmp(c, "1")==0)
		{
			strcat(type,"3031");
		}
		if (strcmp(c, "2")==0)
		{
			strcat(type,"3032");
		}
		if (strcmp(c, "3")==0)
		{
			strcat(type,"3033");
		}
		if (strcmp(c, "4")==0)
		{
			strcat(type,"3034");
		}
		if (strcmp(c, "5")==0)
		{
			strcat(type,"3035");
		}
		if (strcmp(c, "6")==0)
		{
			strcat(type,"3036");
		}
		if (strcmp(c, "7")==0)
		{
			strcat(type,"3037");
		}
		if (strcmp(c, "8")==0)
		{
			strcat(type,"3038");
		}
		if (strcmp(c, "9")==0)
		{
			strcat(type,"3039");
		}
		c[0] = first[3];
		if (strcmp(c, "0")==0)
		{
			strcat(type,"30");
		}
		if (strcmp(c, "1")==0)
		{
			strcat(type,"31");
		}
		if (strcmp(c, "2")==0)
		{
			strcat(type,"32");
		}
		if (strcmp(c, "3")==0)
		{
			strcat(type,"33");
		}
		if (strcmp(c, "4")==0)
		{
			strcat(type,"34");
		}
		if (strcmp(c, "5")==0)
		{
			strcat(type,"35");
		}
		if (strcmp(c, "6")==0)
		{
			strcat(type,"36");
		}
		if (strcmp(c, "7")==0)
		{
			strcat(type,"37");
		}
		if (strcmp(c, "8")==0)
		{
			strcat(type,"38");
		}
		if (strcmp(c, "9")==0)
		{
			strcat(type,"39");
		}	
	}
	if(strlen(append)==6)
	{
		//already has formated
	}
	if(strlen(append) > 6)
	{
		//is incorrect, do format error
	}
	return type;
}

char* ToTypeOne(char* set)
{
	//printf("TypeOne Arg: %s\n\n", set);
	static char sub[MAX_STRING]= "";
	char append[MAX_STRING] = "";
	char c[2] = "\0";
	int i = 0;
	int get_type =  0;
	while(1)
	{
		if (set[i] == '\x3')
		{
			char* ascii = num2ascii(append);
			//printf("My ascii--: %s\n\n", hex);
			strcat(sub, ascii);
			memset(ascii,0,sizeof(ascii));	
			memset(append,0,sizeof(append));	
			memset(c,0,sizeof(c));	
			break;
		}
		if (set[i] == ',')
		{
			if (get_type == 0)
			{
				char* new_type = SetTyping(append);
				strcat(sub,new_type);
				//if(strcmp(new_type,"303030")==0){break;}
				memset(new_type,0,sizeof(new_type));	
				memset(append,0,sizeof(append));	
				memset(c,0,sizeof(c));	
				get_type=1;
				i++;
				continue;
			}
			char* ascii  = num2ascii(append);
			//printf("My ascii--: %s\n", hex);
			strcat(sub, ascii);
			strcat(sub, "2c");
			memset(ascii,0,sizeof(ascii));	
			memset(append,0,sizeof(append));	
			memset(c,0,sizeof(c));	
			i++;
			continue;
		}	
		c[0] = set[i];
		strcat(append,c);
		i++;
	}
	return sub;
}

char* change_type(char* values, char* tf)
{
	printf("\nValues Argument: %s\n\n", values);
	static char result[MAX_STRING]="";
	strcat(result, "\x2");//starting delimeter
	char append[MAX_STRING] = "";
	char c[2] = "\0";
	if (strcmp(tf,"3")==0)
	{	
		int i = 0; // index of string
		int cross_sec = i; 
		while(1)
		{
			if(values[i] == '\x2')
			{
				//printf("Start of value: %c\n", values[i+1]);
				i++;
				cross_sec = i;
				while(1)
				{
					if (values[cross_sec] == '\x3')
					{
						c[0] = values[cross_sec];
						strcat(append, c);
						if (append[0] == '0')
						{
							//printf("Doing type 0->1 conversion\n");
							char* done = ToTypeOne(append);
							printf("Type 0->1 result: %s\n", done);
							memset(done,0,sizeof(done));	
						}
						if (append[0] == '1')
						{
							//printf("Doing type 1->0 conversion\n");
							char* done = ToTypeZero(append);
							printf("Type 1->0 result: %s\n", done);
							memset(done,0,sizeof(done));	

						}
						//printf("End of value: %c\n", values[cross_sec-1]);
						i = cross_sec;
						break;
					}
					c[0] = values[cross_sec];
					//printf("%c\n", values[cross_sec]);
					strcat(append, c);
					cross_sec++;
				}
			}
			//printf("End of value: %c\n", values[i-1]);
			if(values[i]=='\x4')
			{
				printf("End of arg.\n");
				break;
			}
			memset(append,0,sizeof(append));	
			memset(c,0,sizeof(c));	
			i++;
		}
	}

	if (strcmp(tf,"2")==0)
	{	
		int i = 0; // index of string
		int cross_sec = i; 
		while(1)
		{
			if(values[i] == '\x2')
			{
				//printf("Start of value: %c\n", values[i+1]);
				i++;
				cross_sec = i;
				while(1)
				{
					if (values[cross_sec] == '\x3')
					{
						c[0] = values[cross_sec];
						strcat(append, c);
						if (append[0] == '0')
						{
							//printf("Doing type 0->1 conversion\n");
							char* done = ToTypeZero(append);
							printf("Type 0->0 result: %s\n", done);
							memset(done,0,sizeof(done));	
						}
						if (append[0] == '1')
						{
							//printf("	Doing type 1->0 conversion: %s\n", append);
							char* done = ToTypeZero(append);
							printf("Type 1->0 result: %s\n", done);
							memset(done,0,sizeof(done));	

						}
						//printf("End of value: %c\n", values[cross_sec-1]);
						i = cross_sec;
						break;
					}
					c[0] = values[cross_sec];
					//printf("%c\n", values[cross_sec]);
					strcat(append, c);
					cross_sec++;
				}
			}
			//printf("End of value: %c\n", values[i-1]);
			if(values[i]=='\x4')
			{
				printf("End of arg.\n");
				break;
			}
			memset(append,0,sizeof(append));	
			memset(c,0,sizeof(c));	
			i++;
		}
	}
	if (strcmp(tf,"1")==0)
	{	
		int i = 0; // index of string
		int cross_sec = i; 
		while(1)
		{
			if(values[i] == '\x2')
			{
				//printf("Start of value: %c\n", values[i+1]);
				i++;
				cross_sec = i;
				while(1)
				{
					if (values[cross_sec] == '\x3')
					{
						c[0] = values[cross_sec];
						strcat(append, c);
						if (append[0] == '0')
						{
							//printf("Doing type 0->1 conversion: %s\n", append);
							char* done = ToTypeOne(append);
							printf("Type 0->1 result: %s\n", done);
							memset(done,0,sizeof(done));	
						}
						if (append[0] == '1')
						{
							//printf("Doing type 1->0 conversion\n");
							char* done = ToTypeOne(append);
							printf("Type 1->1 result: %s\n", done);
							memset(done,0,sizeof(done));	

						}
						//printf("End of value: %c\n", values[cross_sec-1]);
						i = cross_sec;
						break;
					}
					c[0] = values[cross_sec];
					//printf("%c\n", values[cross_sec]);
					strcat(append, c);
					cross_sec++;
				}
			}
			//printf("End of value: %c\n", values[i-1]);
			if(values[i]=='\x4')
			{
				printf("End of arg.\n");
				break;
			}
			memset(append,0,sizeof(append));	
			memset(c,0,sizeof(c));	
			i++;
		}
	}
	if (strcmp(tf,"0")==0)
	{	
		int i = 0; // index of string
		int cross_sec = i; 
		while(1)
		{
			if(values[i] == '\x2')
			{
				//printf("Start of value: %c\n", values[i+1]);
				i++;
				cross_sec = i;
				while(1)
				{
					if (values[cross_sec] == '\x3')
					{
						c[0] = values[cross_sec];
						strcat(append, c);
						if (append[0] == '0')
						{
							//printf("Doing type 0->1 conversion\n");
							char* done = ToTypeZero(append);
							printf("Type 0->0 result: %s\n", done);
							memset(done,0,sizeof(done));	
						}
						if (append[0] == '1')
						{
							//printf("Doing type 1->0 conversion\n");
							char* done = ToTypeOne(append);
							printf("Type 1->1 result: %s\n", done);
							memset(done,0,sizeof(done));	

						}
						//printf("End of value: %c\n", values[cross_sec-1]);
						i = cross_sec;
						break;
					}
					c[0] = values[cross_sec];
					//printf("%c\n", values[cross_sec]);
					strcat(append, c);
					cross_sec++;
				}
			}
			//printf("End of value: %c\n", values[i-1]);
			if(values[i]=='\x4')
			{
				printf("End of arg.\n");
				break;
			}
			memset(append,0,sizeof(append));	
			memset(c,0,sizeof(c));	
			i++;
		}
	}
	return result;
}

int check_file(char* input_file)
{
	if( access( input_file, F_OK ) != -1 ) 
	{
    	printf("// file exists\n");
    	return 0;
	} 
	else {
    	printf("// file doesn't exist");
    	return 1;
	}
}