#include "saper.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics.hpp>

Board::Board() // konstruktor calej planszy
{
    for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			T[i][j].setting(i*40, j*40);
		}
	}
}

void Board::deploy_mines(int n, bool random) // metoda rozmieszczajaca miny na planszy
{
    srand(time(NULL));
    bool is_bomb = true;

    if (is_bomb && random)
    {
        while (is_bomb && n > 0)
        {
            for (int i = 0; i < M; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (!T[i][j].mine && n > 0 && rand() % 29 == 0) // ustawilem modulo 29,
                    {                                               // poniewaz jest to liczba pierwsza, nie za mala, nie za duza
                        T[i][j].place_mine();                       // i rozmiesci miny bardziej losowo na planszy
                        n--;
                    }
                }
            }
        }
    }
    else if (!random)
    {
        int j = 0;
        for (int i = 0; i < M; i++)
        {
            T[i][j].place_mine();
            j++;
        }
    }
}

bool Board::has_Mine(int x, int y) // metoda sprawdzajaca czy na zadanym polu znajduje sie mina
{
    if (T[x][y].mine)
    {
        return true;
    }
    return false;
}

int Board::count_mines(int x, int y) // metoda zliczajaca miny w poblizu odkrytego pola
{
    int near = 0;
    int edge_x = 0;
    int edge_y = 0;
    int edge_x_max = 3;
    int edge_y_max = 3;

    if (x == 0)
    {
        edge_x = 1;
    }
    if (y == 0)
    {
        edge_y = 1;
    }
    if (x == M - 1)
    {
        edge_x_max = 2;
    }
    if (y == N - 1)
    {
        edge_y_max = 2;
    }
    // stosuje oddzielne instrukcje warunkowe if, poniewaz warunki sa rozlaczne,
    // musza byc sprawdzane kazdorazowo

    for (int pomoc1 = edge_x; pomoc1 < edge_x_max; pomoc1++)
	{
		for (int pomoc2 = edge_y; pomoc2 < edge_y_max; pomoc2++)
		{
			if (has_Mine(x - 1 + pomoc1, y - 1 + pomoc2)) near++;
		}
	}
	return near;
}

void Board::reveal(int x, int y) // metoda odkrywajaca szereg pol na planszy
{
    T[x][y].uncover();

    if (!count_mines(x, y))
	{
		int x_min = 0;
		int y_min = 0;
		int x_max = 3;
		int y_max = 3;
		if (x == 0) // pierwsza krawedz x
		{
			x_min = 1;
		}
		if (y == 0) // pierwsza krawedz y
		{
			y_min = 1;
		}
		if (x == M - 1) // ostatnia krawedz x
		{
			x_max = 2;
		}
		if (y == N - 1) // ostatnia krawedz y
		{
			y_max = 2;
		}
		for (int i = x_min; i < x_max; i++)
		{
			for (int j = y_min; j < y_max; j++)
			{
				if (T[x - 1 + i][y - 1 + j].is_covered()) reveal(x - 1 + i, y - 1 + j); // rekurencyjnie wywolywana metoda reveal
			}                                                                           // gdy sa puste pola, kolega mi pomogl z tym
		}                                                                               // mialem z odkrywaniem pol ogromny problem
	}
}

void Board::modify_flag(int x, int y) // metoda wywolujaca metode klasy Field, ktora dynamicznie
{                                    // (w trakcie dzialania programu) ukrywa/zakrywa zadane pole przez uzytkownika
	T[x][y].change_flag();
}

bool Board::whether_hidden(int x, int y) // metoda wywolujaca metode klasy Field, ktora zwraca wartosc logiczna zakrycia/odkrycia pola
{
	return T[x][y].is_covered();
}

void Board::draw_area(sf::RenderWindow & win) // metoda rysujaca cala plansze
{
    sf::Text text;
    sf::Font font;
    font.loadFromFile("Font\arial.ttf");
    text.setFont(font);

    for (int i = 0; i < M; i++)
	{
	    win.draw(text);
		for (int j = 0; j < N; j++)
		{
			T[i][j].draw_square(win);
			win.draw(text);

            if (T[i][j].covered && T[i][j].flag) T[i][j].place_flag_c();
            else if (!T[i][j].covered && T[i][j].mine) T[i][j].mine_c();
            else if (T[i][j].covered && !T[i][j].flag) T[i][j].covered_c();
            else if (!T[i][j].covered && count_mines(i, j) == 0) T[i][j].uncovered_c();
            else if (!T[i][j].covered && count_mines(i, j) == 1)
            {
                win.draw(text);
                T[i][j].uncovered_c();
                text.setString("1");
                text.setCharacterSize(24);
                text.setPosition(41.43*i, 40.4*j);
                text.setColor(sf::Color::Blue);
                text.setStyle(sf::Text::Bold);
                win.draw(text);
            }
            else if (!T[i][j].covered && count_mines(i, j) == 2)
            {
                win.draw(text);
                T[i][j].uncovered_c();
                text.setString("2");
                text.setCharacterSize(24);
                text.setPosition(41.43*i, 40.4*j);
                text.setColor(sf::Color::Black);
                text.setStyle(sf::Text::Bold);
                win.draw(text);
            }
            else if (!T[i][j].covered && count_mines(i, j) == 3)
            {
                win.draw(text);
                T[i][j].uncovered_c();
                text.setString("3");
                text.setCharacterSize(24);
                text.setPosition(41.43*i, 40.4*j);
                text.setColor(sf::Color::Red);
                text.setStyle(sf::Text::Bold);
                win.draw(text);
            }
            else if (!T[i][j].covered && count_mines(i, j) == 4)
            {
                win.draw(text);
                T[i][j].uncovered_c();
                text.setString("4");
                text.setCharacterSize(24);
                text.setPosition(41.43*i, 40.4*j);
                text.setColor(sf::Color::Blue);
                text.setStyle(sf::Text::Bold);
                win.draw(text);
            }
            else if (!T[i][j].covered && count_mines(i, j) == 5)
            {
                win.draw(text);
                T[i][j].uncovered_c();
                text.setString("5");
                text.setCharacterSize(24);
                text.setPosition(41.43*i, 40.4*j);
                text.setColor(sf::Color::Magenta);
                text.setStyle(sf::Text::Bold);
                win.draw(text);
            }
            else if (!T[i][j].covered && count_mines(i, j) == 6)
            {
                win.draw(text);
                T[i][j].uncovered_c();
                text.setString("6");
                text.setCharacterSize(24);
                text.setPosition(41.43*i, 40.4*j);
                text.setColor(sf::Color::Magenta);
                text.setStyle(sf::Text::Bold);
                win.draw(text);
            }
            else if (!T[i][j].covered && count_mines(i, j) == 7)
            {
                win.draw(text);
                T[i][j].uncovered_c();
                text.setString("7");
                text.setCharacterSize(24);
                text.setPosition(41.43*i, 40.4*j);
                text.setColor(sf::Color::Magenta);
                text.setStyle(sf::Text::Bold);
                win.draw(text);
            }
            else if (!T[i][j].covered && count_mines(i, j) == 8)
            {
                win.draw(text);
                T[i][j].uncovered_c();
                text.setString("1");
                text.setCharacterSize(24);
                text.setPosition(41.43*i, 40.4*j);
                text.setColor(sf::Color::Black);
                text.setStyle(sf::Text::Bold);
                win.draw(text);
            }

        }
	}
}
