%{
	#include <stdio.h>
	int count = 0;
%}

letter [a-zA-Z]
digit   [0-9]
id	[a-zA-Z_][a-zA-Z0-9_]*

%%
({letter}|"_")({letter}|{digit}|"_")*   {count++;}
.*      {;}
\n         {;}
%%

int main()
{
    yyin = fopen("x.txt", "r");
    yylex();
    printf("\nnum %d\n", count );
    return 0;
}

int yywrap(){
	return 1;
}