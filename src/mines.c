#include <mines.h>
#include <stdio.h>
#include <stdlib.h>

int NORMALIZE(int n, int _min, int _max){
	if(n < _min)
		return _min;
	if(n > _max)
		return _max;
	return n;
}

int MAX(int x, int y){
	return(x>y)?x:y;
}

int MIN(int x, int y){
	return(x<y)?x:y;
}

void plot_table(table t){
	int i, j;
	printf("\t");
	for(i = 0; i< COLS; i++){
		printf("%d\t", i+1);
	}
	printf("\n");

	for(i = 0; i<LINES; i++){
		printf("%d\t", i+1);
		for(j = 0; j<COLS; j++)
		#ifdef DEBUG
			printf("%c\t", t.hid[i][j]);
		#else
			printf("%c\t", t.mat[i][j]);
		#endif
		printf("\n");
	}
}

void zero_table(table *t){
	int i,j;
	for(i = 0; i<LINES; i++)
		for(j = 0; j<COLS; j++)
			t->hid[i][j]='0';
}

void fill_table(table *t){
	int i, j;
	int _mines = 0;
	for(i = 0; i<LINES; i++){
		for(j = 0; j<COLS; j++){
			t->mat[i][j] = 'H';
		}
	}
	zero_table(t);
	do{
		for(i = 0; i<LINES; i++){
			for(j = 0; j<COLS; j++){
				if(rand()%100 > 90 && t->hid[i][j] != 'x' && _mines < MINES){
					t->hid[i][j] = 'x';
					_mines ++;
				}
			}
		}
	}while(_mines < MINES);

	fill_numbers(t);
}

int round_count(table t, int a, int b){
	int i,j, count=0;
	for(i = NORMALIZE(a-1,0,LINES); i<=NORMALIZE(a+1,0,LINES); i++){
		for(j = NORMALIZE(b-1,0,COLS); j<=NORMALIZE(b+1,0,COLS); j++){
			if(t.hid[i][j] == 'x')
				count ++;
		}
	}
	return count;
}

void fill_numbers(table *t){
	int i,j;
	for(i = 0; i<LINES; i++){
		for(j = 0; j<COLS; j++){
			if(t->hid[i][j] != 'x'){
				t->hid[i][j] = '0' + round_count(*t,i,j);
			}
		}
	}
}

int reveal_cell(table *t, int a, int b){

	if(a < 0 || a >=LINES || b < 0 || b >= COLS)
		return 1;
	t->mat[a][b] = t->hid[a][b];
	if(t->mat[a][b] == 'x')
		return -1; //Dead
	if(t->mat[a][b] == '0'){
		reveal_zeroes(t,a,b);
	}
	return 0;
}

void reveal_zeroes(table *t, int a, int b){
	t->mat[a][b] = t->hid[a][b];return;
	if(t->hid[a][b] != '0')
		return;
	if(a-1 >= 0)
		reveal_zeroes(t, a-1, b);
	if(b-1 >= 0)
		reveal_zeroes(t, a, b-1);
	if(a+1 < LINES)
		reveal_zeroes(t, a+1, b);
	if(b+1 < COLS)
		reveal_zeroes(t, a, b+1);
}
