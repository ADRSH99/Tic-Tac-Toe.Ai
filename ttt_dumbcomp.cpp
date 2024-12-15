#include <iostream>
#include <cctype>
#include <ctime>
#include <cstdlib>

static char array[3][3]={{' ', ' ', ' '},{' ', ' ', ' '},{' ', ' ', ' '}} ;
static int option;
static char playerchoice;
static char player2choice;
static int a;
static int b;
static char computerchoice;

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

void computerplay() 
{
        srand(time(0)); // Initialize random seed
        int row, col;
        while (true) {
            row = rand() % 3;
            col = rand() % 3;
            if (array[row][col] == ' ')
            {
                array[row][col] = computerchoice;
                std::cout << "\nComputer's move: " << ++row << " " << ++col << std::endl;
                break;
            }
        }
}
//answer=0 nobody wins 
//answer=1 user wins
//answer=2 computer wins
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
        if (array[i][0]==c && c==computerchoice)
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
        if (array[0][j]==c && c==computerchoice)
        {
            if (array[1][j]==c && array[2][j]==c) return answer+2;
        }
   }
   // diagonal checker
   if (array[0][0]==c && c==playerchoice)
   {
        if (array[1][1]==c && array[2][2]==c) return answer+1;
   }
   else if (array[0][0]==c && c==computerchoice)
   {
        if (array[1][1]==c && array[2][2]==c) return answer+2;
   }
   //opposite diagonal checker
   if (array[0][2]==c && c==playerchoice)
   {
        if (array[1][1]==c && array[2][0]==c) return answer+1;
   }
   else if (array[0][2]==c && c==computerchoice)
   {
        if (array[1][1]==c && array[2][0]==c) return answer+2;
   }

    if (answer==0) return answer;
}

void userinput()
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
    array[a][b]=playerchoice;
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
    std::cout << "Do you want to start first(1) or the computer(0)?";
    std::cin >> option;
    std::cout << "X or O?";
    std::cin >> playerchoice;
    if (playerchoice=='X') computerchoice='O';
    else computerchoice='X';
    int result=0;
    int boardstatus=isBoardFull();
    if (option==1 || option==0) 
    {

        if (option==1)
        {
            while (result==0 && boardstatus==false)
            {
               userinput();
               result=checker(playerchoice);
               writer();
               if (result==1) std::cout << "\nUser Won.";
               else if (result==2) std::cout << "\nUser Lost.";
               else 
               {
                computerplay();
                result=checker(computerchoice);
                writer();
                if (result==2) std::cout << "\nUser lost.";
                else if (result==1) std::cout << "\nUser Won.";
               }
               int boardstatus=isBoardFull();
            }
        }
        else if (option==0)
        {
            while (result==0 && boardstatus==false)
            {
                computerplay();
                result=checker(computerchoice);
                writer();
                std::cout << "\n";
                if (result==1) std::cout << "\nUser Won.";
                else if (result==2) std::cout << "\nUser Lost";
                else 
                {
                    userinput();
                    result=checker(playerchoice);
                    writer();
                    if (result==1) std::cout << "\nUser Won.";
                    else if (result==2) std::cout << "\nUser Lost.";
                }
                int boardstatus=isBoardFull();
            }
        }
        result=checker(playerchoice);
        int boardstatus=isBoardFull();
        if (boardstatus==true && result==0) std::cout << "\nDRAW";
    }
}