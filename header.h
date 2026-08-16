#ifndef head_h
#define head_h

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>

typedef struct
{
    int line;
    char tok[50];

    char *input_file_name;
    FILE *input_fp;

    char output_file_name[30];
    FILE *output_fp;
}Token;

typedef enum 
{
    FAILURE,
    SUCCESS
}status;

static char *res_keywords[] = { "const", "volatile", "extern", "auto", "register", "static", 
                         "signed", "unsigned", "short", "long", "double", "char", "int", "float", 
                         "struct", "enum", "union" ,"void", "typedef"}; //Total:19

static char *non_res_keywords[] = { "if", "else", "switch", "case", "goto", "lable", "default",
                                    "break", "continue", "for", "do", "while", "return", "sizeof"}; //Total:14

static char *directives[] = { "#include", "#define", "#if", "#endif", "#ifdef", "#ifndef", "#undef"}; //Total:7

static char *compound_operators[] = { "==", "!=", "|=", "&=", "^=", "<=", ">=", "+=", "-=", "*=", "/=", "%=", 
                                     "<<", ">>", "++", "--","->"}; //Total:17
static char operators[] = { '/', '*', '-', '+', '%', '=', '<', '>', '&', '!', '^', '|', '~', ','}; //Total:14
static char symbol[]    = { '(', ')', '{', '}', '[', ']', ':'}; //Total:7


status evaluate_arguments(int argc,char *argv[]);

status open_file(char *argv[],Token *token);

status scan(Token *token);

status preprocessor_scan(unsigned int ch,Token *token);
status comment_scan(unsigned int ch,Token *token);
status header_scan(unsigned int ch,Token *token);
status macro_scan(unsigned int ch,Token *token);

status word_scan(unsigned int ch,Token *token);

status is_operator(char ch,Token *token);
status is_compound_operator(char ch,Token *token);
status is_terminating_operator(char ch,Token *token);

status is_symbol(char ch,Token *token);

status is_numeric_constant(unsigned int ch,Token *token);

status is_character(char ch,Token *token);
status is_string_literal(unsigned int ch,Token *token);


#endif