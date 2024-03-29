#ifndef __MINES__H__
#define __MINES__H__

#define LINES 11 //Number of lines on grid
#define COLS  15 //Number of columns on grid
#define MINES 5 //Number of mines to put on grid

//#define DEBUG

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef enum {TRUE,FALSE} bool;

typedef struct{
	char mat[11][15];
	bool hid[11][15];
}table;


void fill_table(table*);
void plot_table(table);
int reveal_cell(table*, int, int);
void fill_numbers(table*);
void reveal_zeroes(table*, int, int);
int check_victory(table);
void reveal_all_mines(table, int, int);

#ifdef DEBUG
int MAX(int,int);
int MIN(int,int);
#endif

#endif //__MINES__H__
