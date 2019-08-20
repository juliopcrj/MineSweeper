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
		plot_table(t);
		printf("Please pick your line and column\n");
		scanf("%d %d", &i, &j);
	}while(reveal_cell(&t, i, j) != -1);

	plot_table(t);
	printf("KABOOOOM!\n");
	return 0;
}
