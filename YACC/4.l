%{
    #include<stdio.h>
    #include "y.tab.h"
%}


%%
[a]     return A;
[b]     return B;
\n      return NEWLINE;
.       return yytext[0];
%%