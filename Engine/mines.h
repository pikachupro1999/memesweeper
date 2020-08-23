#pragma once
#include"Mouse.h"
#include"Graphics.h"
#include"SpriteCodex.h"
#include"Vei2.h"
#include<random>
class mines
{  private:
	class cell {
	public:
		enum class type {
			Hidden,
			Release,
			Flag
		};
		cell() = default;
	    cell(const Vei2& a);
		void init(const Vei2&a);
		bool hasbomb1();
		void setbomb();
		void draw(Graphics& gfx);
		void setrelease();
		void setflag();
		void setvalue(int a);
		int getvalue();
		type gettype();
		void settype();
	private:
		Vei2 pos;
		type state = type::Hidden;
		bool hasbomb = false;
		int x=1;
};
public:
	mines();
	void spawnbomb();
	void draw(Graphics& gfx);
	void change(Mouse& mo1);
	void update();
	void update2(int i,int j);
	~mines();
private:
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
	static int constexpr width = 30;
	static int constexpr height = 30;
	static int constexpr celledge = 15;
	cell bombcell[width*height];
	int nbomb=200;
	bool isupdate[width*height] = { false };
};

