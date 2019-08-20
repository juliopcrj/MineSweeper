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
	plot_table(t);

	return 0;
}
