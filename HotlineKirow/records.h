#ifndef RECORDS_H_INCLUDED
#define RECORDS_H_INCLUDED



void Interface::readRecord(View&view)
{
    int level=1;
    string levelname, timet, itert;
    Vector2f start=Vector2f(0,100), et, end=Vector2f(0,2000);

    TEXTt levelim=TEXTt("","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(0,300),50);
    TEXTt name=TEXTt("","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(0,300),50);
    TEXTt time=TEXTt("","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(0,300),50);
    TEXTt iter=TEXTt("","ofont.ru_Unutterable.ttf",Color::Red,Vector2f(0,300),50);

    levelname="level"+to_string(level);
    levelim.setString(levelname+":");
    levelim.setPosition(Vector2f(levelim.getLocalBounds().width/2,levelim.getLocalBounds().height));
    et=Vector2f(0,levelim.getPosition().y+levelim.getLocalBounds().height/2);
    XMLDocument doc;
    string filename=levelname+".xml";
    if(doc.LoadFile(filename.c_str())!=0)
    {
        return;
    }

    XMLElement* root=doc.RootElement();
    //root->NextSiblingElement();



    Texture backT;
    Sprite backS;
    backT.loadFromFile("recbg.png");
    backT.update(backT);
    backS.setTexture(backT);


    Sprite sprite;
    sprite.setTexture(backT);
    sprite.setTextureRect(IntRect(0, 0, shir, levelim.getPosition().y+levelim.getLocalBounds().height));


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::Escape) return;
                }


            if (event.type == sf::Event::MouseWheelMoved)
            {

                if(et.y<levelim.getPosition().y+levelim.getLocalBounds().height/2)
                {
                   if(event.mouseWheel.delta>0) et.y+=25;
                }

                if(end.y>dlin)
                {
                    if(event.mouseWheel.delta<0) et.y-=25;
                }
                //else {if (event.mouseWheel.delta>0) et.y+=25;}
            }
        }
    cursor.Menuupdate(window,view);
    window.draw(backS);
    XMLElement* userNode=root->FirstChildElement("User");
    start=et;
    while(userNode != NULL)
    {
    name.setString(userNode->Attribute("Name"));
    name.setPosition(Vector2f(start.x+ name.getLocalBounds().width/2,start.y+name.getLocalBounds().height/2+40));


    //XMLElement*userNode1=userNode->FirstChildElement(levelname.c_str());

    timet="Время: ";
    timet+=userNode->Attribute("time");
        time.setString(timet);
        time.setPosition(Vector2f(name.getPosition().x+ time.getLocalBounds().width/2+40+name.getLocalBounds().width/2, name.getPosition().y));

    itert="Попытки: ";
    itert+=userNode->Attribute("iter");
        iter.setString(itert);
        iter.setPosition(Vector2f(time.getPosition().x+iter.getLocalBounds().width/2+time.getLocalBounds().width/2+40,name.getPosition().y));

    start=Vector2f(start.x, iter.getPosition().y+iter.getLocalBounds().height/2);
    userNode = userNode->NextSiblingElement();

    name.draw(window);

    time.draw(window);
    iter.draw(window);
    }
    end=start;
    window.draw(sprite);
    levelim.draw(window);
    cursor.drawMenu(window);
    window.display();
    }
}

char Interface::writeRecord(View&view,string GamerName, string levelname,float&time, int&iter)
{
levelname+=".xml";
XMLDocument doc;
doc.LoadFile(levelname.c_str());

bool non=true;

    XMLElement* root=doc.RootElement();
    XMLElement* userNode=root->FirstChildElement("User");
    if(!userNode)
    {
        XMLElement* userNode1=doc.NewElement("User");
        userNode1->SetAttribute("Name",GamerName.c_str());
        userNode1->SetAttribute("time",to_string(time).c_str());
        userNode1->SetAttribute("iter",to_string(iter).c_str());
        root->InsertEndChild(userNode1);
        non=false;
    }
    else
    {
    userNode=root->FirstChildElement("User");
            if((atof(userNode->Attribute("time"))>=time))
            {
                XMLElement* userNode1=doc.NewElement("User");
                string tmp;

                tmp=userNode->Attribute("Name");
                userNode1->SetAttribute("Name",tmp.c_str());
                userNode->SetAttribute("Name",GamerName.c_str());

                tmp=userNode->Attribute("time");
                userNode1->SetAttribute("time",tmp.c_str());
                userNode->SetAttribute("time",to_string(time).c_str());

                tmp=userNode->Attribute("iter");
                userNode1->SetAttribute("iter",tmp.c_str());
                userNode->SetAttribute("iter",to_string(iter).c_str());

                root->InsertAfterChild(userNode,userNode1);
                non=false;
            }
            else
            while(userNode->NextSiblingElement()!= NULL)
            {


                if( (atof(userNode->NextSiblingElement()->Attribute("time"))>=time))
                {
                    XMLElement* userNode1=doc.NewElement("User");
                    userNode1->SetAttribute("Name",GamerName.c_str());
                    userNode1->SetAttribute("time",to_string(time).c_str());
                    userNode1->SetAttribute("iter",to_string(iter).c_str());
                    root->InsertAfterChild(userNode,userNode1);
                    non=false;
                    break;
                }
                userNode = userNode->NextSiblingElement();
            }
    if(non)
    {
        XMLElement* userNode1=doc.NewElement("User");
        userNode1->SetAttribute("Name",GamerName.c_str());
        userNode1->SetAttribute("time",to_string(time).c_str());
        userNode1->SetAttribute("iter",to_string(iter).c_str());
        root->InsertEndChild(userNode1);
    }
    XMLElement* userNode1=doc.NewElement("User");
    }
    bool fl=false;
    while(userNode!= NULL)
    {
        if(userNode->Attribute("Name")==GamerName&&(!fl)) fl=true;
        else if(userNode->Attribute("Name")==GamerName&&(fl))
        {
            root->DeleteChild(userNode);
            break;
        }
        userNode = userNode->NextSiblingElement();
    }
    doc.SaveFile(levelname.c_str());
    return 1;
}

#endif // RECORDS_H_INCLUDED
