#include <stdio.h>
#include "tkf.h"


void displayMenu(Menu menu[])
{
    printf("\n");
    printf("              Korean Food (TKF) Restaurant\n");
    printf("----------------------------------------------------\n");
    printf(" No   Menu                              Regular Large\n");
    printf("----------------------------------------------------\n");


    for(int i = 0; i < MENU_SIZE; i++)
    {
        printf(" %-3d  %-35s %.2f  %.2f\n",
               i+1,
               menu[i].name,
               menu[i].regularPrice,
               menu[i].largePrice);
    }


    printf("----------------------------------------------------\n");
    printf("Maximum order per customer: %d\n", MAX_ORDER);
}