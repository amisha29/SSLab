%{
    #include<stdio.h>
    #include "y.tab.h"
%}

letter  [a-zA-Z]
digit   [0-9]

%%
{letter}({letter}|{digit}|"_")*     return ID;
{digit}+                            {yylval  = atoi(yytext); return NUM;}
\n                                return NEWLINE;
.                                   return yytext[0];
%%