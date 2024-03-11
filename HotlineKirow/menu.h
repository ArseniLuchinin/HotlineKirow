#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

void Interface::zastavka(Sprite&menuS)
{
    TEXTt t=TEXTt(L"выполнил студент группы »426Ѕ\n\t\t\tЋучинин јрсений","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(shir/4,dlin/4));
    menuS.setScale(0.5,0.5);
    while(window.isOpen())
        {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased) return;

        }
        window.draw(menuS);
        t.draw(window);
        window.display();
    }
}

char Interface::levelSelect(View&view,sf::String&GamerName)

{   sf::String Levelname="Level";
    int i=1;
    float rotate=0.f;
    Clock *rotateTime=new Clock;
    rotateTime->restart();
    Image image, Bimage;
    Sprite sprite,Bsprite;
    Texture texture, Btexture;

    Btexture.loadFromFile("backGround.png");
    Btexture.update(Btexture);
    Btexture.setSmooth(true);
    Bsprite.setTexture(Btexture);
    Bsprite.setPosition(0,0);
    image.loadFromFile(Levelname+to_string(i)+".png");

    bool updf=true;

    char *lvlchr=new char[12];
    while(window.isOpen())
        {Event event;
        while (window.pollEvent(event))
            {

                if (event.type == Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::Escape) return 0;
                    if ( (event.key.code == sf::Keyboard::Enter)||(event.key.code == sf::Keyboard::Space))
                    {
                        char mn=0;
                        Levelname=Levelname+to_string(i);
                        do
                        {int itr=0;
                        while(!(mn=game(Levelname,view,itr++,GamerName)));
                        }
                        while(mn==3);
                            view.reset(sf::FloatRect(0, 0, shir, dlin));
                            view.setCenter(shir/2, dlin/2);
                            window.setView(view);
                        return 1;
                    }
                    if (event.key.code == sf::Keyboard::D||event.key.code == sf::Keyboard::Right)
                    {

                        if(!image.loadFromFile(Levelname+to_string(++i)+".png")) image.loadFromFile(Levelname+to_string(--i)+".png");
                        updf=true;
                    }
                    if (event.key.code == sf::Keyboard::A||event.key.code == sf::Keyboard::Left)
                    {
                        if(!image.loadFromFile(Levelname+to_string(--i)+".png")) image.loadFromFile(Levelname+to_string(++i)+".png");
                        updf=true;
                    }

                }
                if (event.type == sf::Event::MouseButtonReleased)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                        char mn=0;
                        Levelname=Levelname+to_string(i);
                        do
                        {int itr=0;
                        while(!(mn=game(Levelname,view,itr++,GamerName)));
                        }
                        while(mn==3);
                            view.reset(sf::FloatRect(0, 0, shir, dlin));
                            view.setCenter(shir/2, dlin/2);
                            window.setView(view);
                        return 1;
                        }
                    }
            }

            if(updf)
            {
                Image image3;
                Sprite sprite2;
                cretePImage(image,texture);
                sprite2.setTexture(texture);

                sprite=sprite2;
                sprite.setOrigin(image.getSize().x/2,image.getSize().y/2);
                sprite.setScale(
                (600)/sprite.getLocalBounds().width,
                (600)/sprite.getLocalBounds().height);
                sprite.setPosition(view.getCenter());
                updf=false;
            }


            if(rotateTime->getElapsedTime().asSeconds()>0.01f) {sprite.setRotation(rotate+=0.1);rotateTime->restart();}
            cursor.Menuupdate(window,view);
            window.clear();
            window.draw(Bsprite);
            window.draw(sprite);
            cursor.drawMenu(window);
            window.display();
        }
}




void Interface::education(View&view)
{
    Texture texture;
    Sprite sprite;
    texture.loadFromFile("EducationBG.png");
    texture.update(texture);
    sprite.setTexture(texture);

    TEXTt W=TEXTt("W","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(330,153),60);
    TEXTt S=TEXTt("S","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(330,237),60);
    TEXTt A=TEXTt("A","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(246,237),60);
    TEXTt D=TEXTt("D","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(414,237),60);
    TEXTt mov=TEXTt(L"-способ передвижени€ по кирќву","ofont.ru_Unutterable.ttf"); mov.setPosition(Vector2f(550+mov.getLocalBounds().width/2,190));
    TEXTt Lmos=TEXTt(L"-»спользовать оружие\n(основное действие кирќвчанина)","ofont.ru_Unutterable.ttf"); Lmos.setPosition(Vector2f(550+Lmos.getLocalBounds().width/2,450));
    TEXTt Rmos=TEXTt(L"-подобрать/выкинуть оружие","ofont.ru_Unutterable.ttf"); Rmos.setPosition(Vector2f(550+Rmos.getLocalBounds().width/2,700));
    TEXTt Esc=TEXTt("Escape","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(330,900),60);
    TEXTt PEsc=TEXTt(L"- попытка сбежать от\nкирќвских реальтностей","ofont.ru_Unutterable.ttf"); PEsc.setPosition(Vector2f(550+PEsc.getLocalBounds().width/2,930));
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Escape) return;
            }

        }

        cursor.Menuupdate(window,view);
        window.clear(Color(250, 220, 220, 0));

        window.draw(sprite);
        W.draw(window);
        S.draw(window);
        A.draw(window);
        D.draw(window);
        mov.draw(window);
        Lmos.draw(window);
        Rmos.draw(window);
        Esc.draw(window);
        PEsc.draw(window);
        cursor.drawMenu(window);
        window.display();
    }
}

bool Interface::GamerSet(View&view,sf::String&GamerName)
{
    Texture backT;
    Sprite backS;
    getSprite("backname.png",backT,backS);

    wstring message=L"";


    TEXTt name=TEXTt("","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(40,300),50);
    TEXTt vvedite=TEXTt(L"¬ведите своЄим€,  ирќвчанин: ","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(0,300),50);
    vvedite.setPosition(Vector2f(100+vvedite.getLocalBounds().width/2,300));

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::Escape) return false;
                }

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == 8)
                {
                    if(message.size()!=0)
                    {
                        message.resize(message.size()-1);
                        name.getText().setString(message);
                    }

                }
                else if (event.text.unicode == 13)
                {
                    GamerName=name.getText().getString().toAnsiString();
                    writeNameFromFile(GamerName);
                    return true;
                }
                else if (event.text.unicode == 27);
                else
                {
                message += static_cast<wchar_t>(event.text.unicode);
                name.getText().setString(message);
                }
            }
        }
    name.setPosition(Vector2f(vvedite.getPosition().x+vvedite.getLocalBounds().width/2+name.getLocalBounds().width/2,name.getPosition().y));
    cursor.Menuupdate(window,view);
    window.draw(backS);
    vvedite.draw(window);
    name.draw(window);
    cursor.drawMenu(window);
    window.display();
    }
}




void Interface::mainMenu(Sprite&menuS,View&view)
    {
        menuS.setScale(1,1);
        String GamerName=L"»грок не ввЄл им€";
        bool namefl=readNameFromFile(GamerName);
        TEXTt text1=TEXTt(L"¬ыбрать уровень","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(shir/3,dlin/3));
        TEXTt name=TEXTt(GamerName,"ofont.ru_Unutterable.ttf",Color::Red,Vector2f(0,0));
        TEXTt text3=TEXTt(L"ѕам€тка  ирќвчанина","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(shir/3.,text1.getPosition().y+text1.getLocalBounds().height+10.f));
        TEXTt text4=TEXTt(L"таблица рекордов","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(shir/3.,text3.getPosition().y+text3.getLocalBounds().height+10.f));
        TEXTt text5=TEXTt(L"¬вести им€ игрока","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(shir/3.,text4.getPosition().y+text4.getLocalBounds().height+10.f));
        TEXTt text2=TEXTt(L"ѕокинуть  ирќв","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(shir/3.,text5.getPosition().y+text5.getLocalBounds().height+10.f));
        name.setString(GamerName);
        name.setPosition(Vector2f(name.getLocalBounds().width/2,name.getLocalBounds().height/2));
        if(namefl) text5.setString(L"сменить игрока");
        string Levelname;
        string none="none";
    while (window.isOpen())
    {
        if(cursor.getCenter().intersects(text1.getLocalBounds())) text1.setColor(Color::Black);
        else text1.setColor(Color::Red);
        if(cursor.getCenter().intersects(text2.getLocalBounds())) text2.setColor(Color::Black);
        else text2.setColor(Color::Red);
        if(cursor.getCenter().intersects(text3.getLocalBounds())) text3.setColor(Color::Black);
        else text3.setColor(Color::Red);
        if(cursor.getCenter().intersects(text4.getLocalBounds())) text4.setColor(Color::Black);
        else text4.setColor(Color::Red);
        if(cursor.getCenter().intersects(text5.getLocalBounds())) text5.setColor(Color::Black);
        else text5.setColor(Color::Red);
        Event event;
        while (window.pollEvent(event))
            {
                if (event.type == Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::Escape) window.close();
                }
                if (event.type == sf::Event::Closed) window.close();

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                        if (cursor.getCenter().intersects(text1.getLocalBounds())) { if (namefl) levelSelect(view, GamerName); }
                        else if (cursor.getCenter().intersects(text3.getLocalBounds())) education(view);
                        else if (cursor.getCenter().intersects(text2.getLocalBounds())) window.close(); //text2.setString("Ќ≈ ѕџ“ј…“≈—№ ѕо »Ќ”“№  »–ќ¬");
                        else if(cursor.getCenter().intersects(text4.getLocalBounds())) readRecord(view);
                        else if(cursor.getCenter().intersects(text5.getLocalBounds()))
                        {
                            namefl=GamerSet(view,GamerName);
                            name.setString(GamerName);
                            name.setPosition(Vector2f(name.getLocalBounds().width/2,name.getLocalBounds().height/2));
                            if(namefl) text5.setString(L"сменить игрока");
                        }

                }
            }
    cursor.Menuupdate(window,view);
    window.clear(Color(250, 220, 220, 0));

    window.draw(menuS);
    text1.draw(window);
    text3.draw(window);
    text2.draw(window);
    text4.draw(window);
    text5.draw(window);
    name.draw(window);

    cursor.drawMenu(window);
    window.display();
    }

    }

#endif // MENU_H_INCLUDED
