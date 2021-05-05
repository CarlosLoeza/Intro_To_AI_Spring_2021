//
//  Problem.cpp
//  Project1_Search_Algorithms
//
//
#include "Problem.hpp"
#include <iostream>
using namespace std;

// Checks to see if our zero index can move up
vector<int> Problem::move_up(vector<int> init, int zero_index){
    // checks to make sure we can move our zero up
    int top_spot_index = zero_index-3;
    // return vector with -1 to let us know we cannot perform this move
    vector<int> failed(1,-1);

    // if index > -1, is not ouf of bounds
    if(top_spot_index > -1){
        // value above our zero
        int &top_spot_value = init[top_spot_index];
        // swap zero and value above it
        init.at(zero_index) = top_spot_value;
        init.at(top_spot_index) = 0;
        return init;
    } else
        return failed;
}

// Checks to see if our zero index can move down
vector<int> Problem::move_down(vector<int> init, int zero_index){
    // checks to make sure we can move our zero up
    int down_spot_index = zero_index+3;
    // return vector with -1 to let us know we cannot perform this move
    vector<int> failed(1,-1);

    if(down_spot_index < 9){
        // value above our zero
        int &down_spot_value = init[down_spot_index];
        // swap zero and value above it
        init.at(zero_index) = down_spot_value;
        init.at(down_spot_index) = 0;
        return init;
    } else
        return failed;

}

// Checks to see if our zero index can move left
vector<int> Problem::move_left(vector<int> init, int zero_index){
    // holds the left spot index incase it is a valid move(move left)
    int left_spot_index = zero_index-1;
    // return vector with -1 to let us know we cannot perform this move
    vector<int> failed(1,-1);
    // Make sures we are not in the first column of puzzle
    if((zero_index != 0) && (zero_index != 3) && (zero_index != 6)){
        // value above our zero
        int &left_spot_value = init[left_spot_index];
        // swap zero and value above it
        init.at(zero_index) = left_spot_value;
        init.at(left_spot_index) = 0;
        return init;
    } else
        return failed;
}

// Checks to see if our zero index can move right
vector<int> Problem::move_right(vector<int> init, int zero_index){
    // holds the right spot index incase it is a valid move(move right)
    int right_spot_index = zero_index+1;
    // return vector with -1 to let us know we cannot perform this move
    vector<int> failed(1,-1);

    if(zero_index != 2 && zero_index != 5 && zero_index != 8){
        // value above our zero
        int &right_spot_value = init[right_spot_index];
        // swap zero and value above it
        init.at(zero_index) = right_spot_value;
        init.at(right_spot_index) = 0;
        return init;
    } else
        return failed;
}

// Make sure the move is valid. Ex: value on the top right corner
// can only move right and down
bool Problem::valid_state(vector<int> state){
    if(state.size() > 1)
        return true;
    else
        return false;
}



// Find the location of a given number in our puzzle and return index
int Problem::find_value(vector<int> init, int number){
    int position; // get position of
    auto it = find(init.begin(), init.end(), number);
    
    // If zero postion is located
    if (it != init.end())
        position = it - init.begin();
    else
        position = -1;
    
    return position;
}
