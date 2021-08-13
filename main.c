#include "header.h"
#include "input.h"

struct passwd get_user_name()
{
    uid_t uid = geteuid();
    struct passwd *passw = getpwuid(uid);
    return *passw;
}

int check_tilda(char *str1, char *str2, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (str1[i] != str2[i])
        {
            return 0;
        }
    }
    return 1;
}

void sig_stp_handle(int s)
{
    pid_t pid = getpid();
    kill(pid, SIGSTOP);
    return;
}

void sig_handle(int val)
{
    //lol kya kare iss function k :D
}

int main()
{
    signal(SIGINT, sig_handle);
    signal(SIGTSTP, sig_handle);
    //signal(SIGCHLD, check_process);
    int sig_flag = 1;
    child_process = 1;
    strcpy(prev_dir, "\0");
    struct utsname s;
    struct passwd s1;
    char command[3000] = "\0";
    strcpy(com_str, "\0");
    char usr[200] = "\0";
    char sys_name[200] = "\0";
    char cw_d[4096] = "/home/";
    char pw_d[4096] = "~";
    s1 = get_user_name();
    strcpy(usr, s1.pw_name);
    uname(&s);
    strcpy(sys_name, s.nodename);
    strcat(cw_d, usr);
    int length = strlen(usr) + strlen("/home/");
    char str1[length];
    strcpy(str1, cw_d);
    int temp = chdir(cw_d);
    int flag_out = 1;
    if (temp < 0)
    {
        printf("Error\n");
    }
    strcpy(prev_dir, cw_d);
    if (temp < 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Failed to change directory to ~\n");
        return 0;
    }
    p_pid[0] = getpid();
    while (flag_out)
    {
        getcwd(cw_d, 4096);
        if (check_tilda(str1, cw_d, length))
        {
            for (int i = 0; i < strlen(cw_d); i++)
            {
                pw_d[i + 1] = cw_d[length + i];
            }
            printf("<%s@%s:%s>", usr, sys_name, pw_d);
        }
        else
        {
            printf("<%s@%s:%s>", usr, sys_name, cw_d);
        }
        if (fgets(command, sizeof command, stdin))
        {
            command[strcspn(command, "\n")] = 0;
            strcpy(com_str, command);
            create_history(command);
            if (!strcmp(command, "exit") || !strcmp(command, "quit"))
            {
                break;
            }
            else
            {
                sig_flag = and_n_or(command);
            }
            if (sig_flag)
            {
                printf(":')");
            }
            else
            {
                printf(":'(");
            }
        }
        else
        {
            if (feof(stdin))
            {
                printf("\n");
                flag_out = 0;
                return 0;
            }
            else
                printf("Error : In reading the command, Please Enter the command again\n");
        }
    }
    return 0;
}
