#include "header.h"

int main(int argc, char *argv[], char envp[])
{
    printf("Welcome to Lexical Analyzer\n\n");
    Token token;

    if( evaluate_arguments(argv) )
    {
        if( open_file(argv,&token) )
        {
            if( scan(&token) )
            {
                printf("Lexical Analysis completed\n\n");
            }
            else
            {
                printf("Lexical Analysis failed\n");
            }
        }
        else
        {
            printf("open_files failed\n");
        }
    }
    else
    {
        printf("evaluate_arguments Failed\n");
    }

    printf("---------------------------------------------\n");
    printf("Data saved in Analysis_Report.txt\n");
    fprintf(token.output_fp,"---------------------------------------------\n");
    return SUCCESS;
}