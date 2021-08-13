#include "header.h"
#include "input.h"

char **redirect(char **args)
{
    int sig_flag = 1;
    int i = 0;
    int fd_in = dup(STDIN_FILENO);
    int fd_out = dup(STDOUT_FILENO);
    char in[200];
    char out[200];
    char outdir[200];

    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;

    for (i = 0; args[i] != NULL; i++)
    {
        //nothing lol :'>
    }
    int len = i;
    int fd1, fd2, fd3;

    for (i = 0; args[i] != NULL; i++)
    {

        if (!strcmp(args[i], "<"))
        {
            flag1 = 1;
            if (args[i + 1] != NULL)
            {
                strcpy(in, args[i + 1]);
            }
            else
            {
                bold_red();
                printf("Error : ");
                reset();
                printf("Failed to open the input_redirection file\n");
                return 0;
            }
        }
        else if (!(strcmp(args[i], ">")))
        {
            flag2 = 1;
            if (args[i + 1] != NULL)
            {
                strcpy(out, args[i + 1]);
            }
            else
            {
                bold_red();
                printf("Error : ");
                reset();
                printf("Failed to open the output_redirection file\n");
                return 0;
            }
        }
        else if (!strcmp(args[i], ">>"))
        {
            flag3 = 1;
            if (args[i + 1] != NULL)
            {
                strcpy(outdir, args[i + 1]);
            }
            else
            {
                bold_red();
                printf("Error : ");
                reset();
                printf("Failed to open the output_redirection file\n");
                return 0;
            }
        }
    }

    if (!flag1 && !flag2 && !flag3)
        return args;

    if (flag1)
    {

        fd1 = open(in, O_RDONLY, 0);

        if (fd1 < 0)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Failed to open the input_redirection file\n");
            return NULL;
        }

        dup2(fd1, 0);
        close(fd1);
    }

    if (flag2)
    {
        fd2 = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd2 < 0)
        {

            bold_red();
            printf("Error : ");
            reset();
            printf("failed to open the output_redirection file\n");
            return NULL;
        }

        dup2(fd2, 1);
        close(fd2);
    }

    if (flag3)
    {
        fd3 = open(outdir, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd3 < 0)
        {

            bold_red();
            printf("Error : ");
            reset();
            printf("Failed to open the output_redirection file\n");
            return NULL;
        }

        dup2(fd3, 1);
        close(fd3);
    }
    for (int k = 0; k < len; k++)
    {
        if (!strcmp(args[k], "<") || !strcmp(args[k], ">>") || !strcmp(args[k], ">"))
        {
            for (int j = k + 2; j < len; j++)
            {
                args[j - 2] = args[j];
            }
            len = len - 2;
            args[len] = NULL;
        }
    }
    char str[200] = "\0";
    for (i = 0; args[i] != NULL; i++)
    {
        strcat(str, args[i]);
        strcat(str, " ");
    }
    sig_flag = dirct_command(args, i, str);
    if (flag3)
    {
        close(fd3);
    }
    if (flag2)
    {
        close(fd2);
    }
    if (flag1)
    {
        close(fd1);
    }
    if (flag1)
    {
        dup2(fd_in, STDIN_FILENO);
    }
    if (flag3 || flag2)
    {
        dup2(fd_out, STDOUT_FILENO);
    }
    if (!sig_flag)
    {
        return NULL;
    }
    else
    {
        return args;
    }
}