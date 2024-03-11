#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "instruments.h"
#include <string.h>
using namespace sf;
using namespace std;
class cUrsor
{
protected:
    Sprite sprite, Msprite;
    Texture texture, Mtexture;
public:


//////////////////////////////////////////

    cUrsor(const string& filename,const string& Mfilename)
    {
        getSprite(filename,texture,sprite);
        getSprite(Mfilename,Mtexture,Msprite);
        sprite.setOrigin(texture.getSize().x/2,texture.getSize().y/ 2);

    }
    cUrsor(){}
    void update(RenderWindow &window, View&view)
    {
            sprite.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window),view));
    }
    void Menuupdate(RenderWindow &window, View&view)
    {
            Msprite.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window),view));
    }
    inline void draw(RenderWindow& window) {window.draw(sprite);}
    inline void drawMenu(RenderWindow& window) {window.draw(Msprite);}

    Vector2f getPosition(void) {return sprite.getPosition();}

    FloatRect getCenter(void){return FloatRect(Msprite.getPosition().x,Msprite.getPosition().y,3.,3.);}
};



#endif // CURSOR_H_INCLUDED
