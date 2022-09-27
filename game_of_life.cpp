// Nabira Ahmad
// This is Conway's Game of Life
// Rules:
/* The world consists of a grid of cells. Cells are either alive or dead.
   Each cell may have up to 8 neighbors, i.e. diagonals count.
   But a corner cell will only have three neighbors
   and a border cell that is not a corner will have five.
   A living cell with two or three neighboring living cells survives into the
   next generation. A living cell with fewer than two living neighbors dies of
   loneliness and a living cell with more than three living neighbors will die
   from overcrowding. Each empty/dead cell that has exactly three living neighbors
   --no more, no fewer-- comes to life in the next generation. */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main () {
    // opening the file
    
    ifstream world("life.txt");
    
    if (!world) {                     // exception handling
        cerr << "failed to open life.txt";
        exit(1);
    } else {
        cout << "life.txt successfully opened" << endl;
    }
    
    vector<string> worldVector;       // creating a vector of strings (2D world)
    string line;
    
    while ((getline(world, line))) {  // pushing strings into vector
        worldVector.push_back(line);
    }
    
    cout << "Initial World\n";        // printing the initial world
    for (size_t i = 0; i < worldVector.size(); ++i) {
        cout << worldVector[i] << endl;
    }
    
    cout << "===========================\n";
    
    for (int gen = 1; gen < 11; ++gen) { // loop from gen1-> gen10
        vector<string> newWorld;
        for (size_t row = 1; row < worldVector.size() + 1; ++row) {
            string currRow = worldVector[row - 1];
            string newRow = "";
            for (size_t col = 1; col < currRow.size() + 1; ++col) {
                char currCell = currRow[col - 1];
                int aliveNei = 0;
                
                int rowind = row - 1;
                int colind = col - 1;
                
                if (row > 1) {
                    if (worldVector[rowind - 1][colind] == '*') {
                        ++aliveNei;
                    }
                    if (col > 1) {
                        if (worldVector[rowind - 1][colind - 1] == '*') {
                            ++aliveNei;
                        }
                    }
                    if (col < 20) {
                        if (worldVector[rowind - 1][colind + 1] == '*') {
                            ++aliveNei;
                        }
                    }
                }
                
                if (col > 1) {
                    if (worldVector[rowind][colind - 1] == '*') {
                        ++aliveNei;
                    }
                }
                
                if (col < 20) {
                    if (worldVector[rowind][colind + 1] == '*') {
                        ++aliveNei;
                    }
                }
                
                if (row < 8) {
                    if (worldVector[rowind + 1][colind] == '*') {
                        ++aliveNei;
                    }
                    if (col > 1) {
                        if (worldVector[rowind + 1][colind - 1] == '*') {
                            ++aliveNei;
                        }
                    }
                    if (col < 20) {
                        if (worldVector[rowind + 1][colind + 1 ] == '*') {
                            ++aliveNei;
                        }
                    }
                }
                char newState;
                if (currCell == '*') {
                    newState = '*';
                    if (aliveNei < 2 || aliveNei > 3) {
                        newState = '-';
                    }
                } else {
                    newState = '-';
                    if (aliveNei == 3) {
                        newState = '*';
                    }
                }
                newRow = newRow + newState;
            }
            newWorld.push_back(newRow);
        }
        {
            cout << "Generation: " << gen << endl;
            for (int i = 0; i < worldVector.size(); i++) {
                for (int j = 0; j < worldVector[i].size(); j++) {
                    cout << worldVector[i][j];
                }
                cout << endl;
            }
            worldVector = newWorld;
            cout << "===========================\n";
        }
        world.close();
    }
}
