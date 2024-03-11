#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
class Level
{
    protected:
    int hight, width, H, W;

    //char **mapOrigin;
    sf::Sprite sprite, mapSprite;
    sf::Texture texture, mapTexture;
    public:
    char **maps;
    Map mapp;

bool read_map(string filename, string imagename,List<enemy*>&all_enemy,List<Gun*>&guns,int h=32, int w=32)
    {
            H=h; W=w;
            mapp.TileSize=Vector2i(h,w);
            char mapname[20];
            filename+=".txt";
            FILE* file=fopen(filename.c_str(),"r");

            fscanf(file,"%d %d %s",&hight, &width, mapname);

            mapp.MapSize=Vector2i(hight,width);

            if(!mapTexture.loadFromFile(mapname)) return false;
            mapSprite.setTexture(mapTexture);
            maps=new char*[hight];
            for(int i=0;i<hight;i++)
            {
                maps[i]=new char[width];
                for(int j=0;j<width;j++)
                {
                    char iter[12];
                    fscanf(file,"%s",iter);
                    if( isdigit(iter[0]) ) maps[i][j]=atoi(iter);
                    else if(iter[0]=='T')
                    {

                        enemy *a= new tyrel("tyrel/",maps,j*32,i*32,95,70);

                                    maps[i][j] = 5;
                                    maps[i-1][j-1] = 5;
                                    maps[i][j-1] = 5;
                                    maps[i-1][j] = 5;
                        all_enemy.add(a);
                    }
                    else if(iter[0]=='P')
                    {
                        maps[i][j]='P';
                    }
                    else if(iter[0]=='U')
                    {enemy *u;
                        maps[i][j]=0;
                        if(!strcmp(iter+1,"_akm"))
                        {
                            u=new unit("unit/",maps,j*32,i*32,189,80);
                            u->setGun(new akm());
                        }

                        else if(!strcmp(iter+1,"_drb"))
                        {
                            u=new unit("unit/",maps,j*32,i*32,189,80);
                            u->setGun(new shotgun());
                        }
                        else if(!strcmp(iter+1,"_bkf"))
                        {
                            u=new unit("unit/",maps,j*32,i*32,189,80);
                            u->setGun(new bigknife());
                        }

                        all_enemy.add(u);
                    }
                    else if(!strcmp(iter,"akm"))
                    {
                        Gun *a=new akm();
                        a->setPosition(j*32,i*32);
                        maps[i][j]=0;
                        guns.add(a);
                    }
                    else if(!strcmp(iter,"drb"))
                    {
                        Gun *a=new shotgun();
                        maps[i][j]=0;
                        a->setPosition(j*32,i*32);
                        guns.add(a);
                    }


                }
            }
        mapp.maps=maps;


        texture.loadFromFile(imagename);
        texture.update(texture);
        //texture.setSmooth(true);
        sprite.setTexture(texture);
        fclose(file);
        return true;
    }
    int Hight() {return hight;}
    int Width() {return width;}


    void draw(sf::RenderWindow &window)
    {
        for(int i=0;i<hight;i++)
            for(int j=0;j<width;j++)
            {
                bool flag=1;
                switch(maps[i][j])
                {
                    case 0: sprite.setTextureRect(sf::IntRect(32*maps[i][j], 0,32, 32)); break;
                    case 1: sprite.setTextureRect(sf::IntRect(32*maps[i][j], 0,32, 32)); break;
                    case 2: sprite.setTextureRect(sf::IntRect(32*maps[i][j], 0,32, 32)); break;
                    case 3: sprite.setTextureRect(sf::IntRect(32*maps[i][j], 0,32, 32)); break;
                    case 5: sprite.setTextureRect(sf::IntRect(0, 0,32, 32)); break;
                }

                if(flag) {sprite.setPosition(j * 32.f, i * 32.f); window.draw(sprite);}
                else flag=1;

            }

    }
    void draw2(sf::RenderWindow &window)
    {
        window.draw(mapSprite);
    }
};







#endif // LEVEL_H_INCLUDED
