#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <string>
#include <vector>
#include <unordered_map>


using namespace std;

struct SkipNode {
    string name;
    int score;
    vector<SkipNode*> forward; 
    SkipNode(const string& name, int score, int level);
};

class SkipList {
public:
    SkipList(int maxLevel = 16, float probability = 0.5f);
    ~SkipList();

    void addPlayer(const string& name, int score);

    void removePlayer(const string& name);

    void updateScore(const string& name, int newScore);

    bool hasPlayer(const string& name) const;

    int getScore(const string& name) const;

    vector<pair<string, int>> getRankings() const;

    vector<pair<string, int>> getTopN(int count) const;

    int size() const { return playerScores.size(); }

private:
    SkipNode* header;
    int maxLevel;
    int level;          
    float probability;
    unordered_map<string, int> playerScores; 

    int randomLevel() const;

    void removeNode(const string& name, int score);

    void insertNode(const string& name, int score);
};

#endif
