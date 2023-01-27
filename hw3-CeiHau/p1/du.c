#define _GNU_SOURCE

#include<string.h>
#include<stdio.h>
#include <stdlib.h>

#define MAX_USER 999

int my_sizeof(char *type);
int cal_size(char *line);
int find_user(char * cnet_id);

struct User {
    char name[2000];
    int usage;
};

struct User users[MAX_USER];
int user_num = 0;

int my_sizeof(char *type) {
    if(strcmp(type, "int")==0 || strcmp(type, "int\n") ==0){
        return sizeof(int);
    } else if(strcmp(type, "double") ==0 || strcmp(type, "double\n") ==0){
        return sizeof(double);
    }else if(strcmp(type, "float")==0 || strcmp(type, "float\n") == 0){
        return sizeof(float);
    }else if(strcmp(type, "char") == 0 || strcmp(type, "char\n") ==0){
        return sizeof(char);
    }else{
        return 0;
    }
}

int cal_size(char *line) {
    char * token = strtok(line, " ");
    int index = 0;
    int total_size = 0;
    int user_index = -1;
    while(token != NULL) {
        if (index == 0) {
            // printf("%s\n", token);
            user_index = find_user(token);
        }

        if (index >= 2) {
            total_size += my_sizeof(token);
        }
        token = strtok(NULL, " ");
        index ++;
    }
    users[user_index].usage += total_size;
    return total_size;
}

int find_user(char * cnet_id) {
    // printf("find %s size %d len %d\n", cnet_id, sizeof(cnet_id), strlen(cnet_id));
     int find = 0;
        for(int i = 0; i < user_num; i++) {
            if (strcmp(users[i].name, cnet_id) == 0) {
                find = 1;
                return i;
            }
        }

        if (find == 0) {
            strncpy(users[user_num].name, cnet_id, strlen(cnet_id) + 1);
            user_num++;
        }
        return user_num - 1;
}


int main(){
    char *line = NULL;
    long int len = 0;
    long nRead = getline(&line, &len, stdin);
    int line_num = 0;

    while ( nRead != -1) {
        
        if (line_num != 0){
            cal_size(line);
        }

        // Done using line so I must free it!!
        free(line);

        //Make sure to reset line back to null for the next line
        line = NULL;
        nRead = getline(&line, &len, stdin);
        line_num++;
    }

    for(int i = 0; i < user_num; i++) {
        printf("%s %d\n" ,users[i].name, users[i].usage);
    }
}
