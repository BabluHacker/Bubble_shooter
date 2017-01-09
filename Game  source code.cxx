#include <stdio.h>
#include <string.h>
#include "graphics.h"

#define WINX 1000
#define WINY 600
//global variabls..........
int pre_time;
int pre_score;

char score_card[10][60];

int flag_shoot=0;

int bubble[26][11];

int end=0;
int grow=0;
int time=0;
int y_ind;
int ind_y;
//background color define........
int back_col=BLACK;
int score=0;

int board;
int rul;

#define ARROW_SIZE 7
#define BALLOON_SIZE 3


//initial moving bubble color
int col=3;

void shadow_draw(int x, int y, int rad)
{
	setcolor(WHITE);
	arc(x,y,89,170,17);
	arc(x,y,87,168,15);
	arc(x,y,88,167,16);

	arc(x,y,87,169,14);
	arc(x,y,96,150,13);

}

void draw_ball(int x, int y,int rad)
{
	setcolor(col);
	setfillstyle(SOLID_FILL,col);
	fillellipse(x,y,rad,rad);


}

void draw_vertix_ball(int x,int y,int rad, int color)
{
	setcolor(color);
	setfillstyle(SOLID_FILL,color);
	fillellipse(x,y,rad,rad);

}

void erase_ball(int x,int y,int rad)
{
	setcolor(back_col);
	setfillstyle(SOLID_FILL,back_col);
	fillellipse(x,y,rad,rad);



}

void move_ball(int x,int y, int rad)
{
	int xx=x,yy=y;

	int ind_x=xx/(2*rad);
	int ind_y;
	int i;
	int bol=0;
	for( i=1;i<=10;i++ )
	{

		if(bubble[ind_x][i]==1 )
		{


			bol=1;
			ind_y=i+1;
			//for check in function
			y_ind=i+1;



			if(i==10)
			{
				end=1;

			}

		}


	}
	if(bol==0)
	{
		ind_y=1;

		y_ind=1;
	}
	bubble[ind_x][ind_y]=1;
	char out[60];
	int cou=0;
	while(1)
	{
		draw_ball(x,y,rad);
		shadow_draw(x,y,rad);
		if(cou<=2*rad)
		{
			draw_ball(xx,yy,rad);


			shadow_draw(xx,yy,rad);
		}
		cou++;
		if(ind_y*rad*2 == y )
			break;


		erase_ball(x,y,rad);
		y--;

	}




}


int check_in(int ind_bx,int ind_by,int rad)
{

	if((flag_shoot==0 && getpixel(ind_bx,(ind_by-1)*rad*2)==col) || (flag_shoot==0 && getpixel(((ind_bx-rad)/(2*rad)+1)*rad*2 + rad,(ind_by)*rad*2)==col) || (flag_shoot==0 && getpixel(((ind_bx-rad)/(2*rad)-1)*rad*2 + rad,(ind_by)*rad*2)==col))
	{
		erase_ball(ind_bx,(ind_by)*rad*2,rad);
		delay(50);
		grow+=50;

		score+=1;
		bubble[(ind_bx-rad)/(2*rad)][ind_by]=0;

		flag_shoot=1;


	}

	//ind_bx=== coordinate x axis
	//ind_by=== index of y axis
	if(getpixel(ind_bx,(ind_by-1)*rad*2)==col)
	{
		erase_ball(ind_bx,(ind_by-1)*rad*2,rad);
		delay(50);
		grow+=50;

		score+=1;
		bubble[(ind_bx-rad)/(2*rad)][ind_by-1]=0;

		check_in(ind_bx,ind_by-1,rad);

	}
	if(getpixel(ind_bx,(ind_by+1)*rad*2)==col)
	{
		erase_ball(ind_bx,(ind_by+1)*rad*2,rad);
		delay(50);
		grow+=50;

		score+=1;
		bubble[(ind_bx-rad)/(2*rad)][ind_by+1]=0;

		check_in(ind_bx,ind_by+1,rad);
	}

	if(getpixel(((ind_bx-rad)/(2*rad)+1)*rad*2 + rad,(ind_by)*rad*2)==col)
	{
		erase_ball(((ind_bx-rad)/(2*rad)+1)*rad*2 + rad ,(ind_by)*rad*2,rad);
		delay(50);
		grow+=50;

		score+=1;
		bubble[(ind_bx-rad)/(2*rad)+1][ind_by]=0;

		check_in(((ind_bx-rad)/(2*rad)+1)*rad*2 + rad ,ind_by,rad);
	}



	if(getpixel(((ind_bx-rad)/(2*rad)-1)*rad*2 + rad,(ind_by)*rad*2)==col)
	{
		erase_ball(((ind_bx-rad)/(2*rad)-1)*rad*2 + rad ,(ind_by)*rad*2,rad);
		delay(50);
		grow+=50;

		score+=1;
		bubble[(ind_bx-rad)/(2*rad)-1][ind_by]=0;

		check_in(((ind_bx-rad)/(2*rad)-1)*rad*2 + rad ,ind_by,rad);
	}




	return 0;


}



void initial_bubble(int rad)
{
	int i;

	//initial still bubble color
	int colo;
	//j= Y axis, i=X axis
	for(int j=1;j<=7;j++)
	{
		for(i=1;i<=23;i++)
		{

			colo=rand()%5 +1;
			draw_vertix_ball(i*rad*2 +rad, j*rad*2,rad,colo);
			shadow_draw(i*rad*2 +rad, j*rad*2, rad);
			bubble[i][j]=1;

		
		}
		
	}
}

void initial_game_window()
{

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,back_col);
	bar(0,0,1300,WINY);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,WHITE);
	bar(WINX+2,0,WINX+4,WINY);
}

int score_board()
{

	char score_line[100];


	readimagefile("score.jpg",0,0,1300,WINY);

	
	
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(GREEN);


	int len;
	int lineb=140;
	for(int l=0;l<10;l++)
	{
		len=strlen(score_card[l]);
		if(len==0)
			break;
		outtextxy(235,lineb,score_card[l]);
	
		lineb+=40;

	}


	int x,y;

	mouse_back_again:
	while (!ismouseclick(WM_LBUTTONDOWN))
    {
    }

	getmouseclick(WM_LBUTTONDOWN, x, y);
	printf("%d %d\n",x,y);
	clearmouseclick (WM_LBUTTONDOWN);
	if(x>=1126 && x<=1270 && y>=524 && y<=555)
	{
		return 1;

		printf("back\n");
	}
	else
	{
		goto mouse_back_again;
	}


}


void name_entry()
{

	char temp[100];

	memset(temp,0,sizeof(temp));
	
	char name_l[100];
	
	char cc;
	
	
	setbkcolor(BLACK);
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);

	setcolor(YELLOW);
	sprintf(name_l,"enter your nick name:");
	outtextxy(300,100,name_l);

	char name;
	int last_pos=0;

	for(int o=0;o<10;o++)
	{
		if(strlen(score_card[o])==0)
		{
			last_pos=o;
			break;
		}
	}

	int k=8;
	/////////////////score_card[last_pos]
	sprintf(temp,"   %d       %d     %d      ",pre_time-time,score,pre_time-time+score);
	outtextxy(300,200,temp);
	int nullity;
	for(int nul=0;nul<=34;nul++)
	{
		if(temp[nul]==0)
		{
			nullity=nul;
			break;
		}
	}
	int i=nullity;

	for(;i<46;)
	{
		temp[i]=(char)getch();
		setcolor(BLACK);
		setfillstyle(SOLID_FILL,BLACK);
		bar(300,200,1300,250);
		
		//enter ascii=10
		if(temp[i]=='\r')
		{
			temp[i]=0;
			break;
		}
		
		if(temp[i]==8)
		{
			temp[i]=0;
			temp[i-1]=0;
			i-=2;
		}
		//score_board[0][i]=0;
		puts(temp);
		
		settextstyle(BOLD_FONT, HORIZ_DIR, 4);
		setcolor(YELLOW);
		outtextxy(300,200,temp);
		i++;
	
	}
	//printing name and score..........
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	setcolor(YELLOW);

	outtextxy(300,200,temp);
	

	//total_score= (pre_time-time) + score
	int total_score=(pre_time-time) + score;

	//sorting.........
	int num=0,num1=0;
	char temp2[100];
	int f_s=0;
	for(int i=0;i<10;i++)
	{
		num=0;
		//strcpy(score_card[i],temp);
		int pow=1;
		for(int j=17;j>=8;j--)
		{
			if(score_card[i][j]>='0' && score_card[i][j]<='9')
			{
				num+=(score_card[i][j]-'0')*pow;
				pow*=10;
				
			}
		}
		printf("%d num:%d\n",i,num);
		num1=0;
		pow=1;
		for(int j=7;j>=2;j--)
		{
			if(score_card[i][j]>='0' && score_card[i][j]<='9')
			{
				num1+=(score_card[i][j]-'0')*pow;
				pow*=10;
			}
		}
		
		num1+=num;
		printf("%d num1:%d\n",i,num1);
		if(total_score>num1 && f_s==0)
		{
			printf("swap\n");
			strcpy(temp2,score_card[i]);
			strcpy(score_card[i],temp);
			strcpy(temp,temp2);
			f_s=1;
			printf("%d num1:%d\n",i,total_score);
			puts(temp);
		}
		
		else if(f_s==1)
		{
			for(int k=i;k<10;k++)
			{
				
				strcpy(temp2,score_card[k]);
				strcpy(score_card[k],temp);
				strcpy(temp,temp2);
			}
			break;
		}

	}

}

int print_rules()
{
	

	readimagefile("rules.jpg",0,0,1300,WINY);
	
	int x,y;

	mouse_back_again2:
	while (!ismouseclick(WM_LBUTTONDOWN))
    {
    }

	getmouseclick(WM_LBUTTONDOWN, x, y);
	printf("%d %d\n",x,y);
	clearmouseclick (WM_LBUTTONDOWN);
	if(x>=1126 && x<=1266 && y>=522 && y<=560)
	{
		return 1;

		printf("back\n");
	}
	else
	{
		goto mouse_back_again2;
	}


}

int challenge_select()
{
	printf("challenge\n");
	readimagefile("challenge.jpg",0,0,1300,WINY);

	int x,y;

	getmouse_again_ch:
	

	while (!ismouseclick(WM_LBUTTONDOWN))
    {
    }
	getmouseclick(WM_LBUTTONDOWN, x, y);
	printf(" mouse:  %d %d\n",x,y);
	clearmouseclick (WM_LBUTTONDOWN);

	if(x>=128 && x<=178 && y>=146 && y<=189)
	{
		pre_time=50;
		pre_score=40;

		printf("ch 1\n");
	}
	else if(x>=130 && x<=177 && y>=258 && y<=300)
	{
		pre_time=70;
		pre_score=60;

		printf("ch 2\n");
	}
	else if(x>=133 && x<=173 && y>=374 && y<=415)
	{
		pre_time=80;
		pre_score=80;
		printf("ch 3\n");
	}
	else if(x>=132 && x<=173 && y>=463 && y<=502)
	{
		pre_time=120;
		pre_score=150;
		printf("ch 4\n");
	}
	else if(x>=1114 && x<=1267 && y>=515 && y<=561)
	{
		return 1;
	}
	else
	{
		goto getmouse_again_ch;
	}

	return 0;
}

int menu_bar()
{
	mainmenu:

	board=0;
	rul=0;

	readimagefile("menu.jpg",0,0,1300,WINY);

	readimagefile("menu.jpg",0,0,1300,WINY);

	int x,y;

	getmouse_again:

	while (!ismouseclick(WM_LBUTTONDOWN))
    {
    }
	getmouseclick(WM_LBUTTONDOWN, x, y);
	printf(" mouse:  %d %d\n",x,y);
	clearmouseclick (WM_LBUTTONDOWN);
	if(x>=133 && x<=333 && y>=162 && y<=216)
	{
		//new game
		board=challenge_select();


	}
	else if(x>=125 && x<=386 && y>=258 && y<=313)
	{
		//////////score board will be here//////////
		board=score_board();
		printf("scorecard\n");
	}
	else if(x>=125 && x<=245 && y>=361 && y<=413)
	{
		//rules
		rul=print_rules();
	}
	else if(x>=116 && x<=232 && y>=462 && y<=513)
	{
		//quit
		return 1;
	}
	else
	{
		goto getmouse_again;
	}

	if(board==1 || rul==1)
	{
		goto mainmenu;
	}
	return 0;
}

int main()
{
	initwindow(1300,WINY,"dance with bubble is now Shoot The Bubble v.26.32.00 :P");

	//file purpose......
	FILE *f1;

	f1=fopen("score.txt","r");
	int l=0,k=0;
	char fc;
	while((fc=getc(f1)) != EOF)
	{

		if(fc=='\n')
		{
			score_card[l][k]=0;
			k=0;
			l++;
		}
		else
			score_card[l][k++]=fc;

	}
	fclose(f1);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,back_col);
	bar(0,0,1300,WINY);

	//beginning warning
	int t=250;
	readimagefile("loading0.jpg",0,0,1300,WINY);
	delay(t);
	readimagefile("loading1.jpg",0,0,1300,WINY);
	delay(t);
	readimagefile("loading2.jpg",0,0,1300,WINY);
	delay(t);
	readimagefile("loading3.jpg",0,0,1300,WINY);
	delay(t);
	readimagefile("loading0.jpg",0,0,1300,WINY);
	delay(t);
	readimagefile("loading1.jpg",0,0,1300,WINY);
	delay(t);
	readimagefile("loading2.jpg",0,0,1300,WINY);
	delay(t);
	readimagefile("loading3.jpg",0,0,1300,WINY);
	delay(t);
	
	char sen[100];
	//goto statement for restart game
	restart:
	end=0;

	////////////////////////////menu will be here/////////////////
	int fl=menu_bar();

	if(fl==1)
	{
		//file reserve............
		f1=fopen("score.txt","w");
		int len;
		for(int l=0;l<10;l++)
		{
			len=strlen(score_card[l]);
			if(len==0)
				break;
			for(int k=0;k<len; k++)
			{
				putc(score_card[l][k],f1);
			}
			putc('\n',f1);
		}
		fclose(f1);
		//quit..............
		return 0;
	}
	initial_game_window();


	int excact_time=pre_time;
	int excact_score=pre_score;

	//timing
	time=excact_time;
	for(int i=1;i<26;i++)
	{
		for(int j=1;j<11;j++)
		{
			bubble[i][j]=0;
		}
	}
	//define radious
	int rad=20;

	//fix bubbles....................
	initial_bubble(rad);
	int cx,cy;

	int x_fix=rad, y_fix=WINY-rad;
	cx=cy=rad;

	int cxx=4,cyy=3;

	int x=60,y=60;

	char s[100];

	//for score
	score=0;

	char sc[100];

	//for time
	grow=0;

	//initially arrow putting............
	readimagefile("ar.jpg",x_fix-rad,y_fix-4*rad,x_fix+rad,y_fix-2*rad);

	setbkcolor(BLACK);
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	setcolor(WHITE);
	sprintf(sc,"Bubble Taken: %d",score);
	outtextxy(WINX+20,40,sc);
	sprintf(sc,"___press q to quit___");
	outtextxy(WINX+20,80,sc);
	sprintf(sc,"___press r to reset___");
	outtextxy(WINX+20,110,sc);
	sprintf(sc,"Time: %d unit",time);
	outtextxy(WINX+20,150,sc);

	sprintf(sc,"Target: %d Bubble",excact_score);
	outtextxy(WINX+20,240,sc);

	sprintf(sc,"//copyright//");
	outtextxy(WINX+20,WINY-80,sc);

	sprintf(sc,"_Mehedi-26,Ruhit-32_");
	outtextxy(WINX+20,WINY-40,sc);

	draw_ball(x_fix,y_fix,rad);
	shadow_draw(x_fix,y_fix,rad);

	long long temp=0;
	char c;
	int mice_get,ind_fix_ball;
	//main loop (game ARC) :p.......................................................
	while(1)
	{
		grow++;
		if(grow>=600)
		{
			grow=0;
			time--;
		}
		if(time>=0 && score>=excact_score)
		{
			//bubble image finish................................................
			readimagefile("win3.jpg",0,0,1300,WINY);
			
			//settextstyle(BOLD_FONT, HORIZ_DIR, 5);
			setcolor(WHITE);
			settextstyle(BOLD_FONT, HORIZ_DIR, 3);
			
			//score print

			sprintf(sc,"Bubble Taken: %d",score);
			outtextxy(WINX+20,100,sc);
			sprintf(sc,"Time: %d unit",time);
			outtextxy(WINX+20,220,sc);
				
			delay(3000);
			
			setcolor(BLACK);
			setfillstyle(SOLID_FILL,BLACK);
			bar(0,0,1300,WINY);
			/////////////for score_card name entry will be here/////////////////
			name_entry();

			sprintf(sc,"completed name entry");
			outtextxy(500,300,sc);
			delay(1000);
			goto restart;

			

		}
		else if(time==0 && score<excact_score)
		{
			//bubble image finish................................................
			readimagefile("lose.jpg",0,0,1300,WINY);

			settextstyle(BOLD_FONT, HORIZ_DIR, 3);
			setcolor(WHITE);

			//score print

			sprintf(sc,"Bubble Taken: %d",score);
			outtextxy(WINX+20,200,sc);
			sprintf(sc,"Time: %d unit",time);
			outtextxy(WINX+20,270,sc);
			
			delay(3000);

			goto restart;

		}

		mice_get=mousex();

		ind_fix_ball=mice_get/(2*rad);
		
		int wall_fix=(2*rad*ind_fix_ball+rad);
		if(wall_fix!=x_fix && wall_fix>=rad && wall_fix<=WINX-rad)
		{
			//erase arrow....
			setcolor(back_col);
			setfillstyle(SOLID_FILL,back_col);		
			bar(x_fix-rad,y_fix-4*rad,x_fix+rad,y_fix-2*rad);
			//erase ball.....
			erase_ball(x_fix,y_fix,rad);

			x_fix=wall_fix;	
			draw_ball(x_fix,y_fix,rad);
			shadow_draw(x_fix,y_fix,rad);


			readimagefile("ar.jpg",x_fix-rad,y_fix-4*rad,x_fix+rad,y_fix-2*rad);

			grow+=5;

		}
		printf("run arc\n");

	
		if(ismouseclick(WM_LBUTTONDOWN) )
		{
			clearmouseclick (WM_LBUTTONDOWN);
			move_ball(x_fix,y_fix,rad);
			readimagefile("ar.jpg",x_fix-rad,y_fix-4*rad,x_fix+rad,y_fix-2*rad);
			delay(50);
			grow+=50;
			//check whether any bubble to shoot
			flag_shoot=0;
			check_in(x_fix,y_ind,rad);


			col=rand()%5 + 1;
			draw_ball(x_fix,y_fix,rad);
			shadow_draw(x_fix,y_fix,rad);

				

			if(end==1)
			{
				
				//bubble image finish................................................
				readimagefile("lose2.jpg",0,0,1300,WINY);
					
				settextstyle(BOLD_FONT, HORIZ_DIR, 3);
				setcolor(WHITE);

					
				//score print

				sprintf(sc,"Bubble Taken: %d",score);
				outtextxy(WINX+20,160,sc);
				sprintf(sc,"Time: %d unit",time);
				outtextxy(WINX+20,220,sc);
				delay(3000);

				goto restart;
					
			}


		}
		if(kbhit())
		{
			c=(char)getch();
			if(c=='q')
			{
				break;
			}
			else if(c=='r')
			{
				goto restart;
			}
		}
		

		else if(!kbhit())
		{
			delay(100);
			grow+=50;
		}
		
		//score print
		setbkcolor(BLACK);
		settextstyle(BOLD_FONT, HORIZ_DIR, 3);
		setcolor(WHITE);
		sprintf(sc,"Bubble Taken: %d",score);
		outtextxy(WINX+20,40,sc);
		
		
		sprintf(sc,"Time: %d unit",time);
		outtextxy(WINX+20,150,sc);

	}

	f1=fopen("score.txt","w");
	int len;
	for(int l=0;l<10;l++)
	{
		len=strlen(score_card[l]);
		if(len==0)
			break;
		for(int k=0;k<len; k++)
		{
			putc(score_card[l][k],f1);
		}
		putc('\n',f1);
	}


	return 0;
}
