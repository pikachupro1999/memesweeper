#include "mines.h"
#include<assert.h>


mines::mines():rng(rd()),xDist(0,29),yDist(0,29)
{
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			bombcell[i*height + j].init(Vei2(i*celledge, j*celledge));
}

void mines::spawnbomb()
{
	int a ;
	int b ;
	do {
		a = xDist(rng);
		b = yDist(rng);
		if (!bombcell[a*width + b].hasbomb1())
		{
			bombcell[a*width + b].setbomb();
			--nbomb;
		}

	} while (nbomb > 0);
}

void mines::draw(Graphics& gfx)
{
	for (int i = 0; i < width; i++)
		for (int j = 0; j < width; j++)
			bombcell[i*height + j].draw(gfx);
}

void mines::change(Mouse & mo1)
{

	while (!mo1.IsEmpty())
	{
		const Mouse::Event e = mo1.Read();
		const Vei2 a = mo1.GetPos1();
		const Vei2 b = a.adaptpos();
		if (e.GetType() == Mouse::Event::Type::LPress)
		{
			
			bombcell[b.x*width + b.y].setrelease();
			mines::update2(b.x, b.y);
			
		}
		if (e.GetType() == Mouse::Event::Type::RPress)
		{
			bombcell[b.x*width + b.y].setflag();
		}
	}

}

void mines::update()
{
	int count;
	for(int i=0;i<width;++i)
		for (int j = 0; j < height; ++j)
		{
			count = 0;
			if (i == 0)
			{
				if (j == 0)
				{
					if (bombcell[1].hasbomb1())
						count++;
					if (bombcell[height].hasbomb1())
						count++;
					bombcell[0].setvalue(count);
				}
				else if(j==width-1) {
					if (bombcell[width-2].hasbomb1())
						count++;
					if (bombcell[2*width-1].hasbomb1())
						count++;
					bombcell[width - 1].setvalue(count);
					
				}
				else
				{
					if (bombcell[j-1].hasbomb1())
						count++;
					if (bombcell[j+1].hasbomb1())
						count++;
					if (bombcell[width+j].hasbomb1())
						count++;
					bombcell[j].setvalue(count);
				}
			}
			else if (i == height - 1)
			{ 
				if (j == 0)
				{
					if (bombcell[(i-1)*width].hasbomb1())
						count++;
					if (bombcell[i*width+1].hasbomb1())
						count++;
					bombcell[i*width].setvalue(count);
				}
				else if (j == width - 1) {
					if (bombcell[i*width+j-1].hasbomb1())
						count++;
					if (bombcell[(i-1)*width+j].hasbomb1())
						count++;
					bombcell[(i+1)*(j+1)-1].setvalue(count);

				}
				else
				{
					if (bombcell[i*width+j+1].hasbomb1())
						count++;
					if (bombcell[i*width + j + j-1].hasbomb1())
						count++;
					if (bombcell[(i-1)*width+j].hasbomb1())
						count++;
					bombcell[i*width+j].setvalue(count);
				}
			}
			else {
				if (j == 0)
				{
					if (bombcell[i*width + j + 1].hasbomb1())
						count++;
					if (bombcell[(i+1)*width + j].hasbomb1())
						count++;
					if (bombcell[(i - 1)*width + j].hasbomb1())
						count++;
					bombcell[i*width+j].setvalue(count);
				}
				else if (j == width - 1)
				{
					if (bombcell[i*width + j -1].hasbomb1())
						count++;
					if (bombcell[(i+1)*width + j ].hasbomb1())
						count++;
					if (bombcell[(i - 1)*width + j].hasbomb1())
						count++;
					bombcell[i*width+j].setvalue(count);
				}
				else {
					if (bombcell[i*width + j - 1].hasbomb1())
						count++;
					if (bombcell[i*width + j + 1].hasbomb1())
						count++;
					if (bombcell[(i + 1)*width + j].hasbomb1())
						count++;
					if (bombcell[(i - 1)*width + j].hasbomb1())
						count++;
					bombcell[i*width + j].setvalue(count);
				}
			}
		}
}

void mines::update2(int i, int j)
{
	if ((!bombcell[i*width + j].hasbomb1()) && (bombcell[i*width + j].getvalue() == 0))
	{
		isupdate[i*width + j] = true;
		if ((i - 1 >= 0) && (i - 1 < width) && (j - 1 >= 0) && (j - 1 < height))
		{
			if (!isupdate[(i - 1)*width + j - 1])
			{
				update2(i - 1, j - 1);
			}
			bombcell[(i - 1)*width + j - 1].settype();
		}

		if ((i - 1 >= 0) && (i - 1 < width) && (j >= 0) && (j < height))
		{  
			if (!isupdate[(i - 1)*width + j])
			{
				update2(i - 1, j );
			}
			bombcell[(i - 1)*width + j].settype();

		}
		if ((i - 1 >= 0) && (i - 1 < width) && (j + 1 >= 0) && (j + 1 < height))
		{   
			if (!isupdate[(i - 1)*width + j + 1])
			{
				update2(i - 1, j + 1);
			}
			bombcell[(i - 1)*width + j + 1].settype();

		}
		if ((i >= 0) && (i < width) && (j - 1 >= 0) && (j - 1 < height))
		{   
			if (!isupdate[(i)*width + j - 1])
			{
				update2(i , j - 1);
			}
			bombcell[(i)*width + j - 1].settype();

		}
		if ((i >= 0) && (i < width) && (j + 1 >= 0) && (j + 1 < height))
		{   
			if (!isupdate[(i )*width + j + 1])
			{
				update2(i , j + 1);
			}
			bombcell[(i)*width + j + 1].settype();
		}

		if ((i + 1 >= 0) && (i + 1 < width) && (j - 1 >= 0) && (j - 1 < height))
		{   
			if (!isupdate[(i + 1)*width + j - 1])
			{
				update2(i + 1, j - 1);
			}
			bombcell[(i + 1)*width + j - 1].settype();
		}
		if ((i + 1 >= 0) && (i + 1 < width) && (j >= 0) && (j < height))
		{   
			if (!isupdate[(i + 1)*width + j])
			{
				update2(i + 1, j );
			}
			bombcell[(i + 1)*width + j - 1].settype();

		}
		if ((i + 1 >= 0) && (i + 1 < width) && (j + 1 >= 0) && (j + 1 < height))
		{   
			if (!isupdate[(i +1)*width + j + 1])
			{
				update2(i + 1, j + 1);
			}
			bombcell[(i + 1)*width + j - 1].settype();
		}

	}
}
	


mines::~mines()
{
}

mines::cell::cell(const Vei2 & a):pos(a)
{ 
}

void mines::cell::init(const Vei2 & a)
{
	pos = a;
}

bool mines::cell::hasbomb1()
{
	return hasbomb;
}

void mines::cell::setbomb()
{ 
	hasbomb = true;
}

void mines::cell::setvalue(int a)
{  
	assert(a >= 0 && a <= 8);
	x = a;
}

int mines::cell::getvalue()
{
	return x;
}

mines::cell::type mines::cell::gettype()
{
	return state;
}

void mines::cell::settype()
{
	state = type::Release;
}

void mines::cell::draw(Graphics & gfx)
{
		switch (state)
		{
		case mines::cell::type::Hidden:
			for (int i = 0; i <= 15; i++)
				for (int j = 0; j <= 15; j++)
					gfx.PutPixel(pos.x + i, pos.y + j, Color(77,77,77));
			SpriteCodex::DrawTileButton(pos, gfx);
			break;
		case mines::cell::type::Flag:
			for (int i = 0; i <= 15; i++)
				for (int j = 0; j <= 15; j++)
					gfx.PutPixel(pos.x + i, pos.y + j, Color(77, 77, 77));
			SpriteCodex::DrawTile0(pos, gfx);
			SpriteCodex::DrawTileFlag(pos, gfx);
			break;
		case mines::cell::type::Release:
			for (int i = 0; i <= 15; i++)
				for (int j = 0; j <= 15; j++)
					gfx.PutPixel(pos.x + i, pos.y + j, Color(200, 200, 200));
			if (!hasbomb)
			{
				switch (x)
				{
				case 1:
					SpriteCodex::DrawTile1(pos, gfx);
					break;
				case 2:
					SpriteCodex::DrawTile2(pos, gfx);
					break;
				case 3:
					SpriteCodex::DrawTile3(pos, gfx);
					break;
				case 4:
					SpriteCodex::DrawTile4(pos, gfx);
					break;
				case 5:
					SpriteCodex::DrawTile5(pos, gfx);
					break;
				case 6:
					SpriteCodex::DrawTile6(pos, gfx);
					break;
				case 7:
					SpriteCodex::DrawTile7(pos, gfx);
					break;
				case 8:
					SpriteCodex::DrawTile8(pos, gfx);
					break;
				default:
					SpriteCodex::DrawTileButton(pos, gfx);
					break;
				}
			}
			else
			{
				SpriteCodex::DrawTileBombRed(pos, gfx);
			}

		default:
		{}
		}
	}

void mines::cell::setrelease()
{
	state = type::Release;
}

void mines::cell::setflag()
{
	state = type::Flag;
}




