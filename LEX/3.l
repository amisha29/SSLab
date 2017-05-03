%{
    #include<stdio.h>
    int top = -1, numOperators = -1, numOperands = -1, valid = 1;
    char operators[100], operands[10][10], stack[100];
%}

letter [a-zA-Z]
digit [0-9]
underscore [_]
%%
[({\[]  {char* val = strdup(yytext);    stack[++top] = val[0];}

"}"     {
            if(stack[top] != '{')
            { valid = 0;   return 0; }
            else
                top--;
        }

"]"     {
            if(stack[top] != '[')
            { valid = 0;   return 0; }
            else
                top--;
        }

")"     {
            if(stack[top] != '(')
            { valid = 0;   return 0; }
            else
                top--;
        }

[+\-*/] {char* val = strdup(yytext);operators[++numOperators] = val[0];}

{digit}+|({letter}|_)({letter}|_{digit}|_)*    {strcpy(operands[++numOperands], yytext);}
%%

int main()
{
    yyin = fopen("math.txt", "r");
    yylex();
    if(valid)
    {
        printf("\nnum of operands: %d\nnum of operators : %d ", numOperands, numOperators );
        if(numOperands - numOperators ==1)
        {
            printf("\nValid expression\n");
            printf("operators are : \n");
            for (int i = 0; i <= numOperators; i++)
                printf("\n%c",operators[i]);
            printf("operands are : \n");
            for (int i = 0; i <= numOperands; i++)
                printf("\n%s",operands[i]);
        }
        else
            printf("\ninvalid");
    }
}

int yywrap()
{
    return 1;
}