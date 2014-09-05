/*
 
 A modified version of TEROS Engine 0.0.2.7 by Kyle L. Miskell - KyleMiskell@gmail.com
 
 Original TEROS project can be found at:
 
 https://github.com/SighoftheSecond/TEROS-ENGINE
 
 - Yamamushi
 
 */

#include "terosobject.h"
#include "terospolygon.h"
#include <iostream>

#include "logger.h"

TerosObject::TerosObject ()
{
	sides.resize (0);
	olink.resize (0);
	rzlink.resize (0);
	rxlink.resize (0);
	rylink.resize (0);
	loadsides.resize (0);
    
	ctrscale = true;
    
	scalep [0] = 0.0;
	scalep [1] = 0.0;
	scalep [2] = 0.0;
    
	basisreset ();
}

void TerosObject::addside (TerosPolygon * side)
{
	sides.resize (sides.size () + 1);
    
	sides [sides.size () - 1] = side;
}

void TerosObject::delside (int index)
{
	if (index < sides.size ())
	{
		sides.erase (sides.begin () + index);
	}
}

void TerosObject::modside (int index, TerosPolygon * side)
{
	if (index < sides.size ())
	{
		sides [index] = side;
	}
}

void TerosObject::rref3x4 (double B [3][4])
{
	double multiple;
    
	if (B [0][0] < 0.00000000001 && B [0][0] > -0.00000000001)
	{
		double buffer;
        
		if (B [1][0] != 0)
		{
			buffer = B [1][0];
			B [1][0] = B [0][0];
			B [0][0] = buffer;
            
			buffer = B [1][1];
            
			B [1][1] = B [0][1];
			B [0][1] = buffer;
            
			buffer = B [1][2];
            
			B [1][2] = B [0][2];
			B [0][2] = buffer;
            
			buffer = B [1][3];
            
			B [1][3] = B [0][3];
			B [0][3] = buffer;
		}
		else
		{
			buffer = B [2][0];
            
			B [2][0] = B [0][0];
			B [0][0] = buffer;
            
			buffer = B [2][1];
            
			B [2][1] = B [0][1];
			B [0][1] = buffer;
            
			buffer = B [2][2];
            
			B [2][2] = B [0][2];
			B [0][2] = buffer;
            
			buffer = B [2][3];
            
			B [2][3] = B [0][3];
			B [0][3] = buffer;
		}
	}
    
	multiple = B [0][0];
    
	for (int j = 0; j < 4; j++)
	{
		B [0][j] /= multiple;
	}
    
	multiple = B [1][0];
    
	for (int i = 1; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			B [i][j] = B [i][j] - B [0][j]*multiple;
		}
        
		multiple = B [2][0];
	}
    
	if (B [1][1] < 0.00000000001 && B [1][1] > -0.00000000001)
	{
		double buffer;
        
		buffer = B [2][1];
        
		B [2][1] = B [1][1];
		B [1][1] = buffer;
        
		buffer = B [2][2];
        
		B [2][2] = B [1][2];
		B [1][2] = buffer;
        
		buffer = B [2][3];
        
		B [2][3] = B [1][3];
		B [1][3] = buffer;
	}
    
	multiple = B [1][1];
    
	for (int j = 0; j < 4; j++)
	{
		B [1][j] /= multiple;
	}
    
	multiple = B [0][1];
    
	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			if (i != 1)
			{
				B [i][j] -= B [1][j]*multiple;
			}
		}
        
		multiple = B [2][1];
	}
    
	multiple = B [2][2];
    
	for (int j = 0; j < 4; j++)
	{
		B [2][j] /= multiple;
	}
    
	multiple = B [0][2];
    
	for (int i = 0; i < 2; i++)
	{
		for (int j = 2; j < 4; j++)
		{
			B [i][j] -= B [2][j]*multiple;
		}
        
		multiple = B [1][2];
	}
    
	double norm = sqrt(pow(B[0][3], 2) + pow (B[1][3], 2) + pow(B[2][3], 2));
    
	if (norm != 0)
	{
		B [0][3] /= norm;
		B [1][3] /= norm;
		B [2][3] /= norm;
	}
}

void TerosObject::rot (char norm, double angle)
{
	int rnum;
    
	double * primarybasis [3];
	double * secondarybasis [3];
	double * normalbasis [3];
    
	if (norm == 'z' || norm == 'Z')
	{
		rnum = rzlink.size ();
		
	}
	else if (norm == 'x' || norm == 'X')
	{
		rnum = rxlink.size ();
	}
	else if (norm == 'y' || norm == 'Y')
	{
		rnum = rylink.size ();
	}
    
	for (int i = -1; i < rnum; i++)
	{
		TerosObject * cobj;
        
		if (i == -1)
		{
			cobj = this;
		}
		else if (norm == 'z' || norm == 'Z')
		{
			cobj = rzlink [i];
		}
		else if (norm == 'x' || norm == 'X')
		{
			cobj = rxlink [i];
		}
		else if (norm == 'y' || norm == 'Y')
		{
			cobj = rylink [i];
		}
        
		double lxbasis [3];
		double lybasis [3];
		double lzbasis [3];
        
		cobj -> putbasis ('x', lxbasis);
		cobj -> putbasis ('y', lybasis);
		cobj -> putbasis ('z', lzbasis);
        
		if (norm == 'z' || norm == 'Z')
		{
			primarybasis [0] = &lybasis [0];
			primarybasis [1] = &lybasis [1];
			primarybasis [2] = &lybasis [2];
            
			secondarybasis [0] = &lxbasis [0];
			secondarybasis [1] = &lxbasis [1];
			secondarybasis [2] = &lxbasis [2];
            
			normalbasis [0] = &lzbasis [0];
			normalbasis [1] = &lzbasis [1];
			normalbasis [2] = &lzbasis [2];
		}
		else if (norm == 'x' || norm == 'X')
		{
			primarybasis [0] = &lzbasis [0];
			primarybasis [1] = &lzbasis [1];
			primarybasis [2] = &lzbasis [2];
            
			secondarybasis [0] = &lybasis [0];
			secondarybasis [1] = &lybasis [1];
			secondarybasis [2] = &lybasis [2];
            
			normalbasis [0] = &lxbasis [0];
			normalbasis [1] = &lxbasis [1];
			normalbasis [2] = &lxbasis [2];
		}
		else if (norm == 'y' || norm == 'Y')
		{
			primarybasis [0] = &lxbasis [0];
			primarybasis [1] = &lxbasis [1];
			primarybasis [2] = &lxbasis [2];
            
			secondarybasis [0] = &lzbasis [0];
			secondarybasis [1] = &lzbasis [1];
			secondarybasis [2] = &lzbasis [2];
            
			normalbasis [0] = &lybasis [0];
			normalbasis [1] = &lybasis [1];
			normalbasis [2] = &lybasis [2];
		}
		else
		{
			return;
		}
        
		double transformation [3][4];
        
		transformation [0][0] = *primarybasis [0];
		transformation [0][1] = *primarybasis [1];
		transformation [0][2] = *primarybasis [2];
		transformation [0][3] = cos (angle);
        
		transformation [1][0] = *normalbasis [0];
		transformation [1][1] = *normalbasis [1];
		transformation [1][2] = *normalbasis [2];
		transformation [1][3] = 0;
        
		transformation [2][0] = *secondarybasis [0];
		transformation [2][1] = *secondarybasis [1];
		transformation [2][2] = *secondarybasis [2];
		transformation [2][3] = cos (PI/2.0 + angle);
        
		rref3x4 (transformation);
        
		*primarybasis [0] = transformation [0][3];
		*primarybasis [1] = transformation [1][3];
		*primarybasis [2] = transformation [2][3];
        
		transformation [0][0] = *secondarybasis [0];
		transformation [0][1] = *secondarybasis [1];
		transformation [0][2] = *secondarybasis [2];
		transformation [0][3] = cos (angle);
        
		transformation [1][0] = *normalbasis [0];
		transformation [1][1] = *normalbasis [1];
		transformation [1][2] = *normalbasis [2];
		transformation [1][3] = 0;
        
		transformation [2][0] = *primarybasis [0];
		transformation [2][1] = *primarybasis [1];
		transformation [2][2] = *primarybasis [2];
		transformation [2][3] = 0;
        
		rref3x4 (transformation);
        
		*secondarybasis [0] = transformation [0][3];
		*secondarybasis [1] = transformation [1][3];
		*secondarybasis [2] = transformation [2][3];
        
		cobj -> modbasis ('x', lxbasis);
		cobj -> modbasis ('y', lybasis);
		cobj -> modbasis ('z', lzbasis);
	}
}

void TerosObject::basisreset ()
{
	xbasis [0] = 1;
	xbasis [1] = 0;
	xbasis [2] = 0;
    
	ybasis [0] = 0;
	ybasis [1] = 1;
	ybasis [2] = 0;
    
	zbasis [0] = 0;
	zbasis [1] = 0;
	zbasis [2] = 1;
}

void TerosObject::putbasis (char basis, double receptacle [3])
{
	if (basis == 'x' || basis == 'X')
	{
		receptacle [0] = xbasis [0];
		receptacle [1] = xbasis [1];
		receptacle [2] = xbasis [2];
	}
	else if (basis == 'y' || basis == 'Y')
	{
		receptacle [0] = ybasis [0];
		receptacle [1] = ybasis [1];
		receptacle [2] = ybasis [2];
	}
	else if (basis == 'z' || basis == 'Z')
	{
		receptacle [0] = zbasis [0];
		receptacle [1] = zbasis [1];
		receptacle [2] = zbasis [2];
	}
}

void TerosObject::modbasis (char basis, double nbasis [3])
{
	if (basis == 'x' || basis == 'X')
	{
		xbasis [0] = nbasis [0];
		xbasis [1] = nbasis [1];
		xbasis [2] = nbasis [2];
	}
	else if (basis == 'y' || basis == 'Y')
	{
		ybasis [0] = nbasis [0];
		ybasis [1] = nbasis [1];
		ybasis [2] = nbasis [2];
	}
	else if (basis == 'z' || basis == 'Z')
	{
		zbasis [0] = nbasis [0];
		zbasis [1] = nbasis [1];
		zbasis [2] = nbasis [2];
	}
}
void TerosObject::shiftctr (double sx, double sy, double sz)
{
	for (int n = -1; n < int(olink.size ()); n++)
	{
		TerosObject * cobj;
        
		if (n == -1)
		{
			cobj = this;
		}
		else
		{
			cobj = olink [n];
		}
        
		for (int i = 0; i < cobj -> sidenum (); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				double x = cobj -> putside(i) -> putpx (j);
				double y = cobj -> putside(i) -> putpy (j);
				double z = cobj -> putside(i) -> putpz (j);
                
				x += sx;
				y += sy;
				z += sz;
                
				cobj -> putside (i) -> modp (j, x, y, z);
			}
		}
	}
}

void TerosObject::setctr (double cx, double cy, double cz)
{
	double c [3];
    
	center (c);
    
	double diffx = cx - c [0];
	double diffy = cy - c [1];
	double diffz = cz - c [2];
    
	shiftctr (diffx, diffy, diffz);
}

void TerosObject::center (double store [3])
{
	store [0] = 0;
	store [1] = 0;
	store [2] = 0;
    
	double ptnum = 0;
    
	for (int i = 0; i < sides.size (); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			store [0] += sides [i] -> putpx (j);
			store [1] += sides [i] -> putpy (j);
			store [2] += sides [i] -> putpz (j);
		}
        
		ptnum += 3;
	}
    
	if (ptnum != 0)
	{
		store [0] /= ptnum;
		store [1] /= ptnum;
		store [2] /= ptnum;
	}
}

void TerosObject::ctrscaleoff (double x, double y, double z)
{
	ctrscale = false;
    
	scalep [0] = x;
	scalep [1] = y;
	scalep [2] = z;
}

void TerosObject::ctrscaleon ()
{
	ctrscale = true;
}

void TerosObject::cpyscalep (double p [3])
{
	p [0] = scalep [0];
	p [1] = scalep [1];
	p [2] = scalep [2];
}

void TerosObject::addolink (TerosObject * linko, bool mode)
{
	for (int i = 0; i < olink.size (); i++)
	{
		if (olink [i] == linko)
		{
			return;
		}
	}
    
	if (mode)
	{
		for (int i = 0; i < linko -> olinknum (); i++)
		{
			linko -> putolink (i) -> addolink (this, false);
            
			olink.resize (olink.size () + 1);
            
			olink [olink.size () - 1] = linko -> putolink (i);
            
			for (int s = 0; s < olink.size (); s++)
			{
				olink [s] -> addolink (linko -> putolink (i), false);
				linko -> putolink (i) -> addolink (olink [s], false);
			}
		}
        
		linko -> addolink (this, false);
        
		for (int i = 0; i < olink.size (); i++)
		{
			olink [i] -> addolink (linko, false);
			linko -> addolink (olink [i], false);
		}
	}
    
	olink.resize (olink.size () + 1);
    
	olink [olink.size () - 1] = linko;
}

void TerosObject::addrzlink (TerosObject * linkrz, bool mode)
{
	for (int i = 0; i < rzlink.size (); i++)
	{
		if (rzlink [i] == linkrz)
		{
			return;
		}
	}
    
	if (mode)
	{
		for (int i = 0; i < linkrz -> rzlinknum (); i++)
		{
			linkrz -> putrzlink (i) -> addrzlink (this, false);
            
			rzlink.resize (rzlink.size () + 1);
            
			rzlink [rzlink.size () - 1] = linkrz -> putrzlink (i);
            
			for (int s = 0; s < rzlink.size (); s++)
			{
				rzlink [s] -> addrzlink (linkrz -> putrzlink (i), false);
				linkrz -> putrzlink (i) -> addrzlink (rzlink [s], false);
			}
		}
        
		linkrz -> addrzlink (this, false);
        
		for (int i = 0; i < rzlink.size (); i++)
		{
			rzlink [i] -> addrzlink (linkrz, false);
			linkrz -> addrzlink (rzlink [i], false);
		}
	}
    
	rzlink.resize (rzlink.size () + 1);
    
	rzlink [rzlink.size () - 1] = linkrz;
}

void TerosObject::addrxlink (TerosObject * linkrx, bool mode)
{
	for (int i = 0; i < rxlink.size (); i++)
	{
		if (rxlink [i] == linkrx)
		{
			return;
		}
	}
    
	if (mode)
	{
		for (int i = 0; i < linkrx -> rxlinknum (); i++)
		{
			linkrx -> putrxlink (i) -> addrxlink (this, false);
            
			rxlink.resize (rxlink.size () + 1);
            
			rxlink [rxlink.size () - 1] = linkrx -> putrxlink (i);
            
			for (int s = 0; s < rxlink.size (); s++)
			{
				rxlink [s] -> addrxlink (linkrx -> putrxlink (i), false);
				linkrx -> putrxlink (i) -> addrxlink (rxlink [s], false);
			}
		}
        
		linkrx -> addrxlink (this, false);
        
		for (int i = 0; i < rxlink.size (); i++)
		{
			rxlink [i] -> addrxlink (linkrx, false);
			linkrx -> addrxlink (rxlink [i], false);
		}
	}
    
	rxlink.resize (rxlink.size () + 1);
    
	rxlink [rxlink.size () - 1] = linkrx;
}

void TerosObject::addrylink (TerosObject * linkry, bool mode)
{
	for (int i = 0; i < rylink.size (); i++)
	{
		if (rylink [i] == linkry)
		{
			return;
		}
	}
    
	if (mode)
	{
		for (int i = 0; i < linkry -> rylinknum (); i++)
		{
			linkry -> putrylink (i) -> addrylink (this, false);
            
			rylink.resize (rylink.size () + 1);
            
			rylink [rylink.size () - 1] = linkry -> putrylink (i);
            
			for (int s = 0; s < rylink.size (); s++)
			{
				rylink [s] -> addrylink (linkry -> putrylink (i), false);
				linkry -> putrylink (i) -> addrylink (rylink [s], false);
			}
		}
        
		linkry -> addrylink (this, false);
        
		for (int i = 0; i < rylink.size (); i++)
		{
			rylink [i] -> addrylink (linkry, false);
			linkry -> addrylink (rylink [i], false);
		}
	}
    
	rylink.resize (rylink.size () + 1);
    
	rylink [rylink.size () - 1] = linkry;
}

void TerosObject::delolink (int index, bool mode)
{
	if (olink.size () == 0)
	{
		return;
	}
    
	if (mode)
	{
		for (int i = 0; i < olink.size (); i++)
		{
			for (int j = 0; j < olink [i] -> olinknum (); j++)
			{
				if (olink [i] -> putolink (j) == this)
				{
					olink [i] -> delolink (j, false);
				}
			}
		}
        
		olink.resize (0);
	}
	else
	{
		olink.erase (olink.begin () + index);
	}
}

void TerosObject::delrzlink (int index, bool mode)
{
	if (rzlink.size () == 0)
	{
		return;
	}
    
	if (mode)
	{
		for (int i = 0; i < rzlink.size (); i++)
		{
			for (int j = 0; j < rzlink [i] -> rzlinknum (); j++)
			{
				if (rzlink [i] -> putrzlink (j) == this)
				{
					rzlink [i] -> delrzlink (j, false);
				}
			}
		}
        
		rzlink.resize (0);
	}
	else
	{
		rzlink.erase (rzlink.begin () + index);
	}
}

void TerosObject::delrxlink (int index, bool mode)
{
	if (rxlink.size () == 0)
	{
		return;
	}
    
	if (mode)
	{
		for (int i = 0; i < rxlink.size (); i++)
		{
			for (int j = 0; j < rxlink [i] -> rxlinknum (); j++)
			{
				if (rxlink [i] -> putrxlink (j) == this)
				{
					rxlink [i] -> delrxlink (j, false);
				}
			}
		}
        
		rxlink.resize (0);
	}
	else
	{
		rxlink.erase (rxlink.begin () + index);
	}
}

void TerosObject::delrylink (int index, bool mode)
{
	if (rylink.size () == 0)
	{
		return;
	}
    
	if (mode)
	{
		for (int i = 0; i < rylink.size (); i++)
		{
			for (int j = 0; j < rylink [i] -> rylinknum (); j++)
			{
				if (rylink [i] -> putrylink (j) == this)
				{
					rylink [i] -> delrylink (j, false);
				}
			}
		}
        
		rylink.resize (0);
	}
	else
	{
		rylink.erase (rylink.begin () + index);
	}
}

void TerosObject::setutexturemode (bool state)
{
	for (int i = 0; i < sides.size (); i++)
	{
		sides [i] -> settexturemode (state);
	}
}

void TerosObject::saveobj (std::string filename)
{
    std::ofstream outfile;
    
	filename += ".tr3";
    
	outfile.open (filename.c_str ());
    
	for (int i = 0; i < sidenum (); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			outfile << putside (i) -> putpx (j) << " ";
			outfile << putside (i) -> putpy (j) << " ";
			outfile << putside (i) -> putpz (j) << " \n";
		}
        
		outfile << int (putside (i) -> putfill ()) << "\n";
		outfile << int (putside (i) -> puttranspid ()) << "\n";
		outfile << putside (i) -> puttexturemode ();
        
		if (!(i + 1 == sidenum ()))
		{
			outfile << "\n";
		}
	}
    
	outfile.close ();
}

void TerosObject::clrloadsides ()
{
	loadsides.resize (0);
}

bool TerosObject::putctrscale ()
{
	return ctrscale;
}

int TerosObject::sidenum ()
{
	return sides.size ();
}

int TerosObject::olinknum ()
{
	return olink.size ();
}

int TerosObject::rzlinknum ()
{
	return rzlink.size ();
}

int TerosObject::rxlinknum ()
{
	return rxlink.size ();
}

int TerosObject::rylinknum ()
{
	return rylink.size ();
}

int TerosObject::loadobj (std::string filename)
{
	bool txtmde = false;
    
	int linenum = 0;
	int intbuff = 0;
    
	double coordbffx = 0.0;
	double coordbffy = 0.0;
	double coordbffz = 0.0;
    
    std::string line;
    
    std::ifstream infile;
    
	if (!(filename [filename.size () - 1] == '3' && filename [filename.size () - 2] == 'r' && filename [filename.size () - 3] == 't' && filename [filename.size () - 4] == '.'))
	{
		return 1;
	}
    
	infile.open (filename.c_str ());
    
	while (!infile.eof())
	{
		getline (infile, line);
		linenum++;
	}
    
	infile.close ();
    
	if (linenum%6)
	{
		return 2;
	}
    
	sides.resize (0);
	olink.resize (0);
	rzlink.resize (0);
	rxlink.resize (0);
	rylink.resize (0);
	loadsides.resize (0);
    
	ctrscale = true;
    
	scalep [0] = 0.0;
	scalep [1] = 0.0;
	scalep [2] = 0.0;
    
	basisreset ();
    
	infile.open (filename.c_str ());
    
	for (int ln = 0; ln < linenum/6; ln++)
	{
		loadsides.resize (loadsides.size () + 1);
        
		for (int i = 0; i < 3; i++)
		{
			infile >> coordbffx >> coordbffy >> coordbffz;
			loadsides [loadsides.size () - 1].modp (i, coordbffx, coordbffy, coordbffz);
		}
        
		infile >> intbuff;
		loadsides [loadsides.size () - 1].setfill (char(intbuff));
        
		infile >> intbuff;
		loadsides [loadsides.size () - 1].settranspid (char(intbuff));
        
		infile >> txtmde;
		loadsides [loadsides.size () - 1].settexturemode (txtmde);
	}
    
	for (int i = 0; i < loadsides.size (); i++)
	{
		addside (&(loadsides [i]));
	}
    
	infile.close ();
    
	return 0;
}

int TerosObject::loadsidenum ()
{
	return loadsides.size ();
}

double TerosObject::centerx ()
{
	double x [3];
    
	center (x);
    
	return x [0];
}

double TerosObject::centery ()
{
	double y [3];
    
	center (y);
    
	return y [1];
}

double TerosObject::centerz ()
{
	double z [3];
    
	center (z);
    
	return z [2];
}


TerosPolygon * TerosObject::putside (int index)
{
	if (index < sides.size () && index >= 0)
	{
		return sides [index];
	}
    else
        return nullptr;
}

TerosObject * TerosObject::putolink (int index)
{
	if (index >= 0 && index < olink.size ())
	{
		return olink [index];
	}
    else
        return nullptr;
}

TerosObject * TerosObject::putrzlink (int index)
{
	if (index >= 0 && index < rzlink.size ())
	{
		return rzlink [index];
	}
    else
        return nullptr;
}

TerosObject * TerosObject::putrxlink (int index)
{
	if (index >= 0 && index < rxlink.size ())
	{
		return rxlink [index];
	}
    else
        return nullptr;
}

TerosObject * TerosObject::putrylink (int index)
{
	if (index >= 0 && index < rylink.size ())
	{
		return rylink [index];
	}
    else
        return nullptr;
}

TerosPolygon TerosObject::putloadside (int index)
{
	if (index >=0 && index < loadsides.size ())
	{
		return loadsides [index];
	}
    else{
        return loadsides [0];
    }
}

std::vector <TerosPolygon> TerosObject::permcpy ()
{
	std::vector<TerosPolygon> newTerosPolygons (0);
    
	newTerosPolygons.resize (sidenum ());
    
	if (ctrscale)
	{
		center (scalep);
	}
    
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
    
	for (int i = 0; i < newTerosPolygons.size (); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			x = (putside (i) -> putpx (j)) - scalep [0];
			y = (putside (i) -> putpy (j)) - scalep [1];
			z = (putside (i) -> putpz (j)) - scalep [2];
            
			(newTerosPolygons [i]).modp (j, (x*xbasis [0] + y*ybasis [0] + z*zbasis [0] + scalep [0]), (x*xbasis [1] + y*ybasis [1] + z*zbasis [1] + scalep [1]), (x*xbasis [2] + y*ybasis [2] + z*zbasis [2] + scalep [2]));
		}
        
		(newTerosPolygons [i]).setfill (putside (i) -> putfill ());
		(newTerosPolygons [i]).settexturemode (putside (i) -> puttexturemode ());
		(newTerosPolygons [i]).settranspid (putside (i) -> puttranspid ());
	}
    
	return newTerosPolygons;
}
