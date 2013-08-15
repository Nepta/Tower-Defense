#include "jsmn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int getTowerRoot(TokenIterator *it, char* jsonFile){
	getNextObject(it);
	while(!it->end){
		
		int objectPosition = it->currentPosition;
		int stringStart = it->tokens[objectPosition+1].start;
		int stringEnd = it->tokens[objectPosition+1].end;
		int stringLenght = stringEnd - stringStart;
		if(strncmp(jsonFile + stringStart, "towers", stringLenght) == 0){
			return it->tokens[objectPosition].size;
		}
		getNextObject(it);
	}
 return 0;
}

void printToken(char* jsonFile, jsmntok_t *token){
	int stringStart = token->start;
	int stringEnd = token->end;
	for(int i=stringStart; i<stringEnd; i++){
		printf("%c",jsonFile[i]);
	}
	printf("\n");
}

int main(){
	FILE *data;
	data = fopen("resources/data.js", "r");
	char* jsonFile = fileToString(data);
	fclose(data);
	
	jsmn_parser parser;
	jsmntok_t tokens[32];	
	jsmn_init(&parser);
	jsmnerr_t parsingError = jsmn_parse(&parser,jsonFile,tokens,32);
	if(parsingError != JSMN_SUCCESS){
		printf("%d\n",parsingError);
		exit(parsingError);
	}
	TokenIterator *it = createTokenIterator(&parser, tokens);
	int towerDeep = getTowerRoot(it,jsonFile);
	if(it->end){
		puts("unexpected end of parsing");
		exit(5);
	}
	getNextObject(it);
	int currentDeepness = it->tokens[it->currentPosition].size;
	while(!(it->end || currentDeepness <= towerDeep)){
		printToken(jsonFile, &it->tokens[it->currentPosition]);
		getNextObject(it);
		currentDeepness = it->tokens[it->currentPosition].size;
	}
	
 return 0;
}
