#include <iostream>
#include <sstream>
#include <iomanip>
#include "skiplist.h"

using namespace std;

void printHelp() {
    cout << "Commands:\n"
              << "  add name score          - add a new player\n"
              << "  update name score       - update an existing player's score\n"
              << "  remove name             - remove a player\n"
              << "  rank                    - show the full leaderboard\n"
              << "  top number              - show the top x number of players\n"
              << "  help                    - show this message\n"
              << "  quit                    - exit\n";
}

void printRankings(const vector<pair<string, int>>& rankings) {
    if (rankings.empty()) {
        cout << "Leaderboard is empty\n";
        return;
    }

    int rank = 1;
    for (const auto& entry : rankings) {
        cout << "  " << left << setw(4) << (to_string(rank) + ".")
             << setw(15) << left << entry.first
             << entry.second << "\n";
        rank++;
    }
}

int main() {
    SkipList leaderboard;
    printHelp();

    leaderboard.addPlayer("DoulbleDragon", 8510);
    leaderboard.addPlayer("RodrigoGona", 5885);
    leaderboard.addPlayer("Dragon", 5650);
    leaderboard.addPlayer("doublehorns", 3805);
    leaderboard.addPlayer("Artimus", 3770);
    leaderboard.addPlayer("DevastatorB1D", 2890);
    leaderboard.addPlayer("Ards-El", 6600);
    leaderboard.addPlayer("soldier-killer", 5665);
    leaderboard.addPlayer("kodu86", 4730);
    leaderboard.addPlayer("MDMAX", 4560);
    leaderboard.addPlayer("DotFire", 3120);
    leaderboard.addPlayer("Hanna1112", 1765);

    string line;

    while (true) {
        cout << "> ";

        if (!getline(cin, line))
            break;

        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "quit" || command == "exit") {

            string extra;
            if (iss >> extra) {
                cout << "Unknown command. Type help for options.\n";
                continue;
            }

            break;

        } else if (command == "help") {

            string extra;
            if (iss >> extra) {
                cout << "Unknown command. Type help to see commands.\n";
                continue;
            }

            printHelp();

        } else if (command == "add") {

            string name;
            int score;
            string extra;

            if (!(iss >> name >> score) || (iss >> extra)) {
                cout << "Unknown command. Type help for options.\n";
                continue;
            }

            if (leaderboard.hasPlayer(name)) {
                cout << name << " already exists.\n";
            } else {
                leaderboard.addPlayer(name, score);
                cout << "Added " << name << " with score " << score << ".\n";
            }

        } else if (command == "update") {

            string name;
            int score;
            string extra;

            if (!(iss >> name >> score) || (iss >> extra)) {
                cout << "Unknown command. Type help for options.\n";
                continue;
            }

            if (!leaderboard.hasPlayer(name)) {
                cout << name << " not found.\n";
            } else {
                leaderboard.updateScore(name, score);
                cout << "Updated " << name << " to score " << score << ".\n";
            }

        } else if (command == "remove") {

            string name;
            string extra;

            if (!(iss >> name) || (iss >> extra)) {
                cout << "Unknown command. Type help for options.\n";
                continue;
            }

            if (!leaderboard.hasPlayer(name)) {
                cout << name << " not found.\n";
            } else {
                leaderboard.removePlayer(name);
                cout << "Removed " << name << ".\n";
            }

        } else if (command == "rank") {

            string extra;

            if (iss >> extra) {
                cout << "Unknown command. Type help for options.\n";
                continue;
            }

            printRankings(leaderboard.getRankings());

        } else if (command == "top") {

            int n;
            string extra;

            if (!(iss >> n) || (iss >> extra)) {
                cout << "Unknown command. Type help for options.\n";
                continue;
            }

            printRankings(leaderboard.getTopN(n));

        } else {

            cout << "Unknown command. Type help for options.\n";
        }
    }

    cout << "Shutting down.\n";
    return 0;
}