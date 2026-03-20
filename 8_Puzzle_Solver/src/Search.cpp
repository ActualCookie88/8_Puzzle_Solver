#include "../header/Search.hpp"
#include "../header/Puzzle.hpp"
#include "../header/Heuristics.hpp"
#include "../header/globals.hpp"
#include <queue>
#include <unordered_map>
#include <iostream>

using namespace::std;

void generalSearch(const vector<vector<int>>& puzzle_, int algorithm) {
    // establish pqueue and visited set
    priority_queue<Node> pq;
    unordered_map<string, int> bestGn;
    vector<string> algs = {"UNIFORM COST SEARCH", "the MISPLACED TILE HEURISTIC", "the MANHATTAN DISTANCE HEURISTIC"};

    // initial state/node, establish gn and hn
    Node init;
    init.puzzle = puzzle_;
    init.gn = 0;

    if(algorithm == 1) {
        init.hn = uniformHeuristic(puzzle_);
    }
    else if(algorithm == 2) {
        init.hn = misplacedHeuristic(puzzle_);
    } 
    else if(algorithm == 3) {
        init.hn = manhattanHeuristic(puzzle_);
    }
    else {
        cout << "ERROR";
        return;
    }

    pq.push(init);

    int numExpanded = 0;
    int queueSize = 1;

    // start loop
    while(!pq.empty()) {
        queueSize = max(queueSize, (int)pq.size());

        Node curr = pq.top();
        pq.pop();

        cout << "The best state to expand with g(n) = " << curr.gn << " and h(n) = " << curr.hn << " is:\n";
        displayPuzzle(curr.puzzle, 2);
        cout << "Expanding this node...\n\n";

        // convert 2D puzzle to string for hashing
        string s = puzzleToString(curr.puzzle);
        
        // if current state not visited yet, expand
        if(bestGn.find(s) != bestGn.end() && bestGn[s] <= curr.gn) continue;

        bestGn[s] = curr.gn;

        // check if puzzle is solved
        if(curr.puzzle == solution) {
            border();
            cout << "Goal state reached! You used " << algs[algorithm-1] << "!\n\n" << 
                    "Solution Depth: " << curr.gn << endl <<
                    "Nodes Expanded: " << numExpanded << endl <<
                    "Max Queue size: " << queueSize << endl;
            return;
        }
        
        // continue expanding
        numExpanded++;
        
        vector<vector<vector<int>>> children = expand(curr.puzzle);

        // loop over every state
        for(int i = 0; i < children.size(); i++) {
            vector<vector<int>> childPuzzle = children[i];

            int newGn = curr.gn + 1;

            // convert 2D puzzle to string for hashing
            string st = puzzleToString(childPuzzle);

            // A*, keep best path
            if(bestGn.count(st) && bestGn[st] <= newGn) continue;

            // child state/node, establish gn and hn
            Node child;
            child.puzzle = childPuzzle;
            child.gn = newGn;

            if(algorithm == 1) {
                child.hn = uniformHeuristic(childPuzzle);
            }
            else if(algorithm == 2) {
                child.hn = misplacedHeuristic(childPuzzle);
            } 
            else if(algorithm == 3) {
                child.hn = manhattanHeuristic(childPuzzle);
            }
            else {
                cout << "ERROR";
                return;
            }
            pq.push(child);
        }
        //cout << "------------------------------------------" << endl;
    }
    // all states have been visited
    cout << "\nFAILED TO FIND SOLUTION!\n";
}