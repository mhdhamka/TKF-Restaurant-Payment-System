#ifndef TKF_H
#define TKF_H

#define MAX_ORDER 5
#define MENU_SIZE 5

typedef struct
{
    char name[50];
    float regularPrice;
    float largePrice;

} Menu;


typedef struct
{
    int receiptNo;

    char memberStatus[20];
    char methodStatus[20];

    char orderName[MAX_ORDER][50];
    char orderSize[MAX_ORDER][5];

    float orderBill[MAX_ORDER];

    int totalOrder;

    float totalBill;
    float serviceTax;
    float governmentTax;
    float finalBill;

} Customer;


/* Menu */
void displayMenu(Menu menu[]);


/* Order */
int addOrder(Customer *customer, Menu menu[]);
int removeOrder(Customer *customer);


/* Billing */
void calculateBill(Customer *customer);


/* Receipt */
void displayReceipt(Customer customer);
void displayTransaction(Customer customers[], int totalCustomer);
void saveTransaction(Customer customers[], int totalCustomer);


#endif