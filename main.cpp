#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

/* ////////////////////////////////////////////////////////////////////

SCAN FILE FOR FEATURES/INSTANCES

//////////////////////////////////////////////////////////////////// */

vector<vector<double>> dataSet;
int numFeatures = 0;

bool scanData(string fileName) {
    ifstream inputFile(fileName);

    // error handling
    if (!inputFile.is_open()) {
        cout << "Error: could not open file.\n";
        return false;
    }

    string line;

    // scan file
    while(getline(inputFile, line)) {
        stringstream ss(line);
        vector<double> instance;
        double value;

        // scan row
        while(ss >> value) {
            instance.push_back(value);
        }

        if(!instance.empty()) {
            dataSet.push_back(instance);
        }
    }

    inputFile.close();

    if(!dataSet.empty()) {
        numFeatures = dataSet[0].size() - 1; // number of columns - class #
    }

    return true;
}

/* ////////////////////////////////////////////////////////////////////

HELPERS

//////////////////////////////////////////////////////////////////// */

// for terminal display purposes
void border() {
    cout << endl;
    cout << "//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
    cout << endl;
}

// user input checker
int selectOptionHelper(int min, int max) {
    string input;
    int number;
    while(true) {
        cin >> input;
        cout << endl;
        try {
            number = stoi(input); 
        } catch(...) {
            cout << "INVALID OPTION. TRY AGAIN: ";
            continue;
        }
        if(number >= min && number <= max) {
            return number;
        } else {
            cout << "INVALID OPTION. TRY AGAIN: ";
        }
    }
}

// Euclidean Distance formula helper
double euclideanDistance(int row1, int row2, const vector<int>& featureSet) {
    double sum = 0.0;

    // compute sum of squared differences between two points
    for(int feature : featureSet) {
        double difference = dataSet[row1][feature] - dataSet[row2][feature];
        sum += difference * difference;
    }
    // square root of sum above
    return sqrt(sum);
}

// Leave one out cross validation
double leaveOneOut(const vector<int>& featureSet) {
    int numCorrectlyClassified = 0;

    // outer loop for each instance
    for(int i = 0; i < dataSet.size(); i++) {
        double labelObjectToClassify = dataSet[i][0];

        double nearestNeighborDist = numeric_limits<double>::infinity();
        int nearestNeighborLoc = -1;
        
        // innter loop to comapare to other instances
        for(int k = 0; k < dataSet.size(); k++) {
            if(k != i) { // dont compare to self
                double distance = euclideanDistance(i, k, featureSet);

                // update nearest neighbor IF closer
                if(distance < nearestNeighborDist) {
                    nearestNeighborDist = distance;
                    nearestNeighborLoc = k;
                }
            }
        }

        double neighborLabel = dataSet[nearestNeighborLoc][0];

        if(labelObjectToClassify == neighborLabel) numCorrectlyClassified++; // amount of correct classifications
    }
    // accuracy calculation
    return (double)numCorrectlyClassified / dataSet.size();
}

/* ////////////////////////////////////////////////////////////////////

ALGORITHMS

//////////////////////////////////////////////////////////////////// */

void forwardSelection() {
    
}

void backwardElimination() {

}

/* ////////////////////////////////////////////////////////////////////

MAIN

//////////////////////////////////////////////////////////////////// */

int main() {\
    border();
    cout << "Feature Selection Algorithm" << endl << endl;

    string fileName;
    
    cout << "Enter dataset filename: ";
    cin >> fileName;
    cout << endl;

    if(!scanData(fileName)) {
        return 1;
    }
        
    cout << "This dataset has " << numFeatures << " features with " << dataSet.size() << " instances.\n";

    cout << "Choose algorithm: \n"
         << "(1) Forward Selection\n"
         << "(2) Backward Elimination\n";
    int choice = selectOptionHelper(1,2);
    
    if(choice == 1) {
        forwardSelection();
    }
    else {
        backwardElimination();
    }

    return 0;
}