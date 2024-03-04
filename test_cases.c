#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#include "mp_definitions.c"
#include "mp_events.c"
#include "mp_events2.c"
#include "mp_functions.c"
#include "mp_saving.c"
#include "mp_ui.c"
#include "mp_game_actions.c"
#include "mp_handlers.c"

void demoRand()
{
    int i;
    int nRandInt;
    srand(time(NULL)); // Seed the RNG
    printf("10 random integers from 1 to 5: randInt(1, 5)\n");
    for (i = 1; i <= 10; i++)
    {
        nRandInt = randInt(1, 5);
        printf("\t%2d.) %d", i, nRandInt);
    }
}

void demoDates()
{
    int nDay;
    for (nDay = 0; nDay <= DAYS + 1; nDay++)
    {
        printf("nDay = %2d: %2d/%-2d - ",
               nDay, toMonth(nDay), toDayOfMonth(nDay));
        displayDayOfWeek(nDay);
        printf("\n");
    }
}

int main()
{
    // demoRand();
    demoDates();
    return 0;
}