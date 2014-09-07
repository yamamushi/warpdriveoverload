/*
 
 A modified version of TEROS Engine 0.0.2.7 by Kyle L. Miskell - KyleMiskell@gmail.com
 
 Original TEROS project can be found at:
 
 https://github.com/SighoftheSecond/TEROS-ENGINE
 
 - Yamamushi
 
 */

#include "teros.h"
#include "terospolygon.h"



TerosWindow::TerosWindow(_SharedPtr<TerosScreen> owner, int width, int height, int posx, int posy)
{
    m_screen = owner;
	m_width = width;
	m_height = height;
    m_xpos = posx;
    m_ypos = posy;
    
	m_cursorchar = '>';
	m_fill = ' ';
	m_cursorid = '&';
	m_atxtid = '%';
	m_transparency = '`';
}





void TerosWindow::loadfromfile(std::string target)
{
    m_screen->drawAt(5, 5, "loading file: " + target);
    
	//m_width = 0;
	//m_height = m_screen->getheight();
    //m_width = 0;
    m_height = 0;
    
    std::ifstream input;
    
    std::string line;
    
	//input.open (target.c_str());
    
	m_content.resize (0);
	m_cursors.resize (0);
	m_activetext.resize (0);
    
    
    char ch;
    fstream fin(target.c_str(), fstream::in);
    int x = 0;
    int y = 0;
    while(fin >> noskipws >> ch){
        
        if(ch == '\n' || ch == '\r'){
            y++;
            x = 0;
        }
        else{
            std::string output(&ch);
            //m_screen->drawAt(x+m_xpos, y, output);
            m_display.push_back(_SharedPtr<GraphChartPoint>(new GraphChartPoint(x+m_xpos, y, output)));
            x++;
        }
    }
    //m_display.push_back(_SharedPtr<GraphChartPoint>(new GraphChartPoint(i, m_height, COLOR_PAIR(1), symbol)));
    
	input.close ();
}




void TerosWindow::loadfromvector (vector<TerosView> input, int column)
{
    
    //    init_pair(12, COLOR_BLUE, COLOR_BLACK); // A default Background Color
	if (input.size()%column)
	{
		return;
	}
    
    m_display.clear();
	m_content.resize (input.size ());
	m_cursors.resize (0);
	m_activetext.resize (0);
    
    int l_width = column;
    int l_height = (int)input.size()/column;
    
    
	for (int i = 0; i < l_height; i++)
	{
		for (int j = 0; j < l_width; j++)
        {
            char test;
            test = input [(i*l_width) + j].c;
            std::string output(&test);
            
            if(m_xpos+j < m_screen->getwidth() && m_ypos+i < m_screen->getheight() ){
                if(input [(i*l_width) + j].c == ' ' ){
                    m_display.push_back(_SharedPtr<GraphChartPoint>(new GraphChartPoint(j+m_xpos, i+m_ypos, " ", input[(i*l_width) + j].fg, input[(i*l_width) + j].bg, input[(i*l_width) + j].attr)));
                }
                else{
                    if(input [(i*l_width) + j].c == '@'){
                        m_display.push_back(_SharedPtr<GraphChartPoint>(new GraphChartPoint(j+m_xpos, i+m_ypos, output, input [(i*l_width) + j].fg, input [(i*l_width) + j].bg, input [(i*l_width) + j].attr)));
                    }
                    else if(input [(i*l_width) + j].c == 'F'){
                        m_display.push_back(_SharedPtr<GraphChartPoint>(new GraphChartPoint(j+m_xpos, i+m_ypos, output, input [(i*l_width) + j].fg, input [(i*l_width) + j].bg, input [(i*l_width) + j].attr)));
                    }
                    else{
                        m_display.push_back(_SharedPtr<GraphChartPoint>(new GraphChartPoint(j+m_xpos, i+m_ypos, output, input [(i*l_width) + j].fg, input [(i*l_width) + j].bg, input [(i*l_width) + j].attr)));
                    }
                }
            }
            
		}
	}
    
	m_cursorid = '\0';
	m_atxtid = '\0';
	m_transparency = '\0';
}









void TerosWindow::loadfromvector (vector<char> input, int column)
{
    
	if (input.size()%column)
	{
		return;
	}
    
    m_display.clear();
	m_content.resize (input.size ());
	m_cursors.resize (0);
	m_activetext.resize (0);
    
    int l_width = column;
    int l_height = (int)input.size()/column;
    
    
	for (int i = 0; i < l_height; i++)
	{
		for (int j = 0; j < l_width; j++)
		{
            char test;
            test = input [(i*l_width) + j];
            std::string output(&test);
            
            if(m_xpos+j < m_screen->getwidth() && m_ypos+i < m_screen->getheight() ){
                if(input [(i*l_width) + j] == ' '){
                    m_display.push_back(_SharedPtr<GraphChartPoint>(new GraphChartPoint(j+m_xpos, i+m_ypos, " ")));
                }
                else{
                    if(input [(i*l_width) + j] == '@'){
                        m_display.push_back(_SharedPtr<GraphChartPoint>(new GraphChartPoint(j+m_xpos, i+m_ypos, output)));
                    }
                    else if(input [(i*l_width) + j] == 'F'){
                        m_display.push_back(_SharedPtr<GraphChartPoint>(new GraphChartPoint(j+m_xpos, i+m_ypos, output)));
                    }
                    else{
                        m_display.push_back(_SharedPtr<GraphChartPoint>(new GraphChartPoint(j+m_xpos, i+m_ypos, output)));
                    }
                }
            }
            
		}
	}
    
	m_cursorid = '\0';
	m_atxtid = '\0';
	m_transparency = '\0';
}

void TerosWindow::setatxtid (char atid)
{
	m_atxtid = atid;
}

void TerosWindow::setcursorid (char cid)
{
	m_cursorid = cid;
}

void TerosWindow::modcontent (char c, int x, int y)
{
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
	{
		m_content [(m_height - y - 1)*m_width + x] = c;
	}
}

void TerosWindow::tlrepos (int x, int y)
{
	m_xpos = x;
	m_ypos = y;
}

void TerosWindow::setcursor (int index, bool state)
{
	if (index < m_cursors.size ())
	{
		m_cursors [index] = state;
	}
}

void TerosWindow::setactivetext (int index, string s)
{
	if (index < m_activetext.size ())
	{
		m_activetext [index] = s;
	}
}

void TerosWindow::setfill (char fillchar)
{
	for (int i = 0; i < m_content.size (); i++)
	{
		if (m_content [i] == m_fill)
		{
			m_content [i] = fillchar;
		}
	}
    
	m_fill = fillchar;
}

void TerosWindow::setcursorchar (char cursor)
{
	m_cursorchar = cursor;
}

bool TerosWindow::putcursor (int index)
{
	if (index < m_cursors.size ())
	{
		return m_cursors [index];
	}
    
	return false;
}

char TerosWindow::putatxtid ()
{
	return m_atxtid;
}

char TerosWindow::putcursorid ()
{
	return m_cursorid;
}

char TerosWindow::putfill ()
{
	return m_fill;
}

char TerosWindow::putcursorchar ()
{
	return m_cursorchar;
}

char TerosWindow::puttranspid ()
{
	return m_transparency;
}

std::string TerosWindow::readcontent (int x, int y)
{
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
	{
		//return m_content [(m_height - y - 1)*m_width + x];
	}
    
	return " ";
}

int TerosWindow::putwidth ()
{
	return m_width;
}

int TerosWindow::putheight ()
{
	return m_height;
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
	return (int)m_cursors.size ();
}

int TerosWindow::activetextcount ()
{
	return (int)m_activetext.size ();
}

string TerosWindow::putactivetext (int index)
{
	if (index < m_activetext.size ())
	{
		return m_activetext [index];
	}
    
	return NULL;
}




TerosScreen::TerosScreen (_SharedPtr<ncursesWindow> owner, int xpos, int ypos, _SharedPtr<GraphChart> renderObject) : Widget(owner)
{
	m_xpos = xpos;
    m_ypos = ypos;
    m_height = m_parent->getY();
    m_width = m_parent->getX();
    m_parent->clearScreen();
    m_graphChart = renderObject;
    
}

void TerosScreen::drawAt(int x, int y, std::string output, int fg, int bg, int attr){
    
    m_graphChart->addRawChartPoint(_SharedPtr<GraphChartPoint>(new GraphChartPoint(x, y, output, fg, bg, attr)));
    
}


void TerosScreen::drawAt(int x, int y, char c, int fg, int bg, int attr){
    
    std::string output(&c);
    
    m_graphChart->addRawChartPoint(_SharedPtr<GraphChartPoint>(new GraphChartPoint(x, y, output, fg, bg, attr)));
    
}

void TerosScreen::buildscr ()
{
    
    m_graphChart->clearAllChartPoints();
    m_graphChart->clearAllRawChartPoints();
    m_display.clear();
    
    for(int x = 0; x < layers.size(); x++){
        std::vector<_SharedPtr<GraphChartPoint> > points = layers.at(x)->getDisplay();
        for(int y = 0; y < points.size(); y++){
            m_display.push_back(points.at(y));
        }
    }
    for(int y = 0; y < m_display.size(); y++){
        m_graphChart->addRawChartPoint(m_display.at(y));
    }
    
}

void TerosScreen::displayscr ()
{
	buildscr ();
    
}

void TerosScreen::addlayer ( _SharedPtr<TerosWindow> overlay)
{
	layers.push_back(overlay);
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
        _SharedPtr<TerosWindow> temp = layers [index1];
        
		layers [index1] = layers [index2];
		layers [index2] = temp;
	}
}

void TerosScreen::modlayer (int index,  _SharedPtr<TerosWindow> replacement)
{
	if (index < layers.size ())
	{
		layers [index] = replacement;
	}
}

int TerosScreen::layercount ()
{
	return (int)layers.size ();
}

_SharedPtr<TerosWindow> TerosScreen::putlayer(int index)
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
    
	for (int i = (int)rstring.size () - 1; i >= 0; i--)
	{
		rstring2 [lcounter] = rstring [i];
        
		lcounter++;
	}
    
	return rstring2;
}
