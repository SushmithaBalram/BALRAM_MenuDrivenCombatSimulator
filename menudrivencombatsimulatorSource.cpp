//adding libraries and dependencies
#include <iostream> //for "cout" and "cin"
#include <conio.h> //for getch call
#include "CIS115-P02S - Menu Driven Combat Simulator.h" //for custom functions
#include <windows.h>//to use the ClearScreen function
using namespace std; 
//hey whats up
//constants
#define HEAL 2
#define ATTACK  1
#define TRUE 1
#define FALSE 0

//funtion prototypes
void displayOutcome(int, int); //funtion that uses two arguments to display end outcome
void menu(int, int); //function that uses two arguments to display menu (enemy and player hp)
int playerAttack(int);//function that determines points of damage towards enemy's hp, that needs to return enemy hp value to main function
int playerHeal(int);//function that determines points of healing to players hp, and returns value to main function
int enemyAttack(int);//function that determines points of damage towards player's hp, and returns player hp value to main function
int validateMenuChoice(int); //funtion for menu choice validation so I don't have to write it in the main code so it looks nicer

//driving function starts here
int main() {
	//declare variables
	int Player_HP = 100;
	int Enemy_HP = 100;
	int menuChoice = 0;

	//seed the random number generator here
	SeedRNGToSystemClock();
	while (Player_HP > 0 && Enemy_HP > 0) {//Huge while loop will hold most of the code 
		//display the menu
		menu(Player_HP,Enemy_HP);//call funtion to display menu
		cin >> menuChoice; //input a menu choice 
		menuChoice = validateMenuChoice(menuChoice); //im calling the validatemenuchoice function to do input validation, so I do menuChoice= 
		//because I'm asking for the new value of menuChoice in the other function to be returned into menuChoice in the main funtion.
		if (menuChoice == ATTACK) { //assuming you have selected 1 which is attack
			Enemy_HP=playerAttack(Enemy_HP);//we call the function for the player to attack
		}
		if (menuChoice == HEAL) {//if you select 2 which is heal
			Player_HP=playerHeal(Player_HP);
		}
		//Now its the enemy's turn!
		Player_HP=enemyAttack(Player_HP);//calling the enemy to attack function, which will happen regardless of whether i attack, miss, or heal
		//Message will display that you either won or lost my checking if either player or enemy HP reached 0
		displayOutcome(Player_HP,Enemy_HP);//call function
		_getch(); //press a key
		ClearScreen();//calling the function to clear the screen.
	}
	_getch();
	return 0;
}
//This is where the other functions are listed:
int validateMenuChoice(int menuChoice) {//function for input validation of menu choice, must return to main function
	while (cin.fail() == TRUE || (menuChoice != ATTACK && menuChoice != HEAL)) {//the validation loop will continue as long as there is an invalid entry or 
		if (cin.fail() == TRUE) {												//the entry is neither attack nor heal
			cout << " ERROR! INVALID ENTRY." << endl;
			cin.clear();	//clear 
			rewind(stdin);	//standard input stream allows us to fix the problem
			menuChoice = 0;
		}
		else if (menuChoice != ATTACK && menuChoice != HEAL) {
			cout << " ERROR! MENU OPTION SHOULD BE EITHER 1 OR 2." << endl;
		}
		//attempt to get the menu choice again
		cout << " : ";
		cin >> menuChoice;
	}
	return menuChoice; //I have to make it go back to the main function to continue the process
}

int playerAttack(int Enemy_HP) {//function that determines points of damage towards enemy's hp, and needs to return enemy hp value to main function
	int randomValue = 0;
	int criticalIdentifier = 0;
	int damage = 0;
	randomValue = generateRandomValue(1, 100); //we are using the random value generator to get a # from 1-100. 1-20 would fail and 21-100 would succeed.
	if (randomValue > 20) {
		damage = generateRandomValue(1, 10);//now if the random # is above 20, we need another random # between 1 and 10 to become the damage points
		criticalIdentifier = generateRandomValue(1, 100); //I need to generate another random # to determine if damage is critical.
		if (criticalIdentifier <= 20) { //if the number is 1-20 that means 20% of the time, so critical damage will happen then
			damage = damage * 2.5 + 5; //damage is recalculated 
			cout << " You ATTACK and score a CRITICAL HIT on the enemy for " << damage << " HP!!!" << endl;
		}
		else {
			cout << " You ATTACK and score a HIT on the enemy for " << damage << " HP! " << endl;
		}
		Enemy_HP = Enemy_HP - damage;//damage is applied to enemy's hp
	}
	else {
		cout << " You ATTACK and MISS :(" << endl;
	}
	return Enemy_HP;
}

int enemyAttack(int Player_HP) {//function that determines points of damage towards player's hp, and returns player hp value to main function
	int randomValue = 0;
	int criticalIdentifier = 0;
	int damage = 0;
	randomValue = generateRandomValue(1, 100);//same thing, get a # 1-100 where 1-20 would miss and 21-100 would hit
	if (randomValue > 20) {
		damage = generateRandomValue(1, 10);//another random # for damage points
		criticalIdentifier = generateRandomValue(1, 100);//determine if damage is critical
		if (criticalIdentifier <= 20) {
			damage = damage * 2.5 + 5;//damage recalculated
			cout << " Oh no enemy attacks and scores a CRITICAL HIT on you for " << damage << " HP!!!" << endl;
		}
		else {
			cout << " Enemy attacks and scores a HIT on you for " << damage << " HP! " << endl;
		}
		Player_HP = Player_HP - damage;//damage is applied to player HP
	}
	else {
		cout << " The enemy MISSED :)" << endl;
	}
	return Player_HP;
}

int playerHeal(int Player_HP) {//function that determines points of healing to players hp, and returns value to main function
	int healPoints = 0;
	healPoints = generateRandomValue(3, 25);//whatever the random number is between 3 and 25, that is now stored in the healPoints.
	Player_HP = Player_HP + healPoints; //add to player hp.
	cout << " You heal yourself " << healPoints << "." << endl;
	return Player_HP;
}

void displayOutcome(int Player_HP,int Enemy_HP) {//this function uses two arguments to display outcome; whether you won or not
	if (Player_HP <= 0) {
		cout << " You lost :( Better luck next time! " << endl<< endl;
		cout << " GAME OVER" << endl;
	}
	else if (Enemy_HP <= 0) {
		cout << " You won! :)" << endl << endl;
		cout << " GAME OVER" << endl;
	}
} //I dont need to return anything if its a void function

void menu(int Player_HP, int Enemy_HP) {//function that uses two arguments to display menu (enemy and player hp)
	cout << " Player HP: " << Player_HP << endl;
	cout << " Enemy HP: " << Enemy_HP << endl;
	cout << " Select an action: " << endl;
	cout << " 1) Attack " << endl;
	cout << " 2) Heal " << endl;
	cout << " : ";
}//I dont need to return anything if its a void function

