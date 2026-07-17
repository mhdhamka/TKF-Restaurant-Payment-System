#include "tkf.h"

void adminPanel(Menu menu[], int *menuCount)
{
    int choice;


    do
    {
        printf("\n");
        printf("====================================\n");
        printf("             ADMIN PANEL\n");
        printf("====================================\n");

        printf("1. Add Menu Item\n");
        printf("2. Update Menu Price\n");
        printf("3. Delete Menu Item\n");
        printf("4. View Sales Report\n");
        printf("5. Back to Main Menu\n");

        printf("====================================\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        clearInputBuffer();

        switch(choice)
        {
            case 1:
                addMenuItem(menu, menuCount);
                break;

            case 2:
                updateMenuPrice(menu,*menuCount);
                break;

            case 3:
                deleteMenuItem(menu, menuCount);
                break;

            case 4:
                salesReport(menu,*menuCount);
                break;

            case 5:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid option.\n");
        }


    }while(choice != 5);

}

void addMenuItem(Menu menu[], int *menuCount)
{
    if(*menuCount >= MAX_MENU)
    {
        printf("Menu is full.\n");
        return;
    }


    Menu newItem;
    newItem.id = *menuCount + 1;

    printf("\nEnter food name: ");
    
    fgets(newItem.name,sizeof(newItem.name),stdin);
    newItem.name[strcspn(newItem.name,"\n")] = '\0';

    printf("Enter category: ");

    fgets(newItem.category,sizeof(newItem.category),stdin);
    newItem.category[strcspn(newItem.category,"\n")] = '\0';

    printf("Enter regular price: ");

    scanf("%f",&newItem.regularPrice);

    printf("Enter large price: ");

    scanf("%f",&newItem.largePrice);

    clearInputBuffer();

    newItem.quantitySold = 0;
    menu[*menuCount] = newItem;
    (*menuCount)++;

    printf("\nMenu item added successfully.\n");

}

void updateMenuPrice(Menu menu[], int menuCount)
{
    int id;

    displayMenu(menu,menuCount);

    printf("\nEnter menu ID to update: ");
    scanf("%d",&id);

    if(id < 1 || id > menuCount)
    {
        printf("Invalid menu ID.\n");
        return;
    }

    printf("New regular price: ");

    scanf("%f",&menu[id-1].regularPrice);

    printf("New large price: ");

    scanf("%f",&menu[id-1].largePrice);

    clearInputBuffer();

    printf("Price updated successfully.\n");

}

void deleteMenuItem(Menu menu[], int *menuCount)
{
    int id;

    displayMenu(menu,*menuCount);

    printf("\nEnter menu ID to delete: ");

    scanf("%d",&id);

    if(id < 1 || id > *menuCount)
    {
        printf("Invalid menu ID.\n");
        return;
    }

    for(int i=id-1;i<(*menuCount)-1;i++)
    {
        menu[i]=menu[i+1];

        menu[i].id=i+1;
    }

    (*menuCount)--;

    printf("Menu item deleted successfully.\n");

}

void salesReport(Menu menu[], int menuCount)
{

    printf("\n");
    printf("====================================\n");
    printf("            SALES REPORT\n");
    printf("====================================\n");


    printf("%-5s %-30s %-10s\n",
           "ID",
           "Food",
           "Sold");

    printf("------------------------------------\n");

    for(int i=0;i<menuCount;i++)
    {

        printf("%-5d %-30s %-10d\n",
               menu[i].id,
               menu[i].name,
               menu[i].quantitySold);

    }


    printf("====================================\n");

}
