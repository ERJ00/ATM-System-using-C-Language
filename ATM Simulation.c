/*

                                ATM Simulation Program

                            BANK NAME: Goldleaf Bank Inc.
    NOTE:

    Please before run the program make sure the flash drive that will be use
    is already have a one empty text file then name as "User Info.txt" and also another
    file then name as "Data Base.txt", the file of "Data Base.txt" put it in the same folder where
    your program file is and the other file "User Info.txt" please don't put the file inside of any folder
    in your flash drive.

    Also in "Data Base.txt" file please insert those information inside that file:

            sample data
            12345
            11/11/1111
            012345678910
            ;<=>
            11100

    Please check those lines and change the path location depending on where do you put your "User Info.txt" file
    on your flash drive:
        293
        310
        323
        378
        381
*/
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include<conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>


//--------------------------------------------------------------------------------
typedef struct info{
    int accountNum;
    char name[31];
    char birthday[31];
    char contactNum[12];
    char pin[6];
    int amount;
}USERINFO;

typedef struct node{
    USERINFO DATABASE;
    struct node* nxt;
}LIST;
LIST *L;

//--------------------------------------------------------------------------------
int accountNum;                     // GLOBAL VARIABLE
char name[31];
char birthday[31];
char contactNum[12];
char encryptedpin[6];
char decryptedpin[6];
char pin[6];
int money;

 //--------------------------------------------------------------------------------
void makenull();                    // FUNCTION DECLARATION
void firstMenu();
void getrecord();
int CheckIfRegistered();
int checkAccNum(int num);
void maxpin();
void add(USERINFO x);
void insertcard();
void removecard();
void savetocard(USERINFO x);
void savetoDB();
void retrievefromcard();
void retrievefromDB();
void encrypt();
void decrypt();
void cardpin();
int menu();
void withdraw();
void deposit();
void fundtransfer();
void updatecard();
void changepin();
void SetColor(int ForgC);
void gotoxy(int x,int y);
void setFontStyle(int FontSize);
void ShowConsoleCursor(int showFlag);
void delay(int milliseconds);
void displayinfo();
void screendisplay(int n);

//--------------------------------------------------------------------------------
                                    // MAIN FUNCTION
int main(){
    setFontStyle(30);
    screendisplay(1);
    srand(time(NULL));
    makenull();
    retrievefromDB();
    firstMenu();
    cardpin();
    while(1){
        menu();
    }
}

//--------------------------------------------------------------------------------
                                    // FUNCTION DEFINED

void makenull(){                    // MAKE NULL FUNCTION
    L=NULL;
}

void firstMenu(){                   // FIRST MENU FUNCTION
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    int pointer = 0;
    const char ENTER = 13;
    char ch = ' ';
    char Menu[][31] =  {"REGISTER YOUR CARD", "TRANSACTION MODE"};
    while (1){
        system("cls");
        ShowConsoleCursor(0);
        gotoxy(47,3);printf( "MENU\n\n");
        gotoxy(23, 11);printf("USE UP OR DOWN ARROW KEYS TO NAVIGATE THROUGH MENU");

        for(int i=0; i<2; ++i){
            if(i==pointer){
                SetConsoleTextAttribute(hConsole,BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
                gotoxy(40,6+i);printf("%s", Menu[i]);
            }else{
                SetConsoleTextAttribute(hConsole, 15);
                gotoxy(40,6+i);printf("%s\n",Menu[i]);
            }
             SetConsoleTextAttribute(hConsole, 15);
        }

        while(1){
            if(GetAsyncKeyState(VK_UP) != 0){
                delay(100);
                --pointer;
                if(pointer == -1){
                    pointer = 1;
                    }break;

            }else if(GetAsyncKeyState(VK_DOWN) != 0){
                delay(100);
                ++pointer;
                if(pointer == 2){
                    pointer = 0;
                }break;

            }else if(ch=getch() == ENTER){
                switch(pointer){
                    case 0:{
                        ShowConsoleCursor(1);
                        insertcard();
                    if (CheckIfRegistered()==1){
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 10);
                        gotoxy(33,7);printf("YOUR CARD IS ALREADY REGISTERED\n");
                        gotoxy(33,9);system("pause");
                        retrievefromcard();
                        return;break;
                    }
                    getrecord();retrievefromcard();return;break;
                    }
                    case 1:{
                        ShowConsoleCursor(1);
                        insertcard();
                    if (CheckIfRegistered()==1){
                        retrievefromcard();
                        return;break;
                    }
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 12);
                        gotoxy(35,7);printf("YOUR CARD IS NOT REGISTERED\n");
                        gotoxy(33,9);system("pause");
                    getrecord();retrievefromcard();return;break;
                    }
                }
                break;
            }
        }
    }
}

void getrecord(){                   // GET RECORD FUNCTION
    FILE *fp;
    USERINFO x;
    int num,checker;
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");
    SetConsoleTextAttribute(hConsole,11);
    gotoxy(40,2);printf("REGISTRATION MODE");
    SetConsoleTextAttribute(hConsole,15);
    gotoxy(20,5);printf("Input the Name: ");
    gotoxy(60,5);scanf(" %[^\n]s",x.name);
    gotoxy(20,7);printf("Input Date of Birth (MM/DD/YYYY): ");
    gotoxy(60,7);scanf(" %[^\n]s",x.birthday);
    gotoxy(20,9);printf("Input Contact Number: ");
    gotoxy(60,9);scanf(" %[^\n]s",x.contactNum);
    gotoxy(20,11);printf("Input PIN (4 digit only): ");
    gotoxy(60,11);maxpin();
    encrypt();
    strcpy(x.pin, pin);
    decrypt();
    num=rand()%99999+11111;
    checker=checkAccNum(num);
    while (checker!=0){
        num=rand()%99999+11111;
        checker=checkAccNum(num);
    }
    x.accountNum=num;
    gotoxy(20,13);printf("Your Account Number is %d",x.accountNum);
    gotoxy(35,15);system("pause");
    x.amount=10000;
    savetocard(x);
    add(x);
    fp=fopen("E:\\HaveAccount.txt","w");
    fclose(fp);
}

void maxpin(){                      // MAX PIN FUNCTION
    int index =0;
    char ch;
    while((ch=getch())!=13 && index<3){
        if (index<0)
            index=0;
    if(ch==8){
        putch('\b');
        putch(' ');
        putch('\b');
        index--;
     continue;
    }
    if(isdigit(ch)){
     pin[index++]=ch;
     putchar('*');
    }
    }
    if (index==3)
        pin[index++]=ch;
        pin[index]='\0';
}

void add(USERINFO x){
    LIST *p, *q, *temp;
    p=q=L;
    temp = (LIST*) ((malloc(sizeof(LIST))));
    temp->DATABASE=x;

    while (p!=NULL && p->DATABASE.name<x.name){
    q=p;
    p=p->nxt;
    }
        if (p==L)
            L=temp;
        else
            q->nxt = temp;
            temp->nxt = p;
}

int checkAccNum(int num){           // CHECK ACCOUNT NUMBER FUNCTION
    LIST *p, *q;
    p=q=L;

    while(p!=NULL && p->DATABASE.accountNum!=num){
        q=p;
        p=p->nxt;
    }
    if (p==NULL)
        return 0;
    else
        return 1;
}

int CheckIfRegistered(){            // CHECK IF REGISTERED FUNCTION
    FILE *fp;
    fp=fopen("E:\\HaveAccount.txt","r");    // Just change the (E:) depending in your drive name.
    fclose(fp);
    if (fp!=NULL){
        return 1;
    }
    else {
        return 0;
    }
}

void insertcard(){                  // INSERT CARD FUNCTION
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    FILE *fp;
    do{ system("cls");
        gotoxy(38,8);printf("Please insert card...");
        fp=fopen("E:\\User Info.txt","r");  // change the path location where your "User Info.txt" file is.
    } while(fp==NULL);
    fclose(fp);
    SetConsoleTextAttribute(hConsole, 15);
}

void removecard(){                  // REMOVE CARD FUNCTION
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
    FILE *fp;
    do{ system("cls");
        gotoxy(38,8);printf("Please remove card...");
        fp=fopen("E:\\User Info.txt","r");  // change the path location where your "User Info.txt" file is.
    } while(fp!=NULL);
    fclose(fp);
    screendisplay(2);
}

void encrypt(){                     // ENCRYPT PIN FUNCTION
    int i=0;
    while(pin[i]!='\0'){
        pin[i]=pin[i]+10;
        i++;
    }

}
void decrypt(){                     // DECRYPT PIN FUNCTION
    int i=0;
    while(pin[i]!='\0'){
        pin[i]=pin[i]-10;
        i++;
    }
}

void savetocard(USERINFO x){        // SAVE TO CARD FUNCTION
    FILE *fp;

    fp = fopen("E:\\User Info.txt","w+");   // change the path location where your "User Info.txt" file is.
    if (fp==NULL){
        printf("File not Exist!!!.\n");
        system("pause");
    }
    else {
        fprintf(fp,"%s\n%d\n%s\n%s\n%s\n%d\n",x.name,x.accountNum,x.birthday,x.contactNum,x.pin,x.amount);
    fclose(fp);
    }
}

void savetoDB(){                    // SAVE TO DATABASE FUNCTION
    FILE *fp;
    LIST *p;
    p=L;

    fp = fopen("Data Base.txt","w+");
    if (fp==NULL){
        printf("File not Exist!!!.\n");
        system("pause");
    }
    else {
        while (p!=NULL){
            fprintf(fp,"%s\n%d\n%s\n%s\n%s\n%d\n",p->DATABASE.name,p->DATABASE.accountNum,p->DATABASE.birthday,p->DATABASE.contactNum,p->DATABASE.pin,p->DATABASE.amount);
            p=p->nxt;
        }
    fclose(fp);
    }
}

void retrievefromcard(){            // RETRIEVE FROM CARD FUNCTION
FILE *fp;

    fp = fopen("E:\\User Info.txt","r+"); // change the path location where your "User Info.txt" file is.
    if (fp==NULL){
        printf("File error !!!\n");
        system("pause");
    }
    else {
        while(!feof(fp)){
            fscanf(fp,"%[^\n]%*c\n%d\n%[^\n]%*c\n%[^\n]%*c\n%[^\n]%*c\n%d\n",name,&accountNum,birthday,contactNum,encryptedpin,&money);
        }
        fclose(fp);
}
}

void retrievefromDB(){              // RETRIEVE FROM DATABASE FUNCTION
FILE *fp;
USERINFO x;

    fp = fopen("Data Base.txt","r+");
    if (fp==NULL){
        printf("File error !!!\n");
        system("pause");
    }
    else {
        while(!feof(fp)){
            fscanf(fp,"%[^\n]%*c\n%d\n%[^\n]%*c\n%[^\n]%*c\n%[^\n]%*c\n%d\n",x.name,&x.accountNum,x.birthday,&x.contactNum,x.pin,&x.amount);
            add(x);
        }
        fclose(fp);
}
}

void cardpin(){                     // CARD PIN FUNCTION
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (1){
        system ("cls");
        SetConsoleTextAttribute(hConsole, 15);
        gotoxy(42,5);printf("ENTER YOUR PIN");
        gotoxy(47,7);maxpin();
        encrypt();
        if (strcmp(pin,encryptedpin)==0){
            decrypt();
            strcpy(decryptedpin,pin);
            return;
        }
        SetConsoleTextAttribute(hConsole, 12);
        gotoxy(41,9);printf("Invalid PIN !!!");
        SetConsoleTextAttribute(hConsole, 15);
        gotoxy(35,11);system ("pause");
    }
}

int menu(){                         // MENU FUNCTION

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int pointer = 0;
    const char ENTER = 13;
    char ch = ' ';
    char Menu[][31]={"BALANCE INQUIRY","WITHDRAW","DEPOSIT","fUND TRANSFER","CHANGE PIN","DISPLAY INFORMATION","EXIT"};

    while (1){
        system("cls");
        ShowConsoleCursor(0);
        gotoxy(40,3);printf( "TRANSACTION MENU\n\n");
        gotoxy(23, 16);printf("USE UP OR DOWN ARROW KEYS TO NAVIGATE THROUGH MENU");
        int ii=0;
        for(int i=0; i<7; ++i){

            if(i==pointer){
                SetConsoleTextAttribute(hConsole,BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
                gotoxy(35,6+i);printf("%s", Menu[i]);
            }else{
                SetConsoleTextAttribute(hConsole, 15);
                gotoxy(35,6+i);printf("%s\n",Menu[i]);
            }
                SetConsoleTextAttribute(hConsole, 15);
        }

        while(1){
            if(GetAsyncKeyState(VK_UP) != 0){
                delay(100);
                --pointer;
                if(pointer == -1){
                    pointer = 6;
                    }break;

            }else if(GetAsyncKeyState(VK_DOWN) != 0){
                delay(100);
                ++pointer;
                if(pointer == 7){
                    pointer = 0;
                }break;

            }else if(ch=getch() == ENTER){
                switch(pointer){
                    case 0:{
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 11);
                        gotoxy(41,3);printf( "BALANCE INQUIRY");
                        SetConsoleTextAttribute(hConsole, 15);
                        gotoxy(35,6);printf("Your Balance :");
                        gotoxy(55,6);printf("PHP %d",money);
                        gotoxy(32,9);system("pause");break;
                        }
                    case 1:{
                        ShowConsoleCursor(1);
                        withdraw();break;
                        }
                    case 2:{
                        ShowConsoleCursor(1);
                        deposit();break;
                        }
                    case 3:{
                        ShowConsoleCursor(1);
                        fundtransfer();break;
                        }
                    case 4:{
                        ShowConsoleCursor(1);
                        changepin();break;
                        }
                    case 5:{
                        ShowConsoleCursor(1);
                        displayinfo();break;
                        }
                    case 6:{
                        ShowConsoleCursor(1);
                        updatecard();savetoDB();removecard();exit(0);break;
                        }
                    }
                    break;
                }
            }
        }
    }

void withdraw(){                    // WITHDRAW FUNCTION
    int withdrawAmount;
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (1){
        system("cls");
        SetConsoleTextAttribute(hConsole,11);
        gotoxy(45,3);printf( "WITHDRAW");
        SetConsoleTextAttribute(hConsole,15);
        gotoxy(33,6);printf("Enter the amount :");
        gotoxy(60,6);scanf("%d",&withdrawAmount);

        if (withdrawAmount%100==0 && withdrawAmount>0){
            if (withdrawAmount<=money){
                money=money-withdrawAmount;
                SetConsoleTextAttribute(hConsole,10);
                gotoxy(35,9);printf("You can now collect the cash");
                SetConsoleTextAttribute(hConsole,15);
                gotoxy(33,12);printf("Your current balance:");
                gotoxy(60,12);printf("PHP %d",money);
                gotoxy(32,15);system("pause");
            return ;
            }
            else {
                SetConsoleTextAttribute(hConsole,12);
                gotoxy(35,9);printf("You don't have enough money");
                gotoxy(32,11);system("pause");
            }
        }
        else {
            SetConsoleTextAttribute(hConsole,12);
            gotoxy(15,9);printf("You are requested to input the amount in multiples of 100, TRY AGAIN!!!\n");
            gotoxy(32,11);system("pause");
        }

    }
}

void deposit(){                     // DEPOSIT FUNCTION
    int amountDeposit;
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (1){
        system("cls");
        SetConsoleTextAttribute(hConsole,11);
        gotoxy(45,3);printf("DEPOSIT");
        SetConsoleTextAttribute(hConsole,15);;
        gotoxy(33,6);printf("Enter the amount :");
        gotoxy(60,6);scanf("%d",&amountDeposit);
        if (amountDeposit%100==0 && amountDeposit>0){
            money=money+amountDeposit;
            SetConsoleTextAttribute(hConsole,10);
                gotoxy(32,9);printf("You deposit PHP %d to your account",amountDeposit);
                SetConsoleTextAttribute(hConsole,15);
                gotoxy(33,12);printf("Your current balance:");
                gotoxy(60,12);printf("PHP %d",money);
                gotoxy(32,15);system("pause");
            return ;
        }
        SetConsoleTextAttribute(hConsole,12);
        gotoxy(15,9);printf("You are requested to input the amount in multiples of 100, TRY AGAIN!!!\n");
        gotoxy(32,11);system("pause");
    }
}

void fundtransfer(){                // FUND TRANSFER FUNCTION
    int num,amount;
    LIST *p, *q;
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (1){
        p=q=L;
        system("cls");
        SetConsoleTextAttribute(hConsole,11);
        gotoxy(42,3);printf("FUND TRANSFER");
        SetConsoleTextAttribute(hConsole,15);
        gotoxy(30,6);printf("Enter the account Number :");
        gotoxy(63,6);scanf("%d",&num);

        while(p!=NULL && p->DATABASE.accountNum!=num){
            q=p;
            p=p->nxt;
        }

        if (p==NULL){
            SetConsoleTextAttribute(hConsole,12);
            gotoxy(30,9);printf("Invalid Account Number, TRY AGAIN !!! ");
            gotoxy(32,11);system("pause");
        }

        else if (p->DATABASE.accountNum==accountNum){
            SetConsoleTextAttribute(hConsole,12);
            gotoxy(30,9);printf("Invalid Account Number, TRY AGAIN !!! ");
            gotoxy(32,11);system("pause");
        }

        else {
            while (1){
                system("cls");
                SetConsoleTextAttribute(hConsole,11);
                gotoxy(42,3);printf("FUND TRANSFER");
                SetConsoleTextAttribute(hConsole,15);
                gotoxy(30,6);printf("Enter the amount to transfer :");
                gotoxy(63,6);scanf("%d",&amount);
                if (amount%100==0 && amount>0){
                    if (amount<=money){
                        money=money-amount;
                        p->DATABASE.amount=p->DATABASE.amount+amount;
                        SetConsoleTextAttribute(hConsole,10);
                        gotoxy(25,9);printf("You transfer PHP %d to the account number %d",amount,p->DATABASE.accountNum);
                        SetConsoleTextAttribute(hConsole,15);
                        gotoxy(30,12);printf("Your current balance: ");
                        gotoxy(63,12);printf("PHP %d",money);
                        gotoxy(32,15);system("pause");
                        return ;
                    }
                    else {
                        SetConsoleTextAttribute(hConsole,12);
                        gotoxy(35,9);printf("You don't have enough money");
                        gotoxy(32,12);system("pause");
                    }
                }
                else {
                    SetConsoleTextAttribute(hConsole,12);
                    gotoxy(15,9);printf("You are requested to input the amount in multiples of 100, TRY AGAIN!!!");
                    gotoxy(32,12);system("pause");
                }
            }
        }
    }
}

void updatecard(){                  // UPDATE CARD FUNCTION
    USERINFO x;
    LIST *p, *q;
    p=q=L;

    x.accountNum=accountNum;
    x.amount=money;
    strcpy(x.birthday,birthday);
    strcpy(x.contactNum,contactNum);
    strcpy(x.name,name);
    strcpy(x.pin,encryptedpin);
    savetocard(x);

        while(p!=NULL && strcmp(p->DATABASE.name,x.name)!=0){
            q=p;
            p=p->nxt;
        }
        if (p==NULL){
        }
        else{
            p->DATABASE=x;
        }
}

void changepin(){                   // CHANGE PIN FUNCTION
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (1){
        system("cls");
        SetConsoleTextAttribute(hConsole,11);
        gotoxy(45,3);printf( "CHANGE PIN");
        SetConsoleTextAttribute(hConsole,15);
        gotoxy(33,6);printf("Enter your current PIN : ");
        gotoxy(60,6);maxpin();
        encrypt();

        if ((strcmp(pin,encryptedpin)==0)){
            gotoxy(33,9);printf("Enter your new PIN : ");
            gotoxy(60,9);maxpin();
            encrypt();
            strcpy(encryptedpin,pin);
            decrypt();
            strcpy(decryptedpin,pin);
            SetConsoleTextAttribute(hConsole,10);
            gotoxy(40,12);printf("Your new PIN is %s",pin);
            SetConsoleTextAttribute(hConsole,15);
            gotoxy(32,15);system("pause");
            return ;
        }
        else{
             SetConsoleTextAttribute(hConsole,12);
             gotoxy(44,9);printf("Invalid PIN");
             gotoxy(32,12);system("pause");
        }
    }

}

void gotoxy(int x,int y){           // GO TO X,Y FUNCTION
    COORD coord = {0,0};
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void SetColor(int ForgC){
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void setFontStyle(int FontSize){    // SET FONT SIZE/STYLE FUNCTION
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = FontSize;
    cfi.FontFamily = FF_DONTCARE;

    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void ShowConsoleCursor(int showFlag){   // SHOW CONSOLE CURSOR FUNCTION

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void delay(int milliseconds){       // DELAY FUNCTION

    //int milliseconds = 1000 * numberofseconds;
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds);
}

void displayinfo(){                 // DISPLAY INFORMATION FUNCTION
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");
    SetConsoleTextAttribute(hConsole,11);
    gotoxy(40,2);printf("USER INFORMTION");
    SetConsoleTextAttribute(hConsole,15);
    gotoxy(30,5);printf("NAME :");
    gotoxy(55,5);printf("%s",name);
    gotoxy(30,6);printf("ACCOUNT NUMBER :");
    gotoxy(55,6);printf("%d",accountNum);
    gotoxy(30,7);printf("BIRTHDAY :");
    gotoxy(55,7);printf("%s",birthday);
    gotoxy(30,8);printf("CONTACT NUMBER :");
    gotoxy(55,8);printf("%s",contactNum);
    gotoxy(30,9);printf("PIN :");
    gotoxy(55,9);printf("%s",decryptedpin);
    gotoxy(30,10);printf("BALANCE :");
    gotoxy(55,10);printf("%d",money);
    gotoxy(30,13);system("pause");

}

void screendisplay(int n){          // SCREEN DISPLAY FUNCTION

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (n==1){

        SetConsoleTextAttribute(hConsole,14);
        gotoxy(45,3);printf("WELCOME TO");
        gotoxy(40,6);printf("GOLDLEAF BANK INC.");
        gotoxy(30,10);system("pause");
    }

    else if (n==2){
        system("cls");
        SetConsoleTextAttribute(hConsole, 14);
        gotoxy(25,6);printf("THANK YOU FOR BANKING WITH GOLDLEAF BANK INC.\n\n\n");
        SetConsoleTextAttribute(hConsole, 15);

    }
}


