#define _GNU_SOURCE

#include<string.h>
#include<stdio.h>
#include <stdlib.h>

typedef struct File{
    char name[2000];
    int usage;
} file;

typedef struct  User{
    char name[2000];
    int usage;
    file files[1000];
    int file_num;
    struct User *next;

}User;

// User node
typedef struct Users{
    User *head;
    User *tail;
    int user_num;
}Users;

int my_sizeof(char *type);
void addUser(Users *users, char *cnet_id, int usage);
User* findUser(Users *users, char *cnet_id);
int calSize(User *users, char *line);
void traverse(Users *users, char *mode, char* cnet_id);
Users * initUsers();

// Init the Users Linked List
Users * initUsers() {
    Users* users = (Users *) malloc(sizeof(Users));
    users->head = NULL;
    users->tail = NULL;
    users->user_num = 0;
    return users;
}

// Create new User with name and usage
User * newUser(char *name, int usage) {
    User* user = (User*) malloc(sizeof(User));
    strncpy(user->name, name, strlen(name) + 1);
    user->next = NULL;
    user->file_num = 0;

    return user;
}

// compare function for sort files
int cmpfunc(const void *a, const void *b) {
    return ((file*)b)->usage - ((file*)a)->usage;
}

// return the size of type represented by char*
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


// void add user to the linked list
void addUser(Users *users, char *cnet_id, int usage) {
    User *user = newUser(cnet_id, usage);

    if(users->head == NULL) {
        users->head = user;
        users->tail = user;
    } else {
        users->tail->next = user;
        users->tail = user;
    }
}

// Find the file in user
int findFile(User *user, char* filename) {
    int find = 0;
    for(int i = 0; i < user->file_num; i++) {
        if(strcmp(user->files[i].name, filename) == 0){
            find = 1;
            return i;
        }
    }
    if (find == 0) {
        strncpy(user->files[user->file_num].name, filename, strlen(filename) + 1);
        user->file_num++;
    }
    return user->file_num - 1;
}

// Calculate usage of files in a line
int calSize(User *users, char *line) {
    char * token = strtok(line, " ");
    int index = 0;  // the index of following line: CNET_ID FILENAME TYPE1 TYPE2 ... TYPEN
    int total_size = 0;
    int file_index;
    User* user;
    while(token != NULL) {
        if (index == 0) {   // token is CNET_ID now
            user = findUser(users, token);
        }
        if(index == 1){
            file_index = findFile(user, token);
            // printf(" file index %d ", file_index);
        }
        if(index >= 2) {
            total_size += my_sizeof(token);
        }
        token = strtok(NULL, " ");
        index++;
    }
    user->usage += total_size;
    user->files[file_index].usage += total_size;
    return total_size;
}

// Find the user in the Users Linked List and return the pointer to the user
User* findUser(Users *users, char *cnet_id) {
    int find = 0;
  
    for(User* ptr = users->head; ptr!=NULL; ptr = ptr->next) {
        //if find the user in linked list, return the ptr to the user
        if(strcmp(ptr->name, cnet_id) == 0) {   
            find = 1;
            return ptr;
        }
    }
        // if cannot find the user, add the user to the linked list
        if (find == 0) {
            addUser(users, cnet_id, 0);
            users->user_num++;
            return users->tail;
        }
}

void traverse(Users *users, char *mode, char* cnet_id) {
    // normal mode
    if (strcmp(mode, "normal") == 0) {
        for(User *ptr = users->head; ptr != NULL; ptr = ptr->next) 
            printf("%s %d with %d files:\n", ptr->name, ptr->usage, ptr->file_num);  
    } else if(strcmp(mode, "file") == 0){
        int total_files_num = 0, index = 0;

        // calculate the total number of files 
        for(User *ptr = users->head; ptr != NULL; ptr = ptr->next) {
            total_files_num += ptr->file_num;
                
        }

        // create total_files struct array
        file * total_files = (file*) malloc(sizeof(file) * total_files_num);
        for(User *ptr = users->head; ptr != NULL; ptr = ptr->next) {
            for(int i = 0; i < ptr->file_num; i++) {
                strncpy(total_files[index].name, ptr->files[i].name, strlen(ptr->files[i].name) + 1);
                total_files[index].usage = ptr->files[i].usage;
                index++;
            }            
        }
        // sort total_files struct array
        qsort(total_files, total_files_num, sizeof(file), cmpfunc);

        //print the result
        for(int i = 0; i < total_files_num; i++) {
            printf("%s %d\n", total_files[i].name, total_files[i].usage);
        }



    } else if (strcmp(mode, "user") == 0) {
        int found = 0;
        for(User *ptr = users->head; ptr != NULL; ptr = ptr->next) {
            if(strcmp(ptr->name, cnet_id) == 0){
                found = 1;
                qsort(ptr->files, ptr->file_num, sizeof(file), cmpfunc);
                for(int i = 0; i < ptr->file_num; i++)
                    printf("%s %d\n",ptr->files[i].name, ptr->files[i].usage);
            }
         
        }
        if (found == 0) {
            printf("user not found\n");
        }
    }

    
}

// Free the memory
void freeUsers(Users *users) {
    User *cur;
    while(users->head != NULL) {
        cur = users->head;
        users->head = users->head->next;
        free(cur);
    }
    free(users);
}

int main(int argc, char * argv[]){
    char *line = NULL;
    long int len = 0;
    long nRead = getline(&line, &len, stdin);
    int line_num = 0;
    Users *users = initUsers();


    while ( nRead != -1) {
        
        if (line_num != 0){
            
            calSize(users, line);
        }

        // Done using line so I must free it!!
        free(line);

        //Make sure to reset line back to null for the next line
        line = NULL;
        nRead = getline(&line, &len, stdin);
        line_num++;
    }

    if (argc == 1){
        traverse(users, "normal", NULL);
    } else if(argc == 2){
        traverse(users, "file", NULL);  // unsorted now, need to be sorted

    } else if(argc == 3) {
        traverse(users, "user", argv[2]);   // unsorted now, need to be sorted
    }

    
    freeUsers(users);
}
