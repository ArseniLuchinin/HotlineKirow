#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED

class unit: public enemy
{
    Vector2f goTo,To;
    Clock *seeTime=new Clock();
    float moveSpeed;
    bool stop=true;

    SoundBuffer bufferO;
    Sound soundO;

    public:
    unit(const string& filename,char**&a, float x=0,float y=0, float sizx=100,float sizy=100)
    {
        posInSprite=new Vector2i[4];
        posBoard=new Vector2i[4];

        TileMap=a;

        RotateTime.restart();
        seeTime->restart();
        rotate=0;
        RotateSpeed=6;
        RotateMoveTime=0.01;
        moveSpeed=500;

        directoru=filename;

        getSprite(directoru+"unit.png",texture,sprite);
        posInSprite[0]=Vector2i(0,0);
        posBoard[0]=Vector2i(58,20);
        posInSprite[1]=Vector2i(0,20);
        posBoard[1]=Vector2i(28,22);
        posInSprite[2]=Vector2i(0,42);
        posBoard[2]=Vector2i(14,24);
        posInSprite[3]=Vector2i(0,66);
        posBoard[3]=Vector2i(25,16);

        sprite.setPosition(x,y);
        //X=x;Y=y;
        lastPosition=sprite.getPosition();
        To=Vector2f(0,0);
        goTo=lastPosition;

        max_dist=500;
        sT->restart();


        oshT=3.;

        gun=NULL;

        bufferO.loadFromFile("unit/osh.ogg");
        soundO.setBuffer(bufferO);
    }

    void setGun(Gun*a)
    {
        gunf=a->Gunf();
        //gunf=new bool(true);
        gun=a;ShootDist=a->getDist();
        gun->setInHand();

        spritePosition(gun->shooter());

        sprite.setScale(3,3);


    }

void Osharashen()
    {
        soundO.play();
        setGun(new none());
        osharashen=true;
        osharshenTime.restart();
        spritePosition(1);
    }



    void shoot(List <Bullet>&all, sf::Vector2f&pos,sf::Vector2f &to)
    {
        gun->Reload();
        gun->shoot(all,pos,to,sT);
    }

    void update(Vector2f Game_pos,List <Bullet>&all,sf::Vector2f from,float&dT)
    {
        float second=Game_pos.y-sprite.getPosition().y, first=Game_pos.x-sprite.getPosition().x,
        rot=atan2(second, first) *180/3.14159265, rst_to=first*first+second*second;
        int mD=ShootDist;
        if(rst_to<=(max_dist*max_dist))
        {
            if(CheckRule(Game_pos.x, Game_pos.y))
            {
                if(rotate>(rot+3)||rotate<(rot-3)) {Rotate(rot);seeTime->restart();}
                else if(rst_to<=mD*mD) {if(see&&seeTime->getElapsedTime().asSeconds()>0.1f){shoot(all,from,Game_pos);see=true; to(Game_pos);}
                                        else see=true;to(Game_pos);}
                else {see=true; to(Game_pos); go(dT);}
            }
            else if(see) {to(goTo); go(dT);}
        }
        else if(see) {to(goTo); go(dT);}
    }
    void to(Vector2f& to)
    {
        Vector2f pos=sprite.getPosition();
        To=(Vector2f(1.0f/(1/cos(atan2(to.y-pos.y, to.x-pos.x))),1.0f/(1/sin(atan2(to.y-pos.y, to.x-pos.x)))));
        goTo=to;

    }
    void go(float&dT)
    {
        int x=goTo.x,y=goTo.y;
        lastPosition=sprite.getPosition();
        sprite.move(To.x*moveSpeed*dT,0);
        Colision();
        sprite.move(0,To.y*moveSpeed*dT);
        if(!Colision())
        {
            sprite.move(To.x*moveSpeed*dT,0);
            Colision();
        }
        int X=sprite.getPosition().x, Y=sprite.getPosition().y;

        if((X/64==x/64)>0&&(Y/64==y/64)>0) {see=false;}


    }
    bool Colision()
	{
        float y =sprite.getPosition().y-R/2.;
        float x =sprite.getPosition().x-R/2.;
        for (int i = y/ 32; i < (y+R)/ 32; i++)
			for (int j = x/ 32; j < (x+R)/ 32; j++)
				{
				if (TileMap[i][j] == 1||TileMap[i][j] == 5)
				{
                    sprite.setPosition(lastPosition);
                    return false;
				}
            }
        return true;
    }
};


void enemyUpdate(List<enemy*>&all_enemy,Vector2f GP,List <Bullet>&all,float&dT)
{
    List<enemy*>::node *c=all_enemy.bg;
    while(c)
    {
    if(!c->object->osh())c->object->update(GP,all,c->object->getPosition(),dT);
    c=c->post;
    }
}
void enemyDraw(sf::RenderWindow &window,List<enemy*>&all_enemy)
{
    List<enemy*>::node *c=all_enemy.bg;
    while(c)
    {
        c->object->draw(window);
        c=c->post;
    }
}


#endif // UNIT_H_INCLUDED
