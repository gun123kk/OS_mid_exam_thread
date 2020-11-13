#include <stdlib.h>
#include <stdio.h>
#include "./matrix.h"


void cal_mxa_mul_mxb(MX_A *mx_a, MX_B *mx_b, MX_C *mx_c) {
	int i,j,k;
	//printf("a_i: %d \n", a_i);
	//printf("b_j: %d \n", b_j);
	for(i=0;i<a_i;i++) {
		for(j=0;j<b_j;j++) {
			for(k=0;k<b_i;k++) { 
				//printf("c: %d \n", mx_c->MTX[i][j]);
				mx_c->MTX[i][j] = mx_c->MTX[i][j] + mx_a->MTX[i][k] * mx_b->MTX[k][j];
			}
			printf("c[%d][%d]: %d \n", i, j, mx_c->MTX[i][j]);
	 	}
	}
}


int main(void) {
	printf("hello\n");
	MX_A *mx_a = NULL;
	MX_B *mx_b = NULL;
	MX_C *mx_c = NULL;
	set_MX_A_addr(&mx_a);
	set_MX_B_addr(&mx_b);
	set_MX_C_addr(&mx_c);
	printf("initial [a]:\n");
	mx_a->show_matrix(mx_a);
	printf("initial [b]:\n");
	mx_b->show_matrix(mx_b);
	printf("initial [c]:\n");
	mx_c->show_matrix(mx_c);
	cal_mxa_mul_mxb(mx_a, mx_b, mx_c);
	printf("cal [c] = [a] * [b]:\n");
	mx_c->show_matrix(mx_c);
	free(mx_a);
	free(mx_b);
	free(mx_c);
}
