#ifndef TREE_SERACH_H
#define TREE_SERACH_H

#include "data_types.h"

#define PREDETERMINED_GOAL_STATE  1 // User will initially determine the goal state if it is true (1)
#define ACTIONS_NUMBER  6          // The number of all possible actions
#define MAX_SEARCHED_NODE 1000 // exit from the search process if it is exceeded  


#define NO_ACTION  0
#define TRUE       1
#define FALSE      0
#define FAILURE    NULL


State* Create_State();
void Print_State(const State *const state);
void Print_Action(const enum ACTIONS action);
int Result(const State *const parent_state, const enum ACTIONS action, Transition_Model *const trans_model);
float Compute_Heuristic_Function(const State *const state, const State *const goal); 
int Goal_Test(const State *const state, const State *const goal_state);

Node* First_GoalTest_Search_TREE(const enum METHODS method, Node *const root, State *const goal_state);
Node* First_InsertFrontier_Search_TREE(const enum METHODS method, Node *const root, State *const goal_state, float alpha); 
Node* DepthType_Search_TREE(const enum METHODS method, Node *const root, State *const goal_state, const int Max_Level);
Node* Child_Node(Node *const parent, const enum ACTIONS action); 
Queue* Start_Frontier(Node *const root);
int Empty(const Queue *const frontier);
Node* Pop(Queue **frontier);
void Insert_FIFO(Node *const child, Queue **frontier);
void Insert_LIFO(Node *const child, Queue **frontier);
void Insert_Priority_Queue_UniformSearch(Node *const child, Queue **frontier); 
void Insert_Priority_Queue_GreedySearch(Node *const child, Queue **frontier);
void Insert_Priority_Queue_A_Star(Node *const child, Queue **frontier); 
void Insert_Priority_Queue_GENERALIZED_A_Star(Node *const child, Queue **frontier, float alpha); 
void Print_Frontier(Queue *const frontier);
void Show_Solution_Path(Node *const goal);	
void Print_Node(const Node *const node);
int Level_of_Node(Node *const node);
void Clear_All_Branch(Node *node, int *Number_Allocated_Nodes);
void Clear_Single_Branch(Node *node, int *Number_Allocated_Nodes);
void Warning_Memory_Allocation();
int Compare_States(const State *const state1, const State *const state2);
Node* Frontier_search(Queue *const frontier, const State *const state);
void Remove_Node_From_Frontier(Node *const old_child, Queue **const frontier) ; 
int find_last_index(State *state,int pos);
int find_last(State *state,int pos);

#endif
