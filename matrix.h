#include <stdlib.h>
#include <stdio.h>


#define a_i 2
#define a_j 3
#define b_i 3
#define b_j 2


typedef struct matrix_a {
	int MTX[a_i][a_j];
	void(*initial_martix)(struct matrix_a *);	
	void(*show_matrix)(struct matrix_a *);	
} MX_A;

typedef struct matrix_b {
	int MTX[b_i][b_j];
	void(*initial_martix)(struct matrix_b *);	
	void(*show_matrix)(struct matrix_b *);	
} MX_B;

typedef struct matrix_c {
	int test;
	int MTX[a_i][b_j];
	void(*initial_martix)(struct matrix_c *);	
	void(*show_matrix)(struct matrix_c *);	
} MX_C;

typedef struct matrix_all{
    MX_A *mx_a;
    MX_B *mx_b;
    MX_C *mx_c;                                                                                                                                                        
    int index; 
} MX_ALL; 

void initial_matrix_a(MX_A *val) {
	// [a] = 12i -3.8j
	int i,j;	
	for(i=0;i<a_i;i++) {
		for(j=0;j<a_j;j++) {
			val->MTX[i][j] = 2*(i+1) + 2*(j+1); 
		}
	}	
}

void initial_matrix_b(MX_B *val) {
	// [b] = 65.1 + 3.3i -20.2j
	int i,j;	
	for(i=0;i<b_i;i++) {
		for(j=0;j<b_j;j++) {
			val->MTX[i][j] = (i+1) + (j+1); 
		}
	}	

}

void initial_matrix_c(MX_C *val) {
	// [c] = [a] * [b]
	int i,j;	
	for(i=0;i<a_i;i++) {
		for(j=0;j<b_j;j++) {
			val->MTX[i][j] = 0; 
		}
	}	

}

void show_matrix_a(MX_A *val) {
	int i,j;	
	for(i=0;i<a_i;i++) {
		for(j=0;j<a_j;j++) {
			printf("%d ",val->MTX[i][j]); 
		}
		printf("\n");
	}	
}

void show_matrix_b(MX_B *val) {
	int i,j;	
	for(i=0;i<b_i;i++) {
		for(j=0;j<b_j;j++) {
			printf("%d ", val->MTX[i][j]); 
		}
		printf("\n");
	}	
}

void show_matrix_c(MX_C *val) {
	int i,j;	
	for(i=0;i<a_i;i++) {
		for(j=0;j<b_j;j++) {
			printf("%d ", val->MTX[i][j]); 
		}
		printf("\n");
	}	
}


void set_MX_A_addr(MX_A **val) {
	*val = malloc(sizeof(MX_A));
	(*val)->initial_martix = initial_matrix_a;
	(*val)->show_matrix = show_matrix_a;
	(*val)->initial_martix(*val);
}

void set_MX_B_addr(MX_B **val) {
	*val = malloc(sizeof(MX_B));
	(*val)->initial_martix = initial_matrix_b;
	(*val)->show_matrix = show_matrix_b;
	(*val)->initial_martix(*val);
}

void set_MX_C_addr(MX_C **val) {
	*val = malloc(sizeof(MX_C));
	(*val)->initial_martix = initial_matrix_c;
	(*val)->show_matrix = show_matrix_c;
	(*val)->initial_martix(*val);
}


