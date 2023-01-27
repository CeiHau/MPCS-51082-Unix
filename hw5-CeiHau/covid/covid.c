#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int zipcodeCol = 0;
const int weekStart = 2;
const int casesWeek = 4;
const int testsWeek = 8;
const int deathsWeek = 14;

char * compute(int zipcode, int month, int year);
void split(char **record, char *line, int *num, char *delimeter);
void parse_time(char *time, int *year, int *month);
char* strtoke(char *str, const char *delim);
int check(char *zip, char *week, char *cases, char *tests, char *deaths);
int push_set(char set[20000][100], int *num, char **record);

int main(int argc, char *argv[]){
    
    FILE *input_file = fopen(argv[1], "r"); 
    FILE *output_file = fopen(argv[2], "w+");

    int temp;
    int zipode, month, year;
    int index = 0;
    while (fscanf(input_file, "%d", &temp) == 1) {
        if (index % 3 ==0) {  
            zipode = temp;
        } else if (index % 3 == 1) {
            month = temp;
        } else if (index % 3 == 2) {
            year = temp;
            // Get all zipode, month, year, and write to output file
            fprintf(output_file, "%d %d %d = ", zipode, month, year);

            // Call compute function 
            char * compute_string = compute(zipode, month, year);

            // Write the result of compute to output file
            fprintf(output_file, "%s\n", compute_string);

            free(compute_string);
            }
        index++;
    }

    fclose(output_file);
    fclose(input_file);

    return 0;
}   


void my_free(char **s, int num) {
    for (int i = 0; i < num; i++) {
        free(s[i]);
    }
}


// Parse the time, get the year and month from it
void parse_time(char *time, int *year, int *month) {
    char * date[3];
    int temp = 0;
    split(date, time, &temp, "/");
    *year = atoi(date[2]);
    *month = atoi(date[0]);

    my_free(date, 3);
}

/* 
    Check if a record for any of specified columns do not contain a value 
*/
int check(char *zip, char *week, char *cases, char *tests, char *deaths) {
    if(strcmp(zip, "") == 0 || strcmp(week,"") == 0 || strcmp(cases,"") == 0  || strcmp(tests,"") == 0  || strcmp(deaths,"") == 0 ) {
        return 0;
    } else {
        return 1;
    }
}

/*
    Split line by delimeter, the num is the item after splitting
*/
void split(char **record, char *origin_line, int *num, char *delimeter){
    char * line = (char *) malloc(sizeof(char) * (strlen(origin_line) + 1));
    strcpy(line, origin_line);

    char * token = strtoke(line, delimeter);
    while (token != NULL) {
        int len = strlen(token) + 1;    // Get the len of the token
        record[*num] = (char*) malloc(sizeof(char) * len);  // Malloc space for record[*num]
        strcpy(record[*num], token);    // Copy token to record[*num]
        (*num)++;
        token = strtoke(NULL, delimeter);
    }
    free(line);
}

// source : https://stackoverflow.com/questions/42315585/split-string-into-tokens-in-c-when-there-are-2-delimiters-in-a-row
/* 
    Cause the prigin strtok is stupid, behaves like strtok() except that it returns empty tokens also
 */
char* strtoke(char *str, const char *delim)
{
        static char *start = NULL; /* stores string str for consecutive calls */
        char *token = NULL; /* found token */
        /* assign new start in case */
        if (str) start = str;
        /* check whether text to parse left */
        if (!start) return NULL;
        /* remember current start as found token */
        token = start;
        /* find next occurrence of delim */
        start = strpbrk(start, delim);
        /* replace delim with terminator and move start to follower */
        if (start) *start++ = '\0';
        /* done */
        return token;
}


/*
    Try push record into set, if fail return 0, else return 1
*/
int push_set(char set[20000][100], int *num, char **record) {
    // record[]
    char *key = (char*) malloc((strlen(record[zipcodeCol]) + strlen(record[weekStart]) + 1) * sizeof(char));
    strcpy(key, record[zipcodeCol]);
    strcat(key, record[weekStart]);

    for(int i = 0; i < *num; i++) {
        if (strcmp(set[i],key) == 0) {
            return 0;   // 0 represents push failed
        }
    }
    strcpy(set[*num], key);
    (*num)++;
    free(key);
    return 1;   // 1 represents push successed
}


/* 
    Calculates the total number of cases, tests, and deaths for a zip code in a given month and year 
*/ 
char * compute(int zipcode, int month, int year) {
    int total_num_cases = 0;
    int total_num_tests = 0;
    int total_num_deaths = 0;
    char set[20000][100]; // A container to check if the record is duplicated
    int set_num = 0;
    
    for(int i = 1; i <= 15; i++) {
        char file_path[100];
        sprintf(file_path, "../data/covid_%d.csv", i);

        FILE *fp = fopen(file_path, "r");
        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        if (fp == NULL) {
            printf("read fail\n");
            exit(EXIT_FAILURE);
        }
        int index = 0;
        // read file line by line
        while ((read = getline(&line, &len, fp)) != -1) {
            int num = 0;
            char * record[100]; // Need to be free
            
            // Split the line by "," and save to record
            split(record, line, &num, ",");
    
            if (index != 0){
                int y, m;

                // Parse the time and get year and month
                parse_time(record[weekStart], &y, &m);
                
                int zc = atoi(record[zipcodeCol]);   // Get the zipcode

                // If the record is the one we are looking for
                if (zc == zipcode && y == year && m == month) {
                    // If the record is valid
                    if (check(record[zipcodeCol], record[weekStart], record[casesWeek], record[testsWeek], record[deathsWeek])){
                        // If the record is not duplicated
                        if (push_set(set, &set_num, record) == 1) {
                            total_num_cases += atoi(record[casesWeek]);
                            total_num_deaths += atoi(record[deathsWeek]);
                            total_num_tests += atoi(record[testsWeek]);
                        }

                    }
                }
            }

            my_free(record, num);
            free(line);
            line = NULL;
            index ++;

        }

        fclose(fp);
        if (line)
            free(line);
    }

    // save the result to char *
    char *result;
    result  = (char *) malloc(sizeof(char) * 30);
    sprintf(result, "%d,%d,%d", total_num_cases, total_num_tests, total_num_deaths);
    return result;
}

