# Reversi

## Game Description 

Reversi is played on a board (like a chess board or a checkers board) that has dimensions n x n, where n is even. The game uses tiles that are white on one side, and black on the other side (they can be ''flipped'' over to change their colour). One player plays white; the other player plays black. 

A “turn” consists of a player laying a tile of his/her own colouron a candidate empty board position, subject to the following two rules:

1. There must be a continuous straight line of tile(s) of the opponent’s colour in at least one of the eight directions from the candidate empty position (North, South, East, West, and diagonals).

2. In the position immediately following the continuous straight line mentioned in #1 above, a tile of the player’s colour must already be placed.

After playing a tile at a position that meets the above criteria, all of the lines of the opponent’s tiles that meet the criteria above are flipped to the player’s colour.

The turns alternate between the players, unless one player has no available move, in which case  the  only  player  with  an  available  move  is  allowed  to  continue  to  make  moves  until  a move  becomes  available  for  the  opponent.  At  this  point,  the  opponent  is  allowed  to  take  a turn and the alternating turns between the players resumes. The game ends when either:

1. the entire board is full,or

2. neither player has an available move.

The overall objective is to flip the most opponent tiles (to your colour) so that at the end of the game, there is more tiles of your colour than the opponents'.

## Game Implementation

The implementation of the game was divided into two parts. The first part focused on configuring the board based on user inputs. It also printed out the list of possible moves for that player at that instant. It also learned to detect whether a move was valid and if so, flipped the tiles. 

The logic from part 1 was combined into part 2 to produce the full game. This part focused on completing the computer algorithm which plays against the human player. Two implementations were written. One is a greedy algorithm that aims to flip the most tiles with each iteration and another is a MiniMax algorithm, which aims to use a game tree to look into the future to decide on the most favorable move.

All code explained above can be found under the folders labelled part 1 and part 2. 

## Running the program

The program was run through an online interactive platform described here: https://github.com/Louis-He/reversi-reactjs

## Credit 

2021, APS105 Teaching Team, University of Toronto

