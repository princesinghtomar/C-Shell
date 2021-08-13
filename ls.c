#include "header.h"
#include "input.h"

void print_time(char *str)
{
    char strin[30] = "\0";
    int i = 0;
    for (i = 4; i < 16; i++)
    {
        strin[i - 4] = str[i];
    }
    strin[i - 4] = '\0';
    printf("%s ", strin);
    return;
}

int implement_ls(DIR *dr, int flag, char directory[200], char command_string[200])
{
    struct dirent *s;
    struct stat s1;
    struct passwd *passw;
    int total = 0;
    if (!flag)
    {
        s = readdir(dr);
        char str[200] = "\0";
        while (s != NULL)
        {
            strcpy(str, s->d_name);
            if (str[0] != '.')
            {
                printf("%s\n", s->d_name);
            }
            s = readdir(dr);
        }
    }
    if (flag == 2)
    {
        s = readdir(dr);
        while (s != NULL)
        {
            printf("%s\n", s->d_name);
            s = readdir(dr);
        }
    }
    if (flag == 1)
    {
        total = 0;
        s = readdir(dr);
        printf(" ");
        while (s != NULL)
        {
            char str[405] = "\0";
            strcpy(str, directory);
            strcat(str, "/");
            char str1[200] = "\0";
            strcpy(str1, s->d_name);
            strcat(str, str1);
            if (str1[0] != '.')
            {
                int val = stat(str, &s1);
                if (val < 0)
                {
                    bold_red();
                    printf("Error : ");
                    reset();
                    printf("Failed to read stat of the file %s\n", str);
                    return 0;
                }
                total += s1.st_blocks / 2;
                printf("\r%c", S_ISDIR(s1.st_mode) ? 'd' : '-');
                printf("%c", s1.st_mode & S_IRUSR ? 'r' : '-');
                printf("%c", s1.st_mode & S_IWUSR ? 'w' : '-');
                printf("%c", s1.st_mode & S_IXUSR ? 'x' : '-');
                printf("%c", s1.st_mode & S_IRGRP ? 'r' : '-');
                printf("%c", s1.st_mode & S_IWGRP ? 'w' : '-');
                printf("%c", s1.st_mode & S_IXGRP ? 'x' : '-');
                printf("%c", s1.st_mode & S_IROTH ? 'r' : '-');
                printf("%c", s1.st_mode & S_IWOTH ? 'w' : '-');
                printf("%s", s1.st_mode & S_IXOTH ? "x " : "- ");
                printf("%3ld ", s1.st_nlink);
                passw = getpwuid(s1.st_uid);
                printf("%9s ", passw->pw_name);
                printf("%9s ", getgrgid(s1.st_gid)->gr_name);
                printf("%9ld ", s1.st_size);
                print_time(ctime(&s1.st_mtime));
                printf("%s\n", str1);
            }
            s = readdir(dr);
        }
        printf("Total : %d", total);
        printf("\n");
    }
    if (flag == 3)
    {
        total = 0;
        s = readdir(dr);
        printf(" ");
        while (s != NULL)
        {
            char str[405] = "\0";
            strcpy(str, directory);
            strcat(str, "/");
            strcat(str, s->d_name);
            if (stat(str, &s1) < 0)
            {
                bold_red();
                printf("Error : ");
                reset();
                printf("Failed to read stat of the file %s\n", str);
                return 0;
            }
            total += s1.st_blocks / 2;
            printf("\r%c", S_ISDIR(s1.st_mode) ? 'd' : '-');
            printf("%c", s1.st_mode & S_IRUSR ? 'r' : '-');
            printf("%c", s1.st_mode & S_IWUSR ? 'w' : '-');
            printf("%c", s1.st_mode & S_IXUSR ? 'x' : '-');
            printf("%c", s1.st_mode & S_IRGRP ? 'r' : '-');
            printf("%c", s1.st_mode & S_IWGRP ? 'w' : '-');
            printf("%c", s1.st_mode & S_IXGRP ? 'x' : '-');
            printf("%c", s1.st_mode & S_IROTH ? 'r' : '-');
            printf("%c", s1.st_mode & S_IWOTH ? 'w' : '-');
            printf("%s", s1.st_mode & S_IXOTH ? "x " : "- ");
            printf("%3ld ", s1.st_nlink);
            passw = getpwuid(s1.st_uid);
            printf("%9s ", passw->pw_name);
            printf("%9s ", getgrgid(s1.st_gid)->gr_name);
            printf("%9ld ", s1.st_size);
            print_time(ctime(&s1.st_mtime));
            printf("%s\n", s->d_name);
            s = readdir(dr);
        }
        printf("Total : %d", total);
        printf("\n");
    }
    return 1;
}

int execute_ls_func(char *command[200], int len, char command_string[200])
{
    int sig_flag = 1;
    char dir_name[200][200];
    int dir_no = 0;
    int flag = 0;
    for (int i = 1; i < len; i++)
    {
        if (strcmp(command[i], "~") && command[i][0] != '-' && command[i][0] != '&')
        {
            strcpy(dir_name[dir_no], command[i]);
            dir_no++;
        }
        else
        {
            if (command[i][0] == '-' || !strcmp(command[i], "~"))
            {
                if (!strcmp(command[i], "-l"))
                {
                    if (!flag)
                        flag = 1;
                    else if (flag == 1)
                        ;
                    else if (flag == 2)
                        flag = 3;
                }
                if (!strcmp(command[i], "-a"))
                {
                    if (!flag)
                        flag = 2;
                    else if (flag == 2)
                        ;
                    else if (flag == 1)
                        flag = 3;
                }
                if (!strcmp(command[i], "-al"))
                    flag = 3;
                if (!strcmp(command[i], "-la"))
                    flag = 3;
                if (!strcmp(command[i], "~"))
                {
                    struct passwd s1;
                    s1 = get_user_name();
                    char path[200] = "/home/";
                    strcat(path, s1.pw_name);
                    strcpy(dir_name[dir_no], path);
                    dir_no++;
                }
            }
        }
    }
    if (dir_no == 0)
    {
        strcpy(dir_name[dir_no], ".");
        dir_no++;
    }
    for (int i = 0; i < dir_no; i++)
    {
        DIR *dr;
        dr = opendir(dir_name[i]);
        if (dr == NULL)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Directory \"%s\" not found\n", dir_name[i]);
            return 0;
        }
        else
        {
            if (dir_no != 1)
            {
                yellow();
                printf("%s :\n", dir_name[i]);
                reset();
            }
            sig_flag &= implement_ls(dr, flag, dir_name[i], command_string);
        }
    }
    return sig_flag;
}