// Tutorials

/*
Jetron Adtoon 

https://www.youtube.com/watch?v=v2BhjHUfdd4  set the cursor
https://www.youtube.com/watch?v=ZetiT5VuACM  arrays
https://www.youtube.com/watch?v=exjQ_CoIhas a program

https://www.youtube.com/watch?v=9iGvTGVJZlE graphic moouse
https://khcomputerscience.blogspot.com/2015/07/interface-hospital-management-system.html

https://c.happycodings.com/gnu-linux/code26.html
*/

/*
https://www.tutorialspoint.com/cprogramming/c_memory_management.htm

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>

clrscr();
printf("lllj");
gotoxy(1,2);
printf("lllj");
scanf("d");
getch();
delay(1000);

_setcursortype(_NOCURSOR);

char field = "";

char links[] = "int", "100", "float", "1000", "float", "1000",  

char links[] = "fields", "", 

void database_fields (){}

for (database){
	
}

if (mysql_query(mysql_connection, "SELECT * FROM Cars")) 
{
  finish_with_error(con);
}

MYSQL_RES *mysql_result = mysql_store_result(con);

if (result == NULL) 
{
  finish_with_error(con);
}

int num_fields = mysql_num_fields(result);

MYSQL_ROW row;

while ((row = mysql_fetch_row(result))) 
{ 
  for(int i = 0; i < num_fields; i++) 
  { 
	  printf("%s ", row[i] ? row[i] : "NULL"); 
  } 
	  printf("\n"); 
}

mysql_free_result(result);
mysql_close(mysql_connection);

exit(0);
*/

#include<stdio.h>
#include<bios.h>
#include<conio.h>
#include<ctype.h>
#include<graphics.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>

enum TYPE {
    PASSWORD,
    INT,
    FLOAT,
    TEXT,
    ALL,
};

union REGS i,o;

int buttonm,xm,ym,gd=9,gm=1,close=1,set=1,midx,midy;

//declearation function

void getmousepos(int *buttonm,int *xm, int *ym);
void restrictmouse(int x1,int y1,int x2,int y2);
void showmouse();
int initmouse();
void setmousepos(int &xpos,int &ypos);
void hidemouse();
int menu(int);
int doctor();
void adddoc();
void deletedoc();
void searchdoc();
int patient();
void updatepat();
void searchpat();
void welgr();
void userl();
void notice();
void setusrl();
void changeusrl();
void removeusrl();
int dropmenu(char menu[7][20],int x1,int y1,int x2,int y2,int opt);
void button(char name[15],int x1,int y1,int x2,int y2,int c);
void clrwin(int opt);
void drawwindow(char head[30],int x1, int y1, int x2, int y2, int c);
int program();
void managetype();
int about();
int rooms();
void manageroom();
void input(int x,int y,char result[50],int limit ,int tc,int bkc,int type);
void inputbox(int x,int y,int limit,int bkc);

//end declearation

void main(){
	
	_setcursortype(0);
	initgraph(&gd,&gm,"..\\BGI");
	int menu1=-1;
	midx=getmaxx()/2;
	midy=getmaxy()/2;
	clrscr();
	welgr();
	setfillstyle(1,BLUE);
	bar(0,0,getmaxx(),getmaxy());
	setcolor(3);
	settextstyle(2,0,5);
	settextjustify(CENTER_TEXT, TOP_TEXT);
	outtextxy(midx,0,"==== Hospital Management System ====");
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(0,0,0);
	clrwin(2);
	restrictmouse(10,18,getmaxx()-10,getmaxy()-10);
	setmousepos(midx,midy);
	showmouse();
	getmousepos(&buttonm,&xm,&ym);
	menu(menu1);
	
 while(1){
	 
	showmouse();
	getmousepos(&buttonm,&xm,&ym);
	
	if(buttonm==1){
		
		if(xm>=10&&xm<=34&&ym>=18&&ym<=32){
			
			menu1=0;
		}
		else if(xm>=35&&xm<=94&&ym>=18&&ym<=32){
		 menu1=1;
		}
		else if(xm>=95&&xm<=169&&ym>=18&&ym<=32){
		 menu1=2;
		}else if(xm>=170&&xm<=219&&ym>=18&&ym<=32){
		 menu1=3;
		}else if(xm>=220&&xm<=269&&ym>=18&&ym<=32){
		 menu1=4;
		}else menu1=-1;
		
		clrwin(1);
		menu(menu1);
		
			switch(menu1){
				case 0:program();break;
				case 1:doctor();break;
				case 2:patient();break;
				case 3:rooms();break;
				case 4:about();break;
			}
		}
	}
}

//mouse function

int initmouse(){
	i.x.ax=0;//for  initialising mouse.
	int86(0x33,&i,&o);
	return (o.x.ax);
}

void showmouse(){
	i.x.ax=1; // for displaying mouse pointer.
	int86(0x33,&i,&o);
}

void hidemouse(){
 i.x.ax=2;
 int86(0x33,&i,&o);
}

void setmousepos(int &xpos,int &ypos){
 i.x.ax=4;
 i.x.cx=xpos;
 i.x.dx=ypos;
 int86(0x33,&i,&o);
}

void restrictmouse(int x1,int y1,int x2,int y2){
	i.x.ax=7;     //to define the upper left boundry of mouse.
	i.x.cx=x1;
	i.x.dx=x2;
	int86(0x33,&i,&o);
	i.x.ax=8;   //to define the bottom right boundry of mouse.
	i.x.cx=y1;
	i.x.dx=y2;
	int86(0x33,&i,&o);
}

void getmousepos(int *buttonm,int *x, int *y){
	i.x.ax=3; //to move mouse.
	int86(0x33,&i,&o);
	*buttonm=o.x.bx;
	*x=o.x.cx;
	*y=o.x.dx;
}
//end mouse function

int program(){
	
	int opt=-1,j;
	char menu[2][20]={"User Login >","Quit"};
	close=1;
	dropmenu(menu,10,33,131,76,opt);
	
	do{
		showmouse();
		getmousepos(&buttonm,&xm,&ym);
		
		if(xm>=10+10&&xm<=131-10&&ym>=33+8&&ym<=76-8&&buttonm==1){
	
		for(j=0;j<(76-33-8)/14;j++)
	
		if((ym-33-8)/14==j){
			 opt=j;
			 break;
		}
		
		dropmenu(menu,10,33,131,76,opt);
		switch(opt){
			case 0: userl();break;
			case 1: delay(100);cleardevice();closegraph();exit(0);
		}
		}else if(xm>=10&&xm<=34&&ym>=18&&ym<=32&&buttonm==1){
			dropmenu(menu,10,33,131,76,opt);
			continue;
		}else if(buttonm==1){
			break;
		}
	}while(close);
	return 0;
}

void userl(){
	
	int opt=-1,j;
	char menu[3][20]={"Set/Reset","Change","Remove"};
	dropmenu(menu,132,41,229,98,opt);
	
	do{
		
	showmouse();
	getmousepos(&buttonm,&xm,&ym);

	if(xm>=132+10&&xm<=229-10&&ym>=41+8&&ym<=98-8&&buttonm==1){
		for(j=0;j<(98-41-8)/14;j++)
		
	if((ym-41-8)/14==j){
		 opt=j;
		 break;
		}
		
		dropmenu(menu,132,41,229,98,opt);
		delay(200);
		switch(opt){
		case 0: setusrl();break;
		case 1: changeusrl();break;
		case 2: removeusrl();break;
		}
	}else if(buttonm==1){
	break;
	}
	}while(close);
	clrwin(1);
	}

void setusrl(){
	
	char head[30]="SET USER LOGIN";
	char usr[30]="",pwd[30]="",code[30]="";
	int a=midx/2+15+textwidth("Program Code : ");
	set=1;
	clrwin(2);
	drawwindow(head, midx/2, midy/2, (getmaxx()*3)/4, (getmaxy()*3)/4,1 );
	button("Set",midx+30,midy*3/2-22,midx+90,midy*3/2-8,7);
	button("Cancel",midx-90,midy*3/2-22,midx-30,midy*3/2-8,7);
	setcolor(15);moveto(midx/2+15,midy-26);
	outtext("Program Code :");inputbox(a,midy-26,15,15);
	setcolor(15);moveto(midx/2+15,midy-7);
	outtext("Username     :");inputbox(a,midy-7,15,15);
	setcolor(15);moveto(midx/2+15,midy+12);
	outtext("Password     :");inputbox(a,midy+12,15,15);
	
	do{
		
	getmousepos(&buttonm,&xm,&ym);
	
	if(buttonm==1){
	
		if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy-26-2&&ym<=midy-26+8){
			
			set=1;
		}
		
		if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy-7-2&&ym<=midy-7+8){
			
			set=2;
		}
		
		if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy+12-2&&ym<=midy+12+8){
			
			set=3;
		}
		if(xm>=midx-90&&ym>=midy*3/2-22&&xm<=midx-30&&ym<=midy*3/2-8){
			
			button("Cancel",midx-90,midy*3/2-22,midx-30,midy*3/2-8,3);
			delay(100);close=0;set=0;
		}

	if(xm>=midx+30&&ym>=midy*3/2-22&&xm<=midx+90&&ym<=midy*3/2-8&&strlen(code)>0&&strlen(usr)>0&&strlen(pwd)>0){
		button("Set",midx+30,midy*3/2-22,midx+90,midy*3/2-8,3);
		delay(100);notice();close=0;set=0;
		}
	}
	
	if(set==4)set=1;
	if(set==1)
	input(a,midy-26,code,15 ,0,15,INT);
	if(set==2)
	input(a,midy-7,usr,15 ,0,15,TEXT);
	if(set==3)
	input(a,midy+12,pwd,15 ,0,15,PASSWORD);
	}while(close);
	
}

void changeusrl(){
 
	char head[30]="CHANGE USER LOGIN";
	char cusr[30]="",cpwd[30]="";
	int a=midx/2+15+textwidth("Current Username : ");
	set=1;

	//display before input data
	clrwin(2);
	drawwindow(head, midx/2, midy/2, (getmaxx()*3)/4, (getmaxy()*3)/4,1 );
	button("OK",midx+30,midy*3/2-22,midx+90,midy*3/2-8,7);
	button("Cancel",midx-90,midy*3/2-22,midx-30,midy*3/2-8,7);
	setcolor(15);moveto(midx/2+15,midy-26);
	outtext("Current Username :");inputbox(a,midy-26,15,15);
	setcolor(15);moveto(midx/2+15,midy+12);
	outtext("Current Password :");inputbox(a,midy+12,15,15);
 
	//start input data
	do{
		
		getmousepos(&buttonm,&xm,&ym);
		if(buttonm==1){
		if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy-26-2&&ym<=midy-26+8){
		set=1;
		}
		if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy+12-2&&ym<=midy+12+8){
		set=2;
		}
		if(xm>=midx-90&&ym>=midy*3/2-22&&xm<=midx-30&&ym<=midy*3/2-8){
		button("Cancel",midx-90,midy*3/2-22,midx-30,midy*3/2-8,3);
		delay(100);close=0;set=0;
		}

		if(xm>=midx+30&&ym>=midy*3/2-22&&xm<=midx+90&&ym<=midy*3/2-8&&strlen(cusr)>0&&strlen(cpwd)>0){
		button("OK",midx+30,midy*3/2-22,midx+90,midy*3/2-8,3);
		delay(100);notice();close=0;set=0;
		}
		}
		if(set==3)set=1;
		if(set==1)
		input(a,midy-26,cusr,15 ,0,15,TEXT);
		if(set==2)
		input(a,midy+12,cpwd,15 ,0,15,PASSWORD);
	}while(close);
}

void notice(){
 char head[30]="Notification";
 clrwin(2);
 drawwindow(head, midx/2, midy/2, (getmaxx()*3)/4, (getmaxy()*3)/4,9);
 button("OK",midx-30,midy*3/2-22,midx+30,midy*3/2-8,7);
 settextstyle(7,0,4);
 setcolor(15);
 outtextxy(midx-((17/2)*17),midy-25,"It Just Interface");
 settextstyle(0,0,0);
 do{
  getmousepos(&buttonm,&xm,&ym);
  if(buttonm==1){
   if(xm>=midx-30&&ym>=midy*3/2-22&&xm<=midx+30&&ym<=midy*3/2-8){
    button("OK",midx-30,midy*3/2-22,midx+30,midy*3/2-8,3);
    delay(100);close=0;;
   }
  }
 }while(close);
}

void removeusrl(){
 char head[30]="REMOVE USER LOGIN";
 char usr[30]="",pwd[30]="";
 int a=midx/2+15+textwidth("Username : ");
 set=1;
 clrwin(2);
 drawwindow(head, midx/2, midy/2, (getmaxx()*3)/4, (getmaxy()*3)/4,1 );
 button("Remove",midx+30,midy*3/2-22,midx+90,midy*3/2-8,7);
 button("Cancel",midx-90,midy*3/2-22,midx-30,midy*3/2-8,7);
 setcolor(15);moveto(midx/2+15,midy-26);
 outtext("Username :");inputbox(a,midy-26,15,15);
 setcolor(15);moveto(midx/2+15,midy+12);
 outtext("Password :");inputbox(a,midy+12,15,15);
 do{
  getmousepos(&buttonm,&xm,&ym);
  if(buttonm==1){
   if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy-26-2&&ym<=midy-26+8){
    set=1;
   }
   if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy+12-2&&ym<=midy+12+8){
    set=2;
   }
   if(xm>=midx-90&&ym>=midy*3/2-22&&xm<=midx-30&&ym<=midy*3/2-8){
    button("Cancel",midx-90,midy*3/2-22,midx-30,midy*3/2-8,3);
    delay(100);close=0;set=0;
   }

   if((xm>=midx+30&&ym>=midy*3/2-22&&xm<=midx+90&&ym<=midy*3/2-8)&&strlen(usr)>0&&strlen(pwd)>0){
    button("Remove",midx+30,midy*3/2-22,midx+90,midy*3/2-8,3);
    delay(100);notice();close=0;set=0;
   }
  }
  if(set==3)set=1;
  if(set==1)
   input(a,midy-26,usr,15 ,0,15,TEXT);
  if(set==2)
   input(a,midy+12,pwd,15 ,0,15,PASSWORD);
  }while(close);
}

void input(int x,int y,char result[50],int limit ,int tc,int bkc,int type){
 char ch,text[2]="";
 int i=0,f=-1,key,j;
 close=1;
 hidemouse();
 setcolor(3);
 rectangle(x-3,y-3,x+limit*8+2,y+9);
 setfillstyle(1,bkc);
 bar(x-2,y-2,x+limit*8+1,y+8);
 showmouse();
 settextstyle(0,0,1);
 i=strlen(result);
 moveto(x,y);
 if(i>0){
  setcolor(tc);
  hidemouse();
  if(type!=0)
   outtext(result);
  else
   for(j=0;j<i;j++)
    outtext("*");
  showmouse();
 }
 if(i>0&&strstr(result,".")!=0){
  for(j=0;j<i;j++)
   if(result[j]=='.')
    break;
   f=j;
 }
 while(kbhit()){
  getch();
 }
 do{
  do{     hidemouse();
   setcolor(tc);
   line(x+i*8,y-1,x+i*8,y+7);
   showmouse();
   getmousepos(&buttonm,&xm,&ym);
   if(buttonm==1){
    if(xm<x-2||xm>x+limit*8+1||ym<y-2||ym>y+8){
     close=0;
     hidemouse();
     setcolor(bkc);
     line(x+i*8,y-1,x+i*8,y+7);
     showmouse();
     goto end;
    }
   }
   if(kbhit()){
    hidemouse();
    setcolor(bkc);
    line(x+i*8,y-1,x+i*8,y+7);
    showmouse();
    break;
   }else
    delay(100);
   hidemouse();
   setcolor(bkc);
   line(x+i*8,y-1,x+i*8,y+7);
   showmouse();
   getmousepos(&buttonm,&xm,&ym);
   if(buttonm==1){
    if(xm<x-2||xm>x+limit*8+1||ym<y-2||ym>y+8){
     close=0;
     hidemouse();
     setcolor(bkc);
     line(x+i*8,y-1,x+i*8,y+7);
     showmouse();
     goto end;
    }
   }
   if(!kbhit())
    delay(100);
  }while(bioskey(1)==0);
  key = bioskey(0);
  ch = key & 0xFF;
  hidemouse();
  if(type==3&&(isalpha(ch)||ch == ' ')&&i<limit){
   result[i++] = ch;
   text[0] = ch;
   text[1] = '\0';
   setcolor(tc);
   outtext(text);
  }
  if((type==1&&isdigit(ch)&&i<limit)||(((ch == '.'&&f==-1)||isdigit(ch))&&type==2&&i<limit)){
   if(ch=='.')
    f=i;
   result[i++] = ch;
   text[0] = ch;
   text[1] = '\0';
   setcolor(tc);
   outtext(text);
  }
  if((type==0||type==4)&&(isalpha(ch)||(ch>='!'&&ch<='@')||ch==95||ch == ' ')&&i<limit){//ch=95=_
   result[i++] = ch;
   text[0] = ch;
   text[1] = '\0';
   setcolor(tc);
   if(type==4)
    outtext(text);
   else
    outtext("*");
  }

  if(ch == 8 && i > 0){
   i--;
   if(i==f)
    f=-1;
   text[0] = result[i];
   text[1] = '\0';
   result[i] = '\0';
   setcolor(bkc);
   moveto(x+(i)*(textwidth(text)),y);
   if(type!=0)
    outtext(text);
   else
    outtext("*");
   moveto(x+textwidth(result),y);
  }
  if(type==0&&key==20992){//key=20992:insert key
   moveto(x,y);
   hidemouse();
   for(int j=0;j<i;j++){
    setcolor(bkc);
    outtext("*");//delete by outtext in same color to bkc;
   }
   result[i]='\0';
   moveto(x,y);
   setcolor(tc);
   outtext(result);
   showmouse();
   delay(70);
   if(!kbhit())
    delay(270);
   moveto(x,y);
   hidemouse();
   setcolor(bkc);
   outtext(result);
   moveto(x,y);
   setcolor(0);
   for(j=0;j<i;j++)
    outtext("*");
   showmouse();
  }
end: showmouse();
 }while(close==1);
 result[i]='\0';
 close=1;
 hidemouse();
 setfillstyle(1,bkc);
 rectangle(x-3,y-3,x+limit*8+2,y+9);
 setcolor(0);
 line(x-3,y-3,x-3,y+9);
 line(x-3,y-3,x+limit*8+2,y-3);
 showmouse();
}

void inputbox(int x,int y,int limit,int bkc){
 hidemouse();
 setfillstyle(1,bkc);
 bar(x-2,y-2,x+limit*8+2,y+8);
 setcolor(0);
 line(x-3,y-3,x-3,y+9);
 line(x-3,y-3,x+limit*8+2,y-3);
 showmouse();
}

int rooms(){
 char menu[4][20]={"All rooms","Available","Manage room >","Manage type >"};
 int opt=-1,j;
 close=1;
 
 dropmenu(menu,170,33,300,104,opt);
 do{
  showmouse();
  getmousepos(&buttonm,&xm,&ym);
  if(xm>=170+10&&xm<=300-10&&ym>=33+8&&ym<=104-8&&buttonm==1){
   for(j=0;j<(104-33-8)/14;j++)
    if((ym-33-8)/14==j){
     opt=j;
     break;
    }
   dropmenu(menu,170,33,300,104,opt);
   switch(opt){
    case 0:notice();break;
    case 1:notice();break;
    case 2:manageroom();break;
    case 3:managetype();break;
   }
  }else if(xm>=170&&xm<=219&&ym>=18&&ym<=32&&buttonm==1){
   dropmenu(menu,170,33,300,104,opt);
   continue;
  }else if(buttonm==1){
    break;
   }
 }while(close);
 return 3;
}

void manageroom(){
 int opt=-1,j;
 char menu[3][20]={"Add new","Delete","Update"};
 dropmenu(menu,301,69,387,126,opt);
 do{
  getmousepos(&buttonm,&xm,&ym);
  if(xm>=301+10&&xm<=387-10&&ym>=69+8&&ym<=126-8&&buttonm==1){
   for(j=0;j<(126-69-8)/14;j++)
    if((ym-69-8)/14==j){
     opt=j;
     break;
    }
   dropmenu(menu,301,69,387,126,opt);
   delay(200);
   switch(opt){
    case 0: notice();break;
    case 1: notice();break;
    case 2: notice();break;
   }
  }else if(buttonm==1){
   break;
  }
 }while(close);
 clrwin(1);
}
void managetype(){
 int opt=-1,j;
 char menu[3][20]={"Add new","Delete","All types"};
 dropmenu(menu,301,83,397,140,opt);
 do{
  getmousepos(&buttonm,&xm,&ym);
  if(xm>=301+10&&xm<=397-10&&ym>=83+8&&ym<=140-8&&buttonm==1){
   for(j=0;j<(140-83-8)/14;j++)
    if((ym-83-8)/14==j){
     opt=j;
     break;
    }
   dropmenu(menu,301,83,397,140,opt);
   delay(200);
   switch(opt){
    case 0: notice();break;
    case 1: notice();break;
    case 2: notice();break;
   }
  }else if(buttonm==1){
   break;
  }
 }while(close);
 clrwin(1);
}

int about(){
 char str[3][35]={"Project : HMS Interface","Created by : VITOU SRUN"};
 close=1;
 drawwindow("About me", midx/2, midy/2, (getmaxx()*3)/4, (getmaxy()*3)/4,1 );
 settextstyle(0,0,1);
 setcolor(15);
 for(int i=0;i<2;i++)
 outtextxy(midx/2+15,midy-50+(i*20),str[i]);
 outtextxy(midx/2+15,midy-10,"Detail : This project I just want to"); 
 outtextxy(midx/2+15,midy+10,"         show you a partof C that it");
 outtextxy(midx/2+15,midy+30,"         can make our project better.");
 button("OK",midx-30,midy*3/2-22,midx+30,midy*3/2-8,7);
 
 do{
  getmousepos(&buttonm,&xm,&ym);
  if(buttonm==1){
   if(xm>=midx-30&&ym>=midy*3/2-22&&xm<=midx+30&&ym<=midy*3/2-8){
    button("OK",midx-30,midy*3/2-22,midx+30,midy*3/2-8,3);
    delay(100);close=0;;
   }
  }
 }while(close);
 return 4;
}

int doctor(){
 char menu[5][20]={"Add","Update","Delete    >","Search    >","View"};
 int opt=-1,j;
 close=1;
 dropmenu(menu,35,33,150,118,opt);
 do{
  showmouse();
  getmousepos(&buttonm,&xm,&ym);
  if(xm>=35+10&&xm<=150-10&&ym>=33+8&&ym<=118-8&&buttonm==1){
   for(j=0;j<(118-33-8)/14;j++)
    if((ym-33-8)/14==j){
     opt=j;
     break;
    }
   dropmenu(menu,35,33,150,118,opt);
   switch(opt){
    case 0:adddoc();break;
    case 1:notice();break;
    case 2:deletedoc();break;
    case 3:searchdoc();break;
    case 4:notice();break;
   }
  }else if(xm>=35&&xm<=94&&ym>=18&&ym<=32&&buttonm==1){
   dropmenu(menu,35,33,150,118,opt);
   continue;
  }else if(buttonm==1){
   break;
  }
 }while(close);
 clrwin(1);
 return 1;
}

void adddoc(){
 char head[30]="SET USER LOGIN";
 char usr[30]="",pwd[30]="",code[30]="";
 int a=midx/8+15+textwidth("Program Code : ");
 set=1;
 clrwin(2);
 drawwindow(head, midx/8, midy/4+16, (getmaxx()*15)/16, (getmaxy()*7)/8+16,1 );
 button("Set",midx+30,midy*3/2-22,midx+90,midy*3/2-8,7);
 button("Cancel",midx-90,midy*3/2-22,midx-30,midy*3/2-8,7);
 setcolor(15);moveto(a-textwidth("Program Code : "),midy-26);
 outtext("Program Code :");inputbox(a,midy-26,15,15);
 setcolor(15);moveto(a-textwidth("Program Code : "),midy-7);
 outtext("Username     :");inputbox(a,midy-7,15,15);
 setcolor(15);moveto(a-textwidth("Program Code : "),midy+12);
 outtext("Password     :");inputbox(a,midy+12,15,15);
 do{
  getmousepos(&buttonm,&xm,&ym);
  if(buttonm==1){
   if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy-26-2&&ym<=midy-26+8){
    set=1;
   }
   if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy-7-2&&ym<=midy-7+8){
    set=2;
   }
   if(xm>=a-2&&xm<=a+15*8+1&&ym>=midy+12-2&&ym<=midy+12+8){
    set=3;
   }
   if(xm>=midx-90&&ym>=midy*3/2-22&&xm<=midx-30&&ym<=midy*3/2-8){
    button("Cancel",midx-90,midy*3/2-22,midx-30,midy*3/2-8,3);
    delay(100);close=0;set=0;
   }

   if(xm>=midx+30&&ym>=midy*3/2-22&&xm<=midx+90&&ym<=midy*3/2-8&&strlen(code)>0&&strlen(usr)>0&&strlen(pwd)>0){
    button("Set",midx+30,midy*3/2-22,midx+90,midy*3/2-8,3);
    delay(100);close=0;set=0;
   }
  }
  if(set==4)set=1;
  if(set==1)
   //inputdat(a,midy-26,day,mon,year ,0,15);
   input(a,midy-26,code,15 ,0,15,INT);
  if(set==2)
   input(a,midy-7,usr,15 ,0,15,TEXT);
  if(set==3)
   input(a,midy+12,pwd,15 ,0,15,PASSWORD);
  }while(close);
}

void deletedoc(){
	
	int opt=-1,j;
	char menu[3][20]={"By ID","By Name"};
	dropmenu(menu,151,69,237,112,opt);
	
	do{
		getmousepos(&buttonm,&xm,&ym);
		if(xm>=151+10&&xm<=237-10&&ym>=69+8&&ym<=112-8&&buttonm==1){
			
			for(j=0;j<(112-69-8)/14;j++)
				if((ym-69-8)/14==j){
					opt=j;
					break;
		}
		dropmenu(menu,151,69,237,112,opt);
		delay(200);
		switch(opt){
		case 0: notice();break;
		case 1: notice();break;
		}
		}else if(buttonm==1){
		break;
		}
	}while(close);
	clrwin(1);
}

void searchdoc(){
	
	int opt=-1,j;
	char menu[4][20]={"By ID","By Last Name","By First Name","By Specialty"};
	dropmenu(menu,151,83,285,154,opt);
 
	do{
		getmousepos(&buttonm,&xm,&ym);
		if(xm>=151+10&&xm<=285-10&&ym>=83+8&&ym<=154-8&&buttonm==1){
		for(j=0;j<(154-83-8)/14;j++)
		if((ym-83-8)/14==j){
		opt=j;
		break;
	}
	
	dropmenu(menu,151,83,285,154,opt);
	delay(200);
	
	switch(opt){
		case 0: notice();break;
		case 1: notice();break;
		case 2: notice();break;
		case 3: notice();break;
	}
	}else if(buttonm==1){
		break;
	}
	}while(close);
	clrwin(1);
}

int patient(){
	
	char menu[5][20]={"Check in","Check out","Update    >","Search    >","View"};
	int opt=-1,j;
	close=1;
	dropmenu(menu,95,33,210,118,opt);
	
	do{ showmouse();
	getmousepos(&buttonm,&xm,&ym);
	if(xm>=95+10&&xm<=210-10&&ym>=33+8&&ym<=118-8&&buttonm==1){
		for(j=0;j<(118-33-8)/14;j++)
			if((ym-33-8)/14==j){
				opt=j;
				break;
	}
	
	dropmenu(menu,95,33,210,118,opt);
	switch(opt){
		case 0:notice();break;
		case 1:notice();break;
		case 2:updatepat();break;
		case 3: searchpat();break;
		case 4:notice();break;
	}
	}else if(xm>=95&&xm<=169&&ym>=18&&ym<=32&&buttonm==1){
	dropmenu(menu,95,33,210,118,opt);
	continue;
	}else if(buttonm==1){
	break;
	}
	}while(close);
	return 2;
}

void updatepat(){
 int opt=-1,j;
 char menu[3][20]={"All","Name","Room"};
 dropmenu(menu,211,69,273,126,opt);
 do{
  getmousepos(&buttonm,&xm,&ym);
  if(xm>=211+10&&xm<=273-10&&ym>=69+8&&ym<=126-8&&buttonm==1){
   for(j=0;j<(126-69-8)/14;j++)
    if((ym-69-8)/14==j){
     opt=j;
     break;
    }
   dropmenu(menu,211,69,273,126,opt);
   delay(200);
   switch(opt){
    case 0: notice();break;
    case 1: notice();break;
   }
  }else if(buttonm==1){
   break;
  }
 }while(close);
 clrwin(1);
}

void searchpat(){
 int opt=-1,j;
 char menu[5][20]={"By ID","By Room","By Last Name","By First Name","By Chickin Date"};
 dropmenu(menu,211,83,361,168,opt);
 do{
  getmousepos(&buttonm,&xm,&ym);
  if(xm>=211+10&&xm<=361-10&&ym>=83+8&&ym<=168-8&&buttonm==1){
   for(j=0;j<(168-83-8)/14;j++)
    if((ym-83-8)/14==j){
     opt=j;
     break;
    }
   dropmenu(menu,211,83,361,168,opt);
   delay(200);
   switch(opt){
    case 0: notice();break;
    case 1: notice();break;
    case 2: notice();break;
    case 3: notice();break;
    case 4: notice();break;
   }
  }else if(buttonm==1){
   break;
  }
 }while(close);
 clrwin(1);
}

int dropmenu(char menu[7][20],int x1,int y1,int x2,int y2,int opt){
	 
	 int i;
	 char ch;
	 setfillstyle(1,14);
	 setcolor(15);
	 hidemouse();
	 line(x1,y1,x2,y1);
	 line(x1,y1,x1,y2);
	 setcolor(0);
	 line(x2,y1,x2,y2);
	 line(x1,y2,x2,y2);
	 bar(x1+1,y1+1,x2-1,y2-1);
	 rectangle(x1+5,y1+5,x2-5,y2-5);
	 
	 for(i=0;i<(y2-y1-15)/14;i++){
	  if(i==opt){
	  setcolor(15);
	  setfillstyle(1,3);
	  bar(x1+10,y1+8+(i*14),x2-10,y1+20+(i*14));
	  outtextxy(x1+15,y1+10+(i*14),menu[i]);
	  }else{
	   setcolor(0);
	   outtextxy(x1+15,y1+10+(i*14),menu[i]);
	  }
	 }
	 
	 showmouse();
	 delay(100);
	 return opt;
}

void button(char name[15],int x1,int y1,int x2 ,int y2,int c){
	setfillstyle(1,c);
	setcolor(15);
	hidemouse();
	line(x1,y1,x2,y1);
	line(x1,y1,x1,y2);
	setcolor(0);
	line(x2,y1,x2,y2);
	line(x1,y2,x2,y2);
	bar(x1+1,y1+1,x2-1,y2-1);
	outtextxy((x2+x1-textwidth(name))/2,(y2+y1-textheight(name))/2,name);
	showmouse();
}

void drawwindow(char head[30],int x1, int y1, int x2, int y2, int c){
	
 hidemouse();
 setfillstyle(1,7);
 bar(x1,y1-14,x2,y1-2);
 setfillstyle(1,c);
 bar(x1,y1,x2,y2);
 setcolor(15);
 line(x1-1,y1-15,x2+1,y1-15);
 line(x1-1,y1-15,x1-1,y2+1);
 setcolor(0);
 line(x2+1,y1-14,x2+1,y2+1);
 line(x1-1,y2+1,x2+1,y2+1);
 line(x1,y1-1,x2,y1-1);
 setcolor(15);
 rectangle(x1+5,y1+5,x2-5,y2-5);
 setcolor(0);
 settextstyle(0,0,1);
 outtextxy((x2+x1-textwidth(head))/2,y1-12,head);
 showmouse();

}

int menu(int select){
 char ch, menu[5][20]={"\360","Doctor","Patient","Room","About"};
 char date[11];
 struct date da;
 hidemouse();
 setfillstyle(1,3);
 setcolor(15);
 line(9,17,631,17);
 line(9,17,9,32);
 setcolor(0);
 line(631,18,631,32);
 bar(10,18,630,32);
 getdate(&da);
 setcolor(0);
 outtextxy(20,21,menu[0]);
 outtextxy(40,21,menu[1]);
 outtextxy(105,21,menu[2]);
 outtextxy(180,21,menu[3]);
 outtextxy(230,21,menu[4]);
 showmouse();
  switch(select){
   case 0: hidemouse();
    setfillstyle(9,9);
    setcolor(0);
    line(10,18,34,18);
    line(10,18,10,31);
    setcolor(15);
    line(35,18,35,32);
    line(10,32,35,32);
    bar(11,19,34,31);
    outtextxy(20,21,menu[0]);
    break;
   case 1: hidemouse();
    setfillstyle(9,9);
    setcolor(0);
    line(35,18,35,31);
    line(35,18,95,18);
    setcolor(15);
    line(95,18,95,32);
    line(35,32,95,32);
    bar(36,19,94,31);
    outtextxy(40,21,menu[1]);
    break;
   case 2: hidemouse();
    setfillstyle(9,9);
    setcolor(0);
    line(95,18,169,18);
    line(95,18,95,32);
    setcolor(15);
    line(170,18,170,31);
    line(95,32,170,32);
    bar(96,19,169,31);
    outtextxy(105,21,menu[2]);
    break;
   case 3: hidemouse();
    setfillstyle(9,9);
    setcolor(0);
    line(170,18,219,18);
    line(170,18,170,32);
    setcolor(15);
    line(220,18,220,31);
    line(170,32,220,32);
    bar(171,19,219,31);
    outtextxy(180,21,menu[3]);
    break;
   case 4: hidemouse();
    setfillstyle(9,9);
    setcolor(0);
    line(220,18,279,18);
    line(220,18,220,32);
    setcolor(15);
    line(221,32,279,32);
    line(280,18,280,32);
    bar(221,19,279,31);
    outtextxy(230,21,menu[4]);
    break;
  }
  sprintf(date,"%02d/%02d/%d",da.da_day,da.da_mon,da.da_year);
  setcolor(0);
  outtextxy(550,21,date);
  showmouse();
 return select;
}

void welgr(){
 clrscr();
 int i, a=(getmaxx()-textwidth("<<<               >>>"))/2;
 setfillstyle(1,BLUE);
 bar(0,0,getmaxx(),getmaxy());
 setcolor(15);
 settextstyle(4, 0, 9);
 outtextxy((getmaxx()-textwidth("Hospital"))/2,1,"Hospital");
 outtextxy((getmaxx()-textwidth("Management"))/2,100,"Management");
 outtextxy((getmaxx()-textwidth("System"))/2,200,"System");
 setfillstyle(1,15);
 bar(50,20,80,110);
 bar(20,50,110,80);
 bar(getmaxx()-50,20,getmaxx()-80,110);
 bar(getmaxx()-20,50,getmaxx()-110,80);
 setcolor(9);
 line(18,48,48,48);
 line(82,48,112,48);
 line(18,82,48,82);
 line(82,82,112,82);
 line(48,18,82,18);
 line(48,112,82,112);
 line(18,48,18,82);
 line(112,48,112,82);
 line(48,18,48,48);
 line(82,18,82,48);
 line(48,82,48,112);
 line(82,82,82,112);

 line(getmaxx()-18,48,getmaxx()-48,48);
 line(getmaxx()-82,48,getmaxx()-112,48);
 line(getmaxx()-18,82,getmaxx()-48,82);
 line(getmaxx()-82,82,getmaxx()-112,82);
 line(getmaxx()-48,18,getmaxx()-82,18);
 line(getmaxx()-48,112,getmaxx()-82,112);
 line(getmaxx()-18,48,getmaxx()-18,82);
 line(getmaxx()-112,48,getmaxx()-112,82);
 line(getmaxx()-48,18,getmaxx()-48,48);
 line(getmaxx()-82,18,getmaxx()-82,48);
 line(getmaxx()-48,82,getmaxx()-48,112);
 line(getmaxx()-82,82,getmaxx()-82,112);
 do{
 settextstyle(0, 0, 1);
 setcolor(BLUE);
 outtextxy(a,getmaxy()-15,"<<<               >>>");
 setcolor(2);
 outtextxy(a,getmaxy()-15,"    PRESS ANY KEY    ");
 delay(250);if(kbhit()){getch();break;}
 setcolor(BLUE);
 outtextxy(a,getmaxy()-15,"<<<               >>>");
 setcolor(2);
 outtextxy(a,getmaxy()-15,"  < PRESS ANY KEY >  ");
 delay(250);if(kbhit()){getch();break;}
 setcolor(BLUE);
 outtextxy(a,getmaxy()-15,"<<<               >>>");
 setcolor(2);
 outtextxy(a,getmaxy()-15," << PRESS ANY KEY >> ");
 delay(250);if(kbhit()){getch();break;}
 setcolor(BLUE);
 outtextxy(a,getmaxy()-15,"<<<               >>>");
 setcolor(2);
 outtextxy(a,getmaxy()-15,"<<< PRESS ANY KEY >>>");
 delay(250);if(kbhit()){getch();break;}
 }while(1);
 setcolor(0);
 for(i=0;i<getmaxy()/4;i++){
  delay(20);
  rectangle(midy-i,midy-i,getmaxx()+i-midy,midy+i);
  rectangle(i,i,getmaxx()-i,getmaxy()-i);
 }
}

void clrwin(int opt){
 if(opt==2)
	  menu(-1);
	 hidemouse();
	 setcolor(0);
	 line(9,33,631,33);
	 line(9,34,9,340);
	 setcolor(15);
	 line(631,34,631,339);
	 line(10,340,631,340);
	 setfillstyle(1,11);
	 bar(10,34,630,339);
	 showmouse();
}


