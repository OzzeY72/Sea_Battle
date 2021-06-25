#pragma once
//#ifndef Game_HEADER
//#define Game_HEADER

#include <iostream>
#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include <iterator>
#include "ShipCell.h"
#include "Ship.h"
#include <SFML/Network.hpp>
#include <thread>

using namespace ::std;

class Game
{
public:
	//Ship *bufship;
	bool type = false;
	int lock = 0;
	bool turn = false;

	int tx = 0;
	int ty = 0;

	string m_missed[10][10];
	string e_missed[10][10];

	Ship *eship[10];
	Ship ship[10];

	sf::RectangleShape cr;
	sf::Texture crt;

	sf::TcpSocket socket;
	sf::TcpListener listener;
	sf::Socket::Status stat;

	sf::Vector2i posn = {0,0};

	sf::RectangleShape shape;
	sf::CircleShape cir;
	/*

	*/
	void setShip(Ship ship[10])
	{
		for (int i = 0; i < 10; i++)
		{
			this->ship[i] = ship[i];
			eship[i] = &this->ship[i];
		}
		
	}
};

//#endif