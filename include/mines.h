#ifndef __MINES__H__
#define __MINES__H__

#define LINES 11 //Number of lines on grid
#define COLS  15 //Number of columns on grid
#define MINES 40 //Number of mines to put on grid

#define DEBUG

typedef enum {TRUE,FALSE} bool;

typedef struct{
	char mat[11][15];
	bool hid[11][15];
}table;

typedef struct{
	int x;
	int y;
}point;

void fill_table(table*);
void plot_table(table);
void reveal_cell(table*, point);
void fill_numbers(table*);

#ifdef DEBUG
int MAX(int,int);
int MIN(int,int);
#endif

#endif //__MINES__H__
