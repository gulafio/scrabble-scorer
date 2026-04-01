==== SCRABBLE SCORE TRACKER: ====
A console-based Scrabble score tracking tool written in C. Designed to assist players during a physical game of Scrabble by handling all score calculations automatically.

==== FEATURES: ====
_Multi-player support
_Letter scoring based on official Scrabble tile values
_Premium square multipliers:
  _Double/Triple Letter Scores
  _Double/Triple Word Scores
  _Support for multiple multipliers in a single word
_Blank tile handling
_Input validation
_Pass tracking — game ends when all players pass twice consecutively
_Final scoreboard with winner announcement (accounts for ties)

==== COMPILING INSTRUCTIONS: ====
Make sure you have GCC installed, then run:

bash
gcc -Wall scrabble.c -o scrabble

==== HOW TO RUN: ====
bash
./scrabble

ON WINDOWS:
bash
scrabble.exe

==== HOW TO USE: ====
1) Enter the number of players and each player's name
2) On each turn, choose to play a word, exchange tiles, or pass
3) If playing a word, enter the word and any applicable multipliers
4) The program calculates and tracks the score automatically
5) A final scoreboard displays all scores and announces the winner

==== GAME RULES: ====
1) Each player will start by drawing one tile randomly. The player that drew the letter closest to 'A' will begin.
2) Each player's turn starts by drawing 7 tiles from the bag. You must always have 7 at a time if possible.
3) A player can choose to either use their turn to place a word, exchange a tile, or pass.
4) When exchanging tiles, a player can exchange either 1 or all
5) After an extra point square has been used once, it cannot be used again.
6) If every player passes their turn twice, the game ends

==== PROJECT BACKGROUND: ====
This project was built as a way to improve upon my coding skills in C outside of general coursework, using structs, functions, arrays, string manipulation, and input validation. I like to play a lot of board games with my family, and when it came to scrabble, it was a hassle to have to keep track of everything in pen and paper. I joked that I could write a program that handled everything for us in no more than a week, and thus, this program was made!
