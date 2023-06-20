#include <cstdlib>
#include <algorithm>
#include <climits>
#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
    Move act;
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  int a=INT_MIN;
  for(auto &i: actions){
    int value;
    State* next = state->next_state(i); 
    value=minimax_func(next,depth-1,state->player);
    if(value>a){
        a=value;
        act=i;
    }
  }
    return act;
}
int Minimax::minimax_func(State *state,int depth, int Player){
    if(!depth || !state->legal_actions.size()){
        return state->evaluate(Player);
    }
    int value;
    if(Player==state->player){
        value=INT_MIN;
        if(!state->legal_actions.size())
            state->get_legal_actions();
        for(auto &i:state->legal_actions){
            State* next = state->next_state(i); 
            value=std::max(value,minimax_func(next,depth-1,Player));
        }
    }
    else{
        value=INT_MAX;
        if(!state->legal_actions.size())
            state->get_legal_actions();
        for(auto &i:state->legal_actions){
            State* next = state->next_state(i); 
            value=std::min(value,minimax_func(next,depth-1,Player));
        }
    }
    return value;
}