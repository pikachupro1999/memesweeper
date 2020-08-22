#pragma once
#include"Mouse.h"
#include"Graphics.h"
#include"SpriteCodex.h"
#include"Vei2.h"
#include<random>
class mines
{
	class cell {
	public:
		cell() = default;
	    cell(const Vei2& a);
		void init(const Vei2&a);
		bool hasbomb1();
		void setbomb();
		void draw(Graphics& gfx);
		void changestate(Mouse& mo);
		void setvalue(int a);
	private:
		enum class type {
			Hidden,
			Release,
			Flag
		};
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
	int nbomb=40;
};

