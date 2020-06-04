#include "maps.h"
#include "time.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

class PLAYER {

public:
  float dx, dy;
  FloatRect rect;
  Sprite sprite;
  float currentFrame;

  PLAYER(Texture &image) {
    sprite.setTexture(image);
    rect = FloatRect(50, 40, 29, 29);

    dx = dy = 0.1;
    currentFrame = 0;
  }

  void update(float time)
    {
            rect.left += dx * time;
	    Collision(0);
            rect.top += dy * time;
	    Collision(1);

    currentFrame += 0.005*time;
    if (currentFrame>3) currentFrame -=3;

    if (dy<0) sprite.setTextureRect(IntRect(2+32*int(currentFrame),4,29,29));
    if (dy>0) sprite.setTextureRect(IntRect(2+32*int(currentFrame),68,29,29));
    if (dx<0) sprite.setTextureRect(IntRect(2+32*int(currentFrame),36,29,29));
    if (dx>0) sprite.setTextureRect(IntRect(2+32*int(currentFrame),100,29,29));

    sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

            dx = 0;
            dy = 0;
    }

    void Collision(int dir)
    {

      for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
        for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
        {
          if (TileMap[i][j] == 'B')
          {
            if ((dx > 0) && (dir == 0))
              rect.left = j * 32 - rect.width;
            if ((dx < 0) && (dir == 0))
              rect.left = j * 32 + 32;
            if ((dy > 0) && (dir == 1))
            {
              rect.top = i * 32 - rect.height;
              dy = 0;
            }
            if ((dy < 0) && (dir == 1))
            {
              rect.top = i * 32 + 32;
              dy = 0;
            }
        }
       }
    }


};

void menu(RenderWindow & window) {

	Texture menuTexture1, menuTexture2;
	menuTexture1.loadFromFile("1.jpg");
	menuTexture2.loadFromFile("2.jpg");
	Sprite menu1(menuTexture1),menu2(menuTexture2);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(300, 300);
	menu2.setPosition(850, 450);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(300, 300, 377, 90).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(850, 450, 217, 80).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2)  { window.close(); isMenu = false; }
		}

		window.draw(menu1);
		window.draw(menu2);
		window.display();
	}
}

int main()
{
    RandomGeneration(7);
    RenderWindow window( VideoMode(600,600), "Test");
    menu(window);

    Font font;
    font.loadFromFile("CyrilicOld.TTF");
    Text text("", font, 20);
    text.setFillColor(Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    Clock clock;
    Clock gameTimeClock;

    Texture t;
    t.loadFromFile("hero.png");

    PLAYER p(t);

    while (window.isOpen())
    {
        int gameTime = 50, second;
        float time = clock.getElapsedTime().asMicroseconds();
        second = gameTimeClock.getElapsedTime().asSeconds();
        clock.restart();
        time = time / 500;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

    if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            p.dx = -0.1;
        }

    if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            p.dx = 0.1;
        }

    if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            p.dy = -0.1;

        }

    if (Keyboard::isKeyPressed(Keyboard::Down))
        {
             p.dy = 0.1;
        }

    p.update(time);

    offsetX = p.rect.left - 600/2;
    offsetY = p.rect.top - 600/2;

    window.clear();
    window.clear(Color::White);

    RectangleShape rectangle(Vector2f(32, 32));
    for (int i = 0; i < H; i++)
      for (int j = 0; j < W; j++) {
        if (TileMap[i][j] == 'B') //стена
          rectangle.setFillColor(Color::Black);
        if (TileMap[i][j] == 'Z') //монетка первого типа
          rectangle.setFillColor(Color::Yellow);
        if (TileMap[i][j] == 'X') //монетка второго типа
          rectangle.setFillColor(Color::Green);
        if (TileMap[i][j] == 'C') //монетка третьего типа
          rectangle.setFillColor(Color::Blue);
        if (TileMap[i][j] == ' ')
          continue;

        rectangle.setPosition(j * 32 - offsetX, i * 32 - offsetY);
        window.draw(rectangle);
      }
    std::ostringstream gameTimeString;
	gameTimeString << timer(gameTime, second);
	text.setString(L"Время игры: "+gameTimeString.str());
	text.setPosition(200, 200);

    window.draw(p.sprite);
    window.draw(text);
    window.display();
  }

  return 0;
}
