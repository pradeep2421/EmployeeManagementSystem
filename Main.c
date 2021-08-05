#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct S_Employee {
    char Employee_Name[40] ;
    int Employee_Age ;
    char Employee_Designation[40] ;
    float Employee_Salary ;
      };

void flush()
{
    int c =0 ;
    while((c == getchar()) != '\n' && c != EOF) ;
}

void main(){
    FILE *employeeFile ;
    FILE *employeeFileTemp ;

   char userChoice ;
   char nextChoice ;

    struct S_Employee Employee ;
    char EmployeeName[40] ;

    long int sizeOfEmployeeRecord ;
    const char* filename = "EMPLOYEE.DAT" ;

    employeeFile = fopen(filename,"rb+") ;

    if(employeeFile == NULL){
        employeeFile = fopen(filename,"wb+") ;
        if(employeeFile == NULL){
            printf("Unable to open %s",filename) ;
            exit(1) ;
        }
    }
    sizeOfEmployeeRecord = sizeof(Employee) ; 
   while (1)
   {
     printf("1. Add new Employee.\n") ;
     printf("2. Modify Employee. \n") ;
     printf("3. Delete Employee. \n") ;
     printf("4. Print All Employee Details. \n") ;
     printf("5. Exit. \n") ;
     fflush(stdin) ;
     
     printf("\nEnter an operation of your choice : \n") ; 
     scanf("\n%c" ,&userChoice) ;
     switch (userChoice)
     {
     case '1' :
        fseek(employeeFile,0,SEEK_END) ;
        
        nextChoice = 'y' ;
        while(nextChoice == 'y'){
            fflush(stdin) ;
            printf("\n=========================\n") ;
            printf("Add Employee's name : ") ;
            scanf("%s" ,Employee.Employee_Name) ;
            printf("Add Employee's age : ") ;
            scanf("%d",&Employee.Employee_Age) ;
            printf("Add Employee's designation : ") ;
            scanf("%s",Employee.Employee_Designation) ;
            printf("Add Employee's salary : ") ;
            scanf("%f" ,&Employee.Employee_Salary) ;
           
            fwrite(&Employee ,sizeOfEmployeeRecord,1,employeeFile) ;

             printf("\n%s has been added\n",Employee.Employee_Name) ;

            printf("Would you like to add a new record(y/n) ? \n") ;
            fflush(stdin) ;
            scanf("\n%c" ,&nextChoice) ;
        }
         break ;
     case '2' :
        nextChoice = 'y' ;
        while(nextChoice == 'y')
        {
            fflush(stdin) ;
            printf("Enter the Employee name to modify :") ;
            scanf("%s" ,EmployeeName ) ;
           // rewind(employeeFile) ;
            fseek(employeeFile,0L,SEEK_SET); 
            while(fread(&Employee, sizeOfEmployeeRecord ,1,employeeFile) ==1)
            {
                if(strcmp(Employee.Employee_Name ,EmployeeName) ==0)
                {
                    printf("Change %s name : ",EmployeeName) ;
                    scanf("%s" ,Employee.Employee_Name) ;
                    printf("Change %s age : ",EmployeeName) ;
                    scanf("%d",&Employee.Employee_Age) ;
                    printf("Change %s designation : ",EmployeeName) ;
                    scanf("%s",Employee.Employee_Designation) ;
                    printf("Change %s salary : ",EmployeeName) ;
                    scanf("%f" ,&Employee.Employee_Salary) ;

                    fseek(employeeFile,-sizeOfEmployeeRecord,SEEK_CUR) ;
                    fwrite(&Employee,sizeOfEmployeeRecord,1,employeeFile) ;
                    break ;
                }
            }            
             printf("\n%s has been modified\n",EmployeeName) ;

            printf("\nWould you like to modify another record(y/n) ? ") ;
            fflush(stdin);
            scanf("\n%c" ,&nextChoice) ; 
        }
        break ;
     case '3' :
        nextChoice = 'y' ;
        while(nextChoice == 'y'){
            printf("Enter the Employee name to delete :  ") ;
            scanf("%s", EmployeeName) ;

            employeeFileTemp = fopen("Temp.dat","wb") ;
            rewind(employeeFile) ;
            while(fread(&Employee ,sizeOfEmployeeRecord,1,employeeFile) ==1 )
            {
                if(strcmp(Employee.Employee_Name, EmployeeName) != 0)
                {
                 fwrite(&Employee ,sizeOfEmployeeRecord,1,employeeFileTemp) ;
                }
            }
            fclose(employeeFile) ;
            fclose(employeeFileTemp) ;

            remove("EMPLOYEE.DAT") ;
            rename("Temp.DAT", "EMPLOYEE.DAT") ;

            fopen("EMPLOYEE.DAT","wb+") ;
            printf("\n%s has been deleted\n",EmployeeName) ;

            printf("\nWould you like to delete another record(y/n) ? ") ;
            fflush(stdin) ;
            scanf("\n%c" ,&nextChoice) ;
        }
        break ;
     case '4' :
        fseek(employeeFile,0,SEEK_SET) ;

        while(fread(&Employee,sizeOfEmployeeRecord,1,employeeFile) ==1)
        {
            printf("==================================") ;
            printf("\nEmployee Name : %s" ,Employee.Employee_Name) ;
            printf("\nEmployee' Age : %d",Employee.Employee_Age) ;
            printf("\nEmployee's Designation : %s",Employee.Employee_Designation) ;
            printf("\nEmployee's Salary : %f",Employee.Employee_Salary) ;
            printf("\n====================================\n") ;
        }
        break ;
     case '5' :
        exit(0) ;
     default:
         break;
     }
   }
   

}