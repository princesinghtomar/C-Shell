#include "header.h"
#include "input.h"

void mode1()
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    return;
}

void mode2()
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    return;
}

int getkey()
{
    int bytes;
    mode1();
    ioctl(STDIN_FILENO, FIONREAD, &bytes);
    int ans = bytes > 0 ? 1 : 0;
    mode2();
    return ans;
}

int get_interrupt(int flag)
{
    char str[200] = "/proc/interrupts";
    int fd = open(str, O_RDONLY);
    if (fd < 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Failed to open /proc/interrupts file\n");
        return 0;
    }
    char buf[1000];
    char *s[200];
    int val = read(fd, buf, 1000);
    if (val < 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Failed to read /proc/interrupts\n");
        close(fd);
        return 0;
    }
    int i = 0;
    char *token = strtok(buf, " \n");
    while (token != NULL)
    {
        s[i] = token;
        i++;
        token = strtok(NULL, " \n");
    }
    free(token);
    if (!flag)
    {
        for (int i = 0; i < 8; i++)
        {
            yellow();
            printf("\t%s", s[i]);
            reset();
        }
        printf("\n");
    }
    for (int i = 21; i < 29; i++)
    {
        blue();
        printf("\t%s", s[i]);
        reset();
    }
    printf("\n");
    close(fd);
    return 1;
}

int get_newborn()
{
    char str[40] = "/proc/loadavg";
    char buf[100] = "\0";
    int fd = open(str, O_RDONLY);
    if (fd < 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Failed to open /proc/loadavg \n");
        return 0;
    }
    int val = read(fd, buf, 100);
    close(fd);
    if (val < 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Failed to read /proc/loadavg file\n");
        return 0;
    }
    int i = 0;
    char *s[20];
    char *token = strtok(buf, " \n");
    while (token != NULL)
    {
        s[i] = token;
        i++;
        token = strtok(NULL, " \n");
    }
    free(token);
    printf("%s\n", s[4]);
    return 1;
}

int nightswatch(char *command[200], int len, char command_string[200])
{
    int n, flag = 3, f = 0;
    if (len < 4)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Less arguments than needed\n");
        return 0;
    }
    else
    {
        if (!strcmp(command[1], "-n"))
        {
            n = atoi(command[2]);
        }
        else
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Please give correct inputs\n");
            return 0;
        }
    }
    if (!strcmp(command[3], "newborn"))
        flag = 1;
    else if (!strcmp(command[3], "interrupt"))
        flag = 2;
    else
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("You have entered wrong command\n");
        return 0;
    }
    clock_t last = clock();
    while (1)
    {
        clock_t current = clock();
        if (current >= (last + n * CLOCKS_PER_SEC))
        {
            if (flag == 2)
            {
                get_interrupt(f);
                f = 1;
            }
            else if (flag == 1)
            {
                get_newborn();
            }
            last = current;
        }
        if (getkey())
        {
            if (getchar() == 'q')
            {
                printf("\n");
                return 1;
            }
        }
    }
}