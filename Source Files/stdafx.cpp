#include "../Header Files/stdafx.h"

double getRand()
{
    //srand(time(0));
    return (double)rand()/(double)RAND_MAX; 
    //Возвращает случайное число от 0 до 1
}