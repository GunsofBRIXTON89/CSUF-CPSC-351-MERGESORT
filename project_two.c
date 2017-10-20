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
// A list of integers is divided into two smaller lists of equal siz. Two 
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

#define NUM_SORT_RUNNERS 2 
#define MAX_ARRAY_LEN 10
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
	int offset = MAX_ARRAY_LEN/2;  // used for indexing in the second virtual array V[j] 
	int h =offset; m = offset; // h and m denote the size of each virtual array U[i] and 
				  //  and V[j] which happen to be the same value of offset
	while(i <= h && j<= m){
		if(g_unsorted_array[i] < g_unsorted_array[j+offset]){
			g_sorted_array[k] = g_unsorted_array[i]
			i++;
		}else{
			g_sorted_array[k] = g_unsorted_array[j+offset];
			j++;
		}
		k++;
	}
	if(i>h){ // copy V[j] through V[m] to S[k] through S[h+m]
		while(k <= MAX_ARRAY_LEN - 1){
			g_sorted_array[k] = g_unsorted_array[j+offset];
			++k;
			++j;
			
	}else{ // copy U[i] through U[h] to S[k] through S[h+m]
		while(k <= MAX_ARRAY_LEN - 1){
			g_sorted_array[k] = g_unsorted_array[i];
			++k;
			++i;
	}
 	// Print Sorted Array
	printf("The contents of the Sorted Array are: {");
	for(int i=0; i<MAX_ARRAY_LEN; ++i){
		print("%d, ", g_sorted_array[i]);
	}
	printf("}\n");
	pthread_exit(0);
			
} // end of Merging_Runner



// === main =================================================================================
// 
// ==========================================================================================
int	main(){
	printf("The contents of Unsorted Array are: {");
	for(int i=0; i<MAX_ARRAY_LEN; ++i){
		print("%d, ", g_unsorted_array[i]);
	}
	printf("}\n");
	
	struct runner_struct arg[NUM_SORT_RUNNERS];
	pthread_t t_ids[NUM_SORT_RUNNERS+1]; // 2 Sort Runners and 1 Merge Runner Thread
	arg[0].starting_index = 0;
	arg[1].starting_index = MAX_ARRAY_LEN/2;
	// Launch Threads
	printf("Launching Sorting Runners now...\n");
	for(int i = 0; i < NUM_SORT_RUNNERS; ++i){
		pthread_attr_t attr;
		pthread_attr_init(&attr);   // get the default attributes
		pthread_create( &t_ids[i], &attr, Sorting_Runner, &arg[i]); // create the thread

	}


	// Wait until each thread is done working
	for(int i = 0; i < 2; ++i){
		pthread_join(t_ids[i],NULL);    // wait for the thread to exit
	}
	printf("Sorting Runners Returned.\n Launching Merging Runner.\n");
	// Launch Merge Runner
	pthread_attr_t attr;
	pthread_attr_init(&attr); // get the default attributes
	pthread_create( &t_ids[NUM_SORT_RUNNERS+1], &attr, Merging_Runner, NULL);
	
	return 0;
}// end of main
