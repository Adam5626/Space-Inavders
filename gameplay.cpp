#include <iostream>
#include <time.h>
#include <string>
#include <SFML/Graphics.hpp>
#include "Gameplay.h";
#include <stdlib.h>
#include <math.h>

using namespace std;
using namespace sf;

namespace Space
{
	void game()
	{
		RenderWindow play(VideoMode(1600, 900), "SPACE INVADERS", Style::Close | Style::Resize);

		play.setFramerateLimit(60);

		//Ground
		RectangleShape ground(Vector2f(1600, 20));
		ground.setFillColor(Color::Blue);
		ground.setPosition(0, 760);

		//Lose Condition
		int lives = 3;

		//Enemy Textures
		Texture monster;
		monster.loadFromFile("monster.png");
		Texture skull;
		skull.loadFromFile("skull.png");
		Texture oct;
		oct.loadFromFile("oct.png");
		int tex_type = 0;

		//Enemy Sprites
		Sprite enemy[5][11];

		//Setting enemy Textures
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				if (i == 0)
				{
					enemy[i][j].setTexture(oct);
				}
				if (i == 1 || i == 2)
				{
					enemy[i][j].setTexture(monster);
				}
				if (i == 3 || i == 4)
				{
					enemy[i][j].setTexture(skull);
				}

			}
		}


		int x = 400;
		int y = 100;
		int x2[5][11];
		int y2[5][11];

		//Setting Enemy Initial Position
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				
				enemy[i][j].setPosition(x, y);
				x = x + 70;
				x2[i][j] = x;
				y2[i][j] = y;
			}
			x = 400;
			y = y + 70;

		}
		
		//Enemy Boundaries
		 x = 400;
		 y = 100;

		RectangleShape enemy_boundary[5][11];
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				enemy_boundary[i][j].setSize(Vector2f(50, 50));
				enemy_boundary[i][j].setPosition(x, y);
				x = x + 70;
			}
			x = 400;
			y = y + 70;
		
		}


		//Ship Texture
		Texture ship;
		ship.loadFromFile("ship.png");

		//Ship Sprite
		Sprite myship;
		myship.setTexture(ship);

		Sprite lives_ship[3];
		int k = 790;
		int l = 30;
		for (int i = 0; i < 3; i++)
		{
			lives_ship[i].setTexture(ship);
			lives_ship[i].setPosition(l,k);
			l = l + 70;
			
		}

		RectangleShape ship_bounds(Vector2f(60, 60));

		//Setting Ship's Initial Position
		int x_ship = 50;
		int y_ship = 700;
		myship.setPosition(x_ship, y_ship);
		ship_bounds.setPosition(x_ship, y_ship);

		//Bullet Shape
		RectangleShape bullet(Vector2f(5, 30));

		//Bullet's Initial Position
		int x_bullet = 80;
		int y_bullet = 710;
		bullet.setPosition(x_bullet, y_bullet);
		
		//Clock
		Clock delay;
		float time_;
		Time t;

		Clock bullet_travel;
		float bullet_time;
		
		int invert = 0;
		int vert = 0;

		int shoot = 0;
		int reload = 0;

		float current_x;
		float current_y;
		float current_x_ship;
		float current_y_ship;

		float current_x_ship_bounds;
		float current_y_ship_bounds;

		//Destroy
		Texture destroy;
		destroy.loadFromFile("destroy.png");

		//Score Display
		Font myfont;
		string score_str;
		myfont.loadFromFile("8bit.ttf");
		Text score_txt;
		score_txt.setFont(myfont);
		score_txt.setPosition(50, 50);

		//Lives Display
		Text live;
		live.setFont(myfont);
		string lives_str="3";
		live.setPosition(50, 70);

		//Collision Bypass
		int check[5][11];
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				check[i][j] = 0;
			}
		}

		//Bolt Texture
		int bolt_flag = 0;
		 x = 400;
		 y = 100;

		RectangleShape bolt_enemy[5][11];

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				bolt_enemy[i][j].setSize(Vector2f(10, 50));
				bolt_enemy[i][j].setPosition(x, y);
				bolt_enemy[i][j].setFillColor(Color(255, 255, 255,0));
				x = x + 70;
			}

			x = 400;
			y = y + 70;

		}


		int bolt_check[5][11];
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				bolt_check[i][j] = 0;
			}

		}

		int bolt_x=0;
		int bolt_y=0;
		int row = 0;
		int col = 0;
		
		//Bolt Clock
		Clock bolt_delay;
		float bolt_time;
		int bolt_turn = 0;


		//Score Setting
		int score = 0;
		int score_val[5][11];

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 11; j++)
				{
					if (i == 0)
					{
						score_val[i][j] = 30;
					}
					if (i == 1 || i==2)
					{
						score_val[i][j] = 20;
					}
					if (i == 3 || i==4)
					{
						score_val[i][j] = 10;
					}

				}
			}

		while (play.isOpen())
		{
			Event click;
			while (play.pollEvent(click))
			{
				switch (click.type)
				{

				case Event::Closed:
				{
					play.close();
					break;
				}

				}
			}

			live.setString("Lives : " + lives_str);
			//Movement Of Enemies and Bolts

			time_ = delay.getElapsedTime().asMilliseconds();
			if (time_ >= 1000)

			{
				if (invert == 0)
				{
					if (vert == 1)
					{
						for (int k = 0; k < 5; k++)
						{
							for (int l = 0; l < 11; l++)
							{
								y2[k][l] = y2[k][l] + 10;
							}
						}
						vert = 0;
					}
					
						for (int i = 0; i < 5; i++)
						{

							for (int j = 0; j < 11; j++)
							{
								x2[i][j] = x2[i][j] + 5;

								enemy_boundary[i][j].setPosition(x2[i][j], y2[i][j]);
								if (bolt_check[i][j] == 0)
								{
									bolt_enemy[i][j].setPosition(x2[i][j], y2[i][j]);
								}
								enemy[i][j].setPosition(x2[i][j], y2[i][j]);

							}
						}		
				}

				if (x2[1][10] > 1500)
				{
					invert = 1;
					vert = 1;
					
				}
				
				if (invert == 1)
				{
					if (vert == 1)
					{
						for (int k = 0; k < 5; k++)
						{
							for (int l = 0; l < 11; l++)
							{
								y2[k][l] = y2[k][l] + 10;
							}
						}

						vert=0;
					}
					
					
					for (int i = 0; i < 5; i++)
					{

						for (int j = 0; j < 11; j++)
						{
							x2[i][j] = x2[i][j] - 5;

							enemy_boundary[i][j].setPosition(x2[i][j], y2[i][j]);
							if (bolt_check[i][j] == 0)
							{
								bolt_enemy[i][j].setPosition(x2[i][j], y2[i][j]);
							}
							enemy[i][j].setPosition(x2[i][j], y2[i][j]);
							
						}

					}

					if (x2[1][0] < 100)
					{
						invert = 0;
						vert = 1;
					}
					
					
				}

				time_ = 0;
				delay.restart();

			}

			//Movement Of Ship Using Keyboard
			if (Keyboard::isKeyPressed(Keyboard::Key::Right))
			{
				myship.move(5.0f, 0.0f);
				ship_bounds.move(5.0f, 0.0f);
				if (shoot == 0)
				{
					bullet.move(5.0f, 0.0f);
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Left))
			{
					myship.move(-5.0f, 0.0f);
					ship_bounds.move(-5.0f, 0.0f);
					if (shoot == 0)
					{
						bullet.move(-5.0f, 0.0f);
					}
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Space) && reload==0)
			{
				shoot = 1;
				reload = 1;
			
		    }

			//Getting Current Postion Of Bullet
			Vector2f position_bullet = bullet.getPosition();
			current_x = position_bullet.x;
			current_y = position_bullet.y;

			//Getting Current Postion Of Ship
			Vector2f position_ship = myship.getPosition();
			current_x_ship = position_ship.x;
			current_y_ship = position_ship.y;

			Vector2f position_ship_bounds = ship_bounds.getPosition();
			current_x_ship_bounds = position_ship_bounds.x;
			current_y_ship_bounds = position_ship_bounds.y;


			//Getting Current Position Of enemies
			Vector2f position_enemy[5][11];
			float current_x_enemy[5][11];
			float current_y_enemy[5][11];

			reload:
		
			if (shoot == 1)
			{
				bullet_time = bullet_travel.getElapsedTime().asMilliseconds();
				
					if (bullet_time > 500)
					{
						y_bullet = y_bullet - 50;
						bullet.setPosition(current_x , y_bullet);
						bullet_time = 0;
						bullet_travel.restart();

						if (y_bullet < 100)
						{
							reload = 0;
							shoot = 0;
							bullet.setPosition(current_x_ship+30, current_y_ship+5);
							y_bullet = current_y_ship + 5;
							x_bullet = current_x_ship + 30;

							goto reload;
						}

						for (int i = 0; i < 5; i++)
						{
							for (int j = 0; j < 11; j++)
							{
								position_enemy[i][j] = enemy_boundary[i][j].getPosition();
								current_x_enemy[i][j] = position_enemy[i][j].x;
								current_y_enemy[i][j] = position_enemy[i][j].y;

								if (current_x - current_x_enemy[i][j] <= 0 && current_y - current_y_enemy[i][j] <= 0 && check[i][j]==0)
								{
									
									enemy[i][j].setTexture(destroy);
									reload = 0;
									shoot = 0;
									bullet.setPosition(current_x_ship + 30, current_y_ship + 5);
									y_bullet = current_y_ship + 5;
									x_bullet = current_x_ship + 30;
									check[i][j] = 1;
									score = score + score_val[i][j];
									score_str = to_string(score);

									goto reload;
								}

	      					}
						}
					
					}			
			}

			if (bolt_flag == 0)
			{
				row = rand() % 4 + 0;
				col = rand() & 10 + 0;
				bolt_check[row][col] = 1;
				bolt_flag = 1;
			}
	
			//Getting Current Position Of bolt
			Vector2f position_bolt;
			float current_x_bolt;
			float current_y_bolt;
			position_bolt = bolt_enemy[row][col].getPosition();
			current_x_bolt = position_bolt.x;
			current_y_bolt = position_bolt.y;

			if (bolt_flag == 1)
			{
				bolt_time = bolt_delay.getElapsedTime().asMilliseconds();

				if (bolt_time > 100)
				{
					bolt_y = current_y_bolt;
					bolt_x = current_x_bolt;
					bolt_y = bolt_y + 20;
					bolt_enemy[row][col].setPosition(bolt_x, bolt_y);
					bolt_enemy[row][col].setFillColor(Color(255, 255, 255, 100));
					bolt_time = 0;
					bolt_delay.restart();

				}
				if (bolt_y > 750)
				{
					bolt_enemy[row][col].setFillColor(Color(255, 255, 255, 0));
					bolt_check[row][col] = 0;
					bolt_flag = 0;
				}

				if (bolt_x - current_x_ship_bounds ==5 && current_y_ship_bounds - bolt_y  <= 5 )
				{
					cout << lives << endl;
					bolt_enemy[row][col].setFillColor(Color(255, 255, 255, 0));
					bolt_check[row][col] = 0;
					bolt_flag = 0;
					lives--;
					lives_str = to_string(lives);

					
				}
			}
				
			//Displaying Score
			score_txt.setString("Score : " + score_str);

			for (int k = 0; k < 5; k++)
			{
				for (int l = 0; l < 11; l++)
				{
					play.draw(enemy[k][l]);
				}
			}
			for (int k = 0; k < 5; k++)
			{
				for (int l = 0; l < 11; l++)
				{
					play.draw(bolt_enemy[k][l]);
				}
			}

			for (int k = 0; k < 3; k++)
			{
				
					play.draw(lives_ship[k]);
				
			}

			play.draw(ground);
			play.draw(score_txt);
			play.draw(live);
			play.draw(bullet);
			play.draw(myship);
			play.display();
			play.clear();
		}
		

		

	}



}

