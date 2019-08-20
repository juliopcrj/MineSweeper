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
	printf("\t1   2   3   4   5   6   7   8   9   10  11  12  13  14  15");
	printf("\n");

	for(i = 0; i<LINES; i++){
		printf("%d\t", i+1);
		for(j = 0; j<COLS; j++)
		#ifdef DEBUG
			printf("%c   ", t.hid[i][j]);
		#else
			printf("%c   ", t.mat[i][j]);
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

	if(t->hid[a][b] == 'x'){
		t->mat[a][b] = t->hid[a][b];
		return -1; //Dead
	}
	if(t->hid[a][b] == '0'){
		reveal_zeroes(t,a,b);
	}
	else{
		t->mat[a][b] = t->hid[a][b];
	}
	return 0;
}

void reveal_zeroes(table *t, int a, int b){
	if(t->mat[a][b] == 'H'){
		t->mat[a][b] = t->hid[a][b];
		if(t->mat[a][b] == '0'){
			reveal_zeroes(t, MAX(a-1, 0), b);
			reveal_zeroes(t, a, MAX(b-1, 0));
			reveal_zeroes(t, MIN(a+1,LINES-1), b);
			reveal_zeroes(t, a, MIN(b+1, COLS-1));
		}
		//If the cell wasn't yet revealed.
	}
	return;
}

int check_victory(table t){
	int i,j;
	for(i = 0; i<LINES; i++){
		for(j = 0; j<LINES; j++){
			if(t.hid[i][j] != t.mat[i][j] && t.hid[i][j] != 'x')
				return 0;
		}
	}
	return 1;
}
