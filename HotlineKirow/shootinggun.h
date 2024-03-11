#ifndef SHOOTINGGUN_H_INCLUDED
#define SHOOTINGGUN_H_INCLUDED

class akm: public Gun
{
public:
    akm()
    {
        max_b=30;
        speed=4000.f;
        max_dist=3000;
        getSprite("guns/akm.png",texture,sprite);
        getSprite("guns/outakm.png",outT,outS);
        sprite.setOrigin(0,1);
        gunf=new bool(true);

        buffer.loadFromFile("guns/akms.wav");
        sound.setBuffer(buffer);
    }
    bool Auto(){return true;}
    void shoot(List <Bullet>&all, sf::Vector2f pos,sf::Vector2f to, sf::Clock* sT)
    {
        if(!max_b) return;
        if(sT->getElapsedTime().asSeconds()>0.1f)
        {
            max_b-=1;
            float ran=(-30+rand()%60)/10.f;
            ran=ran/180*3.14;

            Bullet bullet=Bullet(pos,11,4);
            bullet.setDist(max_dist);
            bullet.setRotation(atan2(to.y-pos.y, to.x-pos.x)*180/3.14159265+ran);
            bullet.setMove(sf::Vector2f(1.0f/(1/cos(atan2(to.y-pos.y, to.x-pos.x)+ran)),1.0f/(1/sin(atan2(to.y-pos.y, to.x-pos.x)+ran))));
            bullet.setMove(bullet.getMove()*speed);
            all.add(bullet);
            sound.play();
            sT->restart().asSeconds();
        }
    }
    int shooter(){return 3;}
};

class shotgun: public Gun
{
private:
public:
    int shooter(){return 3;}
    shotgun()
    {
        max_b=6;
        speed=2000.f;
        max_dist=2000;
        getSprite("guns/drb.png",texture,sprite);
        getSprite("guns/outdrb.png",outT,outS);
        gunf=new bool(true);
        sprite.setOrigin(0,0);

        buffer.loadFromFile("guns/drbs.ogg");
        sound.setBuffer(buffer);
    }
    bool Auto(){return 0;}
    void shoot(List <Bullet>&all, sf::Vector2f pos,sf::Vector2f to, sf::Clock* sT)
    {
        if(!max_b) return;
        if(reload&&sT->getElapsedTime().asSeconds()>0.7f)
        {
            reload=false;
            max_b-=1;
            sound.play();
            for(int i=0; i<5; i++)
            {
                float ran=(-50+rand()%100)/10.;
                ran=ran/180*3.14;
                Bullet bullet=Bullet(pos);
                bullet.setDist(max_dist);
                bullet.setRotation(atan2(to.y-pos.y, to.x-pos.x)*180/3.14159265+ran);
                bullet.setMove(sf::Vector2f(1.0f/(1/cos(atan2(to.y-pos.y, to.x-pos.x)+ran)),1.0f/(1/sin(atan2(to.y-pos.y, to.x-pos.x)+ran))));
                bullet.setMove(bullet.getMove()*speed);
                all.add(bullet);
                sT->restart().asSeconds();
            }
        }

    }
};


#endif // SHOOTINGGUN_H_INCLUDED
