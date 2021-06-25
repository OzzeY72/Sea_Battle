#pragma once
#include "Game.h"

class ShipCell
{
public:
	int x;
	int y;
	int rx = -1;
	int ry = -1;
	bool live = true;
	sf::Texture texture;
	sf::RectangleShape sc;

	ShipCell()
	{
		x = 0;
		y = 0;
		texture.loadFromFile("ship.png");
		sc.setSize(sf::Vector2f(50,50));
	}

	void setPosition(int x, int y)
	{
		this->x = x;
		this->y = y;
		sc.setPosition(x, y);
	}
	void setImage(std::string str)
	{
		this->texture.loadFromFile(str);
		sc.setTexture(&this->texture);
	}

};