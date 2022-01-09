#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <windows.h> //for sleep
#include <time.h>

#define N 26
#define nameSize 25

#pragma warning(disable : 4996)
#define LINEAR 0
#define DOUBLE 1
#define MOOD DOUBLE


struct student
{
	char name[nameSize];
	int ID;
	int birth_day;
	int birth_month;
	int birth_year;
	int score;
	struct student *next;
};
struct student *chained[N]={NULL};

//open hashing used functions
int hashChained(int index);
void InsertChained();
void searchChained(char *name);
void deleteChained(char *name);
void displayData (struct student *disp);

//closed hashing used functions
int Hash_Key_Birthdayconst (const struct student target , const int SizeOfTable);
int Linear_Proping( const int SizeOfTable, int *key);
int Double_Proping( const int SizeOfTable, int key,int i);
void Read_New_Student(struct student* newStudent);
void display_One_student_closed(const struct student* disp);
void Delete_Closed_Hash(struct student* Hash, const int SizeOfTable);
void Insert_Closed_Hash(struct student* Hash, const int SizeOfTable);
void display_all_table(const struct student* Hash, const int SizeOfTable);
int Find_Closed_Hash(const struct student* Hash, const int SizeOfTable);


int main()
{
    char element[nameSize];
    int i, choice,choiceChained, choiceClosed;;
    int SizeOfTable = 20;
    struct student *Hash = (struct student*)calloc(SizeOfTable, sizeof(struct student));

    do
     {
      printf("=== Menu ===\n");
      printf("1. Open Hashing\n");
      printf("2. closed Hashing\n");
      printf("3. Exit\n");
      printf("Enter your choice:");
      scanf("%d",&choice);
      system("cls");
      switch(choice)
      {
      case 1:
          //open hashing
          do
     {
          printf("=== Open Hashing Menu ===\n");
          printf("1. Insert new student\n");
          printf("2. search for student\n");
          printf("3. Delete student\n");
          printf("4. Back\n");
          printf("Enter your choice:");
          scanf("%d",&choiceChained);
          system("cls");
          switch (choiceChained)
          {
            case  1:
                InsertChained();
                break;

            case  2:
                printf("please enter name of student to search :");
                //clear buffer
                char temp;
                scanf("%c",&temp);
                fgets(element,nameSize,stdin);
                searchChained(element);
                Sleep(4000);
                break;

            case  3:
                printf("please enter name of student to search :");
                //clear buffer
                char cl;
                scanf("%c",&cl);
                fgets(element,nameSize,stdin);
                deleteChained(element);
               break;

            case  4:
                printf("__________Thank you__________\n");
                break;

            default: printf("__________Invalid Input. Try again__________\n");
                   break;
          }
          Sleep(1000);
          system("cls");
          } while (choiceChained != 4);
          break;
      case 2:
          //closed hashing

        for ( i = 0; i < SizeOfTable; i++)/*initializing empty hash table*/
        {
            (Hash + i)->ID = -1;
        }
        do
         {
              printf("=== Closed Hashing Menu===\n");
              printf("1. Insert new student\n");
              printf("2. search for student\n");
              printf("3. Delete student\n");
              printf("4. Display all students\n");
              printf("5. Back\n");

              printf("Enter your choice:");
              scanf("%d",&choiceClosed);
              system("cls");
              switch (choiceClosed)
              {
                case  1:
                    Insert_Closed_Hash(Hash, SizeOfTable);
                    break;

                case  2:
                    Find_Closed_Hash(Hash, SizeOfTable);
                    Sleep(4000);
                    break;

                case  3:
                    Delete_Closed_Hash(Hash, SizeOfTable);
                    break;

                case  4:
                    display_all_table(Hash, SizeOfTable);
                    break;

                case  5:
                    printf("__________Thank you__________\n");
                    break;

                default:
                    printf("__________Invalid Input. Try again__________\n");
                    break;
              }
              Sleep(1000);
              system("cls");
              } while (choiceChained != 5);
          break;

        case 3:
            printf("__________Thank you__________\n");
            break;

      default:
          printf("__________Invalid Input__________\n");
          break;

      }

      Sleep(1000);
      system("cls");
     } while (choice !=3);
     return 0;
}
/*__________________________________________open hashing used functions__________________________________________*/
int hashChained(int index)
{
    int key = (index-'a')%N;
    return key;
}

//insertion using chained hashing
void InsertChained()
{
    struct student *newStudent = malloc(sizeof(struct student));

    //clear buffer
    char temp;
    scanf("%c",&temp);

    //get data of new student
    printf("Please enter new student name:");
    fgets(newStudent->name,nameSize,stdin);
    //gets(newStudent->name);
    printf("Please enter new student ID :");
    scanf ("%d",&newStudent->ID);
    printf("Please enter new student birth_day:");
    scanf ("%d",&newStudent->birth_day);
    printf("Please enter new student birth_month:");
    scanf ("%d",&newStudent->birth_month);
    printf("Please enter new student birth_year:");
    scanf ("%d",&newStudent->birth_year);
    printf("Please enter new student score:");
    scanf ("%d",&newStudent->score);

    newStudent->next =NULL;

    int arrayIndex = hashChained(newStudent->name[0]);
    struct student *head = chained[arrayIndex];

    //insertion in linked list
    if (head == NULL)
    {
        chained[arrayIndex] = newStudent;
        printf ("__________Successful Insertion__________\n");
        return ;
    }
    else
    {
        while (head->next != NULL)
        {
            head = head->next;
        }
        head->next = newStudent;
        printf ("__________Successful Insertion__________\n");
        return ;
    }

}

//search using chained hashing
void searchChained(char *name)
{
    int index = hashChained(*name);
    struct student *head = chained[index];

    //check if no data
    int empty = 1 ;
    if (head != NULL) empty = 0;

    if (empty)
        printf("You don't have any student start with this letter \n");

    else
    {
        int absent = 1;

        if (!strcmp(head->name,name)) absent =0;
        else

             while (absent&& head->next!=NULL)
            {
                head=head->next;
                absent = strcmp(head->name,name);
            }
         if (absent)
                printf("__________NOT FOUND__________");
        else
        {
            printf("__________FOUND__________\n");
            printf("Here is data of the student:\n");
            displayData (head);
        }
    }
}



//delete element using chained hashing
void deleteChained(char *name)
{
    int index = hashChained(*name);
    struct student *head = chained[index];
    struct student *prev = chained[index];
    //check if no data
    int empty = 1 ;
    if (head != NULL) empty = 0;

    if (empty)
        printf("You don't have any data... Please insert data first to be able to delete it later. \n");

    else
    {
         int absent = 1;

        if (!strcmp(head->name,name)) absent =0;
        else

             while (absent && head->next!=NULL)
            {
                prev=head;
                head=head->next;
                absent = strcmp(head->name,name);
            }
         if (absent)
                printf("__________NOT FOUND__________");
        else
        {
            prev->next=head->next;
            free(head);
            printf("__________Successful deletion__________\n");
        }
    }
}


//display student data
void displayData (struct student *disp)
{
    printf("Name : %s",disp->name);
    printf("ID : %d \n",disp->ID);
    printf("Birth Date : %d/%d/%d \n",disp->birth_day ,disp->birth_month,disp->birth_year);
    printf("Score : %d \n",disp->score);
}

/*__________________________________________closed hashing used functions__________________________________________*/


int Hash_Key_Birthday(const struct student target,const int SizeOfTable)
{
	int key = (target.birth_month % 13)*100  + target.birth_day+ target.birth_day%2;
	while (key < 10*SizeOfTable)
		key += (key);
	return key%SizeOfTable;
}
int Linear_Proping( const int SizeOfTable,int *key)
{
		(*key)++;
		(*key) %= SizeOfTable;
		return (*key);
}

int Double_Proping(const int SizeOfTable, int key,int i)
{

		key+=i*i;
		key %= SizeOfTable;
		return key;
}

void Insert_Closed_Hash(struct student* Hash, const int SizeOfTable)
{
// read the new data
	struct student newStudent;
	Read_New_Student(&newStudent);
	int key = Hash_Key_Birthday(newStudent, SizeOfTable);
	int Times_Of_Insertions = 0;
	int temp_key = key;
	while (Hash[temp_key].ID!=-1&&Times_Of_Insertions<SizeOfTable)
	{
		Times_Of_Insertions++;
		if (MOOD == LINEAR)
		{
			temp_key = Linear_Proping(SizeOfTable, &temp_key);
		}
		else if (MOOD == DOUBLE)
		{
			temp_key = Double_Proping(SizeOfTable, key,Times_Of_Insertions);
		}

	}
	if (Times_Of_Insertions == SizeOfTable)
		printf("\n__________NO STORAGE__________\n");
	else
	{
		Hash[temp_key] = newStudent;
		printf("\n__________Successful Insertion__________\n");
	}
}
int Find_Closed_Hash(const struct student* Hash, const int SizeOfTable)
{
	//enter the required data to search
	//enter id and birth day and birth month
	struct student temp_student;
	printf("Please enter the student ID :");
	scanf("%d", &temp_student.ID);
	printf("Please enter the student birth_day:");
	scanf("%d", &temp_student.birth_day);
	printf("Please enter the student birth_month:");
	scanf("%d", &temp_student.birth_month);
	char temp;
	scanf("%c", &temp);
	int key = Hash_Key_Birthday(temp_student, SizeOfTable);
	int Times_Of_Insertions = 0;
	int temp_key = key;
	while (Hash[temp_key].ID !=temp_student.ID && Times_Of_Insertions < SizeOfTable)
	{
		Times_Of_Insertions++;
		if (MOOD == LINEAR)
		{
			temp_key = Linear_Proping(SizeOfTable, &temp_key);
		}
		else if (MOOD == DOUBLE)
		{
			temp_key = Double_Proping(SizeOfTable, key, Times_Of_Insertions);
		}

	}

	if (Times_Of_Insertions == SizeOfTable)
	{
		printf("\n__________NOT FOUND__________\n");
		return -1;
	}
	else
	{
		printf("\n__________FOUND__________\n");
		display_One_student_closed(&Hash[temp_key]);
		return temp_key;
	}

}

void Delete_Closed_Hash(struct student* Hash,  const int SizeOfTable)
{
	int indicator=Find_Closed_Hash(Hash, SizeOfTable);
	if (indicator != -1)
	{
		Hash[indicator].ID = -1;
		puts("\n__________Successful deletion__________\n");
	}
	else
		puts("\n__________CAN'T BE DELETED__________\n");

}

void Read_New_Student(struct student *newStudent)
{
    //clear buffer
    char temp;
	scanf("%c", &temp);

	printf("Please enter new student name:");
	scanf("%[^\n]%*c", newStudent->name);
	printf("Please enter new student ID :");
	scanf("%d", &newStudent->ID);
	printf("Please enter new student birth_day:");
	scanf("%d", &newStudent->birth_day);
	printf("Please enter new student birth_month:");
	scanf("%d", &newStudent->birth_month);
	printf("Please enter new student birth_year:");
	scanf("%d", &newStudent->birth_year);
	printf("Please enter new student score:");
	scanf("%d", &newStudent->score);

}

void display_One_student_closed(const struct student *disp)
{
	printf("\tName : %s\n", disp->name);
	printf("\tID : %d \n", disp->ID);
	printf("\tBirth Date : %d/%d/%d \n", disp->birth_day, disp->birth_month, disp->birth_year);
	printf("\tScore : %d \n", disp->score);
}

void display_all_table(const struct student* Hash, const int SizeOfTable)
{
    int i ;
	for (i= 0; i < SizeOfTable; i++)
	{
		printf("%d-", i);
		if (Hash[i].ID == -1)
			printf("************************************\n");
		else
			display_One_student_closed(&Hash[i]);
	}
}
