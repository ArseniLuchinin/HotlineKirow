#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include "interface.h"
#include "cUrsor.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class Interface
{
    protected:
    RenderWindow window;
    cUrsor cursor;

    public:
    Interface(VideoMode video, const string &title, Uint32 style, const ContextSettings &settings,cUrsor cr)
    {
        window.create(video,title, style, settings);
        cursor = cr;
    }
    void create(VideoMode video, const String &title, Uint32 style, const ContextSettings &settings)
    {
        window.create(video,title, style, settings);
        window.setMouseCursorVisible(false);
    }
    void mainMenu(Sprite&menuS,View&view);
    void zastavka(Sprite&menuS);
    bool GamerSet(View&view,sf::String&GamerName);
    void education(View&view);
    char levelSelect(View&view,sf::String&GamerName);
    char game(sf::String &filename,View&view,int itr,sf::String &GamerName);
    int Win(View&view, float time, int&itr, sf::String&levelname, sf::String&GamerName);
    char GameOver(string a,Vector2f b,int&zoom);
    char Escape(View&view,Image&ii,int&zoom);
    void readRecord(View&view);
    char writeRecord(View&view,string GamerName, string levelname,float&time, int&iter);
};

#endif // INTERFACE_H_INCLUDED
