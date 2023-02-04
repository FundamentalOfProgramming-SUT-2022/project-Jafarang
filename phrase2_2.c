#include<stdio.h>
#include "conio21/conio2.h"
#include <conio.h>
#include "conio.h"
#include "conio21/conio.c"
#include "main.c"

char file[10000];
char file_name[100];
int start_lines[1000];
int size_of_file=0;
int num_of_lines=0;
int mode=0;
int not_saved=0;
int first_line=0;
int cur_x=1;
int cur_y=1;


int vim();
void get_file_name(char path[]);
void refresh_file(char path[]);
void layout();
void print_line(int line);
void refresh_screen();


int main()
{
    vim();
    return 0;
}
////////////////////////////////////////////////////////////////////////////shoroo
int vim()
{
    char path[100];
    char flag[50];
    scanf("%s",flag);
    if(strcmp(flag,"--file"))
        return error(*invalid_input);
    if(file_input(path)==ERRORERROR)
        return error(*invalid_input);
    if(check_wrong_address(path)==ERRORERROR)
        return error(*invalid_address);
    if(check_existance_of_file(path)==ERRORERROR)
        return error(*no_such_file);
    //////////////////////////////////
    size_of_file=0;
    num_of_lines=0;
    mode=0;
    not_saved=0;
    first_line=0;
    cur_x=1;
    cur_y=1;
    ///////////////////////////////
    refresh_file(path);
    refresh_screen();
    getch(); //
}
void get_file_name(char path[])
{
    for(int i=strlen(path)-1;i>=0;i--)
    {
        if(path[i]=='/')
        {
            strcpy(file_name,&path[i+1]);
            break;
        }
    }
}
void refresh_file(char path[])
{
    FILE*fptr=fopen(path,"r");
    start_lines[num_of_lines]=-1;
    for(;fscanf(fptr,"%c",&file[size_of_file])!=-1;size_of_file++)
    {
        if(file[size_of_file]=='\n')
        {
            num_of_lines++;
            start_lines[num_of_lines]=size_of_file;
        }
    }
    file[size_of_file]='\0';
    num_of_lines++;
    start_lines[num_of_lines]=size_of_file;
    fclose(fptr);
    get_file_name(path);
}
void layout()
{
    clrscr();
    textbackground(DARKGRAY);
    delline();
    textbackground(BLACK);
    delline();
    delline();
    textbackground(CYAN);
    gotoxy(1,28);
    switch(mode)
    {
        case 0:
            cprintf(" NORMAL ");
            break;
        case 1:
            cprintf(" VISUAL ");
            break;
        case 2:
            cprintf(" INSERT ");
            break;
    }
    textbackground(DARKGRAY);
    cprintf("%s",file_name);
    if(not_saved==1)
        cprintf("+ ");
    textbackground(BLACK);
    gotoxy(1,1);
}
void print_line(int line)
{
    printf("%d    ",line+1);
    for(int i=start_lines[line]+1;i<start_lines[line+1];i++)
    {
        printf("%c",file[i]);
    }
    printf("\n");
}
void refresh_screen()
{
    layout();
    for(int i=0;i<27;i++)
    {
        if(first_line+i<num_of_lines)
            print_line(first_line+i);
        else
        {
            for(;i<27;i++)
            {
                printf("~\n");
            }
        }
    }
    gotoxy(1,1);
}
