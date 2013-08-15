#ifndef __jsonParser_H__
#define __jsonParser_H__

typedef struct{
	int currentPosition;
	int endPosition;
	jsmntok_t *tokens;
	int end;
}TokenIterator;

TokenIterator* createTokenIterator(jsmn_parser *parser, jsmntok_t *tokens);
TokenIterator* copyTokenIterator(TokenIterator *it);
char* fileToString(FILE *file);
void getNextObject(TokenIterator *iterator);
void printToken(char* jsonFile, jsmntok_t *token);
void getNextStringValue(TokenIterator*, char*, const char*);
TokenIterator* parseJson(char *jsonFile);


#endif /* __jsonParser_H__ */

