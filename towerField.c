#include "towerField.h"

#include <stdio.h>
#include <stdlib.h>

FieldInterface* createFieldInterface(){
	FieldInterface *field = malloc(sizeof (FieldInterface));
 return field;
}

void clickOnScreen(Interface *interfaces, int x,int y){
	FieldInterface *field = interfaces->field;
	printf("(%d,%d)\n",x,y);
}
