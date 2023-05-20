#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure to store all the booking details provided by the customers
struct bookings
{
	char name[30];
	char age[10];
	char passport[20];
	char phonenumber[20];
	char email[30];
	char roomnumber[10];
	char days[10];
	char credcard[25];
	char code[3];
	char password[20];
	char indate[15];
	char outdate[15];
	char status[10];
}book;

//forward declarations of all the functions used in the program
void exitfunc();
void menu();
void admin();
void admin_menu();
void admin_roombookings();
void admin_personbookings();
void admin_allbookings();
void newcustomer();
void newcustomer_detials();
void newcustomer_availability();
void newcustomer_booking();
void registeredcustomer();
void registeredcustomer_menu(char passport[30], char password[30]);
void registeredcustomer_details(char passport[30], char password[30]);
void registeredcustomer_receipt(char passport[30], char password[30]);
void registeredcustomer_extend(char passport[30], char password[30]);
void registeredcustomer_edit(char passport[30], char password[30]);
void registeredcustomer_checkout(char passport[30], char password[30]);

int main()
{
	menu();
	return 0;
}

//function to give the user the option to exit
void exitfunc()
{
	char exitloop[10];
	printf("Enter 0 to Exit: ");
	scanf("%s", &exitloop);
	while (strcmp(exitloop, "0") != 0)		//checks if the user input is correct
	{
		printf("Incorrect Input, Please Try Again\n");
		printf("Enter 0 to Exit: ");
		scanf("%s", &exitloop);
	}
}

//function to display the main menu of the program
void menu()
{
	int menuoptions, exitloop = 0;
	while (exitloop != 1)
	{
		printf("\nWELCOME TO GRAND PLAZA HOTEL\n");
		printf("----------------------------\n");
		printf("Please choose what you are here for. Your options are:\n1. New Customer\n2. Registered Customer\n3. Admnin\n4. Exit\n");
		printf("Please select one of the given options: ");
		scanf("%d", &menuoptions);
		switch (menuoptions)		//takes the user to their selected option
		{
		case  1:
			newcustomer();
			break;
		case 2:
			registeredcustomer();
			break;
		case 3:
			admin();
			break;
		case 4:
			printf("\nThank You For Visiting\n");
			exitloop = 1;
			break;
		default:
			printf("Incorrect Input, Please Try Again\n");
		}
	}
}

//function to let admin sign in with correct credentials
void admin()
{
	int exitloop = 0;
	char username[20], password[20];
	printf("\nWelcome Admin, Please enter your username and password to continue.\n");
	while (exitloop != 1)
	{
		printf("Enter your username: ");
		scanf("%s", &username);
		printf("Enter your password: ");
		scanf("%s", &password);
		if (strcmp(username, "admin") == 0 && strcmp(password, "12345") == 0)		//checks if the admin username and password are correct
		{
			admin_menu();
			exitloop = 1;
		}
		else
		{
			printf("Incorrect username or password\n");
			printf("Enter 0 to Retry or 1 to Exit: ");
			scanf("%d", &exitloop);

			while (exitloop != 0 && exitloop != 1)
			{
				printf("Incorrect Input, Please Try Again\n");
				printf("Enter 0 to Retry or 1 to Exit: ");
				scanf("%d", &exitloop);
			}

		}
	}
}

//function to display admin menu
void admin_menu()
{
	int adminchoice, exitloop = 0;
	while (exitloop == 0)
	{
		printf("\nYour options are:\n1. View All Bookings\n2. View A Specific Person Bookings\n3. View A Specific Room Bookings\n4. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &adminchoice);
		switch (adminchoice)		//takes admin to their selected option
		{
		case 1:
			admin_allbookings();
			break;
		case 2:
			admin_personbookings();
			break;
		case 3:
			admin_roombookings();
			break;
		case 4:
			exitloop = 1;
			break;
		default:
			printf("Incorrect Input, Please Try Again\n");
		}
	}
}

//function to let admin view bookings for a specific room
void admin_roombookings()
{
	FILE* fp;
	char line[1024], roomno[30];
	printf("Enter the room number: ");
	scanf("%s", &roomno);
	fp = fopen("Bookings.txt", "r");
	if (fp == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
	printf(fgets(line, sizeof(line), fp));
	while (fgets(line, sizeof(line), fp))		//reads the text file line by line
	{
		sscanf(line, "%30[^\t] %s %s %s %s %s %s %s %s %s %s", book.name, book.age, book.passport, book.phonenumber, book.email, book.roomnumber, book.days, book.indate, book.outdate, book.password, book.status);		//sorts the data from the text file line
		if (strcmp(book.roomnumber, roomno) == 0)		//compares the room number entered with the room number in the line to print it
		{
			printf(line);
		}
	}
	fclose(fp);
	exitfunc();
}

//function to let admin view bookings for a specific person
void admin_personbookings()
{
	FILE* fp;
	char line[1024], pno[30];
	printf("Enter the passport number: ");
	scanf("%s", &pno);
	fp = fopen("Bookings.txt", "r");
	if (fp == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
	printf(fgets(line, sizeof(line), fp));
	while (fgets(line, sizeof(line), fp))
	{
		if (strstr(line, pno) != NULL)		//checks for the passport number entered in each line
		{
			printf(line);
		}
	}
	fclose(fp);
	exitfunc();
}

//function to let admin view all the bookings
void admin_allbookings()
{
	FILE* fp;
	char line[1024];
	fp = fopen("Bookings.txt", "r");
	if (fp == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
	while (fgets(line, sizeof(line), fp))		//reads and prints each line
	{
		printf(line);
	}
	fclose(fp);
	exitfunc();
}

//function display the new customer menu
void newcustomer()
{
	int ncchoice, exitloop = 0;
	while (exitloop != 1)
	{
		printf("\nWelcome Customer, please choose one of the following options for what you would like to do.\n");
		printf("1. View Room Details\n2. Check For Available Rooms\n3. Book A Room\n4. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &ncchoice);
		switch (ncchoice)		//takes the user to their selected option
		{
		case 1:
			newcustomer_detials();
			break;
		case 2:
			newcustomer_availability();
			break;
		case 3:
			newcustomer_booking();
			break;
		case 4:
			exitloop = 1;
			break;
		default:
			printf("Incorrect Input, Please Try Again\n");
		}
	}
}

//function to let new customer view room detials
void newcustomer_detials()
{
	char line[1024];
	FILE* fp;
	fp = fopen("RoomList.txt", "r");
	if (fp == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
	while (fgets(line, sizeof(line), fp))		//reads and prints the room details stored in the file
	{
		printf(line);
	}
	fclose(fp);
	exitfunc();
}

//function to let new customer check for available rooms
void newcustomer_availability()
{
	FILE* fp;
	fp = fopen("AvailableRooms.txt", "r");
	if (fp == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
	char line[1024];
	printf("\nThe available rooms are:\n");
	while (fgets(line, sizeof(line), fp))		//reads and prints the available rooms stored in the file
	{
		printf(line);
	}
	fclose(fp);
	exitfunc();
}

//function to let new customer book a room
void newcustomer_booking()
{
	int introom, intdays, available, confirm, correct = 0, pcorrect = 0;
	char line[1024], line2[1024], filename[30], p1[30], p2[30];
	float  amount = 0, taxamount = 0, tourismtax = 0, totalamount = 0;
	printf("Please enter your details\n");		//asks customer for their detials
	while (getchar() != '\n');
	printf("Enter your name: ");
	gets(book.name);
	printf("Enter your age: ");
	scanf("%s", book.age);
	printf("Enter your passport number: ");
	scanf("%s", book.passport);
	strcpy(filename, book.passport);
	printf("Enter your phone number: ");
	scanf("%s", book.phonenumber);
	printf("Enter your email: ");
	scanf("%s", book.email);

	while (correct == 0)
	{
		printf("Enter the room number you would like to book: ");
		scanf("%s", book.roomnumber);
		available = 0;
		FILE* fp1;
		fp1 = fopen("AvailableRooms.txt", "r");
		if (fp1 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
		while (fgets(line, sizeof(line), fp1))
		{
			if (strstr(line, book.roomnumber) != NULL)		//checks if the room number is present in the available rooms file
			{
				available = 1;
			}
		}
		fclose(fp1);
		if (available == 1)
		{
			introom = atoi(book.roomnumber);
			if (introom == 101 || introom == 201)		//details for the selected room
			{
				printf("You have selected the Superior Room\nPrice: RM180\n");
				amount = 180;
				correct = 1;
			}
			else if (introom == 102 || introom == 202)
			{
				printf("You have selected the Deluxe Room\nPrice: RM200\n");
				amount = 200;
				correct = 1;
			}
			else if (introom == 103 || introom == 203)
			{
				printf("You have selected the Studio Room\nPrice: RM250\n");
				amount = 250;
				correct = 1;
			}
			else if (introom == 104 || introom == 204)
			{
				printf("You have selected the Executive Suite\nPrice: RM400\n");
				amount = 400;
				correct = 1;
				break;
			}
			else if (introom == 105 || introom == 205)
			{
				printf("You have selected the Deluxe Suite\nPrice: RM500\n");
				amount = 500;
				correct = 1;
			}
			else
			{
				printf("The room you have chosen does not exist, Please try again\n");
			}
		}
		else
		{
			printf("The room you have chosen either does not exist or has already Booked, Please choose a different room\n");
		}
	}

	printf("Enter the number of days of your stay: ");
	scanf("%s", book.days);
	intdays = atoi(book.days);
	printf("Enter the check in date (DD/MM/YYYY): ");
	scanf("%s", book.indate);
	printf("Enter the check out date (DD/MM/YYYY): ");
	scanf("%s", book.outdate);
	printf("Enter your credit card number: ");
	scanf("%s", book.credcard);
	printf("Enter the 3 digit security code: ");
	scanf("%s", book.code);


	while (pcorrect == 0)
	{
		printf("Enter a password for your account: ");
		scanf("%s", p1);
		printf("Please enter the password again for verification: ");
		scanf("%s", p2);
		if (strcmp(p1, p2) != 0)		//validates password
		{
			printf("The Passwords Don't Match, Please Try Again\n");
		}
		else
		{
			strcpy(book.password, p1);
			pcorrect = 1;
		}
	}
	strcpy(book.status, "Initial");
	taxamount = amount + (amount / 10);		//calculates the taxes
	tourismtax = taxamount + 10;
	totalamount = tourismtax * intdays;

	printf("\nYour details are:\n");		//displays details for confirmation
	printf("%-30s\t%-10s\t%-20s\t%-20s\t%-25s\t%-10s\t%-10s\t%-15s\t%-15s\t%-20s\n", "NAME:", "AGE:", "PASSPORT NO:", "PHONE NO:", "EMAIL:", "ROOM NO:", "DAYS:", "CHECK IN:", "CHECK OUT:", "PASSWORD:");
	printf("%-30s\t%-10s\t%-20s\t%-20s\t%-25s\t%-10s\t%-10s\t%-15s\t%-15s\t%-20s\n", book.name, book.age, book.passport, book.phonenumber, book.email, book.roomnumber, book.days, book.indate, book.outdate, book.password);
	printf("Press 1 to Confirm or 0 to Go Back: ");
	scanf("%d", &confirm);
	while (confirm != 1 && confirm != 0)
	{
		printf("Incorrect Input, Please Try Again\n");
		printf("Press 1 to Confirm or 0 to Exit: ");
		scanf("%d", &confirm);
	}
	if (confirm == 1)
	{
		FILE* fp2, * fp3;
		fp2 = fopen("Bookings.txt", "a");
		if (fp2 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
		fprintf(fp2, "%-30s\t%-10s\t%-20s\t%-20s\t%-25s\t%-10s\t%-10s\t%-15s\t%-15s\t%-20s\t%-10s\n", book.name, book.age, book.passport, book.phonenumber, book.email, book.roomnumber, book.days, book.indate, book.outdate, book.password, book.status);		//writes details into file for all bookings
		fclose(fp2);
		fp3 = fopen(strcat(filename, ".txt"), "a");
		if (fp3 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
		fprintf(fp3, "%-30s\t%-10s\t%-20s\t%-20s\t%-25s\t%-10s\t%-10s\t%-15s\t%-15s\t%-20s\t%-10s\n", "NAME:", "AGE:", "PASSPORT NO:", "PHONE NO:", "EMAIL:", "ROOM NO:", "DAYS:", "CHECK IN:", "CHECK OUT:", "PASSWORD:", "STATUS:");
		fprintf(fp3, "%-30s\t%-10s\t%-20s\t%-20s\t%-25s\t%-10s\t%-10s\t%-15s\t%-15s\t%-20s\t%-10s\n", book.name, book.age, book.passport, book.phonenumber, book.email, book.roomnumber, book.days, book.indate, book.outdate, book.password, book.status);		//writes details in a file specifically made for the user which will be deleted when they leave
		fclose(fp3);
		printf("Your Booking Has Been Completed Successfully!\n");
		printf("\n\nReceipt:\n");		//prints a receipt for the booking
		printf("\nGRAND PLAZA HOTEL\n\nName: %s\nPassport Number: %s\nRoom Booked: %s\nRoom Cost: RM%.2f Per Night\nTax: 10 Percent\nTourism Tax: RM10 Per Night\nDuration Of Stay: %s\nCheck In Date: %s\nCheck Out Date: %s\nTotal Cost: RM%.2f\n\nThank You For Booking A Room With Us!\n", book.name, book.passport, book.roomnumber, amount, book.days, book.indate, book.outdate, totalamount);

		FILE* fp4, * fp5, * fp6;
		fp4 = fopen("AvailableRooms.txt", "r");
		if (fp4 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
		while (fgets(line2, sizeof(line2), fp4))		//transfers the room selected from available rooms file to booked rooms file
		{
			if (strstr(line2, book.roomnumber) != NULL)
			{
				fp5 = fopen("BookedRooms.txt", "a");
				if (fp5 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
				fputs(line2, fp5);
				fclose(fp5);
			}
			else
			{
				fp6 = fopen("AvailableRooms2.txt", "a");
				if (fp6 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
				fputs(line2, fp6);
				fclose(fp6);
			}
		}
		fclose(fp4);
		remove("AvailableRooms.txt");
		rename("AvailableRooms2.txt", "AvailableRooms.txt");

		exitfunc();
	}
}

//function to let customers with a room sign in with the right credentials
void registeredcustomer()
{
	char pno[30], pass[30], filename[30], line[1024];
	int exitloop, call1, call2, correct = 0;
	while (correct == 0)
	{
		call1 = 0;
		call2 = 0;
		correct = 0;
		printf("Enter your passport number: ");		//user enters passport and password numbers
		scanf("%s", &pno);
		printf("Enter your password: ");
		scanf("%s", &pass);
		strcpy(filename, pno);

		FILE* fp1, * fp2;
		fp1 = fopen("Bookings.txt", "r");
		if (fp1 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
		while (fgets(line, sizeof(line), fp1))
		{
			if (strstr(line, pno) != NULL && strstr(line, pass) != NULL)		//looks for the passport number and password entered in each line
			{
				call1 = 1;
				break;
			}
		}
		fclose(fp1);
		fp2 = fopen(strcat(filename, ".txt"), "r");
		if (fp2 != NULL)		//checks if the file made specifically for the user still exists, if not means they have checked out
		{
			call2 = 1;
			fclose(fp2);
		}
		if (call1 == 1 && call2 == 1)		//if both the conditions are met, takes user to registered customer menu
		{
			registeredcustomer_menu(pno, pass);
			correct = 1;
		}
		else if (call1 == 1 && call2 == 0)
		{
			printf("No such entry found, You may have already checked out\n");
		}
		else
		{
			printf("No such entry found\n");
		}
		if (correct == 1)
		{
			break;
		}
		printf("Press 1 to Retry or 0 to Exit: ");
		scanf("%d", &exitloop);
		while (exitloop != 0 && exitloop != 1)
		{
			printf("Incorrect Input, Please Try Again\n");
			printf("Press 1 to Retry or 0 to Exit: ");
			scanf("%d", &exitloop);
		}
		if (exitloop == 0)
		{
			correct = 1;
		}
	}
}

//function to display the menu for registered customers
void registeredcustomer_menu(char passport[30], char password[30])
{
	int rcchoice, exitloop = 0;
	while (exitloop != 1)
	{
		printf("\nWelcome back Customer, Please choose what you would like to do.\n");
		printf("1. View Booking Details\n2. View Receipt\n3. Extend Stay\n4. Edit Booking Details\n5. Check Out\n6. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &rcchoice);
		switch (rcchoice)		//takes user to their selected option
		{
		case 1:
			registeredcustomer_details(passport, password);
			break;
		case 2:
			registeredcustomer_receipt(passport, password);
			break;
		case 3:
			registeredcustomer_extend(passport, password);
			break;
		case 4:
			registeredcustomer_edit(passport, password);
			exitloop = 1;
			break;
		case 5:
			registeredcustomer_checkout(passport, password);
			exitloop = 1;
			break;
		case 6:
			exitloop = 1;
			break;
		default:
			printf("Incorrect Input, Please Try Again\n");
		}
	}
}

//function to let the customer view their booking details
void registeredcustomer_details(char passport[30], char password[30])
{
	char filename[30];
	strcpy(filename, passport);
	FILE* fp;
	fp = fopen(strcat(filename, ".txt"), "r");
	if (fp == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
	char line[1024];
	while (fgets(line, sizeof(line), fp))		//prints all the details from the user's file
	{
		printf(line);
	}
	fclose(fp);
	exitfunc();
}

//function to show the customer their receipt
void registeredcustomer_receipt(char passport[30], char password[30])
{
	int intdays, introom, days = 0;
	float amount, taxamount, tourismtax, totalamount;
	char line[1024];
	FILE* fp;
	fp = fopen("Bookings.txt", "r");
	if (fp == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
	while (fgets(line, sizeof(line), fp))
	{
		if (strstr(line, passport) != NULL && strstr(line, password) != NULL)		//looks for lines with the users details in the users file
		{
			sscanf(line, "%25[^\t] %s %s %s %s %s %s %s %s %s %s", book.name, book.age, book.passport, book.phonenumber, book.email, book.roomnumber, book.days, book.indate, book.outdate, book.password, book.status);
			intdays = atoi(book.days);
			days += intdays;
		}
	}
	fclose(fp);
	introom = atoi(book.roomnumber);
	if (introom == 101 || introom == 201)		//looks for the users room number
	{
		amount = 180;
	}
	else if (introom == 102 || introom == 202)
	{
		amount = 200;
	}
	else if (introom == 103 || introom == 203)
	{
		amount = 250;
	}
	else if (introom == 104 || introom == 204)
	{
		amount = 400;
	}
	else
	{
		amount = 500;
	}

	taxamount = amount + (amount / 10);
	tourismtax = taxamount + 10;
	totalamount = tourismtax * days;
	printf("\n\nReceipt:\n");		//displays a receipt to user
	printf("\nGRAND PLAZA HOTEL\n\nName: %s\nPassport Number: %s\nRoom Booked: %s\nRoom Cost: RM%.2f Per Night\nTax: 10 Percent\nTourism Tax: RM10 Per Night\nDuration Of Stay: %d\nCheck In Date: %s\nCheck Out Date: %s\nTotal Cost: RM%.2f\n\n", book.name, book.passport, book.roomnumber, amount, days, book.indate, book.outdate, totalamount);
	exitfunc();
}

//function to let the customer extend their stay
void registeredcustomer_extend(char passport[30], char password[30])
{
	int introom, intdays, confirm;
	float amount, taxamount, tourismtax, totalamount;
	char line[1024], filename[30];
	FILE* fp1;
	fp1 = fopen("Bookings.txt", "r");
	if (fp1 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
	while (fgets(line, sizeof(line), fp1))
	{
		if (strstr(line, passport) != NULL && strstr(line, password) != NULL)		//gets all the user details from the bookings file
		{
			sscanf(line, "%25[^\t] %s %s %s %s %s %s %s %s %s %s", book.name, book.age, book.passport, book.phonenumber, book.email, book.roomnumber, book.days, book.indate, book.outdate, book.password, book.status);
		}
	}
	fclose(fp1);

	printf("How many days would you like to extend your booking for?: ");		//gets details from the user
	scanf("%s", book.days);
	intdays = atoi(book.days);
	printf("Enter new check out date (DD/MM/YYYY): ");
	scanf("%s", book.outdate);

	introom = atoi(book.roomnumber);
	if (introom == 101 || introom == 201)
	{
		amount = 180;
	}
	else if (introom == 102 || introom == 202)
	{
		amount = 200;
	}
	else if (introom == 103 || introom == 203)
	{
		amount = 250;
	}
	else if (introom == 104 || introom == 204)
	{
		amount = 400;
	}
	else
	{
		amount = 500;
	}

	printf("Enter your credit card number: ");
	scanf("%s", book.credcard);
	printf("Enter the 3 digit security code: ");
	scanf("%s", book.code);

	taxamount = amount + (amount / 10);
	tourismtax = taxamount + 10;
	totalamount = tourismtax * intdays;

	printf("Press 1 to Confirm or 0 to Exit: ");
	scanf("%d", &confirm);
	while (confirm != 1 && confirm != 0)
	{
		printf("Incorrect Input, Please Try Again\n");
		printf("Press 1 to Confirm or 0 to Exit: ");
		scanf("%d", &confirm);
	}
	if (confirm == 1)
	{
		strcpy(book.status, "Extention");
		FILE* fp2, * fp3;
		fp2 = fopen("Bookings.txt", "a");
		if (fp2 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
		fprintf(fp2, "%-30s\t%-10s\t%-20s\t%-20s\t%-25s\t%-10s\t%-10s\t%-15s\t%-15s\t%-20s\t%-10s\n", book.name, book.age, book.passport, book.phonenumber, book.email, book.roomnumber, book.days, book.indate, book.outdate, password, book.status);		//writes extention details to the text file
		fclose(fp2);
		strcpy(filename, passport);
		fp3 = fopen(strcat(filename, ".txt"), "a");
		if (fp3 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
		fprintf(fp3, "%-30s\t%-10s\t%-20s\t%-20s\t%-25s\t%-10s\t%-10s\t%-15s\t%-15s\t%-20s\t%-10s\n", book.name, book.age, book.passport, book.phonenumber, book.email, book.roomnumber, book.days, book.indate, book.outdate, password, book.status);		//writes extention details to users file
		fclose(fp3);
		printf("Your Booking Has Been Extended Successfully!\n");
		printf("\n\nReceipt:\n");		//prints a receipt for the extention
		printf("\nGRAND PLAZA HOTEL\n\nName: %s\nPassport Number: %s\nRoom Booked: %s\nRoom Cost: RM%.2f Per Night\nTax: 10 Percent\nTourism Tax: RM10 Per Night\nDuration Of Stay: %s\nCheck In Date: %s\nCheck Out Date: %s\nTotal Cost: RM%.2f\n\nThank You For Extending Your Stay With Us!\n", book.name, book.passport, book.roomnumber, amount, book.days, book.indate, book.outdate, totalamount);
		exitfunc();
	}
}

//function to let a customer edit their booking details
void registeredcustomer_edit(char passport[30], char password[30])
{
	int editchoice, exitloop = 0, confirm;
	char line[1024], line2[1024], filename[30], filename2[30];
	FILE* fp1, * fp2, * fp3, * fp4, * fp5;
	struct bookings book2 = { 0 };
	fp1 = fopen("Bookings.txt", "r");
	if (fp1 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
	while (fgets(line, sizeof(line), fp1))
	{
		if (strstr(line, passport) != NULL && strstr(line, password) != NULL)		//looks for the user details and stores it
		{
			sscanf(line, "%25[^\t] %s %s %s %s %s %s %s %s %s %s", book.name, book.age, book.passport, book.phonenumber, book.email, book.roomnumber, book.days, book.indate, book.outdate, book.password, book.status);
			break;
		}
	}
	fclose(fp1);
	while (exitloop != 1)
	{
		printf("\nWhich detail of yours would you like to edit?\n1. Name\n2. Age\n3. Passport Number\n4. Phone Number\n5. Email\n6. Password\n7. Confirm Changes\n8. Exit\n");
		printf("Please choose one of the options: ");
		scanf("%d", &editchoice);
		switch (editchoice)		//takes the user to the details they want to edit
		{
		case 1:
			while (getchar() != '\n');
			printf("Name: %s\n", book.name);
			printf("Enter new name: ");
			gets(book.name);
			break;
		case 2:
			printf("Age: %s\n", book.age);
			printf("Enter new age: ");
			scanf("%s", book.age);
			break;
		case 3:
			printf("Passport Number: %s\n", book.passport);
			printf("Enter new passport number: ");
			scanf("%s", book.passport);
			break;
		case 4:
			printf("Phone Number: %s\n", book.phonenumber);
			printf("Enter new phone number: ");
			scanf("%s", book.phonenumber);
			break;
		case 5:
			printf("Email: %s\n", book.email);
			printf("Enter new email: ");
			scanf("%s", book.email);
			break;
		case 6:
			printf("Password: %s\n", book.password);
			printf("Enter new password: ");
			scanf("%s", book.password);
			break;
		case 7:
			printf("Are you sure you want to save the changes?\n");
			printf("Press 1 to Confirm or 0 to Exit: ");
			scanf("%d", &confirm);
			while (confirm != 1 && confirm != 0)
			{
				printf("Incorrect Input, Please Try Again\n");
				printf("Press 1 to Confirm or 0 to Exit: ");
				scanf("%d", &confirm);
			}
			if (confirm == 1)		//makes changes only if the user wants to confirm
			{
				strcpy(filename, passport);
				fp2 = fopen("Bookings.txt", "r");
				if (fp2 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
				fp3 = fopen("Bookings2.txt", "a");
				if (fp3 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
				fp4 = fopen(strcat(filename, ".txt"), "w");
				if (fp4 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
				fprintf(fp4, "%-30s\t%-10s\t%-20s\t%-20s\t%-25s\t%-10s\t%-10s\t%-15s\t%-15s\t%-20s\t%-10s\n", "NAME:", "AGE:", "PASSPORT NO:", "PHONE NO:", "EMAIL:", "ROOM NO:", "DAYS:", "CHECK IN:", "CHECK OUT:", "PASSWORD:", "STATUS:");
				fclose(fp4);
				fp5 = fopen(filename, "a");
				if (fp5 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
				while (fgets(line2, sizeof(line2), fp2))
				{
					if (strstr(line2, passport) != NULL && strstr(line2, password) != NULL)		//checks for the lines that have the users details
					{
						sscanf(line2, "%25[^\t] %s %s %s %s %s %s %s %s %s %s", book2.name, book2.age, book2.passport, book2.phonenumber, book2.email, book2.roomnumber, book2.days, book2.indate, book2.outdate, book2.password, book2.status);
						fprintf(fp3, "%-30s\t%-10s\t%-20s\t%-20s\t%-25s\t%-10s\t%-10s\t%-15s\t%-15s\t%-20s\t%-10s\n", book.name, book.age, book.passport, book.phonenumber, book.email, book.roomnumber, book2.days, book.indate, book2.outdate, book.password, book2.status);		//writes updated details to bookings file
						fprintf(fp5, "%-30s\t%-10s\t%-20s\t%-20s\t%-25s\t%-10s\t%-10s\t%-15s\t%-15s\t%-20s\t%-10s\n", book.name, book.age, book.passport, book.phonenumber, book.email, book.roomnumber, book2.days, book.indate, book2.outdate, book.password, book2.status);		//writes updated details to the users files
					}
					else
					{
						fputs(line2, fp3);
					}
				}
				fclose(fp5);
				fclose(fp3);
				fclose(fp2);
				remove("Bookings.txt");
				rename("Bookings2.txt", "Bookings.txt");
				strcpy(filename2, book.passport);
				strcat(filename2, ".txt");
				rename(filename, filename2);
				printf("The Changes Have Been Made Succesfully!\n");
				exitloop = 1;
			}
			break;
		case 8:
			exitloop = 1;
			break;
		default:
			printf("Incorrect Input, Please Try Again\n");
		}
	}
}

//function to let the customer check out from their hotel room
void registeredcustomer_checkout(char passport[30], char password[30])
{
	int confirm;
	printf("Are you sure you want to Check Out? Press 1 to Confirm or 0 to Exit: ");
	scanf("%d", &confirm);
	while (confirm != 0 && confirm != 1)
	{
		printf("Incorrect Input, Please Try Again\n");
		printf("Press 1 to Confirm or 0 to Exit: ");
		scanf("%d", &confirm);
	}
	if (confirm == 1)		//checks out only when the user gives confirmation
	{
		FILE* fp1, * fp2, * fp3, * fp4, * fp5;
		char line[1024], line2[1024];
		fp1 = fopen("Bookings.txt", "r");
		if (fp1 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
		while (fgets(line, sizeof(line), fp1))
		{
			if (strstr(line, passport) != NULL && strstr(line, password) != NULL)		//stores all the users details
			{
				sscanf(line, "%25[^\t] %s %s %s %s %s %s %s %s %s %s", book.name, book.age, book.passport, book.phonenumber, book.email, book.roomnumber, book.days, book.indate, book.outdate, book.password, book.status);
				break;
			}
		}
		fclose(fp1);
		fp2 = fopen("BookedRooms.txt", "r");
		if (fp2 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
		while (fgets(line2, sizeof(line2), fp2))
		{
			if (strstr(line2, book.roomnumber) != NULL)		//transfers the room the user booked back to the available rooms file
			{
				fp3 = fopen("AvailableRooms.txt", "a");
				if (fp3 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
				fputs(line2, fp3);
				fclose(fp3);
			}
			else
			{
				fp4 = fopen("BookedRooms2.txt", "a");
				if (fp4 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
				fputs(line2, fp4);
				fclose(fp4);
			}
		}
		fclose(fp2);
		fp5 = fopen("Bookings.txt", "a");
		if (fp5 == NULL) { printf("Error, file couldn't be opened\n"); exit(0); }
		strcpy(book.status, "Checkout");
		fprintf(fp5, "%-30s\t%-10s\t%-20s\t%-20s\t%-25s\t%-10s\t%-10s\t%-15s\t%-15s\t%-20s\t%-10s\n", book.name, book.age, book.passport, book.phonenumber, book.email, book.roomnumber, book.days, book.indate, book.outdate, book.password, book.status);
		fclose(fp5);
		remove("BookedRooms.txt");
		rename("BookedRooms2.txt", "BookedRooms.txt");
		remove(strcat(passport, ".txt"));		//deletes the file made specifically for the user
		printf("You Have Checked Out Successfully!\n");
		exitfunc();
	}
}