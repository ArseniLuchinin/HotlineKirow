#ifndef INSTRUMENTS_H_INCLUDED
#define INSTRUMENTS_H_INCLUDED

inline void getSprite(const string a,Texture&texture, Sprite&sprite)
{
        texture.loadFromFile(a);
        texture.update(texture);
        sprite.setTexture(texture);
}

void cretePImage(Image&image,Texture&texture)
{
    Image image2;
    if(image.getSize().x!=image.getSize().y)
    {
        if(image.getSize().x>image.getSize().y)
        {
            image2.create(image.getSize().x,image.getSize().x,Color::Red);
            image2.createMaskFromColor(Color::Red);
            image2.copy(image,0,0,IntRect(0,0,image.getSize().x,image.getSize().y));
        }
        else
        {
            image2.create(image.getSize().y,image.getSize().y,Color::Red);
            image2.createMaskFromColor(Color::Red);
            image2.copy(image,0,0,IntRect(0,0,image.getSize().x,image.getSize().y));
        }


    }
    else
    {
        texture.loadFromImage(image);
        texture.update(image);
        return;
    }
    texture.loadFromImage(image2);
    texture.update(image2);
}

bool readNameFromFile(sf::String&GamerName)
{

    XMLDocument doc;
    if(!doc.LoadFile("LP.xml"));
    XMLElement* root;
    if(!(root=doc.RootElement()));
    XMLElement* userNode;
    if(!(userNode=root->FirstChildElement("User"))) return false;
    GamerName=userNode->Attribute("Name"); return true;

}

void writeNameFromFile(sf::String&GamerName)
{

    XMLDocument doc;
    if(!doc.LoadFile("LP.xml"));
    XMLElement* root;
    root=doc.RootElement();
    XMLElement* userNode;
    if(!(userNode=root->FirstChildElement("User"))) userNode=doc.NewElement("User");
    userNode->SetAttribute("Name",GamerName.toWideString().c_str());
    root->InsertEndChild(userNode);
    doc.SaveFile("LP.xml");
}

#endif // INSTRUMENTS_H_INCLUDED
