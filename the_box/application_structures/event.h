/*
	
	
	Functionality :
	- Error Object (used in: standard games, social tool)
	- 
	- 
	- Files (project/errors.txt)
	
	Inherit :
	
	Notes :
*/

char event_name;
char event_type[]; 
char event_time;
char event_start;
char event_end;
char event_price;
char event_duration;
char event_place;
char event_discription;
char event_foto;
char event_video;
char event_adherence;
char event_contacts;

char event_users; //players, 



char order[] = {"name", "type", "time", "start"};

event_data_local(int mx, int my);

event_data_local(int mx, int my){
	
}

/*
 *  Event handling:
 */

void	app_main_loop(App *app);
int 	app_wait_event(App *app);
int 	app_process_events(App *app);
int 	app_do_event(App *app);
int 	app_peek_event(App *app);

int 	app_get_mouse_event(App *app, int *buttons, Point *p);

void	app_pass_event(Control *c);

void	app_draw_all(App *app);

/*
 *  Event handlers:
 */

  typedef void (*WindowFunc)      (Window *w);
  typedef void (*WindowMouseFunc) (Window *w, int buttons, Point xy);
  typedef void (*WindowKeyFunc)   (Window *w, unsigned long key);
  typedef void (*WindowDrawFunc)  (Window *w, Graphics *g);

  typedef void (*ControlFunc)     (Control *c);
  typedef void (*MouseFunc)       (Control *c, int buttons, Point xy);
  typedef void (*KeyFunc)         (Control *c, unsigned long key);
  typedef void (*DrawFunc)        (Control *c, Graphics *g);

  typedef void (*MenuAction)      (MenuItem *mi);

  typedef void (*TimerAction)     (Timer *t);

  typedef char * (*TipFunc)       (Control *c, Graphics *wg, Rect *r); //!!