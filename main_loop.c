/*
compile:
$ gcc -pthread main_loop.c 

run:
% ./a.out strategy_number
ex ./a.out 1 (selecting strategy 1)

test on the ubuntu18.04 ok

reference:
https://blog.gtwang.org/programming/pthread-multithreading-programming-in-c-tutorial/
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "./matrix.h"
#include <sys/time.h>

void *test2(void*);
void run_test2(pthread_t *, MX_A *, MX_B *, MX_C *);
void wait_all_thread_done(pthread_t *);
float cal_one_cell(MX_A *, MX_B *, int *);
void cal_mxa_mul_mxb(MX_A *, MX_B *, MX_C *);

typedef struct matrix_all{
	MX_A *mx_a;
	MX_B *mx_b;
	MX_C *mx_c;
	int index;
} MX_ALL;


void *test2(void* data) {
	MX_ALL *mx_all = (MX_ALL*) data;
	int i,j;
	int indexs[2];
	int td_index = mx_all->index; 
	i = td_index / a_i;
	indexs[0] = i;
	j = td_index % a_i;
	indexs[1] = j;

	mx_all->mx_c->MTX[i][j] = cal_one_cell(mx_all->mx_a, mx_all->mx_b, indexs);
	//printf("c[%d][%d]: %d \n", i, j, mx_all->mx_c->MTX[i][j]);

	free(data);
	pthread_exit(NULL);
}

void run_test2(pthread_t *td, MX_A *mx_a, MX_B *mx_b, MX_C *mx_c) {
	//test2: 10k threads
	int i = 0;
	for (i=0;i<a_i*b_j;i++) {
		MX_ALL *mx_all = malloc(sizeof(MX_ALL));
		mx_all->mx_a = mx_a;
		mx_all->mx_b = mx_b;
		mx_all->mx_c = mx_c;
		mx_all->index = i;

		pthread_create(&(td[i]), NULL, test2, (void*) mx_all);
	}
}

void wait_all_thread_done(pthread_t *td) {
	int i = 0;
	for (i=0;i<a_i*b_j;i++) {
		pthread_join(td[i], NULL);
	}
}


float cal_one_cell(MX_A *mx_a, MX_B *mx_b, int *indexs) {
	int i = indexs[0];
	int j = indexs[1];
	float cell_sum = 0;
	int k = 0;
	for (k=0;k<b_i;k++) { 
		cell_sum = cell_sum + mx_a->MTX[i][k] * mx_b->MTX[k][j];
	}
	return cell_sum;
} 


void cal_mxa_mul_mxb(MX_A *mx_a, MX_B *mx_b, MX_C *mx_c) {
	//test1: loop
	int i,j,k;
	int indexs[2];
	//printf("a_i: %d \n", a_i);
	//printf("b_j: %d \n", b_j);
	for(i=0;i<a_i;i++) {
		indexs[0] = i;
		for(j=0;j<b_j;j++) {
			indexs[1] = j;
			mx_c->MTX[i][j] = cal_one_cell(mx_a, mx_b, indexs);
			printf("c[%d][%d]: %d \n", i, j, mx_c->MTX[i][j]);
	 	}
	}
}


int main(int *argc, char *argv[]) {

	MX_A *mx_a = NULL;
	MX_B *mx_b = NULL;
	MX_C *mx_c = NULL;
	int strategy = 0;
	struct timeval start, end;
	int passed_time = 0;	

	pthread_t td[a_i *b_j];	
	strategy = atoi(argv[1]);
	printf("select test_%d\n", strategy);

	//initial matrix
	set_MX_A_addr(&mx_a);
	set_MX_B_addr(&mx_b);
	set_MX_C_addr(&mx_c);
	printf("initial [a]:\n");
	mx_a->show_matrix(mx_a);
	printf("initial [b]:\n");
	mx_b->show_matrix(mx_b);
	printf("initial [c]:\n");
	mx_c->show_matrix(mx_c);
	
	gettimeofday( &start, NULL );
	
	// run process by selected strategy 
	if (strategy == 1) {	
		printf("==== test1 ====\n");
		cal_mxa_mul_mxb(mx_a, mx_b, mx_c);
		printf("cal [c] = [a] * [b]:\n");
		mx_c->show_matrix(mx_c);
	} else if (strategy == 2) {
		printf("==== test2 ====\n");
		run_test2(td, mx_a, mx_b, mx_c);
		wait_all_thread_done(td);
		mx_c->show_matrix(mx_c);
	}
	gettimeofday( &end, NULL );

	passed_time= 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec; 
    printf("passed time: %d us\n", passed_time);
	free(mx_a);
	free(mx_b);
	free(mx_c);
}
