#include "header.h"  

status preprocessor_scan(unsigned int ch,Token *token)
{
    int i=0,j=0;
    token->tok[i++]=ch;

    if( ch =='#' )
    {
        ch=fgetc(token->input_fp);
        while( (ch != ' ') && (ch != '\n') && (ch != '\r') && (ch != '<') && (ch != '"') )
        {
            token->tok[i++]=ch;
            ch=fgetc(token->input_fp);
        }
        token->tok[i]='\0';

        for(j=0; j<7 ; j++)
        {
            if( strcmp(token->tok,directives[j]) == 0)
            {
                printf("%-10d %-15s : PRE-PROCESSOR\n",token->line,token->tok);
                fprintf(token->output_fp,"%-10d %-15s : PRE-PROCESSOR\n",token->line,token->tok);
                break;
            }
        }

        if(ch == ' ')
            while((ch=fgetc(token->input_fp)) == ' ');
        // printf("%d:%c\n",ch,ch);
        if( (ch=='<') || (ch=='"') )
            header_scan(ch,token);
        else if( ((ch >='a') && (ch <='z')) || (ch >='A') && (ch <='Z') )
            macro_scan(ch,token);
        else if( is_numeric_constant(ch,token) )
            return SUCCESS;
        else if(ch=='\n')
            (token->line)++;
        else if(ch==';')
        {
            printf("%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
            fprintf(token->output_fp,"%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
        }
        return SUCCESS;
    }
    else if( ch =='/' )
    {
        int i=0,j=0;
        token->tok[i++]=ch;

        ch=fgetc(token->input_fp);
        if(ch=='/')
        {
            while( (ch != '\n') && (ch != '\r'))
            {
                token->tok[i++]=ch;
                ch=fgetc(token->input_fp);
            }
            token->tok[i]='\0';

            printf("%-10d COMMENT: %s\n",token->line,token->tok);
            fprintf(token->output_fp,"%-10d COMMENT: %s\n",token->line,token->tok);

        }
        else if(ch=='*')
        {
            int flag=0;
            token->tok[i++]=ch;
            ch=fgetc(token->input_fp);
            token->tok[i++]=ch;  
            while( (ch != '/') && !flag)
            { 
                if(ch=='*') flag=1;
                else flag=0;  
                ch=fgetc(token->input_fp);
                token->tok[i++]=ch;             
            }
            token->tok[i]='\0';

            printf("%-10d MULTI-LINE COMMENT: %s\n",token->line,token->tok);
            fprintf(token->output_fp,"%-10d COMMENT: %s\n",token->line,token->tok);
        }

    }

}

status header_scan(unsigned int ch,Token *token)
{
    int i=0,flag=0;
    token->tok[i++]=ch;
    ch=fgetc(token->input_fp);
    while( (ch != '>') && (ch != '"') )
    {
        token->tok[i++]=ch;
        ch=fgetc(token->input_fp);
        if(ch=='\n')
        {
            (token->line)++;
            flag=1;
            break;
        }
        else if(ch==';')
        {
            printf("%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
            fprintf(token->output_fp,"%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
            while(ch=fgetc(token->input_fp)!='\n');
            (token->line)++;
            flag=1;
            break;
        }
    }
    if(flag)
    {
        (token->error)++;
        return SUCCESS;
    }
    else
    {
        token->tok[i++]=ch;
        token->tok[i]='\0';
        printf("%-10d %-15s : HEADER\n",token->line,token->tok);
        fprintf(token->output_fp,"%-10d %-15s : HEADER\n",token->line,token->tok);
    }
    
    ch=fgetc(token->input_fp);
    if(ch =='\r')
        ch=fgetc(token->input_fp);
    
    while( ch == ' ')
        ch=fgetc(token->input_fp);
    
    if(ch=='\n')
    {
        (token->line)++;
        return SUCCESS;
    }
    else if(ch==';')
    {
        printf("%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
        fprintf(token->output_fp,"%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
        while(ch=fgetc(token->input_fp)!='\n');
        (token->line)++;
        return SUCCESS;
    }
}

status macro_scan(unsigned int ch,Token *token)
{
    int i=0;
    token->tok[i++]=ch;
    ch=fgetc(token->input_fp);
    while( (ch != ' ') )
    {
        token->tok[i++]=ch;
        ch=fgetc(token->input_fp);
    }
    token->tok[i]='\0';
    printf("%-10d %-15s : MACRO\n",token->line,token->tok);
    fprintf(token->output_fp,"%-10d %-15s : MACRO\n",token->line,token->tok);
    
    while( (ch=fgetc(token->input_fp)) == ' ');

    if(ch=='\n')
    {
        (token->line)++;
        return SUCCESS;
    }
    else if(ch==';')
    {
        printf("%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
        fprintf(token->output_fp,"%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
        return SUCCESS;
    }
    else
    {
        i=0;
        while( !((ch == ' ') || (ch == ';') || (ch == '\n')) )
        {
            token->tok[i++]=ch;
            ch=fgetc(token->input_fp);
        }
        token->tok[i]='\0';
        printf("%-10d %-15s : MACRO VALUE\n",token->line,token->tok);
        fprintf(token->output_fp,"%-10d %-15s : MACRO VALUE\n",token->line,token->tok);
    }

    while( ch == ' ')
    {
        ch=fgetc(token->input_fp);
    }
    
    if(ch=='\n')
    {
        (token->line)++;
        return SUCCESS;
    }
    else if(ch==';')
    {
        printf("%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
        fprintf(token->output_fp,"%-10d %-15c : TERMINATING OPERATOR\n",token->line,ch);
        while( (ch=fgetc(token->input_fp))!='\n' );
        (token->line)++;
        return SUCCESS;
    }  
}