#include "jsmn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jsonParser.h"
#define MAX_TOKEN 32

TokenIterator* createTokenIterator(jsmn_parser *parser, jsmntok_t *tokens){
	TokenIterator *iterator = malloc(sizeof (TokenIterator));
	iterator->currentPosition = -1;
	iterator->end = 0;
	iterator->endPosition = parser->toknext;
	iterator->tokens = tokens;
 return iterator;
}

TokenIterator* copyTokenIterator(TokenIterator *it){
	TokenIterator *iterator = malloc(sizeof (TokenIterator));
	iterator->currentPosition = it->currentPosition;
	iterator->end = it->end;
	iterator->endPosition = it->endPosition;
	iterator->tokens = it->tokens;
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

void printToken(char* jsonFile, jsmntok_t *token){
	int stringStart = token->start;
	int stringEnd = token->end;
	for(int i=stringStart; i<stringEnd; i++){
		printf("%c",jsonFile[i]);
	}
	printf("\n");
}

void getNextStringValue(TokenIterator *iterator, char* jsonFile, const char* key){
	iterator->currentPosition++;
	while(!(iterator->currentPosition >= iterator->endPosition)){
		if(iterator->tokens[iterator->currentPosition].type == JSMN_STRING){
			int objectPosition = iterator->currentPosition;
			int stringStart = iterator->tokens[objectPosition].start;
			int stringEnd = iterator->tokens[objectPosition].end;
			int stringLenght = stringEnd - stringStart;
			if(strncmp(jsonFile + stringStart, key, stringLenght) == 0){
				iterator->currentPosition++;
				return;
			}
		}
		iterator->currentPosition++;
	}
	if(iterator->currentPosition >= iterator->end){
		iterator->end = 1;
	}
}

TokenIterator* parseJson(char *jsonFile){
	jsmn_parser parser;
	jsmntok_t *tokens = malloc(MAX_TOKEN * sizeof (jsmntok_t));
	jsmn_init(&parser);
	jsmnerr_t parsingError = jsmn_parse(&parser,jsonFile,tokens,MAX_TOKEN);
	if(parsingError != JSMN_SUCCESS){
		printf("%d\n",parsingError);
		exit(parsingError);
	}
	TokenIterator *it = createTokenIterator(&parser, tokens);
	return it;
}

