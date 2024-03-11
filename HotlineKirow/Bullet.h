#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

class Bullet
{
protected:
    sf::Vector2f Move, now_dist=sf::Vector2f(0.f,0.f);
    int max_dist;
    sf::RectangleShape bullet;
public:
    bool MapEvent(Map&TileMap)
	{
        int y =bullet.getPosition().y/(TileMap.TileSize.y);
        int x =(bullet.getPosition().x)/((TileMap.TileSize.x));
        if(x<=0||y<=0) return false;
        else if(x>=(TileMap.MapSize.x)||y>=(TileMap.MapSize.y)) return false;
        if (TileMap[y][x] == 1)	return false;


        return true;
}

    Bullet() {}
    Bullet(sf::Vector2f position, float a=5.f, float b=5.f,Color cl=Color::Black)
    {
        bullet.setSize(sf::Vector2f(a,b));
        bullet.setFillColor(cl);
        bullet.setPosition(position);
        bullet.setOrigin(a/2,b/2);
    }
    void setDist(int a) {max_dist=a;}

    void setMove(sf::Vector2f a) {Move=a;}

    void draw(RenderWindow& window){window.draw(bullet);}

    Vector2f getMove() {return Move;}

    void move(sf::Vector2f mv){bullet.move(mv);}

    void setRotation(float angle) {this->bullet.setRotation(angle);}

    bool Dist(sf::Vector2f a)
        {
            now_dist+=a;
            if(now_dist.x*now_dist.x+now_dist.y*now_dist.y>=(max_dist*max_dist) ) return false;
            return true;
        }
    Vector2f getPosition(){return bullet.getPosition();}
    FloatRect getGlobalBounds() {return bullet.getGlobalBounds();}
};


void draw_bullets(sf::RenderWindow &window, List <Bullet>&all, float &dT, Map&a)
{
    List<Bullet>::node *c=all.bg;
    while(c)
    {
        c->object.move(c->object.getMove()*dT);
        c->object.draw(window);
        if(c->object.Dist(c->object.getMove()*dT)&&(c->object.MapEvent(a))) c=c->post;
            else c=all.del(c);

    }
}

#endif // BULLET_H_INCLUDED
