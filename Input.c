#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
	int day, year;
	char weekday[20], month[20], dtm[100];
	strcpy( dtm, "Saturday March 25 1989" );
	sscanf( dtm, "%s %s %d  %d", weekday, month, &day, &year );
	printf("%s %d, %d = %s\n", month, day, year, weekday );
	// fprintf(stdout,"%ld\n",strlen(dtm));
	// for(int i=0;i<strlen(dtm);i++)
	//fprintf(stdout,"%c",dtm[13]);
	fprintf(stdout,"%s\n",dtm);

	return(0);
}
