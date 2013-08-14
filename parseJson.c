#include "jsmn.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int currentPosition;
	int endPosition;
	jsmntok_t *tokens;
	int end;
}TokenIterator;

TokenIterator* createTokenIterator(jsmn_parser *parser, jsmntok_t *tokens){
	TokenIterator *iterator = malloc(sizeof (TokenIterator));
	iterator->currentPosition = -1;
	iterator->end = 0;
	iterator->endPosition = parser->toknext;
	iterator->tokens = tokens;
 return iterator;
}

char* fileToString(FILE *file){
	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	char *string = calloc(fileSize,1);
	fread(string, 1, fileSize+1, file);
 return string;
}

void getNextObject(TokenIterator *iterator){
	iterator->currentPosition++;
	while(!(iterator->currentPosition >= iterator->endPosition)){
		if(iterator->tokens[iterator->currentPosition].type == JSMN_OBJECT){
			return;
		}else{
			iterator->currentPosition++;
		}
	}
	if(iterator->currentPosition >= iterator->end){
		iterator->end = 1;
	}
}

int main(){
	FILE *data;
	data = fopen("resources/data.js", "r");
	char* jsonFile = fileToString(data);
	fclose(data);
	
	jsmn_parser parser;
	jsmntok_t tokens[32];	
	jsmn_init(&parser);
	jsmn_parse(&parser,jsonFile,tokens,32);

	TokenIterator *it = createTokenIterator(&parser, tokens);
	getNextObject(it);
	while(!it->end){
		int objectPosition = it->currentPosition;
		for(int j=tokens[objectPosition].start; j<tokens[objectPosition].end; j++){
			printf("%c",jsonFile[j]);
		}
		printf("\n");
		getNextObject(it);
	}
 return 0;
}
