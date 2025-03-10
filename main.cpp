#include <vector>
#include <iostream>
#include <cmath>
#include <queue>
#include <set>
#include <map>

using namespace std;

struct a_state {
    vector<vector<int>> cstate;
    int g_val;  // Cost from start node
    int heuristic_val;
    int f_val;  // f(n) = g(n) + h(n)

    // Constructor
    a_state(vector<vector<int>> s, int g, int h) {
        cstate = s;
        g_val = g;
        heuristic_val = h;
        f_val = g + h;
    }

    // Overload < operator for use in a set (for visited states)
    bool operator<(const a_state& other) const {
        return cstate < other.cstate;
    }
};
void print_setup(vector<vector<int>> userarr);
// Goal state
vector<vector<int>> goal = {{0,1,2},{3,4,5},{6,7,8}};

//  moves (up, left, right, down)
int movex[] = {-1, 0, 0, 1};
int movey[] = {0, -1, 1, 0};

// Function prototypes
int calcheruistic_val(vector<vector<int>> currboard);
pair<int, int> findzero(vector<vector<int>>& board);
pair<int, int> findGoalPosition(vector<vector<int>>& goalstate, int value);
void A_star(vector<vector<int>> start);

// Comparator for priority queue (min-heap)
struct comparestate {
    bool operator()(const a_state& s1, const a_state& s2) {
        return s1.f_val > s2.f_val; // Min-heap (lowest f_val has highest priority)
    }
};


pair<int, int> findzero(vector<vector<int>>& board) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == 0)
                return {i, j};
    return {-1, -1};
}

// search for location of x,y in goal pos
pair<int, int> findGoalPosition(vector<vector<int>>& goalstate, int value) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (goalstate[i][j] == value) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

// Calculate Manhattan distance heuristic
int calcheruistic_val(vector<vector<int>> currboard) {
    // here we are going to calculate the straight line heruistic


    // maybe we can sort the array
    //for(int i = 0; i < 9; i++) {
    //
    //  }
    // in order to calculate the herusitic we probably need to find the manhattan distance between the goal state

    int distance = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int value = currboard[i][j];
            if (value != 0) { // Ignore the empty tile
                pair<int, int> goalPos = findGoalPosition(goal, value);
                distance += abs(i - goalPos.first) + abs(j - goalPos.second);
            }
        }
    }
    return distance;
}


void A_star(vector<vector<int>> start) {
    priority_queue<a_state, vector<a_state>, comparestate> pq;

    set<vector<vector<int>>> visited;
    map<vector<vector<int>>, vector<vector<int>>> parent; // For path reconstruction

    // Initialize start state
    int h_val = calcheruistic_val(start);
    a_state initial_state(start, 0, h_val);
    pq.push(initial_state);
    int scounter = 0;
    while (!pq.empty()) {
        a_state current = pq.top();
        pq.pop();

        //If we found the correct goal
        if (current.cstate == goal) {
            cout << "Reached goal" << endl;
            //cout << "The goal cost is: " << current.g_val << endl;
            vector<vector<int>> temp = goal;
            while (parent.find(temp) != parent.end()) {
                print_setup(temp);
                cout <<"Heuristic val: " << calcheruistic_val(temp) << endl;
                temp = parent[temp];
            }
            print_setup(start);
            cout << "Number of states to reach goal: " << current.g_val<< endl;
            return;
        }

        // Mark current state as visited
        visited.insert(current.cstate);

        // Find the blank tile (zero)
        auto [x, y] = findzero(current.cstate);

        //this is where we expand the nodes
        for (int i = 0; i < 4; i++) {
            int newx = x + movex[i];
            int newy = y + movey[i];

           //going throuhg all of the moves
            if (newx >= 0 && newx < 3 && newy >= 0 && newy < 3) {
                vector<vector<int>> newBoard = current.cstate;
                swap(newBoard[x][y], newBoard[newx][newy]);

                if (visited.find(newBoard) == visited.end()) { // If not visited
                    int new_g = current.g_val + 1;
                    int new_h = calcheruistic_val(newBoard);
                    a_state new_state(newBoard, new_g, new_h);

                    pq.push(new_state);
                    parent[newBoard] = current.cstate; // Track path
                    //parent[new board] = for example {1,2,3,6,7,5,8,0,4} and then this get mapped to the new
                    //state which is supposedly better because it was selected from its hueristic value
                }
            }
        }
    }

    cout << "No solution found!" << endl;
}


void print_setup(vector<vector<int>> userarr) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << userarr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// main function
int main() {
    vector<vector<int>> board = {{1, 0, 2}, {3, 4, 8}, {7, 6, 5}};

    cout << "Initial state:" << endl;
    print_setup(board);

    A_star(board);

    return 0;
}