/* 
    These functions are compulsory for search algorithms but they are specific
    to problems. More clearly, you must must update their blocks but do not change
    their input and output parameters.
    
    Also, you can add new functions at the end of file by declaring them in GRAPH_SEARCH.h
*/

#include "GRAPH_SEARCH.h"
#include "data_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//______________________________________________________________________________
State* Create_State()
{
	State *state = (State*)malloc(sizeof(State));
	
    if(state==NULL)
    	Warning_Memory_Allocation(); 
    	
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            state->hanoi_towers[i][j] = 0; // Diziyi başlangıçta boşalt
        }
    }
   
    int temp_disk_num;
    int disk_num;
    printf("How many disks do you want to use (3, 5, or 7): ");
    scanf("%d", &disk_num);

    state->disk_num = disk_num;
    temp_disk_num=disk_num;
    
   	int tower;
    do { 
        printf("Which tower (1, 2, or 3): ");
        scanf("%d", &tower);
		state->hanoi_towers[tower-1][find_last_index(state,tower-1)+1]=temp_disk_num;
        temp_disk_num--;
    } while (temp_disk_num > 0);
    
	       
	Print_State(state);
	       
    return state;    
}

//______________________________________________________________________________
void Print_State(const State *const state) {
    printf("Hanoi Towers State:\n");
    for (int i = 0; i < 3; i++) {
        printf("Tower %d:", i + 1);
        for (int j = 0; j < 8; j++) {
            printf(" %d", state->hanoi_towers[i][j]);
        }
        printf("\n");
    }
}

//______________________________________________________________________________
void Print_Action(const enum ACTIONS action)
{
	switch(action)
	{
		case  first_tosecond:   
			printf("1 to 2 "); break;
		case  first_tothird:   
			printf("1 to 3"); break;
		case  second_tofirst:   
			printf("2 to 1"); break;
		case  second_tothird:   
			printf("2 to 3"); break;
		case  third_tofirst:   
			printf("3 to 1"); break;
		case  third_tosecond:   
			printf("3 to 2"); break;
	}
}
//______________________________________________________________________________
int Result(const State *const parent_state, const enum ACTIONS action, Transition_Model *const trans_model) {
    State new_state;
    int k,l;
    int taken_from, put_into;
    for (k = 0; k < 3; k++) {
        for (l = 0; l < 8; l++) {
            new_state.hanoi_towers[k][l] = parent_state->hanoi_towers[k][l];
        }
    }

    switch(action) {
        case  first_tosecond:   
			taken_from = 0; put_into = 1; break;
		case  first_tothird:   
			taken_from = 0; put_into = 2; break;
		case  second_tofirst:   
			taken_from = 1; put_into = 0; break;
		case  second_tothird:   
			taken_from = 1; put_into = 2; break;
		case  third_tofirst:   
			taken_from = 2; put_into = 0; break;
		case  third_tosecond:   
			taken_from = 2; put_into = 1; break;
		default:
			return FALSE; // Geçersiz action değeri
	}

    // Hedef kule boş değilse ve taşınacak disk hedef kuledeki diskten büyükse veya kaynak kule boşsa
    if ((find_last(&new_state, put_into) != 0 && 
        (find_last(&new_state, taken_from) > find_last(&new_state, put_into) || find_last_index(&new_state, taken_from) == -1)) ||
        // Hedef kule boşsa ve kaynak kule de boşsa
        (find_last(&new_state, put_into) == 0 && find_last_index(&new_state, taken_from) == -1)) {
        return FALSE;
    }

    // Geçerli hareketi uygula
    new_state.hanoi_towers[put_into][find_last_index(&new_state, put_into) + 1] = 
        new_state.hanoi_towers[taken_from][find_last_index(&new_state, taken_from)];
    new_state.hanoi_towers[taken_from][find_last_index(&new_state, taken_from)] = 0;

    trans_model->new_state = new_state;
    trans_model->step_cost = abs(taken_from - put_into) * find_last(&new_state, put_into);
    return TRUE;
}

//______________________________________________________________________________
float Compute_Heuristic_Function(const State *const state, const State *const goal) {
  float heuristic = 0;
	float tower_counter;
  for (int i = 0; i < 3; i++) {
  	tower_counter=0;
  	
    for (int j = 0; j < 8; j++) {
      int disk = state->hanoi_towers[i][j];
      if (disk != 0 && i != 2) { // Disk hedef kulede değilse
      	tower_counter++;
      }
    }
    float distance = abs(i - 2); // Hedef kuleye olan mesafe
    heuristic += tower_counter * distance; // Mesafe ve ağırlığı çarp
  }

  return heuristic;
}
//_______________ Update if your goal state is not determined initially ___________________________________
int Goal_Test(const State *const state, const State *const goal_state)
{
	if(PREDETERMINED_GOAL_STATE)	
		return Compare_States(state, goal_state); 
	else
		return 1;
}

// ==================== WRITE YOUR OPTIONAL FUNCTIONS (IF REQUIRED) ==========================

int find_last_index(State *state,int pos) {
    int counter = 0;
    for (int i = 0; state->hanoi_towers[pos][i] != 0  && i<8; i++) {
        counter++;
    }
    return counter-1;
}

int find_last(State *state,int pos) {
    int counter = 0;
    for (int i = 0; state->hanoi_towers[pos][i] != 0 && i<8 ; i++) {
        counter++;
    }
    if(counter>0){
    	return state->hanoi_towers[pos][counter-1];
	}
	else{
		return 0;
	}
    
}
