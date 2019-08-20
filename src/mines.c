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
	for(i = 0; i<LINES; i++){
		for(j = 0; j<COLS; j++)
		#ifdef DEBUG
			printf("%c ", t.hid[i][j]);
		#else
			printf("%c ", t.mat[i][j]);
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
	for(i = NORMALIZE(a-1,0,LINES); i<NORMALIZE(a+1,0,LINES); i++){
		for(j = NORMALIZE(j-1,0,COLS); j<NORMALIZE(j+1,0,COLS); j++){
			if(t.hid[i][j] == 'x')
				count ++;
		}
	}

	#ifdef DEBUG
	printf("Count is %d, and value is %c\n", count, '0'+count);
	#endif
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

void reveal_cell(table *t, point p){
	//Todo: if cell is bomb, end game. Else, show cell
}
