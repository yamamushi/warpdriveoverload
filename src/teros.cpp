/*
 
 A modified version of TEROS Engine 0.0.2.7 by Kyle L. Miskell - KyleMiskell@gmail.com
 
 Original TEROS project can be found at:
 
 https://github.com/SighoftheSecond/TEROS-ENGINE
 
 - Yamamushi
 
 */

#include "teros.h"
#include "terospolygon.h"

TerosWindow::TerosWindow(_SharedPtr<ncursesWindow> parent, int posx, int posy) : Widget(parent, posx, posy)
{
	width = parent->getX();
	height = parent->getY();

	//m_xpos = 0;
	m_ypos = height - 1;

	cursorchar = '>';
	fill = ' ';
	cursorid = '&';
	atxtid = '%';
	transparency = '`';
}

void TerosWindow::loadfromfile (string fname)
{
	width = 0;
	height = 0;

	ifstream input;

	string line;

	input.open (fname.c_str());

	while (!input.eof())
	{
		getline (input, line);

		if (line.size() > width)
		{
			width = line.size ();
		}
	}

	input.close ();

	input.open (fname.c_str());

	content.resize (0);
	cursors.resize (0);
	activetext.resize (0);

	while (!input.eof())
	{
		getline (input, line);

		for (int i = 0; i < width; i++)
		{
			content.resize (content.size () + 1);

			if (i < line.size ())
			{
				content [i + height*width] = line [i];
			}
			else
			{
				content [i + height*width] = fill;
			}

			if (content [i + height*width] == cursorid)
			{
				cursors.resize (cursors.size () + 1);
				cursors [cursors.size () - 1] = false;
			}
			else if (content [i + height*width] == atxtid)
			{
				activetext.resize (activetext.size () + 1);

				activetext [activetext.size () - 1] = "";
			}
		}

		height++;
	}

	input.close ();
}

void TerosWindow::loadfromvector (vector <char> input, int columns)
{
	if (input.size ()%columns)
	{
		return;
	}

	content.resize (input.size ());
	cursors.resize (0);
	activetext.resize (0);

	width = columns;
	height = input.size ()/columns;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			content [(height - i - 1)*width + j] = input [(i*width) + j];
		}
	}

	cursorid = '\0';
	atxtid = '\0';
	transparency = '\0';
}

void TerosWindow::setatxtid (char atid)
{
	atxtid = atid;
}

void TerosWindow::setcursorid (char cid)
{
	cursorid = cid;
}

void TerosWindow::modcontent (char c, int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		content [(height - y - 1)*width + x] = c;
	}
}

void TerosWindow::tlrepos (int x, int y)
{
	m_xpos = x;
	m_ypos = y;
}

void TerosWindow::setcursor (int index, bool state)
{
	if (index < cursors.size ())
	{
		cursors [index] = state;
	}
}

void TerosWindow::setactivetext (int index, string s)
{
	if (index < activetext.size ())
	{
		activetext [index] = s;
	}
}

void TerosWindow::setfill (char fillchar)
{
	for (int i = 0; i < content.size (); i++)
	{
		if (content [i] == fill)
		{
			content [i] = fillchar;
		}
	}

	fill = fillchar;
}

void TerosWindow::setcursorchar (char cursor)
{
	cursorchar = cursor;
}

bool TerosWindow::putcursor (int index)
{
	if (index < cursors.size ())
	{
		return cursors [index];
	}

	return false;
}

char TerosWindow::putatxtid ()
{
	return atxtid;
}

char TerosWindow::putcursorid ()
{
	return cursorid;
}

char TerosWindow::putfill ()
{
	return fill;
}

char TerosWindow::putcursorchar ()
{
	return cursorchar;
}

char TerosWindow::puttranspid ()
{
	return transparency;
}

char TerosWindow::readcontent (int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		return content [(height - y - 1)*width + x];
	}

	return ' ';
}

int TerosWindow::putwidth ()
{
	return width;
}

int TerosWindow::putheight ()
{
	return height;
}

int TerosWindow::putxpos ()
{
	return m_xpos;
}

int TerosWindow::putypos ()
{
	return m_ypos;
}

int TerosWindow::cursorcount ()
{
	return cursors.size ();
}

int TerosWindow::activetextcount ()
{
	return activetext.size ();
}

string TerosWindow::putactivetext (int index)
{
	if (index < activetext.size ())
	{
		return activetext [index];
	}

	return NULL;
}

TerosScreen::TerosScreen ()
{
	clrscr ();
}

void TerosScreen::clrscr ()
{
	int x = 0;
	int y = SCRHEIGHT - 1;

	while (x < SCRWIDTH || y > 0)
	{
		display [x][y] = ' ';

		x++;

		if (x >= SCRWIDTH && y > 0)
		{
			x = 0;
			y--;
		}
	}
}

void TerosScreen::buildscr ()
{
	clrscr ();

	for (int i = 0; i < layers.size (); i++)
	{
		int x = 0;
		int y = SCRHEIGHT - 1;

		int acdetect = 0;
		int ccursor = 0;

		while (x < SCRWIDTH || y > 0)
		{
			if (x >= layers [i] -> putxpos () && x < layers [i] -> putxpos () + layers [i] -> putwidth () && y <= layers [i] -> putypos () && y > layers [i] -> putypos () - layers [i] -> putheight ())
			{
				if (layers [i] -> readcontent (x - layers [i] -> putxpos (), y - (layers [i] -> putypos () - layers [i] -> putheight () + 1)) != layers [i] -> putatxtid () && layers [i] -> readcontent (x - layers [i] -> putxpos (), y - (layers [i] -> putypos () - layers [i] -> putheight () + 1)) != layers [i] -> putcursorid () && layers [i] -> readcontent (x - layers [i] -> putxpos (), y - (layers [i] -> putypos () - layers [i] -> putheight () + 1)) != layers [i] -> puttranspid ())
				{
					display [x][y] = layers [i] -> readcontent (x - layers [i] -> putxpos (), y - (layers [i] -> putypos () - layers [i] -> putheight () + 1));
				}
				else if (layers [i] -> readcontent (x - layers [i] -> putxpos (), y - (layers [i] -> putypos () - layers [i] -> putheight () + 1)) == layers [i] -> putcursorid ())
				{
					if (layers [i] -> putcursor (ccursor))
					{
							display [x][y] = layers [i] -> putcursorchar ();
					}
					else if (layers [i] -> putfill () != layers [i] -> puttranspid ())
					{
						display [x][y] = layers [i] -> putfill ();
					}

					ccursor++;
				}
				else if (layers [i] -> readcontent (x - layers [i] -> putxpos (), y - (layers [i] -> putypos () - layers [i] -> putheight () + 1)) == layers [i] -> putatxtid ())
				{
					string activec = layers [i] -> putactivetext (acdetect);

					for (int ac = 0; ac < activec.size () && x + ac < layers [i] -> putxpos () + layers [i] -> putwidth () && x + ac < SCRWIDTH; ac++)
					{
						display [x + ac][y] = activec [ac];
	
						if (ac + 1 >= activec.size () || x + ac + 1 >= layers [i] -> putxpos () + layers [i] -> putwidth () || x + ac + 1 >= SCRWIDTH)
						{
							x += ac;
						}
					}

					acdetect++;
				}
			}

			x++;

			if (x >= SCRWIDTH && y > 0)
			{
				x = 0;
				y--;
			}
		}
	}
}

void TerosScreen::displayscr ()
{
	buildscr ();

	int x = 0;
	int y = SCRHEIGHT - 1;

	cout << "\n ";

	while (x < SCRWIDTH && y > 0)
	{
		cout << display [x][y];

		x++;

		if (x >= SCRWIDTH && y > 0)
		{
			cout << "\n ";

			x = 0;
			y--;
		}
	}
}

void TerosScreen::addlayer (TerosWindow * overlay)
{
	layers.resize (layers.size () + 1);

	layers [layers.size () - 1] = overlay;
}

void TerosScreen::dellayer (int index)
{
	if (index < layers.size ())
	{
		layers.erase (layers.begin () + index);
	}
}

void TerosScreen::swaplayer (int index1, int index2)
{
	if (index1 < layers.size () && index2 < layers.size ())
	{
		TerosWindow * temp = layers [index1];

		layers [index1] = layers [index2];
		layers [index2] = temp;
	}
}

void TerosScreen::modlayer (int index, TerosWindow * replacement)
{
	if (index < layers.size ())
	{
		layers [index] = replacement;
	}
}

int TerosScreen::layercount ()
{
	return layers.size ();
}

TerosWindow * TerosScreen::putlayer (int index)
{
	if (index < layers.size () && index >= 0)
	{
		return layers [index];
	}

	return NULL;
}





int roundnum (double toround)
{
	if (toround - floor(toround) >= 0.5)
	{
		return ceil(toround);
	}
    
	return floor(toround);
}

double dist (double a, double b, double c, double x, double y, double z)
{
	return sqrt(pow (abs(a - x), 2) + pow (abs(b - y), 2) + pow (abs(c - z), 2));
}

double findang (double q, double r)
{
	double angle = 0;
    
	if (q != 0 && r != 0)
	{
		angle = atan(abs(r)/abs(q));
	}
    
	if (q < 0 && r > 0)
	{
		angle = PI - angle;
	}
	else if (q < 0 && r < 0)
	{
		angle = PI + angle;
	}
	else if (q > 0 && r < 0)
	{
		angle = 2.0*PI - angle;
	}
    
	if (abs(r) == 0 && q > 0)
	{
		angle = 0;
	}
	else if (abs(r) == 0 && q < 0)
	{
		angle = PI;
	}
	else if (abs(q) == 0 && r > 0)
	{
		angle = PI*0.5;
	}
	else if (abs(q) == 0 && r < 0)
	{
		angle = PI*1.5;
	}
	else if (abs(q) == 0 && abs(r) == 0)
	{
		angle = -1;
	}
    
	return angle;
}

string doubletostring (double num)
{
	string rstring = "";
	string rstring2 = "";
    
	num *= pow (10, 6);
    
	int lcounter = 0;
    
	bool neg = false;
	bool tripdec = false;
    
	if (num == 0)
	{
		return "0.000000";
	}
	else if (num < 0)
	{
		neg = true;
		num *= -1;
	}
    
	while (int(num) > 0)
	{
		if (lcounter == 6)
		{
			rstring += ".";
			tripdec = true;
		}
        
		rstring += char(int(num) % 10 + 48);
		num = int(num)/10;
        
		lcounter++;
	}
    
	if (!tripdec)
	{
		rstring += ".0";
	}
    
	if (neg)
	{
		rstring += "-";
	}
    
	lcounter = 0;
    
	rstring2.resize (rstring.size ());
    
	for (int i = rstring.size () - 1; i >= 0; i--)
	{
		rstring2 [lcounter] = rstring [i];
        
		lcounter++;
	}
    
	return rstring2;
}
