#include <vector>
#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

struct a_state {
    vector<vector<int>> cstate;
    int heuristic_val;

};
void expand(vector<a_state>);

//in order to move up we use -1 and keep the y the same
//going down we do +1 and the same y
// in order to move left we keep y the same and move x -1
// for the right side we add one

int movex[] = {-1,0,0,1};
int movey[] = {0,-1,1,0};

pair<int, int> findzero(vector<vector<int>> &board) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == 0)
                return {i, j};
    return {-1, -1}; //if we somehow end uo out of bounds dont continue
}



void print_setup(int arr[]) {
    //this prints out the array so that its easy to see
    int count = 0;
    for(int i = 0; i < 9; i++) {
        if(count < 3) {
            cout << arr[i] << " ";
            count++;
        }
        else {
            cout << endl;
            cout << arr[i] << " ";
            count = 1;
        }
    }
    cout << endl;
}
int calcheruistic_val(vector<vector<int>>);

int main() {
    //the zero represents the space
    vector<vector<int>> board = {{1,0,2}, {3,4,8},{7,6,5}};
    struct a_state nstate;
    nstate.cstate = board;

    //
    a_state sarray[1] = {nstate};


    // find the zeroes in the board
    auto [x,y] = findzero(board);



    cout << x << " " << y << endl;
    cout << board[1][1] << endl;
    // print_setup(arr);
    cout << "Hello world" << endl;

    return 0;
}

void expand(vector<a_state>& statearr, vector<vector<int>> currstate) {
    auto [x,y] = findzero(currstate);
    struct a_state holderstate;
    for(int i = 0; i < 4; i++) {
        int newx = x + movex[i];
        int newy = y + movey[i];

        if(newx >= 0 && newx < 3 && newy >= 0 && newy < 3) {
            vector<vector<int>> newBoard = currstate;
            swap(newBoard[x][y], newBoard[newx][newy]);
            holderstate.cstate = newBoard;
            holderstate.heuristic_val = calcheruistic_val(newBoard);
            statearr.push_back(holderstate);
        }

    }




}


int calcheruistic_val(vector<vector<int>>) {
    // here we are going to calculate the straight line heruistic

    // maybe we can sort the array
    for(int i = 0; i < 9; i++) {

    }

    struct a_state curr;
    curr.cstate = board;
    cout << "States have been copied over: "<< curr.cstate[0][0] << endl;
    return 0;
}




