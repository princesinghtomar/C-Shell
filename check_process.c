#include "header.h"
#include "input.h"

void check_process()
{
    int status;
    pid_t pid;
    pid = waitpid(-1, &status, WNOHANG);
    int flag1 = 0;
    if (pid >= 0)
        for (int i = 1; i <= child_process; i++)
        {
            if (pid == p_pid[i])
            {
                {
                    if (i != child_process && p_pid[i] != 0)
                    {
                        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
                        {
                            green();
                            printf("\n[%d]-  %8s %7d exited Successfully\n", i, p_name[i], pid);
                            reset();
                        }
                        else if (WIFSIGNALED(status))
                        {
                            red();
                            printf("\n[%d]-  %8s %7d exited abnormally\n", i, p_name[i], pid);
                            reset();
                        }
                    }
                }
                p_pid[i] = 0;
                flag1++;
            }
        }
    else
        return;
    return;
}