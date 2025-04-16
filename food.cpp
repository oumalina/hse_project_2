#include "food.h"
#include <stdlib.h>

void Food::expire()
{
    //изменение текстурки
}

void Food::food()
{
    x = rand() % 1260;
	y = rand() % 700;
    //появление текстурки
}