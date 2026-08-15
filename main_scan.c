#include "header.h"

status evaluate_arguments(char *argv[])
{
    if( argv[1] && !argv[2])
    {
        if(argv[1][0] == '.')
            goto error;

        if(!strstr(argv[1],".c"))
            goto error;

        if( *(strstr(argv[1],".c")+2) != '\0' )
            goto error;
        
        int i=0,count=0;
        while( argv[1][i] )
        {
            if(argv[1][i++] == '.') count++;
            if (count==2) goto error;
        }

        return SUCCESS;

        error:
        printf("Invalid CLA Input\nFollow: ./a.out input_file.c\n");
        return FAILURE;
    }
    else
    {
        printf("Argument Evaluation is Failed\n");
        return FAILURE;
    }
}

status open_file(char *argv[],Token *token)
{
    strcpy(token->input_file_name,argv[1]);
    
    token->input_fp = fopen(token->input_file_name,"r+");
    if(!(token->input_file_name))
    {
        printf("Memory Allocation Failed-1\n");
        return FAILURE;
    }
    printf("Entered File Name: %s\n",token->input_file_name);

    strcpy(token->output_file_name,"Analysis_Report.text");
    token->output_fp = fopen(token->output_file_name,"w+");
    if(!(token->output_file_name))
    {
        printf("Memory Allocation Failed-2\n");
        return FAILURE;
    }
    printf("Output File Name: %s\n\n",token->output_file_name);
    return SUCCESS;
}

status scan(Token *token)
{
    printf("---------------------------------------------\n");
    printf("%-10s %-15s %s\n","Line No","Token","Token Type");
    printf("---------------------------------------------\n");

    fprintf(token->output_fp,"---------------------------------------------\n");
    fprintf(token->output_fp,"%-10s %-15s %s\n","Line No","Token","Token Type");
    fprintf(token->output_fp,"---------------------------------------------\n");

    unsigned int ch;
    token->line =1;
    token->error=0;
    while(1)
    {
        ch=fgetc(token->input_fp);
        
        if(ch=='\r') 
            ch=fgetc(token->input_fp);
        
        if(ch=='\n')
            (token->line)++;
        
        while(ch==' ' || ch=='\n' || ch=='\t')
        {
            ch=fgetc(token->input_fp);
            if(ch=='\n') 
                (token->line)++;
        }
        // printf("%d:%c\n",ch,ch);
        if( ch=='#' || ch=='/' )
        {

            if(preprocessor_scan(ch,token))
                continue;
            else
                return FAILURE;
        }
        else if( ((ch >='a') && (ch <='z')) || ((ch >='A') && (ch <='Z')) || ch=='_' )
        {   
            if(word_scan(ch,token))
                continue;
            else
                return FAILURE;
        }
        else if( is_symbol(ch,token) )
        {
            if ( (ch=='(') || (ch=='{'))
            {
                printf("%-10d %-15c : OPEN_BRACE\n",token->line,ch);
                fprintf(token->output_fp,"%-10d %-15c : OPEN_BRACE\n",token->line,ch);
            }
            else if( (ch==')') || (ch=='}') )
            {
                printf("%-10d %-15c : CLOSE_BRACE\n",token->line,ch);
                fprintf(token->output_fp,"%-10d %-15c : CLOSE_BRACE\n",token->line,ch);
            }
            else
            {
                printf("%-10d %-15c : SYMBOL\n",token->line,ch);
                fprintf(token->output_fp,"%-10d %-15c : CLOSE_BRACKET\n",token->line,ch);
            }
            continue;
        }
        else if( is_operator(ch,token) )
        {   
            if( is_compound_operator(ch,token) )
            {
                printf("%-10d %-15s : COMPOUND OPERATOR\n",token->line,token->tok);
                fprintf(token->output_fp,"%-10d %-15s : COMPOUND OPERATOR\n",token->line,token->tok);
            }
            else
            {
                printf("%-10d %-15c : OPERATOR\n",token->line,ch);
                fprintf(token->output_fp,"%-10d %-15c : OPERATOR\n",token->line,ch);
            }
            continue;
        }
        else if( is_numeric_constant(ch,token) )
        {
            continue;
        }
        else if( is_string_literal(ch,token) )
        {
            continue;
        }
        else if(ch==';')
        {
            printf("%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
            fprintf(token->output_fp,"%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
            while( (ch=fgetc(token->input_fp))!='\n' );
            (token->line)++;
            continue;
        }
        else if(ch == EOF)
            break;
    }
    return SUCCESS;
}