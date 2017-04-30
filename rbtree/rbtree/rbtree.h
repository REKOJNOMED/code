#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <fstream>
using namespace std;
template <typename T>
class   Queue
{
public:
    vector<T> queue;
    void enqueue(T t){queue.push_back(t);}
    T dequeue(){ T t=*queue.begin();queue.erase(queue.begin());return t;}
    int empty(){if(queue.size()==0)return 1;else return 0;}
    int size(){return (int)queue.size();}
};
class rbtree
{
public:
    int key;
    char color;
    rbtree* lchild;
    rbtree* rchild;
    rbtree* parent;
    rbtree(){key=color=0;lchild=rchild=parent=NULL;}
    rbtree(int a,char c) {key=a,color=c;lchild=rchild=parent=NULL;}
};
rbtree NIL(0,'b');
void RB_left_rotate(rbtree *t)
{
    rbtree *s=t->rchild;
    t->rchild=s->lchild;
    s->lchild->parent=t;
    s->lchild=t;
    if(t==t->parent->lchild)
    {
        t->parent->lchild=s;
        s->parent=t->parent;
    }
    else
    {
        t->parent->rchild=s;
        s->parent=t->parent;
    }
    t->parent=s;;
}
void RB_right_rotate(rbtree *t)
{
    rbtree *s=t->lchild;
    t->lchild=s->rchild;
    s->rchild->parent=t;
    s->rchild=t;
    if(t==t->parent->lchild)
    {
        t->parent->lchild=s;
        s->parent=t->parent;
    }
    else
    {
        t->parent->rchild=s;
        s->parent=t->parent;
    }
    t->parent=s;
}
void RB_insert_fix(rbtree*&head,rbtree *t)
{
    while(t->parent->color=='r')
    {
        if(t->parent->parent->lchild==t->parent)
        {
            if(t->parent->parent->rchild->color=='r')
            {
                t->parent->parent->rchild->color='b';
                t->parent->color='b';
                t->parent->parent->color='r';
                t=t->parent->parent;
            }
            else
            {
                if(t==t->parent->rchild)
                {
                    RB_left_rotate(t->parent);
                    if(t->parent==&NIL) head=t;
                    t=t->lchild;
                }
                RB_right_rotate(t->parent->parent);
                t->parent->color='b';
                t->parent->rchild->color='r';
                if(t->parent->parent==&NIL) head=t->parent;
                break;
            }
        }
        else
        {
            if(t->parent->parent->lchild->color == 'r')
            {
                t->parent->parent->lchild->color='b';
                t->parent->color='b';
                t->parent->parent->color='r';
                t=t->parent->parent;
            }
            else
            {
                if(t==t->parent->lchild)
                {
                    RB_right_rotate(t->parent);
                    if(t->parent==&NIL) head=t;
                    t=t->rchild;
                }
                RB_left_rotate(t->parent->parent);
                t->parent->color='b';
                t->parent->lchild->color='r';
                if(t->parent->parent==&NIL) head=t->parent;
                break;
            }
        }
    }
    head->color='b';
}
rbtree* RB_insert(rbtree *t,int k)
{
    rbtree*head=t;
    if(t==NULL)
    {
        t=new rbtree;
        t->key=k;
        t->lchild=&NIL;
        t->rchild=&NIL;
        t->color='b';
        t->parent=&NIL;
        return t;
    }
    else
    {
        while(1)
        {
            if(k<t->key)
            {
                if(t->lchild==&NIL)
                {
                    t->lchild=new rbtree;
                    t->lchild->color='r';
                    t->lchild->key=k;
                    t->lchild->parent=t;
                    t->lchild->lchild=&NIL;
                    t->lchild->rchild=&NIL;
                    RB_insert_fix(head,t->lchild);
                    break;
                }
                else t=t->lchild;
            }
            else if(k>t->key)
            {
                if(t->rchild==&NIL)
                {
                    t->rchild=new rbtree;
                    t->rchild->color='r';
                    t->rchild->key=k;
                    t->rchild->parent=t;
                    t->rchild->lchild=&NIL;
                    t->rchild->rchild=&NIL;
                    RB_insert_fix(head,t->rchild);
                    break;
                }
                else t=t->rchild;
            }
            else break;
        }
        return head;
    }
}
template <typename T>
void swap(T& a ,T& b)
{
    T temp;
    temp =a;
    a=b;
    b=temp;
}
rbtree* RB_find(rbtree* t,int k)
{
    while(t!=&NIL&&t!=NULL)
    {
        if(k<t->key)
            t=t->lchild;
        else if(k>t->key)
            t=t->rchild;
        else
            return t;
    }
    return NULL;
}
rbtree* RB_min(rbtree*t)
{
    while(t->lchild!=&NIL)
        t=t->lchild;
    return t;
}
void RB_delete_fix(rbtree *t,rbtree*&head)
{
    rbtree* w=NULL;
    while(t->parent!=&NIL&&t->color=='b')
    {
        if(t==t->parent->lchild)
        {
            w=t->parent->rchild;
            if(w->color=='r')
            {
                w->color='b';
                t->parent->color='r';
                RB_left_rotate(t->parent);
                if(w->parent==&NIL) head=w->parent;
                w=t->parent->rchild;
            }
            if(w->lchild->color=='b'&&w->rchild->color=='b')
            {
                w->color='r';
                t=t->parent;
            }
            else
            {
                if(w->rchild->color=='b')
                {
                    w->lchild->color='b';
                    w->color='r';
                    rbtree*parent =t->parent;
                    RB_right_rotate(w);
                    t->parent=parent;
                    w=t->parent->rchild;
                }
                w->color=t->parent->color;
                t->parent->color='b';
                w->rchild->color='b';
                RB_left_rotate(t->parent);
                if(t->parent==&NIL) head=t;
                break;
            }
        }
        else
        {
            w=t->parent->lchild;
            if(w->color=='r')
            {
                w->color='b';
                t->parent->color='r';
                RB_right_rotate(t->parent);
                if(w->parent==&NIL) head=w;
                w=t->parent->lchild;
            }
            if(w->lchild->color=='b'&&w->rchild->color=='b')
            {
                w->color='r';
                t=t->parent;
            }
            else
            {
                if(w->lchild->color=='b')
                {
                    w->rchild->color='b';
                    w->color='r';
                    rbtree*parent =t->parent;
                    RB_left_rotate(w);
                    t->parent=parent;
                    w=t->parent->lchild;
                }
                w->color=t->parent->color;
                t->parent->color='b';
                w->lchild->color='b';
                RB_right_rotate(t->parent);
                if(t->parent==&NIL) head=t;
                break;
            }
        }
    }
    t->color='b';
}
rbtree* RB_delete(rbtree*t ,int k)
{
    rbtree*head=t;
    rbtree* x=RB_find(t,k);
    if(x==NULL) return t;
    rbtree*y =NULL;
    char color;
    if(x->lchild==&NIL)
    {
        color=x->color;
        y=x->rchild;
        y->parent=x->parent;
        if(x->parent->lchild==x)
            x->parent->lchild=y;
        else
            x->parent->rchild=y;
        delete x;
    }
    else if(x->rchild==&NIL)
    {
        color=x->color;
        y=x->lchild;
        y->parent=x->parent;
        if(x->parent->lchild==x)
            x->parent->lchild=y;
        else
            x->parent->rchild=y;
        delete x;
    }
    else
    {
        y=RB_min(x->rchild);
        ::swap(x->key,y->key);
        x=y;
        color=x->color;
        y=y->rchild;
        y->parent=x->parent;
        if(x->parent->lchild==x)
            x->parent->lchild=y;
        else
            x->parent->rchild=y;
        delete x;
    }
    if(color=='b')
        RB_delete_fix(y,head);
    return head;
}
int Height(rbtree *t)
{
    if(t!=&NIL&&t!=NULL)
    {
        int m,n;
        m=Height(t->lchild);
        n=Height(t->rchild);
        return m>n? m+1:n+1;
    }
    else
        return 0;
}
void print(rbtree *t)
{
    int h=Height(t);
    Queue<rbtree*> q;
    int w=(int)pow(2,h);
    q.enqueue(t);
    while(w!=1)
    {
        int flag=0;
        for(int i=q.size();i!=0;i--)
        {
            rbtree * t=q.dequeue();
            if(t!=&NIL&&t!=NULL)
            {
                if(flag==0)
                {cout<<setw(w)<<t->key<<t->color; flag=1;}
                else
                    cout<<setw(2*w-1)<<t->key<<t->color;
                q.enqueue(t->lchild);
                q.enqueue(t->rchild);
            }
            else
            {
                if(flag==0)
                {cout<<setw(w)<<"  "; flag=1;}
                else
                    cout<<setw(2*w)<<" ";
                q.enqueue(NULL);
                q.enqueue(NULL);
            }
        }
        cout<<endl;
        w=w/2;
    }
}
rbtree *Creat_RB_tree()
{
    rbtree* t=NULL;
    fstream file("rbtree.txt",ios::in);
    int k;
    while(file>>k)
    {
        t=RB_insert(t, k);
    }
    return t;
}





