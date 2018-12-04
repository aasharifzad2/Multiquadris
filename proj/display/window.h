#ifndef _window_h_
#define _window_h_


#ifdef GRAPHICS
#include <X11/Xlib.h>
#endif


#include <iostream>
#include <string>

class Xwindow
{
#ifdef GRAPHICS
    Display *d;
    Window w;
#endif
	int s;
#ifdef GRAPHICS
    GC gc;
#endif
	unsigned long colours[11];
	int width, height;

public:
	Xwindow(int width=500, int height=500)
#ifdef GRAPHICS
    ;
#else
    {}
#endif
    
	~Xwindow()
#ifdef GRAPHICS
    ;
#else
    {}
#endif

	enum { White = 0, Black,red, green, blue, cyan, yellow, magenta,
		orange, Brown, Darkgreen }; // Available colours.


	// Draws a string
	void drawString(int x, int y, std::string msg, int colour = Black)
#ifdef GRAPHICS
    ;
#else
    {}
#endif
	void drawBigString(int x, int y, std::string msg, int colour = Black)
#ifdef GRAPHICS
    ;
#else
    {}
#endif

	// if you use this function, make sure font exists on the undergrad environment
    void drawStringFont(int x, int y, std::string msg, std::string font, int colour = Black);

	// Draws a rectangle
	void fillRectangle(int x, int y, int width, int height, int colour=Black)
#ifdef GRAPHICS
    ;
#else
    {}
#endif

	// Draw a polygon with the first vertex at (x, y) with num vertices, side length side
	//     and rotated rotate radians. The second vertex is (x + side, y) rotated by
	//     rotate
	void fillPolygon(int x, int y, int num, int side, int rotate = 0, int colour = Black);

	// Draws a line from (x1, y1) to (x2, y2)
	void drawLine(int x1, int y1, int x2, int y2);

	// Draws an arc centered at (x, y) with height and width starting from angle1 to angle2
	//   angle1 being 0 is (x + width, y) and measured in degrees
	void drawArc(int x, int y, int width, int height, int angle1, int angle2);

	void fillArc(int x, int y, int width, int height, int angle1, int angle2, int colour);
	// Draws a circle centered at (x, y) with diameter d
	void fillCircle(int x, int y, int d, int colour = Black);

    void showAvailableFonts();

private:
#ifdef GRAPHICS
    void printMessage(int x, int y, const std::string& msg, int colour, XFontStruct& f);
#endif
};

#endif
