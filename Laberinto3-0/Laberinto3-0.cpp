//============================================================================
// Name        : Labrynth3-0.cpp
// Author      : Ivan Santiago Gutierrez Estrada (& Rogelio, en la version 1.0)
// Version     : 3.0-Windows
// Copyright   : Made for school
// Description : labrynth, final version.
//============================================================================



/*NOTA PARA DANI: El programa requiere de sonido, y hay que configurar unas cosas como en este link:https://www.youtube.com/watch?v=9WeDQHi6sJs */
/*Si no tienes tiempo, Busca "PlaySound(TEXT("Gamegame.wav"), NULL, SND_ASYNC);" y coméntalo para que jale el programa*/


#pragma region libraries

#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <array> 
#include <stdlib.h>
#include <tuple> 
#include <time.h>
#include <chrono>
#include <thread>
#include "LabrrynthClasses.h"
// <curses.h>

#pragma endregion

//definitions to include arrow movement
#define KEY_UP 72
#define KEY_DOWN 'á'
#define KEY_LEFT 75
#define KEY_RIGHT 77

//unnecesary writting avoidance
using namespace std;

/*Declaring vars that are used throughout the program*/
#pragma region globalVars 

//position vars
int userLinePosition, userColumnPosition, UserCurrentLevel;

//some aux vars that need to be here...
int auxBossHealth, auxUserHealtrh;

//health of user 
int userHealth = 5;

//counter to regen health
int counterToRegenHealth = 3;

//char to save user input
char userDecision;

//bool to make continue aviable
bool isContinueAviable = true;

//bool to know if user is on a spike
bool isUserOnASpike = false;

//bool to control fight
bool isFightEngaged = false;

//keep track of the score (set to 0 for bug prevention purposes)
int score = 0;

//bool to end the game
bool Continuethegame = true;

//bool to prevent final battle repetition
bool HasFinalBattleOccured = false;

//bool to reset the game if needed (set to false for bug prevention purposes)
bool resetPointsCounter = false;

//bools to keep track of the points
bool HasUserWon;

//bool to set if the cracken has been released
bool IsTHE_BOSS_Released = false;

//string for a message if needed...
string message;



#pragma endregion

/*Array for levels*/
#pragma region AllLevelsInOneArray

//array that has all the levels
char Laberinto[3][20][20]
{

	{//LEVEL1                   4                        9                        14                       19
			{'#','#','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
			{'#',' ',' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#'},
			{'#','#','#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', ' ', ' ', '#'},
			{'#',' ',' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', '#', '#', ' ', '#'},
	   /*4*/{'#',' ','#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', ' ', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', '#', '#'},
			{'#',' ','#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', ' ', ' ', '#'},
			{'#',' ','#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', '#', '#', ' ', '#'},
			{'#',' ','#', ' ', '#', '#', ' ', '#', ' ', ' ', ' ', '#', '#', '#', ' ', '#', ' ', ' ', ' ', '#'},
	   /*9*/{'#',' ','#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', '#', '#'},
			{'#',' ','#', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', ' ', ' ', '#'},
			{'#',' ','#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', '#', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', ' ', ' ', '#'},
			{'#',' ','#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', '#', '#'},
	  /*14*/{'#',' ','#', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ', ' ', ' ', '#'},
			{'#',' ','#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', '#', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', '#', '#', ' ', '#', ' ', ' ', ' ', '#'},
			{'#',' ','#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#'},
			{'#',' ',' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' '},
	  /*19*/{'#','#','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
	},

	{//LEVEL2                   4                        9                        14                       19
			{'#','#','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
			{'#',' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
			{'#',' ','#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
	   /*4*/{'#',' ','#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
			{'#',' ','#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
			{'#',' ','#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
	   /*9*/{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
			{'#',' ','#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', '#', ' ', '#'},
	  /*14*/{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', '#', '#', '#', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
			{'#',' ','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
			{' ',' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	  /*19*/{'#','#','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
	},

	{//LEVEL3                   4                        9                        14                       19
			{'#','#','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
			{' ',' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
			{'#','#','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
			{'#',' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
	   /*4*/{'#',' ','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
	   /*9*/{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
			{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
	  /*14*/{'#',' ','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
			{'#',' ','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
			{'#',' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
			{'#','#','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#'},
			{'#',' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
	  /*19*/{'#','#','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#'}
	},
};

#pragma endregion

/*classes fo the game*/
#pragma region Classes

/*making an array of the points for easier management*/
Points point[10]
{
	{0, 0, 10, 4, false},
	{1, 0, 8,  8, false},
	{2, 0, 16, 8, false},
	{3, 1, 1,  1, false},
	{4, 1, 1,  3, false},
	{5, 1, 12, 6, false},
	{6, 2, 12, 1, false},
	{7, 2, 13, 1, false},
	{8, 2, 14, 1, false},
	{9, 2, 16, 1, false}
};

//Making an array of doors for easier management
THEDOORS Door[3]
{
	{0, 0, 18, 19, 3},
	{1, 1, 1,  19, 6},
	{2, 2, 19,16, 10}
};

//making an array of static enemies for easier management
staticEnemy spikes[7]
{
	{0,  9,  3},
	{1,  1,  2},
	{1,  2,  3},
	{1,  6,  3},
	{1, 10,  3},
	{1,	 1, 17},
	{2, 15,  1}
};

//making a class for THE BOSS
dinamicEnemy THE_BOSS(2, 16, 4, 20);

#pragma endregion

/*Shouting the existence of these funtions*/
#pragma region FunctionsAwareness

//data import
void dataImport();

//funtion to manage the lobby/start screen/The first Thng the player sees/greeting
void THE_ALL_MIGHTY_LOBBY();

//rewrite data if needed
void ContinueGameOrStartNew();

//set the spikes
void setTheSpikes();

//print Labrynth
void printHeathMessageAndLabrynth();

//ask user what to do and check it is a valid input
void askWhatToDoAndCheckIt();

//verify the user can move to the desired position
void MovementCheck();

//manage if Points Have Been Picked Up
void HavePointsBeenPickedUp();

//see if doors can be opened
void CanDoorsBeOpenedAndTheCrackenReleased();

//movement for the cracken
void DynEnemyMovement();

//Check if user can switch level or win
void levelChanging_lose_winConditions();

//ask user if wants to save progress or delete it once it decides to quit
void saveOrErase();

//save data
void saveData();

//print the health bar, no animation
void PrintTheHealthBars();

//IT'S TIME FOR THE D,D,D,D,D,D,D,D,D,D,DUEL
void THECOMBAT();

#pragma endregion


/*THE MAIN SHOW*/
int main()
{

	dataImport();

	THE_ALL_MIGHTY_LOBBY();

	ContinueGameOrStartNew();

	setTheSpikes();

	//clear the screen and print instructions
	system("cls");

	cout << "Necesitas los puntos para abrir las puertas de los niveles.";
	cout << endl << "Buena suerte... Presiona ENTER para continuar...";

	//wait for the enter
	cin.ignore();


	while (Continuethegame)
	{
		printHeathMessageAndLabrynth();

		askWhatToDoAndCheckIt();

		MovementCheck();

		HavePointsBeenPickedUp();

		CanDoorsBeOpenedAndTheCrackenReleased();

		levelChanging_lose_winConditions();

		saveOrErase();

		saveData();

		/*If the boss is released  & the final battle HAS NOT ocurred*/
		if (IsTHE_BOSS_Released && !HasFinalBattleOccured)
		{
			DynEnemyMovement();
		}

		if (isFightEngaged)
		{
			THECOMBAT();
		}

	}

}


#pragma region FunctionsCode

//data import
void dataImport()
{
	//search and open the location file
	ifstream myfileread("coordinates.txt");

	//if it exists
	if (myfileread.is_open())
	{
		//import position
		myfileread >> UserCurrentLevel;

		myfileread >> userLinePosition;

		myfileread >> userColumnPosition;


	}
	//if the file does not exist
	else
	{

		//set location to the start
		UserCurrentLevel = 0;

		userLinePosition = 1;

		userColumnPosition = 1;

	}

	//close the location file
	myfileread.close();

	//set location of user
	Laberinto[UserCurrentLevel][userLinePosition][userColumnPosition] = '*';

	//search and open points file
	ifstream myfile("points.txt");


	//if it exists
	if (myfile.is_open())
	{
		//import score
		myfile >> score;

		//import Health
		myfile >> userHealth;

		//if score is zero and user is in the inital position
		if (score == 0 && Laberinto[0][1][1] == '*')
		{
			//disable continue option
			isContinueAviable = false;
		}
		//if user is not in the initial position AND hasn´t got any points 
		else
		{
			//enable continue option
			isContinueAviable = true;
		}

		//import "if points have been picked up"
		for (int i = 0; i < 10; i++)
		{
			myfile >> point[i].HasItBeenPickedUp;
		}
	}
	//if the file does not exist
	else
	{
		//set score to 0
		score = 0;

		isContinueAviable = false;
		
		//set all the 10 points to be pickbale, because They Have Not Been Picked Up
		for (int i = 0; i < 10; i++)
		{
			point[i].HasItBeenPickedUp = false;
		}

	}

	//closinng the point file
	myfile.close();

	//get the aviable points into the labrynth layout, depending on their Have they Been Picked Up status
	for (int i = 0; i < 10; i++)
	{
		//if point Has NOT Been Picked Up
		if (point[i].HasItBeenPickedUp == false)
		{
			//put it in the layout
			Laberinto[point[i].levelPosition][point[i].linePosition][point[i].columPosition] = '+';
		}
		//if point HAS Been Picked Up
		else
		{
			//do NOT put it in the layout, and leave a space
			Laberinto[point[i].levelPosition][point[i].linePosition][point[i].columPosition] = ' ';
		}
		
	}

	
}

//funtion to manage the lobby/start screen/The first Thng the player sees/greeting
void THE_ALL_MIGHTY_LOBBY()
{
	do /*while the user des not make a valid input*/
	{
		//Title
		cout <<endl << "		EL		L A B E R I N T O" << endl << endl;

		//give intructions to the player
		cout << "Presiona \"N\" para Nuevo Juego";

		//print Continue (the second option)
		if (isContinueAviable == true)
			cout << " o \"C\" para continuar";

		cout << ": ";

		//save input
		userDecision = _getch();

		//if user chose Continue, but it's not aviable
		if ((userDecision == 'C'|| userDecision == 'c') && isContinueAviable == false)
		{
			//clear the screen
			system("cls");

			//change the Decision Var to make the loop continue
			userDecision = 'z';
		}

	} while (userDecision != 'N' && userDecision != 'n' && userDecision != 'C' && userDecision != 'c');
}

//rewrite data if needed
void ContinueGameOrStartNew()
{
	/*Do this depending on user's choice*/
	switch (userDecision)
	{
	/*If user chose new game*/
	case 'n':
	case 'N':
		/*Set current imported location to a space to avoid problems*/
		Laberinto[UserCurrentLevel][userLinePosition][userColumnPosition] = ' ';

		/*Reset ALL data*/
		UserCurrentLevel = 0;
		userLinePosition = 1;
		userColumnPosition = 1;
		score = 0;
		for (int i = 0; i < 10; i++)
		{
			point[i].HasItBeenPickedUp = false;
			Laberinto[point[i].levelPosition][point[i].linePosition][point[i].columPosition] = '+';
		}
		userHealth = 5;

		/*Set new user location*/
		Laberinto[UserCurrentLevel][userLinePosition][userColumnPosition] = '*';
		break;

	/*If user chose to continue*/
	case 'C':
	case 'c':
		
		
		break;
	default:
		break;
	}

	//see if score is big enough to open doors
	CanDoorsBeOpenedAndTheCrackenReleased();
}

//set the spikes
void setTheSpikes()
{
	for (int i = 0; i < 7; i++)
	{	
		/*if user IS on the location of a spike, set the position and say that it is indeed over a spike*/
		if (spikes[i].levelPosition == UserCurrentLevel && spikes[i].linePosition == userLinePosition && spikes[i].columPosition == userColumnPosition)
		{
			Laberinto[spikes[i].levelPosition][spikes[i].linePosition][spikes[i].columPosition] = '*';
			isUserOnASpike = true;
		}
		/*set a normal spike if nothing changed*/
		else
		{
			Laberinto[spikes[i].levelPosition][spikes[i].linePosition][spikes[i].columPosition] = '^';
		}

		
	}
}

//print Labrynth
void printHeathMessageAndLabrynth() 
{
	//aesthetic screen cleaning
	system("cls");

	//noded for to print labrinth
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{

			//if carachter is a trump, color it blue
			if (Laberinto[UserCurrentLevel][i][j] == '#')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE);
				cout << Laberinto[UserCurrentLevel][i][j];
			}

			//if character is a point, paint it yellow
			else if (Laberinto[UserCurrentLevel][i][j] == '+')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_RED);
				cout << Laberinto[UserCurrentLevel][i][j];
			}

			//If character is the user, and it's not over a spike, paint it green
			else if (Laberinto[UserCurrentLevel][i][j] == '*' && isUserOnASpike == false)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_GREEN);
				cout << Laberinto[UserCurrentLevel][i][j];
			}

			//If character is the user, and it's over a spike, paint it red
			else if (Laberinto[UserCurrentLevel][i][j] == '*' && isUserOnASpike == true)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_INTENSITY);
				cout << Laberinto[UserCurrentLevel][i][j];
			}

			//If character is a spike, paint it as a bright cyan
			else if (Laberinto[UserCurrentLevel][i][j] == '^')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
				cout << Laberinto[UserCurrentLevel][i][j];
			}

			//if character is the boss paint it bright red
			else if (Laberinto[UserCurrentLevel][i][j] == '$')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_INTENSITY);
				cout << Laberinto[UserCurrentLevel][i][j];
			}

			//if character is a blank space, paint it cyan
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_GREEN /*| BACKGROUND_INTENSITY*/);
				cout << Laberinto[UserCurrentLevel][i][j];
			}
			//aesthetic corrections
			cout << (" ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

		}

		//jump to the next line
		cout << endl;
	}

	//set an aux var to not alter real health
	int auxHealth = userHealth;

	//print health in a bar form
	cout << endl  << "Salud: ";

	for (int i = 0; i < 5; i++)
	{
		if (auxHealth > 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
			auxHealth--;
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
		}

		cout << "  ";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

	}

	//print extra health points if aviable
	while (auxHealth > 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_RED);
		cout << "  ";
		auxHealth--;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

	cout << endl << endl;

	//print any message that might ocurr

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED |BACKGROUND_INTENSITY);

	cout << message;
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

	cout << endl << endl;

	//clear message string to avoid repetition
	message = "";
}

//ask user what to do and check it is a valid input
void askWhatToDoAndCheckIt()
{
	do /*Do this while the user doesn't make a valid input*/
	{
		cout << endl << endl << "Presiona WASD para moverte, o Q para salir: ";
		userDecision = _getch();
	} while 
		(/*Conditions where the user makes an invalid input*/
		userDecision != 'w' && userDecision != 'W' && /*userDecision != KEY_UP    &&*/
		userDecision != 'a' && userDecision != 'A' && /*userDecision != KEY_LEFT  &&*//*This is supposed to be for the arrows...*/
		userDecision != 's' && userDecision != 'S' && /*userDecision != KEY_DOWN  &&*/
		userDecision != 'd' && userDecision != 'D' && /*userDecision != KEY_RIGHT &&*/
		userDecision != 'q' && userDecision != 'Q' 
		);
	
}

//verify the user can move to the desired position
void MovementCheck()
{
	//make current position a space, for aesthetic purposes
	Laberinto[UserCurrentLevel][userLinePosition][userColumnPosition] = ' ';
	
	//set vars to modify position
	int lineModifier = 0;
	int columnModifier = 0;

	//alter modifier values 
	switch (userDecision)
	{
	case 'W':
	case 'w':
		lineModifier = -1;
		break;
	case 'A':
	case 'a':
		columnModifier = -1;
		break;
	case 's':
	case 'S':
		lineModifier = 1;
		break;
	case 'd':
	case 'D':
		columnModifier = 1;
		break;
		
		//
	case 'q':
	case 'Q':
		Continuethegame = false;
		break;
	default:
		cout << "Bug in hit detection, segment of modyfying." << endl;
		break;
	}

	/*LOGIC BEHIND THIS
	
	
						lineModifier = -1

	columnModifier = 1	CURRENT_POSITION    columnModifier = 1
						
						lineModifier = 1
	
	
	
	*/

	/*If user wants to move to a negative position*/
	if (userLinePosition + lineModifier < 0 || userColumnPosition + columnModifier < 0)
	{
		/*queue message that that's not possible*/
		message = "No, no puedes salirte del laberinto...";
		
		//set modifiers back to 0
		lineModifier = 0;
		columnModifier = 0;
	}
	else
	{
		//detection process with modifyers. Output depends on the position the user wants to move
		switch (Laberinto[UserCurrentLevel][userLinePosition + lineModifier][userColumnPosition + columnModifier])
		{
			//in case the position where user wants to move is a space
		case ' ':
			//reset spike status (and the spike)if needed
			if (isUserOnASpike)
			{
				isUserOnASpike = false;
				Laberinto[UserCurrentLevel][userLinePosition][userColumnPosition] = '^';

			}

			break;
			

			//in case the position where user wants to move is a wall
		case '#':
			//say te movement is not possible
			message = "Oye, no puedes atravesar un muro...";

			//set modifiers back to 0
			lineModifier = 0;
			columnModifier = 0;
			break;

			//in case the user dared to touch the final boss
		case '$':
			//avoid starting battle if it already ocurred
			if (HasFinalBattleOccured)
			{

			}
			else
			{
				//set modifiers back to 0
				lineModifier = 0;
				columnModifier = 0;
				isFightEngaged = true;
			}

			

			break;


			//in case the position where user wants to move is a point
		case '+':
			//reset spike status (and the spike)if needed
			if (isUserOnASpike)
			{
				isUserOnASpike = false;
				Laberinto[UserCurrentLevel][userLinePosition][userColumnPosition] = '^';

			}

			//increase score
			score++;

			//print the current score
		
			message = "Un punto mas! :D";

			//passive health regen management
			counterToRegenHealth--;

			//if it can be regened
			if (counterToRegenHealth == 0)
			{
				userHealth++;

				counterToRegenHealth = 3;

				message = "Un punto mas, y regeneraste vida! :DD";
			}

			break;

			//in case user walked over a spike
		case '^':

			//reset previous spike status (and the previous spike)if needed
			if (isUserOnASpike)
			{
				isUserOnASpike = false;
				Laberinto[UserCurrentLevel][userLinePosition][userColumnPosition] = '^';

			}

			//wake user aware of the situation
			message = "Ouch, pasaste por encima de unas puas :c";

			//reduce Health
			userHealth--;
			isUserOnASpike = true;

			break;

			//adding this for patching purposes
		default:
			cout << "Bug in hit detection, segment of wallcheck." << endl;
			break;
		}
	}

	//add values of position and its modifyers together (to make the new position)
	userLinePosition += lineModifier;

	userColumnPosition += columnModifier;


	//make current position a space, for aesthetic purposes
	Laberinto[UserCurrentLevel][userLinePosition][userColumnPosition] = '*';
}

//manage if Points Have Been Picked Up
void HavePointsBeenPickedUp() 
{
	for (int i = 0; i < 10; i++)
	{
		//if user is in the position of the point
		if (Laberinto[point[i].levelPosition][point[i].linePosition][point[i].columPosition] == '*')
		{
			//set it as It Has Been PickedUp
			point[i].HasItBeenPickedUp = true;
		}
	}
}

//see if doors can be opened
void CanDoorsBeOpenedAndTheCrackenReleased()
{
	for (int i = 0; i < 3; i++)
	{
		/*If the score is still too small to open the door*/
		if (score < Door[i].ScoreToBeOpened)
		{
			/*keep it as a wall*/
			Laberinto[Door[i].levelPosition][Door[i].linePosition][Door[i].columPosition] = '#';
		}
		else/*the score is big enough to open the door*/
		{
			/**/
			Laberinto[Door[i].levelPosition][Door[i].linePosition][Door[i].columPosition] = ' ';
		}

		//if all points have been picked up
		if (Door[i].ID == 2 && score == 10 && !HasFinalBattleOccured)
		{
			//RELEASE THE BOSS
			Laberinto[THE_BOSS.levelPosition][THE_BOSS.linePosition][THE_BOSS.columPosition] = '$';

			IsTHE_BOSS_Released = true;
		}
	}
}

//LET THE BOSS MOVE
void DynEnemyMovement()
{
	//aux char for movement
	char EnemyMovement;

	//boss's own movement modifyers
	int enemyLineMod = 0, enemyColumnMod = 0;

	//set Boss's current position to a space to avoid problems
	Laberinto[THE_BOSS.levelPosition][THE_BOSS.linePosition][THE_BOSS.columPosition] = ' ';

	//generate a random number for the movement
	int intMovement = rand() % 4 + 1;

	//set "The key" the boss "pressed" to move depending on the random number
	if (intMovement == 1)
		EnemyMovement = 'w';
	else if (intMovement == 2)
		EnemyMovement = 'a';
	else if (intMovement == 3)
		EnemyMovement = 's';
	else
		EnemyMovement = 'd';

	//alter modifier values 
	switch (EnemyMovement)
	{
	case 'w':
		enemyLineMod = -1;
		break;
	case 'a':
		enemyColumnMod = -1;
		break;
	case 's':
		enemyLineMod = 1;
		break;
	case 'd':
		enemyColumnMod = 1;
		break;
	default:
		cout << "Bug in dyamic enemy movement" << endl;
		break;
	}

	/*Same logic as in User Movent's Fuction MovementCheck();*/

	/*If THE BOSS wants to move to a negative position*/
	if (THE_BOSS.linePosition + enemyLineMod < 0 || THE_BOSS.linePosition + enemyColumnMod < 0)
	{
		//set modifiers back to 0
		enemyLineMod = 0;
		enemyColumnMod = 0;
	}
	else
	{
		//detection process with modifyers. Output depends on the position the user wants to move
		switch (Laberinto[THE_BOSS.levelPosition][THE_BOSS.linePosition + enemyLineMod][THE_BOSS.columPosition + enemyColumnMod])
		{
			//in case the position where THE CRACKEN wants to move is a space
		case ' ':
			break;


			//in case the position where THE CRACKEN wants to move is a wall
		case '#':

			//set modifiers back to 0
			enemyLineMod = 0;
			enemyColumnMod = 0;
			break;

			//IF IT CHALLENGES THE USER
		case '*':
			//do nothing if the battle has ocurred (ergo, the boss is already dead)
			if (HasFinalBattleOccured)
			{

			}
			else
			{
				//set modifiers back to 0
				enemyLineMod = 0;
				enemyColumnMod = 0;

				isFightEngaged = true;
			}
			

			break;


			//in case the position where THE BOSS wants to move is a point
		case '+':
			
			//reset anything related to spikes
			if (THE_BOSS.amIOverASpike)
			{
				THE_BOSS.amIOverASpike = false;
				Laberinto[THE_BOSS.levelPosition][THE_BOSS.linePosition][THE_BOSS.columPosition] = '^';

			}


			break;

		case '^':
			//reset anything related to spikes
			if (THE_BOSS.amIOverASpike)
			{
				THE_BOSS.amIOverASpike = false;
				Laberinto[THE_BOSS.levelPosition][THE_BOSS.linePosition][THE_BOSS.columPosition] = '^';

			}

			//say the boss is over a spike
			THE_BOSS.amIOverASpike = true;

			break;

			//adding this for patching purposes
		default:
			cout << "Bug in hit detection, segment of wallcheck." << endl;
			break;
		}
	}

	//add values of position and its modifyers together
	THE_BOSS.linePosition += enemyLineMod;

	THE_BOSS.columPosition += enemyColumnMod;


	if (HasFinalBattleOccured)
	{
		Laberinto[THE_BOSS.levelPosition][THE_BOSS.linePosition][THE_BOSS.columPosition] = ' ';
	}
	else
	{
		Laberinto[THE_BOSS.levelPosition][THE_BOSS.linePosition][THE_BOSS.columPosition] = '$';
	}
	

}

//Check if user can switch level or win
void levelChanging_lose_winConditions()
{
	//debug
	Laberinto[UserCurrentLevel][userLinePosition][userColumnPosition] = '*';

	//if user crossed the first door
	if (Laberinto[0][18][19] == '*')
	{
		message = "Has pasado al nivel 2!";

		Laberinto[UserCurrentLevel][userLinePosition][userColumnPosition] = ' ';

		UserCurrentLevel = 1;

		userColumnPosition = 0;


	}

	//if user crossed the second door
	if (Laberinto[1][1][19] == '*')
	{
		message = "Has pasado al nivel 3!" ;

		Laberinto[UserCurrentLevel][userLinePosition][userColumnPosition] = ' ';

		UserCurrentLevel = 2;

		userColumnPosition = 0;
	}

	//if user crossed the third door
	if (Laberinto[2][19][16] == '*')
	{
		system("cls");

		cout << "Has ganado!!!!!!!!!!!!!" << endl;


		Continuethegame = false;



		//RESET IT ALL
		UserCurrentLevel = 0;

		userLinePosition = 1;

		userColumnPosition = 1;

		score = 0;

		userHealth = 5;

		for (int i = 0; i < 10; i++)
		{
			point[i].reset();
		}

	}


	//if user died...
	if (userHealth == 0)
	{
		system("cls");

		cout << "Ups, te moriste..." << endl << endl;

		Continuethegame = false;

		UserCurrentLevel = 0;

		userLinePosition = 1;

		userColumnPosition = 1;

		score = 0;

		for (int i = 0; i < 10; i++)
		{
			point[i].reset();
		}
	}

	//#############################

	//setting user position again for debugging purposes
	Laberinto[UserCurrentLevel][userLinePosition][userColumnPosition] = '*';
}

//ask user if wants to save progress or delete it once it decides to quit
void saveOrErase()
{
	//if user decided to quit
	if (userDecision == 'q' || userDecision == 'Q' /*&& Continuethegame == false*/)
	{

		do
		{
			//clear screen
			system("cls");

			//be sure user didn't do a typo
			cout << "Quieres salir ((s)i, (n)o)?: ";

			//wait for an input
			userDecision = _getch();

		} while (userDecision != 's' && userDecision != 'S' && userDecision != 'n' && userDecision != 'N');/*do this until a valid input is get*/

		//if its sure user wants to go out
		if (userDecision == 's' || userDecision == 'S')
		{
			do
			{
				//clear screen once again
				system("cls");

				//ask if to save progres or not
				cout << endl << "Quieres guardar tu progreso ((s)i , (n)o)?: ";

				//wait input
				userDecision = _getch();

			} while (userDecision != 's' && userDecision != 'S' && userDecision != 'n' && userDecision != 'N');/*Do this until a valid input*/

			//if user decided to save progress
			if (userDecision == 's' || userDecision == 'S')
			{
				//set the game to end
				Continuethegame = false;
			}
			
			//if user decided to NOT save the progress
			else
			{
				//reset all data
				UserCurrentLevel = 0;

				userLinePosition = 1;

				userColumnPosition = 1;

				score = 0;

				for (int i = 0; i < 10; i++)
				{
					point[i].HasItBeenPickedUp = false;
				}

			}
		}
		//if user changed mind about quitting (The game), for whatever reason
		else
		{
			//set the game to continue
			Continuethegame = true;
		}
	}
}

//save data
void saveData()
{
	//auxiliar bool to hel saving data
	bool auxHasItBeenPickedUp;
	
	//open position file
	ofstream myfile("coordinates.txt");

	//write an save position
	myfile << UserCurrentLevel << endl;

	myfile << userLinePosition << endl;

	myfile << userColumnPosition << endl;

	//close position file
	myfile.close();

	//open points file
	ofstream myPfile("points.txt");

	//save score
	myPfile << score << endl;

	//isave Health
	myPfile << userHealth << endl;

	
	for (int i = 0; i < 10; i++)
	{
		//give the aux var the value of the HasItBeenPickedUp state of the current point
		auxHasItBeenPickedUp = point[i].HasItBeenPickedUp;

		//save the value into the file
		myPfile << auxHasItBeenPickedUp << endl;
	}
	
	//close position file
	myPfile.close();

}

//print the health bar, no animation
void PrintTheHealthBars()
{

	//aesthetic fix
	system("cls");
	
	//aux Health var to not alter original one
	auxBossHealth = THE_BOSS.health;



	//print boss health bar
	cout << "salud del Jefe: ";

	for (int i = 0; i < 20/*because is the max health the boss has*/; i++)
	{

		//if the auxHealth is not zero
		if (auxBossHealth > 0)
		{
			//print two spaces in green
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			cout << "  ";

			//aesthetic fix, return to black coloring
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

			//substract 1 from the aux var
			auxBossHealth--;
		}

		/*if the aux var has reached zero, meaning, all the Health points the boss has have already been painted in green*/
		else
		{
			//paint two spaces in red
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_INTENSITY);
			cout << "  ";

			//aesthetic fix, return to black coloring
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		}
	}

	

	//give decent space 
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;

	//set another aux health, now with the user's health
	auxUserHealtrh = userHealth;


	//print user's health bar
	cout << "Tu salud: ";

	for (int i = 0; i < 5; i++)
	{
		//if the auxHealth is not zero
		if (auxUserHealtrh > 0)
		{
			//print two spaces in green
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			cout << "  ";
			auxUserHealtrh--;
			//aesthetic fix, return to black coloring
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		}

		/*if the aux var has reached zero, meaning, all the Health points the user has have already been painted in green*/
		else
		{
			//paint two spaces in red
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_INTENSITY);
			cout << "  ";
			//aesthetic fix, return to black coloring
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		}
	}

	//setthe yellow for the extra health points
	while (auxUserHealtrh > 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		cout << "  ";
		auxUserHealtrh--;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
}

//IT'S TIME FOR THE D,D,D,D,D,D,D,D,D,D,DUEL
void THECOMBAT()
{
	//Random Sh*t i need to copy in order to make this function work
	using namespace std::this_thread;
	using namespace std::chrono_literals;
	using std::chrono::system_clock;

	//list ob objects that can be thrown with their damage
	enum ObjectsToThrow
	{
		knife = 4,
		grenade = 8,
		SaintSword = 20
	};
	
	//var with the object the user currently has
	ObjectsToThrow CurrentUserObject = knife;
	
	//Var with the object the boss is going to launch
	ObjectsToThrow BossIsGoingToLaunchThis = SaintSword;
	/*aux int of this var*/int intBossIsGoingToLaunchThis;


	//string to print combat message
	string CombatMessage;

	//ints for punches, nerfs and buffs
	int UserHardPunch = 2, UserVeryHardPunch = 5, UserExtraHardPunch = 7, UserDefaultBuff = 0;
	int userHealthModifier = 0, bossHealthModifier = 0;

	//Stamina the user has (to recover)
	int userStamina = 0;

	//diverse vars to manage Boss's actions
	int intBossAction;
	char BossAction;

	//bool to check if user can continue avoiding
	bool canUserContinueAvoiding = false;

	//bool to help seek out if plafer chose to defend itself
	bool isUserDefendingItself = false;

	//bool if user made a critical hit
	bool didUserMakeACritHit = false;

	//bool to end the game loop
	bool hasSomeoneWon = false;

	//bool to check if user has an item
	bool DoesUserHaveAnItem = false;

	//time counter
	int counter = 0;

	//int to count how many times something has been pressed
	int TimesAWasPressed = 0;

#pragma region InitialHealthBarPrinting
	//clear screen for aesthethic purposes
	system("cls");

	//SET THE HYPE WITH MUSIC
	PlaySound(TEXT("Gamegame.wav"), NULL, SND_ASYNC);

	//Tell the player a battle is about to begin (All time holdins are for aesthetic purposes
	cout << "El jefe te desafia ";

	sleep_for(1400ms);

	for (int i = 0; i < 3; i++)
	{
		cout << ".";
		sleep_for(75ms);
	}

	sleep_for(280ms);
	cout << " A PELEAR!";

	sleep_for(400ms);

	//clear screen again
	system("cls");

	//set an auxiliar health var with boss's health, in order to help paint the health bar and not alter the original health var
	int auxBossHealth = THE_BOSS.health;

	//print boss health bar
	cout << "salud del Jefe: ";

	for (int i = 0; i < 20/*because is the max health the boss has*/; i++)
	{

		//if the auxHealth is not zero
		if (auxBossHealth > 0)
		{
			//print two spaces in green
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			cout << "  ";

			//substract 1 from the aux var
			auxBossHealth--;
		}
		
		/*if the aux var has reached zero, meaning, all the Health points the boss has have already been painted in green*/
		else
		{
			//paint two spaces in red
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_INTENSITY);
			cout << "  ";
		}
		sleep_for(50ms);
	}

	//aesthetic fix, return to black coloring
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

	//give decent space 
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;

	//set another aux health, now with the user's health
	int auxUserHealtrh = userHealth;


	//print user's health bar
	cout << "Tu salud: ";

	for (int i = 0; i < 5; i++)
	{
		//if the auxHealth is not zero
		if (auxUserHealtrh > 0)
		{
			//print two spaces in green
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
			cout << "  ";
			auxUserHealtrh--;
		}

		/*if the aux var has reached zero, meaning, all the Health points the user has have already been painted in green*/
		else
		{
			//paint two spaces in red
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_INTENSITY);
			cout << "  ";
		}
		sleep_for(50ms);

		//aesthetic fix, return to black coloring
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	}

	

#pragma endregion

	while (!hasSomeoneWon)
	{
		//reprinting health bars for aesthetic purposes
		PrintTheHealthBars();
		
		//if user has enough Stamina
		if (userStamina >= 0)
		{
			do
			{
				//ask user what to do
				cout << endl << "Quieres (G)olpear, (D)efenderte o (L)anzar algo?: ";

				//save input
				userDecision = _getch();

				/*repeat if and until User makes  valid input*/
			} while (userDecision != 'G' && userDecision != 'g' && userDecision != 'D' && userDecision != 'd' && userDecision != 'L' && userDecision != 'l');

			/*Actions depending on what the user wants to do*/
			switch (userDecision)
			{

				/*hit*/
			case 'g':
			case 'G':

				do
				{
					//ask user how hard to punch
					cout << endl << "Quieres golpear (D)uro, (M)uy duro o (E)xtra duro?: ";

					//save input
					userDecision = _getch();


					/*repeat if and until User makes  valid input*/
				} while (userDecision != 'M' && userDecision != 'm' && userDecision != 'D' && userDecision != 'd' && userDecision != 'E' && userDecision != 'e');


				//Set the modifier with the conditions of the type of hit the user chose
				if (userDecision == 'D' || userDecision == 'd')
				{
					bossHealthModifier += UserHardPunch;

					CombatMessage = "Has golpeado duro al jefe!";
				}

				else if (userDecision == 'M' || userDecision == 'm')
				{
					bossHealthModifier += UserVeryHardPunch;

					CombatMessage = "Has golpeado muy duro al jefe, y te cansaste!";

					userStamina -= 2;
				}

				else if (userDecision == 'E' || userDecision == 'e')

				{
					bossHealthModifier += UserExtraHardPunch;

					CombatMessage = "Has golpeado extra duro al jefe, y te cansaste mucho!";

					userStamina -= 3;
				}

				break;

				/*defend*/
			case 'd':
			case 'D':
				UserDefaultBuff = 5;

				isUserDefendingItself = true;

				CombatMessage = "Has decidido defenderte!";

			break;

				/*Launch a thing*/
			case 'l':
			case 'L':
				//if user has something to thow
				if (DoesUserHaveAnItem)
				{
					//set damage to the boss and print it
					bossHealthModifier += (int)CurrentUserObject;
					switch (CurrentUserObject)
					{
					case knife:
						CombatMessage = "Le lasnzaste un cuchillo al jefe!";
						break;
					case grenade:
						CombatMessage = "Le lasnzaste una granada al jefe!";
						break;
					case SaintSword:
						CombatMessage = "Le lasnzaste la espada santa al jefe!";
						break;
					default:
						break;
					}
					//tell, user does not longer have an item
					DoesUserHaveAnItem = false;
				}
				else
				{
					//tell user there`s nothing to throw
					CombatMessage = "Buscal algo para lanzar... Pero no lo encuentras!";

				}



			break;

			default:
				break;
			}
		}
		
		/*If user deos NOT have enough stamina*/
		else
		{
			CombatMessage = "Quisieras hacer algo... pero estás muy cansado para ello!";
		}

		//print the health bars (yet again), now with a nice effect that shows life reduction
		
		PrintTheHealthBars();

		cout << endl << CombatMessage << endl;
		THE_BOSS.health -= bossHealthModifier;
		bossHealthModifier = 0;

		sleep_for(1500ms);

		system("cls");
		
		
		PrintTheHealthBars();

		//empty the message slot
		CombatMessage = "";

		//let user read what's happening
		sleep_for(1s);

		//if the boss is dead
		if (THE_BOSS.health <= 0)
			BossAction = 'G';
		else
		{
			//generate a random number for boss's first action
			intBossAction = rand() % 2;
			if (intBossAction == 0)
				BossAction = 'L';
			else
				BossAction = 'G';
		}
		
			

		//if boss chose to attack
		if (BossAction == 'G')
		{
			system("cls");

			if(THE_BOSS.health <= 0)
				cout << "EL CUERPO DEL JEFE TE VA A CAER ENCIMA!!!";
			else
				cout << "SE VIENE EN ATAQUE!!!";

			//give user time ro read
			sleep_for(1500ms);

			system("cls");

			if (isUserDefendingItself)
			{
				cout << "por protegerte estás a salvo! :D";
			}
			else
			{
				cout << "PRESIONA \"A\"!!!";
				

				//measure time to know if user responded in time or not
				chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
				userDecision = _getch();
				chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

				//make a float with the results
				float elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();

				system("cls");

				//if user hit  the wrong button
				if (userDecision != 'A' && userDecision != 'a')
				{
					cout << "Presionaste la que no era D:";
					userHealthModifier -= 1;
				}
				//if user took too many time to press
				else if (elapsedTime >= 1000)
				{
					cout << "Tardaste mucho... :(";
					userHealthModifier -= 1;

				}
				//give user time  time to read
				sleep_for(1500ms);

				//reprint health bars 
				PrintTheHealthBars();

				cout << endl << CombatMessage << endl;
				userHealth -= userHealthModifier;
				sleep_for(750ms);

				userHealthModifier = 0;

				PrintTheHealthBars();
			}

		}

		//if Boss decided to launch
		else
		{
			//get a random number
			intBossIsGoingToLaunchThis = rand() % 1000;

			//debug reset
			userHealthModifier = 0;

			system("cls");
			
			//use random number to know what object to throw
			if (intBossIsGoingToLaunchThis == 999)
				BossIsGoingToLaunchThis = SaintSword;
			else if (intBossIsGoingToLaunchThis < 999 && intBossIsGoingToLaunchThis > 400)
				BossIsGoingToLaunchThis = knife;
			else
				BossIsGoingToLaunchThis = grenade;

			cout << "EL GEFE TE VA A LANZAR ";

			if (BossIsGoingToLaunchThis == SaintSword)
			{
				cout << "UNA ESPADA SANTA!!!";
			}
			else if (BossIsGoingToLaunchThis == knife)
			{
				cout << "UN CUCHILLO!!!";
			}
			else
			{
				cout << "UNA GRANADA!!!";
			}

			//give user time to read
			sleep_for(1500ms);

			system("cls");

			if (isUserDefendingItself)
			{
				cout << "por Estarte protegiendo ya no pudiste obtener el objeto! D:";

				cout << endl << "por lo menos sigues viv@...";
			}
			else
			{
				cout << "Presiona \"A\" PARA OBTENER EL OBJETO!!! ";

				//measure time to know if user responded in time or not
				std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
				userDecision = _getch();
				std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

				//float with the results
				float elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count();

				if (elapsedTime >= 1000)
				{
					cout << endl << "Ups, te tardaste mucho... :C";
					userHealthModifier += 1;

				}
				else if (userDecision != 'A' && userDecision != 'a')
				{
					cout << "Presionaste la que no era D:";
					userHealthModifier += 1;
				}
				else
				{
					cout << endl << "Lo lograste!! Ahora tienes ";
					if (BossIsGoingToLaunchThis == SaintSword)
					{
						cout << "una espada santa";
					}
					else if (BossIsGoingToLaunchThis == knife)
					{
						cout << "un cuchillo";
					}
					else
					{
						cout << "una granada";
					}

					cout << " en tu inventario :D";
					if (DoesUserHaveAnItem)
					{
						cout << ". Pero como no puedes cargar mucho, sueltas el otro objeto que tenias...";
					}

					CurrentUserObject = BossIsGoingToLaunchThis;

					DoesUserHaveAnItem = true;

				}
			}
			//give user time to read
			sleep_for(1500ms);

			//reprint health bars
			PrintTheHealthBars();

			cout << endl << CombatMessage << endl;
			userHealth -= userHealthModifier;
			sleep_for(750ms);

			userHealthModifier = 0;

			PrintTheHealthBars();
		}

		//regen user Stamina passively
		userStamina++;

		//reset defense bool
		isUserDefendingItself = false;

		//if user died
		if (userHealth <= 0)
		{
			hasSomeoneWon = true;

			cout << endl << "No lograste salir viv@... :(";

			Continuethegame = false;
		}
		
		//if the boss died
		if (THE_BOSS.health <= 0)
		{
			hasSomeoneWon = true;

			cout << endl << "LO LOGRASTE!!!!";

			Laberinto[THE_BOSS.levelPosition][THE_BOSS.linePosition][THE_BOSS.columPosition] = ' ';
			IsTHE_BOSS_Released = false;

			isFightEngaged = false;

			HasFinalBattleOccured = true;
		}
	}
	cout << endl;
}
