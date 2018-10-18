
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

//1.) do writing! with perfect case DONE!
//2.) do file checking (ex. check if ascii is greater than  2147483647 (check atoi of value!))
		// ^^^ IS VERY HARD DO LATER!!!
//3.) then do server client fixes new delimeters! (DONE!)
//4.) fix file non existant socketing....

//CHECK THOSE MULTIPLE CASES!!!

int hex_convert(char* s)
{
    //printf("\nValue Input: %s\n", s);
	char amt[MAX_STRING] ="";
	if(strlen(s) < 2){return -1;}
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
			return -1;
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
   //printf("\nValue Input:%s\n", s);
	char amt[MAX_STRING] ="";
  //printf("\n%d", strlen(s));
	for (int i = 1; i < strlen(s); i=i+2)
	{
		////printf("\n%c", s[i]);
		if (s[i-1]!='3'){return -1;}
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
			printf("\nInvalid ascii character: %c", s[i]);
			return -1;
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
		printf("\n Unknown Type \n");
		return -1;
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


char* get_values(char* contents) {
    //printf("\nvalues args: %s\n",contents );
    printf("\n");
    static char values[MAX_STRING]="";
    char num[MAX_STRING] = "";
	char append[MAX_STRING] = "";

	char curr[2] = "\0";
	char prev[2] = "\0";

	int type;
	int type_digits = 2;
	int num_length;
	int amt_length;
	int hex_ascii_switch;
	int ascii_reset = 1;
	int i = 0;
	while(1)
	{	
		type_digits=2;
		//printf("current values: %s\n", values);

		while(type_digits > 0)
		{
			if(ascii_reset==0)
			{
				ascii_reset = 1;
			//	printf("prev: %s\n",prev);
				strcat(num,prev);
				type_digits--;
			}
			else
			{
				if (i == strlen(contents))
				{
					strcat(values,"\x3");
					strcat(values,"\x4");
					memset(num,0,sizeof(num));
					memset(append,0,sizeof(num));
					memset(curr,0,sizeof(curr));
					memset(prev,0,sizeof(prev));
					return values;
				}
				prev[0] = curr[0];
				curr[0] = contents[i];
				//printf("current: %s\n",curr);
				if (strcmp(curr, " ") == 0 ||  strcmp(curr,"\r")==0 || strcmp(curr,"\n")==0)
				{
					i++;
					continue;
				}
				strcat(num,curr);
			//	printf("num: %s\n",num);
				type_digits--;
				i++;
			}
		}

		type = type_convert(num);
	//	printf("Is Type: %d\n\n", type);
		if (type == 0)
		{
			amt_length = 2; // # of bytes in amount
			num_length = 4;// # of chars per num
			hex_ascii_switch = 0;
		}
		if (type == 1)
		{
			amt_length = 6; // # of bytes in amount
			hex_ascii_switch = 1;
		}
  		memset(num,0,sizeof(num));	
  		while (amt_length>0)
  		{
  			if (i == strlen(contents))
			{
				strcat(values,"\x3");
				strcat(values,"\x4");
				memset(num,0,sizeof(num));
				memset(append,0,sizeof(num));
				memset(curr,0,sizeof(curr));
				memset(prev,0,sizeof(prev));
				return values;
			}
			prev[0] = curr[0];
  			curr[0] = contents[i];
  			if (strcmp(curr, " ") == 0 ||  strcmp(curr,"\r")==0 || strcmp(curr,"\n")==0)
			{
				i++;
				continue;
			}
			
			strcat(num,curr);	
			amt_length--;	
			i++;
			//printf("current: %d\n",amt_length);
  		}
		int amt;
		if (hex_ascii_switch == 0)
		{

		 	amt = hex_convert(num);
		 	//printf("Converted hex amt to: %s %d\n",num, amt);
		}
		else 
		{
		  	amt = ascii_convert(num);
		  	//printf("Converted ascii amt to: %s %d\n",num, amt);
		}
		strcat(values,"\x2");//start of value string	
		sprintf(append,"%d",type); // put the int into a string
    	strcat(values, append);
    	sprintf(append,"%d",amt); // put the int into a string
    	strcat(values, append);	
    	strcat(values, ",");
		memset(num,0,sizeof(num));	
		memset(append,0,sizeof(append));	

		int char_counter = 0;
		int val;
		if(amt == 0)
		{
			strcat(values, "\x3");
		}
		while(amt > 0)
		{
			//printf("Top Amount: ---- %d\n", amt);
			if(ascii_reset==0)
			{
				ascii_reset=1;
			}
			else
			{
				prev[0] = curr[0];
				curr[0] = contents[i];
			}
			
			if (i == strlen(contents))
			{

				val = ascii_convert(num);
				sprintf(append,"%d",val); 
				strcat(values, append);
				strcat(values,"\x3");
				strcat(values,"\x4");
				memset(num,0,sizeof(num));
				memset(append,0,sizeof(num));
				memset(curr,0,sizeof(curr));
				memset(prev,0,sizeof(prev));
				return values;
			}
			prev[0] = curr[0];
			curr[0] = contents[i];
			if (strcmp(curr, " ") == 0 ||  strcmp(curr,"\r")==0 || strcmp(curr,"\n")==0)
			{
				i++;
				continue;
			}
			char_counter++;
			strcat(num,curr);
			i++;
			if(hex_ascii_switch==0)
			{
				if (char_counter==num_length)
				{
					val = hex_convert(num);
					sprintf(append,"%d",val);
					strcat(values,append);
					char_counter = 0;
					amt--;
					if(amt==0)
					{
						strcat(values,"\x3");
					}
					else
					{
						strcat(values,",");
					}
					memset(append,0,sizeof(append));	//resets string
				 	memset(num,0,sizeof(num));	//resets string
				}				
			}
			else
			{
				//printf("ascii curr: %s %s\n",curr,num);
				//printf("previous: %c %c\n", num[strlen(num)-1], num[strlen(num)-2]);//I wrote current to NUM
				if (num[strlen(num)-1] == 'c')
				{
					num[strlen(num)-2]='\0';
				//	printf("comma DOING WITH NUM: %s\n",num);
					val = ascii_convert(num);
				//	printf("Comma - Got value:%d\n",val);
					sprintf(append,"%d",val);
					strcat(values,append);
					strcat(values,",");
					amt--;
					memset(append,0,sizeof(append));	//resets string
		    		memset(num,0,sizeof(num));	//resets string
		    		continue;
				}
				if(num[strlen(num)-2]!='3' && curr[0]=='0' ) 
				{	
				//	printf("	Suspicious:%s || %c %c %c\n",num, contents[i-1],contents[i],contents[i+1]);
					if (contents[i]=='0' || contents[i] =='1')
					{
					//	    printf("	end of num: %s\n",num);
							num[strlen(num)-1] ='\0';
							ascii_reset=0;
							val = ascii_convert(num);
						//	printf("reset DOING WITH NUM: %s\n",num);
							sprintf(append,"%d", val);
							strcat(values,append);
							strcat(values,"\x3");
							amt--;
							memset(num,0,sizeof(num));
							memset(append,0,sizeof(append));
							break;
					}
				//	printf("	Is okay\n");
				} 

			}
		}
	}
	return values;
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
	//printf("\nValues Argument: %s\n\n", values);
	static char result[MAX_STRING]="";
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
							strcat(result, "\x2");//starting delimeter
							char* done = ToTypeOne(append);
							//printf("Type 0->1 result: %s\n", done);
							strcat(result, done);
							strcat(result, "\x3");
							memset(done,0,sizeof(done));	
						}
						if (append[0] == '1')
						{
							//printf("Doing type 1->0 conversion\n");
							strcat(result, "\x2");//starting delimeter
							char* done = ToTypeZero(append);
							//printf("Type 1->0 result: %s\n", done);
							strcat(result, done);
							strcat(result, "\x3");
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
				//printf("End of arg.\n");
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
							strcat(result, "\x2");//starting delimeter
							char* done = ToTypeZero(append);
							//printf("Type 0->0 result: %s\n", done);
							strcat(result, done);
							strcat(result, "\x3");
							memset(done,0,sizeof(done));	
						}
						if (append[0] == '1')
						{
							//printf("	Doing type 1->0 conversion: %s\n", append);
							strcat(result, "\x2");//starting delimeter
							char* done = ToTypeZero(append);
							//printf("Type 1->0 result: %s\n", done);
							strcat(result, done);
							strcat(result, "\x3");							
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
				//printf("End of arg.\n");
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
							strcat(result, "\x2");//starting delimeter
							char* done = ToTypeOne(append);
							//printf("Type 0->1 result: %s\n", done);
							strcat(result, done);
							strcat(result, "\x3");							
							memset(done,0,sizeof(done));	
						}
						if (append[0] == '1')
						{
							//printf("Doing type 1->0 conversion\n");
							strcat(result, "\x2");//starting delimeter
							char* done = ToTypeOne(append);
							//printf("Type 1->1 result: %s\n", done);
							strcat(result, done);
							strcat(result, "\x3");
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
				//printf("End of arg.\n");
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
							strcat(result, "\x2");//starting delimeter
							char* done = ToTypeZero(append);
							//printf("Type 0->0 result: %s\n", done);
							strcat(result, done);
							strcat(result, "\x3");							
							memset(done,0,sizeof(done));	
						}
						if (append[0] == '1')
						{
							//printf("Doing type 1->0 conversion\n");
							strcat(result, "\x2");//starting delimeter	
							char* done = ToTypeOne(append);
							//printf("Type 1->1 result: %s\n", done);
							strcat(result, done);
							strcat(result, "\x3");							
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
				//printf("End of arg.\n");
				break;
			}
			memset(append,0,sizeof(append));	
			memset(c,0,sizeof(c));	
			i++;
		}
	}
	strcat(result, "\x4");
	return result;
}

int do_write(char* trans, char* target)
{
	char c[2] = "\0";
	//printf("Doing write of: %s\n", trans);
	int i = 0;
	FILE* wp;
	wp = fopen(target, "w+");
	while(1)
	{
		c[0] = trans[i];
		i++;
		if(strcmp(c,"\x2")==0)
		{
			//printf("Start of value\n");
			continue;
		}
		if(strcmp(c,"\x3")==0)
		{
			//printf("End of value\n");
			continue;
		}
		if(strcmp(c,"\x4")==0)
		{
			//printf("\nWrote.\n");
			break;
		}
		fputc(c[0], wp);	
	}
	fclose(wp);
	return 0;
}



int check_file(char* contents) {
    //printf("\nvalues args: %s\n",contents );
    printf("\n");
    char num[MAX_STRING] = "";

	char curr[2] = "\0";
	char prev[2] = "\0";
	
	int val;
	int type;
	int type_digits = 2;
	int num_length;
	int amt_length;
	int hex_ascii_switch;
	int ascii_reset = 1;
	int i = 0;
	if (strlen(contents) < 4)//based off min of type 0 and 1
	{
		//printf("Contents too short\n");
		return -1;
	}
	if(contents[0]!='0')//incorrect starting type
	{
		//printf("Incorrect starting type\n");
		return -1;
	}	
	while(1)
	{	
		type_digits=2;
		while(type_digits > 0)
		{
			if(ascii_reset==0)
			{
				ascii_reset = 1;
				strcat(num,prev);
				type_digits--;
			}
			else
			{
				if (i == strlen(contents)) // should be only successful
				{
					memset(num,0,sizeof(num));
					memset(curr,0,sizeof(curr));
					memset(prev,0,sizeof(prev));
					return 0;
				}
				prev[0] = curr[0];
				curr[0] = contents[i];
				if (strcmp(curr, " ") == 0 ||  strcmp(curr,"\r")==0 || strcmp(curr,"\n")==0)
				{
					i++;
					continue;
				}
				strcat(num,curr);
				type_digits--;
				i++;
			}
		}

		type = type_convert(num);
		if(type<0)
		{
		 	return -1;
		}
		//printf("Is Type: %d\n\n", type);
		if (type == 0)
		{
			amt_length = 2; // # of bytes in amount
			num_length = 4;// # of chars per num
			hex_ascii_switch = 0;
		}
		if (type == 1)
		{
			amt_length = 6; // # of bytes in amount
			hex_ascii_switch = 1;
		}
  		memset(num,0,sizeof(num));	
  		while (amt_length>0)
  		{
  			if (i == strlen(contents)-1)
			{
				strcat(num,prev);	
				if (hex_ascii_switch == 0)
				{
					val = hex_convert(num);
					if(val<0)
		 			{
		 				return -1;
		 			}
				}
				else
				{
					val = ascii_convert(num);
					if(val<0)
		 			{
		 				return -1;
		 			}
				}
				memset(num,0,sizeof(num));
				memset(curr,0,sizeof(curr));
				memset(prev,0,sizeof(prev));
				return 0;
			}
			prev[0] = curr[0];
  			curr[0] = contents[i];
  			if (strcmp(curr, " ") == 0 ||  strcmp(curr,"\r")==0 || strcmp(curr,"\n")==0)
			{
				i++;
				continue;
			}
			
			strcat(num,curr);	
			amt_length--;	
			i++;
  		}
		int amt;
		if (hex_ascii_switch == 0)
		{

		 	amt = hex_convert(num);
		 	if(amt<0 || i >= strlen(contents))
		 	{
		 		return -1;
		 	}
		}
		else 
		{
		  	amt = ascii_convert(num);
		  	if(amt<0 || i >= strlen(contents))
		 	{
		 		return -1;
		 	}
		}
		memset(num,0,sizeof(num));	
		int char_counter = 0;
		if(amt == 0)
		{
			//strcat(values, "\x3");
		}
		while(amt > 0)
		{
			if(ascii_reset==0)
			{
				ascii_reset=1;
			}
			else
			{
				prev[0] = curr[0];
				curr[0] = contents[i];
			}
			
			if (i == strlen(contents))
			{
				val = ascii_convert(num);
				if(val<0)
		 		{
		 			return -1;
		 		}
				memset(num,0,sizeof(num));
				memset(curr,0,sizeof(curr));
				memset(prev,0,sizeof(prev));
				return 0;
			}
			prev[0] = curr[0];
			curr[0] = contents[i];
			if (strcmp(curr, " ") == 0 ||  strcmp(curr,"\r")==0 || strcmp(curr,"\n")==0)
			{
				i++;
				continue;
			}
			char_counter++;
			strcat(num,curr);
			i++;
			if(hex_ascii_switch==0)
			{
				if (char_counter==num_length)
				{
					val = hex_convert(num);
					if(val<0)
		 			{
		 				return -1;
		 			}
					char_counter = 0;
					amt--;
					if(amt==0)
					{
					//	strcat(values,"\x3");
					}
					else
					{
					//	strcat(values,",");
					}
				 	memset(num,0,sizeof(num));	//resets string
				}				
			}
			else
			{
				if (num[strlen(num)-1] == 'c')
				{
					num[strlen(num)-2]='\0';
					val = ascii_convert(num);
				  	if(val<0)
		 			{
		 				return -1;
		 			}	
					amt--;
		    		memset(num,0,sizeof(num));	//resets string
		    		continue;
				}
				if(num[strlen(num)-2]!='3' && curr[0]=='0' ) 
				{	
					if (contents[i]=='0' || contents[i] =='1')
					{
							num[strlen(num)-1] ='\0';
							ascii_reset=0;
							val = ascii_convert(num);
							if(val<0)
		 					{
		 						return -1;
		 					}
							amt--;
							memset(num,0,sizeof(num));
							break;
					}
				} 

			}
		}
	}
	return 0;
 }