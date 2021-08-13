#include "header.h"
#include "input.h"

int handle_pipe(char *commands, int len)
{
    int sig_flag = 1;
    int fd_flag = 1;
    int i = 0;
    int status;
    char usr_name[200] = "/home/";
    struct passwd pw;
    pw = get_user_name();
    strcat(usr_name, pw.pw_name);
    strcat(usr_name, "/.for_child_to_parent.temp");
    int **pipes = (int **)calloc(sizeof(int *) * 2, 1);
    pipes[0] = (int *)calloc(sizeof(int) * 2, 1);
    pipes[1] = (int *)calloc(sizeof(int) * 2, 1);
    int fd1 = open(usr_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
    int fd2 = open(usr_name, O_RDWR);
    if (fd1 < 0 || fd2 < 0)
    {
        fd_flag = 0;
    }
    char *token = strtok(commands, "|");
    char *temp[200];
    i = 0;
    while (token != NULL)
    {
        temp[i] = token;
        token = strtok(NULL, "|");
        i++;
    }
    i = 0;
    while (len > i)
    {
        char *cmd = temp[i];
        if (temp[i] == NULL || !strcmp(temp[i], ""))
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Syntax is not correct\n");
            return 0;
        }
        if (pipe(pipes[(i & 1)]) == -1)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Failed to pipe\n");
            return 0;
        }
        char cmd2[200] = "\0";
        strcpy(cmd2, cmd);

        pid_t pid = fork();

        if (pid < 0)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Failed to fork a child process\n");
            return 0;
        }
        else if (pid == 0)
        {

            if (!i)
            {
                dup2(pipes[0][1], STDOUT_FILENO);
            }
            else if (i != len - 1)
            {
                dup2(pipes[i & 1][1], STDOUT_FILENO);
                dup2(pipes[((i + 1) & 1)][0], STDIN_FILENO);
            }
            else
            {
                dup2(pipes[((i + 1) & 1)][0], STDIN_FILENO);
            }

            sig_flag = dist_command_2(cmd2);

            char buffer[5] = "\0";
            sprintf(buffer, "%d", sig_flag);
            if (fd_flag && i == len - 1)
            {
                write(fd1, buffer, 5);
            }
            close(fd1);
            
            exit(EXIT_SUCCESS);
        }
        else
        {
            int value20 = waitpid(pid, &status, 0);
            if (value20 < 0)
            {
                bold_red();
                printf("Error : ");
                reset();
                printf("Failed to wait for child process\n");
                return 0;
            }
            char buf[5] = "\0";
            if (fd_flag)
            {
                read(fd2, buf, 5);
            }
            char *token = strtok(buf, " \n\t");
            if (token != NULL)
            {
                sig_flag = atoi(token);
                token = strtok(NULL, " \n\t");
            }
            else
            {
                sig_flag = atoi(buf);
            }

            if (!i)
            {
                close(pipes[0][1]);
            }
            else if (i != len - 1)
            {
                close(pipes[i & 1][1]);
                close(pipes[((i + 1) & 1)][0]);
            }
            else
            {
                close(pipes[((i + 1) & 1)][0]);
            }
            i++;
        }
    }
    close(fd1);
    close(fd2);
    remove(usr_name);
    free(token);
    free(pipes[1]);
    free(pipes[2]);
    free(pipes);
    return sig_flag;
}
