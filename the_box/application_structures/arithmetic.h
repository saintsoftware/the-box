
  typedef struct Point       Point;
  typedef struct Rect        Rect;

  struct Point {
	int   x;
	int   y;
  };

  struct Rect {
	int   x;        /* left-most pixel inside rectangle */
	int   y;        /* top-most pixel inside rectangle */
	int   width;    /* in pixels */
	int   height;   /* in pixels */
  };

/*
 *  Drawing primitives (implemented as macros for speed):
 */

#define app_copy_rect(g,dp,src,sr) ((g)->copy_rect((g),(dp),(src),(sr)))
#define app_fill_rect(g,r)         ((g)->fill_rect((g),(r)))
#define app_draw_utf8(g,p,utf8,nb) ((g)->draw_utf8((g),(p),(utf8),(nb)))
#define app_draw_line(g,p1,p2)     ((g)->draw_line((g),(p1),(p2)))

/*
 *  Points:
 */

#define pt(x,y)       app_new_point((x),(y))

Point app_new_point(int x, int y);
int   app_points_equal(Point p1, Point p2);
int   app_point_in_rect(Point p, Rect r);


/*
 *  Rectangles:
 */

#define rect(x,y,w,h) app_new_rect((x),(y),(w),(h))

Rect app_new_rect(int x, int y, int width, int height);
Rect app_center_rect(Rect r1, Rect r2);
Rect app_inset_rect(Rect r, int width);
int  app_rect_in_rect(Rect r1, Rect r2);
int  app_rect_intersects_rect(Rect r1, Rect r2);
int  app_rects_equal(Rect r1, Rect r2);
Rect app_clip_rect(Rect r1, Rect r2);
Rect app_rect_abs(Rect r);

int  app_clip_line_to_rect(Rect r, Point *p1, Point *p2);

/*
 *  Regions:
 */

Region * app_new_region(void);
void     app_del_region(Region *rgn);
Region * app_new_rect_region(Rect r);
Region * app_copy_region(Region *rgn);
void     app_move_region(Region *rgn, int dx, int dy);
int      app_union_region(Region *rgn1, Region *rgn2, Region *dest);
int      app_union_region_with_rect(Region *rgn, Rect r, Region *dest);
int      app_intersect_region(Region *rgn1, Region *rgn2, Region *dest);
int      app_intersect_region_with_rect(Region *rgn, Rect r, Region *dest);
int      app_subtract_region(Region *rgn1, Region *rgn2, Region *dest);
int      app_xor_region(Region *rgn1, Region *rgn2, Region *dest);
int      app_region_is_empty(Region *rgn);
int      app_regions_equal(Region *rgn1, Region *rgn2);
int      app_point_in_region(Point p, Region *rgn);
int      app_rect_intersects_region(Rect r, Region *rgn);
int      app_rect_in_region(Rect r, Region *rgn);



static Point          current_point     = {0,0};

/*
 *  Point and rectangle arithmetic.
 */

Point newpoint(int x, int y)
{
	Point p;

	p.x = x;
	p.y = y;
	return p;
}

Rect newrect(int x, int y, int width, int height)
{
	Rect r;

	r.x = x;
	r.y = y;
	r.width = width;
	r.height = height;
	return r;
}

Rect rpt(Point min, Point max)
{
	Rect r;

	r.x = min.x;
	r.y  = min.y;
	r.width = max.x - min.x;
	r.height = max.y - min.y;
	return r;
}

Point topleft(Rect r)
{
	Point p;

	p.x = r.x;
	p.y = r.y;

	return p;
}

Point topright(Rect r)
{
	Point p;

	p.x = r.x + r.width - 1;
	p.y = r.y;

	return p;
}

Point bottomright(Rect r)
{
	Point p;

	p.x = r.x + r.width - 1;
	p.y = r.y + r.height - 1;

	return p;
}

Point bottomleft(Rect r)
{
	Point p;

	p.x = r.x;
	p.y = r.y + r.height - 1;

	return p;
}

Point addpt(Point p1, Point p2)
{
	p1.x += p2.x;
	p1.y += p2.y;
	return p1;
}

Point subpt(Point p1, Point p2)
{
	p1.x -= p2.x;
	p1.y -= p2.y;
	return p1;
}

Point midpt(Point p1, Point p2)
{
	Point p;

	p.x = (p1.x + p2.x)/2;
	p.y = (p1.y + p2.y)/2;
	return p;
}

Point mulpt(Point p, int i)
{
	p.x *= i;
	p.y *= i;
	return p;
}

Point divpt(Point p, int i)
{
	p.x /= i;
	p.y /= i;
	return p;
}

Rect rmove(Rect r, Point p)
{
	r.x = p.x;
	r.y  = p.y;
	return r;
}

Rect raddpt(Rect r, Point p)
{
	r.x += p.x;
	r.y += p.y;
	return r;
}

Rect rsubpt(Rect r, Point p)
{
	r.x -= p.x;
	r.y  -= p.y;
	return r;
}

Rect rmul(Rect r, int i)
{
	if (i != 1) {
		r.x *= i;
		r.y  *= i;
		r.width *= i;
		r.height *= i;
	}
	return r;
}

Rect rdiv(Rect r, int i)
{
	if (i != 1) {
		r.x /= i;
		r.y  /= i;
		r.width /= i;
		r.height /= i;
	}
	return r;
}

Rect growr(Rect r, int w, int h)
{
	r.x -= w;
	r.y  -= h;
	r.width += 2*w;
	r.height += 2*h;
	return r;
}

Rect insetr(Rect r, int i)
{
	r.x += i;
	r.y  += i;
	r.width -= 2*i;
	r.height -= 2*i;
	return r;
}

Rect rcenter(Rect r1, Rect r2) /* center r1 on r2 */
{
	Rect r;

	r.x = r2.x + (r2.width-r1.width)/2;
	r.y  = r2.y + (r2.height-r1.height)/2;
	r.width = r1.width;
	r.height = r1.height;

	return r;
}

int ptinr(Point p, Rect r)
{
	if ((p.x>=r.x) && (p.x<r.x+r.width) &&
			(p.y>=r.y) && (p.y<r.y+r.height))
		return 1;
	else
		return 0;
}

int rinr(Rect r1, Rect r2)
{
	if ((r1.x>=r2.x) && (r1.y>=r2.y) &&
		(r1.x+r1.width<=r2.x+r2.width) &&
		(r1.y+r1.height<=r2.y+r2.height))
		return 1;
	else
		return 0;
}

int rxr(Rect r1, Rect r2)
{
	if ((r1.x<r2.x+r2.width) &&
		(r2.x<r1.x+r1.width) &&
		(r1.y<r2.y+r2.height) &&
		(r2.y<r1.y+r1.height))
		return 1;
	else
		return 0;
}

int equalpt(Point p1, Point p2)
{
	if ((p1.x==p2.x) && (p1.y==p2.y))
		return 1;
	else
		return 0;
}

int equalr(Rect r1, Rect r2)
{
	if ((r1.x==r2.x) && (r1.width==r2.width) &&
		(r1.y==r2.y) && (r1.height==r2.height))
		return 1;
	else
		return 0;
}

Rect clipr(Rect r1, Rect r2)
{
	if (rxr(r1,r2) == 0)
		return rect(0,0,0,0); /* they don't overlap */

	if (r1.x < r2.x) {
		r1.width -= (r2.x - r1.x);
		r1.x = r2.x;
	}
	if (r1.y < r2.y) {
		r1.height -= (r2.y - r1.y);
		r1.y = r2.y;
	}
	if (r1.x + r1.width > r2.x + r2.width)
		r1.width = r2.x + r2.width - r1.x;
	if (r1.y + r1.height > r2.y + r2.height)
		r1.height = r2.y + r2.height - r1.y;
	return r1; /* they do overlap */
}

Rect rcanon(Rect r)
{
	if (r.width < 0) {
		r.x += r.width;
		r.width = -r.width;
	}
	if (r.height < 0) {
		r.y += r.height;
		r.height = -r.height;
	}
	return r;
}