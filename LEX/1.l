%{#include<stdio.h>
int chars = 0;
int words = 0;
int spaces = 0;
int lines = 0;
%}

%%
[^ \n\t]+ {words++;   chars += yyleng;}
\n          {lines++;}
[ ]         {spaces++;}
%%

int main()
{
    yyin=fopen("input.txt", "r");
    yylex();
    printf("\nWords : %d\nChars : %d\nLines: %d\nSpaces: %d", words, chars, lines, spaces);
    return 0;
}

int yywrap(void)
{
    return 1;
}