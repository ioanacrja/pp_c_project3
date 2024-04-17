#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char name[50], surname[50];

struct book {
    char name[100];
    char author[100];
    int quantity;
};

struct clients
{
    char name[50];
    char surname[50];
};


struct account
{
    char name[50], surname[50];
    int numberborrows, numberdonations;
    char title[100], author[100];
    char datetoday[20], datereturn[20];
    int copies;
};

void createBookFile();
void createclientsFile();
void createaccountFile();
void menu();
void menu2();
void borrow();
void donate();
void search();
void login();
void signup();
void exit1();
void view();
void returnbook();


void createBookFile(struct book books[], int numBooks, const char* file_name) {
    FILE *file_pointerB;
    file_pointerB = fopen(file_name, "a");
    if (file_pointerB == NULL) {
        printf ("-----------------------\n");
        printf("Error creating the file.\n");
        printf ("-----------------------\n");
        return;
    }
    printf("File created successfully!\n");
    fclose(file_pointerB);
}


void createclientsFile(struct clients clients[], int numclients, const char* clientsfile_name) {
    FILE *file_pointerC;
    file_pointerC = fopen("clients.txt", "a");
    if (file_pointerC == NULL) {
        printf ("-----------------------\n");
        printf("Error creating the file.\n");
        printf ("-----------------------\n");
        return;
    }
    printf("File created successfully!\n");
    fclose(file_pointerC);
}


void createaccountFile(struct account account[], int numaccounts, const char* accountfile_name, char * s[100]) {
    FILE *file_pointerA;
    file_pointerA = fopen(s, "a");
    if (file_pointerA == NULL) {
        printf ("-----------------------\n");
        printf("Error creating the file.\n");
        printf ("-----------------------\n");
        return;
    }
    account->numberborrows=0;
    account->numberdonations=0;
    printf("File created successfully!\n");
    fclose(file_pointerA);
}



void menu()
{
    int n;
    printf ("-----------------------\n");
    printf("WELCOME TO OUR LIBRARY!\n");
    printf ("-----------------------\n");
    printf("1.Login\n2.Sign up\n3.Exit\n");
    printf ("-----------------------\n");
    printf ("Select your option: ");
    scanf ("%d",&n);
    if (n==1)
        login();
    else if (n==2)
        signup();
    else if(n==3)
        exit1();
    else {
        printf ("-----------------------\n");
        printf("Option not available\n");
        printf ("-----------------------\n");
        menu();
    }
}



void borrow()
{
    char clientfile_name[100];
    char title[100], author[100], datetoday[20];
    int copies;
    sprintf(clientfile_name, "%s_%s.txt", name, surname);

    printf("Today's date(dd/mm/yy): ");
    scanf(" %[^\n]", datetoday);
    printf("Type the title of the book you want to borrow: ");
    getchar();
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';
    printf("Type the author of the book you want to borrow: ");
    fgets(author, sizeof(author), stdin);
    author[strcspn(author, "\n")] = '\0';
    printf("How many copies of the chosen book do you want to borrow? ");
    scanf("%d", &copies);

    FILE *file_pointerB = fopen("books.txt", "r+");
    if (file_pointerB == NULL) {
        printf ("-----------------------\n");
        printf("Error opening the file.\n");
        printf ("-----------------------\n");
        return;
    }

    int bookExists = 0;
    struct book temp;
    long int last_pos = ftell(file_pointerB);
    while (fscanf(file_pointerB, "Book Name: %[^\n]\nAuthor: %[^\n]\nQuantity: %d\n\n", temp.name, temp.author, &temp.quantity) != EOF) {
        if (strcmp(title, temp.name) == 0 && strcmp(author, temp.author) == 0)
        {
            bookExists = 1;
            temp.quantity -= copies;
            fseek(file_pointerB, last_pos, SEEK_SET);
            fprintf(file_pointerB, "Book Name: %s\nAuthor: %s\nQuantity: %d\n\n", temp.name, temp.author, temp.quantity);
            break;
        }
        last_pos = ftell(file_pointerB);
    }
    if (!bookExists) {
        fseek(file_pointerB, 0, SEEK_END);
        fprintf(file_pointerB, "Book Name: %s\nAuthor: %s\nQuantity: %d\n\n", title, author, copies);
    }

    fclose(file_pointerB);

    FILE *file_pointerA = fopen(clientfile_name, "a");
    if (file_pointerA == NULL) {
        printf ("-----------------------\n");
        printf("Error opening the client's account file.\n");
        printf ("-----------------------\n");
        return;
    }
    fprintf(file_pointerA, "LOAN DATE: %s\n", datetoday);
    fprintf(file_pointerA, "BOOK TITLE: %s\n", title);
    fprintf(file_pointerA, "COPIES BORROWED: %d\n\n", copies);
    fclose(file_pointerA);

    printf ("-----------------------\n");
    printf("Book borrowed successfully!\n");
    printf ("-----------------------\n");
    menu2();
}



void returnbook()
{
    char clientfile_name[100];
    char title[100], author[100], datetoday[20];
    int copies;
    sprintf(clientfile_name, "%s_%s.txt", name, surname);

    printf("Today's date(dd/mm/yy): ");
    scanf(" %[^\n]", datetoday);
    printf("Type the title of the book you want to return: ");
    getchar();
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';
    printf("Type the author of the book you want to return: ");
    fgets(author, sizeof(author), stdin);
    author[strcspn(author, "\n")] = '\0';
    printf("How many copies of the chosen book do you want to return? ");
    scanf("%d", &copies);

    FILE *file_pointerB = fopen("books.txt", "r+");
    if (file_pointerB == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    int bookExists = 0;
    struct book temp;
    long int last_pos = ftell(file_pointerB);
    while (fscanf(file_pointerB, "Book Name: %[^\n]\nAuthor: %[^\n]\nQuantity: %d\n\n", temp.name, temp.author, &temp.quantity) != EOF) {
        if (strcmp(title, temp.name) == 0 && strcmp(author, temp.author) == 0)
        {
            bookExists = 1;
            temp.quantity += copies;
            fseek(file_pointerB, last_pos, SEEK_SET);
            fprintf(file_pointerB, "Book Name: %s\nAuthor: %s\nQuantity: %d\n\n", temp.name, temp.author, temp.quantity);
            break;
        }
        last_pos = ftell(file_pointerB);
    }
    if (!bookExists)
    {
        fseek(file_pointerB, 0, SEEK_END);
        printf ("-----------------------\n");
        printf("This book doesn't exist in our stock. Choose to donate or return another book!\n");
        printf ("-----------------------\n");
    }

    fclose(file_pointerB);

    FILE *file_pointerA = fopen(clientfile_name, "a");
    if (file_pointerA == NULL) {
        printf ("-----------------------\n");
        printf("Error opening the client's account file.\n");
        printf ("-----------------------\n");
        return;
    }
    fprintf(file_pointerA, "RETURN DATE: %s\n", datetoday);
    fprintf(file_pointerA, "BOOK TITLE: %s\n", title);
    fprintf(file_pointerA, "COPIES RETURNED: %d\n\n", copies);
    fclose(file_pointerA);

    printf ("-----------------------\n");
    printf("Book returned successfully!\n");
    printf ("-----------------------\n");
    menu2();
}



void donate() {
    char accountfile_name[100];
    char datetoday[20];

    struct book *book = malloc(100 * sizeof(struct book));
    if (book == NULL) {
        printf ("-----------------------\n");
        printf("Memory allocation failed.\n");
        printf ("-----------------------\n");
        return;
    }

    char clientfile_name[100];
    sprintf(clientfile_name, "%s_%s.txt", name, surname);

    char title[100], author[100];
    printf("Type the title of the book you want to donate: ");
    getchar();
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';
    printf("Type the author of the book you want to donate: ");
    fgets(author, sizeof(author), stdin);
    author[strcspn(author, "\n")] = '\0';

    int copies;
    printf("How many copies of the chosen book do you want to donate? ");
    scanf("%d", &copies);

    FILE *file_pointerB = fopen("books.txt", "a");
    if (file_pointerB == NULL) {
        printf ("-----------------------\n");
        printf("Error opening the file.\n");
        printf ("-----------------------\n");
        return;
    }

    int bookExists = 0;
    struct book temp;
    while (fscanf(file_pointerB, "Book Name: %[^\n]\nAuthor: %[^\n]\nQuantity: %d\n\n", temp.name, temp.author,
                  &temp.quantity) != EOF) {
        if (strcmp(title, temp.name) == 0 && strcmp(author, temp.author) == 0)
        {
            bookExists = 1;
            returnbook();
            fseek(file_pointerB, -1 * (strlen(temp.name) + strlen(temp.author) + 16), SEEK_CUR);
            break;
        }
    }
    if (!bookExists) {
        fprintf(file_pointerB, "Book Name: %s\nAuthor: %s\nQuantity: %d\n\n", title, author, copies);
    }

    fclose(file_pointerB);

    printf("Today's date (dd/mm/yy): ");
    scanf("%s", datetoday);

    FILE *file_pointerA = fopen(clientfile_name, "a");
    if (file_pointerA == NULL) {
        printf ("-----------------------\n");
        printf("Error opening the client's account file.\n");
        printf ("-----------------------\n");
        free(book);
        return;
    }
    fprintf(file_pointerA, "DONATION DATE: %s\n", datetoday);
    fprintf(file_pointerA, "BOOK TITLE: %s\n", title);
    fprintf(file_pointerA, "COPIES DONATED: %d\n\n\n", copies);
    fclose(file_pointerA);
    free(book);

    printf("-----------------------\n");
    printf("Thank you for donating!\n");
    printf("-----------------------\n");
    menu2();
}



void view() {
    char clientfile_name[100];
    sprintf(clientfile_name, "%s_%s.txt", name, surname);

    FILE *file_pointerA = fopen(clientfile_name, "r");
    if (file_pointerA == NULL) {
        printf ("-----------------------\n");
        printf("Error opening the client's account file.\n");
        printf ("-----------------------\n");
        return;
    }
    printf ("-----------------------\n");
    printf("Content of the client's account file:\n");
    printf ("-----------------------\n");
    char ch;
    while ((ch = fgetc(file_pointerA)) != EOF) {
        printf("%c", ch);
    }

    fclose(file_pointerA);
    menu2();
}



void search() {
    printf("Search for a book by:\n1. Title\n2. Author\n");
    printf("-----------------------\n");
    printf("Enter your choice (1 or 2): ");
    int choice;
    scanf("%d", &choice);
    printf("-----------------------\n");

    if (choice == 1) {
        char title[100];
        printf("Enter the title of the book: ");
        getchar();
        fgets(title, sizeof(title), stdin);
        title[strcspn(title, "\n")] = '\0';

        FILE *file_pointerB;
        file_pointerB = fopen("books.txt", "r");
        if (file_pointerB == NULL) {
            printf("Error opening the file.\n");
            return;
        }

        int found = 0;
        struct book temp;
        while (fscanf(file_pointerB, "Book Name: %[^\n]\nAuthor: %[^\n]\nQuantity: %d\n\n", temp.name, temp.author, &temp.quantity) == 3) {
            if (strcmp(title, temp.name) == 0) {
                printf ("-----------------------\n");
                printf("There are %d copies of the book \"%s\".\n", temp.quantity, temp.name);
                found = 1;
            }
        }

        fclose(file_pointerB);

        if (!found) {
            printf ("-----------------------\n");
            printf("Sorry, the book \"%s\" doesn't exist.\n", title);
            printf ("-----------------------\n");
        }
    }
    else if (choice == 2) {
        char author[100];
        printf("Enter the author's name: ");
        getchar();
        fgets(author, sizeof(author), stdin);
        author[strcspn(author, "\n")] = '\0';

        FILE *file_pointerB;
        file_pointerB = fopen("books.txt", "r");
        if (file_pointerB == NULL) {
            printf ("-----------------------\n");
            printf("Error opening the file.\n");
            printf ("-----------------------\n");
            return;
        }

        int found = 0;
        struct book temp;
        while (fscanf(file_pointerB, "Book Name: %[^\n]\nAuthor: %[^\n]\nQuantity: %d\n\n", temp.name, temp.author, &temp.quantity) == 3) {
            if (strstr(temp.author, author) != NULL)
            {
                printf ("-----------------------\n");
                printf("There are %d copies of the book \"%s\" by %s.\n", temp.quantity, temp.name, temp.author);
                printf ("-----------------------\n");
                found = 1;
            }
        }

        fclose(file_pointerB);

        if (!found) {
            printf("Sorry, there are no books by \"%s\".\n", author);
        }
    }
    else {
        printf ("-----------------------\n");
        printf("Invalid choice.\n");
        printf ("-----------------------\n");
    }
    menu2();
}



void menu2()
{
    int n;
    const char *user_file_name;
    printf("\n1.Borrow a book\n2.Return a book\n3.Donate a book\n4.Search for a book\n5.Go back to main menu\n6.View loans\n");
    printf ("-----------------------\n");
    printf("Please select an option(1/2/3/4/5/6):");
    scanf("%d", &n);
    if (n==1)
        borrow(&user_file_name);
    else if (n==2)
        returnbook();
    else if (n==3)
        donate();
    else if (n==4)
        search();
    else if (n==5)
        menu();
    else if (n==6)
        view();
    else
    {
        printf ("-----------------------\n");
        printf ("Option not available\n");
        printf ("-----------------------\n");
        menu2();
    }
}

void login()
{
    printf ("name:");
    scanf ("%s", &name);
    printf ("\n surname:");
    scanf("%s", &surname);
    int numclients=0, cnt=0;
    struct clients clients[100];
    FILE *file_pointerC;
    file_pointerC = fopen("clients.txt", "r");
    while(!feof(file_pointerC))
    {
        fscanf(file_pointerC, "%s", &clients[numclients].name);
        fscanf(file_pointerC, "%s", &clients[numclients].surname);
        numclients=numclients+1;
    }
    for (int i=0; i<numclients; i++)
    {
        if (strcmp(clients[i].name,name)==0 && strcmp(clients[i].surname,surname)==0)
        {
            cnt++;
            break;
        }
    }
    if (cnt==1)
    {
        printf ("\n-----------------------\n");
        printf ("Logged in successfully!\n");
        printf ("-----------------------\n");
        struct account * account;
        char s[100];
        strcpy(s, name);
        strcat(s, surname);
        const char accountfile_name[100];
        strcpy(accountfile_name, s);
        fopen(accountfile_name, "r");
        menu2();
    }
    else if (cnt==0)
    {
        printf ("-----------------------\n");
        printf ("There is no account with this name and surname. Try again or sign up.\n");
        printf ("-----------------------\n");
        menu();
    }

}


void signup()
{
    printf ("name:");
    scanf ("%s", name);
    printf ("\n surname:");
    scanf("%s", surname);
    struct clients clients[100];
    int numclients = 0;
    FILE *file_pointerC;
    file_pointerC = fopen("clients.txt", "r");
    if (file_pointerC == NULL)
    {
        printf ("-----------------------\n");
        printf("Error opening the file.\n");
        printf ("-----------------------\n");
        return;
    }
    while (fscanf(file_pointerC, "%s %s", clients[numclients].name, clients[numclients].surname) == 2)
    {
        numclients++;
    }
    fclose(file_pointerC);
    int cnt = 0;
    for (int i=0; i<numclients; i++)
    {
        if (strcmp(clients[i].name, name)==0 && strcmp(clients[i].surname, surname)==0)
        {
            cnt++;
            break;
        }
    }
    if (cnt==1)
    {
        printf ("-----------------------\n");
        printf ("There already exists an account with this name and surname. Try again or login.");
        printf ("-----------------------\n");
        menu();
    }
    else
    {
        file_pointerC = fopen("clients.txt", "a");
        if (file_pointerC == NULL) {
            printf("Error opening the file.\n");
            return;
        }
        fprintf(file_pointerC, "%s %s\n", name, surname);
        fclose(file_pointerC);

        char accountfile_name[100];
        sprintf(accountfile_name, "%s_%s.txt", name, surname);
        FILE *file_pointerA;
        file_pointerA = fopen(accountfile_name, "w");
        if (file_pointerA == NULL) {
            printf("Error creating the account file.\n");
            return;
        }
        printf ("-----------------------\n");
        printf("Account created successfully!\n");
        printf ("-----------------------\n");
        fclose(file_pointerA);
        menu2();
    }
}


void exit1()
{
    printf ("-----------------------\n");
    printf ("Thank you for visiting our library!\n");
    printf ("-----------------------\n");
}



int main() {
    struct book books[100];
    int numBooks = sizeof(books) / sizeof(books[0]);
    const char file_name[] = "books.txt";
    createBookFile(books, numBooks, file_name);

    struct clients clients[100];
    int numclients=sizeof(clients);
    const char clientsfile_name[] = "clients.txt";
    createclientsFile(clients , numclients, clientsfile_name);

    menu();
    return 0;
}