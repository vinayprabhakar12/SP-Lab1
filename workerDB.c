#include <stdio.h>
#include <string.h>
#include "readfile.h"

#define MAXNAME 64

//Definition of the employee structure
struct employee {
    unsigned int id;
    char firstName[MAXNAME];
    char lastName[MAXNAME];
    unsigned int salary;
};

int main(int argc, char **argv) {

    char *filename = argv[1]; //Assinged the string passed in commandline to the filename to be opened

    struct employee empList[1024], temp;
    int numEmployees = 0;
    int i = 0;

    open_file(filename);

    FILE *reads;
    reads = fopen(filename, "r"); //Open the file
    if (reads==NULL) {
        printf("Error! Re-run the program with a proper filename");
        return -1;
    }
    else{
        while(!feof(reads)){      //Read the file and store into the empList struct array
            fscanf(reads,"%d %s %s %d", &empList[i].id, empList[i].firstName, empList[i].lastName, &empList[i].salary);
            i++;
            numEmployees++;
        };
        //return 0;
    }

    // Sort the structure 
    for (i = 1; i < numEmployees; i++){
      for (int j = 0; j < numEmployees - i; j++) {
         if ((empList[j].id - empList[j + 1].id) < 0) {
            temp = empList[j];
            empList[j] = empList[j + 1];
            empList[j + 1] = temp;
         }
      }
    }

    int choice;
    unsigned int searchID =999999;
    char searchName[64];

    //Loop for main menu with choices for the user
    while(choice!=5){
        printf("Employee Database Menu:\n");
        printf("--------------------------------\n");
        printf("    (1) Print the Database\n");
        printf("    (2) Lookup by ID\n");
        printf("    (3) Lookup by Last Name\n");
        printf("    (4) Add an Employee\n");
        printf("    (5) Quit\n");
        printf("--------------------------------\n");
        printf("Enter your choice : ");
        fflush(stdout);
        scanf("%d", &choice);
        printf("Your choice is : %d\n\n", choice);

        //Printing entire database
        if(choice == 1){
            printDB(empList, numEmployees);
        }

        //Lookup employee by id
        else if(choice == 2){
            printf("Enter a 6 digit employee id: ");
            fflush(stdout);
            scanf("%d", &searchID);
            printf("The search ID is : %d\n", searchID);
            int found=0;
            int i=0;
            while(!found && i<numEmployees){
                if(empList[i].id == searchID){
                    found = 1;
                    printf("%-10s %-18s  %7s %10s\n", "NAME", "", "SALARY", "ID");
                    printf("-------------------------------------------------\n");
                    printEmployee(&(empList[i]));
                    printf("-------------------------------------------------\n\n");
                }
                i++;
            }
            if(!found){
                printf("Employee with that ID not found !\n\n");
            }
        }

        //Lookup employee by last name
        else if(choice == 3){
            printf("Enter Employee's last name (no extra spaces): ");
            fflush(stdout);
            scanf("%s", searchName);
            printf("The search Last Name is : %s\n", searchName);
            int found=0;
            int i=0;
            while(!found && i<numEmployees){
                if(strcmp(empList[i].lastName,searchName)==0){
                    found = 1;
                    printf("%-10s %-18s  %7s %10s\n", "NAME", "", "SALARY", "ID");
                    printf("-------------------------------------------------\n");
                    printEmployee(&(empList[i]));
                    printf("-------------------------------------------------\n\n");
                }
                i++;
            }
            if(!found){
                printf("Employee with that last name not found !\n\n");
            }
        }

        //Add a new employee
        else if(choice == 4){
            int confirm = 0;
            struct employee userEmp;
            enterEmp(&userEmp); 
            printf("Do you want to add the following employee to the DB?\n %20s, %s, Salary: %d\n", userEmp.firstName, userEmp.lastName, userEmp.salary);
            printf("Enter 1 for yes, 0 for no: ");
            fflush(stdout);
            scanf("%d", &confirm);
            if(confirm){
                userEmp.id = empList[numEmployees-1].id + 1;
                empList[numEmployees] = userEmp;
                numEmployees++;
            }
            printf("\n\n");
        }  

        //Exit choice for the user
        else if(choice == 5){
            printf("Goodbye!");
        }

        //Reprompt the user if wrong choice entered
        else{
            printf("Hey, %d is not between 1 and 5, try again...\n", choice);
        }
    }
    return 0;
}

//Function to print the structure array
void printDB(struct employee empList[1024], int numEmployees){
    printf("%-10s %-18s  %7s %10s\n", "NAME", "", "SALARY", "ID");
    printf("-------------------------------------------------\n");
    for(int i=0; i<numEmployees;i++){
        printEmployee(&(empList[i]));
    }
    printf("-------------------------------------------------\n");
    printf("Number of Employees = %d\n\n", numEmployees);
}

//Function to print each employee
void printEmployee(struct employee *empPtr){
    printf("%-10s %-18s $%7d %10d\n", (*empPtr).firstName, (*empPtr).lastName, (*empPtr).salary, (*empPtr).id);
}

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

//Funciton to take in details of a new employee from user 
void enterEmp(struct employee *emp){
    read_firstName(&(*emp).firstName);
    read_lastName(&(*emp).lastName);
    int ret = -1;
    while(ret!=0)
        ret = read_salary(&(*emp).salary);
    ret = -1;
}