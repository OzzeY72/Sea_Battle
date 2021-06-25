#include "Game.h"


void draw(sf::RectangleShape *sh, sf::RenderWindow *window,Ship *ship[10],int *lock,sf::Text *text,Game *game)
{
	sh->setSize(sf::Vector2f(49, 49));
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			
			sh->setPosition(sf::Vector2f(50 + i * 50, 50 + j * 50));
			sh->setFillColor(sf::Color::Blue);
			window->draw(*sh);
			if (game->m_missed[i][j] == "v")
			{
				sh->setPosition(sf::Vector2f(50 + i * 50, 50 + j * 50));
				sh->setFillColor(sf::Color::Yellow);
				window->draw(*sh);
			}
			if (game->m_missed[i][j] == "r")
			{
				sh->setPosition(sf::Vector2f(50 + i * 50, 50 + j * 50));
				sh->setFillColor(sf::Color::Red);
				window->draw(*sh);
			}
			//for enemy
			sh->setPosition(sf::Vector2f(650 + i * 50, 50 + j * 50));
			sh->setFillColor(sf::Color::Blue);
			window->draw(*sh);
			if (game->e_missed[i][j] == "v")
			{
				sh->setPosition(sf::Vector2f(650 + i * 50, 50 + j * 50));
				sh->setFillColor(sf::Color::Yellow);
				window->draw(*sh);
			}
			if (game->e_missed[i][j] == "r")
			{
				sh->setPosition(sf::Vector2f(650 + i * 50, 50 + j * 50));
				sh->setFillColor(sf::Color::White);
				window->draw(*sh);
				game->crt.loadFromFile("cr.png");
				game->cr.setTexture(&game->crt);

				game->cr.setPosition(i * 50 + 650, j * 50 + 50);
				window->draw(game->cr);
				//cout << "Drawed at" << i * 50 + 650 << " " << j * 50 + 50 << endl;
			}/*
			if (game->m_missed[i][j] == "r")
			{
				game->crt.loadFromFile("cr.png");
				game->cr.setTexture(&game->crt);

				game->cr.setPosition(i * 50 + 50, j * 50 + 50);
				window->draw(game->cr);
				//cout << "Drawed at" << i * 50 + 50 << " " << j * 50 + 50 << endl;
			}*/
		}
	}
	for (int i = 0; i < 10; i++)
	{
		ship[i]->drawShip(window);
		text->setString(to_string(i));
		text->setPosition(i*50 + 63,13);
		window->draw(*text);

		text->setString(to_string(i));
		text->setPosition(i * 50 + 663, 13);
		window->draw(*text);
	}
	for (int i = 0; i < 10; i++)
	{
		string str = "ABCDEFGHKL";
		text->setString(str[i]);
		text->setPosition(13, i * 50 + 63);
		window->draw(*text);

		text->setString(str[i]);
		text->setPosition(613, i * 50 + 63);
		window->draw(*text);
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < ship[i]->type; j++)
		{
			if (!ship[i]->scell[j].live)
			{
				game->crt.loadFromFile("cr.png");
				game->cr.setTexture(&game->crt);
				game->cr.setPosition(ship[i]->scell[j].x, ship[i]->scell[j].y);
				window->draw(game->cr);

			}
			if (!ship[i]->live)
			{
				game->crt.loadFromFile("cr.png");
				game->cr.setTexture(&game->crt);
				game->cr.setPosition(ship[i]->scell[j].x, ship[i]->scell[j].y);
				window->draw(game->cr);
			}
		}
	}
	
}

void initConnection(Game *game,Ship ship[10])
{
	
}

bool isDead(Ship *ship)
{
	for (int j = 0; j < ship->type; j++)
	{
		if (ship->scell[j].live) return false;
	}
	return true;
}

void setVE(int x,int y,Game *game,Ship *ship[10])
{
	int rx = (x - 650) / 50;
	int ry = (y - 50) / 50;

	if (rx >= 0 && rx < 10 && ry >= 0 && ry < 10)
	{

		game->e_missed[rx][ry] = "v";

		for (int i = 0; i < 10; i++)
		{
			//int c = 0;
			//if (ship[i]->live) 
			{
				if (ship[i]->type == 1)
				{
					if (ship[i]->rx == rx && ship[i]->ry == ry)
					{
						ship[i]->live = false;
						game->e_missed[rx][ry] = "r";
					}
				}
				for (int j = 0; j < ship[i]->type; j++)
				{
					if (ship[i]->scell[j].rx == rx && ship[i]->scell[j].ry == ry)
					{
						ship[i]->scell[j].live = false;
						game->e_missed[rx][ry] = "r";
						//if (ship[i]->scell[j].live == false) c++;
					}
				}
				//if (c == ship[i]->type) ship[i]->live = false;
				if (isDead(ship[i]))
				{
					ship[i]->live = false;
				}
				if (!ship[i]->live)
				{
					//cout << "Pomer" << endl;
					for (int j = 0; j < ship[i]->type; j++)
					{
						for (int h = ship[i]->scell[j].rx - 1; h < ship[i]->scell[j].rx + 2; h++)
						{
							for (int w = ship[i]->scell[j].ry - 1; w < ship[i]->scell[j].ry + 2; w++)
							{
								if (h >= 0 && h < 10 && w >= 0 && w < 10)
								//if(h != rx && w != ry)
								{
										if (ship[i]->rx != h || ship[i]->ry != w) 
										{
												//game->e_missed[h][w] = "v";
										}
										//for (int l = 0; l < ship[i]->type; l++)
										{
											//if (ship[i]->scell[j].rx != h || ship[i]->scell[j].ry != w) 
											if (game->e_missed[h][w] != "r")
											{
												game->e_missed[h][w] = "v";
											}
										}
								}
							}
						}
						if (ship[i]->type == 1)
						{
							for (int h = ship[i]->rx - 1; h < ship[i]->rx + 2; h++)
							{
								for (int w = ship[i]->ry - 1; w < ship[i]->ry + 2; w++)
								{
									if (h >= 0 && h < 10 && w >= 0 && w < 10)
										//if(h != rx && w != ry)
									{
										if (ship[i]->rx != h || ship[i]->ry != w)
										{
											game->e_missed[h][w] = "v";
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void setV(int x, int y, Game *game, Ship *ship[10])
{
	int rx = (x - 600) / 50;
	rx -= 1;
	int ry = (y - 50) / 50;

	if (rx >= 0 && rx < 10 && ry >= 0 && ry < 10)
	{

		game->m_missed[rx][ry] = "v";

		for (int i = 0; i < 10; i++)
		{
			//int c = 0;
			//if (ship[i]->live) 
			{
				if (ship[i]->type == 1)
				{
					if (ship[i]->rx == rx && ship[i]->ry == ry)
					{
						ship[i]->live = false;
						game->m_missed[rx][ry] = "r";
					}
				}
				for (int j = 0; j < ship[i]->type; j++)
				{
					if (ship[i]->scell[j].rx == rx && ship[i]->scell[j].ry == ry)
					{
						ship[i]->scell[j].live = false;
						game->m_missed[rx][ry] = "r";
						//if (ship[i]->scell[j].live == false) c++;
					}
				}
				//if (c == ship[i]->type) ship[i]->live = false;
				if (isDead(ship[i]))
				{
					ship[i]->live = false;
				}
				if (!ship[i]->live)
				{
					//cout << "Pomer" << endl;
					for (int j = 0; j < ship[i]->type; j++)
					{
						for (int h = ship[i]->scell[j].rx - 1; h < ship[i]->scell[j].rx + 2; h++)
						{
							for (int w = ship[i]->scell[j].ry - 1; w < ship[i]->scell[j].ry + 2; w++)
							{
								if (h >= 0 && h < 10 && w >= 0 && w < 10)
									//if(h != rx && w != ry)
								{
									if (ship[i]->rx != h || ship[i]->ry != w)
									{
										//game->m_missed[h][w] = "v";
									}
									//for (int l = 0; l < ship[i]->type; l++)
									{
										//if (ship[i]->scell[j].rx != h || ship[i]->scell[j].ry != w) 
										if (game->m_missed[h][w] != "r")
										{
											game->m_missed[h][w] = "v";
										}
									}
								}
							}
						}
						if (ship[i]->type == 1)
						{
							for (int h = ship[i]->rx - 1; h < ship[i]->rx + 2; h++)
							{
								for (int w = ship[i]->ry - 1; w < ship[i]->ry + 2; w++)
								{
									if (h >= 0 && h < 10 && w >= 0 && w < 10)
										//if(h != rx && w != ry)
									{
										if (ship[i]->rx != h || ship[i]->ry != w)
										{
											game->m_missed[h][w] = "v";
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void InitArray(Game *game)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			game->m_missed[i][j] = "n";
			game->e_missed[i][j] = "n";
		}
	}

}

void Sync(Ship *ship[10])
{
	for (int i = 0; i < 10; i++)
	{
		if ((ship[i]->x - 50) / 50 >= 0 && (ship[i]->x - 50) / 50 <= 10 && (ship[i]->y - 50) / 50 >= 0 && (ship[i]->y - 50) / 50 <= 10)
		{
			ship[i]->rx = (ship[i]->x - 50) / 50;
			ship[i]->ry = (ship[i]->y - 50) / 50;
			//cout << "Synced";
			int tp = ship[i]->type -1;
			if (tp != 0) if ((ship[i]->scell[tp].x - 50) / 50 >= 0 && (ship[i]->scell[tp].x - 50) / 50 <= 10 && (ship[i]->scell[tp].y - 50) / 50 >= 0 && (ship[i]->scell[tp].y - 50) / 50 <= 10)
			{
				for (int j = 0; j < ship[i]->type; j++)
				{
					ship[i]->scell[j].rx = (ship[i]->scell[j].x - 50) / 50;
					ship[i]->scell[j].ry = (ship[i]->scell[j].y - 50) / 50;
				}
			}
		}
	}
}

sf::Socket::Status sendCell(int x,int y,Game *game)
{
	sf::Packet pack;
	bool turn;
	turn = game->turn;
	pack << x << y << turn;
	return game->socket.send(pack);
}

sf::Vector2i receiveCell(Game *game)
{
	sf::Packet pack;
	bool turn;
	game->stat = game->socket.receive(pack);
	sf::Vector2i temp;
	pack >> temp.x >> temp.y >> turn;
	game->turn = turn;
	//game->turn = true;
	return temp;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 600), "Seawar");
	Game game;
	Ship *ship[10];
	sf::Text text;
	text.setCharacterSize(25);
	sf::Font font;
	font.loadFromFile("arial.ttf");
	text.setFont(font);

	game.cr.setSize(sf::Vector2f(50, 50));
	InitArray(&game);

	game.cir.setPosition(0,0);
	game.cir.setRadius(25.f);
	game.cir.setFillColor(sf::Color::Green);
	ship[0] = new Ship(100,550,Ship::FORWARD,1,true);

	for (int i = 1; i < 10; i++)
	{
		int t = 0;
		if (i < 4) t = 1;
		if (i >= 4 && i < 7) t = 2;
		if (i >= 7 && i < 9) t = 3;
		if (i == 9) t = 4;

		ship[i] = new Ship(150 + 50*i, 550, Ship::LEFT,t,true);
	}
	
	string ip;
	short port;
	char cs;
	//cout << "Enter ip:" << endl;
	//cin >> ip;
	//cout << endl << "Enter port" << endl;
	//cin >> port;
	ip = "46.175.250.105";
	port = 27015;
	cout << endl << "s or c" << endl;
	cin >> cs;
	//sf::TcpSocket socket;

	if (cs == 'c')
	{
		window.setTitle("Client");
		game.turn = false;
		sf::Packet pack;
		game.socket.connect(ip, port);
		/*Ship shp[10];
		socket.receive(pack);
		for (int i = 0; i < 10; i++)
		{
			pack >> shp[i].rx >> shp[i].ry >> shp[i].type >> shp[i].id;
			for (int j = 0; j < shp[i].type; j++)
			{
				pack >> shp[i].scell[j].rx >> shp[i].scell[j].ry;
			}
			cout << " " << shp[i].rx << " " << shp[i].ry << " " << shp[i].type << " " << shp[i].id;
		}
		game.setShip(shp);*/
		/*
		for (int i = 0; i < 10; i++)
		{
			//pack << ship[i]->rx << ship[i]->ry << ship[i]->type << ship[i]->id << ship[i]->direct;
			for (int j = 0; j < ship[i]->type; j++)
			{
				//pack << ship[i]->scell[j].rx << ship[i]->scell[j].ry;
			}
		}*/
		//socket.send(pack);

	}
	if (cs == 's')
	{
		window.setTitle("Server");
		game.turn = true;
		sf::Packet pack;
		game.listener.listen(port) != sf::Socket::Done;
		game.listener.accept(game.socket);/*
		for (int i = 0; i < 10; i++)
		{
			pack << ship[i]->rx << ship[i]->ry << ship[i]->type << ship[i]->id;
			for (int j = 0; j < ship[i]->type; j++)
			{
				pack << ship[i]->scell[j].rx << ship[i]->scell[j].ry;
			}
		}
		socket.send(pack);*/
	}


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized)
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//if (game.lock != 0) { game.lock = 0; }
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			if (!game.type)
			{
				int h = 0;
				while (h < 10)
				{
					for (int i = 0; i < ship[h]->type; i++)
					{
						if (ship[h]->scell[i].sc.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
						{
							game.lock = h + 1;
							ship[h]->id = h;
						}
					}
					h++;
				}
			}
			else
			{
				//setVE(pos.x, pos.y, &game, ship);
				if (game.turn) 
				{/*
					sf::Socket::Status status = sendCell(pos.x, pos.y, &game);
					if(status == sf::Socket::Status::Done)
					{
						//game.turn = false;
						setVE(pos.x, pos.y, &game, game.eship);
					}
					if (status == sf::Socket::Done) {
						std::cout << "Sent " << " bytes.\n";
					}
					else if (status == sf::Socket::Error) {
						std::cout << "Error\n";
					}
					else if (status == sf::Socket::Disconnected) {
						std::cout << "Disconnected\n";
					}
					else if (status == sf::Socket::NotReady) {
						std::cout << "NotReady\n";
					}
					*/
					//cout << "PRESSED" << endl;
					if (pos.x >= 0 && pos.y >= 0)
					{
						setVE(pos.x, pos.y, &game, game.eship);
						game.tx = pos.x;
						game.ty = pos.y;
						cout << pos.x << " DA " << pos.y;
					}
				}
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			//Sync(ship);
			if (game.lock != 0) {
				Sync(ship);
				int x = (ship[game.lock - 1]->x / 50) -1;
				int y = (ship[game.lock - 1]->y / 50) -1;
				if (ship[game.lock - 1]->isGoodPosition(x, y,ship))
				{
					ship[game.lock - 1]->x = x*50 + 50;
					ship[game.lock - 1]->y = y*50 + 50;
					game.lock = 0;
					Sync(ship);
				}else game.cir.setFillColor(sf::Color::Red);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			if (game.lock != 0)
			{
				if (ship[game.lock - 1]->direct == Ship::LEFT) ship[game.lock - 1]->direct = Ship::FORWARD;
				else ship[game.lock - 1]->direct = Ship::LEFT;
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			//game.setShip(*ship);
			game.type = true;
			//initConnection(&game,*ship);
			if (cs == 'c')
			{
				sf::Packet pack;
				//socket.connect(ip, port);
				Ship shp[10];
				game.socket.receive(pack);
				for (int i = 0; i < 10; i++)
				{
					pack >> shp[i].rx >> shp[i].ry >> shp[i].type >> shp[i].id >> shp[i].live;
					int temp;
					pack >> temp;
					if (temp == 1) shp[i].direct = Ship::LEFT;
					if (temp == 0) shp[i].direct = Ship::FORWARD;

					for (int j = 0; j < shp[i].type; j++)
					{
						pack >> shp[i].scell[j].rx >> shp[i].scell[j].ry >> shp[i].scell[j].live;
					}
					cout << " " << shp[i].rx << " " << shp[i].ry << " " << shp[i].type << " " << shp[i].id << endl;
				}
				game.setShip(shp);
				pack.clear();
				for (int i = 0; i < 10; i++)
				{
					pack << ship[i]->rx << ship[i]->ry << ship[i]->type << ship[i]->id << ship[i]->live;
					int temp;
					if (ship[i]->direct == Ship::LEFT) temp = 1;
					if (ship[i]->direct == Ship::FORWARD) temp = 0;
					pack << temp;
					for (int j = 0; j < ship[i]->type; j++)
					{
						pack << ship[i]->scell[j].rx << ship[i]->scell[j].ry << ship[i]->scell[j].live;
					}
					cout << " " << ship[i]->rx << " " << ship[i]->ry << " " << ship[i]->type << " " << ship[i]->id << endl;
				}
				game.socket.send(pack);
				//sendCell(1,1,&game);
			}
			else
			{
				sf::Packet pack;
				for (int i = 0; i < 10; i++)
				{
					pack << ship[i]->rx << ship[i]->ry << ship[i]->type << ship[i]->id << ship[i]->live;
					int temp;
					if (ship[i]->direct == Ship::LEFT) temp = 1;
					if (ship[i]->direct == Ship::FORWARD) temp = 0;
					pack << temp;
					for (int j = 0; j < ship[i]->type; j++)
					{
						pack << ship[i]->scell[j].rx << ship[i]->scell[j].ry << ship[i]->scell[j].live;
					}
					cout << " " << ship[i]->rx << " " << ship[i]->ry << " " << ship[i]->type << " " << ship[i]->id << endl;
				}
				game.socket.send(pack);
				//#$^@#&%
				pack.clear();
				Ship shp[10];
				game.socket.receive(pack);
				for (int i = 0; i < 10; i++)
				{
					pack >> shp[i].rx >> shp[i].ry >> shp[i].type >> shp[i].id >> shp[i].live;
					int temp;
					pack >> temp;
					if (temp == 1) shp[i].direct = Ship::LEFT;
					if (temp == 0) shp[i].direct = Ship::FORWARD;

					for (int j = 0; j < shp[i].type; j++)
					{
						pack >> shp[i].scell[j].rx >> shp[i].scell[j].ry >> shp[i].scell[j].live;
					}
					cout << " " << shp[i].rx << " " << shp[i].ry << " " << shp[i].type << " " << shp[i].id << endl;
				}
				//game.setShip(shp);
				//sf::Vector2i temp = receiveCell(&game);
				//cout << temp.x << temp.y << endl;
			}

		}
			if (game.lock != 0)
			{
				sf::Vector2i pos = sf::Mouse::getPosition(window);
				ship[game.lock - 1]->x = pos.x;
				ship[game.lock - 1]->y = pos.y;

			}
			else 
			{
				if (!game.type) game.cir.setFillColor(sf::Color::Green);
			}
			if(game.turn) game.cir.setFillColor(sf::Color::Blue);
			if(!game.turn) game.cir.setFillColor(sf::Color::Red);

		if (game.type)
		{
			//sf::Vector2i temp; //temp = receiveCell(&game);
			//setV(temp.x, temp.y, &game, game.eship);
			//cout << "We receive" << endl;
			if (cs == 'c')
			{
				game.posn = receiveCell(&game);
				if (game.posn.x != 0 && game.posn.y != 0)
				{
					if (game.m_missed[game.posn.x][game.posn.y] != "v")
					{
						//setV(game.posn.x, game.posn.y, &game, ship);
					}
				}
				if (game.tx < 0) game.tx = 0;
				if (game.ty < 0) game.ty = 0;
				if (game.tx > 2000) game.tx = 0;
				if (game.ty > 2000) game.ty = 0;
				//cout <<  game.ty << endl;
				cout << game.tx << " ETO " << game.ty;
				sf::Socket::Status status = sendCell(game.tx,game.ty,&game);
				if (status == sf::Socket::Status::Done)
				{
					//if(game.turn && game.tx != 0) game.turn = false;
					game.tx = 0;
					game.ty = 0;
				}/*
				if (game.stat == sf::Socket::Status::Done)
				{
					game.turn = true;
					game.stat = sf::Socket::Status::Error;
				}*/
			}
			//PROBLEMA V SERVEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
			if (cs == 's')
			{
				if (game.tx < 0) game.tx = 0;
				if (game.ty < 0) game.ty = 0;
				if (game.tx > 2000) game.tx = 0;
				if (game.ty > 2000) game.ty = 0;
				sf::Socket::Status status = sendCell(game.tx, game.ty, &game);
				if (status == sf::Socket::Status::Done)
				{
					//if (game.turn && game.tx != 0) game.turn = false;
					game.tx = 0;
					game.ty = 0;
				}
				game.posn = receiveCell(&game);
				//cout << game.posn.x << " " << game.posn.y;
				//cout << game.posn.y << endl;
				if (game.posn.x != 0 && game.posn.y != 0)
				{
					if (game.m_missed[game.posn.x][game.posn.y] != "v")
					{
						//setV(game.posn.x, game.posn.y, &game, ship);
					}
				}
				/*
				if (game.stat == sf::Socket::Status::Done) 
				{
					//game.turn = true;
					game.stat = sf::Socket::Status::Error;
				}*/
			}
			//receiveCell(&game);
			/*
			if (game.m_missed[game.posn.x][game.posn.y] != "v")
			{
				setV(game.posn.x,game.posn.y,&game,ship);
				//game.turn = true;
			}*/
		}

		window.clear();

		draw(&game.shape, &window,ship,&game.lock,&text,&game);
		//cout << ship[0]->scell[0].x << "  " << ship[0]->scell[0].y << endl;
		//cout << ship[1]->scell[0].x << "  " << ship[1]->scell[0].y << endl;
		//cout << game.lock << endl;
		//cout << sf::Mouse::getPosition(window).x << "  " << sf::Mouse::getPosition(window).y << endl;
		//cout << ship[0]->rx << " " << ship[0]->ry << endl;
		window.draw(game.cir);

		window.display();
	}

	return 0;
}
