#pragma once



class DataForAllKinds
{

public:
	int levelPosition;
	int linePosition;
	int columPosition;
	bool amITheUser = false;
	bool amIADynamicEnemy = false;
};

class User : public DataForAllKinds
{
	int health;


	
	User(int auxLevelPosition, int auxLinePosition, int auxColumnPosition, int auxHealth)
	{
		levelPosition = auxLevelPosition;
		linePosition = auxLinePosition;
		columPosition = auxColumnPosition;
		health = auxHealth;
	}

};

class Points : public DataForAllKinds
{

public:
	bool HasItBeenPickedUp;
	int ID;

	Points(int auxID, int auxLevelPosition, int auxLinePosition, int auxColumnPosition, bool auxHasItBeenPikedUp)
	{
		ID = auxID;
		levelPosition = auxLevelPosition;
		linePosition = auxLinePosition;
		columPosition = auxColumnPosition;
		HasItBeenPickedUp = auxHasItBeenPikedUp;
	}

	void reset()
	{
		HasItBeenPickedUp = false;
	}

};

class staticEnemy : public DataForAllKinds
{

public:

	staticEnemy(int auxLevelPosition, int auxLinePosition, int auxColumnPosition)
	{
		levelPosition = auxLevelPosition;
		linePosition = auxLinePosition;
		columPosition = auxColumnPosition;
	}

};

class dinamicEnemy : public DataForAllKinds
{

public:

	int health;
	bool amIOverASpike = false;

	dinamicEnemy(int auxLevelPosition, int auxLinePosition, int auxColumnPosition, int auxHealth)
	{
		levelPosition = auxLevelPosition;
		linePosition = auxLinePosition;
		columPosition = auxColumnPosition;
		health = auxHealth;
		amIADynamicEnemy = true;
	}

	
};

class THEDOORS: public DataForAllKinds
{
public:
	int ScoreToBeOpened, ID;
	
	THEDOORS(int auxID, int auxLevelPosition, int auxLinePosition, int auxColumnPosition, int auxScoreToBeOpened)
	{
		ID = auxID;
		levelPosition = auxLevelPosition;
		linePosition = auxLinePosition;
		columPosition = auxColumnPosition;
		ScoreToBeOpened = auxScoreToBeOpened;

	}
};

