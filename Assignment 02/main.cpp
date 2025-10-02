#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

using namespace std; 

int main()

{

// print title of game, then, new line
 cout <<"LOTO MAX Random Number Game" ".\n";

 // print group members and group number to console 
 cout << "Written by Mariam Mueen" ".\n" 
"and Fayzabanu Diwan" ".\n"

"Group 9" ".\n";
 // get name from user
 // REFERENCE: Murach C++ Slides, Week 2 Part 2, C2 Slide 24

string PlayerName;
 cout << "Please enter your name: ";
 getline (cin, PlayerName);
 cout << "Hello " << PlayerName << ".\n";

 // declare variable for number guess
string NumberGuess;

 // get number guess from user
 cout << "Please enter your LOTO numbers (You should input seven two-digit numbers), " << 
PlayerName << ".\n";
 cin >> NumberGuess; 

 // print guess 
 cout << "You guessed: " << NumberGuess << ".\n";

 // generate 7 random numbers between 1 and 49
 // Reference: https://cplusplus.com/reference/cstdlib/rand/
 // Chose to find more efficient way of generating random numbers lol 
int GeneratedNumber1 = rand() % 50; 
int GeneratedNumber2 = rand() % 50; 
int GeneratedNumber3 = rand() % 50; 
int GeneratedNumber4 = rand() % 50; 
int GeneratedNumber5 = rand() % 50; 
int GeneratedNumber6 = rand() % 50; 
int GeneratedNumber7 = rand() % 50; 

 // print them
 cout << "The lucky LOTO numbers are: "
<< GeneratedNumber1 << " "
<< GeneratedNumber2 << " "
<< GeneratedNumber3 << " "
<< GeneratedNumber4 << " "
<< GeneratedNumber5 << " "
<< GeneratedNumber6 << " "
<< GeneratedNumber7 << "\n";

 // thank player, and end game 
 cout << "Thank you for playing, " << PlayerName << "." ".\n"
" Play again soon!";

return 0;

}