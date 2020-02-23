#include <graphics.h>

int main()
{
   int gd = DETECT, gm;
   int x = 320, y = 240, radius;

   initgraph(&gd, &gm, "C:\\TC\\BGI");

   for ( radius = 25; radius <= 125 ; radius = radius + 20)
      circle(x, y, radius);

   getch();
   closegraph();
   return 0;
}

#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>

void func_exit();

void func_circle();

void func_line();

void func_pixel();

void func_triangle();

void func_rectangle();

 

enum ITEMTYPE

{

      MI_PARENT, MI_ACTION

};

 

struct MENUITEM {

      enum ITEMTYPE type;

      char *name;

      char *helpstring;

      void *p;

 

};

 

struct MENU {

      int vertical;

      char *name;

      int left;

      int top;

      int right;

      int bottom;

      int count;

      struct MENUITEM **menuitemlist;

      int curritem;

      struct MENU *parent;

};

 

struct MENUITEM draw_circle = {

      MI_ACTION, "Circle", "Enter to draw the animated Circles", (void*) func_circle

};

 

struct MENUITEM draw_line = {

      MI_ACTION, "Line", "Enter to draw the animated Lines", (void*) func_line

};

 

struct MENUITEM draw_pixel = {

      MI_ACTION, "Pixel", "Enter to draw the animated Pixels", (void*) func_pixel

};

 

struct MENUITEM draw_triangle = {

      MI_ACTION, "Triangle", "Enter to draw the animated Triangles", (void*) func_triangle

};

 

struct MENUITEM draw_rectangle = {

      MI_ACTION, "Rectangle", "Enter to draw the animated Rectangles", (void*) func_rectangle

};

 

struct MENUITEM *draw_list[] = {

      &draw_pixel, &draw_line, &draw_circle, &draw_triangle, &draw_rectangle

};

 

extern struct MENU menu_root;

 

struct MENU menu_draw = {

      1, "draw menu", 2, 21, 85, 90, sizeof(draw_list) / sizeof(draw_list[0]), draw_list, 0, &menu_root

};

 

struct MENUITEM root_draw = {

      MI_PARENT, "Draw", "Enter to list the drawing options menu", (void*) &menu_draw

};

 

struct MENUITEM root_exit = {

      MI_ACTION, "Exit", "Enter to exit from this application", (void*) func_exit

};

 

struct MENUITEM *root_list[] = {

      &root_draw, &root_exit

};

 

struct MENU menu_root = {

      0, "Main Menu", 2, 2, 198, 18, sizeof(root_list) / sizeof(root_list[0]), root_list, 0, NULL

};

 

struct WINDOW {

      int title;

      char *name;

      int left;

      int top;

      int right;

      int bottom;

      int color;

};

 

struct WINDOW title_window = {

      1, "Menu Design - softwareandfinance.com", 0, 0, 639, 50, BLUE

};

 

struct WINDOW help_window = {

      0, "Help", 0, 370, 639, 425, GREEN

};

 

struct WINDOW message_window = {

      0, "Message", 0, 430, 639, 479, LIGHTGRAY

};

 

struct WINDOW menu_window = {

      0, "Menu Window", 0, 55, 200, 365, DARKGRAY

};

 

struct WINDOW menu_window2 = {

      0, "Menu Window", 0, 70, 200, 365, DARKGRAY

};

 

struct WINDOW user_window = {

      0, "User Window", 205, 55, 639, 365, LIGHTBLUE

};

 

void displaywindow(struct WINDOW *wp)

{

      int w, h;

      setcolor(WHITE);

      setfillstyle(SOLID_FILL, wp->color);

      bar(wp->left, wp->top, wp->right, wp->bottom);

      rectangle(wp->left, wp->top, wp->right, wp->bottom);

      if(wp->title == 1)

      {

            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

            w = wp->left + wp->right - textwidth(wp->name);

            h = wp->top + wp->bottom - textheight(wp->name);

            outtextxy(w / 2, h / 2, wp->name);

      }

      else

      {

            settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

            rectangle(wp->left, wp->top, wp->right, wp->top + 15);

            w = wp->left + wp->right - textwidth(wp->name);

            outtextxy(w / 2, wp->top + 2, wp->name);

      }

 

}

 

void displaymenu(struct MENU *mp)

{

// menu_window = 0, 55, 200, 365,

      int i = 0;

      int x, y;

 

      struct WINDOW *wp = &menu_window2;

      setfillstyle(SOLID_FILL, wp->color);

      setcolor(WHITE);

      bar(wp->left + mp->left, wp->top + mp->top, wp->left + mp->right, wp->top + mp->bottom);

      rectangle(wp->left + mp->left, wp->top + mp->top, wp->left + mp->right, wp->top + mp->bottom);

 

      if(mp->vertical == 1)

      {

            x = wp->left + mp->left + 5;

            y = wp->top + mp->top + 5;

 

            for(i = 0; i < mp->count; i++)

            {

                  if(i == mp->curritem)

                  {

                        setfillstyle(SOLID_FILL, WHITE);

                        bar(x - 2, y - 1, x + textwidth(mp->menuitemlist[i]->name), y + textheight(mp->menuitemlist[i]->name));

                        setcolor(wp->color);

                        outtextxy(x, y, mp->menuitemlist[i]->name);

                        y += textheight(mp->menuitemlist[i]->name);

                        y += 4;

                        setfillstyle(SOLID_FILL, wp->color);

                        setcolor(WHITE);

                        displaywindow(&help_window);

                        outtextxy(help_window.left + 10, help_window.top + 30, mp->menuitemlist[i]->helpstring);

                  }

                  else

                  {

                        outtextxy(x, y, mp->menuitemlist[i]->name);

                        y += textheight(mp->menuitemlist[i]->name);

                        y += 4;

                  }

            }

      }

      else

      {

            x = wp->left + mp->left + 5;

            y = wp->top + mp->top + 5;

 

            for(i = 0; i < mp->count; i++)

            {

                  if(i == mp->curritem)

                  {

                        setfillstyle(SOLID_FILL, WHITE);

                        bar(x - 2, y - 1, x + textwidth(mp->menuitemlist[i]->name), y + textheight(mp->menuitemlist[i]->name));

                        setcolor(wp->color);

                        outtextxy(x, y, mp->menuitemlist[i]->name);

                        x += textwidth(mp->menuitemlist[i]->name);

                        x += 15;

                        setfillstyle(SOLID_FILL, wp->color);

                        setcolor(WHITE);

                        displaywindow(&help_window);

                        outtextxy(help_window.left + 10, help_window.top + 30, mp->menuitemlist[i]->helpstring);

                  }

                  else

                  {

                        outtextxy(x, y, mp->menuitemlist[i]->name);

                        x += textwidth(mp->menuitemlist[i]->name);

                        x += 15;

                  }

            }

      }

 

 

}

 

#define LTARROW 0x4B

#define RTARROW 0x4D

#define UPARROW 0x48

#define DNARROW 0x50

 

#define CR 0x0d

#define ESC 0x1b

 

#define ALT_X 0x2d

 

 

struct MENU* handlekey(struct MENU *mp, int key)

{

 

      void (*fp) (void) = NULL;

      if( (key & 0x00FF) > 0)

            key = key & 0x00FF;

      else

            key = (key & 0xFF00) >> 8;

 

      displaywindow(&message_window);

 

      switch(key)

      {

      case UPARROW:

            {

                  if(mp->vertical == 1)

                  {

                        mp->curritem--;

                        if(mp->curritem < 0)

                              mp->curritem = 0;

                  }

                  break;

            }

      case DNARROW:

            {

                  if(mp->vertical == 1)

                  {

                        mp->curritem++;

                        if(mp->curritem > mp->count - 1)

                              mp->curritem = mp->count - 1;

                  }

                  break;

            }

      case LTARROW:

            {

                  if(mp->vertical == 0)

                  {

                        mp->curritem--;

                        if(mp->curritem < 0)

                              mp->curritem = 0;

                  }

                  break;

            }

 

      case RTARROW:

            {

                  if(mp->vertical == 0)

                  {

                        mp->curritem++;

                        if(mp->curritem > mp->count - 1)

                              mp->curritem = mp->count - 1;

                  }

                  break;

            }

      case CR:

            {

                  struct MENUITEM *itemp = mp->menuitemlist[mp->curritem];

                  if(itemp->type == MI_PARENT)

                  {

                        struct MENU *mp2 = (struct MENU*) itemp->p;

                        displaymenu(mp);

                        mp = mp2;

                  }

                  else if(itemp->type == MI_ACTION)

                  {

                         fp = (void (*) ()) itemp->p;

                         fp();

                  }

            }

            break;

      case ESC:

            {

                  if(mp->parent != NULL)

                  {

                        displaywindow(&menu_window);

                        mp = mp->parent;

                  }

            }

            break;

      case ALT_X:

            return NULL;

      }

 

      displaymenu(mp);

      return mp;

}

 

void func_exit()

{

      closegraph();

      exit(0);

}

 

void func_circle()

{

      struct WINDOW *wp = &user_window;

      int i = 0;

      int midx = (wp->left + wp->right) / 2;

      int midy = (wp->top + wp->bottom) / 2;

      int maxradius = ((wp->bottom - wp->top) / 2 - 15);

 

      displaywindow(wp);

 

      randomize();

      for(i = 0; i < maxradius; i += 3)

      {

            setcolor(rand() % 15);

            circle(midx, midy, i);

            delay(2);

      }

      displaywindow(&message_window);

      outtextxy(message_window.left + 10, message_window.top + 30, "Circles are drawn");

}

 

void func_line()

{

      struct WINDOW *wp = &user_window;

      int i = 0;

      int midx = (wp->left + wp->right) / 2;

      int midy = (wp->top + wp->bottom) / 2;

      int maxradius = ((wp->bottom - wp->top) / 2 - 18);

 

      displaywindow(wp);

 

      randomize();

      for(i = 0; i < 360; i += 3)

      {

            setcolor(rand() % 15);

            line(midx,

                  midy,

                  midx + maxradius * cos(i * 3.1417 / 180),

                  midy - maxradius * sin(i * 3.1417 / 180) );

            delay(2);

      }

      displaywindow(&message_window);

      outtextxy(message_window.left + 10, message_window.top + 30, "Lines are drawn");

}

 

void func_pixel()

{

      struct WINDOW *wp = &user_window;

      int i = 0;

      int midx = (wp->left + wp->right) / 2;

      int midy = (wp->top + wp->bottom) / 2;

      int maxradius = ((wp->bottom - wp->top) / 2 - 18);

 

      displaywindow(wp);

 

      randomize();

      for(i = 0; i < 2000; i ++)

      {

            putpixel(midx + rand() % maxradius, midy + rand() % maxradius, rand() % 15);

            putpixel(midx - rand() % maxradius, midy - rand() % maxradius, rand() % 15);

            putpixel(midx + rand() % maxradius, midy - rand() % maxradius, rand() % 15);

            putpixel(midx - rand() % maxradius, midy + rand() % maxradius, rand() % 15);

      }

      displaywindow(&message_window);

      outtextxy(message_window.left + 10, message_window.top + 30, "Pixels are drawn");

 

}

 

void func_triangle()

{

      struct WINDOW *wp = &user_window;

      int i = 0;

      int x1, y1, x2, y2, x3, y3;

      int midx = (wp->left + wp->right) / 2;

      int midy = (wp->top + wp->bottom) / 2;

      int maxradius = ((wp->bottom - wp->top) / 2 - 18);

 

      displaywindow(wp);

 

      randomize();

      for(i = 0; i < 360; i += 3)

      {

            setcolor(rand() % 15);

            x1 = midx + maxradius * cos( (i+90) * 3.1417 / 180 );

            y1 = midy - maxradius * sin( (i+90) * 3.1417 / 180 );

 

            x2 = midx + maxradius * cos( (i+180) * 3.1417 / 180 );

            y2 = midy - maxradius * sin( (i+180) * 3.1417 / 180 );

 

            x3 = midx + maxradius * cos( (i+270) * 3.1417 / 180 );

            y3 = midy - maxradius * sin( (i+270) * 3.1417 / 180 );

 

            line(x1, y1, x2, y2);

            line(x2, y2, x3, y3);

            line(x3, y3, x1, y1);

            delay(2);

      }

      displaywindow(&message_window);

      outtextxy(message_window.left + 10, message_window.top + 30, "Triangles are drawn");

 

}

 

void func_rectangle()

{

      struct WINDOW *wp = &user_window;

      int i = 0;

      int left, top, right, bottom;

      int midx = (wp->left + wp->right) / 2;

      int midy = (wp->top + wp->bottom) / 2;

      int maxradius = ((wp->bottom - wp->top) / 2 - 18);

 

      displaywindow(wp);

 

      randomize();

      for(i = 0; i < 360; i += 3)

      {

            setcolor(rand() % 15);

            left = midx + maxradius * cos( (i + 90) * 3.1417 / 180);

            top =  midy - maxradius * sin( (i + 90) * 3.1417 / 180);

 

            right = midx + maxradius * cos( (i + 270) * 3.1417 / 180);

            bottom =  midy - maxradius * sin( (i + 270) * 3.1417 / 180);

 

            rectangle(left, top, right, bottom);

            delay(2);

      }

      displaywindow(&message_window);

      outtextxy(message_window.left + 10, message_window.top + 30, "Rectangles are drawn");

}

 

void main()

{

      int i, grd, grm;

      struct MENU *mp = &menu_root;

      detectgraph(&grd,&grm);

      initgraph(&grd, &grm, "");

 

      displaywindow(&title_window);

      displaywindow(&help_window);

      displaywindow(&message_window);

      displaywindow(&menu_window);

      displaywindow(&user_window);

 

      displaymenu(mp);

 

      while(!kbhit())

      {

      int key = bioskey(0);

      mp = handlekey(mp, key);

      if(mp == NULL)

            break;

      }

      func_exit();