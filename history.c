#include "header.h"
#include "input.h"

void restructure_history(int len, char path[500], char *buffer[200])
{
    remove(path);
    int fd = open(path, O_RDWR | O_CREAT, 0644);
    char str[201] = "\0";
    for (int j = (len - 20); j < len; j++)
    {
        strcpy(str, buffer[j]);
        strcat(str, "`");
        int val = write(fd, &str, strlen(str));
        if (val < 0)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Failed to write in .history.temp file\n");
            close(fd);
            return;
        }
    }
    return;
}

int check_history(char *command)
{
    struct passwd s1;
    s1 = get_user_name();
    char path[500] = "/home/";
    strcat(path, s1.pw_name);
    strcat(path, "/.history.temp");
    int fd = open(path, O_RDWR, 0644);
    if (fd < 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Can't open file of .history.temp \n");
        return 0;
    }
    char buf[4000];
    char *buffer[500];
    int i = 0;
    int v = read(fd, buf, 4000);
    if (v < 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Failed to read .history.temp File\n");
        return 0;
    }
    close(fd);
    char *token = strtok(buf, "`");
    while (token != NULL)
    {
        buffer[i] = token;
        i++;
        token = strtok(NULL, "`");
    }
    free(token);
    return strcmp(command, buffer[i - 1]);
}

void create_history(char *command)
{
    struct passwd s1;
    char str[200] = "\0";
    strcpy(str, command);
    s1 = get_user_name();
    char path[500] = "/home/";
    strcat(path, s1.pw_name);
    strcat(path, "/.history.temp");
    int fd = open(path, O_RDWR | O_APPEND);
    if (fd < 0)
    {
        int fd1 = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
        if (fd1 < 0)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Unable to create .history.temp file\n");
            return;
        }
        write(fd1, &str, strlen(str));
        write(fd1, "`", strlen("`"));
        close(fd1);
    }
    else if (check_history(command))
    {
        if (fd < 0)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Failed to opening .history.temp file\n");
            return;
        }
        write(fd, &str, strlen(str));
        write(fd, "`", strlen("`"));
        close(fd);
        fd = open(path, O_RDONLY);
        char buf[4000] = "\0";
        char *buffer[200];
        int i = 0;
        int v = read(fd, buf, 4000);
        if (v < 0)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Failed to reading .history.temp file\n");
            close(fd);
            return;
        }
        close(fd);
        char *token = strtok(buf, "`");
        while (token != NULL)
        {
            buffer[i] = token;
            i++;
            token = strtok(NULL, "`");
        }
        if (i > 20)
            restructure_history(i, path, buffer);
    }
    return;
}
int print_history(char *command[200], int len, char command_string[200])
{
    struct passwd s1;
    s1 = get_user_name();
    char path[500] = "/home/";
    strcat(path, s1.pw_name);
    strcat(path, "/.history.temp");
    int fd = open(path, O_RDWR, 0644);
    char buf[4000] = "\0";
    char *buffer[200];
    int i = 0, val = 0;
    int v = read(fd, buf, 4000);
    if (v < 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Failed to read .history.temp file\n");
        close(fd);
        return 0;
    }
    close(fd);
    char *token = strtok(buf, "`");
    while (token != NULL)
    {
        buffer[i] = token;
        i++;
        token = strtok(NULL, "`");
    }

    if (len > 2)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("History have more arguments than needed\n");
        return 0;
    }
    if (len == 1)
    {
        val = 10;
        int start = (i - val > 0) ? (i - val) : 0;
        for (int j = start; j < i; j++)
        {
            printf("%s\n", buffer[j]);
        }
    }
    if (len == 2)
    {
        val = atoi(command[1]);
        int start = (i - val > 0) ? (i - val) : 0;
        for (int j = start; j < i; j++)
        {
            printf("%s\n", buffer[j]);
        }
    }
    return 1;
}