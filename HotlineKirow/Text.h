#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

class TEXTt
{
    protected:
    Text text;
    Font font;
    public:
    TEXTt(){}
    TEXTt( sf::String a,sf::String fontname, Color c=Color::Red, Vector2f p=Vector2f(0,0),int size=50)
    {

        if(!font.loadFromFile("Fonts/"+fontname)) return;
        text.setFont(font);
        text.setString(a);
        text.setCharacterSize(size);
        text.setFillColor(c);
        text.setPosition(p);
    }
    void setString(sf::String a)
    {
        text.setString(a);
    }
    Text& getText(){return text;}
    void setPosition(Vector2f f)
    {
        text.setPosition(f);
    }
    Vector2f getPosition()
    {
        return text.getPosition();
    }
    void setColor(Color c)
    {
        text.setFillColor(c);
    }
    void draw(RenderWindow& window) {text.setOrigin(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2);window.draw(text);}
    FloatRect getLocalBounds(void){return text.getGlobalBounds();}
};

#endif // TEXT_H_INCLUDED
