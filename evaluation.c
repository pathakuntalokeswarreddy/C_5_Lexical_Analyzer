#include "header.h"

//  evaluate_arguments() function evaluates the input command line arguments
//  USAGE: ./a.out input.c
status evaluate_arguments(int argc,char *argv[])
{ 
    if(argc>2)
        goto error;

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
    printf("Invalid CLA Input\nUSAGE: ./a.out input_file.c\n\n");
    return FAILURE;
}

// open_file() will set streams for Input and Output file
status open_file(char *argv[],Token *token)
{
    //Input File
    token->input_file_name = argv[1]; 
    token->input_fp = fopen(token->input_file_name,"r+");
    if(!(token->input_file_name))
    {
        perror("Memory Allocation Failed for input_file\n");
        return FAILURE;
    }
    printf("Entered File Name: %s\n",token->input_file_name);


    //Output File
    strcpy(token->output_file_name,"Analysis_Report.text");
    token->output_fp = fopen(token->output_file_name,"w+");
    if(!(token->output_file_name))
    {
        perror("Memory Allocation Failed for output file\n");
        return FAILURE;
    }
    printf("Output File Name: %s\n\n",token->output_file_name);

    
    return SUCCESS;
}