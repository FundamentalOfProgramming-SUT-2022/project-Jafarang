#include<stdio.h>
#include "conio21/conio2.h"
#include <conio.h>
#include "conio.h"
#include "conio21/conio.c"
#include "main.c"

char file[10000];
char file_name[100];
char path[100];
int start_lines[1000];
int size_of_file=0;
int num_of_lines=0;
int mode=0;
int not_saved=0;
int first_line=0;


int vim();
void get_file_name(char path[]);
void refresh_file();
void layout();
void print_line(int line);
void refresh_screen();
void visual_mode();
void normal_mode();


int main()
{
    vim();
    return 0;
}
////////////////////////////////////////////////////////////////////////////shoroo
int vim()
{
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
    //////////////////////////////////////////////
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
    ////////////////////////////////
    refresh_screen();
    visual_mode();
    normal_mode();
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
void refresh_file()
{
    size_of_file=0;
    num_of_lines=0;
    start_lines[num_of_lines]=-1;
    for(;file[size_of_file]!='\0';size_of_file++)
    {
        if(file[size_of_file]=='\n')
        {
            num_of_lines++;
            start_lines[num_of_lines]=size_of_file;
        }
    }
    num_of_lines++;
    start_lines[num_of_lines]=size_of_file;
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
    {
        cprintf(" + ");
    }
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
    char command[100];
    char c;
    while(1)
    {if(kbhit()){
        gotoxy(1,29);
        scanf("%c",&c);
        gotoxy(1,30);
        cprintf("                                              ");
        gotoxy(1,30);
        if(c!=':')
        {
            printf("invalid input");
            continue;
        }
        gotoxy(2,29);
        scanf("%s",command);
        if(strcmp(command,"save")==0)
        {
            if(check_existance_of_file(path)==ERRORERROR)
            {
                gotoxy(1,30);
                printf("please enter a path for your file");
                gotoxy(6,29);
                if(file_input(path)==ERRORERROR)
                {
                    gotoxy(1,30);
                    printf("invalid input");
                    continue;
                }
                if(go_to_address(path)==ERRORERROR)
                {
                    gotoxy(1,30);
                    printf("invalid address");
                    continue;
                }
                get_file_name(path);
                char path2[100];
                strcpy(path2,path);
                path2[3]='z';
                go_to_address(path2);
                FILE*fptr=fopen(path,"w");
                fprintf(fptr,"%s",file);
                fclose(fptr);
                fptr=fopen(path2,"w");
                fprintf(fptr,"%s",file);
                fclose(fptr);
                not_saved=0;
                gotoxy(1,30);
                printf("saved\n");
                gotoxy(1,29);
                cprintf("                                              ");
                gotoxy(1,29);
            }
            char path2[100];
            char c;
            strcpy(path2,path);
            path2[3]='z';
            FILE*fptr1,*fptr2;
            fptr2=fopen(path2,"w");
            fptr1=fopen(path,"r");
            while((c=fgetc(fptr1))!=-1)
            {
                fprintf(fptr2,"%c",c);
            }
            fclose(fptr1);
            fclose(fptr2);
            FILE*fptr=fopen(path,"w");
            fprintf(fptr,"%s",file);
            fclose(fptr);
            not_saved=0;
            gotoxy(1,30);
            printf("saved\n");
            gotoxy(1,29);
            cprintf("                                              ");
            gotoxy(1,29);
            continue;
        }
        if(strcmp(command,"saveas")==0)
        {
            if(file_input(path)==ERRORERROR)
            {
                gotoxy(1,30);
                printf("invalid input");
                continue;
            }
            if(go_to_address(path)==ERRORERROR)
            {
                gotoxy(1,30);
                printf("invalid address");
                continue;
            }
            char path2[100];
            strcpy(path2,path);
            path2[3]='z';
            go_to_address(path2);
            FILE*fptr=fopen(path,"w");
            fprintf(fptr,"%s",file);
            fclose(fptr);
            fptr=fopen(path2,"w");
            fprintf(fptr,"%s",file);
            fclose(fptr);
            not_saved=0;
            gotoxy(1,30);
            printf("saved\n");
            gotoxy(1,29);
            cprintf("                                              ");
            gotoxy(1,29);
            continue;
        }
    }}
}
/////////////////////////////////
void dehighlight(int cur_pos,int start_select)
{
    int x=wherex();
    int y=wherey();
    int pre_x=wherex();
    int pre_y=wherey();
    if(start_select!=-10)
    {
        if(start_select>cur_pos)
        {
            for(int i=cur_pos;i<=start_select;i++)
            {
                cprintf("%c",file[i]);
            }
        }else
        {
            for(int i=cur_pos;i>=start_select;i--)
            {
                cprintf("%c",file[i]);
                x--;
                gotoxy(x,y);
            }
        }
        gotoxy(pre_x,pre_y);
    }
}

void visual_mode()
{
    int cur_x=1;
    int cur_y=1;
    int scr_x=cur_x+5;
    int scr_y=cur_y-first_line;
    int cur_pos=0;
    int start_select=-10;
    char c;
    int if_highlighted[size_of_file];
    for(int i=0;i<size_of_file;i++)
    {
        if_highlighted[i]=0;
    }
    char end_of_file[10000];
    gotoxy(scr_x,scr_y);
    while(1)
    {
        if(kbhit())
        {
            c=getch();
            switch(c)
            {
                case 'n':
                    dehighlight(cur_pos,start_select);
                    if(start_select!=-10)
                    {
                        int size;
                        if (cur_pos>start_select)
                        {
                            size=cur_pos-start_select;
                            free(clipboard);
                            clipboard=(char*)malloc((size+3)*sizeof(char));
                            strncpy(clipboard,&file[start_select],size);
                            if(if_highlighted[cur_pos])
                            {
                                clipboard[strlen(clipboard)]=file[cur_pos];
                                clipboard[strlen(clipboard)+1]='\0';
                            }
                        }else if (cur_pos<start_select)
                        {
                            size=start_select-cur_pos;
                            free(clipboard);
                            clipboard=(char*)malloc((size+3)*sizeof(char));
                            int p=1;
                            if(if_highlighted[cur_pos])
                            {
                                p=0;
                                size++;
                            }
                            strncpy(clipboard,&file[cur_pos+p],size);
                            clipboard[size]='\0';
                        }
                    }
                    break;
                case 'p':
                    strcpy(end_of_file,&file[cur_pos]);
                    file[cur_pos]='\0';
                    strcat(file,clipboard);
                    strcat(file,end_of_file);
                    not_saved=1;
                    refresh_file();
                    refresh_screen();
                    gotoxy(scr_x,scr_y);
                    break;
                case 'e':
                    mode=0;
                    return;
                case 'h':
                    dehighlight(cur_pos,start_select);
                    start_select=-10;
                    if (cur_x>1)
                    {
                        cur_x--;
                        scr_x--;
                        gotoxy(scr_x,scr_y);
                        cur_pos--;
                    }
                    break;
                case 'l':
                    dehighlight(cur_pos,start_select);
                    start_select=-10;
                    if(cur_x<start_lines[cur_y]-start_lines[cur_y-1])
                    {
                        cur_x++;
                        scr_x++;
                        gotoxy(scr_x,scr_y);
                        cur_pos++;
                    }
                    break;
                case 'j':
                    dehighlight(cur_pos,start_select);
                    start_select=-10;
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
                    dehighlight(cur_pos,start_select);
                    start_select=-10;
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
                        cur_pos=start_lines[cur_y-1]+cur_x;
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
                        cur_pos=start_lines[cur_y-1]+cur_x;
                    }
                    break;
                case 'H':
                    if(start_select==-10)
                        start_select=cur_pos;
                    if(cur_pos<=start_select)
                    {
                        textbackground(LIGHTBLUE);
                        cprintf("%c",file[cur_pos]);
                        if_highlighted[cur_pos]=1;
                        gotoxy(scr_x,scr_y);
                        textbackground(BLACK);
                    }else if(if_highlighted[cur_pos]==0)
                    {
                        gotoxy(scr_x-1,scr_y);
                        cprintf("%c",file[cur_pos-1]);
                        if_highlighted[cur_pos-1]=0;
                        gotoxy(scr_x,scr_y);
                    }else
                    {
                        gotoxy(scr_x,scr_y);
                        cprintf("%c",file[cur_pos]);
                        if_highlighted[cur_pos]=0;
                        gotoxy(scr_x,scr_y);
                    }
                    ///////////////
                    if (cur_x>1)
                    {
                        cur_x--;
                        scr_x--;
                        gotoxy(scr_x,scr_y);
                        cur_pos--;
                    }
                    break;
                case 'L':
                    if(start_select==-10)
                        start_select=cur_pos;
                    if(cur_pos>=start_select)
                    {
                        textbackground(LIGHTBLUE);
                        cprintf("%c",file[cur_pos]);
                        if_highlighted[cur_pos]=1;
                        gotoxy(scr_x,scr_y);
                        textbackground(BLACK);
                    }else if(if_highlighted[cur_pos]==0)
                    {
                        gotoxy(scr_x+1,scr_y);
                        cprintf("%c",file[cur_pos+1]);
                        if_highlighted[cur_pos+1]=0;
                        gotoxy(scr_x,scr_y);
                    }else
                    {
                        gotoxy(scr_x,scr_y);
                        cprintf("%c",file[cur_pos]);
                        if_highlighted[cur_pos]=0;
                        gotoxy(scr_x,scr_y);
                    }
                    //////////////////////
                    if(cur_x<start_lines[cur_y]-start_lines[cur_y-1]-1)
                    {
                        cur_x++;
                        scr_x++;
                        gotoxy(scr_x,scr_y);
                        cur_pos++;
                    }
                    break;
            }
        }
    }
}


