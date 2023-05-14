#include <SFML/Graphics.hpp>
#include <iostream>
class Pou
{
public:
	sf::Texture texture;
	sf::Sprite sprite;
	double deltaTime;
	Pou()
	{
		if (!texture.loadFromFile("pouTexture.png"))
		{
			std::cout << "Failed to load a pou texture" << std::endl;
		}
		sprite = sf::Sprite(texture);
		sprite.setScale(0.1f, 0.1f);		
		sprite.setPosition(250, 100);
		deltaTime = 0.003;
	}
};
