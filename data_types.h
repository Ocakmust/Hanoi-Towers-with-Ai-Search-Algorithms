#ifndef DATA_TYPES_H
#define DATA_TYPES_H


#define ROWS  3
#define COLUMNS 8

enum ACTIONS // All possible actions
{
	first_tosecond, first_tothird,
    second_tofirst, second_tothird,
    third_tofirst,third_tosecond
};

typedef struct State  
{
    int hanoi_towers[ROWS][COLUMNS];
    int disk_num;
    float h_n;   // Heuristic function
} State;


enum METHODS
{
	BreastFirstSearch = 1,   UniformCostSearch = 2,        DepthFirstSearch = 3,    
	DepthLimitedSearch= 4,   IterativeDeepeningSearch = 5, GreedySearch = 6,
    AStarSearch = 7, GeneralizedAStarSearch = 8  
};


typedef struct Transition_Model
{
    State new_state;
    float step_cost;
}Transition_Model;

typedef struct Node
{
    State state;
    float path_cost;
    enum ACTIONS action; 
    struct Node *parent;
    int Number_of_Child; 
}Node;

typedef struct Queue  
{
    Node *node;
    struct Queue *next;
}Queue;



#endif
