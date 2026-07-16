#include <stdio.h>
#include <string.h>
#include "tkf.h"



int addOrder(Customer *customer, Menu menu[])
{
    if(customer->totalOrder >= MAX_ORDER)
    {
        printf("Maximum order reached.\n");
        return 0;
    }


    int choice;
    char size;


    printf("\nEnter menu number: ");
    scanf("%d",&choice);


    if(choice < 1 || choice > MENU_SIZE)
    {
        printf("Invalid menu.\n");
        return 0;
    }


    printf("Enter size (R/L): ");
    scanf(" %c",&size);


    strcpy(customer->orderName[customer->totalOrder],
           menu[choice-1].name);



    if(size == 'R' || size == 'r')
    {
        strcpy(customer->orderSize[customer->totalOrder],"R");

        customer->orderBill[customer->totalOrder]
        =
        menu[choice-1].regularPrice;


    }
    else if(size == 'L' || size == 'l')
    {
        strcpy(customer->orderSize[customer->totalOrder],"L");

        customer->orderBill[customer->totalOrder]
        =
        menu[choice-1].largePrice;

    }
    else
    {
        printf("Invalid size.\n");
        return 0;
    }


    customer->totalOrder++;

    return 1;
}



int removeOrder(Customer *customer)
{
    int remove;


    if(customer->totalOrder == 0)
    {
        printf("Cart is empty.\n");
        return 0;
    }


    printf("Remove order number (1-%d): ",
           customer->totalOrder);

    scanf("%d",&remove);



    if(remove < 1 || remove > customer->totalOrder)
    {
        printf("Invalid order.\n");
        return 0;
    }



    for(int i=remove-1;i<customer->totalOrder-1;i++)
    {
        strcpy(customer->orderName[i],
               customer->orderName[i+1]);


        strcpy(customer->orderSize[i],
               customer->orderSize[i+1]);


        customer->orderBill[i]
        =
        customer->orderBill[i+1];
    }


    customer->totalOrder--;


    printf("Order removed.\n");


    return 1;
}