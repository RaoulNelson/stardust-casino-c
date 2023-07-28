#ifndef CASINO_H
#define CASINO_H

//global constants
#define SLOTS 1
#define SCRATCH 2
#define BLACKJACK 3
#define EXIT 4

//black jack constants
#define FACES 13
#define SUITS 4
#define CLUBS 0
#define DIAMONDS 1
#define HEARTS 2
#define SPADES 3
#define BUST 21

//black jack global variable
int cards;

//Scratch Off constants
#define ONE 1
#define TWO 2
#define FIVE 5
#define BONUS 20




//Structs
typedef struct OneDollar {
    int winNumber;
    int numbers[5];
    float prizes[5];
    char bonus[2];
} OneDollar;

typedef struct TwoDollar {
    int winNumbers[2];
    int numbers[10];
    float prizes[10];
    char bonus[2];
} TwoDollar;

typedef struct FiveDollar {
    int winNumbers[4];
    int numbers[12];
    float prizes[12];
    char bonus[4];
} FiveDollar;


// function prototypes
void welcomeScreen();
void clearScreen();
int displayMenu();

// game Slots
int playSlots(int);
int playScratchOffs(int);
int playBlackJack(int);
char randomSymbol();

// game Black Jack
void initializeUsed(char used[SUITS][FACES]);
void printDeck(char deck[SUITS][FACES]);
void initializeDeck(char deck[SUITS][FACES]);
int deal(char deck[SUITS][FACES], char used[SUITS][FACES]);
int results(int playScore, int dealScore);

//Function declarations/prototypes for Scratch Offs
OneDollar createScratchOffOne();
void displayScratchOffOne();
TwoDollar createScratchOffTwo();
void displayScratchOffTwo();
FiveDollar createScratchOffFive();
void displayScratchOffFive();
int cashOneDollar();
int cashTwoDollar();
int cashFiveDollar();
char getBonus();



#endif
