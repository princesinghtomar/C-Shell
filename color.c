#include "header.h"
#include "input.h"


void bold_green()
{
    printf("\033[1;32m");
}
void bold_blue()
{
    printf("\033[1;34m");
}
void bold_red()
{
    printf("\033[1;31m");
}
void bold_yellow()
{
    printf("\033[1;33m");
}
void yellow()
{
    printf("\033[0;33m");
}
void red()
{
    printf("\033[0;31m");
}
void green()
{
    printf("\033[0;32m");
}
void blue()
{
    printf("\033[0;34m");
}
void reset()
{
    printf("\033[0m");
}
