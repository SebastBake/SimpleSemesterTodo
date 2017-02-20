/* Written by Sebastian Baker */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LINE_LEN 50
#define LINES_B_DAYS 1
#define LINES_B_HEADS 2
#define SEC_IN_DAY 60*60*24
#define DAYS_IN_WEEK 7
#define FILENAME "MyPlan"


void print_update(struct tm *timeinfo, FILE *fp);
void print_date(time_t info, FILE *fp);
void print_weeks(int weeknum, time_t info, FILE *fp);
void print_day(time_t info, FILE *fp);
void print_gap(int n, FILE *fp);
void print_line(int n, FILE *fp);
char * itoa (int value, char *result, int base);


int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: ./planner <days till planner start> <weeknum> > file\n");
		exit(EXIT_FAILURE);
	}

	time_t c_rawtime, ws_rawtime;
	int weeknum = atoi(argv[2]);
	struct tm *c_datetime;

	// Generate filename & open file
	char *wknumchar;
	wknumchar = (char*)malloc(sizeof(char)*2);
	if(!wknumchar) {
		printf("Error allocating memory...\n");
		exit(-1);
	}
	itoa(weeknum, wknumchar, 10);

	char filename[80];

	strcpy(filename, FILENAME);
	strcat(filename, "_week");
	strcat(filename, wknumchar);
	strcat(filename, ".txt");

	FILE *fp;
	fp = fopen(filename, "a");

	//current date/time
	time( &c_rawtime );
	c_datetime = localtime(&c_rawtime);
	print_update(c_datetime, fp);
	fprintf(fp, "\n");

	//days till monday to get week start time
	ws_rawtime = c_rawtime + (atoi(argv[1]))*SEC_IN_DAY;
	fprintf(fp, "\n");

	//print agenda
	print_weeks(weeknum, ws_rawtime, fp);

	//print other
	print_gap(LINES_B_HEADS, fp);
	print_gap(LINES_B_HEADS, fp);
	fprintf(fp, "OTHER\n=====");
	print_gap(LINES_B_HEADS, fp);
	print_gap(LINES_B_HEADS, fp);
	print_gap(LINES_B_HEADS, fp);
	print_gap(LINES_B_HEADS, fp);
	print_gap(LINES_B_HEADS, fp);
	print_gap(LINES_B_HEADS, fp);
	print_gap(LINES_B_HEADS, fp);

	fflush(fp);
	fclose(fp);
	printf("done/n");

	return 0;
}


void print_weeks(int weeknum, time_t info, FILE *fp){
	int i;
	print_gap(LINES_B_HEADS, fp);
	fprintf(fp, "WEEK %02d\n=======", weeknum);

	for (i=0;i<DAYS_IN_WEEK;i++){
		print_day(info+i*SEC_IN_DAY, fp);
	}

	print_gap(LINES_B_HEADS, fp);
	fprintf(fp, "WEEK %02d\n=======", weeknum+1);
}


void print_day(time_t info, FILE *fp){
	print_gap(LINES_B_HEADS, fp);
	print_line(LINE_LEN, fp);
	fprintf(fp, "(");
	print_date(info, fp);
	fprintf(fp, ")\n");
	fprintf(fp, "Goals:\n");
}


void print_update(struct tm *timeinfo, FILE *fp){
	fprintf(fp,  "Updated: %s\n", asctime(timeinfo) );
}


void print_date(time_t info, FILE *fp){
	struct tm *timeinfo;
	char str[80];

	timeinfo = localtime(&info);
	strftime(str ,80 ,"%A  |  %d %B %Y", timeinfo);
	fprintf(fp,  "%s", str);
}


void print_gap(int n, FILE *fp){
	int i;
	for (i=1; i<=n; i++){
		fprintf(fp, "\n");
	}
}


void print_line(int n, FILE *fp){
	int i;
	for (i=1; i<=n; i++){
		fprintf(fp, "_");
	}
}

char * itoa (int value, char *result, int base){
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while (ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}













