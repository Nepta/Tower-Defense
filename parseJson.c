#include "jsmn.h"
#include <stdio.h>
#include <stdlib.h>

char* fileToString(FILE *file){
	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	char *string = calloc(fileSize,1);
	fread(string, 1, fileSize+1, file);
 return string;
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
	for(int i=0; i<parser.toknext; i++){
		switch(tokens[i].type){
			case JSMN_PRIMITIVE:
				printf("Primitive :");
				break;
			case JSMN_OBJECT:
				printf("Object :");
				break;
			case JSMN_ARRAY:
				printf("Array :");
				break;
			case JSMN_STRING:
				printf("String :");
				break;
			default:
				break;
		}
		for(int j=tokens[i].start; j<tokens[i].end; j++){
			printf("%c",jsonFile[j]);
		}
		printf("\n");
	}
 return 0;
}
