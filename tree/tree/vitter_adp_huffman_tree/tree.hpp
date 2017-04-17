
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
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
class adp_huffman_tree
{
public:
    char val;
    int frequency;
    int order;
    
    adp_huffman_tree* lchild;
    adp_huffman_tree* rchild;
    adp_huffman_tree* parent;
    
    adp_huffman_tree(){val='*';frequency=order=0; lchild=rchild=parent=NULL;}
};
adp_huffman_tree chr[256];
vector<vector<adp_huffman_tree*>> adp_huffman_tree_order_leaf;
vector<vector<adp_huffman_tree*>> adp_huffman_tree_order_internal;
void swap(adp_huffman_tree &ah1,adp_huffman_tree &ah2)
{
    adp_huffman_tree* t1,*t2=NULL;
    if(ah1.parent->lchild->order==ah1.order && ah2.parent->lchild->order==ah2.order)
    {
        t1=ah1.parent->lchild;
        t2=ah1.parent;
        ah1.parent->lchild=ah2.parent->lchild;
        ah1.parent=ah2.parent;
        ah2.parent->lchild=t1;
        ah2.parent=t2;
    }
    else if(ah1.parent->lchild->order==ah1.order && ah2.parent->rchild->order==ah2.order)
    {
        t1=ah1.parent->lchild;
        t2=ah1.parent;
        ah1.parent->lchild=ah2.parent->rchild;
        ah1.parent=ah2.parent;
        ah2.parent->rchild=t1;
        ah2.parent=t2;
    }
    else if(ah1.parent->rchild->order==ah1.order && ah2.parent->lchild->order==ah2.order)
    {
        t1=ah1.parent->rchild;
        t2=ah1.parent;
        ah1.parent->rchild=ah2.parent->lchild;
        ah1.parent=ah2.parent;
        ah2.parent->lchild=t1;
        ah2.parent=t2;
    }
    else
    {
        t1=ah1.parent->rchild;
        t2=ah1.parent;
        ah1.parent->rchild=ah2.parent->rchild;
        ah1.parent=ah2.parent;
        ah2.parent->rchild=t1;
        ah2.parent=t2;
    }
    int temp;
    temp=ah1.order;
    ah1.order=ah2.order;
    ah2.order=temp;
}
void init()
{
    vector<adp_huffman_tree *> v;
    for(int i=0;i!=256;i++)
    {adp_huffman_tree_order_leaf.push_back(v);adp_huffman_tree_order_internal.push_back(v);}
    return;
}
void Slide(adp_huffman_tree *ah)
{
    while(ah->parent!=NULL)
    {
        adp_huffman_tree* fp=ah->parent;
    int w=ah->frequency;
    if(ah->lchild==NULL&&ah->rchild==NULL)
    {
        auto i=adp_huffman_tree_order_leaf[w].begin();
        for(;i!=adp_huffman_tree_order_leaf[w].end();i++)
        {
            if((*i)->order==ah->order) {break;}
        }
        swap(*ah,*(*(adp_huffman_tree_order_leaf[w].end()-1)));
        (*i)=*(adp_huffman_tree_order_leaf[w].end()-1);
        adp_huffman_tree_order_leaf[w].erase(adp_huffman_tree_order_leaf[w].end()-1);
        for(auto i=adp_huffman_tree_order_internal[w].begin();i!=adp_huffman_tree_order_internal[w].end();i++)
        {
            swap(*ah,**i);
        }
        adp_huffman_tree_order_leaf[w+1].insert(adp_huffman_tree_order_leaf[w+1].begin(), ah);
        ah->frequency++;
        ah=ah->parent;
    }
    else
    {
        auto i=adp_huffman_tree_order_internal[w].begin();
        for(;i!=adp_huffman_tree_order_internal[w].end();i++)
        {
            if((*i)->order==ah->order) {break;}
        }
        adp_huffman_tree_order_internal[w].erase(i);
        for(auto i=adp_huffman_tree_order_leaf[w+1].begin();i!=adp_huffman_tree_order_leaf[w+1].end();i++)
        {
            swap(*ah,**i);
        }
        adp_huffman_tree_order_internal[w+1].insert(adp_huffman_tree_order_internal[w+1].begin(), ah);
        ah->frequency++;
        ah=fp;
    }
    }
    adp_huffman_tree_order_internal[ah->frequency].erase(adp_huffman_tree_order_internal[ah->frequency].end()-1);
    ah->frequency++;
    adp_huffman_tree_order_internal[ah->frequency].push_back(ah);
}
int Height(adp_huffman_tree *t)
{
    if(t!=NULL)
    {
        int m,n;
        m=Height(t->lchild);
        n=Height(t->rchild);
        return m>n? m+1:n+1;
    }
    else
        return 0;
}
void print(adp_huffman_tree *t)
{
    int h=Height(t);
    Queue<adp_huffman_tree*> q;
    int w=(int)pow(2,h);
    q.enqueue(t);
    while(w!=1)
    {
        int flag=0;
        for(int i=q.size();i!=0;i--)
        {
            adp_huffman_tree * t=q.dequeue();
            if(t!=NULL)
            {
                if(flag==0)
                {cout<<setw(w)<<'|'<<t->val<<'|'; flag=1;}
                else
                    cout<<setw(2*w-2)<<'|'<<t->val<<'|';
                q.enqueue(t->lchild);
                q.enqueue(t->rchild);
            }
            else
            {
                if(flag==0)
                {cout<<setw(w)<<'|'<<'#'<<'|'; flag=1;}
                else
                    cout<<setw(2*w-2)<<'|'<<'#'<<'|';
                q.enqueue(NULL);
                q.enqueue(NULL);
            }
        }
        cout<<endl;
        w=w/2;
    }
}
void adp_huffman_tree_Encoding()
{
    init();
    fstream file("adp_huffman_tree.txt",ios::in);
    char c;
    adp_huffman_tree *nty=new adp_huffman_tree;
    adp_huffman_tree*head =nty;
    nty->order=255;
    while(!file.eof()&&file>>c)
    {
        if(chr[c].val=='*')
        {
            chr[c].val=c;
            nty->lchild=new adp_huffman_tree;
            nty->lchild->order=nty->order-2;
            nty->lchild->parent=nty;
            nty->rchild=&chr[c];
            chr[c].order=nty->order-1;
            chr[c].parent=nty;
            nty=nty->lchild;
            adp_huffman_tree_order_internal[0].push_back(chr[c].parent);
            Slide(chr[c].parent);
            print(head);
            cout<<endl;
            chr[c].frequency++;
            adp_huffman_tree_order_leaf[1].insert(adp_huffman_tree_order_leaf[1].begin(),&chr[c]);
        }
        else
        {
            Slide(&chr[c]);
            cout<<endl;
            print(head);
        }
    }
    file.close();
}
