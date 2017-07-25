/*
 * Written by Sebastian Baker
 * A C program intended to generate a todo list in a .txt file.
 * Written for practice and revision in C programming.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_ARGS 3
#define LINE_LEN 50
#define LINES_B_DAYS 1
#define LINES_B_HEADS 2
#define SEC_IN_DAY 60*60*24
#define DAYS_IN_WEEK 7
#define FILENAME "MyPlan"
#define ITOA_BASE 10
#define WKNUM_NUM_CHARS 2
#define MALLOC_ERROR_MESSAGE "Error allocating memory...\n"
#define INPUT_INSTRUCTIONS "Usage: ./todo <days till first day> <weeknum> > file\n"

typedef struct {
	time_t raw;
	struct tm date;
} myTimeStruct;

void print_update(myTimeStruct * currentTime, FILE *fp);
void print_date(time_t info, FILE *fp);
void print_weeks(int weeknum, time_t info, FILE *fp);
void print_day(time_t info, FILE *fp);
void print_gap(int n, FILE *fp);
void print_line(int n, FILE *fp);
void generate_filename(int wknum, char * filename);
void init_times(myTimeStruct * currentTime, myTimeStruct  * wkStartTime, int secondsTillStart);
FILE * open_file();
char * myitoa(int value);
char * itoa(int value, char *result, int base);


int main(int argc, char *argv[]) {
	
	// Deal with the inputs
	if (argc != NUM_ARGS) {
		printf(INPUT_INSTRUCTIONS);
		exit(EXIT_FAILURE);
	}
	int secondsTillStart = atoi(argv[1])*SEC_IN_DAY;
	int weeknum = atoi(argv[2]);
	
	// Initialise time variables
	myTimeStruct *currentTime = (myTimeStruct*)malloc(sizeof(myTimeStruct));
	myTimeStruct *wkStartTime = (myTimeStruct*)malloc(sizeof(myTimeStruct));
	if(!currentTime || !wkStartTime) {
		printf(MALLOC_ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
	init_times( currentTime, wkStartTime, secondsTillStart);

	 // Generate filename & open file
	FILE *fp = open_file(weeknum);

	// Begin print to file
	print_update(currentTime, fp);
	print_weeks(weeknum, wkStartTime->raw, fp);
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

	printf("done\n");
	return 0;
}

void init_times(myTimeStruct * currentTime, myTimeStruct  * wkStartTime, int secondsTillStart){
	currentTime->raw = time(NULL);
	currentTime->date = *localtime( &(currentTime->raw) );
	wkStartTime->raw = currentTime->raw + secondsTillStart;
	wkStartTime->date = *localtime( &(wkStartTime->raw) );
}

FILE * open_file(weeknum){
	char filename[80];
	generate_filename(weeknum, filename);
	FILE *fp;
	fp = fopen(filename, "a");
	return fp;
}

void generate_filename(int wknum, char * filename){
	char *wknumchar;
	wknumchar = (char*)malloc(sizeof(char)*WKNUM_NUM_CHARS);
	if(!wknumchar) {
		printf(MALLOC_ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
	
	itoa(wknum, wknumchar, 10);
	strcpy(filename, FILENAME);
	strcat(filename, wknumchar);
	strcat(filename, ".txt");
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


void print_update(myTimeStruct * currentTime, FILE *fp){
	fprintf(fp,  "Updated: %s\n\n", asctime(&(currentTime->date)));
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

char * myitoa(int value) {
	return 0;
}

char * itoa (int value, char *result, int base){
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "0123456789abcdefghijklmnopqrstuvwxyz" [(tmp_value - value * base)];
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













