#include <stdlib.h>
#include <stdio.h>
#include "readfile.h"

//Function to open file
int open_file(char *filename){
    FILE *reads;
    reads = fopen(filename, "r");
    if (reads==NULL) {
        return -1;
    }
    else{
      return 0;
    }
}

//Function to read firstname from user
int read_firstName(char* firstName){
    printf("Enter the first name of the employee: ");
    scanf("%s", firstName);
    return 0;
}

//Function to read lastname from user
int read_lastName(char* lastName){
    printf("Enter the last name of the employee: ");
    scanf("%s", lastName);
    return 0;
}

//Function to read salary from user
int read_salary(unsigned int* id){
    printf("Enter employee's salary (30000 to 150000): ");
    scanf("%d", id);
    if(*id>=30000 && *id<=150000)
        return 0;
    else
        return -1;
}

