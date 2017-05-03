%{
    #include<stdio.h>
    extern int yylval;
    extern char* yytext;
%}

%token ID NUM NEWLINE
%left '+' '-'
%left '*' '/'

%%
entry : expr NEWLINE        {printf("\nValid expr");
                             return 0;}
        ;

expr    : expr '+' expr    
        | expr '-' expr    
        | expr '*' expr    
        | expr '/' expr    
        | '(' expr ')'     
        | NUM
        | ID                
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