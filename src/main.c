#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mines.h>

int main(int argc, char **argv){
	// seeding the rand
	srand(time(NULL));

	table t;
	fill_table(&t);
	printf("\n");

	int i,j;
	do{
		system(CLEAR);
		plot_table(t);
		printf("Please pick your line and column\nType 0 0 to end\n");
		scanf("%d %d", &i, &j);
		if(i == 0){
			system(CLEAR);
			reveal_all_mines(t, -1, -1);
			j = check_victory(t);
			if(j == 1){
				printf("\33[0;32m");
				printf("VICTORY!\n");
			}else{
				printf("\33[0;31m");
				printf("TOTAL DEFEAT!\n");
			}
			return 0;
		}
	}while(reveal_cell(&t, i-1, j-1) == 0);

	system(CLEAR);
	reveal_all_mines(t, i-1, j-1);
	printf("\33[0;31m");
	printf("TOTAL DEFEAT!\n");
	return 0;
}
