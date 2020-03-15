#include <stdio.h>
#include <stdlib.h>
#include "poker_SHORTDECK.h"

/*************************************************/
/*                                               */
/* This code tests my evaluator, by looping over */
/* all 2,598,960 possible five card hands, cal-  */
/* culating each hand's distinct value, and dis- */
/* playing the frequency count of each hand type */
/*                                               */
/* Kevin L. Suffecool, 2001                      */
/* kevin@suffe.cool                              */
/*                                               */
/*************************************************/

main()
{
    int deck[36], hand[5],hero[7], community[5],enemy[7],handList[376992][5],holeList[465][2],rankList[465];
    int a, b, c, d, e, i, j,k,l,m,n,win,loss,tie,counter,hole1,hole2,counter2;
    FILE *fptr;

    // Seed the random number generator.
    srand48(getpid());
//for symmetry reasons we only need to consider holdings 6c7c8c9cTcJcQcKcAc6s7s8s9sTsJsQsKsAs
    // Initialize the deck.
    init_deck(deck);
    fptr = fopen("handOdds.txt", "w");

    counter=0;
    // Loop over every possible five-card hand.
    
    for (a = 0; (a < 32) ; a++)
    {
        hand[0] = deck[a];
        for (b = a+1; (b < 33) ; b++)
        {
            hand[1] = deck[b];
            for (c = b+1; (c < 34) ; c++)
            {
                hand[2] = deck[c];
                for (d = c+1; (d < 35) ; d++)
                {
                    hand[3] = deck[d];
                    for (e = d+1; (e < 36) ; e++)
                    {
                        hand[4] = deck[e];
                          
                        for(m=2;m<7;m++)
                        {
                            enemy[m]=hand[m-2];
                        }
                      
                        counter2=0;
                        for (k = 0; (k < 35); k++)
                        {
                             if((k!=a) & (k!=b) & (k!=c) & (k!=d) & (k!=e))
                             {
                              
                                 enemy[0]=deck[k];
                                 for (l = k+1; (l < 36); l++)
                                 {
                                     if((l!=a) & (l!=b) & (l!=c) & (l!=d) & (l!=e))
                                     {
                                         //printf("k and l %d %d\n AND abcde %d %d %d %d %d\n",k,l,a,b,c,d,e);
                                         enemy[1]=deck[l];
                                         n=eval_7hand(enemy);
                                         //printf("\n holes: %d %d\n",enemy[0],enemy[1]);
                                         holeList[counter2][0]=enemy[0];
                                         holeList[counter2][1]=enemy[1];
                                         rankList[counter2]=n;
                                         counter2++;
                                     }
                                 }
                             }
                                 
                                
                             
                            
                         }
                            
                          for (i=0; i<5;i++)
                          {
                              handList[counter][i]=hand[i];
                          }
                          for (i=0;i<465;i++)
                          {
                              /*printf("Community cards: %d,%d,%d,%d,%d holes: %d,%d, rank %d\n",handList[counter][0],handList[counter][1],handList[counter][2],handList[counter][3],handList[counter][4],holeList[a][1],holeList[a][2],rankList[a]);*/
                              
                              //print_hand(holeList[i],2);
                              //print_hand(handList[counter],5); 
                              
                              //printf(" RANK: %d\n",rankList[i]);
                              //printf("CONTROL: \n%d %d %d %d %d %d %d\n\n\n",holeList[i][0],holeList[i][1],handList[counter][0],handList[counter][1],handList[counter][2],handList[counter][3],handList[counter][4]);
                              fprintf(fptr,"%d,%d,%d,%d,%d,%d,%d,%d\n",handList[counter][0],handList[counter][1],handList[counter][2],handList[counter][3],handList[counter][4],holeList[i][0],holeList[i][1],rankList[i]);
                              
                          }
                          if (counter % 100==0)
                          {
                              printf("\n BoardCounter:%d\n",counter);
                              print_hand(handList[counter],5);
                          }
                         
                          counter++;
                        /*printf("\n Wins: %8d out of %2d\n",win,win+loss);
                        */
                        
                    }
                }
            }
        }
    }
            
                /*printf("HOLECARDS: ");
                print_hand(hero,2);   
                printf("\n BOARD: ");    
                print_hand(handList[a],5);
                printf("\n WINPERCENT: %f \n",freq[a]);*/
               /* fprintf(fptr,"%d,%d,%d,%d,%d,%d,%d,%f\n",hero[0],hero[1],handList[a][1],handList[a][2],handList[a][3],handList[a][4],handList[a][5],freq[a]);*/
   
            /*fprintf(fptr,"€");
            printf("HOLECARDS: ");
            print_hand(hero,2); */
        
    
   
   fclose(fptr);
}