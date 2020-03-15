#include <stdio.h>
#include "SHORTDECK_products.h"
#include "SHORTDECK_values.h"
#include "SHORTDECK_unique5.h"
#include "SHORTDECK_FLUSHES.h"
#include "7choose5nPrimes.h"
#include <string.h>

#include "poker_SHORTDECK.h"

// Poker hand evaluator
//
// Kevin L. Suffecool
// kevin@suffe.cool
//

void srand48();
double drand48();

// perform a binary search on a pre-sorted array
//
int findit(int key)
{
    int low = 0, high = 1151, mid;

    while (low <= high)
    {
        mid = (high + low) >> 1;      // divide by two
        if (key < products[mid])
            high = mid - 1;
        else if (key > products[mid])
            low = mid + 1;
        else
            return mid;
    }
    fprintf(stderr, "ERROR:  no match found; key = %d\n", key);
    return -1;
}


//
//   This routine initializes the deck.  A deck of cards is
//   simply an integer array of length 52 (no jokers).  This
//   array is populated with each card, using the following
//   scheme:
//
//   An integer is made up of four bytes.  The high-order
//   bytes are used to hold the rank bit pattern, whereas
//   the low-order bytes hold the suit/rank/prime value
//   of the card.
//
//   +--------+--------+--------+--------+
//   |xxxbbbbb|bbbbbbbb|cdhsrrrr|xxpppppp|
//   +--------+--------+--------+--------+
//
//   p = prime number of rank (six=2,seven=3, eight=5,nine=7,...,ace=23)
//   r = rank of card (six=4,seven=5,...,ace=12)
//   cdhs = suit of card
//   b = bit turned on depending on rank of card
//
void
init_deck(int *deck)
{
    int i, j, n = 0, suit = 0x8000;

    for (i = 0; i < 4; i++, suit >>= 1)
        for (j = 0; j < 9; j++, n++)
            deck[n] = primes[j] | (j << 8) | suit | (1 << (20+j));
}


//  This routine will search a deck for a specific card
//  (specified by rank/suit), and return the INDEX giving
//  the position of the found card.  If it is not found,
//  then it returns -1
//
int
find_card(int rank, int suit, int *deck)
{
    int i, c;

    for (i = 0; i < 36; i++)
    {
        c = deck[i];
        if ((c & suit) && (RANK(c) == rank))
            return i;
    }
    return -1;
}


//
//  This routine takes a deck and randomly mixes up
//  the order of the cards.
//
void
shuffle_deck(int *deck)
{
    int i, n, temp[36];

    for (i = 0; i < 36; i++)
        temp[i] = deck[i];

    for (i = 0; i < 36; i++)
    {
        do {
            n = (int)(35.9999999 * drand48());
        } while (temp[n] == 0);
        deck[i] = temp[n];
        temp[n] = 0;
    }
}


void
print_hand(int *hand, int n)
{
    int i, r;
    char suit;
    static char *rank = "6789TJQKA";

    for (i = 0; i < n; i++)
    {
        r = (*hand >> 8) & 0xF;
        if (*hand & 0x8000)
            suit = 'c';
        else if (*hand & 0x4000)
            suit = 'd';
        else if (*hand & 0x2000)
            suit = 'h';
        else
            suit = 's';

        printf("%c%c ", rank[r], suit);
        hand++;
    }
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char*
translate_hand(int *hand, int n)
{
    int i, r;
    char suit;
    static char *rank = "6789TJQKA";
    

    for (i = 0; i < n; i++)
    {
        r = (*hand >> 8) & 0xF;
        if (*hand & 0x8000)
            suit = 'c';
        else if (*hand & 0x4000)
            suit = 'd';
        else if (*hand & 0x2000)
            suit = 'h';
        else
            suit = 's';

        return concat(rank[r], suit);
        hand++;
    }
}


int
hand_rank(short val)
{
    if (val > 1284) return HIGH_CARD;        // 121 high card
    if (val > 780) return ONE_PAIR;         // 504 one pair
    if (val > 528) return TWO_PAIR;         //  252 two pair
    if (val > 276) return THREE_OF_A_KIND;  //  252 three-kind
    if (val > 270) return STRAIGHT;         //   6 straights
    if (val > 198)  return FULL_HOUSE;       //  72 full house
    if (val > 78)  return FLUSH;            // 1277 flushes
    if (val > 6)   return FOUR_OF_A_KIND;   //  72 four-kind
    return STRAIGHT_FLUSH;                   //   6 straight-flushes
}


short
eval_5cards(int c1, int c2, int c3, int c4, int c5)
{
    int q;
    short s;

    q = (c1 | c2 | c3 | c4 | c5) >> 16;

    // check for Flushes and StraightFlushes
    if (c1 & c2 & c3 & c4 & c5 & 0xF000)
        return flushes[q];

    // check for Straights and HighCard hands
    s = unique5[q];
    if (s)  return s;

    // let's do it the hard way
    q = (c1&0xFF) * (c2&0xFF) * (c3&0xFF) * (c4&0xFF) * (c5&0xFF);
    q = findit(q);

    return values[q];
}


short
eval_5hand(int *hand)
{
    int c1, c2, c3, c4, c5;

    c1 = *hand++;
    c2 = *hand++;
    c3 = *hand++;
    c4 = *hand++;
    c5 = *hand;

    return eval_5cards(c1,c2,c3,c4,c5);
}


// This is a non-optimized method of determining the
// best five-card hand possible out of seven cards.
// I am working on a faster algorithm.
//
short
eval_7hand(int *hand)
{
    int i, j, q, best = 9999, subhand[5];

    for (i = 0; i < 21; i++)
    {
        for (j = 0; j < 5; j++)
            subhand[j] = hand[ perm7[i][j] ];
        q = eval_5hand(subhand);
        if (q < best)
            best = q;
    }
    return best;
}