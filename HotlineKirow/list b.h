#ifndef LIST_B_H_INCLUDED
#define LIST_B_H_INCLUDED

template<class Object>
class List
{
public:
    struct node
    {
        Object object;
        node *pre, *post;
        node(Object &n)
        {
            object=n;
        }
    } *bg=NULL,*ed=NULL;
    List(){ bg=ed=NULL;}


    void add(Object &n)
    {
        node* tmp = new node(n);
        tmp->post=NULL;
        tmp->pre=ed;
        if(bg==NULL) bg=tmp;
        else ed->post=tmp;
        ed=tmp;
    }
    node* del(node* &d)
    {
        node* tmp=d->post;
        if(d->post==NULL&&d->pre==NULL) {bg=ed=NULL; return NULL;}
        if(!d->post) {d->pre->post=NULL; ed=d->pre;}
        else d->post->pre=d->pre;
        if(!d->pre) {d->post->pre=NULL;bg=d->post;}
        else d->pre->post=d->post;
        //delete d;
        return tmp;
    }
    void delH()
    {
        if(bg->post!=NULL) {bg=bg->post; delete bg->pre; bg->pre=NULL;}
        else bg=ed=NULL;
    }
    bool pyst(void){return bg==NULL&&ed==NULL;}
};



#endif // LIST_B_H_INCLUDED
