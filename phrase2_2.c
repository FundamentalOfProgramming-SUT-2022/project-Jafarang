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


int vim();
void get_file_name(char path[]);
void refresh_file(char path[]);
void layout();
void print_line(int line);
void refresh_screen();
void visual_mode();


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
    ///////////////////////////////
    refresh_file(path);
    refresh_screen();
    visual_mode();
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
    printf("%d  ",line+1);
    if(line+1<10)
        printf("  ");
    else if(line+1<100)
        printf(" ");
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
/////////////////////////////////
void normal_mode()
{
    gotoxy(1,29);
}
/////////////////////////////////
void visual_mode()
{
    int cur_x=1;
    int cur_y=1;
    int scr_x=cur_x+5;
    int scr_y=cur_y-first_line;
    int cur_pos=0;
    char c;
    gotoxy(scr_x,scr_y);
    while(1)
    {
        if(kbhit())
        {
            c=getch();
            switch(c)
            {
                case 'h':
                    if (cur_x>1)
                    {
                        cur_x--;
                        scr_x--;
                        gotoxy(scr_x,scr_y);
                        cur_pos--;
                    }
                    break;
                case 'l':
                    if(cur_x<start_lines[cur_y]-start_lines[cur_y-1]-1)
                    {
                        cur_x++;
                        scr_x++;
                        gotoxy(scr_x,scr_y);
                        cur_pos++;
                    }
                    break;
                case 'j':
                    if(first_line>1&&scr_y<5)
                    {
                        first_line--;
                        refresh_screen();
                        if(cur_x>start_lines[cur_y-1]-start_lines[cur_y-2]-1)
                        {
                            cur_x=start_lines[cur_y-1]-start_lines[cur_y-2]-1;
                            scr_x=cur_x+5;
                        }
                        cur_y--;
                        gotoxy(scr_x,scr_y);
                        cur_pos=start_lines[cur_y-1]+cur_x;
                    }else if(cur_y>1)
                    {
                        if(cur_x>start_lines[cur_y-1]-start_lines[cur_y-2]-1)
                        {
                            cur_x=start_lines[cur_y-1]-start_lines[cur_y-2]-1;
                            scr_x=cur_x+5;
                        }
                        cur_y--;
                        scr_y--;
                        gotoxy(scr_x,scr_y);
                        cur_pos=start_lines[cur_y-1]+cur_x;
                    }
                    break;
                case 'k':
                    if(scr_y>23&&cur_y<num_of_lines)
                    {
                        first_line++;
                        refresh_screen();
                        if(cur_x>start_lines[cur_y+1]-start_lines[cur_y]-1)
                        {
                            cur_x=start_lines[cur_y+1]-start_lines[cur_y]-1;
                            scr_x=cur_x+5;
                        }
                        cur_y++;
                        gotoxy(scr_x,scr_y);
                        cur_pos=start_lines[cur_y+1]+cur_x;
                    }else if(cur_y<num_of_lines)
                    {
                        if(cur_x>start_lines[cur_y+1]-start_lines[cur_y]-1)
                        {
                            cur_x=start_lines[cur_y+1]-start_lines[cur_y]-1;
                            scr_x=cur_x+5;
                        }
                        cur_y++;
                        scr_y++;
                        gotoxy(scr_x,scr_y);
                        cur_pos=start_lines[cur_y+1]+cur_x;
                    }
                    break;
            }
        }
    }
}


