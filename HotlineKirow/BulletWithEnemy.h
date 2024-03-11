#ifndef BULLETWITHENEMY_H_INCLUDED
#define BULLETWITHENEMY_H_INCLUDED

void checkBulletWitchEnemy(List <Bullet>&allBullet,List<enemy*>&allEnemy,List<Sprite>&deads,List<Gun*>&guns)
{
    List<enemy*>::node *en=allEnemy.bg;
    while(en)
    {
        List<Bullet>::node *bl=allBullet.bg;
        FloatRect En=en->object->getGlobalBounds();
        while(bl)
        {
            if(En.intersects(bl->object.getGlobalBounds()))
            {
                en->object->lostGun(guns);
                en->object->getDead(deads);
                allBullet.del(bl);
                allEnemy.del(en);
                break;
            }
            bl=bl->post;
        }
        en=en->post;
    }
}

void checkNoDeadGun(List<Bullet>&allBullet,List<enemy*>&allEnemy,List<Gun*>&guns)
{
    List<enemy*>::node *en=allEnemy.bg;
    while(en)
    {
        List<Bullet>::node *bl=allBullet.bg;
        FloatRect En=en->object->getGlobalBounds();
        while(bl)
        {
            if(En.intersects(bl->object.getGlobalBounds()))
            {
                if(!en->object->osh())
                {
                    en->object->lostGun(guns);
                    en->object->Osharashen();
                }
                break;
            }
            bl=bl->post;
        }
        en=en->post;
    }
}

void checkBulletWitchGamer(List <Bullet>&allBullet,player&a)
{
        List<Bullet>::node *bl=allBullet.bg;
        Sprite En=a.getBody();
        while(bl)
        {
            if(En.getGlobalBounds().intersects(bl->object.getGlobalBounds()))
            {
                allBullet.del(bl);
                a.dead();
            }
            bl=bl->post;
        }
}


void drawDeads(sf::RenderWindow &window, List<Sprite>&all)
{
    List<Sprite>::node*c=all.bg;
    while(c)
    {
        Sprite a=c->object;
        window.draw(a);
        c=c->post;
    }
}
template <class listT>
void free(List<listT>&all)
{
    while(!all.pyst())
    {
        all.delH();
    }

}

bool CheckRuleWithGun(float x, float y,Sprite&sprite,char**&TileMap)
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
float distTo(Vector2f a,Vector2f b)
{
    float dx=(a.x-b.x)*(a.x-b.x);
    float dy=(a.y-b.y)*(a.y-b.y);
    return dx+dy;
}


void checkFreeGun(List<Gun*>&guns,player&a)
{
    List<Gun*>::node* c=guns.bg;
    Sprite En=a.getBody();
    while(c)
    {
        if(distTo(En.getPosition(),c->object->getPosition())<=70.*70.)
            if(CheckRuleWithGun(c->object->getPosition().x,c->object->getPosition().y,En,a.TileMaps()))
                {
                if(a.Gunf())
                {
                    a.gun->setPosition(a.getPosition().x,a.getPosition().y);
                    guns.add(a.gun);
                }
                    a.setGun(c->object);
                    guns.del(c);
                    break;
                }
        c=c->post;
    }
}


#endif // BULLETWITHENEMY_H_INCLUDED
