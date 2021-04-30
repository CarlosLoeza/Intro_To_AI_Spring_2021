//
//  Problem.hpp
//  Project1_Search_Algorithms
//
//  Created by Carlos Loeza on 4/30/21.
//

#ifndef Problem_hpp
#define Problem_hpp

#include <stdio.h>


class Problem {
public:
    // variables
    int init_state[3][3] = {{1,2,3},{4,5,6},{7,0,8}};
    int goal_state[3][3] = {{1,2,3}, {4,5,6},{7,8,0}};
    // methods
    int move_up();
    int move_down();
    int move_left();
    int move_right();
    
    
};
#endif /* Problem_hpp */
