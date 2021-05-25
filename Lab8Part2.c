/*
 * File:        project_reversi_skeleton.c
 * Author:      APS105H1 Teaching Team
 * Modified by: * Yunjia Hao *
 *
 * Date: Jan 2021
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "project_reversi_skeleton.h" // DO NOT modify this line
// ========= Function implementation ==========
/*
 * Function:  printBoard
 * --------------------
 * Print the whole board to the terminal window.
 */
void printBoard(char board[26][26], int n) {

    char firstLetter = 'a';
    /***************Print first row of letters************/
    printf("  ");
    for(char i = firstLetter;i<firstLetter+n;i++)
      printf("%c",i);
    printf("\n");
      /***************Print board************/
    for(int row=0;row<n;row++)
    {
      printf("%c ",firstLetter);//Prints starter letter for column
      for(int col=0; col<n;col++)
        printf("%c",board[row][col]);//Prints array element in board
      printf("\n");
      firstLetter++;//Prints the next letter
    }
}
/*
 * Function:  positionInBounds
 * --------------------
 * Checks whether the specified (row, col) lies within the board dimensions.
 */
bool positionInBounds(int n, int row, int col) {
    if(row>=n || col>=n || row<0 || col<0) //If element is off board return false
      return false;
    else
      return true;
}
/*
 * Function:  checkLegalInDirection
 * --------------------
 * Checks whether (row, col) is a legal position for a tile of colour by “looking” in the direction
 * specified by deltaRow and deltaCol.
 */
bool checkLegalInDirection(char board[26][26], int n, int row,
 		int col, char colour, int deltaRow, int deltaCol) {

  bool notLegal = false,foundValue=false;
  //If space is already occupied, automatically return false
  if(board[row][col]=='W'|| board[row][col]=='B')
    notLegal=true;
  if(notLegal==false) //If space is not occupied, execute
  {
    //For loop iterates until position out of bounds.
    for(int i=deltaRow,j=deltaCol;positionInBounds(n,row+i,col+j)==true; i+=deltaRow, j+=deltaCol)
    {
      //Check if the next element is the same colour, if the next position is out of bounds, if the next position is empty
      //If any of those are TRUE. The position is NOT valid.
      if(board[row+i][col+j]==colour||positionInBounds(n,row+i,col+j)==false|| board[row+i][col+j]=='U')
        notLegal=true;
        //If the position is still legal, check if position after that is in bounds,is of same colour.
        //If all facts are true, then this direction is legal
      if(positionInBounds(n,row+i+deltaRow,col+j+deltaCol)==true && board[row+i+deltaRow][col+j+deltaCol]==colour && notLegal==false)
        foundValue=true;
    }
  }
  return foundValue;//Returns whether the position is legal or not(bool type)
}
/*
 * Function:  findAndStorePositions
 * --------------------
 * Checks whether an empty position is legal by checking all 8 directions
 * If so, the legal position is stored in a row and col array. The size of the array
 *is also stored for iteration purposes.
 */
int findAndStorePositions(char validRow[],char validCol[], int n, char board[26][26],char colour)
{
  int size=0;
  //Iterate through all elements of the board
  for(int row=0; row<n;row++)
  {
    for(int col=0;col<n;col++)
    {
      bool foundValue=false;
      if(board[row][col]=='U') //If the position is empty, we check if it is legal
      {
        for(int deltaRow=-1;deltaRow<2 && foundValue==false;deltaRow++)//Checking all 8 directions
        {
          for(int deltaCol=-1;deltaCol<2 && foundValue==false;deltaCol++)
          {
            if(deltaCol==0 && deltaRow==0);//If the directions are both 0,don't do anything(not valid direction)
            else
            {
              if(checkLegalInDirection(board, n, row, col,colour, deltaRow, deltaCol)) //Check if position is legal if it is, execute
              {
                //Store row,col positions, increase current size of array
                validRow[size]=row+'a';
                validCol[size]=col+'a';
                size++;
                foundValue=true;//Set to true to scan next element in board
              }
            }
          }
        }
      }
    }
  }
  return size;
}
/*
 * Function:  checkMoveValidity
 * --------------------
 * Checks whether a move is valid by checking if the entered move matches one that is stored
 * is the available moves array. If it is valid, moveNotValid=false else, it is true.
 */
bool checkMoveValidity(char charRow,char charCol,int userSize, char userRowMoves[],char userColMoves[])
{
	bool moveNotValid=true;

	for(int i=0; i<userSize; i++) //Check through avaiable positions in array
	{
		if(userRowMoves[i]==charRow && userColMoves[i]==charCol){
      //If inputted values matches a position in the array of available positions. the move is valid
			moveNotValid=false;
			break;//Stop checking through available positions
		}
	}
  return moveNotValid;
}

/*
 * Function:  flipInDirection
 * --------------------
 * Function flips the tile in the valid direction
 */
void flipInDirection(int row,int col,char colour,char board[26][26])
{
  //If it is valid, then flip in direction(to the colour player we are working with)
	if(colour=='W')
	  board[row][col]='W';
	else
		board[row][col]='B';
}
/*
 * Function:  checkValidAndFlip
 * --------------------
 * Function checks if the specified position is valid in any of the 8 positions
 *If it is a valid position, it flips the tiles in those directions
 */
int checkValidAndFlip(char board[][26], int row, int col, char colour, int n,bool flip)
{
	int numFlipped=0;
	for(int deltaRow=-1;deltaRow<2 ;deltaRow++){//Checking all 8 directions
    for(int deltaCol=-1;deltaCol<2 ;deltaCol++){
      if(deltaCol==0 && deltaRow==0);//If the directions are both 0,don't do anything(not valid)
      else
      {
      	if(checkLegalInDirection(board, n, row,col, colour, deltaRow, deltaCol)){ //Check if direction is legal
      		for(int i=row+deltaRow,j=col+deltaCol; board[i][j]!=colour; i+=deltaRow, j+=deltaCol) //If it is, flip all elements until hits element of same colour
      			{
              if(flip)
							       flipInDirection(i,j,colour,board);
							numFlipped++;
						}
      	}
      }
    }
  }
	return numFlipped;
}

/*
 * Function:  makeMove
 * --------------------
 * The player "turn" makes a move at (row, col).
 * Note: This function MUST NOT change board, only row and col can be changed to reflect the move.
 */
/*int makeMove(const char board[26][26], int n, char turn, int *row, int *col) {

  char boardModify[26][26]; //Copy array into board that can be modified
  for(int i=0;i<n;i++)
  {
    for(int j=0; j<n; j++)
      boardModify[i][j]=board[i][j];
  }
  int numFlipped,max=0;
	bool flip=false;
	for(int i=0; i<n;i++)
	{
		for(int j=0; j<n; j++)
		{
			numFlipped = checkValidAndFlip(boardModify,i,j,turn,n,false);
			if(numFlipped>max)
			{
				max=numFlipped;
				*row=i;
				*col=j;
			}
		}
	}
	return max;
}*/

//Function that calculates the number of flipped positions for each valid comp play
void maxNumFlipped(char board[26][26],int n, char turn, int numFlipped[],char compRowMoves[],char compColMoves[],int compSize)
{
  for(int i=0;i<compSize;i++){ //Iterate through valid positions
      numFlipped[i]=checkValidAndFlip(board,compRowMoves[i]-'a',compColMoves[i]-'a',turn, n, false);
  }
}


void amountFlippedOpponent(char board[26][26],char compRowMoves[],char compColMoves[],int compSize,char turn,int n,int opponentMoves[])
{
  char boardModify[26][26],userTurn, validUserRows[26],validUserCols[26]; //Copy array into board that can be modified

  for(int i=0; i<compSize;i++)//Iterates through all valid positions
  {
    int row= compRowMoves[i]-'a', col = compColMoves[i]-'a';

    for(int i=0;i<n;i++)//Copy new board to "BoardModify"
    {
      for(int j=0; j<n; j++)
        boardModify[i][j]=board[i][j];
    }

      int numFlipped = checkValidAndFlip(boardModify,row,col,turn,n,true);//Flips modified board to new configuration
      boardModify[row][col]=turn;
      if(turn=='B')
        userTurn='W';
      else
        userTurn='B';
      opponentMoves[i] = findAndStorePositions(validUserRows,validUserCols,n,board,userTurn);//Stores number of moves available in this array
  }
  //Should return with number of opponent moves for each position
}

bool checkIfCornerPosition(int row,int col, int n)
{
  if((row==0 && col==0) || (row==0 && col==n-1) || (row==n-1 && col==0) || (row==n-1 && col==n-1))
    return true;
  else
    return false;
}

int positionWithHighestScore(int opponentMoves[], int numFlipped[], int n, int *row, int *col, int compSize,char compRowMoves[],char compColMoves[])
{
  //Formula
  int max=-30;

  for(int i=0; i<compSize; i++)
  {
    int rowPos=compRowMoves[i]-'a',colPos=compColMoves[i]-'a';
    bool isCornerPosition = checkIfCornerPosition(rowPos,colPos,n);
    //Compute score
    int score = opponentMoves[i] * -2 + isCornerPosition * 10+numFlipped[i] *5;
    if(score>max){
      max=score;
      *row = rowPos;
      *col = colPos;
    }
  }
  return max;
}

int makeMove(const char board[26][26],int n, char turn, int *row, int *col){

  char boardModify[26][26]; //Copy array into board that can be modified
  for(int i=0;i<n;i++)
  {
    for(int j=0; j<n; j++)
      boardModify[i][j]=board[i][j];
  }
  char compRowMoves[26],compColMoves[26];
  int compSize =findAndStorePositions(compRowMoves,compColMoves,n,boardModify,turn);
  int numFlipped[compSize],opponentMoves[compSize];

  //Returns number flipped of own colour after placement
  maxNumFlipped(boardModify,n,turn,numFlipped,compRowMoves,compColMoves,compSize);
  //Returns number of spaces for next player if placed at that location
  amountFlippedOpponent(boardModify,compRowMoves,compColMoves,compSize,turn,n,opponentMoves);

  //Returns the row and col positions that maximizes certain conditions
  int maxScore= positionWithHighestScore(opponentMoves,numFlipped, n, row, col, compSize, compRowMoves, compColMoves);

  return maxScore;
}

bool boardFilled(char board[26][26],int n)
{
  bool boardFilled=true;
  for(int i=0; i<n;i++)
  {
    for(int j=0; j<n;j++)
    {
      if(board[i][j]=='U')
        boardFilled=false;
    }
  }
  return boardFilled;
}


#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE
int main(int argc, char **argv)
{
	int boardDim;
  /***********Get board dimensions and define variables*************/
  printf("Enter the board dimension: ");
  scanf("%d",&boardDim);
  char board[26][26],charRow,charCol;

  /***********Initialize initial board configuration*************/
  for(int row=0; row<26; row++)   //For loop for rows
  {
    for(int col=0; col<26;col++)  //For loop for columns
    {
      if((col== boardDim/2-1 && row==boardDim/2-1)|| (col==boardDim/2 && row==boardDim/2))
          board[row][col]= 'W';//Assigns to white
      else if((col==boardDim/2-1 && row==boardDim/2) || (col==boardDim/2 && row==boardDim/2-1))
        board[row][col]='B';//Assigns to black
      else
        board[row][col]='U';//Assign to U
    }
  }

  //Finds valid positions for Computer and User and stores the number of available positions
	char compRowMoves[26],compColMoves[26],userRowMoves[26],userColMoves[26],turn='B',compPlay,userPlay;
	int compSize,userSize,*row=(int *)malloc(sizeof(int)),*col=(int *)malloc(sizeof(int));


	bool notEnd=true;
	printf("Computer plays (B/W) : ");
	scanf(" %c",&compPlay);

	printBoard(board, boardDim);
	while(notEnd==true)
	{
    if(compPlay=='B')
  	{
  		compSize =findAndStorePositions(compRowMoves,compColMoves,boardDim,board,'B');
  		userSize= findAndStorePositions(userRowMoves,userColMoves,boardDim,board,'W');
  		userPlay = 'W';
  	}
  	else
  	{
  		compSize = findAndStorePositions(compRowMoves,compColMoves,boardDim,board,'W');
  		userSize = findAndStorePositions(userRowMoves,userColMoves,boardDim,board,'B');
  		userPlay = 'B';
  	}
	  bool noMoreUserMoves=false,invalidMove,noMoreCompMoves=false;
		if(compPlay==turn)
		{
			//Comp go first
			int maxFlipped= makeMove(board,boardDim,turn,row,col);
			if (maxFlipped>-30)
			{
				int numFlipped = checkValidAndFlip(board,*row,*col,turn,boardDim,true);
        board[*row][*col]=turn;
        if(boardFilled(board,boardDim)==true)
          noMoreCompMoves=true;
				printf("Computer places %c at %c%c.\n",compPlay,*row+'a',*col+'a');
				printBoard(board, boardDim);
			}
			else
				noMoreCompMoves=true;
	  }
	  else
	  {
			//User goes first
      if(userSize>0)
      {
        findSmarterMove(board, boardDim, turn, charRow, charCol);
        printf("Testing AI move (row, col): %c%c\n", row + 'a', col + 'a');
    		/*printf("Enter move for colour %c (RowCol): ",userPlay);
    		scanf(" %c%c",&charRow,&charCol);*/
    		bool invalidMove = checkMoveValidity(charRow,charCol,userSize,userRowMoves,userColMoves);
        if(invalidMove==true)
        {
          printf("Invalid move.\n"); //If user enters an invalid move. Game terminates
          printf("%c player wins.\n",compPlay);
          notEnd=false;
        }
    		else //Place at location and flip tiles
    		{
    		  int numFlipped = checkValidAndFlip(board,charRow-'a',charCol-'a',turn,boardDim,true);
          board[charRow-'a'][charCol-'a']=turn;
          if(boardFilled(board,boardDim)==true)
            noMoreUserMoves=true;
    			printBoard(board, boardDim);
    		}
  	  }
      else
        noMoreUserMoves=true;
    }
		//If the opposite player has a move, should switch players
		if((compPlay==turn && noMoreUserMoves==false) || (userPlay==turn && noMoreCompMoves==false))
		{
			if(turn=='B')
				turn='W';
			else
				turn='B';
		}
    //If both players have moves, nothing happens.

    //If the next player has no moves, then the turn shouldn't switch and nothing will happen.
    //The same player plays again
    if(notEnd==true)
    {
      if(noMoreUserMoves==true && noMoreCompMoves==false && boardFilled(board,boardDim)==false)
        printf("%c player has no valid move.\n",userPlay);
      else if(noMoreUserMoves==false && noMoreCompMoves==true && boardFilled(board,boardDim)==false)
        printf("%c player has no valid move.\n",compPlay);
  		//Compare which player has more tiles taken up depending on which one has more print the options
  		else if(noMoreCompMoves==true && noMoreUserMoves==true || boardFilled(board,boardDim)==true)
  		{
        int compCount=0,userCount=0;
  			for(int i=0;i<boardDim;i++)
  			{
  				for(int j=0; j<boardDim;j++)
  				{
  					if(board[i][j]==compPlay)
  						compCount++;
  					else if(board[i][j]==userPlay)
  						userCount++;
  				}
  			}
  			if(compCount>userCount)
  				printf("%c player wins.\n",compPlay);
  			else if(userCount>compCount)
  				printf("%c player wins.\n",userPlay);
  			else
  				printf("Draw!\n");
  			notEnd=false;
  		}
    }
	}
	return 0;
}


#endif // DO NOT DELETE THIS LINE

