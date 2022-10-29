#include <assert.h>
#include "hashtable.h"

struct KVPair* hashArray[SIZE];

int main(int argc, char *argv[]) {
    // load database
    FILE *fp = fopen("database.txt", "r");
    assert(fp != NULL);

    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    int key;
    while ((linelen = getline(&line, &linecap, fp)) > 0) {
        line[linelen - 1] = '\0';
        key = atoi(strsep(&line, ","));
        char *value = strsep(&line, ",");
        insert(key, value);
    }
    fclose(fp);
    free(line);

    char **toFree = (char **)malloc(argc * sizeof(char *));
    assert(toFree != NULL);
    // for each command on command-line args, process them
    for (int i = 1; i < argc; ++i) {
        // parse each command
        char *token, *string;
        string = strdup(argv[i]);
        toFree[i - 1] = string;
        assert(string != NULL);

        char *cmd[3] = { NULL };
        int j = 0;
        while ((token = strsep(&string, ",")) != NULL) {
            cmd[j++] = token;
        }

        struct KVPair* p = NULL;
        char command = **cmd;
        switch (command) {
            case 'p':
                key = atoi(cmd[1]);
                insert(key, cmd[2]);
                break;
            case 'g':
                key = atoi(cmd[1]);
                p = get(key);
                if (p == NULL) {
                    printf("%d not found\n", key);
                } else {
                    printf("%d,%s\n", key, p->val);
                }
                break;
            case 'd':
                key = atoi(cmd[1]);
                p = get(key);
                if (p == NULL) {
                    printf("%d not found\n", key);
                } else {
                    delete(key);
                }
                break;
            case 'c':
                clear();
                break;
            case 'a':
                display();
                break;
            default:
                printf("bad command\n");
        }   
    }
    
    for (int i = 1; i < argc; ++i) {
        free(toFree[i - 1]);  // free the space strdup mallocs
    }
    free(toFree);

    // store database
    fp = fopen("database.txt", "w");
    assert(fp != NULL);

    for (int i = 0; i < SIZE; ++i) {
        if (hashArray[i] != NULL) {
            fprintf(fp, "%d,%s\n", hashArray[i]->key, hashArray[i]->val);
        }
    }

    fclose(fp);
    return 0;
}