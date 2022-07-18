//2434204
//Student Name: Irfaan Mia 

#include <iostream>
#include <fstream> 
#include <string> 
//For the randomize function 
#include <stdlib.h>
#include <time.h>
#include <vector> 
//Header for the display file
#include "Display.cpp"

using namespace std;


//Just call the CheckWinner function the rest of the functions will be called in that function
int CheckWinner(int Board[15][15], int n);
//Vertical check
bool Vertical(int Board[15][15],int row, int col, int player);
//Horizontal check 
bool Horizontal(int Board[15][15],int row , int col, int player);
//Diagonal right check
bool DiagonalRight(int Board[15][15],int row, int col, int player);
//Diagonal left check
bool DiagonalLeft(int Board[15][15],int row, int col, int player);
//Check if position is playable If the position is = 0 than it is playable 
bool IsPositionOpen(int Board[15][15], int row, int col); 
//Check if board is full
bool BoardFull(int Board[15][15],int n); 



int main()
{
    ifstream input; 
    ofstream output;
    //Board variables 
    int n; //board size = n 
    bool StillPlayable = true;  
    bool Player1Move = false; 
    bool Player2Move = false;  
    int row1,col1; 
    int row2,col2,temp2; 
    int Algorithm1Wins = 0; 
    int Algorithm2Wins = 0; 
    int draws = 0;  
    vector <string> outputdata; 
    //Board array initilized to zero
    int Board[15][15] = {0}; 
   


    input.open("input.txt"); 
    output.open("gomokuResults.txt"); 

    //Check if input.txt exist
    if(!input)
    {
        output << "The input.txt cannot be found" << endl; 
        exit(1); 
    }

    //Randomize the seed every game will use different random numbers 
    srand (time(NULL)); 

    while (input >> n)
    {
    //Display the size of the board to gomokuResults.txt and clear vector of moves
    output << "size=" << n << endl;
    outputdata.clear();
    //Reset the max board size
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15 ; j++)
        {
            Board[i][j] = 0; 
        }
    } 

    //Check if the board size requested is within the required range 
    if((n >= 6)and(n <=15))
    {
        //Algorithms start playing the new game
        while(StillPlayable == true)
        {
            //Algorithm one begins to play
            while(Player1Move == false)
            {
            //Random number from 0 to n-1
            row1 = rand() % n; 
            col1 = rand() % n; 

            //Check if the position is available 
            if(IsPositionOpen(Board,row1,col1) == true)
            {
                Board[row1][col1] = 1;
                Player1Move = true; 
                //Display move to the output textfile  
                Display disObj1(row1, col1, '1');
                //output << disObj1.getcomplete() << "\n";
                outputdata.push_back(disObj1.getcomplete());
            }
            }

            //Reset Player 1 move
            Player1Move = false;

            //Check if Alg1 won or board is full 
            if((CheckWinner(Board,n) == 1))
            {
                break; 
            }
            //If board is full and no winner reset board
            else if(BoardFull(Board,n) == true)
            {
            //Reset the max board size
            for (int i = 0; i < 15; i++)
            {
                for (int j = 0; j < 15 ; j++)
                {
                Board[i][j] = 0; 
                }
            }  
            outputdata.clear();   
            }

            //reset and declare variables used in algorithm 2
            bool above = true;  
            bool right = true; 
            bool left = true;
            bool below = true; 

            //Algorithm 2 starts to play
            while(Player2Move == false)
            {
            //Will determine where player2 will play either above,right,left or below
            temp2 = (rand()%4) + 1; 
            //Random number from 0 to n-1
            row2 = rand() % n; 
            col2 = rand() % n;

            if((temp2 == 1) and (above == true))
            {
                //Check if position above is open and is not out of the array index
               if ((IsPositionOpen(Board,row1 - 1,col1) == true) and (row1 - 1 >= 0))
                {
                row2 = row1 - 1;
                col2 = col1;
                Board[row1 - 1][col1] = 2; 
                //Need the statement to exit the loop
                Player2Move = true; 

                //Display the move to the output textfile 
                Display disObj2(row2, col2, '2');
                outputdata.push_back(disObj2.getcomplete());
                }
                else
                {
                    above = false; 
                }
            }
            else if ((temp2 == 2) and (right == true))
            { 
                //Check if the position to the right is open and is not out of the array index
                if ((IsPositionOpen(Board,row1,col1 + 1) == true) and (col1 + 1 < n))
                {
                row2 = row1;
                col2 = col1 + 1; 
                Board[row1][col1+1] = 2; 
                //Need the statement to exit the loop
                Player2Move = true; 

                //Display the move to the output textfile
                Display disObj2(row2, col2, '2');
                outputdata.push_back(disObj2.getcomplete());
                }
                else
                {
                    right = false;
                }
            }
            else if ((temp2 == 3) and (left == true))
            {
                //Check if position to the left is open and is not out of the array index
                if ((IsPositionOpen(Board,row1,col1 - 1) == true) and (col1 - 1 >= 0))
                {
                row2 = row1;
                col2 = col1 - 1;
                Board[row1][col1 - 1] = 2; 
                //Need the statement to exit the loop
                Player2Move = true; 
                 
                //Display the move to the output text file 
                Display disObj2(row2, col2, '2');
                outputdata.push_back(disObj2.getcomplete());
                }
                else
                {
                    left = false;
                }
            }
            else if ((temp2 == 4) and (below == true))
            {
                //Check if position below is open and is not out of the array index
                if ((IsPositionOpen(Board,row1 + 1,col1) == true) and (row1 + 1 < n))
                {
                row2 = row1 + 1;
                col2 = col1;
                Board[row1+1][col1] = 2; 

                //Need the statement to exit the loop
                Player2Move = true; 
                
                //Display the move to the output text file
                Display disObj2(row2, col2, '2');
                outputdata.push_back(disObj2.getcomplete());
                }
                else
                {
                    below = false;
                }
            }
            //if all the positions around player 1 is full
            if( (above == false) and (right  == false) and (left == false) and (below == false))
            {
                while(Player2Move == false)
                {
                 row2 = rand()%n; 
                 col2 = rand()%n; 
                 if (IsPositionOpen(Board,row2,col2) == true)
                 {
                 Board[row2][col2] = 2; 
                 //Need to exit loop
                 Player2Move = true; 

                 //Display Player 1 marker
                 Display disObj2(row2, col2, '2');
                 outputdata.push_back(disObj2.getcomplete());
                 }
                } 
            }

            }
            //Reset Player 2 move  
            Player2Move = false;


            //Check if Alg2 won or board is full after the move of alg2 
            if((CheckWinner(Board,n) == 2) )
            {
            //Will exit the loop
            break; 
            }
            else if(BoardFull(Board,n) == true)
            {
            //Reset the max board size if no winner and board full
            for (int i = 0; i < 15; i++)
            {
                for (int j = 0; j < 15 ; j++)
                {
                Board[i][j] = 0; 
                }
            } 
            outputdata.clear();   
            //output << "New game started due to a draw" << endl;   
            }



        }

        //Output the moves of the winning game of each algorithms
        for(int i = 0 ; i < outputdata.size(); i++)
        {
            output << outputdata[i] << endl; 
        }
        //Display who is the winner of each game and if the game ended in a draw
        if (CheckWinner(Board,n) == 1)
        {
        output<<"win=alg1"<<endl;
        output << endl;
        Algorithm1Wins += 1; 
        }
        else if(CheckWinner(Board,n) == 2)
        {
        output << "win=alg2" << endl;
        output<<endl;
        Algorithm2Wins += 1;  
        }

    }
    else 
    {
        //If board size is not in the accepted range
        output << "Invalid board size" << endl;
        output << endl; 
    }

    }
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << Board[i][j] << " "; 
        }
        cout << endl; 
    }
    //Output the final results of games played
    //output << endl; 
    output << "wins alg1=" << Algorithm1Wins << endl; 
    output << "wins alg2=" << Algorithm2Wins << endl;
    

    //Close the textfiles
    input.close();
    output.close();


    return 0;
}

//Algorithm 1 wins = 1, Algorithm 2 wins = 2, No one wins = 0
int CheckWinner(int Board[15][15], int n)
{
    int result = 0; 
    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0; j < n ; j++)
        {
            //If spot is 1
            if (Board[i][j] == 1)
            {
             //Check Vertical.(Will cover up and down)
             if((Vertical(Board,i,j,1) == true) and (i + 4 < n)) 
             {
                result = 1; 
             }
             //Check Horizontal
             else if((Horizontal(Board,i,j,1) == true) and (j + 4 < n))
             {
                 result = 1; 
             }
             //Check Diagonal Right
             else if((DiagonalRight(Board,i,j,1) == true) and (i - 4 >= 0) and ( j + 4 < n))
             {
                 result = 1; 
             }
             //Check Diagonal Left
             else if((DiagonalLeft(Board,i,j,1) == true) and (i - 4 >= 0 ) and (j - 4 >= 0))
             {
                 result = 1;
             }
            }

            //If spot is 2
            if(Board[i][j] == 2)
            {
             //Check for Vertical
             if((Vertical(Board,i,j,2) == true) and (i + 4 < n)) 
             {
                result = 2; 
             }
             //Check for Horizontal 
             else if ((Horizontal(Board,i,j,2) == true) and (j + 4 < n))
             {
                 result = 2; 
             }
             //Check Diagonal Right
             else if((DiagonalRight(Board,i,j,2) == true) and (i - 4 >= 0) and ( j + 4 < n))
             {
                 result = 2;
             }
             //Check Diagonal Left
             else if((DiagonalLeft(Board,i,j,2) == true) and (i - 4 >= 0 ) and (j - 4 >= 0))
             {
                 result = 2; 
             }
            }
            
           
        }
    }
    return result; 
}


bool Vertical(int Board[15][15],int row ,int col , int player)
{
    bool result = false; 
    if ((Board[row][col] == player))
    {
        if (Board[row+1][col] == player)
        {
            if (Board[row+2][col] == player)
            {
                if (Board[row+3][col] == player)
                {
                    if (Board[row+4][col] == player)
                    {
                        //Return a true to checkwinner function otherwise returns a false
                        result = true;
                    }
                }
            }
        }
    }
    return result; 
}


bool Horizontal(int Board[15][15],int row , int col, int player)
{
    bool result = false; 
    if (Board[row][col+1] == player)
    {
        if (Board[row][col+2] == player)
        {
            if (Board[row][col+3] == player)
            {
                if (Board[row][col+4] == player)
                {
                //Return a true to checkwinner function otherwise returns a false
                result = true;
                }
            }
        }
    }
    return result; 
}


bool DiagonalRight(int Board[15][15],int row, int col, int player)
{
    bool result = false; 
    if (Board[row][col] == player)
    {
        if (Board[row-1][col+1] == player)
        {
            if (Board[row-2][col+2] == player)
            {
                if (Board[row-3][col+3] == player)
                {
                    if (Board[row-4][col+4] == player)
                    {
                        //Return a true to checkwinner function otherwise returns a false
                        result = true;
                    }
                }
            }
        }
    }  
    return result; 
}


bool DiagonalLeft(int Board[15][15],int row, int col, int player)
{
    bool result = false; 
    if (Board[row][col] == player)
    {
        if (Board[row-1][col-1] == player)
        {
            if (Board[row-2][col-2] == player)
            {
                if (Board[row-3][col-3] == player)
                {
                    if (Board[row-4][col-4] == player)
                    {
                        //Return a true to checkwinner function otherwise returns a false
                        result = true;
                    }
                }
            }
        }
    } 
    return result; 
}

//Check if there is a space with a zero
bool BoardFull(int Board[15][15],int n)
{
    bool result = true; 
    for (int i = 0; i < n ; i++)
    {
        for(int j = 0; j < n ; j++) 
        {
            if (Board[i][j] == 0)
            {
                result = false;
                break; 
            }
        }
    }

    return result; 
}

//Check if position is taken or not
bool IsPositionOpen(int Board[15][15], int row, int col)
{
    //assume position is taken 
    bool result = false;  
    if (Board[row][col] == 0)
    {
        result = true; 
    }
    return result; 
}