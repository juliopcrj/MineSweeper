#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mines.h>

#define clear() printf("\033[H\033[J")

int main(int argc, char **argv){
	// seeding the rand
	srand(time(NULL));

	table t;
	fill_table(&t);
	printf("\n");

	int i,j;
	do{
		clear();
		plot_table(t);
		printf("Please pick your line and column\nType 0 0 to end\n");
		scanf("%d %d", &i, &j);
		if(i == 0){
			j = check_victory(t);
			if(j == 1){
				printf("VICTORY!\n");
			}else{
				printf("TOTAL DEFEAT!\n");
			}
			return 0;
		}
	}while(reveal_cell(&t, i-1, j-1) == 0);

	system(CLEAR);
	plot_table(t);
	printf("KABOOOOM!\n");
	return 0;
}
