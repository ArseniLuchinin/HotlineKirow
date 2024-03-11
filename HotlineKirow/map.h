#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

struct Map
{

    char**maps;
    Vector2i TileSize;
    Vector2i MapSize;
    char* operator[](int a) {return maps[a];}
};

#endif // MAP_H_INCLUDED
