
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Structure definition
struct CustomerDetails {
	int ReceiptNo; //Structure members declaration
	int TotalOrder;
	char *MemberStatus;
	char *MethodStatus;
	char *OrderName[5];
	char *OrderSize[5];
	float OrderBill[5];
	float TotalBill;
	float FinalBill;
	float ServiceTax;
	float GovernmentTax;
}*Customer, **ptr = &Customer; //Structure variables declaration

//Function prototype
void DisplayMenu();
void FinalReceipt(int CustomerCounter, int OrderCounter, struct CustomerDetails *ptr);
void TransactionRecord(int TotalCustomer, int CustomerCounter, int OrderCounter, struct CustomerDetails *ptr);
int OrderCart(int CustomerCounter, int OrderCounter, struct CustomerDetails *ptr);
int EditOrder(int CustomerCounter, int OrderCounter, struct CustomerDetails *ptr);
float CalculateBill(int CustomerCounter, int OrderCounter, struct CustomerDetails *ptr);

int main()
{
	//Variable declaration and array initialization
	int InputOption;
	int InputOrder;
	int InputEdit;
	int CustomerCounter;
	int TotalCustomer;
	int OrderCounter;
	int TotalOrder;
	int ContinueEdit;
	float MenuPrice;
	float DiscountRegular;
	float DiscountLarge;
	float NonMemberRegular[5] = {10.00, 9.00, 8.50, 8.50, 7.00};
	float NonMemberLarge[5] = {15.00, 14.00, 13.50, 13.50, 12.00};
	char InputMember;
	char InputMethod;
	char InputSize;
	char CheckOrder;
	char Continue;
	char ContinueRemove;
	char AddOrder;
	char *Member[2] = {"Member", "Non Member"};
	char *Method[2] = {"Dine-In", "Takeaway"};
	char *MenuName[5] = {"Bibimbap", "2 pc(s) Korean Fried Chicken", "Bulgogi", "Japchae", "Hameul Pajeon"};
	char *MenuSize[2] = {"R", "L"};
	
	//Variable initialization
	CustomerCounter = 0;
	DiscountRegular = 0.10;
	DiscountLarge = 0.15;
	Customer = (struct CustomerDetails*)malloc(CustomerCounter*sizeof(int));
	
	//File pointer for TransactionRecord.txt
	FILE *TransactionPtr;
	
	do
	{
		DisplayMenu(); //Function call DisplayMenu() in main to display the menu
		printf("*Displayed prices are not inclusive of tax charges.\n\n");
		printf("Government Tax: 6%% from the total price of the bill excluding Service Tax.\n");
		printf("Service Tax   : 10%% for Dine-In orders from the total price of the bill excluding Government Tax.\n\n");
		printf("                            Please select:\n");
		printf("                         1. Make an Order\n");
		printf("                         2. Transaction Record\n\n");
		
		do
		{
			InputOption = 0;
			printf("Enter the option you want to select: "); //User prompt to enter input for the option
			scanf(" %d", &InputOption); //Stores user input into variable InputOption
			fflush(stdin);
			if (InputOption != 1 && InputOption != 2)
			{
				printf("\nInput entered is invalid, please retry.\n");
			}
		}while(InputOption != 1 && InputOption != 2); //Repeats do_while loop (line 87) if user did not input 1 or 2
		
		if (InputOption == 1)
		{
			CustomerCounter++; //User inputs 1, indicating user wants to place orders therefore CustomerCounter is increased by 1
			Customer[CustomerCounter].ReceiptNo = CustomerCounter; //Assign the CustomerCounter as the ReceiptNo
	
			do
			{
				printf("Are you a member? (Y for Yes | N for No): "); //User prompt to enter input for member status
				scanf(" %c", &InputMember); //Stores user input into variable InputMember
				fflush(stdin);
				if (toupper(InputMember) == 'Y')
				{
					Customer[CustomerCounter].MemberStatus = Member[0]; //Assign MemberStatus as "Member" from array Member[2] (line 63)
				}
				else if (toupper(InputMember) == 'N')
				{
					Customer[CustomerCounter].MemberStatus = Member[1]; //Assign MemberStatus as "Non Member" from array Member[2] (line 63)
				}
				else
				{
					printf("\nInput entered is invalid, please retry.\n");
				}
			}while(toupper(InputMember) != 'Y' && toupper(InputMember) != 'N'); //Repeats do_while loop (line 104) if user did not input Y/y or N/n
			
			do
			{
				printf("Order for Dine-In or Takeaway? (D for Dine-In | T for Takeaway): "); //User prompt to enter input for dining method
				scanf(" %c", &InputMethod); //Stores user input into variable InputMethod
				fflush(stdin);
				if (toupper(InputMethod) == 'D')
				{
					Customer[CustomerCounter].MethodStatus = Method[0]; //Assign MethodStatus as "Dine-In" from array Method[2] (line 64)
				}
				else if (toupper(InputMethod) == 'T')
				{
					Customer[CustomerCounter].MethodStatus = Method[1]; //Assign MethodStatus as "Takeaway" from array Method[2] (line 64)
				}
				else
				{
					printf("\nInput entered is invalid, please retry.\n");
				}
			}while(toupper(InputMethod) != 'D' && toupper(InputMethod) != 'T'); //Repeats do_while loop (line 123) if user did not input D/d or T/t
			
			for (OrderCounter = 0; OrderCounter < 5; OrderCounter++) //For loop to start placing order(s)
			{
				Customer[CustomerCounter].TotalOrder = 0;
				do
				{
					InputOrder = 0;
					printf("\nEnter the menu number you want to order: "); //User prompt to enter input number for the order based on the menu
					scanf(" %d", &InputOrder); //Stores user input into variable InputOrder
					fflush(stdin);
					if (InputOrder != 1 && InputOrder != 2 && InputOrder != 3 && InputOrder != 4 && InputOrder != 5)
					{
						printf("Invalid.\n");
					}
				}while(InputOrder != 1 && InputOrder != 2 && InputOrder != 3 && InputOrder != 4 && InputOrder != 5); //Repeats do_while loop (line 145) if user did not input 1, 2, 3, 4 or 5
				Customer[CustomerCounter].OrderName[OrderCounter] = MenuName[InputOrder-1]; /*OrderName[OrderCounter] is assigned to the element in index
																							  [InputOrder-1] from array MenuName[5] (line 65) and the index
																							  is [InputOrder-1] because index of arrays starts from [0].*/
	
				do
				{
					printf("Enter the size for the order (R for Regular | L for Large): "); //User prompt to enter input for order size
					scanf(" %c", &InputSize); //Stores user input into variable InputSize
					fflush(stdin);
					if (toupper(InputSize) == 'R')
					{
						Customer[CustomerCounter].OrderSize[OrderCounter] = MenuSize[0]; //OrderSize[OrderCounter] is assigned as element "R" from array MenuSize[2] (line 66)
						MenuPrice = NonMemberRegular[InputOrder-1]; /*MenuPrice acts as a placeholder and it is assigned to the element in
																	  index [InputOrder-1] from array NonMemberRegular[5] (line 54) and the
																	  index is [InputOrder-1] because index of arrays starts from [0].*/
					}
					else if (toupper(InputSize) == 'L')
					{
						Customer[CustomerCounter].OrderSize[OrderCounter] = MenuSize[1]; //OrderSize[OrderCounter] is assigned as element "L" from array MenuSize[2] (line 66)
						MenuPrice = NonMemberLarge[InputOrder-1]; /*MenuPrice acts as a placeholder and it is assigned to the element in
																	index [InputOrder-1] from array NonMemberLarge[5] (line 55) and the
																	index is [InputOrder-1] because index of arrays starts from [0].*/
					}
					else 
					{
						printf("Input entered is invalid, please retry.\n");
					}
				}while(toupper(InputSize) != 'R' && toupper(InputSize) != 'L'); //Repeats do_while loop (line 160) if user did not input R/r or L/l
				
				if (Customer[CustomerCounter].MemberStatus == Member[0]) //To calculate the discount for members
				{
					if (Customer[CustomerCounter].OrderSize[OrderCounter] == MenuSize[0]) 
					{
						MenuPrice = MenuPrice - (MenuPrice*DiscountRegular); //Calculate the discount for MenuPrice for size regular
					}
					else if (Customer[CustomerCounter].OrderSize[OrderCounter] == MenuSize[1])
					{
						MenuPrice = MenuPrice - (MenuPrice*DiscountLarge); //Calculate the discount for MenuPrice for size large
					}
				}
				Customer[CustomerCounter].OrderBill[OrderCounter] = MenuPrice; //MenuPrice is assigned to OrderBill[OrderCounter]
				OrderCart(CustomerCounter, OrderCounter, &Customer[CustomerCounter]); //Function call OrderCart in main to display the order cart
				
				do
				{
					ContinueEdit = 0;
					if (OrderCounter < 4) //For the user if the user is still placing <5 orders
					{
						printf("\nNotice: You have %d order(s) remaining.\n", 4-OrderCounter); //To notify the user of the remaining orders
						InputEdit = 0;
						do
						{
							printf("\n               Please select:\n");
							printf("          1. Add another order.\n");
							printf("          2. Remove existing order(s).\n");
							printf("          3. Proceed to checkout.\n");
							printf("\nEnter the option you want to select: "); //User prompt to enter input for edit options
							scanf(" %d", &InputEdit); //Stores user input into variable InputEdit
							fflush(stdin);
							if (InputEdit != 1 && InputEdit != 2 && InputEdit != 3)
							{
								printf("Input entered is invalid, please retry.\n");
							}
						}while(InputEdit != 1 && InputEdit != 2 && InputEdit != 3); //Repeats do_while loop (line 206) if user did not input 1, 2 or 3
						if (InputEdit == 1)
						{
							DisplayMenu(); //Since InputEdit == 1 indicates the user wants to add another order, function call DisplayMenu 
						}
						else if (InputEdit == 2)
						{
							do
							{
								EditOrder(CustomerCounter, OrderCounter, &Customer[CustomerCounter]); //Since InputEdit == 2 indicates the user wants to remove an order, function call EditOrder in main to edit order 
								if (OrderCounter > 0)
								{
									OrderCounter = OrderCounter-1; //Since an order has been removed, OrderCounter is decreased by 1
									do
									{
										printf("\nRemove another order? (Y for Yes | N for No): "); //User prompt to enter input for continuation of order removal
										scanf(" %c", &ContinueRemove); //Stores user input into variable ContinueRemove
										fflush(stdin);
										if (toupper(ContinueRemove) == 'N')
										{
											ContinueEdit = 1; //A variable to continue do_while loop condition (line 312)
										}
										else if (toupper(ContinueRemove) != 'Y' && toupper(ContinueRemove) != 'N')
										{
											printf("Input entered is invalid, please retry.\n");
										}
									}while(toupper(ContinueRemove) != 'Y' && toupper(ContinueRemove) != 'N'); //Repeats do_while loop (line 232) if user did not input Y/y or N/n
								}
								else if (OrderCounter == 0)
								{
									OrderCounter = -1; //Assign OrderCounter to -1 since for loop (line 142) will increase ++ at the end to make OrderCounter revert to 0
									ContinueRemove = 'b'; //To exit the do_while loop condition (line 252)
								}
							}while(toupper(ContinueRemove) == 'Y'); //Repeats do_while loop (line 226) as user wants to continue remove orders
						}
						else if (InputEdit == 3)
						{
							OrderCounter = OrderCounter+6; //To exit the for loop condition (line 142)
							Customer[CustomerCounter].TotalOrder = OrderCounter;
						}
					}
					else if (OrderCounter == 4) //For the user if the user has placed 5 orders
					{
						printf("\nNotice: You have reached the maximum amount of orders.\n"); //To notify the user the user has reached the maximum amount of orders
						InputEdit = 0;
						do
						{
							printf("\n               Please select:\n");
							printf("          1. Remove existing order(s).\n");
							printf("          2. Proceed to checkout.\n");
							printf("\nEnter the option you want to select: "); //User prompt to enter input for edit options
							scanf(" %d", &InputEdit); //Stores user input into variable InputEdit
							fflush(stdin);
							if (InputEdit != 1 && InputEdit != 2)
							{
								printf("Input entered is invalid, please retry.\n");
							}
						}while(InputEdit != 1 && InputEdit != 2); //Repeats do_while loop (line 264) if user did not input 1 or 2
						if (InputEdit == 1)
						{
							do
							{
								EditOrder(CustomerCounter, OrderCounter, &Customer[CustomerCounter]); //Since InputEdit == 1 indicates the user wants to remove an order, function call EditOrder in main to edit order
								if (OrderCounter > 0)
								{
									OrderCounter = OrderCounter-1; //Since an order has been removed, OrderCounter is decreased by 1
									do
									{
										printf("\nRemove another order? (Y for Yes | N for No): "); //User prompt to enter input for continuation of order removal
										scanf(" %c", &ContinueRemove); //Stores user input into variable ContinueRemove
										fflush(stdin);
										if (toupper(ContinueRemove) == 'N')
										{
											ContinueEdit = 1; //A variable to continue do_while loop condition (line 312)
										}
										else if (toupper(ContinueRemove) != 'Y' && toupper(ContinueRemove) != 'N')
										{
											printf("Input entered is invalid, please retry.\n");
										}
									}while(toupper(ContinueRemove) != 'Y' && toupper(ContinueRemove) != 'N'); //Repeats do_while loop (line ) if user did not input Y/y or N/n
								}
								else if (OrderCounter == 0)
								{
									OrderCounter = -1; //Assign OrderCounter to -1 since for loop (line 142) will increase ++ at the end to make OrderCounter revert to 0
									ContinueRemove = 'b'; //To exit the do_while loop condition (line 306)
								}
							}while(toupper(ContinueRemove) == 'Y');
						}
						else if (InputEdit == 2)
						{
							Customer[CustomerCounter].TotalOrder = OrderCounter+1; //Since OrderCounter starts from 0, index for the 5th order is OrderCounter = 4, therefore OrderCounter+1 to finalize the value
						}
					}
				}while(ContinueEdit == 1); //Repeats do_while loop (line 199) to display the edit options (line 206)
					
				if (Customer[CustomerCounter].TotalOrder > 5)
				{
					Customer[CustomerCounter].TotalOrder = Customer[CustomerCounter].TotalOrder-5; //To undo OrderCounter+6 (line 256) if user placed <5 orders
				}
			}
			CalculateBill(CustomerCounter, OrderCounter, &Customer[CustomerCounter]); //Function call CalculateBill in main to calculate the bills
			FinalReceipt(CustomerCounter, OrderCounter, &Customer[CustomerCounter]); //Function call FinalReceipt in main to display the final receipt for the user
		}
		else if (InputOption == 2)
		{
			TransactionRecord(TotalCustomer, CustomerCounter, OrderCounter, &Customer[CustomerCounter]); //Function call TransactionRecord in main to display the daily transactions
		}
		
		do
		{
			printf("Continue? (Y for Yes | N for No): "); //User prompt to enter input for continuation
			scanf(" %c", &Continue); //Stores user input into variable Continue
			fflush(stdin);
			if (toupper(Continue) != 'Y' && toupper(Continue) != 'N')
			{
				printf("Input entered is invalid, please retry.\n");
			}
		}while(toupper(Continue) != 'Y' && toupper(Continue) != 'N'); //Repeats do_while loop (line 327) if user did not input Y/y or N/n
		
		if (toupper(Continue) == 'N') //Indicates user wants to terminate the system
		{
			if ((TransactionPtr = fopen("TransactionRecord.txt", "w")) == NULL)
			{
				printf("File could not be opened.\n");
			}
			else //Perform file operation to save all of the transaction records into file TransactionRecord.txt before system is terminated
			{
				TotalCustomer = CustomerCounter;
				fprintf(TransactionPtr, "                            Transaction Record\n");
				fprintf(TransactionPtr, "-------------------------------------------------------------------------------------\n");
				fprintf(TransactionPtr, "Receipt No.          Order(s)                    Size                    Amount (RM)\n");
				fprintf(TransactionPtr, "-------------------------------------------------------------------------------------\n");
				for (CustomerCounter = 1; CustomerCounter <= TotalCustomer; CustomerCounter++)
				{
					fprintf(TransactionPtr, "     %03d     %s\n             %s\n", Customer[CustomerCounter].ReceiptNo, Customer[CustomerCounter].MemberStatus, Customer[CustomerCounter].MethodStatus);
					for (OrderCounter = 0; OrderCounter < Customer[CustomerCounter].TotalOrder; OrderCounter++)
					{
						fprintf(TransactionPtr, "             %-28s         %-2s                       %5.2f\n", Customer[CustomerCounter].OrderName[OrderCounter], Customer[CustomerCounter].OrderSize[OrderCounter], Customer[CustomerCounter].OrderBill[OrderCounter]);
					}
					fprintf(TransactionPtr, "                                                     Total                 %5.2f\n", Customer[CustomerCounter].TotalBill);
					fprintf(TransactionPtr, "                                               Service Tax                 %5.2f\n", Customer[CustomerCounter].ServiceTax);
					fprintf(TransactionPtr, "                                            Government Tax                 %5.2f\n", Customer[CustomerCounter].GovernmentTax);
					fprintf(TransactionPtr, "                                          Total (Tax Inc.)                 %5.2f\n", Customer[CustomerCounter].FinalBill);
					fprintf(TransactionPtr, "-------------------------------------------------------------------------------------\n");	
				}
				fclose(TransactionPtr);
			}
		}
	}while(toupper(Continue) == 'Y'); //Repeat the whole program if user decides to continue
} //End of main()

void DisplayMenu()
{
	printf("                         Korean Food (TKF) Restaurant\n");
	printf("------------------------------------------------------------------------------------\n");
	printf("                                        Non-Member                  Member\n");
	printf("------------------------------------------------------------------------------------\n");
	printf("               Menu                 Regular    Large          Regular     Large\n");
	printf("------------------------------------------------------------------------------------\n");
	printf("1) Bibimbap                          10.00     15.00          10%% off    15%% off\n");
	printf("2) 2 pc(s) Korean Fried Chicken       9.00     14.00          10%% off    15%% off\n");
	printf("3) Bulgogi                            8.50     13.50          10%% off    15%% off\n");
	printf("4) Japchae                            8.50     13.50          10%% off    15%% off\n");
	printf("5) Hameul Pajeon                      7.00     12.00          10%% off    15%% off\n");
	printf("------------------------------------------------------------------------------------\n");
	printf("*Orders can only be placed up to a maximum of 5 per customer.\n");
	
}

int OrderCart(int CustomerCounter, int OrderCounter, struct CustomerDetails *ptr)
{
	//Local variable declaration
	int OrderCounterPlaceholder; //Acts as a placeholder for OrderCounter as OrderCounter will be used in for loop (line 402)
	
	//Local variable initialization
	OrderCounterPlaceholder = OrderCounter; 
	Customer[CustomerCounter].TotalOrder = OrderCounter;
	
	printf("\nOrder cart:\n");
	printf("---------------------------------------------\n");
	printf(" No.   Order(s)                       Size\n");
	printf("---------------------------------------------\n");
	for (OrderCounter = 0; OrderCounter <= Customer[CustomerCounter].TotalOrder; OrderCounter++)
	{
		printf(" %d     %-28s     %-2s\n", OrderCounter+1, Customer[CustomerCounter].OrderName[OrderCounter], Customer[CustomerCounter].OrderSize[OrderCounter]);
	}
	printf("---------------------------------------------");
	
}

void FinalReceipt(int CustomerCounter, int OrderCounter, struct CustomerDetails *ptr)
{
	
	printf("-------------------------------------------------------------------------------------\n");
	printf("Receipt No.          Order(s)                    Size                    Amount (RM)\n");
	printf("-------------------------------------------------------------------------------------\n");
	printf("     %03d     %s\n             %s\n", Customer[CustomerCounter].ReceiptNo, Customer[CustomerCounter].MemberStatus, Customer[CustomerCounter].MethodStatus);
	for (OrderCounter = 0; OrderCounter < Customer[CustomerCounter].TotalOrder; OrderCounter++)
	{
		printf("             %-28s         %-2s                       %5.2f\n", Customer[CustomerCounter].OrderName[OrderCounter], Customer[CustomerCounter].OrderSize[OrderCounter], Customer[CustomerCounter].OrderBill[OrderCounter]);
	}
	printf("-------------------------------------------------------------------------------------\n");
	printf("                                                     Total                 %5.2f\n", Customer[CustomerCounter].TotalBill);
	printf("                                               Service Tax                 %5.2f\n", Customer[CustomerCounter].ServiceTax);
	printf("                                            Government Tax                 %5.2f\n", Customer[CustomerCounter].GovernmentTax);
	printf("                                          Total (Tax Inc.)                 %5.2f\n", Customer[CustomerCounter].FinalBill);
	printf("-------------------------------------------------------------------------------------\n");
	printf("\n");
	
}

void TransactionRecord(int TotalCustomer, int CustomerCounter, int OrderCounter, struct CustomerDetails *ptr)
{
	TotalCustomer = CustomerCounter; //Acts as a placeholder since CustomerCounter will be used in for loop (line 445)
	
	if (CustomerCounter == 0)
	{
		printf("No orders have been made yet.\n");
	}
	else
	{
		printf("                            Transaction Record\n");
		printf("-------------------------------------------------------------------------------------\n");
		printf("Receipt No.          Order(s)                    Size                    Amount (RM)\n");
		printf("-------------------------------------------------------------------------------------\n");
		for (CustomerCounter = 1; CustomerCounter <= TotalCustomer; CustomerCounter++)
		{
			printf("     %03d     %s\n             %s\n", Customer[CustomerCounter].ReceiptNo, Customer[CustomerCounter].MemberStatus, Customer[CustomerCounter].MethodStatus);
			for (OrderCounter = 0; OrderCounter < Customer[CustomerCounter].TotalOrder; OrderCounter++)
			{
				printf("             %-28s         %-2s                       %5.2f\n", Customer[CustomerCounter].OrderName[OrderCounter], Customer[CustomerCounter].OrderSize[OrderCounter], Customer[CustomerCounter].OrderBill[OrderCounter]);
			}
			printf("                                                     Total                 %5.2f\n", Customer[CustomerCounter].TotalBill);
			printf("                                               Service Tax                 %5.2f\n", Customer[CustomerCounter].ServiceTax);
			printf("                                            Government Tax                 %5.2f\n", Customer[CustomerCounter].GovernmentTax);
			printf("                                          Total (Tax Inc.)                 %5.2f\n", Customer[CustomerCounter].FinalBill);
			printf("-------------------------------------------------------------------------------------\n");	
		}
	}
}

int EditOrder(int CustomerCounter, int OrderCounter, struct CustomerDetails *ptr)
{
	//Local variable declaration
	int OrderCounterPlaceholder; //Acts as a placeholder for OrderCounter as OrderCounter will be be assigned to RemoveOrder (line 488)
	int RemoveOrder;
	int TotalOrder;
	
	//Local variable initialization
	OrderCounterPlaceholder = OrderCounter; 
	TotalOrder = OrderCounter+1;
	
	if (TotalOrder != 0)
	{
		do
		{
			printf("Remove which order? "); //User prompt to enter input for order removal
			scanf(" %d", &RemoveOrder); //Stores user input into variable RemoveOrder
			fflush(stdin);
			if (RemoveOrder > TotalOrder)
			{
				printf("There are only %d order(s).\n", TotalOrder);
			}
		}while(RemoveOrder > TotalOrder);	
		if (RemoveOrder <= TotalOrder)
		{
			if (OrderCounter > 0)
			{
				for (OrderCounter = RemoveOrder-1; OrderCounter < TotalOrder; OrderCounter++) //Replaces elements in index [OrderCounter] with elements in index [RemoveOrder-1]
				{
					Customer[CustomerCounter].OrderName[OrderCounter] = Customer[CustomerCounter].OrderName[OrderCounter+1]; //Replaces elements in index [OrderCounter] with elements in index [OrderCounter+1]
					Customer[CustomerCounter].OrderSize[OrderCounter] = Customer[CustomerCounter].OrderSize[OrderCounter+1];
					Customer[CustomerCounter].OrderBill[OrderCounter] = Customer[CustomerCounter].OrderBill[OrderCounter+1]; 
				}
				OrderCounter = OrderCounterPlaceholder-1; //Since an order has been removed, OrderCounterPlaceholder (OrderCounter's original value) is decreased by 1
				OrderCart(CustomerCounter, OrderCounter, &Customer[CustomerCounter]); //Function call OrderCart to display the order cart
				printf("\nNotice: Order has been successfully removed.\n");
			}
			else if (OrderCounter == 0)
			{
				printf("\nNotice: Order has been successfully removed, order cart is now empty.\n");
			}
		}
	}
}

float CalculateBill(int CustomerCounter, int OrderCounter, struct CustomerDetails *ptr)
{
	//Local variable declaration
	float ServiceTaxRate;
	float GovernmentTaxRate;
	
	//Local variable initialization
	ServiceTaxRate = 0.10;
	GovernmentTaxRate = 0.06;
	Customer[CustomerCounter].TotalBill = 0.00; 
	
	for (OrderCounter = 0; OrderCounter < Customer[CustomerCounter].TotalOrder; OrderCounter++) //For loop will continue based on the Customer[CustomerCounter].TotalOrder
	{
		Customer[CustomerCounter].TotalBill = Customer[CustomerCounter].TotalBill + Customer[CustomerCounter].OrderBill[OrderCounter];
	}
			
	if (Customer[CustomerCounter].MethodStatus == "Dine-In")
	{
		Customer[CustomerCounter].ServiceTax = Customer[CustomerCounter].TotalBill*ServiceTaxRate; //Calculate the service tax for Dine-In orders
	}
	else if (Customer[CustomerCounter].MethodStatus == "Takeaway")
	{
		Customer[CustomerCounter].ServiceTax = 0.00; //Assigns 0.00 for service tax of Takeaway orders
	}
	Customer[CustomerCounter].GovernmentTax = Customer[CustomerCounter].TotalBill*GovernmentTaxRate; //Calculate the service tax for both Dine-In or Takeaway orders
	Customer[CustomerCounter].FinalBill = Customer[CustomerCounter].TotalBill + Customer[CustomerCounter].ServiceTax + Customer[CustomerCounter].GovernmentTax; //Calculate the final bill for the user
	
}
