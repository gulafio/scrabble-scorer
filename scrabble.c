#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// STARTING TILE -> DOUBLE WORD SCORE

// LETTER POINTS
int scores[] = {
    // A B C D E F G H I J K L M N O P
       1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,
    // Q R S T U V W X Y Z
       10,1,1,1,1,4,4,8,4,10
};

// PLAYER STRUCTS
struct player {
    char name[20];
    int score;
    int passes;
};

// FUNCTIONS
int letterScores(char letter);
int scoreCalculator(char word[], char dlLetter, char tlLetter, int dw, int tw, char blankLetter);
struct player createPlayer(char name[]);
int allPlayersPassedTwice(struct player players[], int playerCount);
void endGame(struct player players[], int playerCount);
void gameLoop(struct player players[], int playerCount);

int main(void) {

    int playerNum = 0;
    printf("How many people are playing?\n");
    scanf("%d", &playerNum);
    struct player players[playerNum];


    for (int i = 0; i < playerNum; i++) {
        char name[20];
        printf("What is Player number #%d's name?\n", i+1);
        scanf("%19s", name);

        players[i] = createPlayer(name);
    }

    gameLoop(players, playerNum);
    printf("\nAll players have passed twice. Game over.\n");
    endGame(players, playerNum);
    return 0;
}

struct player createPlayer(char name[]) {
    struct player p = {0};
    strcpy(p.name, name);
    return p;
}

int allPlayersPassedTwice(struct player players[], int playerCount) {
    for (int i = 0; i < playerCount; i++) {
        if (players[i].passes < 2) {
            return 0;
        }
    }
    return 1;
}

void gameLoop(struct player players[], int playerCount) {
    int currentPlayer = 0;

    while (!allPlayersPassedTwice(players, playerCount)) {
        struct player *p = &players[currentPlayer];

        int choice = 0;
        do{
            printf("\n%s's turn\n", p->name);
            printf("1 - Play word\n");
            printf("2 - Exchange tiles\n");
            printf("3 - Pass\n");

            printf("\nEnter a number to choose:\n");
            if(scanf("%d", &choice) != 1){
                printf("Invalid input. Please enter a number.\n");
                while(getchar() != '\n');
                choice = 0;
            }
            

            if(choice < 1 || choice > 3){
                printf("Invalid choice. Pick again\n");
            }

        } while(choice < 1 || choice > 3);

        if(choice == 1) {
            // Play word
            int wordConfirm = 0;
            char word[50];

            do{
                printf("Enter a word\n");
                scanf("%49s", word);
                printf("\n Your word is %s. Is this correct? (Enter '1' if yes or '0' to go back)\n", word);

                if(scanf("%d", &wordConfirm) != 1){
                    printf("Invalid input. Please enter a number.\n");
                    while(getchar() != '\n');
                    wordConfirm = 0;
                }
            } while(wordConfirm != 1);

            int multChoice = 0, dw = 0, tw = 0;
            char dlLetter = '\0', tlLetter = '\0';

            // Subtracts the blank tile from the score, if any
            char blankLetter = '\0';
            int blankChoice = 0;

            do {
                printf("Are there any blanks?\n 1 - Yes\n 2 - No\n");

                if(scanf("%d", &blankChoice) != 1){
                    printf("Invalid input. Please enter a number.\n");
                    while(getchar() != '\n');
                    blankChoice = 0;
                }

                if(blankChoice < 1 || blankChoice > 2)
                    printf("Invalid choice. Pick again\n");
            } while(blankChoice < 1 || blankChoice > 2);

            if(blankChoice == 1) {
                printf("Which letter is the blank?\n");
                scanf(" %c", &blankLetter);
                blankLetter = toupper(blankLetter);
            }

            do{
                printf("Are there any multipliers?\n\n");
                printf("1 - Double Letter Multiplier\n");
                printf("2 - Triple Letter Multiplier\n");
                printf("3 - Double Word Multiplier\n");
                printf("4 - Triple Word Multiplier\n");
                printf("5 - No Multipliers\n");

                if(scanf("%d", &multChoice) != 1){
                    printf("Invalid input. Please enter a number.\n");
                     while(getchar() != '\n');
                     multChoice = 0;
                }

                if(multChoice < 1 || multChoice > 5){
                    printf("Invalid choice. Pick again\n");
                } else{
                    switch(multChoice){
                    case 1:
                        // DOUBLE LETTER
                        printf("Which letter has the double letter score?\n");
                        scanf(" %c", &dlLetter);
                        dlLetter = toupper(dlLetter);
                        break;
                    case 2:
                        // TRIPLE LETTER
                        printf("Which letter has the triple letter score?\n");
                        scanf(" %c", &tlLetter);
                        tlLetter = toupper(tlLetter);
                        break;
                    case 3: 
                        // DOUBLE WORD
                        printf("How many double word score tiles did you hit?\n");
                        if(scanf("%d", &dw) != 1){
                            printf("Invalid input. Please enter a number.\n");
                            while(getchar() != '\n');
                            dw = 0;
                        }
                        break;
                    case 4:
                        // TRIPLE WORD
                        printf("How many triple word score tiles did you hit?\n");
                        if(scanf("%d", &tw) != 1){
                            printf("Invalid input. Please enter a number.\n");
                            while(getchar() != '\n');
                            tw = 0;
                        }
                        break;
                    case 5:
                        break;
                    }
                }
            } while(multChoice != 5);

            int score = scoreCalculator(word, dlLetter, tlLetter, dw, tw, blankLetter);

            p->score += score;
            printf("%s scored %d! Total: %d\n", p->name, score, p->score);
        }

        if (choice == 2) {
            // Exchange tiles
            printf("%s chose to exchange tiles.\n", p->name);
        }

        if (choice == 3) {
            // Pass
            p->passes++;
            printf("%s passed (%d/2)\n", p->name, p->passes);
        } else if(choice == 1 || choice == 2){
            p->passes = 0;
        } 


        currentPlayer = (currentPlayer + 1) % playerCount;
    }
}


int letterScores(char letter) {
    letter = toupper(letter);
    // Checks if the letter is valid
    if (letter >= 'A' && letter <= 'Z') {
        // Returns the point number associated with it
        return scores[letter - 'A'];
    }
    return 0;
}

int scoreCalculator(char word[], char dlLetter, char tlLetter, int dw, int tw, char blankLetter){
    // ORDER OF OPERATIONS:
    // 1) DL (Double Letter) 
    // 2) TL (Triple Letter) 
    // 3) DW (Double Word) 
    // 4) TW (Triple Word) 

    int dlPos = -1, tlPos = -1, blankPos = -1;

    // Find positions
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        if (toupper(word[i]) == dlLetter && dlPos == -1) dlPos = i;
        if (toupper(word[i]) == tlLetter && tlPos == -1) tlPos = i;
        if (toupper(word[i]) == blankLetter && blankPos == -1) blankPos = i;
    }

    // Calculate score
    int score = 0;
    for (int i = 0; i < len; i++) {
        int ls = letterScores(word[i]);
        if (i == blankPos) ls = 0;
        if (i == dlPos) ls *= 2;
        if (i == tlPos) ls *= 3;
        score += ls;
    }

    // Apply word multipliers
    for(int i = 0; i < dw; i++) score *= 2;
    for(int i = 0; i < tw; i++) score *= 3;

    return score;
}

void endGame(struct player players[], int playerCount){
    int highestScore = 0;
    int winnerIndex = 0;
    int isTie = 0;
    int secondWinnerIndex = 0;

    printf("FINAL SCOREBOARD:\n");

    for(int i = 0; i < playerCount; i++){
        printf("Player %d: %s - %d points\n", i+1, players[i].name, players[i].score);
        if(players[i].score > highestScore){
            highestScore = players[i].score;
            winnerIndex = i;
            isTie = 0;
        } else if(players[i].score == highestScore){
            isTie = 1;
            secondWinnerIndex = i;
        }
    }

    if(isTie == 0){
        printf("The winner is %s with a score of %d points!\n Congratulations!", players[winnerIndex].name, players[winnerIndex].score);
    } else{
        printf("The game was a tie!\n The winners are %s and %s with a score of %d points!\n Congratulations!", players[winnerIndex].name, players[secondWinnerIndex].name, players[winnerIndex].score);
    } 

}
