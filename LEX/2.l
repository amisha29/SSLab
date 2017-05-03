%{
#include<stdio.h>
int count = 0;
%}

%%
\/\*[^\*]*\*\/      {count++;}
\/\/.*              {count++;}
(.|\n)              {;}
%%

int main()
{
    yyin = fopen("input.c", "r");
    yylex();
    printf("\nNum of comment lines : %d\n", count);
}

int yywrap()
{
    return 1;
}