#include "header.h"
#include "input.h"


int execute_pinfo_func(char *command[200], int len, char command_string[200])
{
    char id[200] = "\0";
    char buf[300] = "\0";
    char path1[5000] = "\0";
    char path2[5000] = "\0";
    char store1[5000] = "\0";
    char *store2[300];
    struct stat s;
    if (len == 1)
    {
        sprintf(id, "%d", getpid());
    }
    else if (len == 2)
    {
        strcpy(id, command[1]);
    }
    else
    {
        strcat(id, command[1]);
        bold_red();
        printf("Error : ");
        reset();
        printf("To many argument for pinfo\n");
        return 0;
    }
    strcpy(path1, "/proc/");
    strcat(path1, id);
    strcpy(path2, path1);
    strcat(path1, "/stat");
    strcat(path2, "/exe");
    int flag = stat(path1, &s);
    if (flag < 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Process does not exists\n");
        return 0;
    }
    printf("pid -- %s \n", id);
    int fd = open(path1, O_RDONLY);
    int readed = read(fd, store1, 5000);
    if (readed < 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Failed to read /proc/stat file\n");
        return 0;
    }
    close(fd);
    int i = 0;
    char *token = strtok(store1, " \n");
    while (token != NULL)
    {
        store2[i] = token;
        i++;
        token = strtok(NULL, "\t \n");
    }
    printf("Process Status -- %s\n", store2[2]);
    printf("memory -- %s Bytes\n", store2[22]);
    readlink(path2, buf, 300);
    struct passwd s1;
    s1 = get_user_name();
    strcpy(path2, "~");
    strcpy(path1, "/home/");
    strcat(path1, s1.pw_name);
    if (strcmp(buf, "\0"))
    {
        if (check_tilda(path1, buf, strlen(path1)))
        {
            int temp = 0;
            for (i = 0; i < strlen(buf); i++)
            {
                if ((buf[i] == '/'))
                {
                    temp++;
                    if (temp == 3)
                        break;
                }
            }
            temp = 1;
            for (int j = i; j < strlen(buf); j++)
            {
                path2[temp++] = buf[j];
            }
            printf("Executable Path -- %s\n", path2);
        }
        else
        {
            printf("Executable Path -- %s\n", buf);
        }
    }
    else
    {
        printf("Executable Path -- %s\n", store2[1]);
    }
    return 1;
}