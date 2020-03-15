#include <stdio.h>
#include "poker_SHORTDECK.h"

/*************************************************/
/*                                               */
/* This code tests my evaluator, by looping over */
/* all hands  by martin Skoglund */
/*************************************************/

main()
{
    int deck[36], hand[5], freq[10];
    int a, b, c, d, e, i, j;

    // Seed the random number generator.
    srand48(getpid());

    // Initialize the deck.
    init_deck(deck);

    // Zero out the frequency array.
    for (i = 0; i < 10; i++)
        freq[i] = 0;

    // Loop over every possible five-card hand.
    for (a = 0; a < 32; a++)
    {
	hand[0] = deck[a];
	for (b = a+1; b < 33; b++)
	{
	    hand[1] = deck[b];
	    for (c = b+1; c < 34; c++)
	    {
		hand[2] = deck[c];
		for (d = c+1; d < 35; d++)
		{
		    hand[3] = deck[d];
		    for (e = d+1; e < 36; e++)
		    {
			hand[4] = deck[e];

			i = eval_5hand(hand);
			j = hand_rank(i);
			freq[j]++;
		    }
		}
	    }
	}
    }

    for(i = 1; i <= 9; i++)
	printf("%15s: %8d\n", value_str[i], freq[i]);
}
