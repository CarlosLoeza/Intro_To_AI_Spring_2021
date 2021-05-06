////
////  main.cpp
////  Project1_Search_Algorithms
////
////
////
//
//
//
//



//
//  main.cpp
//  Project1_Search_Algorithms
//
//
//


#include "Problem.hpp"
#include <iostream>
#include <map>
#include <iterator>
#include <vector>
using namespace std;


// ** Global varialbe **
// Asks user for search algorithm.
// Used global since I created 1 struct to hold the three search algo. (Uniform, Misplaced, and Euclidean)
int SEARCH_SELECTED;



// This function will return the coordinates of where
queue<int> get_current_location(int spot){
    queue<int> location;
    // first row
    if(spot == 0){
        location.push(0);
        location.push(0);
    }else if(spot ==1){
        // format (y,x) since vector reads vertical first
        location.push(0);
        location.push(1);
    }else if(spot ==2){
        location.push(0);
        location.push(2);
    // second row
    }else if(spot ==3){
        location.push(1);
        location.push(0);
    }else if(spot ==4){
        location.push(1);
        location.push(1);
    }else if(spot ==5){
        location.push(1);
        location.push(2);
    // third row
    }else if(spot ==6){
        location.push(2);
        location.push(0);
    }else if(spot ==7){
        location.push(2);
        location.push(1);
    } else {
        location.push(2);
        location.push(2);
    }
    return location;
}

queue<int> get_original_location(int number){
    queue<int> location;
    // first row
    if(number == 1){
        location.push(0);
        location.push(0);
    }else if(number ==2){
        // format (y,x) since vector reads vertical first
        location.push(0);
        location.push(1);
    }else if(number ==3){
        location.push(0);
        location.push(2);
    // second row
    }else if(number ==4){
        location.push(1);
        location.push(0);
    }else if(number ==5){
        location.push(1);
        location.push(1);
    }else if(number ==6){
        location.push(1);
        location.push(2);
    // third row
    }else if(number ==7){
        location.push(2);
        location.push(0);
    }else if(number ==8){
        location.push(2);
        location.push(1);
    } else if(number == 0){
        location.push(2);
        location.push(2);
    }
    return location;
}


// Find index of our number
int find_value(vector<int> init, int number){
    int position; // get position of
    auto it = find(init.begin(), init.end(), number);
    
    // If zero postion is located
    if (it != init.end())
        position = it - init.begin();
    else
        position = -1;
    
    return position;
}


// Determines the moves we need to make by doing final_position - initial position
// Ex: if #8 is at the top right position (0,0) we need to move 2 steps down and 2 steps right (2,2)
queue<int> get_difference(queue<int> init_postion, queue<int> final_position){
    int init_x ;
    int init_y ;
    int final_x;
    int final_y;
    int result_x;
    int result_y;
    
    init_y = init_postion.front();
    init_postion.pop();
    init_x = init_postion.front();
    
    final_y = final_position.front();
    final_position.pop();
    final_x =final_position.front();

    queue<int> result_coordinate;
    
    result_coordinate.push(final_y-init_y);
    result_coordinate.push(final_x-init_x);

    return result_coordinate;
}

// Count the number of moves we need to make in the x and y coordinates
// Use absolute value since we only care about the moves and not direction
int count_moves(int y, int x){
    return(abs(y)+abs(x));
    
}

// ******
int euclidean_cost(vector<int> init){
    int total_cost = 0;
    for(int i=1; i<9;i++){
        int value_index = find_value(init, init[i]);
        queue<int> current_spot = get_current_location(value_index);
        queue<int> intended = get_original_location(init[i]);
        // get difference from current index and inteded index (final - initial)
        queue<int> diff = get_difference(current_spot, intended);
        int diff_y = diff.front();
        diff.pop();
        int diff_x = diff.front();
        // perform vertical moves
        ///cout << count_moves(diff_y, diff_x);
        total_cost += count_moves(diff_y, diff_x);
    }
    return total_cost;
}


// Get h(n) of puzzle
int misplaced_tiles(vector<int> state){
    int cur_index; // get position of specific number (1-8)
    int goal_index =0; // goal index
    int count=0; // # of misplaced tiles
   // vector<int> new_temp;
    

    // find misplaced tiles (1-8) since we don't count 0 as misplaced
    for(int i = 1; i<9; i++){
        // iterator from beginning to end, looking for value i
        auto it = find(state.begin(), state.end(), i);
        
        // if number found
        if (it != state.end()){
            // get current index of number we are looking for (1-8)
            cur_index = distance(state.begin(), it);
            int value = state[cur_index]; // get value at index i to see if it is in the correct spot
            goal_index = value-1; // goal index is always one less (ex: number 1 goes at index 0)

            
            // if not in the correct index
            // ex: value 1 should be at index 0
            if(cur_index != goal_index){
                count++;
            }
        }
    }
    return count;
}




struct comp
{
    bool operator()(vector<int> a, vector<int> b)
    {
        if(SEARCH_SELECTED == 2)
            return (euclidean_cost(a)) > (euclidean_cost(b));
        else if(SEARCH_SELECTED == 3)
            return (misplaced_tiles(a)) > (misplaced_tiles(b));
        else
            return (-1);
    }
};



// check if state is in frontier
bool inFrontier(priority_queue<vector<int>, vector<vector<int>>, comp> pq, vector<int> pos_state){
    vector<int> cur_pq_state;
    vector<int> cur_pos_state;
    vector<int> hold_pos_states = pos_state;
    bool found = false;

    //cout << "in frontier\n";
    // while priority queue is not empty
    while(!pq.empty() && !found){
        // get the values of the
        for(int i = 0; i<pq.top().size(); i++){
            cur_pq_state.push_back(pq.top()[i]);
            
        }

        
        if(cur_pq_state == pos_state)
            found = true;
        pq.pop();
    
        // if pq != possible state
        // load pos_states again before we loop since we popped them off
        hold_pos_states = pos_state;
    }

    return found;
}

bool inExplored(map<vector<int>, int> explored, vector<int> pos_state){
    vector<int> cur_explored_state;
    vector<int> cur_pos_state;
    vector<int> hold_map_vector;
    bool found = false;

    for(auto it = explored.find(pos_state); it!= explored.end(); it++){
        found = true;
    }

    return found;
}

//




// Driver code
int main()
{
    
    

    
    map<vector<int>, int> states;   // possible states
    map<vector<int>, int> explored;     // explored state
    // Our initial state
    vector<int> init;
    // goal state
    vector<int> goal = {1,2,3,4,5,6,7,8,0};
    //  default vector
    vector<int> def = {1,0,3,4,2,6,7,5,8};
    // This vector will hold the results when we perform move_up,move_down,etc.
    vector<int> temp;
    // Holds the best node/path based on score
    vector<int> cur_best;
    // possible paths from parent state
    vector<vector<int>> pos_states;
    vector<int> cur_pos_state;
    // cost =  h(n)
    int cost;
    // zero location
    int zero_index;
    // place our numbers in the first,second,and third position in a row
    int first;
    int second;
    int third;
    // vectors hold the result state after a move is applied (ex:move_left)
    vector<int> m_left;
    vector<int> m_right;
    vector<int> m_up;
    vector<int> m_down;
    // checks if our puzzle matches the goal state
    bool solutionFound = false;
    // depth = g(n)
    long depth = 0;
    // pq = frontier
    priority_queue<vector<int>, vector<vector<int>>, comp> pq;
    // user response to default puzzle or custom
    int response;
    // puzzle values from user
    int puzzle_values;
    
    Problem myPuzzle;
    
    // init state
    init.push_back(0);
    init.push_back(1);
    init.push_back(2);
    init.push_back(4);
    init.push_back(5);
    init.push_back(3);
    init.push_back(7);
    init.push_back(8);
    init.push_back(6);

    
   
    cout << "Welcome to ________ 8 puzzle solver \n";
    cout << "Type 1 to select default puzzle or type 2 to enter your own \n";
    cout << "Default (1): \n";
    cout << "1 0 3 \n";
    cout << "4 2 6 \n";
    cout << "7 5 8 \n";
    cout << endl;
    cin >> response;
    
    if(response ==1)
        init = def; // initial vector is default
    else{
        cout << "Enter numbers ONLY 0-8. System does not check if value is out of bounds \n";
        for(int i = 0; i<3; i++){
            for(int j =0; j<3; j++){
                cout << "Enter row " << i << ", column: " << j << " value";
                cin >> puzzle_values;
                init.push_back(puzzle_values);
                
            }
        }
        
    }
    
    cout << "Enter your choice of algorithm \n";
    cout << "2. A* with Misplaced Tile Heuristic \n";
    cout << "3. A* with Eucledian distance heuristic \n";
    cin >> SEARCH_SELECTED;
        
    
        
    
    
    

    // main "driver" code
    // push our initial state to frontier
    pq.push(init);
    // loop if frontier is not empty OR solution not found
    while(pq.size() != 0 && !solutionFound){
        // top value in our priority queue
        vector<int> temp = pq.top();
        cout << "---------------------------" << endl;
        cout << "State" << endl;
        // print top value
        for(int i = 0; i<pq.top().size(); i++){
            cout << pq.top()[i] << " ";
            // if we reach the end of row, start a new line
            // ex: 1,2,3 newline
            //     3,4,5 newline etc.
            if(i == 2 || i == 5)
                cout << endl;
        }
        cout << endl;
        // pop top value in our priority queue
        pq.pop();
        cout << "g(n): " << depth << endl;
        
        
        // get cost based on the type of algorithm we are using
        // ex: misplaced tiles or euclidean
        if(SEARCH_SELECTED == 2)
            cost = misplaced_tiles(temp);
        else
            cost = euclidean_cost(temp);
            
            
        
        
        //cost = misplaced_tiles(temp);
        cout << "h(n): " << cost << endl;
        cout << "Total cost: " << cost+depth << endl;

        if(temp == goal){
            cout << "yes goal found" << endl;
            solutionFound = true;

        // temp state != goal state
        } else if(!solutionFound) {
            explored.insert({temp, cost});

            // first find zero location
            zero_index = myPuzzle.find_value(temp, 0);
            // expand the chosen temp's children aka possible moves

            // move_up state
            m_up = myPuzzle.move_up(temp, zero_index);
            // check if this is a valid move
            if(myPuzzle.valid_state(m_up))
                pos_states.push_back(m_up);

            // move_down state
            m_down= myPuzzle.move_down(temp, zero_index);
            // check if this is a valid move
            if(myPuzzle.valid_state(m_down))
                pos_states.push_back(m_down);

            // move_left state
            m_left= myPuzzle.move_left(temp, zero_index);
            // check if this is a valid move
            if(myPuzzle.valid_state(m_left))
                pos_states.push_back(m_left);

            // move_right state
            m_right= myPuzzle.move_right(temp, zero_index);
            // check if this is a valid move
            if(myPuzzle.valid_state(m_right))
                pos_states.push_back(m_right);

            
            // check if pos_states(possible states) is in the frontier or explored
            while(!(pos_states.empty())){
                
                //cout << "Made it in 2 " << endl;
                for(int i = 0; i<pos_states.front().size(); i++){
                    cur_pos_state.push_back(pos_states.back()[i]);
                }
                
                // possible state is not in frontier
                if(!(inFrontier(pq,cur_pos_state))){
                    // possible state is not in explored states
                    if(!(inExplored(explored, cur_pos_state))){
                        // push to priority queue
                        pq.push(cur_pos_state);
                    }
                }
                // pop the the possible state we just checked in order to check the next possible state
                pos_states.pop_back();
                // clear to use again. If we don't clear, values will be carried
                // to the next iteration.
                cur_pos_state = {};
            }
        }
        depth++;
    }
     
    return 0;
}

