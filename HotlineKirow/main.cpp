#define _CRT_SECURE_NO_WARNINGS
//#define setColor setFillColor

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>
#include <sstream>
#include <math.h>
#include <string.h>
#include "tinyxml2.h"
#include "tinyxml2.cpp"
using namespace tinyxml2;
using namespace sf;
using namespace std;
#define dlin 1080
#define shir 1920

#include "instruments.h"

#include "Text.h"

#include "list b.h"
#include "map.h"
#include "Bullet.h"
#include "guns.h"
#include "shootinggun.h"
#include "closecombatgun.h"


#include "vragi.h"
#include "unit.h"


#include "level.h"
#include "player.h"

#include "BulletWithEnemy.h"

#include "cUrsor.h"

#include "interface.h"
#include "inGmameMenu.h"
#include "menu.h"
#include "records.h"

#include "GameBody.h"


int main()
{
    setlocale(LC_ALL, "Russian");
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    cUrsor cr = cUrsor("kyrsor.png","Mcursor.png");
    Interface interface(VideoMode(shir/2,dlin/2),"luchinin",Style::None, settings,cr);
    //RenderWindow window;
    //window.create(VideoMode(shir/2,dlin/2),"luchinin",Style::None, settings);

        string levelname;
        Texture texM;
        Sprite menuS;
        getSprite("Menu.png",texM,menuS);

        View view;
        view.reset(sf::FloatRect(0, 0, shir, dlin));
        interface.zastavka(menuS);

        interface.create(VideoMode(shir,dlin),"luchinin",Style::None, settings);

        interface.mainMenu(menuS,view);
    return 0;
}
