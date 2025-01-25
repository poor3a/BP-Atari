#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>
#include "definitions.h"

FILE *fp;
time_t final_time;/*used for getting system time*/
clock_t timer;
struct tm *time_info;
struct enemy
{
    int state;
    int width;
    int height;
    int hp;
} supply_ship , bomber ,e3 ,e4;
struct temp
{
    int state;
    int width;
    int height;
}item ,bomb1 ,bomb2 ,eb1 ,eb2;

double time_elapsed;
char BOLD_ON[7] = "\033[1m";
char BOLD_OFF[7] = "\033[0m";
char line[80];
char player_name[25];
char time_string[10];
int score = 0;
int score_width = 12;
int score_height = 2;
int bullet_state = 0;
int bullet_width;
int bullet_height;
int hp_width = 40;
int hp_height = 2;
int hp = 5;
int state;
int item_collected = 0;
int difficulty = MEDIUM;


void set_color(int);
char get_input();
int  menu(int);
void make_menu(int);
void make_menu_curser();
void make_menu_curser_2();
void menu_1();
void menu_2();
void menu_3();
void menu_4();
void scores_menu();
void difficulty_menu();
void d_menu_1();
void d_menu_2();
void d_menu_3();
void make_map();
void make_plane(int ,int);
void destroy_plane(int ,int);
void make_mine(int ,int);
void destroy_mine(int ,int);
void make_supply_ship(int ,int);
void destroy_supply_ship(int ,int);
void supply_ship_explosion(int ,int);
void make_item();
void collect_item(int,int);
void make_bomber(int ,int);
void destroy_bomber(int ,int);
void bomber_explosion(int ,int);
void make_bomb(int ,int);
void destroy_bomb(int ,int);
void bomb_explosion(int ,int);
void bomb_explosion(int ,int);
void generate_bullet(int ,int);
int  random_number(int ,int);
void mine_explosion(int ,int);
void enemy_maker();
void enemy_destroyer();
void plane_hit(int ,int);
void bullet_hit();
void end_game();
int  game_loop(int *plane_width,int *plane_height)
{
    item_collected--;
    score ++;
    gotoxy(score_width ,score_height);
    printf("%d  " ,score / 10);
    if (hp <= 0)
    {
        return 1;
    }
    if(bullet_state == 1)
        bullet_hit();
    if (item_collected > 0)
        set_color(Green);
    
    make_plane(*plane_width ,*plane_height);
    set_color(White);
    if ((score % 6 == 0) && (bullet_state == 1))
    {
        generate_bullet(bullet_width ,bullet_height);
        bullet_height-=2;
    }
    if (difficulty == HARD)
    {
        if (score % 10 == 0)
        {
            enemy_destroyer();
            enemy_maker();
            make_item();
        }
    }
    else if (difficulty == MEDIUM)
    {
        if (score % 18 == 0)
        {
            enemy_destroyer();
            enemy_maker();
            make_item();
        }
    }
    else if (difficulty == EASY)
    {
        if (score % 25 == 0)
        {
            enemy_destroyer();
            enemy_maker();
            make_item();
        }
    }

    
    if (kbhit())
    {
        char c = get_input();
        if (c == 'R' && (*plane_width) < 79)
        {
            destroy_plane(*plane_width ,*plane_height);
            (*plane_width) +=1;
        }
        else if (c == 'L' && (*plane_width) > 7)
        {
            destroy_plane(*plane_width ,*plane_height);
            (*plane_width) -=1;
        }
        else if (c == 'D' && (*plane_height) < 28)
        {
            destroy_plane(*plane_width ,*plane_height);
            (*plane_height) +=1;
        }
        else if (c == 'U' && (*plane_height) > 4)
        {
            destroy_plane(*plane_width ,*plane_height);
            (*plane_height) -=1;
        }
        else if ((c == SPACE || c == ENTER) && (bullet_state == 0) && (*plane_height) > 4)
        {
            bullet_width = (*plane_width);
            bullet_height = (*plane_height);
            generate_bullet(bullet_width, bullet_height);
            bullet_state = 1;
        }

    }
    plane_hit(*plane_width ,*plane_height);
    collect_item(*plane_width ,*plane_height);
    return 0;
}

int main()
{
    timer = clock(); /*start timer*/
    srand(time(0));
    supply_ship.state = 0;
    supply_ship.height = 3;
    bomber.state = 0;
    bomber.height = 3;
    e3.state = 0;
    e3.height = 3;
    e4.state = 0;
    e4.height = 3;
    bomb1.state = 0;
    bomb1.width = 10;
    bomb2.state = 0;
    bomb2.width = 10;
    state = menu(1); 
    while(1)
    {
        int plane_width = 42;
        int plane_height = 24;
        bullet_width = plane_width;
        bullet_height = plane_height;

        while (state != 1 && state != 4)
            make_map();

        system("cls");
        make_map();
        if (state == 1)
        {
            while (1)
            {
                if(game_loop(&plane_width ,&plane_height) == 1)
                    break;
            }
        }
        end_game();
    }
}




char get_input()
{
    int input = _getch();

    if (input == ARROW || input == NUMPAD)
    {
        switch (input = _getch())
        {
        case UP:
            return 'U';
            break;
        case DOWN:
            return 'D';
            break;
        case LEFT:
            return 'L';
            break;
        case RIGHT:
            return 'R';
            break;
        }
    }

    return input;
}
void set_color(int x)
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, x);
}
int  random_number(int lower ,int upper)
{
    int sum = (rand() % (upper - lower + 1)) + lower;
    return sum;
}

int  menu(int initial)
{
    printf("\033[?25l"); // hide the cursor
    int menu_index = initial;
    make_menu(menu_index);
    while (1)
    {
        char c = get_input();
        if (c == ENTER || c == SPACE)
        {

            switch (menu_index)
            {
                case 1:
                    usleep(50000);
                    return 1;
                    break;
                case 2:
                    usleep(50000);
                    return 2;
                    break;
                case 3:
                    usleep(50000);
                    return 3;
                    break;
                case 4:
                    usleep(50000);
                    system("cls");
                    _Exit(10);
                    break;

                default:
                    break;
            }
        }
        if (c == 'D' && menu_index < 4)
            menu_index++;

        else if (c == 'U' && menu_index > 1)
            menu_index--;

        make_menu(menu_index);
    }
}
void make_menu(int i)
{
    system("cls");
    set_color(White);
    printf("\n\n\n\n\n\n\n\n\n\n");
    if (i == 1)
        menu_1();

    else if (i == 2)
        menu_2();

    else if (i == 3)
        menu_3();

    else if (i == 4)
        menu_4();
}

void make_menu_curser()
{
    set_color(Red);
    printf("=>");
    set_color(Blue);
}
void make_menu_curser_2()
{
    set_color(Red);
    printf("<=\n\n");
    set_color(White);
}

void menu_1()
{
    printf("\t\t\t\t\t     ");
    make_menu_curser();
    printf("%sPLAY%s", BOLD_ON, BOLD_OFF);
    make_menu_curser_2();
    printf("\t\t\t\t\t    ");
    printf("%sDIFFICULTY%s\n\n", BOLD_ON, BOLD_OFF);
    printf("\t\t\t\t\t      ");
    printf("%sSCORES%s\n\n", BOLD_ON, BOLD_OFF);
    printf("\t\t\t\t\t       ");
    printf("%sEXIT%s", BOLD_ON, BOLD_OFF);
}
void menu_2()
{
    printf("\t\t\t\t\t       ");
    printf("%sPLAY%s\n\n", BOLD_ON, BOLD_OFF);
    printf("\t\t\t\t\t  ");
    make_menu_curser();
    printf("%sDIFFICULTY%s", BOLD_ON, BOLD_OFF);
    make_menu_curser_2();
    printf("\t\t\t\t\t      %sSCORES%s\n\n", BOLD_ON, BOLD_OFF);
    printf("\t\t\t\t\t       %sEXIT%s", BOLD_ON, BOLD_OFF);
}
void menu_3()
{
    printf("\t\t\t\t\t       ");
    printf("%sPLAY%s\n\n", BOLD_ON, BOLD_OFF);
    printf("\t\t\t\t\t    ");
    printf("%sDIFFICULTY%s\n\n", BOLD_ON, BOLD_OFF);
    printf("\t\t\t\t\t    ");
    make_menu_curser();
    printf("%sSCORES%s", BOLD_ON, BOLD_OFF);
    make_menu_curser_2();
    printf("\t\t\t\t\t       %sEXIT%s", BOLD_ON, BOLD_OFF);
}
void menu_4()
{
    printf("\t\t\t\t\t       ");
    printf("%sPLAY%s\n\n", BOLD_ON, BOLD_OFF);
    printf("\t\t\t\t\t    ");
    printf("%sDIFFICULTY%s\n\n", BOLD_ON, BOLD_OFF);
    printf("\t\t\t\t\t      ");
    printf("%sSCORES%s\n\n", BOLD_ON, BOLD_OFF);
    printf("\t\t\t\t\t     ");
    make_menu_curser();
    printf("%sEXIT%s", BOLD_ON, BOLD_OFF);
    make_menu_curser_2();
}

void scores_menu()
{
    int y = 10;
    fp = fopen("../scores.txt" ,"a+");
    system("cls");

    if(fp == NULL)
    {
        gotoxy(30 ,20);
	    printf("Cannot open file\n");
        exit(10);
    }
    while(fgets(line, 80, fp) != NULL)
    {
        gotoxy(10 ,y);
        set_color(Red);
        printf("_____________________________________________________________________________________");
        gotoxy(15 ,y+1);
        set_color(Blue);
        printf("%s" ,line);
        y += 2;
    }
    gotoxy(10 ,y);
    set_color(Red);
    printf("_____________________________________________________________________________________");
    set_color(White);
    fclose(fp);

    gotoxy(15 ,y+5);
    printf("press ESC or ENTER to continue");
    char c = getch();
    if (c == ESC || c == ENTER)
    {
        state = menu(3);
    }
}
void difficulty_menu()
{
    int index = difficulty;
    while (1)
    {
        if (index == 1)
            d_menu_1();
        else if (index == 2)
            d_menu_2();
        else if (index == 3)
            d_menu_3();


        char c = get_input();
        if ((c == 'D') && (index < 3))
        {
            index++;
        }
        else if ((c == 'U') && (index > 1))
        {
            index--;
        }
        else if (c == ENTER || c == SPACE)
        {
            difficulty = index;
            state = menu(2);
            return;
        }

    }
    
}

void d_menu_1()
{
    system("cls");
    printf("%s" ,BOLD_ON);
    set_color(Red);
    gotoxy(30 ,15);
    printf("=>");
    set_color(Green);
    gotoxy(33 ,15);
    printf("EASY");
    set_color(Yellow);
    gotoxy(33 ,17);
    printf("MEDIUM");
    set_color(Red);
    gotoxy(33 ,19);
    printf("HARD");

    set_color(White);
    printf("%s" ,BOLD_OFF);
    gotoxy(30 ,22);
    printf("lower game speed and less enemy spawn");
}
void d_menu_2()
{
    system("cls");
    printf("%s" ,BOLD_ON);
    set_color(Green);
    gotoxy(33 ,15);
    printf("EASY");
    set_color(Red);
    gotoxy(30 ,17);
    printf("=>");
    set_color(Yellow);
    gotoxy(33 ,17);
    printf("MEDIUM");
    set_color(Red);
    gotoxy(33 ,19);
    printf("HARD");

    set_color(White);
    printf("%s" ,BOLD_OFF);
    gotoxy(30 ,22);
    printf("normal game speed and normal enemy spawn");
}
void d_menu_3()
{
    system("cls");
    printf("%s" ,BOLD_ON);
    set_color(Green);
    gotoxy(33 ,15);
    printf("EASY");
    set_color(Yellow);
    gotoxy(33 ,17);
    printf("MEDIUM");
    set_color(Red);
    gotoxy(30 ,19);
    printf("=>");
    gotoxy(33 ,19);
    printf("HARD");

    set_color(White);
    printf("%s" ,BOLD_OFF);
    gotoxy(30 ,22);
    printf("faster game speed and higher enemy spawn ,and you will be oneshot");
}

void make_map()
{
        char arr[35][86] = 
        {"*************************************************************************************\n"
        ,"*   SCORE:                      HP://///                                            *\n"
        ,"*************************************************************************************\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*                                                                                   *\n"
        ,"*************************************************************************************\n"};
    if (state == 1)
    {
        usleep(10000);
        printf("%s" ,BOLD_ON);

        for (int i = 0; i < 35; i++)
        {
            for (int j = 0; j < 86; j++)
            {
                printf("%c" ,arr[i][j]);
            }
        }
        printf("%s" ,BOLD_OFF);
    }
    else if (state == 3)
    {
        scores_menu();
    }
    else if (state == 2)
    {
        difficulty_menu();
    }
}

void make_plane(int w ,int h)
{
    gotoxy(w ,h);
    printf("%c" ,'_' );
    gotoxy(w-1 ,h+1);
    printf("%c" ,'/' );
    gotoxy(w ,h+1);
    printf("%c" ,'|' );
    gotoxy(w+1 ,h+1);
    printf("%c" ,92);
    gotoxy(w-2 ,h+2);
    printf("%c" ,'/' );
    gotoxy(w-1 ,h+2);
    printf("%c" ,'/' );
    gotoxy(w ,h+2);
    printf("%c" ,'|' );
    gotoxy(w+1 ,h+2);
    printf("%c" ,92);
    gotoxy(w+2 ,h+2);
    printf("%c" ,92);
    gotoxy(w-3 ,h+3);
    printf("%c" ,'/' );
    gotoxy(w-2 ,h+3);
    printf("%c" ,'|' );
    gotoxy(w ,h+3);
    printf("%c" ,'|' );
    gotoxy(w+2 ,h+3);
    printf("%c" ,'|' );
    gotoxy(w+3 ,h+3);
    printf("%c" ,92);
    gotoxy(w-4 ,h+4);
    printf("%c" ,'/' );
    gotoxy(w-2 ,h+4);
    printf("%c" ,'|' );
    gotoxy(w ,h+4);
    printf("%c" ,'|' );
    gotoxy(w+2 ,h+4);
    printf("%c" ,'|' );
    gotoxy(w+4 ,h+4);
    printf("%c" ,92);
    gotoxy(w-5 ,h+5);
    printf("%c" ,'/' );
    gotoxy(w-2 ,h+5);
    printf("%c" ,'|' );
    gotoxy(w ,h+5);
    printf("%c" ,'|' );
    gotoxy(w+2 ,h+5);
    printf("%c" ,'|' );
    gotoxy(w+5 ,h+5);
    printf("%c" ,92);
    gotoxy(w-5 ,h+6);
    printf("%c" ,'|' );
    gotoxy(w-4 ,h+6);
    printf("%c" ,'_' );
    gotoxy(w-3 ,h+6);
    printf("%c" ,'_' );
    gotoxy(w-2 ,h+6);
    printf("%c" ,'|' );
    gotoxy(w-1 ,h+6);
    printf("%c" ,'|' );
    gotoxy(w ,h+6);
    printf("%c" ,'|' );
    gotoxy(w+1 ,h+6);
    printf("%c" ,'|' );
    gotoxy(w+2 ,h+6);
    printf("%c" ,'|' );
    gotoxy(w+3 ,h+6);
    printf("%c" ,'_' );
    gotoxy(w+4 ,h+6);
    printf("%c" ,'_' );
    gotoxy(w+5 ,h+6);
    printf("%c" ,'|' );

}
void destroy_plane(int w ,int h)
{
    gotoxy(w ,h);
    printf("%c" ,' ');
    gotoxy(w-1 ,h+1);
    printf("%c" ,' ');
    gotoxy(w ,h+1);
    printf("%c" ,' ');
    gotoxy(w+1 ,h+1);
    printf("%c" ,' ');
    gotoxy(w-2 ,h+2);
    printf("%c" ,' ');
    gotoxy(w-1 ,h+2);
    printf("%c" ,' ');
    gotoxy(w ,h+2);
    printf("%c" ,' ');
    gotoxy(w+1 ,h+2);
    printf("%c" ,' ');
    gotoxy(w+2 ,h+2);
    printf("%c" ,' ');
    gotoxy(w-3 ,h+3);
    printf("%c" ,' ');
    gotoxy(w-2 ,h+3);
    printf("%c" ,' ');
    gotoxy(w ,h+3);
    printf("%c" ,' ');
    gotoxy(w+2 ,h+3);
    printf("%c" ,' ');
    gotoxy(w+3 ,h+3);
    printf("%c" ,' ');
    gotoxy(w-4 ,h+4);
    printf("%c" ,' ');
    gotoxy(w-2 ,h+4);
    printf("%c" ,' ');
    gotoxy(w ,h+4);
    printf("%c" ,' ');
    gotoxy(w+2 ,h+4);
    printf("%c" ,' ');
    gotoxy(w+4 ,h+4);
    printf("%c" ,' ');
    gotoxy(w-5 ,h+5);
    printf("%c" ,' ');
    gotoxy(w-2 ,h+5);
    printf("%c" ,' ');
    gotoxy(w ,h+5);
    printf("%c" ,' ');
    gotoxy(w+2 ,h+5);
    printf("%c" ,' ');
    gotoxy(w+5 ,h+5);
    printf("%c" ,' ');
    gotoxy(w-5 ,h+6);
    printf("%c" ,' ');
    gotoxy(w-4 ,h+6);
    printf("%c" ,' ');
    gotoxy(w-3 ,h+6);
    printf("%c" ,' ');
    gotoxy(w-2 ,h+6);
    printf("%c" ,' ');
    gotoxy(w-1 ,h+6);
    printf("%c" ,' ');
    gotoxy(w ,h+6);
    printf("%c" ,' ');
    gotoxy(w+1 ,h+6);
    printf("%c" ,' ');
    gotoxy(w+2 ,h+6);
    printf("%c" ,' ');
    gotoxy(w+3 ,h+6);
    printf("%c" ,' ');
    gotoxy(w+4 ,h+6);
    printf("%c" ,' ');
    gotoxy(w+5 ,h+6);
    printf("%c" ,' ');
}
void generate_bullet(int bullet_width ,int bullet_height)
{
    if (bullet_height == 4  || bullet_height == 5)
    {
        gotoxy(bullet_width ,bullet_height);
        printf("%c" ,' ');
        bullet_state = 0;
    }
    else
    {
        gotoxy(bullet_width ,bullet_height-2);
        if (score % 16 == 0)
            set_color(Yellow);
        else
            set_color(Red);
        
        printf("%c" ,'^');
        set_color(White);
        gotoxy(bullet_width ,bullet_height);
        printf("%c" ,' ');

    }
    
}

void make_mine(int mine_width ,int mine_height)
{
    if (mine_height == 3)
    {
        gotoxy(mine_width ,mine_height+1);
        printf("%c" ,'"');
    }
    else if (mine_height == 4)
    {
        gotoxy(mine_width-1 ,mine_height);
        printf("%c" ,'"');
        gotoxy(mine_width ,mine_height);
        printf("%c" ,'*');
        gotoxy(mine_width+1 ,mine_height);
        printf("%c" ,'"');
        gotoxy(mine_width ,mine_height+1);
        printf("%c" ,'"');
    }
    else if (mine_height == 34)
    {
        gotoxy(mine_width ,mine_height-1);
        printf("%c" ,'"');
        gotoxy(mine_width-1 ,mine_height);
        printf("%c" ,'"');
        gotoxy(mine_width ,mine_height);
        printf("%c" ,'*');
        gotoxy(mine_width+1 ,mine_height);
        printf("%c" ,'"');
    }
    else if (mine_height > 3)
    {
        gotoxy(mine_width ,mine_height-1);
        printf("%c" ,'"');
        gotoxy(mine_width-1 ,mine_height);
        printf("%c" ,'"');
        gotoxy(mine_width ,mine_height);
        printf("%c" ,'*');
        gotoxy(mine_width+1 ,mine_height);
        printf("%c" ,'"');
        gotoxy(mine_width ,mine_height+1);
        printf("%c" ,'"');
    }
}
void destroy_mine(int mine_width ,int mine_height)
{   
    if (mine_height == 3)
    {
        gotoxy(mine_width ,mine_height+1);
        printf("%c" ,' ');
    }
    else if (mine_height == 34)
    {
        gotoxy(mine_width ,mine_height-1);
        printf("%c" ,' ');
        gotoxy(mine_width-1 ,mine_height);
        printf("%c" ,' ');
        gotoxy(mine_width ,mine_height);
        printf("%c" ,' ');
        gotoxy(mine_width+1 ,mine_height);
        printf("%c" ,' ');
    }
    else if (mine_height == 4)
    {
        gotoxy(mine_width-1 ,mine_height);
        printf("%c" ,' ');
        gotoxy(mine_width ,mine_height);
        printf("%c" ,' ');
        gotoxy(mine_width+1 ,mine_height);
        printf("%c" ,' ');
        gotoxy(mine_width ,mine_height+1);
        printf("%c" ,' ');
    }
    else
    {
        gotoxy(mine_width ,mine_height-1);
        printf("%c" ,' ');
        gotoxy(mine_width-1 ,mine_height);
        printf("%c" ,' ');
        gotoxy(mine_width ,mine_height);
        printf("%c" ,' ');
        gotoxy(mine_width+1 ,mine_height);
        printf("%c" ,' ');
        gotoxy(mine_width ,mine_height+1);
        printf("%c" ,' ');
    }    
}
void mine_explosion(int mine_width,int mine_height)
{
    destroy_mine(mine_width ,mine_height-1);
    set_color(Red);
    usleep(10000);
    make_mine(mine_width ,mine_height);
    usleep(10000);
    gotoxy(mine_width+1 ,mine_height-1);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(mine_width-1 ,mine_height-1);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(mine_width+1 ,mine_height+1);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(mine_width+1 ,mine_height+1);
    printf("%c" ,'&');
    set_color(Yellow);
    usleep(10000);
    make_mine(mine_width ,mine_height);
    usleep(10000);
    gotoxy(mine_width+1 ,mine_height-1);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(mine_width-1 ,mine_height-1);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(mine_width+1 ,mine_height+1);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(mine_width+1 ,mine_height+1);
    printf("%c" ,'&');
    gotoxy(mine_width+1 ,mine_height-1);
    printf("%c" ,' ');
    gotoxy(mine_width-1 ,mine_height-1);
    printf("%c" ,' ');
    gotoxy(mine_width+1 ,mine_height+1);
    printf("%c" ,' ');
    gotoxy(mine_width+1 ,mine_height+1);
    printf("%c" ,' ');
    gotoxy(mine_width ,mine_height-1);
    printf("%c" ,' ');
    gotoxy(mine_width-1 ,mine_height);
    printf("%c" ,' ');
    gotoxy(mine_width ,mine_height);
    printf("%c" ,' ');
    gotoxy(mine_width+1 ,mine_height);
    printf("%c" ,' ');
    gotoxy(mine_width ,mine_height+1);
    printf("%c" ,' ');
    set_color(White);
}

void make_supply_ship(int supply_width ,int supply_height)
{
    
    if (supply_height == 4)
   {
      gotoxy(supply_width + 1, supply_height);
      printf("%c", '*');
      gotoxy(supply_width + 2, supply_height);
      printf("%c", '/');
      gotoxy(supply_width, supply_height);
      printf("%c", '|');
      gotoxy(supply_width - 1, supply_height);
      printf("%c", '*');
      gotoxy(supply_width - 2, supply_height);
      printf("%c", 92);
   }

   else if (supply_height == 6)
   {
      gotoxy(supply_width + 1, supply_height);
      printf("%c", '*');
      gotoxy(supply_width + 2, supply_height);
      printf("%c", '/');
      gotoxy(supply_width, supply_height);
      printf("%c", '|');
      gotoxy(supply_width - 1, supply_height);
      printf("%c", '*');
      gotoxy(supply_width - 2, supply_height);
      printf("%c", 92);
      gotoxy(supply_width + 1, supply_height - 1);
      printf("%c", '|');
      gotoxy(supply_width + 2, supply_height - 1);
      printf("%c", 92);
      gotoxy(supply_width, supply_height - 1);
      printf("%c", '|');
      gotoxy(supply_width - 1, supply_height - 1);
      printf("%c", '|');
      gotoxy(supply_width - 2, supply_height - 1);
      printf("%c", '/');
      gotoxy(supply_width + 1, supply_height - 2);
      printf("%c", '|');
      gotoxy(supply_width, supply_height - 2);
      printf("%c", '|');
      gotoxy(supply_width - 1, supply_height - 2);
      printf("%c", '|');
   }
   else if (supply_height < 37)
   {
      gotoxy(supply_width + 1, supply_height);
      printf("%c", '*');
      gotoxy(supply_width + 2, supply_height);
      printf("%c", '/');
      gotoxy(supply_width, supply_height);
      printf("%c", '|');
      gotoxy(supply_width - 1, supply_height);
      printf("%c", '*');
      gotoxy(supply_width - 2, supply_height);
      printf("%c", 92);
      gotoxy(supply_width + 1, supply_height - 1);
      printf("%c", '|');
      gotoxy(supply_width + 2, supply_height - 1);
      printf("%c", 92);
      gotoxy(supply_width, supply_height - 1);
      printf("%c", '|');
      gotoxy(supply_width - 1, supply_height - 1);
      printf("%c", '|');
      gotoxy(supply_width - 2, supply_height - 1);
      printf("%c", '/');
      gotoxy(supply_width + 1, supply_height - 2);
      printf("%c", '|');
      gotoxy(supply_width, supply_height - 2);
      printf("%c", '|');
      gotoxy(supply_width - 1, supply_height - 2);
      printf("%c", '|');
      gotoxy(supply_width + 1, supply_height - 3);
      printf("%c", '|');
      gotoxy(supply_width + 2, supply_height - 3);
      printf("%c", '/');
      gotoxy(supply_width, supply_height - 3);
      printf("%c", '|');
      gotoxy(supply_width - 1, supply_height - 3);
      printf("%c", '|');
      gotoxy(supply_width - 2, supply_height - 3);
      printf("%c", 92);
   }
}
void destroy_supply_ship(int supply_width ,int supply_height)
{
       if (supply_height == 4)
   {
      gotoxy(supply_width + 1, supply_height);
      printf("%c", ' ');
      gotoxy(supply_width + 2, supply_height);
      printf("%c", ' ');
      gotoxy(supply_width, supply_height);
      printf("%c", ' ');
      gotoxy(supply_width - 1, supply_height);
      printf("%c", ' ');
      gotoxy(supply_width - 2, supply_height);
      printf("%c", ' ');
   }
   else if (supply_height == 6)
   {
      gotoxy(supply_width + 1, supply_height);
      printf("%c", ' ');
      gotoxy(supply_width + 2, supply_height);
      printf("%c", ' ');
      gotoxy(supply_width, supply_height);
      printf("%c", ' ');
      gotoxy(supply_width - 1, supply_height);
      printf("%c", ' ');
      gotoxy(supply_width - 2, supply_height);
      printf("%c", ' ');
      gotoxy(supply_width + 1, supply_height - 1);
      printf("%c", ' ');
      gotoxy(supply_width + 2, supply_height - 1);
      printf("%c", ' ');
      gotoxy(supply_width, supply_height - 1);
      printf("%c", ' ');
      gotoxy(supply_width - 1, supply_height - 1);
      printf("%c", ' ');
      gotoxy(supply_width - 2, supply_height - 1);
      printf("%c", ' ');
      gotoxy(supply_width + 1, supply_height - 2);
      printf("%c", ' ');
      gotoxy(supply_width + 2, supply_height - 2);
      printf("%c", ' ');
      gotoxy(supply_width, supply_height - 2);
      printf("%c", ' ');
      gotoxy(supply_width - 1, supply_height - 2);
      printf("%c", ' ');
      gotoxy(supply_width - 2, supply_height - 2);
      printf("%c", ' ');
   }
   else if (supply_height < 37)
   {
      gotoxy(supply_width + 1, supply_height);
      printf("%c", ' ');
      gotoxy(supply_width + 2, supply_height);
      printf("%c", ' ');
      gotoxy(supply_width, supply_height);
      printf("%c", ' ');
      gotoxy(supply_width - 1, supply_height);
      printf("%c", ' ');
      gotoxy(supply_width - 2, supply_height);
      printf("%c", ' ');
      gotoxy(supply_width + 1, supply_height - 1);
      printf("%c", ' ');
      gotoxy(supply_width + 2, supply_height - 1);
      printf("%c", ' ');
      gotoxy(supply_width, supply_height - 1);
      printf("%c", ' ');
      gotoxy(supply_width - 1, supply_height - 1);
      printf("%c", ' ');
      gotoxy(supply_width - 2, supply_height - 1);
      printf("%c", ' ');
      gotoxy(supply_width + 1, supply_height - 2);
      printf("%c", ' ');
      gotoxy(supply_width + 2, supply_height - 2);
      printf("%c", ' ');
      gotoxy(supply_width, supply_height - 2);
      printf("%c", ' ');
      gotoxy(supply_width - 1, supply_height - 2);
      printf("%c", ' ');
      gotoxy(supply_width - 2, supply_height - 2);
      printf("%c", ' ');
      gotoxy(supply_width + 1, supply_height - 3);
      printf("%c", ' ');
      gotoxy(supply_width + 2, supply_height - 3);
      printf("%c", ' ');
      gotoxy(supply_width, supply_height - 3);
      printf("%c", ' ');
      gotoxy(supply_width - 1, supply_height - 3);
      printf("%c", ' ');
      gotoxy(supply_width - 2, supply_height - 3);
      printf("%c", ' ');
   }
}
void supply_ship_explosion(int supply_width ,int supply_height)
{
    destroy_supply_ship(supply_width ,supply_height -2);
    set_color(Red);
    gotoxy(supply_width ,supply_height);
    printf("%c" ,'&');
    gotoxy(supply_width -1 ,supply_height);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(supply_width +1 ,supply_height);
    printf("%c" ,'*');
    gotoxy(supply_width +2 ,supply_height -1);
    printf("%c" ,'&');
    gotoxy(supply_width -2 ,supply_height -1);
    printf("%c" ,'*');
    usleep(10000);
    gotoxy(supply_width ,supply_height -2);
    printf("%c" ,'&');
    gotoxy(supply_width -1 ,supply_height -2);
    printf("%c" ,'*');
    usleep(10000);
    gotoxy(supply_width -2 ,supply_height -3);
    printf("%c" ,'&');
    gotoxy(supply_width +1 ,supply_height -3);
    printf("%c" ,'*');
    usleep(10000);
    set_color(Yellow);
    gotoxy(supply_width ,supply_height);
    printf("%c" ,'&');
    gotoxy(supply_width -1 ,supply_height);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(supply_width +1 ,supply_height);
    printf("%c" ,'*');
    gotoxy(supply_width +2 ,supply_height -1);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(supply_width -2 ,supply_height -1);
    printf("%c" ,'*');
    gotoxy(supply_width ,supply_height -2);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(supply_width -1 ,supply_height -2);
    printf("%c" ,'*');
    gotoxy(supply_width -2 ,supply_height -3);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(supply_width +1 ,supply_height -3);
    printf("%c" ,'*');
    usleep(10000);
    set_color(White);
    gotoxy(supply_width ,supply_height);
    printf("%c" ,' ');
    gotoxy(supply_width -1 ,supply_height);
    printf("%c" ,' ');
    gotoxy(supply_width +1 ,supply_height);
    printf("%c" ,' ');
    gotoxy(supply_width +2 ,supply_height -1);
    printf("%c" ,' ');
    gotoxy(supply_width -2 ,supply_height -1);
    printf("%c" ,' ');
    gotoxy(supply_width ,supply_height -2);
    printf("%c" ,' ');
    gotoxy(supply_width -1 ,supply_height -2);
    printf("%c" ,' ');
    gotoxy(supply_width -2 ,supply_height -3);
    printf("%c" ,' ');
    gotoxy(supply_width +1 ,supply_height -3);
    printf("%c" ,' ');
    item.height = supply_ship.height -5;
    item.width = supply_ship.width - 1;
    item.state = 1;
}
void make_item()
{
    if (item.state == 1)
    {
        gotoxy(item.width ,item.height);
        if (difficulty == MEDIUM || difficulty == HARD)
        {
            if (score % 4 == 0)
            {
                set_color(Aqua);
            }else
                set_color(Purple);
        }else{
            if (score % 2 == 0)
            {
                set_color(Aqua);
            }else
                set_color(Purple);
        }
        
        printf("+HP+");
    }
    

}
void collect_item(int plane_width ,int plane_height)
{
    if (item.state == 1)
    {
        if ((item.width <= plane_width + 6) && (item.width >= plane_width - 6))
        {
            if (((item.width <= plane_width + 3) && (item.width >= plane_width - 3)) && ((item.height >= plane_height) && (item.height <= plane_height + 3)))
            {
                item.state = 0;
                item_collected = 80;
                gotoxy(item.width ,item.height);
                printf("%c" ,' ');
                gotoxy(item.width+1 ,item.height);
                printf("%c" ,' ');
                gotoxy(item.width+2 ,item.height);
                printf("%c" ,' ');
                gotoxy(item.width+3 ,item.height);
                printf("%c" ,' ');
                hp++;
                hp_width++;
                set_color(Green);
                gotoxy(hp_width ,hp_height);
                printf("%c" ,'/');
                set_color(White);
            }

            else if ((item.height >= plane_height + 3) && (item.height <= plane_height + 7))
            {
                item.state = 0;
                item_collected = 80;
                gotoxy(item.width ,item.height);
                printf("%c" ,' ');
                gotoxy(item.width+1 ,item.height);
                printf("%c" ,' ');
                gotoxy(item.width+2 ,item.height);
                printf("%c" ,' ');
                gotoxy(item.width+3 ,item.height);
                printf("%c" ,' ');
                hp++;
                hp_width++;
                gotoxy(hp_width ,hp_height);
                printf("%c" ,'/');
            }

        }
    }
    

    
}

void make_bomber(int bomber_width,int bomber_height)
{
    if (bomber_height == 4)
    {
        gotoxy(bomber_width - 1 ,bomber_height);
        printf("%c" ,92);
        gotoxy(bomber_width ,bomber_height);
        printf("%c" ,'/');
    }
    else if (bomber_height == 5)
    {
        gotoxy(bomber_width - 1 ,bomber_height);
        printf("%c" ,92);
        gotoxy(bomber_width ,bomber_height);
        printf("%c" ,'/');
        gotoxy(bomber_width -1 ,bomber_height -1);
        printf("%c" ,'/');
        gotoxy(bomber_width +1,bomber_height -1);
        printf("%c" ,'/');
    }
    else if (bomber_height == 6)
    {
        gotoxy(bomber_width - 1 ,bomber_height);
        printf("%c" ,92);
        gotoxy(bomber_width ,bomber_height);
        printf("%c" ,'/');
        gotoxy(bomber_width -1 ,bomber_height -1);
        printf("%c" ,'/');
        gotoxy(bomber_width +1,bomber_height -1);
        printf("%c" ,'/');
        gotoxy(bomber_width - 1 ,bomber_height -2);
        printf("%c" ,92);
        gotoxy(bomber_width ,bomber_height -2);
        printf("%c" ,'-');
        gotoxy(bomber_width + 1 ,bomber_height -2);
        printf("%c" ,'-');
        gotoxy(bomber_width +2,bomber_height -2);
        printf("%c" ,'/');
    }
    else if (bomber_height == 7)
    {
        gotoxy(bomber_width - 1 ,bomber_height);
        printf("%c" ,92);
        gotoxy(bomber_width ,bomber_height);
        printf("%c" ,'/');
        gotoxy(bomber_width -1 ,bomber_height -1);
        printf("%c" ,'/');
        gotoxy(bomber_width +1,bomber_height -1);
        printf("%c" ,'/');
        gotoxy(bomber_width - 1 ,bomber_height -2);
        printf("%c" ,92);
        gotoxy(bomber_width ,bomber_height -2);
        printf("%c" ,'-');
        gotoxy(bomber_width + 1 ,bomber_height -2);
        printf("%c" ,'-');
        gotoxy(bomber_width +2,bomber_height -2);
        printf("%c" ,'/');
        gotoxy(bomber_width - 1 ,bomber_height -3);
        printf("%c" ,'/');
        gotoxy(bomber_width ,bomber_height -3);
        printf("%c" ,'-');
        gotoxy(bomber_width + 1 ,bomber_height -3);
        printf("%c" ,'-');
        gotoxy(bomber_width +2,bomber_height -3);
        printf("%c" ,92);
    }
        else if (bomber_height == 8)
    {
        gotoxy(bomber_width - 1 ,bomber_height);
        printf("%c" ,92);
        gotoxy(bomber_width ,bomber_height);
        printf("%c" ,'/');
        gotoxy(bomber_width -1 ,bomber_height -1);
        printf("%c" ,'/');
        gotoxy(bomber_width +1,bomber_height -1);
        printf("%c" ,'/');
        gotoxy(bomber_width - 1 ,bomber_height -2);
        printf("%c" ,92);
        gotoxy(bomber_width ,bomber_height -2);
        printf("%c" ,'-');
        gotoxy(bomber_width + 1 ,bomber_height -2);
        printf("%c" ,'-');
        gotoxy(bomber_width +2,bomber_height -2);
        printf("%c" ,'/');
        gotoxy(bomber_width - 1 ,bomber_height -3);
        printf("%c" ,'/');
        gotoxy(bomber_width ,bomber_height -3);
        printf("%c" ,'-');
        gotoxy(bomber_width + 1 ,bomber_height -3);
        printf("%c" ,'-');
        gotoxy(bomber_width +2,bomber_height -3);
        printf("%c" ,92);
        gotoxy(bomber_width -1 ,bomber_height -4);
        printf("%c" ,92);
        gotoxy(bomber_width +1,bomber_height -4);
        printf("%c" ,92);
    }
    else
    {
        gotoxy(bomber_width - 1 ,bomber_height);
        printf("%c" ,92);
        gotoxy(bomber_width ,bomber_height);
        printf("%c" ,'/');
        gotoxy(bomber_width -1 ,bomber_height -1);
        printf("%c" ,'/');
        gotoxy(bomber_width +1,bomber_height -1);
        printf("%c" ,'/');
        gotoxy(bomber_width - 1 ,bomber_height -2);
        printf("%c" ,92);
        gotoxy(bomber_width ,bomber_height -2);
        printf("%c" ,'-');
        gotoxy(bomber_width + 1 ,bomber_height -2);
        printf("%c" ,'-');
        gotoxy(bomber_width +2,bomber_height -2);
        printf("%c" ,'/');
        gotoxy(bomber_width - 1 ,bomber_height -3);
        printf("%c" ,'/');
        gotoxy(bomber_width ,bomber_height -3);
        printf("%c" ,'-');
        gotoxy(bomber_width + 1 ,bomber_height -3);
        printf("%c" ,'-');
        gotoxy(bomber_width +2,bomber_height -3);
        printf("%c" ,92);
        gotoxy(bomber_width -1 ,bomber_height -4);
        printf("%c" ,92);
        gotoxy(bomber_width +1,bomber_height -4);
        printf("%c" ,92);
        gotoxy(bomber_width -1 ,bomber_height -5);
        printf("%c" ,'/');
        gotoxy(bomber_width ,bomber_height -5);
        printf("%c" ,92);
    }
}
void destroy_bomber(int bomber_width,int bomber_height)
{
    if (bomber_height == 4)
    {
        gotoxy(bomber_width - 1 ,bomber_height);
        printf("%c" ,' ');
        gotoxy(bomber_width ,bomber_height);
        printf("%c" ,' ');
    }
    else if (bomber_height == 5)
    {
        gotoxy(bomber_width - 1 ,bomber_height);
        printf("%c" ,' ');
        gotoxy(bomber_width ,bomber_height);
        printf("%c" ,' ');
        gotoxy(bomber_width -1 ,bomber_height -1);
        printf("%c" ,' ');
        gotoxy(bomber_width +1,bomber_height -1);
        printf("%c" ,' ');
    }
    else if (bomber_height == 6)
    {
        gotoxy(bomber_width - 1 ,bomber_height);
        printf("%c" ,' ');
        gotoxy(bomber_width ,bomber_height);
        printf("%c" ,' ');
        gotoxy(bomber_width -1 ,bomber_height -1);
        printf("%c" ,' ');
        gotoxy(bomber_width +1,bomber_height -1);
        printf("%c" ,' ');
        gotoxy(bomber_width - 1 ,bomber_height -2);
        printf("%c" ,' ');
        gotoxy(bomber_width ,bomber_height -2);
        printf("%c" ,' ');
        gotoxy(bomber_width + 1 ,bomber_height -2);
        printf("%c" ,' ');
        gotoxy(bomber_width +2,bomber_height -2);
        printf("%c" ,' ');
    }
    else if (bomber_height == 7)
    {
        gotoxy(bomber_width - 1 ,bomber_height);
        printf("%c" ,' ');
        gotoxy(bomber_width ,bomber_height);
        printf("%c" ,' ');
        gotoxy(bomber_width -1 ,bomber_height -1);
        printf("%c" ,' ');
        gotoxy(bomber_width +1,bomber_height -1);
        printf("%c" ,' ');
        gotoxy(bomber_width - 1 ,bomber_height -2);
        printf("%c" ,' ');
        gotoxy(bomber_width ,bomber_height -2);
        printf("%c" ,' ');
        gotoxy(bomber_width + 1 ,bomber_height -2);
        printf("%c" ,' ');
        gotoxy(bomber_width +2,bomber_height -2);
        printf("%c" ,' ');
        gotoxy(bomber_width - 1 ,bomber_height -3);
        printf("%c" ,' ');
        gotoxy(bomber_width ,bomber_height -3);
        printf("%c" ,' ');
        gotoxy(bomber_width + 1 ,bomber_height -3);
        printf("%c" ,' ');
        gotoxy(bomber_width +2,bomber_height -3);
        printf("%c" ,' ');
    }
        else if (bomber_height == 8)
    {
        gotoxy(bomber_width - 1 ,bomber_height);
        printf("%c" ,' ');
        gotoxy(bomber_width ,bomber_height);
        printf("%c" ,' ');
        gotoxy(bomber_width -1 ,bomber_height -1);
        printf("%c" ,' ');
        gotoxy(bomber_width +1,bomber_height -1);
        printf("%c" ,' ');
        gotoxy(bomber_width - 1 ,bomber_height -2);
        printf("%c" ,' ');
        gotoxy(bomber_width ,bomber_height -2);
        printf("%c" ,' ');
        gotoxy(bomber_width + 1 ,bomber_height -2);
        printf("%c" ,' ');
        gotoxy(bomber_width +2,bomber_height -2);
        printf("%c" ,' ');
        gotoxy(bomber_width - 1 ,bomber_height -3);
        printf("%c" ,' ');
        gotoxy(bomber_width ,bomber_height -3);
        printf("%c" ,' ');
        gotoxy(bomber_width + 1 ,bomber_height -3);
        printf("%c" ,' ');
        gotoxy(bomber_width +2,bomber_height -3);
        printf("%c" ,' ');
        gotoxy(bomber_width -1 ,bomber_height -4);
        printf("%c" ,' ');
        gotoxy(bomber_width +1,bomber_height -4);
        printf("%c" ,' ');
    }
    else
    {
        gotoxy(bomber_width - 1 ,bomber_height);
        printf("%c" ,' ');
        gotoxy(bomber_width ,bomber_height);
        printf("%c" ,' ');
        gotoxy(bomber_width -1 ,bomber_height -1);
        printf("%c" ,' ');
        gotoxy(bomber_width +1,bomber_height -1);
        printf("%c" ,' ');
        gotoxy(bomber_width - 1 ,bomber_height -2);
        printf("%c" ,' ');
        gotoxy(bomber_width ,bomber_height -2);
        printf("%c" ,' ');
        gotoxy(bomber_width + 1 ,bomber_height -2);
        printf("%c" ,' ');
        gotoxy(bomber_width +2,bomber_height -2);
        printf("%c" ,' ');
        gotoxy(bomber_width - 1 ,bomber_height -3);
        printf("%c" ,' ');
        gotoxy(bomber_width ,bomber_height -3);
        printf("%c" ,' ');
        gotoxy(bomber_width + 1 ,bomber_height -3);
        printf("%c" ,' ');
        gotoxy(bomber_width +2,bomber_height -3);
        printf("%c" ,' ');
        gotoxy(bomber_width -1 ,bomber_height -4);
        printf("%c" ,' ');
        gotoxy(bomber_width +1,bomber_height -4);
        printf("%c" ,' ');
        gotoxy(bomber_width -1 ,bomber_height -5);
        printf("%c" ,' ');
        gotoxy(bomber_width ,bomber_height -5);
        printf("%c" ,' ');
    }
}
void bomber_explosion(int bomber_width,int bomber_height)
{
    destroy_bomber(bomber_width -3 ,bomber_height -1);
    set_color(Red);
    gotoxy(bomber_width ,bomber_height);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(bomber_width - 1 ,bomber_height - 3);
    printf("%c" ,'#');
    usleep(10000);
    gotoxy(bomber_width + 1 ,bomber_height -2);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(bomber_width +2 ,bomber_height -4);
    printf("%c" ,'#');
    usleep(10000);
    gotoxy(bomber_width -1 ,bomber_height -5);
    printf("%c" ,'&');
    set_color(Yellow);
    gotoxy(bomber_width ,bomber_height);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(bomber_width - 1 ,bomber_height - 3);
    printf("%c" ,'#');
    usleep(10000);
    gotoxy(bomber_width + 1 ,bomber_height -2);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(bomber_width +2 ,bomber_height -4);
    printf("%c" ,'#');
    usleep(10000);
    gotoxy(bomber_width -1 ,bomber_height -5);
    printf("%c" ,'&');
    usleep(10000);
    gotoxy(bomber_width ,bomber_height);
    printf("%c" ,' ');
    gotoxy(bomber_width - 1 ,bomber_height - 3);
    printf("%c" ,' ');
    gotoxy(bomber_width + 1 ,bomber_height -2);
    printf("%c" ,' ');
    gotoxy(bomber_width +2 ,bomber_height -4);
    printf("%c" ,' ');
    gotoxy(bomber_width -1 ,bomber_height -5);
    printf("%c" ,' ');


}
void make_bomb(int bomb_width ,int bomb_height)
{
    gotoxy(bomb_width ,bomb_height);
    printf("(BOMB)");
}
void destroy_bomb(int bomb_width ,int bomb_height)
{
    gotoxy(bomb_width ,bomb_height);
    printf("      ");
}
void bomb_explosion(int bomb_width ,int bomb_height)
{
    destroy_bomb(bomb_width ,bomb_height);
    set_color(Red);
    gotoxy(bomb_width ,bomb_height);
    printf("#");
    usleep(10000);
    gotoxy(bomb_width+ 2 ,bomb_height);
    printf("&");
    usleep(10000);
    gotoxy(bomb_width- 1 ,bomb_height -1);
    printf("&");
    usleep(10000);
    gotoxy(bomb_width+ 1 ,bomb_height +1);
    printf("&");
    usleep(10000);
    gotoxy(bomb_width + 4 ,bomb_height +1);
    printf("#");
    usleep(10000);
    set_color(Yellow);
    gotoxy(bomb_width ,bomb_height);
    printf("#");
    usleep(10000);
    gotoxy(bomb_width+ 2 ,bomb_height);
    printf("&");
    usleep(10000);
    gotoxy(bomb_width- 1 ,bomb_height -1);
    printf("&");
    usleep(10000);
    gotoxy(bomb_width+ 1 ,bomb_height +1);
    printf("&");
    usleep(10000);
    gotoxy(bomb_width + 4 ,bomb_height +1);
    printf("#");
    set_color(White);
    gotoxy(bomb_width ,bomb_height);
    printf(" ");
    usleep(10000);
    gotoxy(bomb_width+ 2 ,bomb_height);
    printf(" ");
    usleep(10000);
    gotoxy(bomb_width- 1 ,bomb_height -1);
    printf(" ");
    usleep(10000);
    gotoxy(bomb_width+ 1 ,bomb_height +1);
    printf(" ");
    usleep(10000);
    gotoxy(bomb_width + 4 ,bomb_height +1);
    printf(" ");
}

void enemy_maker()
{
    if (bomb1.width == bomber.width)
    {
        bomb1.state = 1;
        bomb1.height = bomber.height;
    }   
    if (bomb2.width == bomber.width)
    {
        bomb2.state = 1;
        bomb2.height = bomber.height;
    }
    if (difficulty == HARD || difficulty == MEDIUM)
    {
        if (score % 4 == 0)
            set_color(Yellow);

        else
            set_color(Red);
    }else{
        if (score % 2 == 0)
            set_color(Yellow);

        else
            set_color(Red);
    }


    if (bomb1.state == 1)
    {
        
        bomb1.height++;
        destroy_bomb(bomb1.width ,bomb1.height-1);
        make_bomb(bomb1.width ,bomb1.height);

        if (bomb1.height == 33)
        {
            destroy_bomb(bomb1.width ,bomb1.height);
            destroy_bomb(bomb1.width ,bomb1.height-1);
            bomb1.state = 0;
        }
        
    }
    if (bomb2.state == 1)
    {
        bomb2.height++;
        destroy_bomb(bomb2.width ,bomb2.height-1);
        make_bomb(bomb2.width ,bomb2.height);
        if (bomb2.height == 33)
        {
            destroy_bomb(bomb2.width ,bomb2.height);
            destroy_bomb(bomb2.width ,bomb2.height-1);
            bomb2.state = 0;
        }
        
    }
    set_color(White);
    
    if (supply_ship.state == 0)
    {
        supply_ship.state = random_number(0 , 8);
        if (supply_ship.state > 2)
            supply_ship.state = 0;
    }
    
    switch (supply_ship.state)
    {
    case 1:

        if(supply_ship.height == 3)
        {
            supply_ship.width = random_number(3 , 83);
            supply_ship.hp = 1;
        }
        make_mine(supply_ship.width ,supply_ship.height);

        supply_ship.height += 1;
        if (supply_ship.height ==  34)
        {
            destroy_mine(supply_ship.width ,supply_ship.height - 1);
            supply_ship.state = 0;
            supply_ship.height = 3;
        }


        break;
    case 2:
        if(supply_ship.height == 3)
        {
            supply_ship.width = random_number(9 , 77);
            supply_ship.height++;
            supply_ship.hp = 2;
        }
        if (supply_ship.hp == 1)
            set_color(Red);
        
        make_supply_ship(supply_ship.width ,supply_ship.height);
        set_color(White);

        supply_ship.height += 2;
        if (supply_ship.height ==  36)
        {
            destroy_supply_ship(supply_ship.width ,supply_ship.height - 2);
            supply_ship.state = 0;
            supply_ship.height = 3;
        }

        break;
    }

    if (bomber.state == 0)
    {
        bomber.state = random_number(0 , 8);
        if ((bomber.state != 1) && (bomber.state != 2))
            bomber.state = 0;
    }
    if (bomber.state == 1)
    {
        if(bomber.height == 3)
        {
            bomber.width = random_number(3 , 83);
            bomber.hp = 1;
        }
        make_mine(bomber.width ,bomber.height);

        bomber.height += 1;
        if (bomber.height ==  34)
        {
            destroy_mine(bomber.width ,bomber.height - 1);
            bomber.state = 0;
            bomber.height = 3;
        }
    }
    else if (bomber.state == 2)
    {
        if(bomber.height == 3)
        {
            bomber.width = 3;
            bomber.height++;
            bomber.hp = 1;
            
            if (bomb1.state == 0)
            {
                while (1)
                {
                    if ((bomb1.width = random_number(5 , 30)) % 3 == 0)
                        break;
                }
            }
            
            if (bomb1.state == 0)
            {
                while (1)
                {
                    if ((bomb2.width = random_number(35 , 60)) % 3 == 0)
                        break;
                }
            }
        }

        make_bomber(bomber.width ,bomber.height);
        bomber.height ++;
        bomber.width += 3;

        if (bomber.width == 84)
        {
            destroy_bomber(bomber.width - 3,bomber.height - 1);
            bomber.state = 0;
            bomber.height = 3;
        }
        
    }

    if (e3.state == 0)
    {
        e3.state = random_number(0 , 8);
        if (e3.state != 1)
            e3.state = 0;
    }

    if (e4.state == 0)
    {
        e4.state = random_number(0 , 8);
        if (e4.state != 1)
            e4.state = 0;

    }
    
    if ((e3.state == 1))
    {
        if(e3.height == 3 || e3.width == bomber.width)
        {
            e3.width = random_number(3 , 83);
            e3.hp = 1;
        }
        make_mine(e3.width ,e3.height);

        e3.height += 1;
        if (e3.height ==  34)
        {
            destroy_mine(e3.width ,e3.height - 1);
            e3.state = 0;
            e3.height = 3;
        }

    }
    if ((e4.state == 1))
    {
        if(e4.height == 3 || e4.width == e3.width)
        {
            e4.width = random_number(3 , 83);
            e4.hp = 1;
        }
        make_mine(e4.width ,e4.height);

        e4.height += 1;
        if (e4.height ==  34)
        {
            destroy_mine(e4.width ,e4.height - 1);
            e4.state = 0;
            e4.height = 3;
        }

    }
    
}
void enemy_destroyer()
{

    if ((supply_ship.state == 1))
        destroy_mine(supply_ship.width ,supply_ship.height - 1);
    else if ((supply_ship.state == 2) && supply_ship.height > 4)
        destroy_supply_ship(supply_ship.width ,supply_ship.height - 2);


    if ((bomber.state == 1))
        destroy_mine(bomber.width ,bomber.height -1);
    else if ((bomber.state == 2) && bomber.height > 4)
        destroy_bomber(bomber.width -3 ,bomber.height -1);


    if ((e3.state == 1))
        destroy_mine(e3.width ,e3.height - 1);

    if ((e4.state == 1))
        destroy_mine(e4.width ,e4.height -1);
    
}

void plane_hit(int plane_width,int plane_height)
{
    int collide = 0;
    if (bomb1.state == 1)
    {
        if ((bomb1.width >= plane_width - 7) &&(bomb1.width <= plane_width + 5))
        {
            if ((bomb1.height >= plane_height) && (bomb1.height <= plane_height + 6))
            {
                collide++;
                bomb_explosion(bomb1.width ,bomb1.height);
                hp -= 2;
                gotoxy(hp_width ,hp_height);
                printf("%c" ,' ');
                hp_width--;
                gotoxy(hp_width ,hp_height);
                printf("%c" ,' ');
                hp_width--;
                bomb1.state = 0;
            }
        }
    }
    if (bomb2.state == 1)
    {
        if ((bomb2.width >= plane_width - 7) &&(bomb2.width <= plane_width + 5))
        {
            if ((bomb2.height >= plane_height) && (bomb2.height <= plane_height + 6))
            {
                collide++;
                bomb_explosion(bomb2.width ,bomb2.height);
                hp -= 2;
                gotoxy(hp_width ,hp_height);
                printf("%c" ,' ');
                hp_width--;
                gotoxy(hp_width ,hp_height);
                printf("%c" ,' ');
                hp_width--;
                bomb2.state = 0;
            }
        }
    }
    
    if (supply_ship.state == 1)
    {
        if ((supply_ship.width <= plane_width + 6) && (supply_ship.width >= plane_width - 6))
        {
            if (((supply_ship.width <= plane_width + 3) && (supply_ship.width >= plane_width - 3)) && ((supply_ship.height >= plane_height) && (supply_ship.height <= plane_height + 3)))
            {
                collide++;
                supply_ship.state = 0;
                mine_explosion(supply_ship.width ,supply_ship.height);
                supply_ship.height = 3;
            }
            
            else if ((supply_ship.height >= plane_height + 3) && (supply_ship.height <= plane_height + 7))
            {
                collide++;
                supply_ship.state = 0;
                mine_explosion(supply_ship.width ,supply_ship.height);
                supply_ship.height = 3;
            }
            
        }
    }
    else if (supply_ship.state == 2)
    {
        if ((supply_ship.width <= plane_width + 8) && (supply_ship.width >= plane_width - 8))
        {
            if (((supply_ship.width <= plane_width + 5) && (supply_ship.width >= plane_width - 5)) && ((supply_ship.height >= plane_height) && (supply_ship.height <= plane_height + 5)))
            {
                collide++;
                supply_ship.state = 0;
                supply_ship_explosion(supply_ship.width ,supply_ship.height);
                supply_ship.height = 3;
                hp --;
                gotoxy(hp_width ,hp_height);
                printf("%c" ,' ');
                hp_width--;
            }
            
            else if ((supply_ship.height >= plane_height + 5) && (supply_ship.height <= plane_height + 9))
            {
                collide++;
                supply_ship.state = 0;
                supply_ship_explosion(supply_ship.width ,supply_ship.height);
                supply_ship.height = 3;
                hp --;
                gotoxy(hp_width ,hp_height);
                printf("%c" ,' ');
                hp_width--;
            }
            
        }
    }

    if (bomber.state == 1)
    {
        if ((bomber.width <= plane_width + 6) && (bomber.width >= plane_width - 6))
        {
            if (((bomber.width <= plane_width + 3) && (bomber.width >= plane_width - 3)) && ((bomber.height >= plane_height) && (bomber.height <= plane_height + 3)))
            {
                collide++;
                bomber.state = 0;
                mine_explosion(bomber.width ,bomber.height);
                bomber.height = 3;
            }
            
            else if ((bomber.height >= plane_height + 3) && (bomber.height <= plane_height + 7))
            {
                collide++;
                bomber.state = 0;
                mine_explosion(bomber.width ,bomber.height);
                bomber.height = 3;
            }
            
        }
    }
    else if (bomber.state == 2)
    {
        if ((bomber.width >= plane_width - 5) && (bomber.width <= plane_width + 6))
        {
            if ((bomber.height >= plane_height) && (bomber.height <= plane_height + 14))
            {
                collide++;
                bomber.state = 0;
                bomber_explosion(bomber.width ,bomber.height);
                bomber.height = 3;
                hp --;
                gotoxy(hp_width ,hp_height);
                printf("%c" ,' ');
                hp_width--;
            }
        }
    }

    if (e3.state == 1)
    {
        if ((e3.width <= plane_width + 6) && (e3.width >= plane_width - 6))
        {
            if (((e3.width <= plane_width + 3) && (e3.width >= plane_width - 3)) && ((e3.height >= plane_height) && (e3.height <= plane_height + 3)))
            {
                collide++;
                e3.state = 0;
                mine_explosion(e3.width ,e3.height);
                e3.height = 3;
            }
            
            else if ((e3.height >= plane_height + 3) && (e3.height <= plane_height + 7))
            {
                collide++;
                e3.state = 0;
                mine_explosion(e3.width ,e3.height);
                e3.height = 3;
            }
            
        }
    }   

    if (e4.state == 1)
    {
        if ((e4.width <= plane_width + 6) && (e4.width >= plane_width - 6))
        {
            if (((e4.width <= plane_width + 3) && (e4.width >= plane_width - 3)) && ((e4.height >= plane_height) && (e4.height <= plane_height + 3)))
            {
                collide++;
                e4.state = 0;
                mine_explosion(e4.width ,e4.height);
                e4.height = 3;
            }
            
            else if ((e4.height >= plane_height + 3) && (e4.height <= plane_height + 7))
            {
                collide++;
                e4.state = 0;
                mine_explosion(e4.width ,e4.height);
                e4.height = 3;
            }
            
        }
    }   


    if (collide != 0)
    {
        gotoxy(hp_width ,hp_height);
        printf("%c" ,' ');
        hp_width--;
        hp--;
        score -= 1000;
        if (difficulty == HARD)
        {
            hp = 0;
        }
        
    }
    
}
void bullet_hit()
{
    if (bomb1.state == 1)
    {
        if ((bullet_width == bomb1.width) || (bullet_width == bomb1.width+1) || (bullet_width == bomb1.width + 2) || (bullet_width == bomb1.width + 3) || (bullet_width == bomb1.width + 4))
        {
            if ((bullet_height == bomb1.height) || (bullet_height == bomb1.height + 1) || bullet_height == bomb1.height -1)
            {
                bomb_explosion(bomb1.width ,bomb1.height);
                score += 500;
                bomb1.state = 0;
                bullet_state = 0;
                gotoxy(bullet_width ,bullet_height-1);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height+1);
                printf("%c" ,' ');
            }
        }
    }

    if (bomb2.state == 1)
    {
        if ((bullet_width == bomb2.width) || (bullet_width == bomb2.width+1) || (bullet_width == bomb2.width + 2) || (bullet_width == bomb2.width + 3) || (bullet_width == bomb2.width + 4))
        {
            if ((bullet_height == bomb2.height) || (bullet_height == bomb2.height + 1) || bullet_height == bomb2.height -1)
            {
                bomb_explosion(bomb2.width ,bomb2.height);
                score += 500;
                bomb2.state = 0;
                bullet_state = 0;
                gotoxy(bullet_width ,bullet_height-1);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height+1);
                printf("%c" ,' ');
            }
        }
    }
    
    if (supply_ship.state == 1)
    {
        if ((bullet_width == supply_ship.width) || (bullet_width == supply_ship.width-1) || (bullet_width == supply_ship.width + 1))
        {
            if ((bullet_height == supply_ship.height) || (bullet_height == supply_ship.height + 1) || bullet_height == supply_ship.height -1)
            {
                if (supply_ship.hp >= 2)
                {
                    bullet_state = 0;
                    gotoxy(bullet_width ,bullet_height-1);
                    printf("%c" ,' ');
                    gotoxy(bullet_width ,bullet_height);
                    printf("%c" ,' ');
                    gotoxy(bullet_width ,bullet_height+1);
                    printf("%c" ,' ');
                    supply_ship.hp--;
                }
                else{
                mine_explosion(supply_ship.width ,supply_ship.height);
                score += 1000;
                supply_ship.state = 0;
                supply_ship.height = 3;
                bullet_state = 0;
                gotoxy(bullet_width ,bullet_height-1);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height+1);
                printf("%c" ,' ');
                }
            }
            
        }
    }
    else if (supply_ship.state == 2)
    {
        if ((bullet_width <= supply_ship.width +2) && (bullet_width >= supply_ship.width - 2))
        {
            if ((bullet_height <= supply_ship.height) && bullet_height >= supply_ship.height - 3)
            {
                if (supply_ship.hp == 2)
                {
                    supply_ship.hp --;
                    bullet_state = 0;
                    gotoxy(bullet_width ,bullet_height-1);
                    printf("%c" ,' ');
                    gotoxy(bullet_width ,bullet_height);
                    printf("%c" ,' ');
                    gotoxy(bullet_width ,bullet_height+1);
                    printf("%c" ,' ');
                }
                else if (supply_ship.hp == 1)
                {
                    supply_ship_explosion(supply_ship.width ,supply_ship.height);
                    score += 2000;
                    supply_ship.state = 0;
                    supply_ship.height = 3;
                    bullet_state = 0;
                    gotoxy(bullet_width ,bullet_height-1);
                    printf("%c" ,' ');
                    gotoxy(bullet_width ,bullet_height);
                    printf("%c" ,' ');
                    gotoxy(bullet_width ,bullet_height+1);
                    printf("%c" ,' ');
                }
            }
            
        }
        
    }
    if (bomber.state == 1)
    {
        if ((bullet_width == bomber.width) || (bullet_width == bomber.width-1) || (bullet_width == bomber.width + 1))
        {
            if ((bullet_height == bomber.height) || (bullet_height == bomber.height + 1) || bullet_height == bomber.height -1)
            {
                if (bomber.hp >= 2)
                {
                    bullet_state = 0;
                    gotoxy(bullet_width ,bullet_height-1);
                    printf("%c" ,' ');
                    gotoxy(bullet_width ,bullet_height);
                    printf("%c" ,' ');
                    gotoxy(bullet_width ,bullet_height+1);
                    printf("%c" ,' ');
                    bomber.hp--;
                }
                else{
                mine_explosion(bomber.width ,bomber.height);
                score += 1000;
                bomber.state = 0;
                bomber.height = 3;
                bullet_state = 0;
                gotoxy(bullet_width ,bullet_height-1);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height+1);
                printf("%c" ,' ');
                }
            }
            
        }
    }
    else if (bomber.state == 2)
    {
        if ((bullet_width == bomber.width) || (bullet_width == bomber.width-1) || (bullet_width == bomber.width + 1) || (bullet_width == bomber.width + 2) || (bullet_width == bomber.width-2))
        {
            if ((bullet_height == bomber.height) || (bullet_height == bomber.height + 1) || bullet_height == bomber.height -1)
            {
                if (bomber.hp >= 2)
                {
                    bomber.hp--;
                    bullet_state = 0;
                    gotoxy(bullet_width ,bullet_height-1);
                    printf("%c" ,' ');
                    gotoxy(bullet_width ,bullet_height);
                    printf("%c" ,' ');
                    gotoxy(bullet_width ,bullet_height+1);
                    printf("%c" ,' ');
                }
                else if ((bomber.hp == 1 ))
                {
                bomber_explosion(bomber.width ,bomber.height);
                score += 2000;
                bomber.state = 0;
                bomber.height = 3;
                bomber.hp = 1;
                bullet_state = 0;
                gotoxy(bullet_width ,bullet_height-1);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height+1);
                printf("%c" ,' ');
                }

            }
        }
        
    }
    if (e3.state == 1)
    {
        if ((bullet_width == e3.width) || (bullet_width == e3.width-1) || (bullet_width == e3.width + 1))
        {
            if ((bullet_height == e3.height) || (bullet_height == e3.height + 1) || bullet_height == e3.height -1)
            {
                if (e3.hp >= 2)
                {
                    bullet_state = 0;
                    gotoxy(bullet_width ,bullet_height-1);
                    printf("%c" ,' ');
                    gotoxy(bullet_width ,bullet_height);
                    printf("%c" ,' ');
                    gotoxy(bullet_width ,bullet_height+1);
                    printf("%c" ,' ');
                    e3.hp--;
                }
                else{
                mine_explosion(e3.width ,e3.height);
                score += 1000;
                e3.state = 0;
                e3.height = 3;
                bullet_state = 0;
                gotoxy(bullet_width ,bullet_height-1);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height+1);
                printf("%c" ,' ');
                }
            }
            
        }
    }

    if (e4.state == 1)
    {
        if ((bullet_width == e4.width) || (bullet_width == e4.width-1) || (bullet_width == e4.width + 1))
        {
            if ((bullet_height == e4.height) || (bullet_height == e4.height + 1) || bullet_height == e4.height -1)
            {
                if (e4.hp >= 2)
                {
                bullet_state = 0;
                gotoxy(bullet_width ,bullet_height-1);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height+1);
                printf("%c" ,' ');
                e4.hp --;
                }
                else{
                mine_explosion(e4.width ,e4.height);
                score += 1000;
                e4.state = 0;
                e4.height = 3;
                bullet_state = 0;
                gotoxy(bullet_width ,bullet_height-1);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height);
                printf("%c" ,' ');
                gotoxy(bullet_width ,bullet_height+1);
                printf("%c" ,' ');
                }
            }
            
        }
    }
    
}
void end_game()
{
    hp = 5;
    hp_width = 40;
    supply_ship.state = 0;
    supply_ship.height = 3;
    bomber.state = 0;
    bomber.height = 3;
    bomb1.state = 0;
    bomb2.state = 0;
    e3.state = 0;
    e3.height = 3;
    e4.state = 0;
    e4.height = 3;
    while (kbhit())
        getch();
    
    timer = clock() - timer;
    time_elapsed = ((double)timer) / CLOCKS_PER_SEC; /* calculate the elapsed time*/
    sprintf(time_string, "%0.2f", time_elapsed);
    sleep(2);
    system("cls");
    set_color(Blue);
    printf("%s" ,BOLD_ON);
    gotoxy(30 ,20);
    printf("game over!");
    gotoxy(30 ,21);
    printf("your score :%d" ,score / 10);
    score = 0;
    printf("%s" ,BOLD_OFF);
    gotoxy(30 ,22);
    printf("press ENTER key to continue...");
    while (1)
    {
        if (getch() == ENTER)
        {
            break;
        }
    }
    
    system("cls");
    gotoxy(25 ,20);
    printf("please enter your name below to save your game.");
    printf("%s" ,BOLD_ON);
    gotoxy(25 ,21);
    set_color(Red);
    printf("name:");
    set_color(Blue);
    gotoxy(31 ,21);
    gets(player_name);
    set_color(White);
    strcpy(line ,"player ");
    strcat(line ,player_name);
    strcat(line ," on record ");
    strcat(line ,time_string);
    strcat(line ," seconds  ---");
    final_time = time(NULL);
    time_info = localtime(&final_time);
    strcat(line ,asctime(time_info));
    fp = fopen("../scores.txt" ,"a+");
    fputs(line ,fp);
    fclose(fp);
    usleep(200000);
    scores_menu();
}
