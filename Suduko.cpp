#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
void Display();
void gotoxy(int x, int y);
void ExchangeColumn(int *,int *);
void ExchangeRow(int (*row1)[9], int (*row2)[9]);
void ExchangeRowBlock(int , int );
void ExchangeColumnBlock(int , int );
void FillSuduko();
int SudukoControl();
void FillEntry(int);
void GenerateSuduko();
int SudukoChecker();
void SudukoStart();
void SystemTime();
void SudukoTerminate();
int Suduko[][9]={
                 {1,3,9,6,2,7,5,4,8},
                 {8,4,2,5,9,3,1,7,6},
                 {5,7,6,8,4,1,9,2,3},
                 {6,9,3,2,5,8,4,1,7},
                 {7,5,4,1,6,9,8,3,2},
                 {2,1,8,3,7,4,6,5,9},
                 {3,2,5,9,1,6,7,8,4},
                 {4,6,1,7,8,2,3,9,5},
                 {9,8,7,4,3,5,2,6,1}
               };
int SudukoAux[9][9]={0};
int SudukoAux1[9][9]={0};
int CurX=54,CurY=48;
int main()
{
    GenerateSuduko();
    Display();
    SudukoStart();
    FillSuduko();
    while(SudukoChecker())
    {
           int ch=SudukoControl();
           if(ch==0)
                    break;
           FillEntry(ch);
    }
    SudukoTerminate();
}
void Display()
{
     int i;
      
     for(i=0;i<=27;i++)
     {
						gotoxy(20,23+i);
                       for(int j=0; j<=36;j++)
                       {
                               if(i%3==0 && j==0 && i==0)
                                         printf("%c",201);
                               else if(i%3==0 && j==0 && i>0 && i<27)
                                         printf("%c",186);
                               else if(i==27 && j==0)
                                         printf("%c",200);
                               else if(i==0 && j==36)
                                    printf("%c",187);
                               else if(i==27 && j==36)
                                         printf("%c",188);
                               else if(i%3==0 && j==36 && i>0 && i<27)
                               {
                                    if(i==9 || i==18)
                                            printf("%c",185);
                                    else
                                            printf("%c",186);
                               }
                               else if(j%4==0 && i==0 && j>0 && j<36)
                               {
                                    if(j==12 || j==24)
                                            printf("%c",203);
                                    else
                                            printf("%c",205);
                               }
                               else if((i%3==0 && j%4==0)&& (j>1 && j<36 && i>0 && i<27))
                               {
                                    if((i==9 && j==12) || (i==9 && j==24) || (i==18 && j==12) || (i==18 && j==24))
                                            printf("%c",206);
                                    else if(i==9 || i==18)
                                            printf("%c",216);
                                    else if(j==12 || j==24)
                                            printf("%c",215);
                                    else
                                            printf("%c", 197);
                               }
                               else if(j%4==0 && i==27 && j>0 && j<36)
                               {
                                     if(j==12 || j==24)
                                            printf("%c",202);
                                    else
                                            printf("%c",205);
                               }
                               else if(i%3==0)
                               {
                                     if(i==0 || i==9 || i==18 || i==27)
                                            printf("%c",205);
                                    else
                                            printf("%c",196);
                               }
                               else if(j%4==0)
                               {
                                     if(j==0 ||j==12 || j==24 || j==36)
                                            printf("%c",186);
                                    else
                                            printf("%c",179);
                               }
                               else
                                          printf(" ");
                       }
                       printf("\n");
     }
}
void ExchangeRow(int (*row1)[9], int (*row2)[9])
{
     int i;
     for(i=0;i<9;i++)
     {
                     int temp= *(*row1+i);
                     *(*row1+i)=*(*row2+i);
                     *(*row2+i)=temp;
     }
}
void ExchangeColumn(int *column1, int *column2)
{
     int i;
     for(i=0;i<9;i++)
     {
                     int temp=*(column1+9*i);
                     *(column1+9*i)=*(column2+9*i);
                     *(column2+9*i)=temp;
     }
}
void ExchangeRowBlock(int block1, int block2)
{
     int i;
     for(i=0;i<3;i++)
     {
                     ExchangeRow(&Suduko[block1*3+i], &Suduko[block2*3+i]);
     }
}
void ExchangeColumnBlock(int block1, int block2)
{
     int i;
     for(i=0;i<3;i++)
     {
                     ExchangeColumn(&Suduko[0][block1*3+i],&Suduko[0][block2*3+i]);
     }
}
void gotoxy(int x, int y)
{
      COORD coord;
      coord.X = x;
      coord.Y = y;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void FillSuduko()
{
     HANDLE hStdout;
     hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
     SetConsoleTextAttribute(hStdout, 12);
    for(int i=0;i<9;i++)
    {
            for(int j=0;j<9;j++)
            {
                  gotoxy(22+4*j,24+3*i);
                  if(SudukoAux[i][j]!=0)
                       printf("%d",SudukoAux[i][j]);
                  else
                       printf(" ");
            }
            
    }
}
int SudukoControl()
{
     int ch,flag=1;
     HANDLE hStdout;
     hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
     gotoxy(CurX,CurY); 
     while(flag)
     {
     ch=getch();
     if(ch==224)
         ch=getch();
     if(ch>=49 && ch<=57)
     {
               flag=ch;
               ch=0;
     }
     switch(ch)
     	{
     	case 72:
     	    if(CurY>24 && CurY<=48)
     	                CurY=CurY-3;
            gotoxy(CurX,CurY);
     	break;
     	case 80:
     	     if(CurY >= 24 && CurY<48)
     	                 CurY=CurY+3;
           gotoxy(CurX,CurY);
     	break;
     	case 75:
     	     if(CurX>22 && CurX<=54)
     	                 CurX=CurX-4;
           gotoxy(CurX,CurY);
     	break;
     	case 77:
     	     if(CurX>=22 && CurX<54)
     	                 CurX=CurX+4;
           gotoxy(CurX,CurY);
     	break;
     	case 0:
         {
             int i=(CurY-24)/3;
             int j=(CurX-22)/4;
             if(SudukoAux1[i][j]!=0)
             {
                SetConsoleTextAttribute(hStdout, 12);
                printf("%d",SudukoAux1[i][j]);
                gotoxy(CurX,CurY);
             }
             else
             {
                 ch=flag;
                 flag=0;
             }
        break;
        }
        case 104:
        {
             int i=(CurY-24)/3;
             int j=(CurX-22)/4;
             if(SudukoAux[i][j]==0 || SudukoAux[i][j]!= Suduko[i][j])
             {
                                   SetConsoleTextAttribute(hStdout, 2);
                                   printf("%d",Suduko[i][j]);
                                   gotoxy(CurX,CurY);
                                   Sleep(1000);
                                   if(SudukoAux[i][j]!= Suduko[i][j] && SudukoAux[i][j]!=0 )
                                                        printf("%d",SudukoAux[i][j]);
                                   else
                                                        printf(" ");
                                   gotoxy(CurX,CurY);
             }
        break;
        }
        case 27:
             ch=flag=0;
        break;
     	}
      }
      return(ch);
}
void FillEntry(int ch)
{
     HANDLE hStdout;
     hStdout = GetStdHandle(STD_OUTPUT_HANDLE);     
     int i=(CurY-24)/3;
     int j=(CurX-22)/4;
     if(Suduko[i][j]!=ch-48)
             {
                         SetConsoleTextAttribute(hStdout, 2);
                         printf("%d",ch-48);
             }
     else
     {
                         SetConsoleTextAttribute(hStdout, 7);
                         printf("%d",ch-48);
     }
     SudukoAux[i][j]=ch-48;
}
void GenerateSuduko()
{
     int  i;
     int stime; 
     long ltime;  
     ltime = time(NULL); 
     stime = (unsigned) ltime/2; 
     srand(stime); 
     for(i=0;i<3;i++)
     {
                     int row1=rand();
                     int row2=rand();
                     ExchangeRow(&Suduko[row1%3+3*i],&Suduko[row2%3+3*i]);
     }
     for(i=0;i<3;i++)
     {
                     int row1=rand();
                     int row2=rand();
                     ExchangeColumn(&Suduko[0][row1%3+3*i],&Suduko[0][row2%3+3*i]);
     }
     for(i=0;i<3;i++)
     {
                     int row1=rand();
                     int row2=rand();
                     ExchangeRowBlock(row1%3,row2%3);
     }
     for(i=0;i<3;i++)
     {
                     int row1=rand();
                     int row2=rand();
                     ExchangeColumnBlock(row1%3,row2%3);
     }
     for(i=0;i<=35;i++)
     {
                       int random;
                       random=rand();
                       random= random%81;
                       int j=random%9;
                       random= random/9;
                       SudukoAux1[random][j]=SudukoAux[random][j]=Suduko[random][j];
     }
}
int SudukoChecker()
{
    int i,j,flag=0;
    for(i=0;i<9;i++)
    {
                    for(j=0;j<9;j++)
                    {
                                    if(SudukoAux[i][j]==0 || Suduko[i][j] != SudukoAux[i][j])
                                    {
                                                          flag=1;
                                                          break;
                                    }
                    }
                    if(flag==1)
                               break;
    }
    return flag;
}
void SudukoStart()
{
     HANDLE hStdout;
     hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hStdout, 15);
     gotoxy(0,5);
     printf("   Developed By  : ROHIT KUMAR TIWARI (BIET- JHANSI)\n\n");
     printf("   ESC  : Press ESC to QUIT\n\n");
     printf("   HINT : Press h for Hint\n\n");
     SetConsoleTextAttribute(hStdout, 7);
     printf("   %c%c  : Represent CORRECT Entry\n\n",178,178);
     SetConsoleTextAttribute(hStdout, 2);
     printf("   %c%c  : Represent WRONG Entry\n\n",178,178);
     SetConsoleTextAttribute(hStdout, 12);
     printf("   %c%c  : Represent PERMANENT Entry\n\n",178,178);
     SetConsoleTextAttribute(hStdout, 10);
     SystemTime();
     gotoxy(33,21);
     printf("SUDUKO GAME");    
}
void SystemTime()
{
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);
	printf("   Start Time: %dhh : %dmm : %ds",(str_t.wHour+6)%12,(str_t.wMinute+30)%60,str_t.wSecond);
}
void SudukoTerminate()
{
    gotoxy(22,53);
    printf("Thanx for Using this Application");
    Sleep(2000);
    exit(0);
}
