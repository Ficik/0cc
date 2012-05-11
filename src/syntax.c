#include <stdio.h>
#include <stdlib.h>

#define MAXIMUM_WORD_SIZE 32

#define SYNTAX_UNKNOWN 0
#define SYNTAX_TEXT 1 
#define SYNTAX_NUMBER 2
#define SYNTAX_HEXNUM 3
#define SYNTAX_STRING 4


int is_digit(char ch){
	return ch >= 0x30 && ch <= 0x39;
}

int is_letter(char ch){
  return (ch >= 0x41 && ch <= 0x5A) || (ch >= 0x97 && ch <= 0x7a);
}

/**
 * Parse content of file into syntax tree containing 
 * basic syntax elements (Text, Number, Hexnumber and String)
 */
int* parse(char* filename){
	int  ch_counter = 0;
	FILE *fp;
	char ch;
	char *word;
	int wp = 0;
	int type = SYNTAX_UNKNOWN;
	fp = fopen(filename, "r");
	goto new_word_reset;
	while(1){
		ch = fgetc(fp);
		ch_counter++;
		if (ch == EOF)
			break;
		
		if (ch == ' ' || ch == '\n' || ch == '\t'){
			if (type == SYNTAX_STRING)
				word[wp++] = ' ';
			else if (type != SYNTAX_UNKNOWN)
				goto save_word;
			else
				continue;
		}

		word[wp++] = ch;
		
		if (type == SYNTAX_UNKNOWN){	
			if (ch == '"')
				type = SYNTAX_STRING;
			else if (is_digit(ch)) /* [0-9] */
				type = SYNTAX_NUMBER;
			else if (is_letter(ch) || ch == '_') /* [A-Za-z_] */
				type = SYNTAX_TEXT;
			else {
				printf("Error on char %d\n",ch_counter);
				return NULL;
			}
			continue;
		}

		/* Valid number check */
		if (type == SYNTAX_NUMBER){
			if (ch == 'x'){
				if (word[0] == '0'){
					type = SYNTAX_HEXNUM;
					continue;
				}
			}
			if (ch <= 0x30 || ch >= 0x39){
					printf("Error (NaN) on char %d\n", ch_counter);
					return NULL;
			}
			continue;
		}

		if (type == SYNTAX_HEXNUM){
			if (is_digit(ch) || (ch >= 0x41 && ch <=0x46) || (ch >= 0x61 && ch <=0x66)) /* [0-9a-fA-F] */
				continue;
			printf("Error (NaN) on char %d\n", ch_counter);
			return NULL;
		}

		if (type == SYNTAX_TEXT){
			if (!is_digit(ch) && !is_letter(ch) && ch != '_'){
				printf("Error (wrong name) on char %d\n", ch_counter);
				return NULL;
			}
			continue;
		}

		if (type == SYNTAX_STRING){
			if (ch == '"' && word[wp-1] != '\\')
				goto save_word;
			continue;
		}

		
		if (0) {
			save_word:
				word[wp] = 0;
				/* TODO: save word to tree */
			new_word_reset:
				wp = 0;
				word = malloc(sizeof(char)*MAXIMUM_WORD_SIZE);
				type = SYNTAX_UNKNOWN;
				continue;
		}

		
	}
	
}
