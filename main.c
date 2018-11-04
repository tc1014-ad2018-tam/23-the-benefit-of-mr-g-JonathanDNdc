/*
 * This program sells tickets to the show for the Benefit of Mr. G.
 * The venue has 400 rows, 50 seats on the sides and 100 on the center (200).
 * This program has an initial menu with the following options:
 * 1. Sell a ticket.
 * 2. Save sells data.
 * 3. Reports.
 * 4. Exit.
 *
 * When selling a ticket, the name, and the payment method will be saved.
 * Visa = 1.
 * MasterCard = 2.
 * American Express = 3.
 *
 *
 * Author: Jonathan Nuñez de Caceres.
 * Email: A01411277@itesm.mx
 * Date: 04/11/18
 */

#include <stdio.h> //Standard input/output library, with this we can request data to the user and print to the screen.
#include <string.h> //String library, in this library we can find strcpy.
#include <stdbool.h> //Standard bool library, with this we will be able to use true and false variables;


// Function to print the main menu.
void MainMenu() {
    printf("\nWelcome to the venue.\n");
    printf("Choose an option:\n");
    printf("1. Buy a ticket.\n");
    printf("2. Save sells data.\n");
    printf("3. Reports.\n");
    printf("4. Exit.\n");
}

// Function to print the reports menu.
void ReportsMenu() {
    printf("Choose an option:\n");
    printf("1. Total tickets sold.\n");
    printf("2. Total tickets sold per zone.\n");
    printf("3. Total income.\n");
    printf("4. Total income per zone.\n");
    printf("5. Occupation rate.\n");
    printf("6. Occupation rate per zone.\n");
}

// Function to print the zones.
void Zones() {
    printf("Zones:\n");
    printf("1. VIP: $100\n");
    printf("2. Platinum: $85\n");
    printf("3. Gold: $70\n");
    printf("4. Silver: $55\n");
    printf("5. Green: $45\n");
    printf("6. Yellow: $40\n");
    printf("7. Red: $30\n");
    printf("8. Sky Blue: $50\n");
    printf("9. Navy Blue: $35\n");
    printf("10. Deep Blue: $20\n");
}

// Function to print the payment methods.
void PayementMethod() {
    printf("Payment Methods:\n");
    printf("1. Visa\n");
    printf("2. MasterCard\n");
    printf("3. American Express\n");
}

// Struct data type for the seats.
struct Seats {
    char name[60];
    int paymethod;
    bool taken;
    int price;
}
// variable that holds all the seats.
seats[400][200];

// Function to initialize the file if it doesnt exists.
void InitializeFile(FILE *fp) {
    // Open file in binary write mode (If it does not exists, it creates it).
    fp = fopen("MrG.txt", "wb");

    // For each seat the values are initialized.
    for (int i = 0; i < 400; i++) {
        for (int j = 0; j < 200; j++) {
            strcpy(seats[i][j].name, "");
            seats[i][j].paymethod = 0;
            seats[i][j].taken = false;

            // The prices are given depending on the seat location.

            if (j < 50 || j > 149) {

                if (i < 100) {
                    seats[i][j].price = 50;
                } else if (i < 300) {
                    seats[i][j].price = 35;
                } else {
                    seats[i][j].price = 20;
                }

            } else {

                if (i < 5) {
                    seats[i][j].price = 100;
                } else if (i < 10) {
                    seats[i][j].price = 85;
                } else if (i < 50) {
                    seats[i][j].price = 70;
                } else if (i < 100) {
                    seats[i][j].price = 55;
                } else if (i < 250) {
                    seats[i][j].price = 45;
                } else if (i < 350) {
                    seats[i][j].price = 40;
                } else {
                    seats[i][j].price = 30;
                }

            }
        }
    }
    // The seat variable will be stored in the file.
    fwrite(&seats, sizeof(seats), 1, fp);
}

// Function to buy tickets.
void BuyTicket() {
    // Declaration of variables.
    int option;
    int row;
    int firstrow;
    int lastrow;
    int seat;
    char name[60];
    int paymethod;

    // Prints the Zones
    Zones();
    printf("Select the zone where you want to sit:\n");
    printf("Or any other number to cancel.\n");
    scanf("%d", &option);

    // For each zone the range of rows is established.
    switch (option) {
        case 1:
            firstrow = 1;
            lastrow = 5;
            break;
        case 2:
            firstrow = 6;
            lastrow = 10;
            break;
        case 3:
            firstrow = 11;
            lastrow = 50;
            break;
        case 4:
            firstrow = 51;
            lastrow = 100;
            break;
        case 5:
            firstrow = 101;
            lastrow = 250;
            break;
        case 6:
            firstrow = 251;
            lastrow = 350;
            break;
        case 7:
            firstrow = 351;
            lastrow = 400;
            break;
        case 8:
            firstrow = 1;
            lastrow = 100;
            break;
        case 9:
            firstrow = 101;
            lastrow = 300;
            break;
        case 10:
            firstrow = 301;
            lastrow = 400;
            break;
        default:
            printf("Returning to main menu.\n");
            return;
    }

    do {
        printf("Choose a row between %d-%d", firstrow, lastrow);
        scanf("%d", &row);
    } while (row < firstrow || row > lastrow);

    if (option > 7) {
        do {
            printf("Choose a seat between 1-50 or 151-200");
            scanf("%d", &seat);
        } while ((seat < 1 || seat > 50) && (seat < 151 || seat > 200));

    } else {
        do {
            printf("Choose a seat between 51-150");
            scanf("%d", &seat);
        } while (seat < 51 || seat > 150);
    }

    PayementMethod();
    printf("Select one payment method, or any other number to cancel.");
    scanf("%d", &paymethod);

    if (paymethod < 1 || paymethod > 3) {
        printf("Returning to main menu.\n");
        return;
    }

    printf("Enter your name:");
    fflush(stdin);
    fgets(name, sizeof(name), stdin);

    printf("Enter 0 to accept, anything else to cancel.\n");
    scanf("%d", &option);

    if (!option) {

        if (seats[row - 1][seat - 1].taken) {
            printf("This seat is taken.\n");
        } else {
            seats[row - 1][seat - 1].taken = true;
            seats[row - 1][seat - 1].paymethod = paymethod;
            strcpy(seats[row - 1][seat - 1].name, name);
            printf("Transaction confirmed.\n");
        }

    } else{
        printf("Returning to main menu.");
    }
}

// Function to count the total sales or total income.
int ZoneSoldSum(int firstrow, int lastrow, int firstseat, int lastseat, int sold) {
    int count = 0;
    int sales = 0;
    for (int i = firstrow - 1; i < lastrow; i++) {
        for (int j = firstseat - 1; j < lastseat; j++) {
            if (seats[i][j].taken) {
                count++;
                sales += seats[i][j].price;
            }
        }
    }
    // If the sold variable is equal to 1, this function returns the total sales.
    if (sold) {
        return count;
    }
    // Else the total income is returned.
    return sales;
}
// Function to establish the ranges and sum the totals.
int ZoneSold(int zone, int sold) {
    int count = 0;
    int firstrow;
    int lastrow;

    switch (zone) {
        case 1:
            firstrow = 1;
            lastrow = 5;
            break;
        case 2:
            firstrow = 6;
            lastrow = 10;
            break;
        case 3:
            firstrow = 11;
            lastrow = 50;
            break;
        case 4:
            firstrow = 51;
            lastrow = 100;
            break;
        case 5:
            firstrow = 101;
            lastrow = 250;
            break;
        case 6:
            firstrow = 251;
            lastrow = 350;
            break;
        case 7:
            firstrow = 351;
            lastrow = 400;
            break;
        case 8:
            firstrow = 1;
            lastrow = 100;
            break;
        case 9:
            firstrow = 101;
            lastrow = 300;
            break;
        case 10:
            firstrow = 301;
            lastrow = 400;
            break;
        default:
            firstrow = 1;
            lastrow = 200;
            break;
    }

    if (zone > 7) {
        count += ZoneSoldSum(firstrow, lastrow, 1, 50, sold);
        count += ZoneSoldSum(firstrow, lastrow, 151, 200, sold);
    } else {
        count += ZoneSoldSum(firstrow, lastrow, 51, 150, sold);
    }

    return count;
}

// Reports menu.
void Reports() {
    int option;
    int zone = 0;
    int count = 0;
    float rowsize;

    // Prints the report options.
    ReportsMenu();
    printf("Choose an option, or any other number to return:");
    scanf("%d", &option);

    switch (option) {
        case 1:
            count = ZoneSold(zone, 1);
            printf("Total tickets sold: %d", count);
            break;
        case 2:
            do {
                Zones();
                printf("Enter the zone you want info about:");
                scanf("%d", &zone);
            } while (zone < 1 || zone > 10);

            count = ZoneSold(zone, 1);
            printf("Total tickets sold in this zone: %d", count);
            break;
        case 3:
            count = ZoneSold(zone, 0);
            printf("Total income: $%d", count);
            break;
        case 4:
            do {
                Zones();
                printf("Enter the zone you want info about:");
                scanf("%d", &zone);
            } while (zone < 1 || zone > 10);

            count = ZoneSold(zone, 0);
            printf("Total income in this zone: $%d", count);
            break;
        case 5:
            // Count is equal to the total of tickets and the percentage is calculated.
            count = ZoneSold(zone, 1);
            printf("Occupation rate: %f%%", count * 100.0 / 80000);
            break;
        case 6:
            do {
                Zones();
                printf("Enter the zone you want info about:");
                scanf("%d", &zone);
            } while (zone < 1 || zone > 10);
            count = ZoneSold(zone, 1);

            // The size of the rows is established depending on the zone.
            switch (zone) {
                case 1:
                case 2:
                    rowsize = 5;
                    break;
                case 3:
                    rowsize = 40;
                    break;
                case 4:
                case 6:
                case 7:
                    rowsize = 50;
                    break;
                case 8:
                case 10:
                    rowsize = 100;
                    break;
                case 5:
                    rowsize = 150;
                    break;
                case 9:
                default:
                    rowsize = 200;
                    break;
            }
            printf("Occupation rate in this zone: %f%%", count / rowsize);
            break;
        default:
            printf("Returning to main menu");
            return;
    }


}
// This function updates the file with the array of the program.
void OverWritef(FILE *fp) {
    fp = fopen("MrG.txt", "wb");
    fwrite(&seats, sizeof(seats), 1, fp);
    fclose(fp);
}

int main() {

    // File pointer
    FILE *fp;
    int option;

    //Opens file in binary read mode.
    fp = fopen("mrg.txt", "rb");

    // If the file doesnt exists we initialize it.
    if (fp == NULL) {
        InitializeFile(fp);
    } else {
        // If the file exists the data will be stored in the program's array.
        while (fread(&seats, sizeof(seats), 1, fp));
    }
    // The file is closed.
    fclose(fp);


    do {
        //Print main menu.
        MainMenu();
        scanf("%d", &option);
        fflush(stdin);

        switch (option) {
            case 1:
                BuyTicket();
                break;
            case 2:
                OverWritef(fp);
                printf("Data saved.\n");
                break;
            case 3:
                Reports();
                break;
            case 4:
                OverWritef(fp);
                printf("\nGoodbye.\n");
                break;
            default:
                printf("\nNot valid.\n");
                break;
        }

    } while (option != 4);

    return 0;
}