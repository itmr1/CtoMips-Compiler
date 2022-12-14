%option noyywrap

%{
/* Now in a section of C that will be embedded
   into the auto-generated code. Flex will not
   try to interpret code surrounded by %{ ... %} */

/* Bring in our declarations for token types and
   the yylval variable. */

// This is to work around an irritating bug in Flex
// https://stackoverflow.com/questions/46213840/get-rid-of-warning-implicit-declaration-of-function-fileno-in-flex
extern "C" int fileno(FILE *stream);

/* End the embedded code section. */
#include "c_parser.tab.hpp"
#include <string>
%}


%%

"int"             {return VARTYPE_INT;}
"while"           { return TOK_WHILE; }
"for"             {return TOK_FOR; }
"if"              { return TOK_IF; }
"else"            { return TOK_ELSE; }
"return"          {return TOK_RETURN;}
"break"           {return TOK_BREAK;} 
"continue"        {return TOK_CONT;}  
"case"            {return TOK_CASE;}
"default"         {return TOK_DEFAULT;}
"switch"          {return TOK_SWITCH;}

[0-9]+                   {yylval.number = std::strtod(yytext,0);
                           return TOK_N;}

[a-zA-Z0-9]+                  {yylval.string = new std::string(yytext); 
                           return TOK_VAR;}

[*]               { return TOK_MUL; }
[\/]              { return TOK_DIVIDE;}
[\%]              { return TOK_MOD; }
[+]               { return TOK_PLUS; }
[-]               { return TOK_MINUS; }

"*="              {return TOK_MULASSIGN; }
"/="              {return TOK_DIVASSIGN; }
"+="              {return TOK_ADDASSIGN; }
"-="              {return TOK_SUBASSIGN; }
"%="              {return TOK_MODASSIGN; }
"="               {return TOK_EQASSIGN; }
"&="              {return TOK_ANDASSIGN;}
"|="              {return TOK_ORASSIGN;}
"\^="             {return TOK_XORASSIGN;}

"=="              { return TOK_EQ; }
"!="              { return TOK_NEQ; }
"<="              { return TOK_LE; }
">="              { return TOK_GE; }
">"               { return TOK_G; }
"<"               { return TOK_L; }

"<<"              { return TOK_LSHIFT; }
">>"              { return TOK_RSHIFT;}

[&]               { return TOK_BIT_AND; }
[|]               { return TOK_BIT_OR; }
[~]               { return TOK_BIT_NOT; }
[\^]               { return TOK_BIT_XOR; }

[!]               { return TOK_LOGIC_NOT; }
"&&"              { return TOK_LOGIC_AND; }
"||"              { return TOK_LOGIC_OR; }
"++"              { return TOK_INCR; }
"--"              { return TOK_DECR;}


[\[]              { return TOK_LSQBRACKET;}
[\]]              { return TOK_RSQBRACKET;}
[(]               { return TOK_LBRACKET; }
[)]               { return TOK_RBRACKET; }
[\{]              { return TOK_LCBRACKET; }
[\}]              { return TOK_RCBRACKET; }
[;]               { return TOK_SEMICOLON; }
[,]               { return TOK_COMMA;}
[?]               {return TOK_QMARK;}
[:]               {return TOK_COLON;}
      
[ \t\r\n]+        {;}
. {fprintf(stderr, "Invalid token\n");exit(1);}


%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}
