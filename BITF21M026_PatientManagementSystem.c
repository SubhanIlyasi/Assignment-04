#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct Patient
{
    char id[5];
    char name[15];
    char cnic[13];
    char phnum[11];
    char disease[10];
    char is_adm;
} patient_info;
int menu(void);
int rep_check(int z);
void add(void);
void delete (void);
void update(void);
void search(void);
void display(void);
int main()
{
    int choice;
    while ((choice = menu()) != 6)
    {
        switch (choice)
        {
        case 1:
            add();
            break;
        case 2:
            delete ();
            break;
        case 3:
            update();
            break;
        case 4:
            search();
            break;
        case 5:
            display();
            break;
        default:
            puts("\nIncorrect choice\n");
            break;
        }
    }

    return 0;
}
int menu(void)
{
    int wish;
    printf("\t\t\t*******************************************************************\n\n");
    printf("\t\t\t\tWelcome to PUCIT Hospital. How may we help you?\n\n");
    printf("\t\t\t\t\t  * Services we Offer *\n\n");
    printf("\t\t\t___________________________________________________________________\n\n\n");
    printf("1. Add Patient");
    printf("\t\t\t\t\t\t\t\t\t\t2. Delete Patient\n\n");
    printf("3. Update Patient");
    printf("\t\t\t\t\t\t\t\t\t4. Search Patient\n\n");
    printf("5. Display All Patients");
    printf("\t\t\t\t\t\t\t\t\t6. Exit the Program\n\n");
    printf("\t\t\t\t\t\tEnter your choice: ");
    scanf("%d", &wish);
    return wish;
}
void add(void)
{
    FILE *fptr = NULL;
    int a, found;
    char ar[3];
    fptr = fopen("ADD_PATIENT.txt", "a+");
    printf("You selected Add Patient. Please enter the following information\n");
    printf("Enter Patient's id: ");
    fflush(stdin);
    gets(patient_info.id);
    strcpy(ar, patient_info.id);
    sscanf(patient_info.id, "%d", &a);
    found = rep_check(a);
    if (found == 1)
    {
        printf("Patient Already Exists.\n");
    }
    else
    {
        strcpy(patient_info.id, ar);
        printf("Enter Patient's Name: ");
        gets(patient_info.name);
        printf("Enter Patient's CNIC: ");
        gets(patient_info.cnic);
        printf("Enter Patient's Phone Number: ");
        gets(patient_info.phnum);
        printf("Enter Patient's Disease: ");
        fflush(stdin);
        gets(patient_info.disease);
        printf("Is the patient admitted?(Y or N) ");
        scanf("%c", &patient_info.is_adm);
        fwrite(&patient_info, sizeof(struct Patient), 1, fptr);
        fprintf(fptr, "\n");
    }
    fclose(fptr);
}
void delete (void)
{

    FILE *fp = NULL;
    FILE *ptr = NULL;
    int check = 0;
    ptr = fopen("ADD_PATIENT.txt", "r");
    fp = fopen("DELETE.txt", "a+");
    char id[2];
    printf("Enter Patient id: ");
    scanf("%s", id);
    while (fread(&patient_info, sizeof(struct Patient) + 1, 1, ptr))
    {
        if (strcmp(patient_info.id, id) != 0)
        {
            fwrite(&patient_info, sizeof(struct Patient), 1, fp);
            fprintf(fp, "\n");
        }
        else if (strcmp(patient_info.id, id) == 0)
        {
            check = 1;
        }
    }
    fclose(ptr);
    fclose(fp);
    if (check == 0)
    {
        printf("Record Does Not Exist.\n");
    }
    else
    {
        remove("ADD_PATIENT.txt");
        rename("DELETE.txt", "ADD_PATIENT.txt");
        printf(ptr, "_________________________________________________");
        printf("Deletion Done Succssefully.\n");
    }
}
void display(void)
{
    FILE *fptr = NULL;
    char put;
    int size;
    fptr = fopen("ADD_PATIENT.txt", "r");
    if (fptr)
    {
        fseek(fptr, 0, SEEK_END);
        size = ftell(fptr);
    }
    fseek(fptr, 0, SEEK_SET);
    if (size != 0)
    {
        printf("\n____________________________________________________________________________\n\n\n");
        while (!feof(fptr))
        {
            put = fgetc(fptr);
            printf("%c", put);
        }
        printf("\n____________________________________________________________________________\n\n");
    }
    else if (size == 0)
    {
        printf("No Record Found. File is Empty\n\n");
    }
    fclose(fptr);
}

void update(void)
{
    FILE *fptr = NULL;
    fptr = fopen("ADD_PATIENT.txt", "r");
    FILE *fptr1 = NULL;
    fptr1 = fopen("Updated_Patient.txt", "w");
    int a, ad, found = 0;
    int flag = 1;
    printf("Enter Patient's id you want to update: ");
    scanf("%d", &ad);
    found = rep_check(ad);
    if (found == 1)
    {
        while (fread(&patient_info, sizeof(struct Patient) + 1, 1, fptr))
        {
            flag = 1;
            puts(patient_info.id);
            sscanf(patient_info.id, "%d", &a);
            if (ad == a)
            {
                printf("Enter Patient's id: ");
                fflush(stdin);
                gets(patient_info.id);
                printf("Enter Patient's Name: ");
                gets(patient_info.name);
                printf("Enter Patient's CNIC: ");
                gets(patient_info.cnic);
                printf("Enter Patient's Phone Number: ");
                gets(patient_info.phnum);
                printf("Enter Patient's Disease: ");
                fflush(stdin);
                gets(patient_info.disease);
                printf("Is the patient admitted?(Y or N) ");
                scanf("%c", &patient_info.is_adm);
                fwrite(&patient_info, sizeof(struct Patient), 1, fptr1);
                fprintf(fptr1, "\n");
                flag = 0;
            }
            if (flag == 1)
            {
                fwrite(&patient_info, sizeof(struct Patient), 1, fptr1);
                fprintf(fptr1, "\n");
            }
        }
    }
    else
    {
        printf("No record found\n");
    }

    fclose(fptr);
    fclose(fptr1);
    remove("ADD_PATIENT.txt");
    rename("Updated_Patient.txt", "ADD_PATIENT.txt");
}
void search(void)
{
    FILE *fptr;
    fptr = fopen("ADD_PATIENT.txt", "r");
    int ad, found = 0, a;
    printf("enter the patient you want to search :");
    scanf("%d", &ad);
    found = rep_check(ad);
    if (found == 1)
    {
        printf("\n_________________________________________________________\n\n\n");
        while (fread(&patient_info, sizeof(struct Patient) + 1, 1, fptr))
        {
            sscanf(patient_info.id, "%d", &a);
            if (ad == a)
            {
                printf("PATIENT ID IS :");
                puts(patient_info.id);
                printf("PATIENT NAME IS :");
                puts(patient_info.name);
                printf("PATIENT CNIC IS :");

                puts(patient_info.cnic);
                printf("PATIENT DISEASE IS :");

                puts(patient_info.disease);
                printf("PATIENT PHONE NUMBER IS :");

                puts(patient_info.phnum);
                printf("PATIENT ADMISSION STATUS IS :");
                printf("%c", patient_info.is_adm);
                break;
            }
        }
        printf("\n_________________________________________________________\n");
    }
    else
    {
        printf("\n\n*_ *_ PATIENT NOT FOUND_ *_ *\n");
    }
    fclose(fptr);
}
int rep_check(int z)
{
    FILE *fptr = NULL;
    fptr = fopen("ADD_PATIENT.txt", "r");
    int found = 0, a;
    while (fread(&patient_info, sizeof(struct Patient) + 1, 1, fptr))
    {
        sscanf(patient_info.id, "%d", &a);
        if (z == a)
        {
            found = 1;
            break;
        }
    }
    return found;
    fclose(fptr);
}