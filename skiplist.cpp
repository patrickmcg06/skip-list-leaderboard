#include "skiplist.h"
#include <cstdlib>
#include <ctime>

using namespace std;

SkipNode::SkipNode(const string& name, int score, int level)
    : name(name), score(score), forward(level, nullptr) {}

SkipList::SkipList(int maxLevel, float probability)
    : maxLevel(maxLevel), level(0), probability(probability) {
    header = new SkipNode("", -1, maxLevel);
    srand((unsigned)time(nullptr));
}

SkipList::~SkipList() {
    SkipNode* current = header->forward[0];
    while (current) {
        SkipNode* next = current->forward[0];
        delete current;
        current = next;
    }
    delete header;
}

int SkipList::randomLevel() const {
    int lvl = 1;
    while (((float)rand() / RAND_MAX) < probability && lvl < maxLevel) {
        lvl++;
    }
    return lvl;
}

static bool ranksAbove(int scoreA, const string& nameA,
                        int scoreB, const string& nameB) {
    if (scoreA != scoreB) return scoreA > scoreB;
    return nameA < nameB;
}

void SkipList::insertNode(const string& name, int score) {
    vector<SkipNode*> update(maxLevel, header);
    SkipNode* current = header;

    for (int i = level - 1; i >= 0; i--) {
        while (current->forward[i] &&
               ranksAbove(current->forward[i]->score, current->forward[i]->name, score, name)) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    int newLevel = randomLevel();
    if (newLevel > level) {
        for (int i = level; i < newLevel; i++) {
            update[i] = header;
        }
        level = newLevel;
    }

    SkipNode* newNode = new SkipNode(name, score, newLevel);
    for (int i = 0; i < newLevel; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
}

void SkipList::removeNode(const string& name, int score) {
    vector<SkipNode*> update(maxLevel, header);
    SkipNode* current = header;

    for (int i = level - 1; i >= 0; i--) {
        while (current->forward[i] &&
               ranksAbove(current->forward[i]->score, current->forward[i]->name, score, name)) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];
    if (current && current->name == name && current->score == score) {
        for (int i = 0; i < level; i++) {
            if (update[i]->forward[i] != current) break;
            update[i]->forward[i] = current->forward[i];
        }
        delete current;

        while (level > 1 && header->forward[level - 1] == nullptr) {
            level--;
        }
    }
}

void SkipList::addPlayer(const string& name, int score) {
    if (playerScores.find(name) != playerScores.end()) return; // already exists
    insertNode(name, score);
    playerScores[name] = score;
}

void SkipList::removePlayer(const string& name) {
    auto it = playerScores.find(name);
    if (it == playerScores.end()) return;
    removeNode(name, it->second);
    playerScores.erase(it);
}

void SkipList::updateScore(const string& name, int newScore) {
    auto it = playerScores.find(name);
    if (it == playerScores.end()) return; // not on the leaderboard

    int oldScore = it->second;
    if (oldScore == newScore) return;

    removeNode(name, oldScore);
    insertNode(name, newScore);
    it->second = newScore;
}

bool SkipList::hasPlayer(const string& name) const {
    return playerScores.find(name) != playerScores.end();
}

int SkipList::getScore(const string& name) const {
    auto it = playerScores.find(name);
    return it != playerScores.end() ? it->second : -1;
}

vector<pair<string, int>> SkipList::getRankings() const {
    vector<pair<string, int>> results;
    SkipNode* current = header->forward[0];
    while (current) {
        results.push_back({current->name, current->score});
        current = current->forward[0];
    }
    return results;
}

vector<pair<string, int>> SkipList::getTopN(int count) const {
    vector<pair<string, int>> results;
    SkipNode* current = header->forward[0];
    while (current && (int)results.size() < count) {
        results.push_back({current->name, current->score});
        current = current->forward[0];
    }
    return results;
}
