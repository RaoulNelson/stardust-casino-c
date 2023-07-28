//Stardust Casino Machine
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "casino.h"

//Main function
int main()
{
    srand(time(0));
	
    int play = 1;
    int cash = 1000;
    int chosenGame;
    welcomeScreen();

    while(play)   {
        clearScreen();
        chosenGame = displayMenu();
        clearScreen();

        switch (chosenGame)   {
        //Choose Game
            case SLOTS:
                cash = playSlots(cash);
                break;

            case SCRATCH:
                cash = playScratchOffs(cash);
                break;

            case BLACKJACK:
                cash = playBlackJack (cash);
                break;

            case EXIT:
                chosenGame = 0;
                return 0;
        }
    printf("\nPlayer's cash balance is $%d.\n", cash);
    printf("Player, play another game? (1 = Yes, 0 = No)\n");
    scanf("%d", &play);
    }

    return 0;
}

//Welcome screen function
void welcomeScreen ()   {
    printf("\t#######*############################################*#####\n");
    printf("\t##########################################################\n");
    printf("\t############                                  ############\n");
    printf("\t####*#######         Stardust Casino          #######*####\n");
    printf("\t############                                  ############\n");
    printf("\t##########################################################\n");
    printf("\t#########*###################################*############\n");

}

//Clear screen function
void clearScreen()   {
    printf("\t\t\t <Hit Enter to continue>\n");
    char input;
    scanf("%c", &input);
    system("cls");
    //system("clear");
}

//Display Menu function
int displayMenu()   {
    int selection;
    do {
        printf("Select a game to play by entering the number next to the game\n");
        printf("1. Slots\n");
        printf("2. Scratch Offs\n");
        printf("3. Black Jack\n");
        printf("4. Quit\n");

        scanf("%d", &selection);
    }
    while(selection < SLOTS || selection > EXIT);
    return selection;
}

//Play Slots function
int playSlots (int cash)   {
    const int BET = 5;
    const int MATCH_TWO = 5;
    const int MATCH_THREE = 50;
    int play = 1;
    char sym1, sym2, sym3;

//Rules for Slots
    printf("Lets play the slot machines!\n\n");
    printf("Your cash balance is $%d. The bet is $%d.\n", cash, BET);
    printf("Match two symbols to win $%d.\n", MATCH_TWO);
    printf("Match all three symbols to win $%d.\n\n", MATCH_THREE);

//Checks to see if you have at least $5
    if (cash < BET)   {
        printf("You do not have enough cash to play.\n\n");
        play = 0;

}
//Slots Code
    while (play == 1)   {
        cash -= BET;

        printf("Spinning...\n\n");
        sym1 = randomSymbol () ;
        sym2 = randomSymbol () ;
        sym3 = randomSymbol () ;
        printf("%c\t%c\t%c\n\n", sym1, sym2, sym3);
        if ((sym1 == sym2) && (sym2 == sym3))   {
            cash += MATCH_THREE;
            printf("Three symbols matched! Congrats!\n\n");
        }
        else if ((sym1 == sym2 ) || (sym1 == sym3) || (sym2 == sym3))  {
            cash += MATCH_TWO;
            printf("Two symbols matched! Better than nothing.\n\n");
        }
        else   {
            cash += 0;
            printf("No symbols matched. Better luck next time.\n\n");
        }
        printf("CASH = $%d\n\n", cash);

        if (cash >= 5)   {
            printf("Would you like to spin again (1 = Yes, 0 = No)?\n\n");
            scanf("%d", &play);
        }
        else   {
            printf("You do not have enough cash to spin.\n\n");
            break;
        }
    }
    printf("Thank you for playing slots at Stardust Casino!\n\nYour cash out is $%d\n", cash);
    return cash;
}

//Random Symbol Generator
char randomSymbol ()   {
    const int SYMBOLS = 6;
    //{'$','%','&','#','@','!'}
    //"$%&#@!"
    const char symbols[] = {'$','%','&','#','@','!'};

    char symbol;
    int num;

//Assigns symbols
    num = rand() % 6;
    switch (num)   {

    case 0:
        symbol = symbols[0];
        break;

    case 1:
        symbol = symbols[1];
        break;

    case 2:
        symbol = symbols[2];
        break;

    case 3:
        symbol = symbols[3];
        break;

    case 4:
        symbol = symbols[4];
        break;

    case 5:
        symbol = symbols[5];
        break;
    }
    return symbol;
}

//SCRATCH OFFS SOURCE CODE
int playScratchOffs(int cash)
{
    int play = 1;
    int type;
    int count;
    int c;
    OneDollar oneSO;
    TwoDollar twoSO;
    FiveDollar fiveSO;

//Scratch Off Rules
    printf("Let's play scratch off tickets!\n");
    printf("Players can select from One Dollar, Two Dollar, and Five Dollar tickets\n");
    printf("Prizes are based on the ticket selected\n\n");

    while(play)   {
        //Choosing type of scratch off and how many of that type
        printf("Which type of scratch off would you like\n(1 = One Dollar, 2 = Two Dollar, 5 = Five Dollar)?\n");
        scanf("%d", &type);
        printf("How many scratch offs would you like?\n");
        scanf("%d", &count);

        for(c = 0; c < count; c++)   {
            switch(type)   {

                case ONE:
                    if(cash >= ONE)  {
                        cash -= ONE;
                        oneSO = createScratchOffOne(oneSO);
                        displayScratchOffOne(oneSO);
                        //Changed this from "=" to "+=" as starting cash would get overwritten by last scratch off winnings
                        cash += cashOneDollar(oneSO);
                    }
                    else   {
                        printf("Player does not have enough cash to play.\n");
                        c = count;
                    }
                    break;

                case TWO:
                    if(cash >= TWO)   {
                        cash -= TWO;
                        twoSO = createScratchOffTwo(twoSO);
                        displayScratchOffTwo(twoSO);
                        //Changed this from "=" to "+=" as starting cash would get overwritten by last scratch off winnings
                        cash += cashTwoDollar(twoSO);
                    }
                    else   {
                        printf("Player does not have enough cash to play.\n");
                        c = count;
                    }
                    break;

                case FIVE:
                    if(cash >= FIVE)   {
                        cash -= FIVE;
                        fiveSO = createScratchOffFive(fiveSO);
                        displayScratchOffFive(fiveSO);
                        //Changed this from "=" to "+=" as starting cash would get overwritten by last scratch off winnings
                        cash += cashFiveDollar(fiveSO);
                     }
                     else   {
                        printf("Player does not have enough cash to play.\n");
                        c = count;
                    }
                    break;
            }
        }
        printf("Player's cash balance is $%d.\n", cash);
        printf("Would you like to play more scratch offs? (1 = Yes, 0 = No)\n");
        scanf("%d", &play);
    }


    return cash;
}

//Blackjack Function
int playBlackJack (int cash)   {


    const int BET = 10;
    const int MIN_HIT = 16;
    const int HIT = 1;
    const int STAND = 0;

    int play = 1;
    int choice = 0;
    int bust = 0;
    int player = 0;
    int dealer = 0;
    char deck[SUITS][FACES];
    char dealt[SUITS][FACES];

    //Rules Output
    printf("Let's play black jack!\n\n");
    printf("Your cash balance is $%d\n", cash);
    printf("The bet is $%d\n", BET);
    printf("Dealer must HIT if their score is %d or less\n", MIN_HIT);
    printf("Dealer must STAND if their score is %d or higher\n", MIN_HIT+1);
    printf("If the player wins the hand, they win $20\n");
    printf("if the dealer wins the hand, the $10 bet is lost\n");
    printf("If it is a PUSH, the player keeps their $10 bet\n\n");

    clearScreen();
    //Checks if player has enough cash to play
    if (cash < BET)   {
        printf("You do not have enough cash to play!\n\n");
       return cash;
    }

    initializeUsed(dealt);
    printf("Shuffling the cards...\n");


    //Assigns values to each element in array "deck"
    initializeDeck(deck);

    //Outputs deck onto screen
    printf("Here's the deck...\n");
    printDeck(deck);

    clearScreen();
    printf("Dealing...\n");


    while(play)   {

        printf("Player cash is $%d\n", cash);
        if(cash < BET)   {
            printf("You do not have enough cash to play.\n");
            play = 0;
            continue;
        }
        cash -= BET;
        player = 0;
        dealer = 0;
        bust = 0;


        //I cannot stop it from printing the initial player score twice (this also applies to dealer's score, so code still works)
        player += deal(deck, dealt);
        player += deal(deck, dealt);

        printf("Player's score: %d\n", player); //However if you move this line above the previous one, it starts at 0 score instead.
        dealer += deal(deck, dealt);
        dealer += deal(deck, dealt);

        printf("Player, another card? (0 = STAND, 1 = HIT)\n");
        scanf(" %d", &choice);

        while((choice == HIT) && (player < BUST))   {
            player += deal(deck, dealt);
            //Figure 7 Output
            printf("Player's score: %d\n", player);
            if (player > BUST)   {
                bust = 1;
                //Figure 8 Output
                printf("Player BUSTED! Dealer wins the hand!\n");
                break;
            }
            else   {
                printf("Player, another card? (0 = STAND, 1 = HIT)\n");
                scanf(" %d", &choice);
            }
        }
        if(bust)   {
            //Figure 8
            printf("Play another hand? (1 = Yes, 0 = No)");
            scanf(" %d", &play);
            clearScreen();
            continue;
        }
        else   {

            if(dealer <= MIN_HIT)   {
                choice = HIT;
            }
            else   {
                choice = STAND;
            }
                //xii 2: while loop???
                while(choice == HIT)   {

                    dealer += deal(deck, dealt);

                    if(dealer <= MIN_HIT)   {
                        choice = HIT;
                    }
                    else {
                    choice = STAND;
                    }
                }
        }
        //Figure 9 output
        printf("Dealer's score: %d\n", dealer);
        cash += results(player, dealer);
        //Fig 8: Play another hand
        printf("Player, play another hand? (1 = Yes, 0 = No)\n");
        scanf(" %d", &play);
        clearScreen();

        }
    //Figure 10 Display;


    printf("Thank you for playing Black Jack Casino! Your cash out is $%d\n", cash);
    return cash;
}
//Results function
int results(int playerScore, int dealerScore)   {
    const int WIN = 20;
    const int PUSH = 10;
    const int LOSE = 0;

    if(dealerScore > BUST)   {
        printf("Dealer BUSTED!\n");
        return PUSH;
    }
    else if(dealerScore == playerScore)   {
        printf("It's a PUSH!\n");
        return PUSH;
    }
    else if(playerScore > dealerScore)   {
        printf("Player has won! Nice job!\n");
        return WIN;
    }
    else   {
        printf("Dealer has won! Too bad!\n");
        return LOSE;
    }
}
//Deal Function
int deal(char deck[SUITS][FACES], char dealt[SUITS][FACES])   {
    const int MAX = 52;
    int used;
    int score;
    int suit;
    int face;

    if(cards == MAX)  {
        cards = 0;
        initializeUsed(dealt);
    }
    while(used == 0)   {
        suit = rand() % SUITS;
        face = rand() % FACES;
        if(dealt[suit][face] == 0)   {
            used = 1;
            dealt[suit][face] = 1;
            cards++;
        }
    }
    switch(face)   {

    case 0:
        score = face + 2;
        break;

    case 1:
        score = face + 2;
        break;

    case 2:
        score = face + 2;
        break;

    case 3:
        score = face + 2;
        break;

    case 4:
        score = face + 2;
        break;

    case 5:
        score = face + 2;
        break;

    case 6:
        score = face + 2;
        break;

    case 7:
        score = face + 2;
        break;

    case 8:
        score = 10;
        break;

    case 9:
        score = 10;
        break;

    case 10:
        score = 10;
        break;

    case 11:
        score = 10;
        break;

    case 12:
        score = 11;
        break;
    }
return score;
}

void initializeUsed(char used[SUITS][FACES])   {
    int s;
    int f;

    for(s = 1; s <= SUITS; s++)   {
        for(f = 1; f <= FACES; f++)   {
            used[s][f] = 0;
        }
    }
}
//Creating Deck Function
void initializeDeck(char deck[SUITS][FACES])   {
    //const char face[] = {2,3,4,5,6,7,8,9,'T','J','Q','K','A', };
    const char face[] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};

    int i;
    int j;
    for(i = 0; i < SUITS; i++)   {
        for(j = 0; j < FACES; j++)   {
            deck[i][j] = face[j];
        }
    }
}
//Outputting deck on screen function (This took me forever to realize that I had '%d' instead of '%c'. Main reason why I turned this in so late. I am a fool.
void printDeck(char deck[SUITS][FACES])   {
    int i;
    int j;
    for(i = 0;i < SUITS; i++)   {
        for(j = 0;j < FACES; j++)   {
            switch(i)   {
                case 0:
                    printf("%c of ClUBS\n", deck[i][j]);
                    break;

                case 1:
                    printf("%c of DIAMONDS\n", deck[i][j]);
                    break;

                case 2:
                    printf("%c of HEARTS\n", deck[i][j]);
                    break;

                case 3:
                    printf("%c of SPADES\n", deck[i][j]);
                    break;
            }
        }
    }
}

//Function to create values for scratch off ticket One
OneDollar createScratchOffOne(OneDollar one)   {
    //Constants
    const int SYMS = 2, NUMS = 5, BASE = 20;
    const char symbols[] = {'$', '%', '&', '#', '@', '!'};

    //variables
    int usedSyms[6] = {0};

    //loop control
    int sym, n, used = 0;

    //Chooses winning number
    one.winNumber = (rand() % BASE) + 1;

    //Chooses player numbers
    for(n = 0; n < NUMS; n++)   {
        one.numbers[n] = (rand() % BASE) + 1;
    }

    //Chooses prizes
    for(n = 0; n < NUMS; n++)   {
        //Converts integer value to float
        one.prizes[n] = (float)(((rand() % BASE) + 1) * 5);;
    }
    //Chooses bonus symbols
    for(n = 0; n < SYMS; n++)   {
        used = 0;
        while(!used)   {
            sym = rand() % 6;
            switch(sym)   {
                case 0:
                    one.bonus[n] = symbols[0];
                    break;
                case 1:
                    one.bonus[n] = symbols[1];
                    break;
                case 2:
                    one.bonus[n] = symbols[2];
                    break;
                case 3:
                    one.bonus[n] = symbols[3];
                    break;
                case 4:
                    one.bonus[n] = symbols[4];
                    break;
                case 5:
                    one.bonus[n] = symbols[5];
                    break;
            }
            if(usedSyms[sym] == 0)   {
                usedSyms[sym] = 1;
                used = 1;
                break;
            }
        }
    }
return one;
}
//Displays Scratch offs for ticket ONE
void displayScratchOffOne(OneDollar displayOne)   {
    const int SYMS = 2, NUMS = 5;
    int i;
//Each space between code signifies a new line in display
    printf("Getting your scratch offs...\n");

    printf("+");
    for (i = 0; i < 42; i++)   {
        printf("-");
    }
    printf("+\n");

    printf("| WINNING NUMBER");
    if(displayOne.winNumber < 10) {
            printf("%8s", " ");
            printf("%d", displayOne.winNumber);
    }
    else
    {
        printf("%7s", " ");
        printf("%d", displayOne.winNumber);
    }
    printf("%18s|\n", " ");

    printf("|%42s|\n", " ");

    printf("| YOUR NUMBERS%29s|\n", " ");
    printf("|");
    for (i = 0; i < NUMS; i++)   {
        if (displayOne.numbers[i] < 10) {
            printf("%7s", " ");
            printf("%d", displayOne.numbers[i]);
        }
        else
        {
            printf("%6s", " ");
            printf("%d", displayOne.numbers[i]);
        }
    }
    printf("  |\n");

    printf("|%42s|\n", " ");

    printf("| PRIZES%35s|\n", " ");

    printf("|%42s|\n", " ");

    printf("|");
    for(i = 0; i < NUMS; i++)   {
        if (displayOne.prizes[i] < 10)   {
            printf("%4s", " ");
            printf("%.2f", displayOne.prizes[i]);
        }
        else if (displayOne.prizes[i] == 100)   {
            printf("%2s", " ");
            printf("%.2f", displayOne.prizes[i]);
        }
        else {
            printf("%3s", " ");
            printf("%.2f", displayOne.prizes[i]);
        }
    }
    printf("  |\n");

    printf("|%42s|\n", " ");

    printf("| SYMBOLS%34s|\n", " ");

    printf("|%42s|\n", " ");

    printf("|");
    for(i = 0; i < SYMS; i++)   {
        printf("%7s", " ");
        printf("%c", displayOne.bonus[i]);
    }
    printf("%26s|\n", " ");
    printf("+");
    for (i = 0; i < 42; i++)   {
        printf("-");
    }
    printf("+\n\n");
}
//Function to create values for scratch off ticket TWO
TwoDollar createScratchOffTwo(TwoDollar two)   {
    //constants for ticket two
    const int SYMS = 2, NUMS = 10, BASE = 30;
    const char symbols[] = {'$', '%', '&', '#', '@', '!'};

    //variables
    int usedSyms[6] = {0};
    int usedNums[31] = {0};
    int num;

    //loop control
    int sym, n, used = 0;
    //assigns Win nums
    for (n = 0; n < 2; n++)   {
        used = 0;
        while(!used)   {
            num = (rand() % BASE) + 1;

            if(usedNums[num] == 0)   {
                usedNums[num] = 1;
                two.winNumbers[n] = num;
                used = 1;
                break;
            }
        }
    }
    //assigns player nums
    for(n = 0; n < NUMS; n++)   {
        two.numbers[n] = (rand() % BASE) + 1;
    }
    //assigns prize values
    for(n = 0; n < NUMS; n++)   {
        //Converts integer value to float
        two.prizes[n] = (float)(((rand() % BASE) + 1) * 5);
    }
    //assigns symbols to bonus
    for(n = 0; n < SYMS; n++)   {
        used = 0;
        while(!used)   {
            sym = rand() % 6;
            switch(sym)   {
                case 0:
                    two.bonus[n] = symbols[0];
                    break;
                case 1:
                    two.bonus[n] = symbols[1];
                    break;
                case 2:
                    two.bonus[n] = symbols[2];
                    break;
                case 3:
                    two.bonus[n] = symbols[3];
                    break;
                case 4:
                    two.bonus[n] = symbols[4];
                    break;
                case 5:
                    two.bonus[n] = symbols[5];
                    break;
            }

            if(usedSyms[sym] == 0)   {
                usedSyms[sym] = 1;
                used = 1;
                break;
            }
        }
    }
    return two;
}
//Displays Scratch offs for ticket TWO
void displayScratchOffTwo(TwoDollar displayTwo)   {
    //Each space between code signifies a new line in display(excluding "BREAK"s)
    const int SYMS = 2, NUMS = 10, BREAK = 4;
    int i;
    printf("Getting your scratch offs...\n");

    printf("+");
    for (i = 0; i < 42; i++)   {
        printf("-");
    }
    printf("+\n");

    printf("| WINNING NUMBERS%6s", " ");
    for(i = 0; i < 2; i++)   {
        if(displayTwo.winNumbers[i] < 10) {
            printf("%5s", " ");
            printf("%d", displayTwo.winNumbers[i]);
        }
        else
        {
            printf("%4s", " ");
            printf("%d", displayTwo.winNumbers[i]);
        }
    }
    printf("%8s|\n", " ");

    printf("|%42s|\n", " ");

    printf("| YOUR NUMBERS%29s|\n", " ");
    printf("|");
    for (i = 0; i < NUMS; i++)   {
        if (displayTwo.numbers[i] < 10) {
            printf("%7s", " ");
            printf("%d", displayTwo.numbers[i]);
        }
        else
        {
            printf("%6s", " ");
            printf("%d", displayTwo.numbers[i]);
        }
        if (i == BREAK)  {
            printf("  |\n|");
        }
    }
    printf("  |\n");

    printf("|%42s|\n", " ");

    printf("| PRIZES%35s|\n", " ");

    printf("|%42s|\n", " ");

    printf("|");
    for(i = 0; i < NUMS; i++)   {
        if (displayTwo.prizes[i] < 10.0)   {
            printf("%4s", " ");
            printf("%.2f", displayTwo.prizes[i]);
        }
        else if (displayTwo.prizes[i] < 100.0)   {
            printf("%3s", " ");
            printf("%.2f", displayTwo.prizes[i]);
        }
        else   {
            printf("%2s", " ");
            printf("%.2f", displayTwo.prizes[i]);
        }
        if (i == BREAK)  {
            printf("  |\n|");
        }
    }
    printf("  |\n");

    printf("|%42s|\n", " ");

    printf("| SYMBOLS%34s|\n", " ");

    printf("|%42s|\n", " ");

    printf("|");
    for(i = 0; i < SYMS; i++)   {
        printf("%7s", " ");
        printf("%c", displayTwo.bonus[i]);
    }
    printf("%26s|\n", " ");
    printf("+");
    for (i = 0; i < 42; i++)   {
        printf("-");
    }
    printf("+\n\n");
}
//Function to create values for scratch off ticket FIVE
FiveDollar createScratchOffFive(FiveDollar five)   {
    //constants
    const int SYMS = 4, NUMS = 12, BASE = 50;
    const char symbols[] = {'$', '%', '&', '#', '@', '!', '^', '*'};

    //variables
    int usedSyms[8] = {0};
    int usedNums[51] = {0};
    int num;

    //loop control variables
    int sym, n, used = 0;

    //creates win nums
    for (n = 0; n < 4; n++)   {
        used = 0;
        while(!used)   {
            num = (rand() % BASE) + 1;

            if(usedNums[num] == 0)   {
                usedNums[num] = 1;
                five.winNumbers[n] = num;
                used = 1;
                break;
            }
        }
    }
    //creates player nums
    for(n = 0; n < NUMS; n++)   {
        five.numbers[n] = (rand() % BASE) + 1;
    }
    //creates prize values
    for(n = 0; n < NUMS; n++)   {
        //Convert integer value to float???? (7-h)
        five.prizes[n] = (float)(((rand() % BASE) + 1) * 5);
    }
    //assigns bonus symbols
    for(n = 0; n < SYMS; n++)   {
        used = 0;

        while(!used)   {
            sym = rand() % 8;
            switch(sym)   {
                case 0:
                    five.bonus[n] = symbols[0];
                    break;
                case 1:
                    five.bonus[n] = symbols[1];
                    break;
                case 2:
                    five.bonus[n] = symbols[2];
                    break;
                case 3:
                    five.bonus[n] = symbols[3];
                    break;
                case 4:
                    five.bonus[n] = symbols[4];
                    break;
                case 5:
                    five.bonus[n] = symbols[5];
                    break;
                case 6:
                    five.bonus[n] = symbols[6];
                    break;
                case 7:
                    five.bonus[n] = symbols[7];
                    break;
            }
            if(usedSyms[sym] == 0)   {
                usedSyms[sym] = 1;
                used = 1;
                break;
            }
        }
    }
    return five;
}
//Displays Scratch offs for ticket FIVE
void displayScratchOffFive(FiveDollar displayFive)   {
    //Each space between code signifies a new line in display(excluding "BREAK"s)
    const int SYMS = 4, NUMS = 12, BREAK = 4;
    int i;
    printf("Getting your scratch offs...\n");

    printf("+");

    for (i = 0; i < 42; i++)   {
        printf("-");
    }
    printf("+\n");

    printf("| WINNING NUMBERS%7s", " ");
    for(i = 0; i < 4; i++)   {
        if(displayFive.winNumbers[i] < 10) {
            printf("%3s", " ");
            printf("%d", displayFive.winNumbers[i]);
        }
        else
        {
            printf("%2s", " ");
            printf("%d", displayFive.winNumbers[i]);
        }
    }
    printf("%3s|\n", " ");

    printf("|%42s|\n", " ");

    printf("| YOUR NUMBERS%29s|\n", " ");

    printf("|");
    for (i = 0; i < NUMS; i++)   {
        if (displayFive.numbers[i] < 10) {
            printf("%7s", " ");
            printf("%d", displayFive.numbers[i]);
        }
        else
        {
            printf("%6s", " ");
            printf("%d", displayFive.numbers[i]);
        }

        if (i == BREAK)  {
            printf("  |\n|");
        }
        else if (i == (BREAK * 2))   {
            printf("%10s|\n|", " ");
        }
    }
    printf("%18s|\n", " ");

    printf("|%42s|\n", " ");

    printf("| PRIZES%35s|\n", " ");

    printf("|%42s|\n", " ");

    printf("|");
    for(i = 0; i < NUMS; i++)   {
        if (displayFive.prizes[i] < 10)   {
            printf("%4s", " ");
            printf("%.2f", displayFive.prizes[i]);
        }
        else if (displayFive.prizes[i] < 100)   {
            printf("%3s", " ");
            printf("%.2f", displayFive.prizes[i]);
        }
        else   {
            printf("%2s", " ");
            printf("%.2f", displayFive.prizes[i]);
        }
        if (i == BREAK)  {
            printf("  |\n|");
        }
        else if (i == (BREAK * 2))   {
            printf("%10s|\n|", " ");
        }
    }
    printf("%18s|\n", " ");

    printf("|%42s|\n", " ");

    printf("| SYMBOLS%34s|\n", " ");

    printf("|%42s|\n", " ");

    printf("|");
    for(i = 0; i < SYMS; i++)   {
        printf("%7s", " ");
        printf("%c", displayFive.bonus[i]);
    }
    printf("%10s|\n", " ");
    printf("+");
    for (i = 0; i < 42; i++)   {
        printf("-");
    }
    printf("+\n\n");
}

//Function for OneDollarScratchoff
int cashOneDollar(OneDollar cashOne)   {
    //Declaring constants
    const int SYMS = 2, NUMS = 5;

    //Variables
    float cash;

    //loop control
    int n;

    //Gets Bonus symbol
    char bonus = getBonus(ONE);

    printf("Bonus symbol is %c\n\n\n", bonus);
    //Compares player nums to winning nums and assigns prizes accordingly
    for(n = 0; n < NUMS; n++)   {
        if(cashOne.numbers[n] == cashOne.winNumber)   {
            cash += cashOne.prizes[n];
        }
    }
    //Compares player symbols to bonus symbol
    for (n = 0; n < SYMS; n++)   {
        if(cashOne.bonus[n] == bonus)   {
            cash += BONUS;
        }
    }
    printf("Your One Dollar Scratch Off won $%.2f\n\n", cash);
    return (int) cash;
}

//Function for TwoDollarScratchoff
int cashTwoDollar(TwoDollar cashTwo)   {
    //Declaring constants
    const int WINS = 2, SYMS = 2, NUMS = 10;

    //Variables
    float cash;

    //loop control
    int w, n;

    //Gets Bonus symbol
    char bonus = getBonus(TWO);

    printf("Bonus symbol is %c\n\n\n", bonus);

    //Compares player nums to winning nums and assigns prizes accordingly
    for(n = 0; n < WINS; n++)   {
        for(w = 0; w < NUMS; w++)   {
            if(cashTwo.numbers[w] == cashTwo.winNumbers[n])   {
                cash += cashTwo.prizes[w];
            }
        }
    }
    //Compares player symbols to bonus symbol
    for(n = 0; n < SYMS; n++)   {
        if(cashTwo.bonus[n] == bonus)   {
            cash += BONUS;
        }
    }
    printf("Your Two Dollar Scratch Off won $%.2f\n\n", cash);
    return (int) cash;
}
//Function for FiveDollarScratchoff
int cashFiveDollar(FiveDollar cashFive)   {
    //Declaring constants
    const int WINS = 4, SYMS = 4, NUMS = 12;

    //Variables
    float cash;

    //loop control
    int w, n;

    //Gets Bonus symbol
    char bonus = getBonus(FIVE);

    printf("Bonus symbol is %c\n\n\n", bonus);

    //Compares player nums to winning nums and assigns prizes accordingly
    for(n = 0; n < WINS; n++)   {
        for(w = 0; w < NUMS; w++)   {
            if(cashFive.numbers[w] == cashFive.winNumbers[n])   {
                cash += cashFive.prizes[w];
            }
        }
    }
    //Compares player symbols to bonus symbol
    for(n = 0; n < SYMS; n++)   {
        if(cashFive.bonus[n] == bonus)   {
            cash += BONUS;
        }
    }
    printf("Your Five Dollar Scratch Off won $%.2f\n\n", cash);
    return (int) cash;
}
//Function for getting bonus character
char getBonus (int type)   {
    //Declaring constants
    const int ONE_TWO = 6, FIVE_RAND = 8;
    const char SYMBOLS[] = {'$', '%', '&', '#', '@', '!', '^', '*'};

    //Variables
    char bonus;
    int sym;

    //Gets random bonus symbol from SYMBOLS array and assigns to bonus
    if(type == ONE || type == TWO)   {
        sym = rand() % 6;

        switch(sym)   {
            case 0:
                bonus = SYMBOLS[0];
                break;
            case 1:
                bonus = SYMBOLS[1];
                break;
            case 2:
                bonus = SYMBOLS[2];
                break;
            case 3:
                bonus = SYMBOLS[3];
                break;
            case 4:
                bonus = SYMBOLS[4];
                break;
            case 5:
                bonus = SYMBOLS[5];
                break;
        }
    }
    //Gets random bonus symbol from SYMBOLS array and assigns to bonus
    else if (type == FIVE)   {
        sym = rand() % 8;

        switch(sym)   {
            case 0:
                bonus = SYMBOLS[0];
                break;
            case 1:
                bonus = SYMBOLS[1];
                break;
            case 2:
                bonus = SYMBOLS[2];
                break;
            case 3:
                bonus = SYMBOLS[3];
                break;
            case 4:
                bonus = SYMBOLS[4];
                break;
            case 5:
                bonus = SYMBOLS[5];
                break;
            case 6:
                bonus = SYMBOLS[6];
                break;
            case 7:
                bonus = SYMBOLS[7];
                break;
        }
    }
    return bonus;
}


