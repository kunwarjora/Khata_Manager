#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct profile
{
    char number[16];
    char name[20];
    int balance;
    int token;
    // int s_deposit;
    struct profile *next;
} name;
// int token = 0;

name *create_contact();
void display(name *start);
void display_par(name *start, int token);
int number_of_customer(name *start);
int searching(name *start, char nam[]);
name *insert_at_end(name *start, char data[], char nam[], int bal);
name *take_order(name *start, int money, int token);
void export(name *start);
name *import(name *start);
name *recieve(name *start,int money, int token);
int net_balance(name *start, int token);

int main()
{
    int choose, start, temp, order, token;
    int ptr = -1;
    char numb[20];
    char nam[20], nnam[20];
    char nnumb[20];
    name *p = NULL;
main_menu:
    while (1)
    {
        printf("****Choose any of the following****\n");
        printf("1. Register New Customer\n");
        // printf("2. Delete Customer\n");
        // printf("3. Rename Customer Name\n");
        printf("2. Customer Info\n");
        printf("3. Display total Balance Sheet\n");
        printf("4. Find token number\n");//NOT WORKING FINE

        printf("5. Export\n");
        printf("6. Import Previous Data\n");
        // printf("9. Change Number\n");
        printf("11. Take Order\n");
        printf("12. Collect Money\n");
        printf("10. Exit\n");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            printf("Enter Customer Name: ");
            fflush(stdin);
            gets(nam);
            printf("Enter Phone Number: ");
            fflush(stdin);
            gets(numb);
            p = insert_at_end(p, numb, nam, 0);
            // printf("%s",p->name);//________---> it is working
            break;

        case 2:
            printf("Enter Token No. whose details you want: ");
            fflush(stdin);
            scanf("%d", &temp);
            display_par(p, temp);
            break;
        case 3:
            display(p);
            break;
        case 4:
            printf("Enter Name to be searched : ");
            fflush(stdin);
            gets(nam);
            temp = searching(p, nam);
            if (temp == -2)
            {
                printf("\t**Data Not Found**\n");
            }
            else
                printf("The token no. is  %d\n", temp);
            break;
        case 5:
            export(p);
            break;
        case 6:
            p = import(p);
            break;
        case 9:
            // printf("Enter contact name to be Changed : ");
            // // scanf("%s",nam);
            // fflush(stdin);
            // gets(nam);
            // temp=searching(p,nam);
            // if (temp==-2)
            // {
            //     printf("\t**Contact NOT found**\n");
            // }
            // else{
            // fflush(stdin);
            // printf("Enter new number: ");
            // gets(nnumb);
            // p=c_number(p,temp,nnumb);
            // }
            break;
        case 10:
            exit(0);
        case 11:
            while (1)
            {
                printf("Choose from the following Dish:\n");
                printf("1. PaniPuri         $10\n");
                printf("2. SukhiPuri        $15\n");
                printf("3. DahiPuri         $20\n");
                printf("4. Bhel             $25\n");
                printf("10. Return to main menu\n");
                scanf("%d", &order);
                if (order == 10)
                {
                    goto main_menu;
                }
                if (p == NULL)
                {
                    printf("The List is Empty\n");
                    goto main_menu;
                }
                if (order>4 || order<1 ||order==10)
                {   
                    printf("***Enter valid number***\n");
                    // goto main_menu;
                }
                
                else
                {
                    printf("Enter Token No.: ");
                    scanf("%d", &token);
                    p = take_order(p, order, token);
                }
            }
            break;
        case 12:
            printf("Enter token No. :");
            scanf("%d", &token);
            temp=net_balance(p,token);
            printf("Net Balance for token %d is %d.\n",token,temp);
            printf("Enter the amount:");
            scanf("%d", &order);
            p=recieve(p,order,token);
            printf("Amount Recieved!!!\n");
            temp=net_balance(p,token);
            printf("New Net Balance for token %d is %d.\n",token,temp);


            break;
        default:
            printf("\tEnter a Valid Input \n");
            break;
        }
    }

    return 0;
}
name *create_contact()
{
    name *l;
    // printf("xyz\n");
    l = (name *)malloc(sizeof(name));
    // if (l==NULL)
    // {
    //     printf("Node not created\n");
    //     return l;
    // }
    // else{
    //     printf("Node created\n");
    // }
    l->balance = 0;
    return l;
}

name *insert_at_end(name *start, char data[], char nam[], int bal)
{
    name *new = create_contact();
    name *temp;
    FILE *ptr;
    ptr = fopen(nam, "r");
    if (ptr==NULL)
    {
        fclose(ptr);
    ptr = fopen(nam, "a");
    fprintf(ptr, "Customer Name  : %s\n", nam);
    fprintf(ptr, "Contact Number : %s\n", data);
        
    }
    

    int token;
    // new->number=data;
    strcpy(new->number, data);
    strcpy(new->name, nam);
    new->next = NULL;
    new->balance = bal;

    if (start == NULL)
    {
        start = new;
    }
    else
    {
        temp = start;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new;
    }
    token = number_of_customer(start);

    new->token = token;
    fprintf(ptr, "Token Number   : %d\n", token);
    fprintf(ptr, "__________x__________\n");
    fclose(ptr);
    return start;
}

void display(name *start)
{
    int n;
    if (start == NULL)
    {
        printf("\n*****The list is empty*****\n\n");
    }
    else
    {
        // n=number_of_customer(start);
        // for (int i = 0; i < n; i++)
        // {
        //     /* code */
        // }
        printf("(NAME) --(Num) -- (Token) -- (NET)\n");
        while (start != NULL)
        {
            printf("%s __ %s __ %d __", start->name, start->number, start->token);
            printf("%d\n", start->balance);
            start = start->next;
        }
        // printf("%s -- %s\n",start->name ,start->number);
    }
    return;
}

void display_par(name *start, int token)
{
    int i = 0;
    if (start == NULL)
    {
        printf("***The list is empty!!!***\n");
        return;
    }
    //  while (strcmp(start->name,nam)!=0)
    // {
    //     start=start->next;
    // }
    while (i < token - 1)
    {
        i++;
        start = start->next;
    }

    printf("Name         --> %s\n", start->name);
    printf("Contact No.  --> %s\n", start->number);
    printf("Token Number --> %d\n", start->token);
    printf("Net Balance  --> %d\n", start->balance);
    // printf("%s -- %s\n",start->name ,start->number);
}
//////////////////////////////
int number_of_customer(name *start)
{
    int count = 0;
    while (start != NULL)
    {
        count++;
        start = start->next;
    }
    return count;
}

int searching(name *start, char nam[])
{
    name *temp = start;
    int pos = 0;
    while (temp != NULL)
    {
        if (strcmp(temp->name, nam) == 0)
        {
            // printf("The data is found at %d \n",pos);
            return temp->token;
        }
        temp = temp->next;
        pos++;
    }
    return -2;
}

name *take_order(name *start, int order, int token)
{
    int rate;
    char dish[20];
    name *temp = start;
    FILE *ptr;
    time_t tm;
    time(&tm);
    for (int i = 0; i < token - 1; i++)
    {
        temp = temp->next;
    }
    if (order == 1)
    {
        strcpy(dish, "Pani Puri");
        rate = 10;
    }
    if (order == 2)
    {
        strcpy(dish, "Sukhi Puri");
        rate = 15;
    }
    if (order == 3)
    {
        strcpy(dish, "Dahi Puri");
        rate = 20;
    }
    if (order == 4)
    {
        strcpy(dish, "Bhel");
        rate = 25;
    }
    temp->balance = temp->balance + rate;
    ptr = fopen(temp->name, "a");
    fprintf(ptr, "%s\t%s_____%d\tTotal Balance= %d\n", ctime(&tm), dish, rate, temp->balance);
    // fprintf(ptr,"+%d\n",money);
    fclose(ptr);
    return start;
}
void export(name *start)
{
    FILE *ptr;
    time_t tm;
    time(&tm);
    // FILE *ptr;
    ptr = fopen("backup", "w");
    // ptr2=fopen("logs.txt","a");
    fprintf(ptr, "%s", ctime(&tm));
    // fprintf(ptr2,"\n\t\t%s",ctime(&tm));
    while (start != NULL)
    {
        fprintf(ptr, "%d %s ----> %s _____%d\n", start->token, start->name, start->number, start->balance);
        // fprintf(ptr2,"%s ----> %s\n",start->name,start->number);
        start = start->next;
    }
    fclose(ptr);
    // fclose(ptr2);
    printf("\tExported Successfully\n");
}

name *import(name *start)
{
    int token, balance;
    FILE *ptr;
    name *temp;
    char ch;
    char name[20];
    char nub[16], nub2[16];
    ptr = fopen("backup", "r");

    while (1)
    {
        ch = fgetc(ptr);
        if (ch == '\n')
        {
            // printf("1");
            break;
        }
    }

    while (1)
    {
        // ch=getc(ptr);
        // ptr=ptr-1;
        if (ch == EOF)
        {
            break;
            // return start;
        }
        else
        {
            fscanf(ptr, "%d ", &token); // problem in getting K U Jora
            // fgets(name,16,ptr);
            fscanf(ptr, "%s", &name); // problem in getting K U Jora
            fscanf(ptr, " ----> %s\n", &nub);
            fscanf(ptr, " _____%d\n", &balance);
            start = insert_at_end(start, nub, name, balance);
            // printf("%s ----> %d\n",start->name,start->number);
            ch = getc(ptr);
            // ptr--;
            fseek(ptr, -1, SEEK_CUR);
        }
    }

    printf("\tImported Successfully\n");
    fclose(ptr);
    return start;
}
name *recieve(name *start,int money, int token){
    name *temp=start;
    FILE *ptr;
    time_t tm;
    time(&tm);
    for (int i = 0; i < token-1; i++)
    {
        temp=temp->next;
    }
    temp->balance=temp->balance-money;
    ptr = fopen(temp->name, "a");
    fprintf(ptr, "%s\tRecieved_____%d\tTotal Balance= %d\n", ctime(&tm), money, temp->balance);
    return start;
}
int net_balance(name *start, int token){
    name *temp=start;
    for (int i = 0; i < token-1; i++)
    {
        temp=temp->next;
    }
    return temp->balance;   
}