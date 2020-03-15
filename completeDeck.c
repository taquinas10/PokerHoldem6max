#include <stdio.h>
#include "poker_SHORTDECK.h"

/*************************************************/
/*                                               */
/* This code tests my evaluator, by looping over */
/* all hands  by martin Skoglund */
/*************************************************/

main()
{
    int deck[36],a;
    FILE *fptr;

    // Seed the random number generator.
    srand48(getpid());
//for symmetry reasons we only need to consider holdings 6c7c8c9cTcJcQcKcAc6s7s8s9sTsJsQsKsAs
    // Initialize the deck.
    init_deck(deck);
    fptr = fopen("aShortDeck.txt", "w");
    // Seed the random number generator.
    srand48(getpid());

    // Initialize the deck.
    init_deck(deck);
    for (a=0;a<36;a++)
    {
        fprintf(fptr,"%d\n",deck[a]);
    }
}
