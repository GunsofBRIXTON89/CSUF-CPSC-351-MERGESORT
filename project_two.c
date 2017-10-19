// ============================================================================
// file: project_two.c
// ============================================================================
// Programmers: Jose Ordaz (CWID:) & Faraj Haddad (CWID:)
// Date: 10/19/2017
// Class: CPSC-351 "Operating System Concepts"
// Time: T/TH 2:30 P.M.
// Instructor: Dr. McCarthy, W.
// Project: Multithreaded Sorting Application
//
// Description: 
// A list of integers is divied into two smaller lists of equal siz. Two 
// seperate threads (which are which are dubbed "sorting threads") will sort
// each subset list Using a sorting Algorithm of our choice. Then a third 
// "merging" thread combines the two sublist into a single list.
//
// How to compile: gcc -Wall -std=c99 project_two.c -pthread -o project_two.exe
// ============================================================================
#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
 
#define MAX_ARRAY_LEN
int g_unsorted_array[MAX_ARRAY_LEN] = {7,12,19,3,18,4,3,6,15,8};
int g_sorted_array[MAX_ARRAY_LEN] = { 0 };

struct 	runner_struct {
	int starting_index;
};

// === Sorting_Runner =======================================================================
//
// 
// ==========================================================================================
void*	Sorting_Runner(void* param){
	struct runner_struct* arg_struct = (struct runner_struct*) param;
	int i = arg_struct->starting_index;
	int end_ELEM;
	if( i == 0){ end_ELEM = MAX_ARRAY_LEN/2;}
 	 else if(i > 0){end_ELEM = MAX_ARRAY_LEN;}
	int j = i;
	int n = end_ELEM - i;
	// bubble sorting 
	for (i; i < n-1; i++){         
       		for(j = i; j < n-i-1; j++){ 
          		if(g_unsorted_array[j] > g_unsorted_array[j+1]){
             	 		swap(&g_unsorted_array[j], &g_unsorted_array[j+1]);
			}
		}
	}
	
	printf("Done sorting Indexes [%d] through [%d] of g_unsorted_array[]\n", 
	       			    arg_struct -> starting_index, end_ELEM - 1);
	pthread_exit(0);

} // end of Sorting_Runner



// === Merging_Runner =======================================================================
//
// 
// ==========================================================================================
void*	Merging_Runner(/*void* param*/){
	//struct runner_struct* arg_struct = (struct runner_struct*) param;
	
	int i = 0, j= 0, k = 0;
	while(i <= element from u && j<= element from v){
		if(g_unsorted_array[i] < g_unsorted_array[j]){
			g_sorted_array[k] = g_unsorted_array[i]
			i++;
		}else{
			g_sorted_array[k] = g_unsorted_array[j];
			j++;
		}
		k++;
	}
	if(i>h){ // copy V[i] through V[m] to S[k] through S[h+m]
	}else{ // copy U[i] through U[h] to S[k] through S[h+m]
	
	}
} // end of Merging_Runner



// === main =================================================================================
// 
// ==========================================================================================
int	main(){

	void*   function_pointers[NUM_THREADS] = {CheckRows_runner,CheckColumns_runner,
						  CheckGrid_runner};
	pthread_t   t_ids[NUM_THREADS];
	// Launch Threads
	struct runner_struct arg[NUM_THREADS];

	for(int i = 0; i < NUM_THREADS; ++i){
		arg[i].case_sum = 0;
		pthread_attr_t attr;
		pthread_attr_init(&attr);   // get the default attributes
		pthread_create(&t_ids[i],&attr,function_pointers[i],&arg[i]); // create the thread

	}

	int sum = 0; // sum of all arg->case_sums

	// Wait untill each thread is done working
	for(int i = 0; i < NUM_THREADS; ++i){
		pthread_join(t_ids[i],NULL);    // wait for the thread to exit
		sum += arg[i].case_sum;
	}

	if( sum == 27){printf("The Sudoku Set is a valid set\n");}
	 else{ printf("The Sudoku Set is Not a valid set\n"); }

	return 0;


}// end of main
