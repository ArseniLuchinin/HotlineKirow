#ifndef INGMAMEMENU_H_INCLUDED
#define INGMAMEMENU_H_INCLUDED

char Interface::Escape(View&view,Image&ii,int&zoom)
    {
        //window.setKeyRepeatEnabled(false);//должно рабоать без него
        Texture texture;
        Sprite sprite;
        texture.loadFromImage(ii);
        texture.update(ii);
        //texture.setSmooth(true);
        sprite.setTexture(texture);

        sprite.setScale(
            (shir*zoom)/ sprite.getLocalBounds().width,
            (dlin*zoom) / sprite.getLocalBounds().height);

        TEXTt t1=TEXTt(L"Продолжить","ofont.ru_Unutterable.ttf",Color::Red,view.getCenter(),50);
        TEXTt t2=TEXTt(L"Начаь заново","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(t1.getPosition().x,t1.getPosition().y+t1.getLocalBounds().height+10),50);
        TEXTt t3=TEXTt(L"Выйти","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(t1.getPosition().x,t2.getPosition().y+t2.getLocalBounds().height+10),50);
        sprite.setPosition(view.getCenter().x-(shir*zoom)/2,view.getCenter().y-(dlin*zoom)/2);
        while(window.isOpen())
        {Event event;
            if(cursor.getCenter().intersects(t1.getLocalBounds())) t1.setColor(Color::Black);// через массив не работает
            else t1.setColor(Color::Red);
            if(cursor.getCenter().intersects(t2.getLocalBounds())) t2.setColor(Color::Black);
            else t2.setColor(Color::Red);
            if(cursor.getCenter().intersects(t3.getLocalBounds())) t3.setColor(Color::Black);
            else t3.setColor(Color::Red);
             while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) window.close();
                if (event.type == Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        return 1;
                    }
                }
                if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                        if(cursor.getCenter().intersects(t1.getLocalBounds()))  return 1;
                        if(cursor.getCenter().intersects(t2.getLocalBounds()))  return 3;
                        if(cursor.getCenter().intersects(t3.getLocalBounds()))  return 2;
                }

            }

            window.clear(Color(250, 220, 220, 0));
            window.draw(sprite);
            cursor.Menuupdate(window,view);
            t1.draw(window);
            t2.draw(window);
            t3.draw(window);
            cursor.drawMenu(window);
            window.display();
        }
    }

char Interface::GameOver(string a,Vector2f b,int&zoom)
    {
        Texture texture;
        Sprite sprite;
        Image ii;
        ii.loadFromFile(a);
        texture.loadFromImage(ii);
        texture.update(ii);
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setScale(
            (ii.getSize().x*zoom)/ sprite.getLocalBounds().width,
            (ii.getSize().y*zoom) / sprite.getLocalBounds().height);
        sprite.setOrigin(ii.getSize().x/2,ii.getSize().y/2);
        sprite.setPosition(b);

        window.draw(sprite);
        window.display();
        Event event;
        while(window.isOpen())
        {
            while (window.pollEvent(event))
            {
                if (event.type == Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::Escape) return 0;
                }

            }
        }
    }



int Interface::Win(View&view, float time, int&itr,sf::String&levelname,sf::String&GamerName)
{

    writeRecord(view,GamerName,levelname,time,itr);
    TEXTt text1=TEXTt(L"(По)пыТок: "+to_string(itr),"ofont.ru_Unutterable.ttf",Color::White,Vector2f(0,300),100);
    TEXTt text2=TEXTt(L"Время: "+to_string(time),"ofont.ru_Unutterable.ttf",Color::White,Vector2f(0,300),100);

    text1.setPosition(Vector2f(text1.getLocalBounds().width/2,300));
    text2.setPosition(Vector2f(text2.getLocalBounds().width/2,text1.getPosition().y+text1.getLocalBounds().height+10));

    Sprite sprite,Bsprite;
    Texture texture, Btexture;

    Btexture.loadFromFile("Win.png");
    Btexture.update(Btexture);
    Btexture.setSmooth(true);
    Bsprite.setTexture(Btexture);
    view.reset(sf::FloatRect(0, 0, shir, dlin));
    view.setCenter(shir/2, dlin/2);
                window.setView(view);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
            {
                if (event.type == Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::Escape) return 1;
                }
            }
    cursor.Menuupdate(window,view);
    window.clear(Color(250, 220, 220, 0));
    window.draw(Bsprite);

    text1.draw(window);
    text2.draw(window);


    cursor.drawMenu(window);
    window.display();
    }
    return 1;
}

#endif // INGMAMEMENU_H_INCLUDED
