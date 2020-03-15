#include <stdio.h>
#include <stdlib.h>
#include "poker_SHORTDECK.h"

/*************************************************/
/*                                               */
/* This code tests my evaluator, by looping over */
/* all hands  by martin Skoglund */
/*************************************************/

main()
{
    int deck[36], hand[5],hero[7], community[5],enemy[7],handList[278256][5];
    int a, b, c, d, e, i, j,k,l,m,n,win,loss,tie,counter,hole1,hole2;
    float freq[201376];
    FILE *fptr;

    // Seed the random number generator.
    srand48(getpid());
//for symmetry reasons we only need to consider holdings 6c7c8c9cTcJcQcKcAc6s7s8s9sTsJsQsKsAs
    // Initialize the deck.
    init_deck(deck);
    fptr = fopen("handOdds.txt", "w");
    // Zero out the frequency array.
    for (hole1=0;hole1<17;hole1++)
    {
        hero[0]=deck[hole1];
        for (hole2=hole1+1;hole2<18;hole2++)
        {
            hero[1]=deck[hole2];
            
            counter=0;
    // Loop over every possible five-card hand.
    
            for (a = 0; (a < 32) & a!=hole1 & a!=hole2; a++)
            {
                hand[0] = deck[a];
                for (b = a+1; (b < 33) & b!=hole1 & b!=hole2; b++)
                {
                    hand[1] = deck[b];
                    for (c = b+1; (c < 34) & c!=hole1 & c!=hole2; c++)
                    {
                        hand[2] = deck[c];
                        for (d = c+1; (d < 35) & d!=hole1 & d!=hole2; d++)
                        {
                            hand[3] = deck[d];
                            for (e = d+1; (e < 36) & e!=hole1 & e!=hole2; e++)
                            {
                                hand[4] = deck[e];
                                win=0;
                                loss=0;
                                tie=0;
                           
                                for(m=2;m<7;m++)
                                {
                                    enemy[m]=hand[m-2];
                                    hero[m]=hand[m-2];
                                }
                        
                                i = eval_7hand(hero);
                        
                                for (k = 0; k < 35; k++)
                                {
                                    if ((k!=hole1) & (k!=hole2) & (k!=a) & (k!=b) & (k!=c) & (k!=d) & (k!=e))
                                    {
                                        enemy[0]=deck[k];
                                        for (l = k+1; l < 36; l++)
                                        {
                                            if ((l!=hole1) & (l!=hole2) & (l!=a) & (l!=b) & (l!=c) & (l!=d) & (l!=e))
                                            {
                                                enemy[1]=deck[l];
                                                n=eval_7hand(enemy);
                                                if(i<n){win++;}
                                                if(i==n){tie++;}
                                                if (i>n){loss++;}
                                        
                                            }
                                        }
                                
                                    }
                            
                                }
                        
                                counter++;
                                freq[counter]=(win+0.00001)/(win+loss+tie)+(tie+0.00001)/(2*(win+loss+tie));
                                for (l=0; l<5;l++)
                                {
                                    handList[counter][l]=hand[l];
                                }
                        /*printf("\n Wins: %8d out of %2d\n",win,win+loss);
                        */
                        
                            }
                        }
                    }
                }
            }
            for (a=0;a<278256;a++)
            {
                /*printf("HOLECARDS: ");
                print_hand(hero,2);   
                printf("\n BOARD: ");    
                print_hand(handList[a],5);
                printf("\n WINPERCENT: %f \n",freq[a]);*/
                fprintf(fptr,"%d,%d,%d,%d,%d,%d,%d,%f\n",hero[0],hero[1],handList[a][1],handList[a][2],handList[a][3],handList[a][4],handList[a][5],freq[a]);
            }
            fprintf(fptr,"€");
            printf("HOLECARDS: ");
            print_hand(hero,2); 
        }
    }
   
    fclose(fptr);
}
