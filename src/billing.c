#include "tkf.h"
#include <string.h>


void calculateBill(Customer *customer)
{
    customer->totalBill = 0;

    for(int i = 0; i < customer->totalOrder; i++)
    {
        customer->totalBill += customer->orderBill[i];
    }


    if(strcmp(customer->methodStatus, "Dine-In") == 0)
    {
        customer->serviceTax = customer->totalBill * 0.10;
    }
    else
    {
        customer->serviceTax = 0;
    }


    customer->governmentTax = customer->totalBill * 0.06;


    customer->finalBill =
        customer->totalBill +
        customer->serviceTax +
        customer->governmentTax;
}