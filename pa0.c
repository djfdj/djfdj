/**********************************************************************
 * Copyright (c) 2019
 *  Sang-Hoon Kim <sanghoonkim@ajou.ac.kr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTIABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_NR_TOKENS 32	/* Maximum number of tokens in a command */
#define MAX_TOKEN_LEN 64	/* Maximum length of single token */
#define MAX_COMMAND	256		/* Maximum length of command string */

/***********************************************************************
 * parse_command
 *
 * DESCRIPTION
 *	parse @command, and put each command token into @tokens[] and the number of
 *	tokes into @nr_tokens.
 *
 * A command token is defined as a string without any whitespace (i.e., *space*
 * and *tab* in this programming assignment). For exmaple,
 *   command = "  Hello world   Ajou   University!!  "
 *
 * then, nr_tokens = 4 and tokens should be
 *
 *   tokens[0] = "Hello"
 *   tokens[1] = "workd"
 *   tokens[2] = "Ajou"
 *   tokens[3] = "University!!"
 *
 * Another exmaple is;
 *   command = "  add r0   r1 r2 "
 *
 * then, nr_tokens = 4, and tokens is
 *   tokens[0] = "add"
 *   tokens[1] = "r0"
 *   tokens[2] = "r1"
 *   tokens[3] = "r2"
 *
 *
 * RETURN VALUE
 *	Return 0 after filling in @nr_tokens and @tokens[] properly
 *
 */
static int parse_command(char *command, int *nr_tokens, char *tokens[]){
	int n = 0;
	int scantoken = 0;
	int tokensize = 0;
	int tokenscount = 0;
	int  k = 0;
	while(1){
		if((command[n] != ' ') && (command[n] != '\t')){
			while((command[scantoken] != ' ') * (command[scantoken] != '\t')*(command[scantoken] != '\n')){
				tokensize++;
				scantoken++;
				}
			char* token = (char*)malloc (sizeof(char)*(tokensize+1));
			while((command[n] != ' ') * (command[n] != '\t')*(command[n] != '\n')){
				token[k] = command[n];
				k++;
				n++;
				}
			token[k] ='\0';
			tokens[tokenscount] = token;
			(*nr_tokens)++;

			tokenscount++;
			tokensize = 0;
			k = 0;
			}
		if((command[n] == ' ') || (command[n]  == '\t')  ){
			n++;
			scantoken++;
		}
		if(command[n] == '\n'){
			tokens[tokenscount] = '\0';
			break;

		}
		

	}
	return 0;
}


/***********************************************************************
 * The main function of this program. SHOULD NOT CHANGE THE CODE BELOW
 */
int main(int argc, const char *argv[])
{
	char line[MAX_COMMAND] = { '\0' };
	FILE *input = stdin;

	if (argc == 2) {
		input = fopen(argv[1], "r");
		if (!input) {
			fprintf(stderr, "No input file %s\n", argv[1]);
			return -EINVAL;
		}
	}

	while (fgets(line, sizeof(line), input)) {
		char *tokens[MAX_NR_TOKENS] = { NULL };
		int nr_tokens= 0;

		parse_command(line, &nr_tokens, tokens);

		fprintf(stderr, "nr_tokens = %d\n", nr_tokens);
		int i;
		for (i = 0; i < nr_tokens; i++) {
			fprintf(stderr, "tokens[%d] = %s\n", i, tokens[i]);
		}
		printf("\n");
	}

	if (input != stdin) fclose(input);

	return 0;
}
