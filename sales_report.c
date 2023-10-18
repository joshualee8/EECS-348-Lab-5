#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the number of months in a year as a constant
#define MONTHS 12

// Function to calculate the average of an array of numbers
double calculateAverage(double arr[], int size) {
    double sum = 0.0; // initialize sum to 0
    for (int i = 0; i < size; i++) {
        sum += arr[i]; // add the current element to the sum
    }
    return sum / size; // return the average
}

// Function to sort an array of numbers in descending order
void sortDescending(double arr[], int size) { 
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] < arr[j]) { // if the current element is less than the next element
                // swap the current element with the next element
                double temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Function to read monthly sales from the input file
int readSalesFromFile(double sales[]) { 
    FILE *inputFile = fopen("input.txt", "r"); // open the input file for reading
    if (inputFile == NULL) { // if the file could not be opened
        perror("Error opening input file"); // print an error message
        return 1; // return 1 to indicate an error
    }

    for (int i = 0; i < MONTHS; i++) {
        if (fscanf(inputFile, "%lf", &sales[i]) != 1) { // read the next sales value from the file
            fprintf(stderr, "Error reading sales data from input file\n"); // print an error message
            return 1; // return 1 to indicate an error
        }
    }
    fclose(inputFile); // close the input file
    return 0; // return 0 to indicate success
}

// Function to generate the sales report
void generateSalesReport(char *months[], double sales[]) { 
    printf("Monthly sales report for 2022:\n"); // print the header for the sales report
    printf("Month       Sales\n");
    for (int i = 0; i < MONTHS; i++) { // iterate over the months
        printf("%-10s $%.2lf\n", months[i], sales[i]); // print the sales for the current month
    }
}

// Function to calculate and display the sales summary
void displaySalesSummary(char *months[], double sales[]) {
    double minSales = sales[0]; // initialize the minimum sales to the sales for the first month
    double maxSales = sales[0]; // initialize the maximum sales to the sales for the first month
    double totalSales = sales[0]; // initialize the total sales to the sales for the first month
    for (int i = 1; i < MONTHS; i++) { // iterate over the remaining months
        if (sales[i] < minSales) { // if the sales for the current month are less than the minimum sales
            minSales = sales[i]; // set the minimum sales to the sales for the current month
        }
        if (sales[i] > maxSales) { // if the sales for the current month are greater than the maximum sales
            maxSales = sales[i]; // set the maximum sales to the sales for the current month
        }
        totalSales += sales[i]; // add the sales for the current month to the total sales
    }
    double averageSales = calculateAverage(sales, MONTHS); // calculate the average sales for the year 

    printf("\nSales summary:\n"); // print the header for the sales summary
    printf("Minimum sales: $%.2lf (%s)\n", minSales, months[0]); // print the minimum sales and the month in which they occurred
    printf("Maximum sales: $%.2lf (%s)\n", maxSales, months[MONTHS - 1]); // print the maximum sales and the month in which they occurred
    printf("Average sales: $%.2lf\n", averageSales); // print the average sales
}

// Function to calculate and display six-month moving averages
void displaySixMonthMovingAverages(char *months[], double sales[]) {
    printf("\nSix-Month Moving Average Report:\n"); // print the header for the six-month moving average report
    for (int i = 0; i <= MONTHS - 6; i++) { // iterate over the months for which a six-month moving average can be calculated
        double movingAverage = calculateAverage(&sales[i], 6); // calculate the six-month moving average for the current month
        printf("%-10s - %-10s $%.2lf\n", months[i], months[i + 5], movingAverage); // print the six-month moving average for the current month
    }
}

// Function to sort and display the sales report in descending order
void displaySalesReportDescending(char *months[], double sales[]) {
    // Sort the sales and months arrays in descending order based on the sales values
    for (int i = 0; i < MONTHS - 1; i++) { 
        for (int j = i + 1; j < MONTHS; j++) { 
            if (sales[i] < sales[j]) { // if the current element is less than the next element
                // swap the current element with the next element
                double temp = sales[i];
                sales[i] = sales[j];
                sales[j] = temp;
                char *temp2 = months[i];
                months[i] = months[j];
                months[j] = temp2;
            }
            else if (sales[i] == sales[j]) { // if the current element is equal to the next element
                if (strcmp(months[i], months[j]) > 0) { // if the current month is greater than the next month
                    // swap the current month with the next month
                    char *temp = months[i]; 
                    months[i] = months[j];
                    months[j] = temp;
                }
            }
        }
    }
    
    printf("\nSales Report (Highest to Lowest):\n"); // print the header for the sales report
    printf("Month       Sales\n");
    for (int i = 0; i < MONTHS; i++) { // iterate over the months
        printf("%-10s $%.2lf\n", months[i], sales[i]); // print the sales for the current month
    }
}

int main() {
    // declare an array to store the sales for each month
    double sales[MONTHS];
    // declare an array of strings to store the names of the months
    char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    if (readSalesFromFile(sales) != 0) { // read the sales from the input file into the sales array and check for errors
        return 1; // return 1 to indicate an error
    }
    
    generateSalesReport(months, sales); // generate the sales report
    displaySalesSummary(months, sales); // display the sales summary
    displaySixMonthMovingAverages(months, sales); // display the six-month moving averages
    displaySalesReportDescending(months, sales); // display the sales report in descending order
    return 0; // return 0 to indicate success
}
