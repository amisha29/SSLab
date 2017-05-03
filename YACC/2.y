%{
    #include<stdio.h>
    extern char* yytext;
%}

%token LETTER DIGIT NEWLINE;
%left '*' '/'
%left '+' '-'

%%
id  :   header body NEWLINE     {printf("\nvalid"); return 0;}
        ;
header  :   LETTER
            ;
body    :   LETTER body
            |DIGIT body
            |DIGIT
            |LETTER
            ;        
%%

int main()
{
    printf("\nenter expression : ");
    if(!yyparse())
        printf("\nparse completed");
    else
        printf("\nparse failed");
}

int yywrap(){
	return 1;
}

int yyerror(char* s){
	printf("Invalid identifier! Cause: %s\n",yytext);
}