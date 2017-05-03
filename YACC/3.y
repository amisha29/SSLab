%{
    #include<stdio.h>
    extern int yylval;
    extern char* yytext;
    int flag = 1;
%}

%token ID NUM NEWLINE
%left '+' '-'
%left '*' '/'

%%
entry : expr NEWLINE        {printf("\nValid expr");
                             if(flag) printf("\nValue : %d\n", $1);
                             return 0;}
        ;

expr    : expr '+' expr    {$$ = $1 + $3;}
        | expr '-' expr    {$$ = $1 - $3;}
        | expr '*' expr    {$$ = $1 * $3;}
        | expr '/' expr    {$$ = $1 / $3;}
        | '(' expr ')'     {$$ = $2;}
        | NUM
        | ID                {flag = 0;}
        ;
%%

int main() {
    printf("\nEnter expression : ");
    if(!yyparse())
        printf("\nParse complete");
    else
        printf("Parse fail");
}

int yywrap() {
    return 1;
}

int yyerror(char* s)
{
    printf("%s, cause: %s\n", s, yytext);
}