# skip-list-leaderboard
Project Overview

The project is an interactive leaderboard model implemented in C++. The program uses a skip list as its main data structure to store and maintain players and their scores. The purpose of my project is to show how a skip list can be used to maintain a leaderboard that displays players ranks based on their scores and what will change if their scores are updated, players removed or added, and even if there is a tiebreaker then the leaderboard will rank them in alphabetical order. 

Data Structure used

In this project I used a skip list, a skip list is a linked list based data structure that uses multiple levels of forward pointers. The lowest level contains every element, while higher levels contain less elements; this allows the program to skip over large sections of the list. 

Each player is represented by a SkipNode that contains: 
player’s name 
player’s score 
a vector of forward pointers

As well as the skip list the project uses an unordered_map called playerScores. This stores both the player’s names and scores and allows the code to quickly check if a player exists so then it can fetch the score. This means that the two structures work together, a skip list to keep the players sorted and an unordered map to look up the player’s names. 

Why

I used a skip list because a normal linked list would require the program to move through the players one at a time when searching for a position, which would become very inefficient if the leaderboard was large. The skip list makes this a lot better as it provides more levels of forward pointers. These higher levels mean that the program can jump over multiple players at once. So when using a skip list the searching and inserting takes O(log n) time whereas a normal linked list would take O(n). This means that using a skip list for a leaderboard is much more efficient especially if a leaderboard is frequently changing in real time. 

Running the program

The program already starts off with a set of players with scores to simulate an already existing game (I mostly used the leaderboard from the image I submitted in my proposal)

The commands appear as follows:

Commands:
  add name score          - add a new player
  update name score       - update an existing player's score
  remove name             - remove a player
  rank                    - show the full leaderboard
  top number              - show the top x number of players
  help                    - show this message
  quit                    - exit

The add command when used correctly will add a player to the leaderboard with the score you input and is used as so:
add james 8594
Added james with score 8594

The update command allows you to change the score of any existing player by just inputting their name and a new score. It does this by finding the player’s current score then removing the old node, inserting a new one with a new score and finally updating the player’s score in the unordered_map.
update james 8
Updated james to score 8
However if you try to update a player who doesn’t exist it will say
update jeff 98
jeff not found.

The remove command as expected lets you remove players from the leaderboard again as long as they exist or you will receive the same not found response. If you remove all the players and then try to use the rank command it will let you know that the leaderboard is empty.

The rank command shows you the complete leaderboard ordered from highest to lowest score. If any players have the same score then it will sort alphabetically with capital letters always overruling if the same. There is no limit to the number of players that can be added to the leaderboard other than memory but the rank will only show the top 100. So at the start of the program thanks to the preexisting set of players the leaderboard looks as follows.
  1.  DoulbleDragon  8510
  2.  Ards-El        6600
  3.  RodrigoGona    5885
  4.  soldier-killer 5665
  5.  Dragon         5650
  6.  kodu86         4730
  7.  MDMAX          4560
  8.  doublehorns    3805
  9.  Artimus        3770
  10. DotFire        3120
  11. DevastatorB1D  2890
  12. Hanna1112      1765

The top command allows you to shrink the leaderboard to a certain number of players such as top 3 would output 
  1.  DoulbleDragon  8510
  2.  Ards-El        6600
  3.  RodrigoGona    5885

The help command brings up the list of commands again in case you have forgotten what the commands are.

If anything other than the commands are used or they are used incorrectly e.g. add jeff. But not a score or a command isn’t used at all e.g. please. Then there will be an output:
Unknown command. Type help to see commands. 

Finally the quit command is used to end the program and will say ‘Shutting down.’ before the program ends. 

To compile and run the program 
g++ main.cpp skiplist.cpp -o leaderboard
./leaderboard