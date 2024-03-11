#ifndef GUNS_H_INCLUDED
#define GUNS_H_INCLUDED


class Gun
{
protected:
    Texture texture;
    Sprite sprite;
    Texture outT;
    Sprite outS;
    int R;
    int max_b;
    int max_dist;
    float speed;
    Vector2f moveto,lastPosition;
    int speedto=0;
    /////////////
    SoundBuffer buffer;
    Sound sound;
    bool *gunf=new bool();
    bool reload=true;

public:
    int getSpt(){return speedto;}
    bool* Gunf(){return gunf;}
    Vector2f getSpeed(float&dT)
    {
        speedto=speedto>0?speedto-100*dT:0;
        return moveto*(float)speedto;
    }

    bool Reload(){reload=true; return reload;}
    virtual bool Auto()=0;
    virtual void shoot(List<Bullet>&,sf::Vector2f,sf::Vector2f, sf::Clock*)=0;
    virtual int shooter()=0;
    int getDist(void){return max_dist;}
    void setInHand()
    {
        sprite.setScale(3,3);
    }
    virtual void drawInHand(RenderWindow& window,float a,Vector2f b)
    {
        sprite.setPosition(b);
        sprite.setRotation(a);
        window.draw(sprite);
    }
    void draw(RenderWindow& window)
    {
        window.draw(outS);
    }
    void setPosition(float x,float y)
    {
        outS.setScale(3,3);
        outS.setOrigin(outT.getSize().x/2,outT.getSize().y/2);
        outS.setRotation(sprite.getRotation());
        outS.setPosition(x,y);
        lastPosition=outS.getPosition();
    }
    void setPosition(Vector2f a)
    {
        R=outT.getSize().x>outT.getSize().y?outT.getSize().y*outS.getScale().y:outT.getSize().x*outS.getScale().x;
        outS.setScale(3,3);

        outS.setOrigin(outT.getSize().x/2,outT.getSize().y/2);
        outS.setRotation(sprite.getRotation());
        outS.setPosition(a);
    }
    Vector2f getPosition(void){return outS.getPosition();}
    //Sprite getBody(){return outS;}

    void move(Vector2f a){outS.move(a); outS.setRotation(outS.getRotation()+rand()%5);}

    void fly(Vector2f to,Vector2f pos,float speedp,Vector2f&ToFly)
    {
        speedto=1800.f;
        moveto=(Vector2f(1.0f/(1/cos(atan2(to.y-pos.y, to.x-pos.x))),1.0f/(1/sin(atan2(to.y-pos.y, to.x-pos.x)))));
        if((moveto.x*ToFly.x>0)||(moveto.y*ToFly.y>0) ) speedto+=speedp;
        else speedto-=speedp;
        setPosition(pos);
    }

    void Colision(Map TileMap)
	{

        float y =outS.getPosition().y-R/2.;
        float x =outS.getPosition().x-R/2.;
        int i = y/(TileMap.TileSize.y);
        int j = x/(TileMap.TileSize.x);

        if(i<=0||j<=0) {speedto=0; return;}
        else if(j>=(TileMap.MapSize.x)||i>=(TileMap.MapSize.y)) {speedto=0; return;}
        for (; i < (y+R)/TileMap.TileSize.y; (i++))
			for (; j < (x+R)/TileMap.TileSize.x; (j++) )
				{
				if (TileMap[i][j] == 1)
				{
                    //outS.setPosition(lastPosition);
                    //speedto=0;
                    if((TileMap[i+1][j]==1)||(TileMap[i-1][j]==1)) moveto=Vector2f(moveto.x*(-1),moveto.y*(1));
                    else if((TileMap[i][j+1]==1)||(TileMap[i][j+1]==1)) moveto=Vector2f(moveto.x*(1),moveto.y*(-1));
                    speedto*=0.7;
                    return;
				}
            }
        lastPosition=outS.getPosition();
    }

};


#endif // GUNS_H_INCLUDED
