#include "food.h"
#include <stdlib.h>

void food::expire()
{
    //изменение текстурки
}

food::food()
{
    x = rand() % 1260;
	y = rand() % 700;
    //появление текстурки
}