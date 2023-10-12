#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#define COLOR_X 1
#define COLOR_Y 2


int numberoftasks;
void add_text(char *t)
{
	move(LINES/2 , (COLS-strlen(t))/2);
	while(*t)
	{
		addch(*t);
		refresh();
		napms(100);
		t++;
	}
}
//creates the list and highlights the particular task being selected
void create_list(int item , char tasks[][21])
{
	for(int i = 0 ; i < numberoftasks ; i++)
	{
		if(i == item)
		{
			attron(A_REVERSE);
			mvaddstr(3+(i*2), 20 , tasks[i]);
			attroff(A_REVERSE);
		}
		else
		{
			mvaddstr(3+(i*2) , 20 , tasks[i]);

		}

	}
	mvaddstr(14 , LINES/2 , "To move down press j ");
	mvaddstr(15 , LINES/2 , "To move up press k ");
	mvaddstr(16 , LINES/2 , "To switch to light/dark mode press d");
	mvaddstr(17 , LINES/2 , "If you have completed a task press enter");
	mvaddstr(18 , LINES/2 , "To exit the application press q");

	refresh();
}
//adds the line attribute to the task selected
void entered(int item , char tasks[][21])
{	
	int maxx , maxy ;
	getmaxyx(stdscr , maxy , maxx);
	for(int i = 0 ; i < maxx; i++)
	{
		mvaddch(3+(item*2) , i , ACS_HLINE);
	}
	refresh();
	
}
//to change the color_theme of the app
void change_mode(int mode)
{
	if(mode == 1)
	{
		init_color(COLOR_Y , 255 , 209 , 220);
		init_pair(2 , COLOR_Y , COLOR_BLACK);
		bkgd(COLOR_PAIR(2));

	}	
	else
	{
		init_color(COLOR_X, 117 , 80 , 123);
		init_pair(1, COLOR_X, COLOR_WHITE);
		bkgd(COLOR_PAIR(1));
	}	
	refresh();
}
int main()
{	
	
	char *welcome = {"TO DO Terminal App"};
	char *input = {"How many tasks do you want to schedule for today"};
	int mode = 0;
	initscr();
	start_color();
	change_mode(mode);
	add_text(welcome);
	clear();
	move(2,0);
	addstr(input);
	scanw(" %d " , &numberoftasks);
	char tasks[numberoftasks][21]; 
	move(4,0);
	move(5,0);
	addstr("Enter your tasks accordingly: ");
	refresh();
	for(int i = 0 ; i < numberoftasks ; i++)
	{
		scanw("%s",&tasks[i]);

	}
	clear();
	refresh();
	mvaddstr(1, LINES/2 , "To Do List");
	move(6 , 0);
	int ch;
	int listitem = 0;
	noecho();
	create_list(listitem , tasks);
	do
	{
		ch = getch();
		if(ch  == 106)
		{
		    if(listitem == numberoftasks - 1)
			    listitem = 0;
		    else
		    listitem++;
		}
		else if(ch  == 107)
		{
		    if(listitem == 0)
			    listitem = numberoftasks - 1;
		    else
		    listitem--;
		}

		else if(ch == 100)
		{
			if(mode == 0)
			 mode = 1;
			else
			 mode = 0;

			change_mode(mode);
		}

		else if(ch == 10)
		{
			entered(listitem , tasks);
		}
	
	create_list(listitem , tasks);
	}
	while(ch != 113);
	
	refresh();
	endwin();
	return 0;
}
