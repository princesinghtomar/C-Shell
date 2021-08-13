#include "header.h"
#include "input.h"

int jobs(int len)
{
    if(len!=1){
        bold_red();
        printf("Error : ");
        reset();
        printf("Invalid input\n");
        return 0;
    }
    for (int i = 1; i <= child_process; i++)
    {
        char str[500] = "\0";
        sprintf(str, "/proc/%d/stat", p_pid[i]);
        char buf[100] = "\0";
        int fd = open(str, O_RDONLY);
        int val = read(fd, buf, 100);
        close(fd);
        if (val < 0)
        {
            continue;
        }
        char *token = strtok(buf, " \t");
        char *btr[200];
        int j = 0;
        while (token != NULL)
        {
            btr[j] = token;
            token = strtok(NULL, " \t");
            j++;
        }
        char status_string[100] = "\0";
        int print_flag = 0;
        if (!strcmp(btr[2], "T"))
        {
            strcpy(status_string, "Stopped");
            print_flag++;
        }
        else if (!strcmp(btr[2], "R") || !strcmp(btr[2], "S"))
        {
            strcpy(status_string, "Running");
            print_flag++;
        }
        if (print_flag)
        {
            printf("[%d] %s %s [%d]\n", i, status_string, p_name[i], p_pid[i]);
        }
    }
    return 1;
}

int kjob(char **str, int len, char *command_string)
{
    if (len < 3)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Invalid input\n");
        return 0;
    }
    if (len > 3)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Invalid input\n");
        return 0;
    }
    int index = atoi(str[1]);
    if (index <= 0 || index >= child_process)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("No such process with index no. %s\n", str[1]);
        return 0;
    }
    pid_t pid = p_pid[index];
    int sig_number = atoi(str[2]);
    if (sig_number < 1 || sig_number > 31)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Invalid signal number\n");
        return 0;
    }
    if (sig_number == 9)
    {
        kill(pid, SIGKILL);
    }
    else
    {
        kill(pid, sig_number);
    }
    return 1;
}

int overkill(char **str, int len, char *command_string)
{
    if (len != 1)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Irrelevant arguments for overkill function\n");
        return 0;
    }
    for (int i = 1; i <= child_process; i++)
    {
        int status;
        if (p_pid[i] > 0)
        {
            signal(SIGCHLD, SIG_IGN); //disabling sig_child interrupt
            kill(p_pid[i], SIGTERM);
            usleep(500); // will give 500 msec to die
            waitpid(p_pid[i], &status, WNOHANG);
            kill(p_pid[i], SIGKILL);
            signal(SIGCHLD, check_process); //inabling sigchild interrupt
        }
    }
    child_process = 1;
    return 1;
}

int fg(char **command, int len, char *command_string)
{
    int st;
    if (len < 2)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Check your arguments\n");
        return 0;
    }
    int job_index = atoi(command[1]);
    if (len > 2)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Check your arguments\n");
        return 0;
    }
    if (job_index >= child_process || job_index <= 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Enter valid job index\n");
        return 0;
    }
    pid_t job_pid = p_pid[job_index];
    if (!job_pid)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Enter valid job index\n");
        return 0;
    }
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    previous_process = p_pid[0];
    p_pid[0] = job_pid;
    tcsetpgrp(0, p_pid[0]);
    kill(p_pid[0], SIGCONT);

    int val = waitpid(p_pid[0], &st, WUNTRACED);

    if (val < 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Failed to wait\n");
        return 0;
    }
    tcsetpgrp(0, getpgrp());
    p_pid[job_index] = 0;
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    /*
    //pendingIDs[jobn - 1] = 0;

    // similar to that of process.c, if we get ctrl z
    */
    if (WIFSTOPPED(st))
    {
        p_pid[child_process] = p_pid[0];
        strcpy(p_name[child_process], p_name[job_index]);
        child_process++;
        return 0;
    }
    return 1;
}

int bg(char **command, int len, char *command_string)
{
    if (len < 2)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Check your arguments\n");
        return 0;
    }
    int job_index = atoi(command[1]);
    if (len > 2)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Check your arguments\n");
        return 0;
    }
    if (job_index >= child_process || job_index <= 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Enter valid job index\n");
        return 0;
    }
    pid_t job_pid = p_pid[job_index];
    if (!job_pid)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Enter valid job index\n");
        return 0;
    }
    kill(job_pid, SIGTTIN);
    kill(job_pid, SIGCONT);
    return 1;
}
