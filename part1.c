/*
 * File:        project_reversi_skeleton.c
 * Author:      APS105H1 Teaching Team
 * Modified by: * Yunjia Hao *
 *
 * Date: Jan 2021
 */
#include <stdio.h>
#include <stdbool.h>
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
bool checkMoveValidity(char colour, char charRow, char charCol, int Wsize,int Bsize,
  char validWRow[], char validWCol[],char validBRow[],char validBCol[])
{
	bool moveNotValid=true;

	if(colour=='W')
	{
		for(int i=0; i<Wsize; i++) //Check through avaiable positions in array
		{
			if(validWRow[i]==charRow && validWCol[i]==charCol){
        //If inputted values matches a position in the array of available positions. the move is valid
				moveNotValid=false;
				break;//Stop checking through available positions
			}
		}
	}
	else
	{
		for(int i=0; i<Bsize; i++)//Same logic
		{
			if(validBRow[i]==charRow && validBCol[i]==charCol){
				moveNotValid=false;
				break;
			}
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

void checkValidAndFlip(char board[][26], int row, int col, char colour, int n,bool flip)
{
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
						}
      	}
      }
    }
  }
}
#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE
int main(void) {

    int boardDim;

    /***********Get board dimensions and define variables*************/

    printf("Enter the board dimension: ");
    scanf("%d",&boardDim);
    char board[26][26],colour,charRow,charCol;

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
    /********************************************************************/
    printBoard(board, boardDim);//Prints board to terminal

    /********Obtaining board positions to insert to board until '!!!'**********/
    printf("Enter board configuration:\n");
    do {
        scanf(" %c%c%c",&colour,&charRow,&charCol);
        int row= charRow-'a'; //Convert char to int through char arithmetic
        int col= charCol-'a';
        board[row][col]=colour;
    } while(colour!='!' && charRow!='!' && charCol!='!'); //Keeps asking for input until '!!!'
/********************************************************************/
    printBoard(board, boardDim);//Prints current board

/**************Printing available moves for each player************************/
    char validWRow[26],validBRow[26],validWCol[26],validBCol[26];
    //Finds valid positions for W and B and stores the number of available positions
    int Wsize= findAndStorePositions(validWRow,validWCol,boardDim,board,'W');
    int Bsize = findAndStorePositions(validBRow,validBCol,boardDim,board,'B');

   printf("Available moves for W:\n");
   for(int i=0;i<Wsize;i++)
    printf("%c%c\n", validWRow[i],validWCol[i]);

  printf("Available moves for B:\n");
  for(int i=0;i<Bsize;i++)
    printf("%c%c\n", validBRow[i],validBCol[i]);
  /********************************************************************/
  printf("Enter a move:");
  scanf(" %c%c%c",&colour,&charRow,&charCol);
  bool moveNotValid = checkMoveValidity(colour,charRow,charCol,Wsize,Bsize,validWRow,validWCol,validBRow,validBCol);

	if(moveNotValid==true)//If move isn't valid
		printf("Invalid move.\n");
	else //If move is valid
	{
		printf("Valid move.\n");
		checkValidAndFlip(board,charRow-'a',charCol-'a',colour,boardDim,true);//Flip all remaining tiles
    board[charRow-'a'][charCol-'a']=colour;
  }
	printBoard(board, boardDim);

    return 0;
}
#endif // DO NOT DELETE THIS LINE
