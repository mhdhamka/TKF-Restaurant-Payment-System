#include <stdio.h>
#include "tkf.h"


void displayReceipt(Customer customer)
{
    printf("\n");
    printf("----------------------------------------------------\n");
    printf("                 TKF RECEIPT\n");
    printf("----------------------------------------------------\n");


    printf("Receipt No : %03d\n", customer.receiptNo);
    printf("Status     : %s\n", customer.memberStatus);
    printf("Order Type : %s\n\n", customer.methodStatus);


    printf("Order                 Size        Price\n");
    printf("--------------------------------------------\n");


    for(int i=0;i<customer.totalOrder;i++)
    {
        printf("%-22s %-5s %.2f\n",
               customer.orderName[i],
               customer.orderSize[i],
               customer.orderBill[i]);
    }


    printf("--------------------------------------------\n");

    printf("Subtotal              %.2f\n",
           customer.totalBill);

    printf("Service Tax           %.2f\n",
           customer.serviceTax);

    printf("Government Tax        %.2f\n",
           customer.governmentTax);


    printf("--------------------------------------------\n");

    printf("Total                 %.2f\n",
           customer.finalBill);


    printf("--------------------------------------------\n");
}



void displayTransaction(Customer customers[], int totalCustomer)
{

    if(totalCustomer == 0)
    {
        printf("No transaction available.\n");
        return;
    }


    for(int i=0;i<totalCustomer;i++)
    {
        displayReceipt(customers[i]);
    }
}



void saveTransaction(Customer customers[], int totalCustomer)
{
    FILE *file;


    file=fopen("TransactionRecord.txt","w");


    if(file==NULL)
    {
        printf("Cannot create file.\n");
        return;
    }



    for(int i=0;i<totalCustomer;i++)
    {

        fprintf(file,
        "Receipt No : %03d\n",
        customers[i].receiptNo);


        fprintf(file,
        "Status : %s\n",
        customers[i].memberStatus);


        fprintf(file,
        "Method : %s\n\n",
        customers[i].methodStatus);

        for(int j=0;j<customers[i].totalOrder;j++)
        {
            fprintf(file,
            "%s %s %.2f\n",
            customers[i].orderName[j],
            customers[i].orderSize[j],
            customers[i].orderBill[j]);
        }


        fprintf(file,
        "Total %.2f\n",
        customers[i].finalBill);


        fprintf(file,
        "---------------------------------\n");

    }


    fclose(file);
}