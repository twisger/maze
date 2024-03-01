#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <set>

using namespace std;
using Point = pair<int, int>;

class MazeGenerator {
private:
    int rows;
    int cols;
    vector<bool> visited;
    vector<vector<bool>> connected;
    //! convert point to index
    int point2Index(Point p) {
        return p.first * cols + p.second;
    }
    //! convert index to point
    Point index2Point(int i) {
        return make_pair(i / cols, i % cols);
    }
    //! get all neighbors of the point
    vector<Point> getNeighbors(Point point) {
        int i = point.first;
        int j = point.second;
        vector<Point> neighbors;

        // add all neighbors
        if (i + 1 < rows) neighbors.push_back({i + 1, j});
        if (i - 1 >= 0) neighbors.push_back({i - 1, j});
        if (j + 1 < cols) neighbors.push_back({i, j + 1});
        if (j - 1 >= 0) neighbors.push_back({i, j - 1});

        random_device rd;
        mt19937 g(rd());
        shuffle(neighbors.begin(), neighbors.end(), g);

        return neighbors;
    }

public:
    MazeGenerator(int numRows, int numCols) : rows(numRows), cols(numCols) {
        visited.resize(rows * cols, false);
        connected.resize(rows * cols, vector<bool>(rows * cols, false));
    }
    //! check if point a and point b is connected in maze
    bool isConnected(Point a, Point b) {
        if (a.first < 0 || a.first >= rows || b.first < 0 || b.first >= rows) {
            return false;
        }
        if (b.second < 0 || b.second >= cols || b.second < 0 || b.second >= cols) {
            return false;
        }
        return connected[point2Index(a)][point2Index(b)];
    }
    //! generate maze via dfs algorthm
    void generateMaze(Point start) {
        int index = point2Index(start);
        visited[index] = true;
        vector<Point> neighbors = getNeighbors(start);
        for (const auto& neighbor : neighbors) {
            int neighborIndex = point2Index(neighbor);
            if (!visited[neighborIndex]) {
                connected[index][neighborIndex] = true;
                connected[neighborIndex][index] = true;
                generateMaze(neighbor);
            }
        }
    }
    //! print maze in command line
    void print() {
        int num_cols = cols;
        int num_rows = rows;
        for (int i = 0; i < num_cols; ++i) {
            cout << "+---";
        }
        cout << "+" << endl;

        for (int i = 0; i < num_rows; ++i) {
            string row_wall = "|";
            string col_wall = "+";
            for (int j = 0; j < num_cols; ++j) {
                if (j == num_cols - 1 || !isConnected(make_pair(i,j), make_pair(i, j+1))) {
                    row_wall += "   |";
                } else {
                    row_wall += "    ";
                }
                if (i == num_rows - 1 || !isConnected(make_pair(i,j), make_pair(i+1, j))) {
                    col_wall += "---+";
                } else {
                    col_wall += "   +";
                }
            }
            cout << row_wall << endl;
            cout << col_wall << endl;
        }
    }
};

// int main() {
//     MazeGenerator maze(15);
//     maze.generateMaze({0, 0});
//     maze.print();
//     return 0;
// }



