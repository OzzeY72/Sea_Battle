#pragma once
#include "Game.h"

class Ship
{
public:
	int x;
	int y;
	int type;
	int id;
	int rx = -1;
	int ry = -1;

	ShipCell scell[4];

	enum dir
	{
		FORWARD,
		LEFT
	};

	dir direct;

	bool live;

	Ship(int x, int y, dir d, int type, bool live)
	{
		this->x = x;
		this->y = y;
		this->direct = d;
		this->type = type;
		this->live = live;
	}
	Ship()
	{
		this->x = 0;
		this->y = 0;
		this->direct = FORWARD;
		this->type = 4;
		this->live = false;
	}

	bool isGoodPosition(int x, int y, Ship *ship[10])
	{
		//std::cout << "Check" << std::endl;
		//std::cout << x << " " << y << std::endl;
		if (x < 0 || x >= 10 || y < 0 || y >= 10) return false;
		//std::cout << "Check" << std::endl;
		for (int h = 0; h < type; h++)
		{
			if (type == 1) break;
			if (scell[h].rx < 0 || scell[h].rx >= 10 || scell[h].ry < 0 || scell[h].ry >= 10) return false;
		}
		//std::cout << "Check1" << std::endl;
		for (int h = 0; h < type; h++) {
			if (type == 1) break;
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < ship[i]->type; j++)
				{
					for (int g = scell[h].rx-1; g < scell[h].rx+2; g++)
					{
						for (int w = scell[h].ry - 1; w < scell[h].ry + 2; w++)
						{
							if (g >= 0 && g < 10 && w >= 0 && w < 10)
							{
								if (ship[i]->scell[j].rx != -1 && ship[i]->rx != -1)
								{
									if (id != ship[i]->id)
									{
										if (ship[i]->scell[j].rx == g && ship[i]->scell[j].ry == w)
										{
											//std::cout << i << " " << h << " " << j << " P " << g << " " << w << std::endl;
											return false;
										}
										if (ship[i]->rx == g && ship[i]->ry == w)
										{
											return false;
										}
										//std::cout << ship[i]->rx  << " " << ship[i]->ry << " P " << g << " " << w << std::endl;
									}
								}
							}
							//else return false;
						}
					}
				}
			}
		}
		
		for (int i = 0; i < 10; i++)
		{
			//if (type != 1) break;
			for (int j = 0; j < ship[i]->type; j++)
			{
				for (int g = rx - 1; g < rx + 2; g++)
				{
					for (int w = ry - 1; w < ry + 2; w++)
					{
						if (g >= 0 && g < 10 && w >= 0 && w < 10)
						{
							//std::cout << g << " " << w << std::endl;
							if (ship[i]->rx != -1)
							{
								if (id != ship[i]->id)
								{
									if (ship[i]->scell[j].rx == g && ship[i]->scell[j].ry == w)
									{
										//std::cout << i << " " << j << " P " << g << " " << w << std::endl;
										return false;
									}
									if (ship[i]->rx == g && ship[i]->ry == w)
									{
										return false;
									}
									//if(i == 0)std::cout << ship[i]->rx << " " << ship[0]->ry << " " << g << " " << w << std::endl;
								}
							}
						}
					}
				}
			}
		}
		return true;
	}

	void drawShip(sf::RenderWindow *window)
	{
		switch (this->direct)
		{
		case 0:
			for (int i = 0; i < type; i++)
			{
				if (i == 0)
				{
					scell[i].setImage("shipcornerf.png");
					scell[i].setPosition(x, y);
				}
				else if (i == 3)
				{
					scell[i].setImage("shipcornerb.png");
					scell[i].setPosition(x, y + i * 50);
				}
				else
				{
					scell[i].setImage("ship.png");
					scell[i].setPosition(x, y + i * 50);
				}
				window->draw(scell[i].sc);
			}
			break;
		case 1:
			for (int i = 0; i < type; i++)
			{
				if (i == 0)
				{
					scell[i].setImage("shipcornerl.png");
					scell[i].setPosition(x, y);
				}
				else if (i == 3)
				{
					scell[i].setImage("shipcornerr.png");
					scell[i].setPosition(x + i * 50, y);
				}
				else
				{
					scell[i].setImage("shipr.png");
					scell[i].setPosition(x + i * 50, y);
				}
				window->draw(scell[i].sc);
			}
			break;
		default:
			break;
		}
	}

};