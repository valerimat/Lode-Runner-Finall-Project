#include <SFML/Graphics.hpp>


class Button
{
public:
	Button(std::shared_ptr<sf::Texture> texture, sf::Vector2f location);
	void Draw(sf::RenderWindow& window);
private:
	sf::Sprite m_sprite;
};