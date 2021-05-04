//
//  Problem.cpp
//  Project1_Search_Algorithms
//
//  Created by Carlos Loeza on 4/30/21.
//

#include "Problem.hpp"
#include <iostream>
using namespace std;

vector<int> Problem::move_up(vector<int> init, int zero_index){
    // checks to make sure we can move our zero up
    int top_spot_index = zero_index-3;
    // return vector with -1 to let us know we cannot perform this move
    vector<int> failed(1,-1);


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




// Check if possible states(moves) are in explored
vector<vector<int>> Problem::unique_states(vector<vector<int>> explored, vector<vector<int>> pos_states){
    vector<int> temp_possible = {};
    vector<vector<int>> t_explored;
    vector<vector<int>> new_states;
    bool found = false;
    
    t_explored = explored;
    
    ///cout << "temp_possible: ";
    for(int i = 0; i<pos_states.front().size(); i++){
        temp_possible.push_back(pos_states.back()[i]);
        ///cout << pos_states.back()[i];
        
    }
    ///cout << endl;
    pos_states.pop_back();
    
    while(!(t_explored.empty())){
        vector<int> temp_explored = {};
        ///cout << "temp_explored: ";
        for(int i =0; i<explored.front().size(); i++){
            temp_explored.push_back(t_explored.back()[i]);
            ///cout << t_explored.back()[i];
        }
        if(temp_explored == temp_possible)
            found = true;
        ///cout << endl;
        t_explored.pop_back();
    }
    if(!found)
        new_states.push_back(temp_possible);
    ///cout << endl;
    
    return new_states;

}



// Find the zero
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

