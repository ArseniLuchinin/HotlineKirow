#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class player
{
protected:
    bool life=true;
    int W, H,R;
    Sprite sprite;
    Texture texture;
    Vector2f lastPosition;
    Vector2f to;

    Vector2i *posInSprite;
    Vector2i *posBoard;
    int psf;

    float speed=500;
    bool *gunf;
    char**TileMap;

////////////////////////////////////////////////////////////////////////
public:
    Gun *gun;
    bool Gunf(){return *gunf;}
    char**& TileMaps(){return TileMap;}

    player(){};
    player(const string& filename,Level &maps, float x=0,float y=0)
    {
        posInSprite=new Vector2i[2];
        posBoard=new Vector2i[2];

        getSprite(filename,texture,sprite);

        posInSprite[0]=Vector2i(0,0);
        posBoard[0]=Vector2i(14,24);
        posInSprite[1]=Vector2i(0,24);
        posBoard[1]=Vector2i(25,16);



        TileMap=maps.maps;

        for(int i=0;i<maps.Hight();i++)
            for(int j=0;j<maps.Width();j++)
                if(TileMap[i][j]=='P') {sprite.setPosition(Vector2f(j*32, i*32)); TileMap[i][j]=0; break;}

        setGun(new none());
        lastPosition=sprite.getPosition();
    }
    Vector2f getPosition(void) {return sprite.getPosition();}

    void update(bool flmw,bool flms,bool flma,bool flmd, float dT,Vector2f mouse_pos)
    {
    if(!life) return;
    to=Vector2f(0,0);
    lastPosition=sprite.getPosition();
    sprite.setRotation(atan2(mouse_pos.y-sprite.getPosition().y, mouse_pos.x-sprite.getPosition().x) *180/3.14159265);
    if(flmw) {sprite.move(0,-1.0f*dT*speed);if(!Colision()) to.y+=-1;}
    if(flms) {sprite.move(0,1.0f*dT*speed);if(!Colision()) to.y+=1;}

    if(flma)
        {
            sprite.move(-1.0f*dT*speed,0);
            if(!Colision())
            {
                if(flmw) {sprite.move(0,-1.0f*dT*speed); if(!Colision()) to.y+=-1;}
                else if(flms) {sprite.move(0,1.0f*dT*speed);if(!Colision()) to.y+=1;}
                to.x+=-1;
            }
        }
    if(flmd)
        {
            sprite.move(1.0f*dT*speed,0);
            if(!Colision())
            {
                if(flmw) {sprite.move(0,-1.0f*dT*speed);if(!Colision()) to.y+=-1;}
                else if(flms) {sprite.move(0,1.0f*dT*speed);if(!Colision()) to.y+=1;}
                to.x+=1;
            }
        }



    }
    void draw(RenderWindow& window)
    {
        window.draw(sprite);
        if(*gunf) gun->drawInHand(window,sprite.getRotation(),sprite.getPosition());
    }
    void setGun(Gun*new_gun) {
        gun=new_gun;gun->setInHand();
        gunf=gun->Gunf();
        spritePosition(gun->shooter()-2);
        }

    Sprite& getBody(void){return sprite;}
    bool Colision()
	{
        float y =sprite.getPosition().y-R/2.;
        float x =sprite.getPosition().x-R/2.;
        for (int i = y/ 32; i < (y+R)/ 32; (i++))
			for (int j = x/ 32; j < (x+R)/ 32; (j++) )
				{
				if (TileMap[i][j] == 1||TileMap[i][j] == 5)
				{
                    sprite.setPosition(lastPosition);
                    return false;
				}
            }
        return true;

    }
void lostGun(List<Gun*>&guns,Vector2f a)
    {
        gun->fly(a,getPosition(),speed,to);
        guns.add(gun);
        setGun(new none());
    }
void setPosition(Vector2f a) {sprite.setPosition(a);}

void dead(){life=false;}
bool Life(){return life;}

void spritePosition(int a)
{
    psf=a;
    sprite.setTextureRect(IntRect(posInSprite[psf].x, posInSprite[psf].y, posBoard[psf].x, posBoard[psf].y));
    W=posBoard[psf].x;
    H=posBoard[psf].y;
    R=W>H?H:W;

    sprite.setOrigin(posBoard[psf].x/2-1,posBoard[psf].y/2-1);
    sprite.setScale(3,3);
}
};

#endif // PLAYER_H_INCLUDED
