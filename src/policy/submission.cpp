#include <cstdlib>
#include <algorithm>
#include <climits>
#include "../state/state.hpp"
#include "./submission.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Alphabeta::get_move(State *state, int depth){
    Move act;
    int A=INT_MIN;
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  int a=INT_MIN;
  for(auto &i: actions){
    int value;
    State* next = state->next_state(i); 
    value=alphabeta_func(next,A,INT_MAX,depth-1,state->player);
    if(value>a){
        a=value;
        act=i;
    }
    A=std::max(A,a);
  }
  return act;
}
int Alphabeta::alphabeta_func(State *state,int A,int B,int depth, int Player){
    if(!depth || !state->legal_actions.size()){
        return state->evaluate(Player);
    }
    int value;
    if(Player==state->player){  
        value=INT_MIN;
        //if(!state->legal_actions.size())
            state->get_legal_actions();
        for(auto &i:state->legal_actions){
            State* next = state->next_state(i); 
            value=std::max(value,alphabeta_func(next,A,B,depth-1,Player));
            A=std::max(A,value);
            if(A>=B) break;
        }
    }
    else{
        value=INT_MAX;
        //if(!state->legal_actions.size())
            state->get_legal_actions();
        for(auto &i:state->legal_actions){
            State* next = state->next_state(i); 
            value=std::min(value,alphabeta_func(next,A,B,depth-1,Player));
            B=std::min(B,value);
            if(A>=B) break;
        }
    }
    return value;
}