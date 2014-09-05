/*
 
 A modified version of TEROS Engine 0.0.2.7 by Kyle L. Miskell - KyleMiskell@gmail.com
 
 Original TEROS project can be found at:
 
 https://github.com/SighoftheSecond/TEROS-ENGINE
 
 - Yamamushi
 
 */

#include "teroscam.h"
#include "terosobject.h"
#include "terospolygon.h"
#include <iostream>

#include "logger.h"


TerosCam::TerosCam ()
{
	//setviewsize (SCRWIDTH, SCRHEIGHT);
    
	clearview ();
    
	m_camx = 0;
	m_camy = 0;
	m_camz = 0;
    m_zoomfactor = 10;
    m_position.set(m_camx, m_camy, m_camz, 1.0f);

	basisreset ();

}

void TerosCam::drawobjects ()
{
	clearview ();
    
	for (int i = 0; i < objects.size (); i++)
	{
		drawobject (*objects [i]);
	}
}

void TerosCam::drawobject (TerosObject obj)
{
	for (int i = 0; i < obj.sidenum (); i++)
	{
		TerosPolygon * temp = obj.putside (i);
        
		drawpolygon(*temp, obj);
	}
}

void TerosCam::drawpolygon (TerosPolygon cTerosPolygon, TerosObject obj)
{
	if (cTerosPolygon.puttexturemode ())
	{
		texturepolygon(cTerosPolygon, obj);
	}
	else
	{
		double p1 [3];
		double p2 [3];
		double p3 [3];
        
		if (!twodconvert (p1, p2, p3, obj, cTerosPolygon))
		{
			return;
		}
        
		drawline (p1, p2, cTerosPolygon.putfill());
		drawline (p2, p3, cTerosPolygon.putfill());
		drawline (p3, p1, cTerosPolygon.putfill());
	}
}

void TerosCam::drawline (double p1 [3], double p2 [3], char fill, int fg, int bg, int attr)
{
	double snorm = 0;
    
	bool swap = false;
    
	if (!(p2 [1] >= 0 && p2 [1] <= m_viewcolumns - 1 && p2 [2] >= 0 && p2 [2] <= view.size ()/m_viewcolumns - 1))
	{
		if (p1 [1] >= 0 && p1 [1] <= m_viewcolumns - 1 && p1 [2] >= 0 && p1 [2] <= view.size ()/m_viewcolumns - 1)
		{
			double buffer [3];
            
			buffer [0] = p2 [0];
			buffer [1] = p2 [1];
			buffer [2] = p2 [2];
            
			p2 [0] = p1 [0];
			p2 [1] = p1 [1];
			p2 [2] = p1 [2];
            
			p1 [0] = buffer [0];
			p1 [1] = buffer [1];
			p1 [2] = buffer [2];
            
			swap = true;
		}
		else
		{
			if (p1 [1] - p2 [1] != 0)
			{
				double ux = -1;
				double uy = -1;
				double dx = -1;
				double dy = -1;
				double lx = -1;
				double ly = -1;
				double rx = -1;
				double ry = -1;
                
				double up;
				double dp;
				double lp;
				double rp;
                
				double m = (p1 [2] - p2 [2])/(p1 [1] - p2 [1]);
				double b = p1 [2] - p1 [1]*m;
                
				if ((view.size ()/m_viewcolumns - 1 - b)/m >= 0 && (view.size ()/m_viewcolumns - 1 - b)/m <= m_viewcolumns - 1)
				{
					ux = (view.size ()/m_viewcolumns - 1 - b)/m;
					uy = view.size ()/m_viewcolumns - 1;
				}
                
				if ((0 - b)/m >= 0 && (0 - b)/m <= m_viewcolumns - 1)
				{
					dx = (0 - b)/m;
					dy = 0;
				}
                
				if (0*m + b >= 0 && 0*m + b <= view.size ()/m_viewcolumns - 1)
				{
					lx = 0;
					ly = 0*m + b;
				}
                
				if ((m_viewcolumns - 1)*m + b >= 0 && (m_viewcolumns - 1)*m + b <= view.size ()/m_viewcolumns - 1)
				{
					rx = m_viewcolumns - 1;
					ry = (m_viewcolumns - 1)*m + b;
				}
                
				up = dist (ux, uy, 0, p2 [1], p2 [2], 0);
				dp = dist (dx, dy, 0, p2 [1], p2 [2], 0);
				lp = dist (lx, ly, 0, p2 [1], p2 [2], 0);
				rp = dist (rx, ry, 0, p2 [1], p2 [2], 0);
                
				if (ux != -1 && lx != -1)
				{
					if (up < lp)
					{
						snorm = up;
					}
					else
					{
						snorm = lp;
					}
				}
				else if (ux != -1 && dx != -1)
				{
					if (up < dp)
					{
						snorm = up;
					}
					else
					{
						snorm = dp;
					}
				}
				else if (ux != -1 && rx != -1)
				{
					if (up < rp)
					{
						snorm = up;
					}
					else
					{
						snorm = rp;
					}
				}
				else if (rx != -1 && dx != -1)
				{
					if (rp < dp)
					{
						snorm = rp;
					}
					else
					{
						snorm = dp;
					}
				}
				else if (rx != -1 && lx != -1)
				{
					if (rp < lp)
					{
						snorm = rp;
					}
					else
					{
						snorm = lp;
					}
				}
				else if (dx != -1 && lx != -1)
				{
					if (dp < lp)
					{
						snorm = dp;
					}
					else
					{
						snorm = lp;
					}
				}
				else
				{
					return;
				}
			}
			else
			{
				if (p2 [1] >= 0 && p2 [1] <= m_viewcolumns - 1)
				{
					if (abs(p2 [2] - view.size ()/m_viewcolumns - 1) < abs(p2 [2] - 0))
					{
						snorm = abs(p2 [2] - view.size ()/m_viewcolumns - 1);
					}
					else
					{
						snorm = abs(p2 [2] - 0);
					}
				}
			}
		}
	}
    
	double dispx = p1 [1] - p2 [1];
	double dispy = p1 [2] - p2 [2];
    
	double normdispxy = dist (dispx, dispy, 0, 0, 0, 0);
    
	dispx /= normdispxy;
	dispy /= normdispxy;
    
	for (double norm = snorm; norm < normdispxy; norm += 0.5)
	{
		if (getelementindex (roundnum(dispx*norm + p2 [1]), roundnum(dispy*norm + p2 [2])) == -1)
		{
			if (swap)
			{
				double buffer [3];
                
				buffer [0] = p2 [0];
				buffer [1] = p2 [1];
				buffer [2] = p2 [2];
                
				p2 [0] = p1 [0];
				p2 [1] = p1 [1];
				p2 [2] = p1 [2];
                
				p1 [0] = buffer [0];
				p1 [1] = buffer [1];
				p1 [2] = buffer [2];
			}
            
			return;
		}
        
		if (((norm/normdispxy)*(p1 [0] - p2 [0])) + p2 [0] > 0 && (((norm/normdispxy)*(p1 [0] - p2 [0])) + p2 [0] < viewdepth [getelementindex (roundnum(dispx*norm + p2 [1]), roundnum(dispy*norm + p2 [2]))] || viewdepth [getelementindex (roundnum(dispx*norm + p2 [1]), roundnum(dispy*norm + p2 [2]))] == -1))
		{
			view [getelementindex (roundnum(dispx*norm + p2 [1]), roundnum(dispy*norm + p2 [2]))].c = fill;
            view [getelementindex (roundnum(dispx*norm + p2 [1]), roundnum(dispy*norm + p2 [2]))].fg = fg;
            view [getelementindex (roundnum(dispx*norm + p2 [1]), roundnum(dispy*norm + p2 [2]))].bg = bg;
            view [getelementindex (roundnum(dispx*norm + p2 [1]), roundnum(dispy*norm + p2 [2]))].attr = attr;
            
			viewdepth [getelementindex (roundnum(dispx*norm + p2 [1]), roundnum(dispy*norm + p2 [2]))] = norm/normdispxy*(p1 [0] - p2 [0]) + p2 [0];
		}
	}
}

void TerosCam::setcampos (double x, double y, double z)
{
	m_camx = x;
	m_camy = y;
	m_camz = z;
    
    m_position.set(m_camx, m_camy, m_camz, 1.0f);
    setViewMatrix();
}

void TerosCam::addobject (TerosObject * nextelement)
{
	//objects.resize (objects.size () + 1);
    
	objects.push_back(nextelement);
}

void TerosCam::delobject (int index)
{
	if (index < objects.size ())
	{
		objects.erase (objects.begin () + index);
	}
}

void TerosCam::modobject (int index, TerosObject * newelement)
{
	if (index < objects.size ())
	{
		objects [index] = newelement;
	}
}

void TerosCam::clearview ()
{
	for (int i = 0; i < view.size (); i++)
	{
		view [i].c = ' ';
		viewdepth [i] = -1.0;
	}
}

void TerosCam::rotatecam (char absnorm, double angle)
{
	double radius;
	double cangle;
    
	if (absnorm == 'z' || absnorm == 'Z')
	{
		radius = dist (cambasisx [0], cambasisx [1], 0, 0, 0, 0);
		cangle = findang (cambasisx [0], cambasisx [1]);
        
		cambasisx [0] = radius*cos(cangle + angle);
		cambasisx [1] = radius*sin(cangle + angle);
        
		radius = dist (cambasisy [0], cambasisy [1], 0, 0, 0, 0);
		cangle = findang (cambasisy [0], cambasisy [1]);
        
		cambasisy [0] = radius*cos(cangle + angle);
		cambasisy [1] = radius*sin(cangle + angle);
        
		radius = dist (cambasisz [0], cambasisz [1], 0, 0, 0, 0);
		cangle = findang (cambasisz [0], cambasisz [1]);
        
		cambasisz [0] = radius*cos(cangle + angle);
		cambasisz [1] = radius*sin(cangle + angle);
	}
	else if (absnorm == 'x' || absnorm == 'X')
	{
		radius = dist (0, cambasisx [1], cambasisx [2], 0, 0, 0);
		cangle = findang (cambasisx [1], cambasisx [2]);
        
		cambasisx [1] = radius*cos(cangle + angle);
		cambasisx [2] = radius*sin(cangle + angle);
        
		radius = dist (0, cambasisy [1], cambasisy [2], 0, 0, 0);
		cangle = findang (cambasisy [1], cambasisy [2]);
        
		cambasisy [1] = radius*cos(cangle + angle);
		cambasisy [2] = radius*sin(cangle + angle);
        
		radius = dist (0, cambasisz [1], cambasisz [2], 0, 0, 0);
		cangle = findang (cambasisz [1], cambasisz [2]);
        
		cambasisz [1] = radius*cos(cangle + angle);
		cambasisz [2] = radius*sin(cangle + angle);
        
	}
	else if (absnorm == 'y' || absnorm == 'Y')
	{
		radius = dist (cambasisx [0], 0, cambasisx [2], 0, 0, 0);
		cangle = findang (cambasisx [0], cambasisx [2]);
        
		cambasisx [0] = radius*cos(cangle + angle);
		cambasisx [2] = radius*sin(cangle + angle);
        
		radius = dist (cambasisy [0], 0, cambasisy [2], 0, 0, 0);
		cangle = findang (cambasisy [0], cambasisy [2]);
        
		cambasisy [0] = radius*cos(cangle + angle);
		cambasisy [2] = radius*sin(cangle + angle);
        
		radius = dist (cambasisz [0], 0, cambasisz [2], 0, 0, 0);
		cangle = findang (cambasisz [0], cambasisz [2]);
        
		cambasisz [0] = radius*cos(cangle + angle);
		cambasisz [2] = radius*sin(cangle + angle);
	}
    
    setViewMatrix();
    
}


// These Get Angle functions don't do what I thought they did
// Will rewrite.
vmml::vector<4, double> TerosCam::getAngleX(){
    
    vmml::vector<4, double> angle;
    angle = viewMatrix.get_row(0);
    return angle;
}

vmml::vector<4, double> TerosCam::getAngleY(){
    
    vmml::vector<4, double> angle;
    angle = viewMatrix.get_row(1);
    return angle;
    
}

vmml::vector<4, double> TerosCam::getAngleZ(){
    
    vmml::vector<4, double> angle;
    angle = viewMatrix.get_row(2);
    return angle;
    
}

void TerosCam::basisreset ()
{
	cambasisx [0] = 1;
	cambasisx [1] = 0;
	cambasisx [2] = 0;
    
	cambasisy [0] = 0;
	cambasisy [1] = 1;
	cambasisy [2] = 0;
    
	cambasisz [0] = 0;
	cambasisz [1] = 0;
	cambasisz [2] = 1;
    
    setViewMatrix();

}


void TerosCam::setViewMatrix(){
    
    viewMatrix.set_row(0,  vmml::vector<4, double>(cambasisx[0], cambasisx[1], cambasisx[2], 0.0));
    viewMatrix.set_row(1,  vmml::vector<4, double>(cambasisy[0], cambasisy[1], cambasisy[2], 0.0));
    viewMatrix.set_row(2,  vmml::vector<4, double>(cambasisz[0], cambasisz[1], cambasisz[2], 0.0));
    viewMatrix.set_row(3,  vmml::vector<4, double>(m_camx, m_camy, m_camz, 1.0));

}


void TerosCam::cpybasis (char axis, double store [3])
{
	if (axis == 'x' || axis == 'X')
	{
		store [0] = cambasisx [0];
		store [1] = cambasisx [1];
		store [2] = cambasisx [2];
	}
	else if (axis == 'y' || axis == 'Y')
	{
		store [0] = cambasisy [0];
		store [1] = cambasisy [1];
		store [2] = cambasisy [2];
	}
	else if (axis == 'z' || axis == 'Z')
	{
		store [0] = cambasisz [0];
		store [1] = cambasisz [1];
		store [2] = cambasisz [2];
	}
}

void TerosCam::setviewsize (int rows, int column)
{
	if (column > 0 && rows > 0)
	{
		m_viewcolumns = column;
		view.resize (column*rows);
		viewdepth.resize (view.size ());
	}
}

void TerosCam::modview (char elem, int x, int y)
{
	if (getelementindex (x, y) != -1)
	{
		view [getelementindex (x, y)].c = elem;
	}
}

void TerosCam::texturepolygon (TerosPolygon cTerosPolygon, TerosObject obj)
{
	if (cTerosPolygon.putfill () == cTerosPolygon.puttranspid ())
	{
		return;
	}
    
	double p1 [3];
	double p2 [3];
	double p3 [3];
    
	if (!twodconvert (p1, p2, p3, obj, cTerosPolygon))
	{
		return;
	}
    
	double minx = p1 [1];
	double maxx = p1 [1];
	double miny = p1 [2];
	double maxy = p1 [2];
    
	if (p2 [1] < minx)
	{
		minx = p2 [1];
	}
    
	if (p3 [1] < minx)
	{
		minx = p3 [1];
	}
    
	if (p2 [2] < miny)
	{
		miny = p2 [2];
	}
    
	if (p3 [2] < miny)
	{
		miny = p3 [2];
	}
    
	if (p2 [1] > maxx)
	{
		maxx = p2 [1];
	}
    
	if (p3 [1] > maxx)
	{
		maxx = p3 [1];
	}
    
	if (p2 [2] > maxy)
	{
		maxy = p2 [2];
	}
    
	if (p3 [2] > maxy)
	{
		maxy = p3 [2];
	}
    
	if (maxx > m_viewcolumns - 1)
	{
		maxx = m_viewcolumns - 1;
	}
    
	if (maxy > view.size ()/m_viewcolumns - 1)
	{
		maxy = view.size ()/m_viewcolumns - 1;
	}
    
	if (minx < 0)
	{
		minx = 0;
	}
    
	if (miny < 0)
	{
		miny = 0;
	}
    
	int x = minx;
	int y = maxy;
    
	double a = ((p2 [1] - p1 [1])*(p3 [2] - p1 [2]) - (p3 [1] - p1 [1])*(p2 [2] - p1 [2]));
	double b = ((p2 [2] - p1 [2])*(p3 [0] - p1 [0]) - (p3 [2] - p1 [2])*(p2 [0] - p1 [0]));
	double c = ((p2 [0] - p1 [0])*(p3 [1] - p1 [1]) - (p3 [0] - p1 [0])*(p2 [1] - p1 [1]));
	double d = -1*(a*p1 [0] + b*p1 [1] + c*p1 [2]);
    
	while (x <= maxx || y > miny)
	{
		double v1 [2] = {x - p1 [1], y - p1 [2]};
		double v2 [2] = {x - p2 [1], y - p2 [2]};
		double v3 [2] = {x - p3 [1], y - p3 [2]};
        
		double norm;
        
		norm = dist (v1 [0], v1 [1], 0, 0, 0, 0)*1.000001;
        
		v1 [0] /= norm;
		v1 [1] /= norm;
        
		norm = dist (v2 [0], v2 [1], 0, 0, 0, 0)*1.000001;
        
		v2 [0] /= norm;
		v2 [1] /= norm;
        
		norm = dist (v3 [0], v3 [1], 0, 0, 0, 0)*1.000001;
        
		v3 [0] /= norm;
		v3 [1] /= norm;
        
		double angletotal = 0;
        
		angletotal += acos(v1 [0]*v2[0] + v1 [1]*v2 [1]) + acos(v1 [0]*v3 [0] + v1 [1]*v3 [1]) + acos(v2 [0]*v3 [0] + v2 [1]*v3[1]);
        
		if (((-1*d - c*y - b*x)/a < viewdepth [getelementindex (x, y)] || viewdepth [getelementindex (x, y)] == -1) && (-1*d - c*y - b*x)/a > 0 && angletotal > 2*PI - 0.01 && angletotal < 2*PI + 0.01)
		{
			view [getelementindex (x, y)].c = cTerosPolygon.putfill ();
            view [getelementindex (x, y)].fg = cTerosPolygon.getfg ();
            view [getelementindex (x, y)].bg = cTerosPolygon.getbg ();
            view [getelementindex (x, y)].attr = cTerosPolygon.getattr ();


			viewdepth [getelementindex (x, y)] = (-1*d - c*y - b*x)/a;
		}
        
		x++;
        
		if (x > maxx && y > miny)
		{
			x = minx;
			y--;
		}
	}
}

void TerosCam::modviewdepth (double d, int x, int y)
{
	if (getelementindex (x, y) != -1)
	{
		viewdepth [getelementindex (x, y)] = d;
	}
}

void TerosCam::applyrotation (double x, double y, double z, double frompt [3], double returnpt [3], TerosObject obj)
{
	double objbasisx [3];
	double objbasisy [3];
	double objbasisz [3];
    
	obj.putbasis ('x', objbasisx);
	obj.putbasis ('y', objbasisy);
	obj.putbasis ('z', objbasisz);
    
	x = x - frompt [0];
	y = y - frompt [1];
	z = z - frompt [2];
    
	returnpt [0] = x*objbasisx [0] + y*objbasisy [0] + z*objbasisz [0] + frompt [0];
	returnpt [1] = x*objbasisx [1] + y*objbasisy [1] + z*objbasisz [1] + frompt [1];
	returnpt [2] = x*objbasisx [2] + y*objbasisy [2] + z*objbasisz [2] + frompt [2];
    
	x = returnpt [0] - m_camx;
	y = returnpt [1] - m_camy;
	z = returnpt [2] - m_camz;
    
	returnpt [0] = x*cambasisx [0] + y*cambasisy [0] + z*cambasisz [0];
	returnpt [1] = x*cambasisx [1] + y*cambasisy [1] + z*cambasisz [1];
	returnpt [2] = x*cambasisx [2] + y*cambasisy [2] + z*cambasisz [2];
}

void TerosCam::setzoomfactor (double zfac)
{
	m_zoomfactor = zfac;
}

void TerosCam::scalept (double ptscalex, double ptscaley, double ptscalez, double store [3])
{
	store [0] = ptscalex;
	store [1] = m_zoomfactor*(ptscaley)/(ptscalex > 0 ? ptscalex/3 : 0.1) + m_viewcolumns/2;
	store [2] = m_zoomfactor*(ptscalez)/(ptscalex > 0 ? ptscalex/3 : 0.1) + (view.size ()/m_viewcolumns)/2;
}

bool TerosCam::twodconvert (double p1 [3], double p2 [3], double p3 [3], TerosObject obj, TerosPolygon cTerosPolygon)
{
	int nogo = 0;
    
	double pscale [3];
	double actpt [3];
    
	if (obj.putctrscale ())
	{
		pscale [0] = obj.centerx ();
		pscale [1] = obj.centery ();
		pscale [2] = obj.centerz ();
	}
	else
	{
		obj.cpyscalep (pscale);
	}
    
	applyrotation (cTerosPolygon.putpx (0), cTerosPolygon.putpy (0), cTerosPolygon.putpz (0), pscale, actpt, obj);
    
	if (actpt [0] < 0)
	{
		nogo++;
	}
    
	scalept (actpt[0], actpt [1], actpt [2], p1);
    
	applyrotation (cTerosPolygon.putpx (1), cTerosPolygon.putpy (1), cTerosPolygon.putpz (1), pscale, actpt, obj);
    
	if (actpt [0] < 0)
	{
		nogo++;
	}
    
	scalept (actpt[0], actpt [1], actpt [2], p2);
    
	applyrotation (cTerosPolygon.putpx (2), cTerosPolygon.putpy (2), cTerosPolygon.putpz (2), pscale, actpt, obj);
    
	if (actpt [0] < 0)
	{
		nogo++;
	}
    
	if (nogo >= 3)
	{
		return false;
	}
    
	scalept (actpt[0], actpt [1], actpt [2], p3);
    
	return true;
}

char TerosCam::getelement (int x, int y)
{
	if (getelementindex (x, y) != -1)
	{
		return view [getelementindex (x, y)].c;
	}
    
	return ' ';
}

char TerosCam::getelementraw (int index)
{
	if (index < view.size ())
	{
		return view [index].c;
	}
    
	return ' ';
}

int TerosCam::getelementindex (int x, int y)
{
	if (x >= 0 && x < m_viewcolumns && y >= 0 && y < view.size ()/m_viewcolumns)
	{
		return (x + y*m_viewcolumns);
	}
    
	return -1;
}

int TerosCam::objectnum ()
{
	return (int)objects.size ();
}

int TerosCam::putviewsize ()
{
	return (int)view.size ();
}

int TerosCam::putviewcolumns ()
{
	return m_viewcolumns;
}

double TerosCam::getviewdepth (int x, int y)
{
	if (getelementindex (x, y) != -1)
	{
		return viewdepth [getelementindex (x, y)];
	}
    
	return -1;
}

double TerosCam::getviewdepthraw (int index)
{
	if (index < viewdepth.size () && index > 0)
	{
		return viewdepth [index];
	}
    
	return -1;
}

double TerosCam::putcamx ()
{
	return m_camx;
}

double TerosCam::putcamy ()
{
	return m_camy;
}

double TerosCam::putcamz ()
{
	return m_camz;
}

double TerosCam::putzoomfactor ()
{
	return m_zoomfactor;
}

vector <TerosView> TerosCam::putview ()
{
	return view;
}

vector <double> TerosCam::putviewdepth ()
{
	return viewdepth;
}

TerosObject * TerosCam::putobj (int index)
{
	if (index >= 0 && index < objects.size ())
	{
		return objects [index];
	}
    
	return NULL;
}



void TerosCam::moveForward( double speed, double distance){
    
    m_speed = speed;
    
    //  Right - Up - Look
    //    X     Y     Z
    viewMatrix = viewMatrix * (distance*m_speed);
    
    vmml::vector<4, double> translation;
    translation = viewMatrix;

    m_position = m_position + translation;

    m_camx = m_position.x();
    m_camy = m_position.y();
    m_camz = m_position.z();
    
    setcampos(m_camx, m_camy, m_camz);
    
}
