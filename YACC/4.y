%{
    #include<stdio.h>
    extern char* yytext;
    int aCount = 0, bCount = 0;
%}

%token A B NEWLINE

%%
S   :   C D NEWLINE     { if(aCount > 0 && bCount > 0)
                                printf("\nValid\n");
                            return 0;}

C   :   A C             {aCount++;}
        |A              {aCount++;}
        ;

D   :   B D             {bCount++;}
        |B              {bCount++;}
        ;
        
%%

int main(){
    printf("\nEnter string : \n");
    if(!yyparse())
        printf("\nparse successful");
    else
        printf("\nunsuccessful");
}

int yywrap(){
	return 1;
}

int yyerror(char* s){
	printf("Invalid identifier! Cause: %s\n",yytext);
}