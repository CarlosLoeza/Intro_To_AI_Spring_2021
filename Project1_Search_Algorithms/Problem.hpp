//
//  Problem.hpp
//  Project1_Search_Algorithms
//
//  Created by Carlos Loeza on 4/30/21.
//


#ifndef Problem_hpp
#define Problem_hpp

#include <stdio.h>
#include <deque>
#include <vector>
#include <queue>
#include <map>
#include <iterator>

using namespace std;


class Problem {
public:
    // * variables *
    int zero_index;
    
    // * methods *
    // purpose of each method is placed above the function in Problem.cpp
    vector<int> move_up(vector<int> init, int zero_index);
    vector<int> move_down(vector<int> init, int zero_index);
    vector<int> move_left(vector<int> init, int zero_index);
    vector<int> move_right(vector<int> init, int zero_index);
    bool valid_state(vector<int> state);
    int find_value(vector<int> init, int number);
    int get_cost(vector<int>);
    
};


#endif /* Problem_hpp */


