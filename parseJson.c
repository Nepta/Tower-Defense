#include "jsmn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jsonParser.h"

int main(){
	FILE *data;
	data = fopen("resources/data.js", "r");
	char* jsonFile = fileToString(data);
	fclose(data);
	
	TokenIterator *it = parseJson(jsonFile);
	
	getNextStringValue(it,jsonFile,"towers");
	int towerDeep = it->tokens[it->currentPosition].size; //getTowerRoot(it,jsonFile);
	getNextObject(it);
	int currentDeepness = it->tokens[it->currentPosition].size;
	while(!(it->end || currentDeepness <= towerDeep)){
		getNextStringValue(it,jsonFile,"location");//location
		printToken(jsonFile, &it->tokens[it->currentPosition]);
		
		getNextStringValue(it,jsonFile,"description");//description
		printToken(jsonFile, &it->tokens[it->currentPosition]);
		puts("");
		getNextObject(it);
		currentDeepness = it->tokens[it->currentPosition].size;
	}
	free(it);	
 return 0;
}
