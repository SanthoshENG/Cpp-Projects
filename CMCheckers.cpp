#include <iostream>
#include <iomanip>
#include <string>
#include<cmath>

using namespace std;

//Global constants used throughout the program
const int MAX_ARRAY_SIZE = 18;
const int MIN_ARRAY_SIZE = 8;
const int MAX_PIECES = 72; 
const int NOPLAYER = 0;
const int WHITEWINS = 1;
const int REDWINS = 2;
const int NOONEWINS = 0;
const int WHITESOLDIER = 1;
const int WHITEMULE = 2;
const int WHITEKING = 3;
const int REDSOLDIER = 4;
const int REDMULE = 5;
const int REDKING = 6;
const int WHITEPLAYER = 1;
const int REDPLAYER = 2;

// Various Function Prototypes used in the main program

void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
                             int numRowsInBoard );
 
void DisplayBoard(const int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], 
int numRowsInBoard);
 
int CountJumps( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], 
int numRowsInBoard, int player, int xLocArray[], int yLocArray[] );
 
bool CheckList( int inArray1[], int inArray2[], int xIndex, int yindex);
 
int CountMove1Squares( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
int numRowsInBoard, int player, int xLocArray[],  int yLocArray[] );
 
bool IsMove1Squares( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], 
int numRowsInBoard, int player, int xLoc, int yLoc);
 
bool IsJump( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], 
int numRowsInBoard, int player, int xLoc, int yLoc);
 
bool MakeMove( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], 
int numRowsInBoard, int player, int fromSquareNum, 
int toSquareNum, bool &jumped );
 
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

int main()
{

//Variables used in the main program
int myCMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = {'\0'};
const int maxsquares=324;
 const int maxXYindices=18;
int xIndicesMove[maxXYindices] = {0}; 
int yIndicesMove[maxXYindices] = {0};
int xIndicesJump[maxXYindices] = {0};
int yIndicesJump[maxXYindices] = {0};
int numRowsInBoard = 0;
int counter = 0;
int terminate = 0;
const int MAXGUESS = 3;
int c=0;
int i = 0;
int j=0;
int TestBoard[maxsquares] = {'\0'};
bool jumped;
int Xval=0;
int Yval=0;
int jump;
int move;
bool move1;
bool jump1;
int player=0;
int squareNum=0;
int squareNumTo=0;
bool win;
int xindex=0;
int yindex=0;
int count=0;
int squarenum[maxsquares]={'\0'};
int Xval1=0;
int Yval1=0;
int totsquares=0;

// Checking and correcting errors for size of Checker Board
do
{
	cout << "Enter the number of squares along each edge of the board" << endl;
	
	if (!(cin >> numRowsInBoard))
	{
		cerr << "ERROR:  Board size is not an integer" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		counter++;
		continue;
	}

	if(numRowsInBoard > MAX_ARRAY_SIZE)
	{
		cerr << "ERROR:  Board size too large" <<  endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		counter++;
		continue;

	}
	
	else if (numRowsInBoard < MIN_ARRAY_SIZE)
	{
		cerr << "ERROR:  Board size too small" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		counter++;
		continue;
	}

	else if ( numRowsInBoard % 2 != 0 )
	{
		cerr << "ERROR:  Board size odd" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		counter++;
		continue;

	}
	else 
	{
		break;
	}

	

counter++;
}while(counter < MAXGUESS);

//Terminates the program if maximum number of tries is exceeded

if( counter >= MAXGUESS)
{
	cerr << "ERROR:  Too many errors entering the size of the board" << endl;
	return 1; 
}

totsquares=(numRowsInBoard*numRowsInBoard)-1;
//Prints intial board
InitializeBoard(myCMCheckersBoard,numRowsInBoard);

//Main loop which alternates between players
//Makes moves after checking for all possible errors and illegal moves
for(i=0; i<numRowsInBoard;i++)
{
	for(j=0;j<numRowsInBoard;j++)
	{
		TestBoard[count]=myCMCheckersBoard[i][j];
		squarenum[count]=count;
		count++;
	}
}
DisplayBoard(myCMCheckersBoard, numRowsInBoard);

win = CheckWin(myCMCheckersBoard, numRowsInBoard);
for ( c = 1; win == false ; c++)
{	
	if (c % 2 == 1)
	{
		player = 1;
	}
	else if (c % 2 == 0)
	{
		player = 2;
	}
	jump = CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump);

	move = CountMove1Squares( myCMCheckersBoard, numRowsInBoard, player, xIndicesMove, yIndicesMove);

	if ( jump == 0 && move == 0 && player == 1)
	{
		cout << "White is unable to move" << endl;
		cout << "GAME OVER, Red has won" << endl;
		cout << "Enter any character to close the game" << endl;
	
		if (!(cin>>terminate))
		{
			return 2;
		}
		else
		{
			return 3;
		}

	}
	else if ( jump == 0 && move == 0 && player == 2)
	{

		cout << "Red is unable to move" << endl;
		cout << "GAME OVER, White has won" << endl;
		cout << "Enter any character to close the game" << endl;
		if (!(cin>>terminate))
		{
			return 4;
		}
		else
		{
			return 5;
		}

	}
	else if ( jump > 0 || move > 0 )
	{
		if (player == 1)
		{
			cout << "White takes a turn" << endl;
		}
		else if (player == 2)
		{
			cout << "red takes a turn" << endl;
		}
	}
	do
	{
		cout << "Enter the square number of the checker you want to move" << endl;
		

		if (!(cin>> squareNum))
		{
			cerr << "ERROR:  you did not enter an integer" << endl;
			cerr << "Try again" << endl; 
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		counter = 0;
				for (i = 0; i < numRowsInBoard; i++)
				{
					for (j = 0; j < numRowsInBoard; j++)
					{
						if (counter == squareNum)
						{
	
							Xval = j;
							Yval = i;
						}
						counter++;
					}
				}
		if (squareNum > ((numRowsInBoard*numRowsInBoard)-1) || squareNum < 0)
		{
			cerr << "ERROR:  that square is not on the board." << endl; 
			cerr << "Try again" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		
		
		else if (myCMCheckersBoard[Yval][Xval] == NOPLAYER)
		{
			cerr << "ERROR:  that square is empty" << endl;
			cerr << "Try again" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else if(player==WHITEPLAYER && (myCMCheckersBoard[Yval][Xval]==REDKING || myCMCheckersBoard[Yval][Xval]==REDMULE || myCMCheckersBoard[Yval][Xval]==REDSOLDIER))	
				{
					cerr << "ERROR:  that square contains an opponent's checker" << endl << "Try again" << endl;
			        cin.clear();
			        cin.ignore(numeric_limits<streamsize>::max(), '\n');
			       continue;
				    }
	    else if(player==REDPLAYER && (myCMCheckersBoard[Yval][Xval]==WHITEKING || myCMCheckersBoard[Yval][Xval]==WHITEMULE || myCMCheckersBoard[Yval][Xval]==WHITESOLDIER))	
				{
					cerr << "ERROR:  that square contains an opponent's checker" << endl << "Try again" << endl;
			        cin.clear();
			        cin.ignore(numeric_limits<streamsize>::max(), '\n');
			       continue;
		        }
		
	    else if (jump != 0 && !(CheckList(xIndicesJump, yIndicesJump, Xval, Yval)))
		{
			counter = 0;
			cerr << "ERROR: You can jump with another checker, you may not move your chosen checker" << endl;
			cerr << "You can jump using checkers on the following squares:    " << endl; 
			
			for (j = 0; j < numRowsInBoard; j++)
			{
							if (CheckList(xIndicesJump, yIndicesJump, j, i)
								&&((player == REDPLAYER
								&&(myCMCheckersBoard[i][j] == REDKING
								|| myCMCheckersBoard[i][j] == REDMULE
								|| myCMCheckersBoard[i][j] == REDSOLDIER))
								|| (player == WHITEPLAYER
								&&(myCMCheckersBoard[i][j] == WHITEKING
								|| myCMCheckersBoard[i][j] == WHITEMULE
								|| myCMCheckersBoard[i][j] == WHITESOLDIER))))
							{
								cerr << counter << " ";
							}
							counter++;
						
				}
			
			cerr << "Try again" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else if (IsMove1Squares(myCMCheckersBoard,numRowsInBoard,player,Xval,Yval)==false && IsJump(myCMCheckersBoard,numRowsInBoard,player,Xval,Yval)==false )
		{
			cerr << "ERROR: There is no legal move for this checker" << endl;
			cerr << "Try again"<<endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else 
		{
			break;
		}
	}while(counter != -1);

	do
	{

		cout << "Enter the square number of the square you want to move your checker to" << endl;

		if (!(cin>> squareNumTo))
		{
			cerr << "ERROR:  you did not enter an integer" << endl;
			cerr << "Try again" << endl; 
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');		
			continue;
		}
		for (i = 0; i < numRowsInBoard; i++)
				{
					for (j = 0; j < numRowsInBoard; j++)
					{
						if (counter == squareNumTo)
						{
							Xval1 = j;
							Yval1 = i;
						}
						counter++;
					}
				}
		if (squareNumTo > ((numRowsInBoard*numRowsInBoard)-1) || squareNum < 0)
		{
			cerr << "ERROR:  It is not possible to move to a square that is not on the board." << endl; 
			cerr << "Try again" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else if (TestBoard[squareNumTo] != NOPLAYER)
		{
			cerr << "ERROR:  It is not possible to move to a square that is already occupied" << endl;
			cerr << "Try again" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else if(IsJump(myCMCheckersBoard,numRowsInBoard,player,Xval1,Yval1)==true && IsMove1Squares(myCMCheckersBoard,numRowsInBoard,player,Xval1,Yval1)==false)
	      {
			cerr << "ERROR:  You can jump with this checker, you must jump not move 1 space" << endl;
			cerr << "Try again" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;     
		}
		else 
		{
			
			move1 =MakeMove(myCMCheckersBoard, numRowsInBoard, player, squareNum, squareNumTo, jumped);
			DisplayBoard(myCMCheckersBoard, numRowsInBoard);

			if (move1 == false)
			{
			cerr << "ERROR: moving to that square is not legal, Try again" << endl;
			continue;
			}
			for (i = 0; i < numRowsInBoard; i++)
				{
					for (j = 0; j < numRowsInBoard; j++)
					{
						if (counter == squareNumTo)
						{
							Xval1 = j;
							Yval1 = i;
						}
						counter++;
					}
				}
			if (move1 == true)
			{
				if ( jumped == true)
				{
					squareNum=squareNumTo;
					jump1 = IsJump(myCMCheckersBoard, numRowsInBoard, player, Xval1, Yval1);
					
					while ( jump1 == true )
					{
					
						cout << "You can jump again,  Please enter the next square you wish to move your checker to" << endl;
					
						squareNum = squareNumTo;
						if (!(cin>> squareNumTo))
		             {
			          cerr << "ERROR:  you did not enter an integer" << endl;
			         cerr << "Try again" << endl; 
			         cin.clear();
			            cin.ignore(numeric_limits<streamsize>::max(), '\n');		
			                 continue;
		         }
		for (i = 0; i < numRowsInBoard; i++)
				{
					for (j = 0; j < numRowsInBoard; j++)
					{
						if (counter == squareNumTo)
						{
							Xval1 = j;
							Yval1 = i;
						}
						counter++;
					}
				}
		if (squareNumTo > ((numRowsInBoard*numRowsInBoard)-1) || squareNum < 0)
		{
			cerr << "ERROR:  It is not possible to move to a square that is not on the board." << endl; 
			cerr << "Try again" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else if (TestBoard[squareNumTo] != NOPLAYER)
		{
			cerr << "ERROR:  It is not possible to move to a square that is already occupied" << endl;
			cerr << "Try again" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else if(IsJump(myCMCheckersBoard,numRowsInBoard,player,Xval,Yval)==true && IsMove1Squares(myCMCheckersBoard,numRowsInBoard,player,Xval1,Yval1)==false)
	      {
			cerr << "ERROR:  You can jump with this checker, you must jump not move 1 space" << endl;
			cerr << "Try again" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;     
		}
	    move1 =MakeMove(myCMCheckersBoard, numRowsInBoard, player, squareNum, squareNumTo, jumped); 
		DisplayBoard(myCMCheckersBoard,numRowsInBoard);
					}
				}
			}
					
		}
	}while(move1==false);
	win=CheckWin(myCMCheckersBoard,numRowsInBoard);

}





return 0;
}

//Prints Initial Board
void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],int numRowsInBoard )
{
	int i=0;
	int j=0;
	for(i=0;i<numRowsInBoard;i++)
	{
		for(j=1;j<numRowsInBoard;j++)
		{
			if(i==0)
			{
				for(j=1;j<numRowsInBoard;j=j+2)
				{
				CMCheckersBoard[i][j]=2;
				}
			}
			else if(i==1)
			{
				for(j=0;j<numRowsInBoard;j=j+2)
				{

				CMCheckersBoard[i][j]=1;
			    }
			}
			else if(i==2)
			{
				for(j=1;j<numRowsInBoard;j=j+2)
				{
				CMCheckersBoard[i][j]=1;
				}
			}
			else if(i==3)
			{
				for(j=0;j<numRowsInBoard;j=j+2)
				{
				CMCheckersBoard[i][j]=1;
				}
			}
			else if((numRowsInBoard-i)==1)
			{
				for(j=0;j<numRowsInBoard;j=j+2)
				{
				CMCheckersBoard[i][j]=5;
				}
			}
			else if((numRowsInBoard-i)==2)
			{
				for(j=1;j<numRowsInBoard;j=j+2)
				{
				CMCheckersBoard[i][j]=4;
				}
			}
			else if((numRowsInBoard-i)==3)
			{
				for(j=0;j<numRowsInBoard;j=j+2)
				{
				CMCheckersBoard[i][j]=4;
				}
			}
			else if((numRowsInBoard-i)==4)
			{
				for(j=1;j<numRowsInBoard;j=j+2)
				{
				CMCheckersBoard[i][j]=4;
				}
			}
			else
			{
				CMCheckersBoard[i][j]=0;
			}

		}
	}

}

//Prints Display Board
void DisplayBoard( const int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{

	int r = 0;
	int c = 0;
	int count = 0; 
	string name;

	for( r= 0; r<numRowsInBoard; r++)
	{
	
		for( c= 0; c<numRowsInBoard; c++)
		{
			if ( CMCheckersBoard[r][c] == 1 )
			{
				cout<<setw(4) << "WS";
				name="WS";
			}
			else if(CMCheckersBoard[r][c] == 2)
			{
				cout<<setw(4) << "WM";
				name="WM";
			}
			else if(CMCheckersBoard[r][c] == 3)
			{
				cout<<setw(4) << "WK";
				name="WK";
			}
			else if(CMCheckersBoard[r][c] == 4)
			{
				cout<<setw(4) << "RS";
				name="RS";
			}
			else if(CMCheckersBoard[r][c] == 5)
			{
				cout <<setw(4)<< "RM";
				name="RM";
			}
			else if(CMCheckersBoard[r][c] == 6)
			{
				cout <<setw(4)<< "RK";
				name="RK";
			}
			else
			{
				cout<<setw(4)<<count;
			}
			  
			count++;
		}
		cout<<endl;
	}
}

// Checklist determines which checkers can be moved legally
bool CheckList( int inArray1[], int inArray2[], int xIndex, int yindex)
{
	int i=0;
	int j=0;
	int count=0;
	int count1=0;
	for(i=0;i<MAX_ARRAY_SIZE;i++)
	{
		if(inArray1[i]==xIndex)
		{
			count++;
		}
		if(inArray1[i]==yindex)
		{
			count1++;
		}
	}
	if(count>0 && count1>0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//The function returns an integer value which contains the number of the player’s checkers that can jump an opponent’s checker
int CountJumps( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], 
			   int numRowsInBoard, int player, int xLocArray[], int yLocArray[] )
{
	int i=0;
	int j=0;
	int jumps=0;
	for(i=0;i<numRowsInBoard;i++)
	{
		xLocArray[i]=-1;
	}
	for(i=0;i<numRowsInBoard;i++)
	{
		yLocArray[i]=-1;
	}
	for(i=0;i<numRowsInBoard;i++)
	{
		for(j=0;j<numRowsInBoard;j++)
		{
			if(player==1)
			{
				if(IsJump(CMCheckersBoard,numRowsInBoard,player,j,i)==true)
				{
					jumps++;
					xLocArray[j+1]=j;
					yLocArray[j+1]=i;

				}
			}
			if(player==2)
				{
				if(IsJump(CMCheckersBoard,numRowsInBoard,player,j,i)==true)
				{
					jumps++;
					xLocArray[j+1]=j;
					yLocArray[j+1]=i;

				}
			}
		}
	}
		return jumps;
	}

//Checks to see if the players checker is able to jump over an opponents checker
bool IsJump( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],int numRowsInBoard, int player, 
			int xLoc, int yLoc)

{
int count=0;
int count1=0;
int count2=0;
int count3=0;

	if(player==1)
	{
		if(CMCheckersBoard[yLoc][xLoc]==WHITEKING || CMCheckersBoard[yLoc][xLoc]==WHITEMULE || CMCheckersBoard[yLoc][xLoc]==WHITESOLDIER)
		{
			if(CMCheckersBoard[yLoc][xLoc]==WHITEKING)
			{
		
			if(CMCheckersBoard[yLoc+1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]== REDKING || CMCheckersBoard[yLoc+1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]==REDMULE ||
				CMCheckersBoard[yLoc+1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]==REDSOLDIER)

			    {
				if(CMCheckersBoard[yLoc+2][((xLoc+2)+numRowsInBoard)%numRowsInBoard]==0)
				{
                count++;
				}
			}
			
		if(CMCheckersBoard[yLoc+1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]== REDKING || CMCheckersBoard[yLoc+1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]==REDMULE ||
				CMCheckersBoard[yLoc+1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]==REDSOLDIER)

			    {
				if(CMCheckersBoard[yLoc+2][((xLoc-2)+numRowsInBoard)%numRowsInBoard]==0)
				{
                count++;
				}
		}
			if(CMCheckersBoard[yLoc-1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]== REDKING || CMCheckersBoard[yLoc-1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]==REDMULE ||
				CMCheckersBoard[yLoc-1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]==REDSOLDIER)

			    {
				if(CMCheckersBoard[yLoc-2][((xLoc+2)+numRowsInBoard)%numRowsInBoard]==0)
				{
                count++;
				}
			}
			if(CMCheckersBoard[yLoc-1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]== REDKING || CMCheckersBoard[yLoc-1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]==REDMULE ||
				CMCheckersBoard[yLoc-1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]==REDSOLDIER)

			    {
				if(CMCheckersBoard[yLoc-2][((xLoc-2)+numRowsInBoard)%numRowsInBoard]==0)
				{
                count++;
				}

			}
			if(count>0)
			{
				return true;
		    }
			}
			else if(CMCheckersBoard[yLoc][xLoc]==WHITEMULE || CMCheckersBoard[yLoc][xLoc]==WHITESOLDIER)
			{
		
			if(CMCheckersBoard[yLoc+1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]== REDKING || CMCheckersBoard[yLoc+1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]==REDMULE ||
				CMCheckersBoard[yLoc+1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]==REDSOLDIER)

			    {
				if(CMCheckersBoard[yLoc+2][((xLoc+2)+numRowsInBoard)%numRowsInBoard]==0)
				{
                count1++;
				}
			}
			
		if(CMCheckersBoard[yLoc+1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]== REDKING || CMCheckersBoard[yLoc+1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]==REDMULE ||
				CMCheckersBoard[yLoc+1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]==REDSOLDIER)

			    {
				if(CMCheckersBoard[yLoc+2][((xLoc-2)+numRowsInBoard)%numRowsInBoard]==0)
				{
                count1++;
				}
		     }
		if(count1>0)
		{
			return true;
		}
			}
		}
	}
	
	else if(player==2)
	{
		if(CMCheckersBoard[yLoc][xLoc]==REDKING || CMCheckersBoard[yLoc][xLoc]==REDMULE || CMCheckersBoard[yLoc][xLoc]==REDSOLDIER)
		{
			if(CMCheckersBoard[yLoc][xLoc]==REDKING)
			{
		
			if(CMCheckersBoard[yLoc+1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]==WHITEKING || CMCheckersBoard[yLoc+1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]==WHITEMULE ||
				CMCheckersBoard[yLoc+1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]==WHITESOLDIER)

			    {
				if(CMCheckersBoard[yLoc+2][((xLoc+2)+numRowsInBoard)%numRowsInBoard]==0)
				{
                count2++;
				}
			}
			
		if(CMCheckersBoard[yLoc+1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]== WHITEKING || CMCheckersBoard[yLoc+1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]==WHITEMULE ||
				CMCheckersBoard[yLoc+1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]==WHITESOLDIER)

			    {
				if(CMCheckersBoard[yLoc+2][((xLoc-2)+numRowsInBoard)%numRowsInBoard]==0)
				{
                count2++;
				}
		}
			if(CMCheckersBoard[yLoc-1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]== WHITEKING || CMCheckersBoard[yLoc-1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]==WHITEMULE ||
				CMCheckersBoard[yLoc-1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]==WHITESOLDIER)

			    {
				if(CMCheckersBoard[yLoc-2][((xLoc+2)+numRowsInBoard)%numRowsInBoard]==0)
				{
                count2++;
				}
			}
			if(CMCheckersBoard[yLoc-1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]== WHITEKING || CMCheckersBoard[yLoc-1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]==WHITEMULE ||
				CMCheckersBoard[yLoc-1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]==WHITESOLDIER)

			    {
				if(CMCheckersBoard[yLoc-2][((xLoc-2)+numRowsInBoard)%numRowsInBoard]==0)
				{
                count2++;
				}

			}
			if(count2>0)
			{
				return true;
		    }
			}
			else if(CMCheckersBoard[yLoc][xLoc]==REDMULE || CMCheckersBoard[yLoc][xLoc]==REDSOLDIER)
			{
		
			if(CMCheckersBoard[yLoc-1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]== WHITEKING || CMCheckersBoard[yLoc-1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]==WHITEMULE ||
				CMCheckersBoard[yLoc-1][((xLoc+1)+numRowsInBoard)%numRowsInBoard]==WHITESOLDIER)

			    {
				if(CMCheckersBoard[yLoc-2][((xLoc+2)+numRowsInBoard)%numRowsInBoard]==0)
				{
                count3++;
				}
			}
			
		if(CMCheckersBoard[yLoc-1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]== WHITEKING || CMCheckersBoard[yLoc-1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]==WHITEMULE ||
				CMCheckersBoard[yLoc-1][((xLoc-1)+numRowsInBoard)%numRowsInBoard]==WHITESOLDIER)

			    {
				if(CMCheckersBoard[yLoc-2][((xLoc-2)+numRowsInBoard)%numRowsInBoard]==0)
				{
                count3++;
				}
		     }
		if(count3>0)
		{
			return true;
		}
			}
		}
	}
	return false;
}


//Checks to see if the player can move one space diagonally
bool IsMove1Squares ( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
int numRowsInBoard, int player, int xLoc,  int yLoc )
{

int count=0;
int count1=0;
int count2=0;
int count3=0;

	if(player==1)
	{
		if(CMCheckersBoard[yLoc][xLoc]==WHITEKING || CMCheckersBoard[yLoc][xLoc]==WHITEMULE || CMCheckersBoard[yLoc][xLoc]==WHITESOLDIER)
		{
			if(CMCheckersBoard[yLoc][xLoc]==WHITEKING )
			{
			if(CMCheckersBoard[yLoc+1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]== REDKING || CMCheckersBoard[yLoc+1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]==REDMULE ||
				CMCheckersBoard[yLoc+1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]==REDSOLDIER || CMCheckersBoard[yLoc+1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]== WHITEKING || 
				CMCheckersBoard[yLoc+1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]==WHITEMULE || CMCheckersBoard[yLoc+1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]==WHITESOLDIER)
			{
				count2++;
			}
				
			if(CMCheckersBoard[yLoc+1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]== REDKING || CMCheckersBoard[yLoc+1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]==REDMULE ||
				CMCheckersBoard[yLoc+1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]==REDSOLDIER || CMCheckersBoard[yLoc+1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]== WHITEKING || 
				CMCheckersBoard[yLoc+1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]==WHITEMULE || CMCheckersBoard[yLoc+1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]==WHITESOLDIER)
			{
				count2++;
			}
			if(CMCheckersBoard[yLoc-1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]== REDKING || CMCheckersBoard[yLoc-1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]==REDMULE ||
				CMCheckersBoard[yLoc-1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]==REDSOLDIER || CMCheckersBoard[yLoc-1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]== WHITEKING || 
				CMCheckersBoard[yLoc-1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]==WHITEMULE || CMCheckersBoard[yLoc-1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]==WHITESOLDIER)
			{
				count2++;
			}
				
			if(CMCheckersBoard[yLoc-1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]== REDKING || CMCheckersBoard[yLoc-1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]==REDMULE ||
				CMCheckersBoard[yLoc-1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]==REDSOLDIER || CMCheckersBoard[yLoc-1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]== WHITEKING || 
				CMCheckersBoard[yLoc-1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]==WHITEMULE || CMCheckersBoard[yLoc-1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]==WHITESOLDIER)
			{
				count2++;
			}
			if(count2==4)
			{
				return false;
			}
			else
			{
				return true;
			
			}
			
		
			}





			else
			{
			
			if(CMCheckersBoard[yLoc+1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]== REDKING || CMCheckersBoard[yLoc+1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]==REDMULE ||
				CMCheckersBoard[yLoc+1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]==REDSOLDIER || CMCheckersBoard[yLoc+1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]== WHITEKING || 
				CMCheckersBoard[yLoc+1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]==WHITEMULE || CMCheckersBoard[yLoc+1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]==WHITESOLDIER)
			{
				count++;
			}
				
			if(CMCheckersBoard[yLoc+1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]== REDKING || CMCheckersBoard[yLoc+1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]==REDMULE ||
				CMCheckersBoard[yLoc+1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]==REDSOLDIER || CMCheckersBoard[yLoc+1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]== WHITEKING || 
				CMCheckersBoard[yLoc+1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]==WHITEMULE || CMCheckersBoard[yLoc+1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]==WHITESOLDIER)
			{
				count++;
			}
			
				
			if(count==2)
			{
				return false;
			}
			else 
			{
				return true;
			}

			}
		}
}

		if(player==2)
	{
		if(CMCheckersBoard[yLoc][xLoc]==REDKING || CMCheckersBoard[yLoc][xLoc]==REDMULE || CMCheckersBoard[yLoc][xLoc]==REDSOLDIER)
		{
			if(CMCheckersBoard[yLoc][xLoc]==REDKING )
			{
				if(CMCheckersBoard[yLoc+1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]== NOPLAYER)
			{
				count3++;
			}
				
				if(CMCheckersBoard[yLoc+1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]== NOPLAYER)
			{
				count3++;
			}
				if(CMCheckersBoard[yLoc-1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]== NOPLAYER)
			{
				count3++;
			}
				
				if(CMCheckersBoard[yLoc-1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]== NOPLAYER)
			{
				count3++;
			}
			if(count3>0)
			{
				return true;
			}
			else
			{
				return false;
			
			}
			}
			
			else if(CMCheckersBoard[yLoc][xLoc]==REDMULE || CMCheckersBoard[yLoc][xLoc]==REDSOLDIER)
			{

				if(CMCheckersBoard[yLoc-1][(((xLoc+1)+numRowsInBoard)%numRowsInBoard)]== NOPLAYER)
			{
				count1++;
			}
				
				if(CMCheckersBoard[yLoc-1][(((xLoc-1)+numRowsInBoard)%numRowsInBoard)]== NOPLAYER)
			{
				count1++;
			}

				
			if(count1>0)
			{
				return true;
			}
			else 
			{
				return false;
			}

		
		}
		}
		}
			
	return true;
}

//Checks to see if the player has a move that does not involve jumping over an opponent’s piece, if legal this function completes the move
int CountMove1Squares( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE],
int numRowsInBoard, int player, int xLocArray[],  int yLocArray[] )
{
	int i=0;
	int j=0;
	int moves=0;
	for(i=0;i<numRowsInBoard;i++)
	{
		xLocArray[i]=-1;
	}
	for(i=0;i<numRowsInBoard;i++)
	{
		yLocArray[i]=-1;
	}

	for (i=0; i<numRowsInBoard; i++)
	{
		for (j=0; j<numRowsInBoard;j++)
		{
			if(player==1){
				if(IsMove1Squares ( CMCheckersBoard,numRowsInBoard, player, j, i ) == true){
					moves++;
					xLocArray[j+1]=j;
					yLocArray[j+1]=i;	
				}
			if(player==2){
				if (IsMove1Squares ( CMCheckersBoard, numRowsInBoard, player, j, i ) == true){
					 moves++;
					xLocArray[j+1]=j;
					yLocArray[j+1]=i;	
				}
			}
			}
		}
	}
	return moves;
}

// Checks to see if the player's move is legal. If legal this function makes the move
  bool MakeMove( int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum,int toSquareNum, bool &jumped )
  {
	  int i=0;
	  int j=0;
	  int count=0;
	  int yindex=0;
	  int xindex=0;
	  int xindex1=0;
	  int yindex1=0;
	  int ch;
	  int xdistance=0;
	  int ydistance=0;
	  for(i=0;i<numRowsInBoard;i++)
	  {
		  for(j=0;j<numRowsInBoard;j++)
		  { 
			  if(count==fromSquareNum)
			  {
				  xindex=j;
				  yindex=i;
			  }
			  else if(count==toSquareNum)
			  {
				  xindex1=j;
				  yindex1=i;
			  }

			  count++;
		  }
	  }
	int xBefore = -10;
	int yBefore = -10;
	int xAfter = -10;
	int yAfter = -10;
	int xJump = -10;
	int yJump = -10;
	int xdelete=0;
	int ydelete=0;
	bool canjump=false;


	if ((xindex == numRowsInBoard - 1 && xindex1 == 0) || (xindex == 0 && xindex1 == numRowsInBoard - 1))
	{
		xdistance = 1;
	}
	else if ((xindex == numRowsInBoard - 2 && xindex1 == 0) || (xindex == 0 && xindex1 == numRowsInBoard - 2))
	{
		xdelete = numRowsInBoard - 1;
		xdistance = 2;
	}
		
	else if ((xindex == numRowsInBoard - 1 && xindex1 == 1) || (xindex == 1 && xindex1 == numRowsInBoard - 1))
	{
		xdelete = 0;
		xdistance = 2;
		
	}
	
	
	else
	{
	    if (xindex1 == xindex + 2)
		{
			xdelete = xindex + 1;
		}
	
		if (xindex1 == xindex - 2)
		{
			xdelete = xindex - 1;
		}
		xdistance = abs(xindex1 - xindex);
		
	}
	  ydistance=abs(yindex-yindex1);

	 if (yindex1 == yindex - 2)
	{
		ydelete = yindex - 1;
	}
	else if (yindex1 == yindex + 2)
	{
		ydelete = yindex + 1;
	}
	  if (((player == WHITEPLAYER 
		  && (CMCheckersBoard[ydelete][xdelete] == REDMULE
		||  CMCheckersBoard[ydelete][xdelete] == REDSOLDIER
		||  CMCheckersBoard[ydelete][xdelete] == REDKING))

		|| (player == REDPLAYER
		&& (CMCheckersBoard[ydelete][xdelete] == WHITEMULE
		||  CMCheckersBoard[ydelete][xdelete] == WHITESOLDIER
		||  CMCheckersBoard[ydelete][xdelete] == WHITEKING)))
		&& xdistance == 2
		&& xdelete != -10 && ydelete != -10)
	{
		canjump = true;
	}


	  if(ydistance>2)
	  {
		  cerr<<"Illegal move";
		  return false;
	  }
	  else if(xdistance==2 && ydistance==2)
	  {
		  if(yindex1>yindex && xindex1<xindex )
		  {
			  if(CMCheckersBoard[yindex+1][((xindex-1)+numRowsInBoard)%numRowsInBoard]==0)
			  {
				 cerr<<"Illegal move";
				 return false;
			  }
			 
		   }
		else if(yindex1>yindex && xindex1>xindex)
			{
				  if(CMCheckersBoard[yindex+1][((xindex+1)+numRowsInBoard)%numRowsInBoard]==0)
				  {
					  cerr<<"Illegal move";
					  return false;
				  }
		    }
		else if(yindex1<yindex && xindex1<xindex)
		{
			if(CMCheckersBoard[yindex-1][((xindex-1)+numRowsInBoard)%numRowsInBoard]==0)
			{
				cerr<<"Illegal move";
					return false;
			}
		}
		else if(yindex1<yindex && xindex1>xindex)
		{
			if(CMCheckersBoard[yindex-1][((xindex+1)+numRowsInBoard)%numRowsInBoard]==0)
			{
				cerr<<"Illegal move";
				return false;
			}
		}
	  }
	  else if(CMCheckersBoard[yindex][xindex]==REDMULE)
	  {
		  count++;
		  if(yindex1>yindex)
		  {
			  cerr<<"Illegal move";
			  return false;
		  }
	  }
	  else if(CMCheckersBoard[yindex][xindex]==REDSOLDIER)
	  {
		  count++;
		  if(yindex1>yindex)
		  {
			  cerr<<"Illegal move";
			  return false;
		  }
	  }
	  else if(CMCheckersBoard[yindex][xindex]==WHITEMULE)
	  {
		  count++;
		  if(yindex>yindex1)
		  {
			  cerr<<"Illegal move";
			  return false;
		  }
	  }
	  else if(CMCheckersBoard[yindex][xindex]==WHITESOLDIER)
	  {
		  count++;
		  if(yindex>yindex1)
		  {
			  cerr<<"Illegal move";
			  return false;
		  }
	  }
	  else if(CMCheckersBoard[yindex][xindex]==REDKING ||CMCheckersBoard[yindex][xindex]==WHITEKING)
	  {
		  count++;
	  }
	  if(count>0 && xdistance==ydistance)
    {
		  CMCheckersBoard[yindex1][xindex1]=CMCheckersBoard[yindex][xindex];
		  CMCheckersBoard[yindex][xindex]=NOPLAYER;
		  if(ydistance==2)
		  {
			  jumped=true;

		  }
		  if (canjump==true)
		  {
			  CMCheckersBoard[ydelete][xdelete]=NOPLAYER;
		  }

	  }
	  else 
	  {
		  return false;
	  }
	  if(CMCheckersBoard[yindex1][xindex1]==REDMULE || CMCheckersBoard[yindex1][xindex1]==REDSOLDIER)
	  {
		  if(yindex1==0  && CMCheckersBoard[yindex1][xindex1]==REDSOLDIER)
		  {
			  CMCheckersBoard[yindex1][xindex1]=REDKING;
		  }
		  else if(yindex1==0  && CMCheckersBoard[yindex1][xindex1]==REDMULE)
		  {
			  CMCheckersBoard[yindex1][xindex1]=8;
		  }
	  }
	  if(CMCheckersBoard[yindex1][xindex1]==WHITEMULE || CMCheckersBoard[yindex1][xindex1]==WHITESOLDIER)
	  {
		  if(yindex1==numRowsInBoard && CMCheckersBoard[yindex1][xindex1]==WHITESOLDIER)
		  {
			  CMCheckersBoard[yindex1][xindex1]=WHITEKING;
		  }
		  
			  
		  else if(yindex1==numRowsInBoard && CMCheckersBoard[yindex1][xindex1]==WHITEMULE)
		  {
			  CMCheckersBoard[yindex1][xindex1]=REDWINS;
		  }
	  }
	  if(CMCheckersBoard[yindex1][xindex1]!=REDWINS && CMCheckersBoard[yindex1][xindex1]!=WHITEWINS)
	  {
		  return true;
	  }
	  else if(CMCheckersBoard[yindex1][xindex1]==8)
	  {
		  cout<<"Red has created a MULE king,White wins the game"<<endl;
		  cout<<"Enter any character to terminate the game then press the enter key"<<endl;
		  cin>>ch;
		  if (!(cin>>ch))
		{
			return 4;
		}
		else
		{
			return 5;
		}
	  }
	  else if(CMCheckersBoard[yindex1][xindex1]==9)
	  {
		 cout<<" White has created a MULE King, Red wins the game"<<endl;
		 cout<<"Enter any character to terminate the game then press the enter key"<<endl;
		  cin>>ch;
	   if (!(cin>>ch))
		{
			return 4;
		}
		else
		{
			return 5;
		}


	  }
	  return true;
}

//Checks to see if and the how a player has won 
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	int i = 0;
	int j = 0;
	int countRed1 = 0;
	int countRed2 = 0;
	int countWhite1 = 0;
	int countWhite2 = 0;

	for( i = 0; i<numRowsInBoard; i++)
	{
	
		for( j = 0; j<numRowsInBoard; j++)
		{
			if(CMCheckersBoard[i][j] == 2)
			{
				countWhite1++;
			}
			if(CMCheckersBoard[i][j] == 5)
			{
				countRed1++;
			}
			if(CMCheckersBoard[i][j] == 1 || CMCheckersBoard[i][j] == 3)
			{
				countWhite2++;
			}
			if(CMCheckersBoard[i][j] == 4 || CMCheckersBoard[i][j] == 6)
			{
				countRed2++;
			}
		}

	}
	if (countWhite1 == 0)
	{
		cout << "The White Player has won the game by losing all of the White Mules" << endl;
	
		return true; 
	}
	else if(countRed1 == 0)
	{
		cout << "The Red Player has won the game by losing all of the Red Mules" << endl;

		return true;

	}	
	else if(countWhite2 == 0)
	{
		cout << "The Red Player has won by capturing all of the white players soldiers and kings" << endl;

		return true;
	}
	else if(countRed2 == 0)
	{
		cout << "The White Player has won by capturing all of the red players soldiers and kings" << endl;
		
		return true;
	}
	else
	{
		return false;
	}
}