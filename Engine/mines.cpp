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

void mines::change(Mouse& mo1)
{
	const Vei2 poscur = mo1.GetPos1();
	const Vei2 poscur1 = poscur.adaptpos();
	bombcell[poscur1.x*height + poscur1.y].changestate(mo1);

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

void mines::cell::changestate( Mouse& mo)
{
	while (!mo.IsEmpty())
	{
		const Mouse::Event e = mo.Read();
		if (e.GetType() == Mouse::Event::Type::LPress)
	{
			if (state == type::Hidden)
			{
			 state = type::Release;
		    }
		}
		 if (e.GetType() == Mouse::Event::Type::RPress)
		{    
			if (state == type::Hidden)
			{
				state = type::Flag;
			}
			else if (state == type::Flag)
			{
				state = type::Hidden;
			}
		}
	}
}

void mines::cell::setvalue(int a)
{  
	assert(a >= 0 && a <= 8);
	x = a;
}

void mines::cell::draw(Graphics & gfx)
{
		switch (state)
		{
		case mines::cell::type::Hidden:
			SpriteCodex::DrawTileButton(pos, gfx);
			break;
		case mines::cell::type::Flag:
			SpriteCodex::DrawTile0(pos, gfx);
			SpriteCodex::DrawTileFlag(pos, gfx);
			break;
		case mines::cell::type::Release:
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

