#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "mp_definitions.c"

void shortCircuitDemo()
{
    if (true || printf("123 - I will not get called.\n"))
        printf("ABC - Hi!\n");

    if (false || printf("456 - I will get called.\n"))
        printf("DEF - Hello!\n");

    if (false && printf("789 - I will not get called.\n"))
        printf("GHI - Bye!\n");

    if (true && printf("101 - I will get called.\n"))
        printf("JKL - Bello!\n");
}


void progressBarIdeaDemo()
{
    system("cls");
    printf("Standard:");
    printf("\n\t[" BACK_RED "               " COLOR_RESET "]\n\n");
    printf("Standard, text overlay:");
    printf("\n\t[" BACK_RED "  Inoffensive  " COLOR_RESET "]\n\n");
    printf("Vertical:");
    printf("\n\t[" FORE_RED "|||||||||||||||" COLOR_RESET "]\n\n");
    printf("Diagonal:");
    printf("\n\t[" FORE_RED "///////////////" COLOR_RESET "]\n\n");
    printf("Horizontal:");
    printf("\n\t[" FORE_RED "---------------" COLOR_RESET "]\n\n");
    printf("Hashy:");
    printf("\n\t[" FORE_RED "###############" COLOR_RESET "]\n\n");
    printf("Boxy:");
    printf("\n\t[" FORE_RED "][][][][][][][]" COLOR_RESET "]\n\n");
    printf("Dotty:");
    printf("\n\t[" FORE_RED ":::::::::::::::" COLOR_RESET "]\n\n");
    printf("Dotty Precise:");
    printf("\n\t[" FORE_RED "::::::.        " COLOR_RESET "]\n\n");
}

int timesTwo(int n)
{
    return n * 2;
}

void plusTwoPointers(int *p)
{
    *p = *p + 3;
}

int main()
{
    system("cls");


    int nProduct = timesTwo(2);

    int nSum = 5;
    plusTwoPointers(&nSum);

    printf("nProduct = %d; nSum = %d", nProduct, nSum);
    return 0;
}

