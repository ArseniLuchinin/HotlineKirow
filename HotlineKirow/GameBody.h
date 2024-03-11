#ifndef GAMEBODY_H_INCLUDED
#define GAMEBODY_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS

char Interface::game(sf::String &filename,View&view,int itr,sf::String&GamerName)
{
    itr++;
    Clock gameTime;
    gameTime.restart();
    //return Win(window,cursor,view,gameTime.getElapsedTime().asSeconds(),itr,filename);
    List <Bullet>all_bullets;
    List <Bullet>player_bullets;
    List <Bullet>NoDeadBullet;
    List <Sprite>deads;
    List<enemy*>all_enemy;
    List<Gun*>free_gun;
    Level level;

    Texture fonT;
    Sprite fonS;
    fonT.loadFromFile("FON.png");
    fonT.update(fonT);
    fonS.setTexture(fonT);
    fonS.setOrigin(fonT.getSize().x/2,fonT.getSize().y/2);
    fonS.setPosition(shir/2,dlin/2);
    fonS.setScale(3,3);
    if(!level.read_map(filename,"map.png",all_enemy,free_gun)) return 1;
    player gamer= player("heroForRotate.png",level,shir/2, dlin/2);

        bool flmd=0, flmw=0,flms=0,flma=0,flL=0, flS=1;
    int zoom=1;
    view.reset(sf::FloatRect(0, 0, shir*zoom, dlin*zoom));

    Clock* clock = new Clock, *shootT=new Clock;
    shootT->restart();
    float dT;

    while (window.isOpen())
    {
    dT = clock->restart().asSeconds();
    Event event;
        while (window.pollEvent(event))
        {

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::A) flma=1;
            if (event.key.code == sf::Keyboard::D) flmd=1;
            if (event.key.code == sf::Keyboard::W) flmw=1;
            if (event.key.code == sf::Keyboard::S) flms=1;
        }

        if (event.type == Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::A) flma=0;
            if (event.key.code == sf::Keyboard::D) flmd=0;
            if (event.key.code == sf::Keyboard::W) flmw=0;
            if (event.key.code == sf::Keyboard::S) flms=0;
            if (event.key.code == sf::Keyboard::Escape)
            {
                char rtr;
                sf::Image ii;
                //window.capture();
                if((rtr=Escape(view,ii,zoom))!=1)
                    {

                        free(all_bullets);
                        free(player_bullets);
                        free(all_enemy);
                        free(deads);
                        return rtr;
                    }
                dT=0; clock->restart().asSeconds();
            }
        }


        if (event.type == sf::Event::Closed) window.close();


        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left) flL=1;
        }
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left) flL=0;
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                if(gamer.Gunf()) gamer.lostGun(free_gun,cursor.getPosition());
                else if(!free_gun.pyst())checkFreeGun(free_gun,gamer);
            }
        }
        }



    if(gamer.Life())
    {
        switch(flL)
        {
        case 1:
            if(flS) {if(gamer.Gunf())
                        gamer.gun->shoot(player_bullets,gamer.getPosition(),cursor.getPosition(),shootT);
                    else gamer.gun->shoot(NoDeadBullet,gamer.getPosition(),cursor.getPosition(),shootT);
                    flS=gamer.gun->Auto();}
                    break;
        case 0: flS=gamer.gun->Reload(); break;
        }
        gamer.update(flmw,flms,flma,flmd,dT,cursor.getPosition());
        enemyUpdate(all_enemy,gamer.getPosition(),all_bullets,dT);
    }


    view.setCenter(gamer.getPosition());
    cursor.update(window,view);

    if(!player_bullets.pyst())checkBulletWitchEnemy(player_bullets,all_enemy,deads,free_gun);
    if(!NoDeadBullet.pyst()) checkNoDeadGun(NoDeadBullet,all_enemy,free_gun);

    window.setView(view);

    //window.clear(Color(250, 220, 220, 0));
    window.draw(fonS);

    level.draw2(window);

    if(!all_bullets.pyst()) draw_bullets(window, all_bullets, dT, level.mapp);
    if(!player_bullets.pyst()) draw_bullets(window, player_bullets, dT, level.mapp);
    if(!NoDeadBullet.pyst()) draw_bullets(window, NoDeadBullet, dT, level.mapp);
    if(!all_bullets.pyst()) (checkBulletWitchGamer(all_bullets,gamer));
    if(!deads.pyst()) drawDeads(window,deads);
    if(!free_gun.pyst()) {drawFreeGun(window,free_gun,dT,level.mapp);}

    gamer.draw(window);
    if(!all_enemy.pyst()) enemyDraw(window,all_enemy);
    else return Win(view,gameTime.getElapsedTime().asSeconds(),itr,filename,GamerName);

    if(!gamer.Life())
        {
            free(all_bullets);
            free(player_bullets);
            free(all_enemy);
            free(deads);
            return GameOver("LOH.png",view.getCenter(),zoom);
        }
    cursor.draw(window);
    window.display();

    }

}


#endif // GAMEBODY_H_INCLUDED
