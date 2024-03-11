#ifndef VRAGI_H_INCLUDED
#define VRAGI_H_INCLUDED

class enemy
{
    protected:
    string directoru;
    float rotate;
    int ShootDist;

    float RotateSpeed, RotateMoveTime;
    bool see=false;
    int W, H, R;
    Vector2f lastPosition;
    int max_dist;
    char**TileMap;
    bool *gunf=new bool(false), osharashen=false;;
    Vector2i *posInSprite;
    Vector2i *posBoard;
    Sprite sprite;
    Texture texture;
    int psf;
    float oshT;


    Gun *gun;

    Clock RotateTime;
    Clock osharshenTime;
    Clock* sT=new Clock;
public:
bool osh()
    {
        if(osharashen)
            if(osharshenTime.getElapsedTime().asSeconds()>oshT)
            {
                osharashen=false;
                spritePosition(2);
            }

    return osharashen;
    }
void spritePosition(int a)
{
    psf=a;
    sprite.setTextureRect(IntRect(posInSprite[psf].x, posInSprite[psf].y, posBoard[psf].x, posBoard[psf].y));
    W=posBoard[psf].x;
    H=posBoard[psf].y;
    R=W>H?H:W;

    sprite.setOrigin(posBoard[psf].x/2-1,posBoard[psf].y/2-1);
}
void lostGun(List<Gun*>&guns)
{
    if(*gunf)
    {
        gun->setPosition(sprite.getPosition().x,sprite.getPosition().y);
        guns.add(gun);
    }
}

void getDead(List<Sprite>&deads)
{

    spritePosition(0);
    deads.add(sprite);
}
void draw(RenderWindow& window)
    {
        window.draw(sprite);
        if(*gunf) {gun->drawInHand(window,rotate,sprite.getPosition());}
    }

virtual void shoot(List <Bullet>&, sf::Vector2f&,sf::Vector2f& )=0;
virtual void update(Vector2f,List<Bullet>&,Vector2f,float&)=0;
virtual void setGun(Gun*)=0;
virtual void Osharashen()=0;




    Vector2f getPosition(void){return sprite.getPosition();}

    void Rotate(float a)
    {
        if(RotateTime.getElapsedTime().asSeconds()>RotateMoveTime)
        {
            if(rotate>0.&&a<0)
                {
                    if( ((180+a)+(180-rotate))<180) {rotate+=RotateSpeed; if(rotate>180.) rotate=-180+(180.-rotate);}
                    else {rotate-=RotateSpeed; if(rotate<-180.) rotate=180-(180.+rotate);}
                }

            else if(rotate<0&&a>0)
            {
                if(((180+rotate)+(180-a))<180) {rotate-=RotateSpeed; if(rotate<-180.) rotate=180-(180.+rotate);}
                else {rotate+=RotateSpeed; if(rotate>180.) rotate=-180+(180.-rotate);}

            }

            else if(a>=rotate) rotate+=RotateSpeed;
            else rotate-=RotateSpeed;
            RotateTime.restart();
            sprite.setRotation(rotate);
        }
    }

    bool CheckRule(float& x, float& y)
    {
    int x1=sprite.getPosition().x/32, y1=sprite.getPosition().y/32, x2=x/32, y2=y/32;
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;

    while(x1 != x2 || y1 != y2)
   {
        switch(TileMap[y1][x1])
        {
            case 1: return false;
        }
        int error2 = error * 2;
        if(error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
    return true;

}
//Sprite getSprite(void){return sprite;}
FloatRect getGlobalBounds() {return sprite.getGlobalBounds();}
};

class tyrel: public enemy
{
protected:
    float ShootSpeed;
    SoundBuffer buffer;
    Sound sound;
public:
    void Osharashen(){}
    void setGun(Gun*){}

    tyrel(const string& filename,char**&a, float x=0,float y=0, float sizx=100,float sizy=100 )
    {
        posInSprite=new Vector2i[2];
        posBoard=new Vector2i[2];

        TileMap=a;
        RotateTime.restart();
        RotateSpeed=1.5;
        RotateMoveTime=0.01;
        directoru=filename;


        posInSprite[0]=Vector2i(0,0);
        posBoard[0]=Vector2i(95,69);
        posInSprite[1]=Vector2i(0,70);
        posBoard[1]=Vector2i(95,70);

        gun=nullptr;
        gunf=new bool(false);
        getSprite(filename+"tyrel.png",texture,sprite);

        spritePosition(1);
        sprite.setOrigin(posBoard[1].x/2,posBoard[1].y/2);

        sprite.setTexture(texture);

        sprite.setPosition(x,y);

//        X=x;
        //Y=y;
        lastPosition=sprite.getPosition();
        max_dist=1000;
        ShootDist=2000;
        ShootSpeed=3000;
        sT->restart();

        rotate=0;


        buffer.loadFromFile("guns/akms.wav");
        sound.setBuffer(buffer);

    }
    void update(Vector2f Game_pos,List <Bullet>&all,sf::Vector2f from,float&dT)
    {
        float second=Game_pos.y-sprite.getPosition().y, first=Game_pos.x-sprite.getPosition().x,
        rot=atan2(second, first) *180/3.14159265, rst_to=first*first+second*second;
        if(rst_to<=(max_dist*max_dist ))
        if(CheckRule(Game_pos.x, Game_pos.y))
        {
            if(rotate>(rot+3)||rotate<(rot-3))Rotate(rot);
            else if(rst_to<=ShootDist*ShootDist) shoot(all,from,Game_pos);

        }

    }

    void shoot(List <Bullet>&all, sf::Vector2f&pos,sf::Vector2f &to)
    {
        if(sT->getElapsedTime().asSeconds()>0.1f)
        {
            sound.play();
            float ran=-3+rand()%6;
            ran=ran/180*3.14;

            Bullet bullet=Bullet(pos,13);
            bullet.setDist(ShootDist);
            bullet.setRotation(atan2(to.y-pos.y, to.x-pos.x)*180/3.14159265+ran);
            bullet.setMove(sf::Vector2f(1.0f/(1/cos(atan2(to.y-pos.y, to.x-pos.x)+ran)),1.0f/(1/sin(atan2(to.y-pos.y, to.x-pos.x)+ran))));
            bullet.setMove(bullet.getMove()*ShootSpeed);
            all.add(bullet);
            sT->restart().asSeconds();
        }
    }
};

#endif // VRAGI_H_INCLUDED
