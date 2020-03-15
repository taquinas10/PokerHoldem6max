#include <stdio.h>
#include <stdlib.h>
#include "poker_SHORTDECK.h"
#include "translated.h"

/*************************************************/
/*                                               */
/*entries of boards(of size 1278*10) are         */
/*C1,C2,C3,C4,C5,RANK,#5cardCombos,6,7,primeProd */
/*                                               */
/* martin skoglund, 2019                         */
/* martin_skog@hotmail.com                       */
/*                                               */
/*************************************************/

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

main()
{
    int deck[36],hand[7];
    int a, b, c, n,rank,n5,n6,n7,primeP;
    FILE *fptr;

    // Seed the random number generator.
    srand48(getpid());
//for symmetry reasons we only need to consider holdings 6c7c8c9cTcJcQcKcAc6s7s8s9sTsJsQsKsAs
    // Initialize the deck.
    init_deck(deck);
    fptr = fopen("handOdds.txt", "w");

    // Loop over the boards
    
    
    for (a = 0; (a < 1278) ; a++)
    {
        hand[0] = boards[a*10];
        hand[1] = boards[a*10+1];
        hand[2] = boards[a*10+2];
        hand[3] = boards[a*10+3];
        hand[4] = boards[a*10+4];
        rank=boards[a*10+5];
        n5=boards[a*10+6];
        n6=boards[a*10+7];
        n7=boards[a*10+8];
        primeP=boards[a*10+9];
        
        for (b = 0; (b < 35) ; b++)
        {
            if (deck[b]!=hand[0] & deck[b]!=hand[1] & deck[b]!=hand[2] & deck[b]!=hand[3] & deck[b]!=hand[4])
            {
                hand[5] = deck[b];
                for (c = b+1; (c < 36) ; c++)
                {
                    if (deck[c]!=hand[0] & deck[c]!=hand[1] & deck[c]!=hand[2] & deck[c]!=hand[3] & deck[c]!=hand[4])
                    {
                        hand[6] = deck[c];
                        n=eval_7hand(hand);
                        print_hand(hand,7);
                        printf("BOARD: %d %d %d %d %d, HAND:%d %d,RankBOARD:%d,Rankhand:%d\n",hand[0],hand[1],hand[2],hand[3],hand[4],hand[5],hand[6],rank,n);
                        fprintf(fptr,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",hand[0],hand[1],hand[2],hand[3],hand[4],hand[5],hand[6],n5,n6,n7,primeP,rank,n);
                    }
                    
                }
            }
        }     
     }                           
                        
                         // for (i=0;i<465;i++)
                          //{
                              /*printf("Community cards: %d,%d,%d,%d,%d holes: %d,%d, rank %d\n",handList[counter][0],handList[counter][1],handList[counter][2],handList[counter][3],handList[counter][4],holeList[a][1],holeList[a][2],rankList[a]);*/
                              
                              //print_hand(holeList[i],2);
                              //print_hand(handList[counter],5); 
                              
                              //printf(" RANK: %d\n",rankList[i]);
                              //printf("CONTROL: \n%d %d %d %d %d %d %d\n\n\n",holeList[i][0],holeList[i][1],handList[counter][0],handList[counter][1],handList[counter][2],handList[counter][3],handList[counter][4]);
                              //fprintf(fptr,"%d,%d,%d,%d,%d,%d,%d,%d\n",handList[counter][0],handList[counter][1],handList[counter][2],handList[counter][3],handList[counter][4],holeList[i][0],holeList[i][1],rankList[i]);
                              
                          //}
                          //if (counter % 100==0)
                          //{
                          //    printf("\n BoardCounter:%d\n",counter);
                          //    print_hand(handList[counter],5);
                          //}
                         
                          //counter++;
                        /*printf("\n Wins: %8d out of %2d\n",win,win+loss);
                        */
                        
                     
             
        
    
   
   fclose(fptr);
}