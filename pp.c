#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_NR_TOKENS 32
#define MAXMTOKEN_LEN 64

static int parse(char* command, int* nr_tokens, char* tokens[])
{
int n = 0;
int scantoken = 0;
int tokensize = 0;
int tokenscount = 0;
int k =0;
while(1){
if(command[n] != ' '){
while(command[scantoken] != ' '){
if(command[scantoken] == '\0') break;
tokensize++;
scantoken++;
}
char* token = (char*)malloc (sizeof(char*)*(tokensize+1));
while(command[n] != '\0'){
if(command[n] == '\0')break;
token[k] = command[n];
k++;
n++;
}
token[k] = '\0';
tokens[tokenscount] = token;
(*nr_tokens)++;
if(command[n] == '\0') break;
tokenscount++;
tokensize = 0;
k = 0;
}
if(command[n] == ' '){
n++;
scantoken++;
}
}
return 0;
}


int main(){

char* tokens[10];
int nr_tokens = 0;
char* command = "sdf sdf  sdf";

parse(command, &nr_tokens, char* tokens[]);

return 0;

}
