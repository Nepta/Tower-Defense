#include "towerField.h"
#include <stdio.h>
#include <stdlib.h>

FieldInterface* createFieldInterface(){
	FieldInterface *field = malloc(sizeof (FieldInterface));
 return field;
}

void clickOnScreen(FieldInterface *field, int x,int y){
	printf("(%d,%d)\n",x,y);
}
