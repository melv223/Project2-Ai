#include <vector>
#include <iostream>
#include <cmath>
#include <queue>

using namespace std;


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
int calcheruistic_val(int arr[]);

int main() {
    //the zero represents the space
    vector<vector<int>> board = {{1,0,2}, {3,4,8},{7,6,5}};
    auto [x,y] = findzero(board);
    cout << x << " " << y << endl;
    cout << board[1][1] << endl;
    // print_setup(arr);
    cout << "Hello world" << endl;

    return 0;
}

int calcheruistic_val(int arr[]) {
    // here we are going to calculate the straight line heruistic

    // maybe we can sort the array
    for(int i = 0; i < 9; i++) {

    }
    return 0;
}




