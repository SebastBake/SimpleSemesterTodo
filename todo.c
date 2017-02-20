/* Written by Sebastian Baker */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINE_LEN 50
#define LINES_B_DAYS 1
#define LINES_B_HEADS 2
#define SEC_IN_DAY 60*60*24
#define DAYS_IN_WEEK 7


void print_update(struct tm *timeinfo);
void fprint_date(time_t info);
void print_weeks(int weeknum, time_t info);
void print_day(time_t info);
void print_gap(int n);
void print_line(int n);


int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: ./planner <days till planner start> <weeknum> > file\n");
		exit(EXIT_FAILURE);
	}

	time_t c_rawtime, ws_rawtime;
	int weeknum = atoi(argv[2]);
	struct tm *c_datetime;

	//current date/time
	time( &c_rawtime );
	c_datetime = localtime(&c_rawtime);
	print_update(c_datetime);
	printf("\n");

	//days till monday to get week start time
	ws_rawtime = c_rawtime + (atoi(argv[1]))*SEC_IN_DAY;
	printf("\n");

	//print agenda
	print_weeks(weeknum, ws_rawtime);

	//print other
	print_gap(LINES_B_HEADS);
	printf("OTHER\n=====");
	print_gap(LINES_B_HEADS);
	print_gap(LINES_B_HEADS);
	print_gap(LINES_B_HEADS);
	print_gap(LINES_B_HEADS);
	print_gap(LINES_B_HEADS);
	print_gap(LINES_B_HEADS);
	print_gap(LINES_B_HEADS);
	print_gap(LINES_B_HEADS);

	return 0;
}


void print_weeks(int weeknum, time_t info){
	int i;
	print_gap(LINES_B_HEADS);
	printf("WEEK %02d\n=======", weeknum);

	for (i=0;i<DAYS_IN_WEEK;i++){
		print_day(info+i*SEC_IN_DAY);
	}

	print_gap(LINES_B_HEADS);
	printf("WEEK %02d\n=======", weeknum+1);

}


void print_day(time_t info){
	print_gap(LINES_B_DAYS);
	print_line(LINE_LEN);
	printf("(");
	fprint_date(info);
	printf(")\n");
	printf("Goals:\n");
}


void print_update(struct tm *timeinfo){
	printf( "Updated: %s\n", asctime(timeinfo) );
}


void fprint_date(time_t info){
	struct tm *timeinfo;
	char str[80];

	timeinfo = localtime(&info);
	strftime(str ,80 ,"%A  |  %d %B %Y", timeinfo);
	printf( "%s", str);
}


void print_gap(int n){
	int i;
	for (i=1; i<=n; i++){
		printf("\n");
	}
}


void print_line(int n){
	int i;
	for (i=1; i<=n; i++){
		printf("_");
	}
}














