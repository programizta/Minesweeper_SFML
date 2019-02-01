#include "saper.h"
#include <SFML\Audio.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics.hpp>

int main()
{
    while (true)
    {
        Field button;
        Board b1;
        int column, line, mines = 0, hidden;
        sf::RenderWindow menu(sf::VideoMode(1152, 648), "Menu");
        sf::Texture texture;
        texture.loadFromFile("Pictures/menu_picture.jpg");
        sf::Sprite sprite(texture);
        menu.draw(sprite);
        button.draw_buttons(menu);
        button.draw_text(menu);
        menu.display();

        while (menu.isOpen())
        {
            while (menu.isOpen())
            {
                sf::Event event;

                while (menu.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        menu.close();
                        return 0;
                    }
                    if (event.type == sf::Event::MouseButtonPressed)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left && sf::Mouse::getPosition(menu).x <= 250 && sf::Mouse::getPosition(menu).x >= 50 && sf::Mouse::getPosition(menu).y <= 570 && sf::Mouse::getPosition(menu).y >= 470)
                        {
                            sf::Music play;
                            play.openFromFile("Music/Bulletproof (GAMPER & DADONI Remix).mp3");
                            play.play();
                            button.easy_pressed();
                            b1.deploy_mines(15, 1);
                            for (int i = 0; i < M; i++)
                            {
                                for (int j = 0; j < N; j++)
                                {
                                    if (b1.has_Mine(i, j)) mines++;
                                }
                            }
                            menu.clear();
                            menu.draw(sprite);
                            button.draw_buttons(menu);
                            button.draw_text(menu);
                            menu.display();
                        }
                        if (event.mouseButton.button == sf::Mouse::Left && sf::Mouse::getPosition(menu).x <= 670 && sf::Mouse::getPosition(menu).x >= 470 && sf::Mouse::getPosition(menu).y <= 570 && sf::Mouse::getPosition(menu).y >= 470)
                        {
                            button.medium_pressed();
                            b1.deploy_mines(30, 1);
                            for (int i = 0; i < M; i++)
                            {
                                for (int j = 0; j < N; j++)
                                {
                                    if (b1.has_Mine(i, j)) mines++;
                                }
                            }
                            menu.clear();
                            menu.draw(sprite);
                            button.draw_buttons(menu);
                            button.draw_text(menu);
                            menu.display();
                        }
                        if (event.mouseButton.button == sf::Mouse::Left && sf::Mouse::getPosition(menu).x <= 1102 && sf::Mouse::getPosition(menu).x >= 902 && sf::Mouse::getPosition(menu).y <= 570 && sf::Mouse::getPosition(menu).y >= 470)
                        {
                            button.hard_pressed();
                            b1.deploy_mines(50, 1);
                            for (int i = 0; i < M; i++)
                            {
                                for (int j = 0; j < N; j++)
                                {
                                    if (b1.has_Mine(i, j)) mines++;
                                }
                            }
                            menu.clear();
                            menu.draw(sprite);
                            button.draw_buttons(menu);
                            button.draw_text(menu);
                            menu.display();
                        }
                        if (event.mouseButton.button == sf::Mouse::Left && sf::Mouse::getPosition(menu).x <= 1102 && sf::Mouse::getPosition(menu).x >= 902 && sf::Mouse::getPosition(menu).y <= 400 && sf::Mouse::getPosition(menu).y >= 298)
                        {
                        menu.close();
                        menu.clear();
                        menu.draw(sprite);
                        button.draw_buttons(menu);
                        menu.display();

                        sf::RenderWindow game(sf::VideoMode(598, 598), "Rozgrywka");

                        while (game.isOpen())
                        {
                            sf::Event event;

                            while (game.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed) game.close();
                                if (event.type == sf::Event::MouseButtonPressed)
                                {
                                    if (event.mouseButton.button == sf::Mouse::Left)
                                    {
                                        hidden = 0;
                                        column = sf::Mouse::getPosition(game).x/40;
                                        line = sf::Mouse::getPosition(game).y/40;
                                        b1.reveal(column, line);

                                        for (int i = 0; i < M; i++) // obliczanie ilosci zakrytych pol
                                        {
                                            for (int j = 0; j < N; j++)
                                            {
                                                if (b1.whether_hidden(i, j)) hidden++;
                                            }
                                        }

                                        if (b1.has_Mine(column, line)) // jesli trafisz na bombe to przegrales
                                        {
                                            sf::Music defeat;
                                            defeat.openFromFile("Music/explosion.ogg");
                                            defeat.play();
                                            sf::RenderWindow game_over(sf::VideoMode(540, 360), "Przegrana!");
                                            sf::Texture texture;
                                            texture.loadFromFile("Pictures/bomb.jpg");
                                            sf::Sprite sprite(texture);

                                            while (game_over.isOpen())
                                            {
                                                game.clear();
                                                b1.draw_area(game);
                                                game.display();
                                                sf::Event event;

                                                while (game_over.pollEvent(event))
                                                {
                                                    if (event.type == sf::Event::Closed)
                                                    {
                                                        game_over.close();
                                                        game.close();
                                                    }
                                                }
                                                game_over.clear();
                                                game_over.draw(sprite);
                                                game_over.display();
                                            }
                                        }
                                        else if (mines == hidden) // w przeciwnym razie jesli jest tyle
                                        {                         // samo min co zakrytych pol to wygrales
                                            b1.draw_area(game);
                                            game.display();
                                            sf::Music win;
                                            win.openFromFile("Music/win.ogg");
                                            win.play();
                                            sf::RenderWindow victory(sf::VideoMode(540, 333), "Wygrana!");
                                            sf::Texture texture;
                                            texture.loadFromFile("Pictures/victory.jpg");
                                            sf::Sprite sprite(texture);

                                            while (victory.isOpen())
                                            {
                                                game.clear();
                                                b1.draw_area(game);
                                                game.display();
                                                sf::Event event;

                                                while (victory.pollEvent(event))
                                                {
                                                    if (event.type == sf::Event::Closed)
                                                    {
                                                        victory.close();
                                                        game.close();
                                                    }
                                                }
                                                victory.clear();
                                                victory.draw(sprite);
                                                victory.display();
                                            }
                                        }
                                    }

                                    if (event.mouseButton.button == sf::Mouse::Right)
                                    {
                                        column = sf::Mouse::getPosition(game).x/40;
                                        line = sf::Mouse::getPosition(game).y/40;
                                        b1.modify_flag(column, line);
                                    }
                                }
                            }
                            game.clear();
                            b1.draw_area(game);
                            game.display();
                        }
                    }
                    }
                }
            }
        }
    }
    return 0;
}
