#include <iostream>
#include <cctype>
#include <ctime>
#include <cstdlib>

static char array[3][3]={{' ', ' ', ' '},{' ', ' ', ' '},{' ', ' ', ' '}} ;
static char playerchoice='X';
static char player2choice='O';
static int a;
static int b;

//dumb computer logic

void writer()
{
    char *pc=&array[0][0];
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if (j!=2)  std::cout << *pc << " | ";
            else if (j==2) std:: cout << *pc;
            pc++;        
        }
        if (i!=2) std::cout << "\n----------\n";
    }

}

//answer=0 nobody wins 
//answer=1 user wins
//answer=2 user 2 wins
int checker(char c)
{
   int answer=0;
   //row checker
   for (int i=0; i<3; i++)
   {
        if (array[i][0]==c && c==playerchoice)
        {
            if (array[i][1]==c && array[i][2]==c) return answer+1;
        }
        if (array[i][0]==c && c==player2choice)
        {
            if (array[i][1]==c && array[i][2]==c) return answer+2;
        }
   }

   //column checker
   for (int j=0; j<3; j++)
   {
        if (array[0][j]==c && c==playerchoice)
        {
            if (array[1][j]==c && array[2][j]==c) return answer+1;
        }
        if (array[0][j]==c && c==player2choice)
        {
            if (array[1][j]==c && array[2][j]==c) return answer+2;
        }
   }
   // diagonal checker
   if (array[0][0]==c && c==playerchoice)
   {
        if (array[1][1]==c && array[2][2]==c) return answer+1;
   }
   else if (array[0][0]==c && c==player2choice)
   {
        if (array[1][1]==c && array[2][2]==c) return answer+2;
   }
   //opposite diagonal checker
   if (array[0][2]==c && c==playerchoice)
   {
        if (array[1][1]==c && array[2][0]==c) return answer+1;
   }
   else if (array[0][2]==c && c==player2choice)
   {
        if (array[1][1]==c && array[2][0]==c) return answer+2;
   }

    if (answer==0) return answer;
}

void userinput(char c)
{
    std::cout << "\nEnter row-column (1-3)";
    std::cin >> a >> b;
    a--;
    b--;
    while (a < 0 || a >= 3 || b < 0 || b >= 3 || isalpha(array[a][b]) ) 
    {
        std::cout << "\nInvalid move. Try again: ";
        std::cin >> a >> b;
    }
    array[a][b]=c;
}

bool isBoardFull() 
{
    int count=0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) 
        {
            if (isalpha(array[i][j])) count++;
        }
    }
    if (count==9) return true;
    else return false;
}

int main()
{
    std::cout << "TIC TAC TOE\n";
    std::cout << "X plays first.";
    int result=0;
    int boardstatus=isBoardFull();
    while (result==0 && boardstatus==false)
            {
               userinput(playerchoice);
               result=checker(playerchoice);
               writer();
               if (result==1) std::cout << "\nUser X Won.";
               else if (result==2) std::cout << "\nUser O Lost.";
               else 
               {
                userinput(player2choice);
                result=checker(player2choice);
                writer();
                if (result==2) std::cout << "\nUser O lost.";
                else if (result==1) std::cout << "\nUser X Won.";
               }
               int boardstatus=isBoardFull();
            }
        
    result=checker(playerchoice);
    boardstatus=isBoardFull();
    if (boardstatus==true && result==0) std::cout << "\nDRAW";
}