#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_NR_TOKENS 32
#define MAX_TOKEN_LEN 64
#define MAX_COMMAND  256

static int parse_command(char* command, int *nr_tokens, char* tokens[]){
int n = 0;
int scantoken = 0;
int tokensize = 0;
int tokenscount = 0;
int  k = 0;
while(1){
if(command[n] != ' '){
while(command[scantoken] != ' '){
if(command[scantoken] == '\0') break;
tokensize++;
scantoken++;
}
char* token = (char*)malloc (sizeof(char)*(tokensize+1));
while(command[n] != ' '){
if(command[n] == '\0') break;
token[k] = command[n];
k++;
n++; }
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

int main(int argc, const char* argv[])
{
char line[MAX_COMMAND] = { '\0' };
FILE* input = stdin;

if(argc == 2){
input = fopen(argv[1], "r");
if(!input){
fprintf(stderr, "No input %s\n", argv[1]);
return -EINVAL;

}

}
while(fgets(line, sizeof(line), input)){
char* tokens[MAX_NR_TOKENS] = { NULL };
int nr_tokens = 0;

parse_command(line, &nr_tokens, tokens);

fprintf(stderr, "nr_tokens = %d\n", nr_tokens);
int i= 0;
for( i = 0; i < nr_tokens; i++){
fprintf(stderr, "tokens[%d] = %s\n", i, tokens[i]);
}
printf("\n");
}
if(input != stdin) fclose(input);

return 0;
}



