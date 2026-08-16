#include "header.h" 

int main(int argc, char *argv[], char envp[])
{
    printf("Welcome to Lexical Analyzer\n\n");
    Token token;
      
    if( evaluate_arguments(argc,argv) )
    {
        if( open_file(argv,&token) )
        {
            if( scan(&token) )
            {
                printf("---------------------------------------------\n");
                printf("Data saved in Analysis_Report.txt\n");
                printf("Lexical Analysis completed\n\n");

                fprintf(token.output_fp,"---------------------------------------------\n");
                
                fclose(token.input_fp);
                fclose(token.output_fp);
            }
            else
                printf("Lexical Analysis failed\n");
        }
        else
            printf("open_files failed\n");
    }
    return SUCCESS;
}