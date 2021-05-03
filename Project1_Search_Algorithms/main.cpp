//
//  main.cpp
//  Project1_Search_Algorithms
//
//  Created by Carlos Loeza on 4/30/21.
//

#include <iostream>
#include <deque>
#include <vector>
#include "Problem.hpp"
using namespace std;


// Get h(n) of puzzle
int puzzle_cost(vector<int> temp){
    int cur_index; // get position of specific number (1-8)
    int goal_index; // goal index
    int count=0; // # of misplaced tiles
    vector<int> new_temp;
    

    // find misplaced tiles (1-8) since we don't count 0 as misplaced
    for(int i = 1; i<9; i++){
        // iterator from beginning to end, looking for value i
        auto it = find(new_temp.begin(), new_temp.end(), i);
        // if number found
        if (it != new_temp.end()){
            cur_index = it - new_temp.begin(); // index for value i (i = 1-8)
            int &value = new_temp[cur_index]; // value at index i
            goal_index = value-1; // goal index is always one less (ex: number 1 goes at index 0)
            // Correct spot
            if(cur_index != goal_index){
                count++;
            }
        }
    }

    return count;
}

bool valid_state(vector<int> state){
    if(state.size() > 1)
        return true;
    else
        return false;

}

// Comparison object to be used to order the heap
struct comp
{
    bool operator()(vector<int> a, vector<int> b)
    {
        return (puzzle_cost(a)) > (puzzle_cost(b));
    }
};

// check if state is in frontier
bool inFrontier(priority_queue<vector<int>, vector<vector<int>>, comp> pq, vector<vector<int>> pos_states){
    vector<int> cur_pq_state;
    vector<int> cur_pos_state;

    while(!(pq.empty())){

        for(int i = 0; i<pq.top().size(); i++){
            cur_pq_state.push_back(pq.top()[i]);
            cur_pos_state.push_back(pos_states.front()[i]);
        }
        if(cur_pq_state == cur_pos_state)
            return true;
        else
            pq.pop();
    }

    return false;
}

bool inExplored(vector<vector<int>> explored, vector<vector<int>> pos_states){
    vector<int> cur_explored_state;
    vector<int> cur_pos_state;
    vector<vector<int>> temp_explored = explored; // use temp to hold our explored states so we can pop recover popped states

    cout << "explored size: " << explored.size() << endl;
    cout << "pos_state_size: "<< pos_states.size() << endl;;
    // loop until there is no more possible states (move_up, move_down,etc.) left
    while(!(pos_states.empty())){
        cur_pos_state = {};
        //temp_explored = explored; // assign our explored states to temp_explored
        // for loop to get current possible state (move_up, move_down,etc.)
        cout << "cur_pos_state: ";
        for(int i = 0; i<pos_states.front().size(); i++){
            cout << pos_states.front()[i];
            cur_pos_state.push_back(pos_states.front()[i]);
        }
        cout << endl;
            // for loop to get the current explored state
        while(!temp_explored.empty()){
            cur_explored_state = {}; // clear
            cout << "cur_explore state: ";
            for(int j =0; j<temp_explored.front().size(); j++){
                cout << temp_explored.front()[j];
                cur_explored_state.push_back(temp_explored.front()[j]);
            }
            cout << endl;
            if(cur_explored_state == cur_pos_state)
                return true;
            else
                temp_explored.pop_back();

        }
        cout << "out" << endl;
        pos_states.pop_back();
    }

    while(!(explored.empty())){

        for(int i = 0; i<explored.front().size(); i++){
            cur_explored_state.push_back(explored.front()[i]);
            cur_pos_state.push_back(pos_states.front()[i]);
        }
        if(cur_explored_state == cur_pos_state)
            return true;
        else
            explored.pop_back();
    }

    return false;
}



int main() {
    // Our initial state
    vector<int> init;
    // goal state
    vector<int> goal = {1,2,3,4,5,6,7,8,0};
    // This vector will hold the results when we perform move_up,move_down,etc.
    vector<int> temp;
    // Holds the best node/path based on score
    vector<int> cur_best;
    // possible paths from parent state
    vector<vector<int>> pos_states;
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
    // priority queue aka frontier
    priority_queue<vector<int>, vector<vector<int>>, comp> pq;
    // explored states
    vector<vector<int>> explored = {};
    // checks if our puzzle matches the goal state
    bool solutionFound = false;
    
    Problem myPuzzle;
    

    // init state
    init.push_back(1);
    init.push_back(2);
    init.push_back(3);
    init.push_back(4);
    init.push_back(5);
    init.push_back(6);
    init.push_back(7);
    init.push_back(0);
    init.push_back(8);


    // main "driver" code
    // push our initial state to frontier
    pq.push(init);
    // loop if frontier is not empty OR solution not found
    while(pq.size() != 0 && !solutionFound){

        vector<int> temp = pq.top();
        cout << "---------------------------" << endl;
        cout << "top" << endl;
        // print top
        for(int i = 0; i<pq.top().size(); i++){
            cout << pq.top()[i];
            if(i == 2 || i == 5)
                cout << endl;
        }
    

        cout << endl;

        pq.pop();
        // if temp state == goal state
        if(temp == goal){
            cout << "yes goal found" << endl;
            solutionFound = true;

        // temp state != goal state
        } else if(!solutionFound) {
            explored.push_back(temp);
            // if explored is empty push top value of priority queue
//            if(explored.size() == 0 && pq.size() == 0){
//                cout << "explored size 0";
//                explored.push_back(temp);
//            }

            // first find zero location
            zero_index = myPuzzle.find_zero(temp);
            // expand the chosen temp's children aka possible moves

            // move_up state
            m_up = myPuzzle.move_up(temp, zero_index);
            // check if this is a valid move
            if(valid_state(m_up))
                pos_states.push_back(m_up);

            // move_down state
            m_down= myPuzzle.move_down(temp, zero_index);
            // check if this is a valid move
            if(valid_state(m_down))
                pos_states.push_back(m_down);

            // move_left state
            m_left= myPuzzle.move_left(temp, zero_index);
            // check if this is a valid move
            if(valid_state(m_left))
                pos_states.push_back(m_left);

            // move_right state
            m_right= myPuzzle.move_right(temp, zero_index);
            // check if this is a valid move
            if(valid_state(m_right))
                pos_states.push_back(m_right);

            // check if pos_states is in frontier or explored
            while(!(pos_states.empty())){
                // not in frontier
                if(!(inFrontier(pq,pos_states))){
                    // not in explored
                    cout << "not in frontier: ";
                    for(int i = 0; i<pos_states.front().size(); i++){
                        cout << pos_states.back()[i];
                    }
                    cout << endl;
                    if(!(inExplored(explored, pos_states))){
                        cout << "not in explored: ";
                        for(int i = 0; i<pos_states.front().size(); i++){
                            cout << pos_states.back()[i];
                        }
                        pq.push(pos_states.back());
                        //cout << endl;
                    }
                } else {
                    cout << "yes in frontier or explored: ";
                    for(int i = 0; i<pos_states.front().size(); i++){
                        cout << pos_states.front()[i];
                    }
                    cout << endl;
                }
                cout << endl;
                cout << "** explored: " << explored.size() << endl;
                //cout << "pos size before pop: " << pos_states.size() <<  endl;
                pos_states.pop_back();
                //cout << "pos size after pop: " << pos_states.size() <<  endl;
            }
            cout << "outside while" << endl;
        }
    }

    
    return 0;
}

