#include "rbtree.h"
#include "md5.h"
#include <time.h>
#include <string>
#include<stdlib.h>
#define N  100
class server
{
public:
    rbtree* machine;
    string server_mark;
    server(){machine=NULL;}
};
class virtual_server
{
public:
    server*server;
    string virtual_server_mark;
    virtual_server(){server=NULL;}
};
class Node
{
public:
    int data;
    Node*next;
    int flag;
    virtual_server virtual_service;
    Node(){data=flag=0;next=NULL;}
};
class Hash
{
public:
    Node node[N];
    int ser_num,virtual_ser_num;
    vector<int> virtual_server_pos;
    int hash(int key) {return key%N;}
    int server_pos_generator(string s);
    void next_pos(int &pos) {pos=(pos+1)%N;}
    void pre_pos(int &pos) {pos-- ;if(pos==-1) pos=N-1;}
    void Init_server();
    void Add_data(int data);
    void Add_server();
    void Delete_server(string server_mark);
    void Delete_data(int data);
    void Find(int data);
private:
    void Add_virtual_server_fix(int pos);
    void Delete_virtual_server_fix(int pos);
};
void Hash::Find(int data)
{
    int h=hash(data);
    int ser_pos=h;
    for(;node[ser_pos].flag==0;next_pos(ser_pos));
    rbtree *x=RB_find(node[ser_pos].virtual_service.server->machine,data);
    if(x!=NULL) cout<<data;
    else cout<<"未找到"<<endl;
}
int Hash::server_pos_generator(string s)
{
    s=MD5(s).toString();
    long long m1=0,m2=0,m3=0,m4=0;
    int m=1;
    for(int i=7;i>=0;i--)
    {
        m1+=m*(s[i]-'0');
        m=m*16;
    }
    m=1;
    for(int i=15;i>=8;i--)
    {
        m2+=m*(s[i]-'0');
        m=m*16;
    }
    m=1;
    for(int i=23;i>=16;i--)
    {
        m3+=m*(s[i]-'0');
        m=m*16;
    }
    m=1;
    for(int i=31;i>24;i--)
    {
        m4+=m*(s[i]-'0');
        m=m*16;
    }
    int h=(m1+m2+m3+m4)%N;
    while(node[h].flag==1) next_pos(h);
    return h;
}
void Hash::Init_server()
{
    cout<<"请输入初始服务器数量和每个服务器关联的虚拟服务器数量："<<endl;
    cin>>ser_num>>virtual_ser_num;
    string s,s1;
    for(int i=0;i!=ser_num;i++)
    {
        cout<<"输入机器编号。"<<endl;
        cin>>s;
        cout<<"输入其虚拟节点编号"<<endl;
        cin>>s1;
        int pos=server_pos_generator(s1);
        virtual_server_pos.push_back(pos);
        node[pos].virtual_service.server=new server;
        node[pos].flag=1;
        node[pos].virtual_service.server->server_mark=s;
        node[pos].virtual_service.virtual_server_mark=s1;
        for(int j=1;j!=virtual_ser_num;j++)
        {
            cout<<"输入其虚拟节点编号"<<endl;
            cin>>s1;
            int pos2=server_pos_generator(s1);
            virtual_server_pos.push_back(pos2);
            node[pos2].flag=1;
            node[pos2].virtual_service=node[pos].virtual_service;
            node[pos2].virtual_service.virtual_server_mark=s1;
        }
    }
}
void Hash::Delete_data(int data)
{
    int h=hash(data);
    Node*i=node[h].next;
    Node*pre=&node[h];
    while(i!=NULL)
    {
        if(i->data==data)
        {
            pre->next=i->next;
            delete i;
        }
        pre=i;
        i=i->next;
    }
    int ser_pos=h;
    for(;node[ser_pos].flag==0;next_pos(ser_pos));
    node[ser_pos].virtual_service.server->machine=RB_delete(node[ser_pos].virtual_service.server->machine,data);
}
void Hash::Add_data(int data)
{
    int h=hash(data);
    Node *p=new Node;
    p->data=data;
    p->next=node[h].next;
    node[h].next=p;
    int ser_pos=h;
    for(;node[ser_pos].flag==0;next_pos(ser_pos));
    node[ser_pos].virtual_service.server->machine=RB_insert(node[ser_pos].virtual_service.server->machine,data);
}
void Hash::Add_virtual_server_fix(int pos)
{
    int ser_pos_pre=pos;
    int ser_pos_next=pos;
    pre_pos(ser_pos_pre);
    next_pos(ser_pos_next);
    for( ;node[ser_pos_pre].flag==0;pre_pos(ser_pos_pre));
    for(;node[ser_pos_next].flag==0;next_pos(ser_pos_next));
    next_pos(ser_pos_pre);
    for(;node[ser_pos_pre].flag==0;next_pos(ser_pos_pre))
    {
        for(Node *i=node[ser_pos_pre].next;i!=NULL;i=i->next)
        {
            node[ser_pos_next].virtual_service.server->machine=RB_delete(node[ser_pos_next].virtual_service.server->machine,i->data);
            node[pos].virtual_service.server->machine=RB_insert(node[pos].virtual_service.server->machine,i->data);
        }
    }
    for(Node *i=node[ser_pos_pre].next;i!=NULL;i=i->next)
    {
        node[ser_pos_next].virtual_service.server->machine=RB_delete(node[ser_pos_next].virtual_service.server->machine,i->data);
        node[pos].virtual_service.server->machine=RB_insert(node[pos].virtual_service.server->machine,i->data);
    }
}
void Hash::Add_server()
{
    if(ser_num==N)
    {
        cout<<"服务器已达数量上限。"<<endl;
        return ;
    }
    else
    ser_num++;
    string s,s1;
    cout<<"输入服务器编号。"<<endl;
    cin>>s;
    cout<<"输入虚拟服务器编号。"<<endl;
    cin>>s1;
    int pos=server_pos_generator(s1);
    node[pos].virtual_service.virtual_server_mark=s1;
    virtual_server_pos.push_back(pos);
    node[pos].flag=1;
    node[pos].virtual_service.server=new server;
    node[pos].virtual_service.server->server_mark=s;
    Add_virtual_server_fix(pos);
    for(int i=1;i!=virtual_ser_num;i++)
    {
        cout<<"输入虚拟服务器编号。"<<endl;
        cin>>s1;
        int pos2=server_pos_generator(s1);
        virtual_server_pos.push_back(pos2);
        node[pos2].flag=1;
        node[pos2].virtual_service=node[pos].virtual_service;
        node[pos2].virtual_service.virtual_server_mark=s1;
        Add_virtual_server_fix(pos2);
    }
}
void Hash::Delete_virtual_server_fix(int pos)
{
    int ser_pos_pre=pos;
    int ser_pos_next=pos;
    for( ;node[ser_pos_pre].flag==0;pre_pos(ser_pos_pre));
    for(;node[ser_pos_next].flag==0;next_pos(ser_pos_next));
    next_pos(ser_pos_pre);
    for(;ser_pos_pre!=pos;next_pos(ser_pos_pre))
    {
        for(Node *i=node[ser_pos_pre].next;i!=NULL;i=i->next)
        {
            node[ser_pos_next].virtual_service.server->machine=RB_insert(node[ser_pos_next].virtual_service.server->machine,i->data);
        }
    }
    for(Node *i=node[ser_pos_pre].next;i!=NULL;i=i->next)
    {
        node[ser_pos_next].virtual_service.server->machine=RB_insert(node[ser_pos_next].virtual_service.server->machine,i->data);
    }

}
void Hash::Delete_server(string server_mark)
{
    ser_num--;
    for(int j=0;j!=virtual_server_pos.size();j++)
    {
        int i=virtual_server_pos[j];
        if(node[i].flag==1&&node[i].virtual_service.server->server_mark==server_mark)
        {
            node[i].flag=0;
            node[i].virtual_service.server=NULL;
            Delete_virtual_server_fix(i);
        }
    }
}

