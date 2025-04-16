#include <iostream>
#include <time.h>

int main()
{
    bool flag = true;
    int counter = 0; 
    int year = 0;
    const int LOOPS_PER_YEAR = 4;
    while (flag)
    {

        counter++;
        if (counter % LOOPS_PER_YEAR == 0) {
            year++;
        }
    }

    return 0;
}