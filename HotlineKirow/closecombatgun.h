#ifndef CLOSECOMBATGUN_H_INCLUDED
#define CLOSECOMBATGUN_H_INCLUDED

class none: public Gun
{
public:
    int shooter(){return 2;}
    bool Auto(){return 0;}
    none()
    {
        max_b=1;
        max_dist=40;
        speed=1000.f;

        gunf=new bool(false);

        buffer.loadFromFile("guns/nons.ogg");
        sound.setBuffer(buffer);
    }
    void shoot(List<Bullet>&all,sf::Vector2f pos,sf::Vector2f to,sf::Clock* sT)
    {
        if(sT->getElapsedTime().asSeconds()>0.2f)
        {
            //float ran=-3+rand()%6;
            //ran=ran/180*3.14;
            sound.play();
            Bullet bullet=Bullet(pos,max_dist,30.f,Color(0,0,0,0));
            bullet.setDist(max_dist);
            bullet.setRotation(atan2(to.y-pos.y, to.x-pos.x)*180/3.14159265);
            bullet.setMove(sf::Vector2f(1.0f/(1/cos(atan2(to.y-pos.y, to.x-pos.x))),1.0f/(1/sin(atan2(to.y-pos.y, to.x-pos.x)))));
            bullet.setMove(bullet.getMove()*speed);
            all.add(bullet);
            sT->restart().asSeconds();
        }
    }
};

class bigknife: public Gun
{
public:
    int shooter(){return 2;}
    bool Auto(){return 0;}
    bigknife()
    {
        max_b=1;
        max_dist=60;
        speed=1100.f;
        getSprite("guns/bkf.png",texture,sprite);
        getSprite("guns/outbkf.png",outT,outS);
        sprite.setOrigin(0,-7);
        gunf=new bool(true);
        buffer.loadFromFile("guns/bkfs.ogg");
        sound.setBuffer(buffer);
    }
    void shoot(List<Bullet>&all,sf::Vector2f pos,sf::Vector2f to,sf::Clock* sT)
    {
        if(sT->getElapsedTime().asSeconds()>0.15f)
        {
            sound.play();
            Bullet bullet=Bullet(pos,max_dist,30.f,Color(0,0,0,0));
            bullet.setDist(max_dist);
            bullet.setRotation(atan2(to.y-pos.y, to.x-pos.x)*180/3.14159265);
            bullet.setMove(sf::Vector2f(1.0f/(1/cos(atan2(to.y-pos.y, to.x-pos.x))),1.0f/(1/sin(atan2(to.y-pos.y, to.x-pos.x)))));
            bullet.setMove(bullet.getMove()*speed);
            all.add(bullet);
            sT->restart().asSeconds();
        }
    }
    void drawInHand(RenderWindow& window,float a,Vector2f b)
    {
        sprite.setPosition(b.x,b.y);
        sprite.setRotation(a);
        window.draw(sprite);
    }
};


void drawFreeGun(RenderWindow& window, List<Gun*>&guns,float&dT,Map&TileMap)
{
    List<Gun*>::node* c=guns.bg;
    while(c)
    {
        if(c->object->getSpt())
        {
            c->object->move(c->object->getSpeed(dT)*dT);
            c->object->Colision(TileMap);
        }

        c->object->draw(window);
        c=c->post;
    }
}

#endif // CLOSECOMBATGUN_H_INCLUDED
