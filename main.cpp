#include <iostream>
#include <SFML/Graphics.hpp>
#include "gameplay.h";

using namespace std;
using namespace sf;



int main()
{
	RenderWindow space_invaders(VideoMode(1600, 900), "Space Invaders", Style::Close | Style::Resize);


	//Local Variables
	int click = 0;

	//Loading Fonts
	Font my_font;
	my_font.loadFromFile("8bit.ttf");

	//Space Invaders
	Text text;
	text.setFont(my_font);
	text.setString("SPACE INVADERS");
	text.setCharacterSize(100);
	text.setPosition(500, 100);

	//Play Button
	Text play;
	play.setFont(my_font);
	play.setString("CLICK HERE TO PLAY !");
	play.setCharacterSize(100);
	play.setPosition(420, 200);

	RectangleShape play_button(Vector2f(800, 90));
	play_button.setPosition(420, 210);
	
	//Mouse Position
	Vector2i mousepos;

	//Cursor
	Cursor point;
	point.loadFromSystem(Cursor::Hand);

	Cursor normal;
	normal.loadFromSystem(Cursor::Arrow);
	
	while (space_invaders.isOpen())
	{
		Event mouse;
		while (space_invaders.pollEvent(mouse))
		{
			switch (mouse.type)
			{

			   case Event::Closed:
				{
				space_invaders.close();
				break;
				}
				
			   case Event::MouseButtonPressed :
			   {
				   click = 1;
			   }


			}

			mousepos = Mouse::getPosition(space_invaders);


			if (play_button.getGlobalBounds().contains(static_cast <Vector2f>(mousepos)))
			{
				
				space_invaders.setMouseCursor(point);
				play.setFillColor(Color::Green);
				if (click == 1)
				{
					click = 0;
					space_invaders.close();
					Space::game();
					break;
				}
				
			}
			if (!play_button.getGlobalBounds().contains(static_cast<Vector2f>(mousepos)))
			{
				play.setFillColor(Color::White);
				space_invaders.setMouseCursor(normal);
			}
		}

		space_invaders.draw(text);
		space_invaders.draw(play);
		
		space_invaders.display();
		space_invaders.clear();

	}



	return 0;

}