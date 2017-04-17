#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#define MAX 99999
#define N 20
using namespace std;
struct edge
{
    int v1;
    int v2;
    int weight;
    edge(){v1=v2=-1;weight=MAX;}
};
class Union
{
public:
    int father[N];
    int rank[N];
    Union(int n){for(int i=0;i!=n;i++) {father[i]=i;rank[i]=1;} }
    int find_set(int x)
    {
        while(x!=father[x])
            x=father[x];
        return x;
    }
    void merge(int x,int y)
    {
        int x0=x,y0=y;
        x=find_set(x);
        y=find_set(y);
        if(x==y) return;
        cout<<x0<<'-'<<y0<<' ';
        if(rank[x]<rank[y]) father[x]=y;
        else
        {
            if(rank[x]==rank[y]) rank[x]++;
            father[y]=x;
        }
        return;
    }
};
template <typename T>
class Stack
{
public:
    T stack[N]={0};
    int esp;
    Stack() {esp=-1;}
    void push(T a) {esp++;stack[esp]=a;}
    T pop() {esp--;return stack[esp+1];}
    T top() {return stack[esp];}
};
class node
{
public:
    int vertex;
    int weight;
    node*next;
    node(){vertex=0;next=NULL;}
};
class d_graph
{
public:
    vector<node> adj_list;
    vector<int> dfn;
    vector<int> low;
    vector<vector<int>> st_connect_component;
    int ver_num;
    int edge_num;
    int isStrongConnect;
    int st_connect_num;
    int weight;
    int adj_matrix[N][N];
    Stack<int> s;
    Stack<int>s1;
    d_graph(){ver_num=edge_num=st_connect_num=0;}
    d_graph(int a,int b):ver_num(a),edge_num(b){for(int i=0;i!=ver_num;i++)
    {node *p=new node; p->vertex=i;adj_list.push_back(*p);dfn.push_back(0);low.push_back(0);}
        st_connect_num=0;
    }
    void Tarjan(int u);
    void D_Tarjan(int u);
    void list_to_matrix();
    int p[N];
    void Dijkstra();
    void show_Dijkstra(int i);
    int p2[N][N];
    void Floyd();
    void show_Floyd();
    vector<int> sq;
    int Topologically_sort(int i);
    int dag_distance[N];
    int dag_path[N];
    void Dag_shortest_path();
    void show_dag_path(int i);
};
class u_graph
{
public:
    vector<node> adj_list;
    vector<int> dfn;
    vector<int> low;
    vector<int> dfn1;
    vector<int> low1;
    vector<vector<int>> db_vertex_connect_component;
    vector<vector<int>> db_edge_connect_component;
    int ver_num;
    int edge_num;
    int db_vertex_connect_num;
    int db_edge_connect_num;
    int adj_matrix[N][N];
    Stack<int> s;
    Stack<int>s1;
    u_graph(){ver_num=edge_num=db_vertex_connect_num=db_edge_connect_num=0;}
    u_graph(int a,int b):ver_num(a),edge_num(b){for(int i=0;i!=ver_num;i++)
    {node *p=new node; p->vertex=i;adj_list.push_back(*p);dfn.push_back(0);dfn1.push_back(0);low.push_back(0);low1.push_back(0);}
    }
    void list_to_matrix();
    void U_vertex_Tarjan(int u,int p);
    void U_edge_Tarjan(int u,int p);
    void sparse_Prime();
    void Prime();
    void Kruskal();
    int p[N];
    void Dijkstra();
    void show_Dijkstra(int i);
    int p2[N][N];
    void Floyd();
    void show_Floyd();
};
void Creat_dg_list(d_graph &g)
{
    fstream file("d_edge_info.txt",ios::in);
    int i,j,k;
    while(!file.eof()&&file>>i>>j>>k)
    {
        node *p=new node;
        p->next=g.adj_list[i].next;
        g.adj_list[i].next=p;
        p->vertex=j;
        p->weight=k;
    }
    file.close();
}
void Creat_ug_list(u_graph &g)
{
    fstream file("u_edge_info.txt",ios::in);
    int i,j,k;
    while(!file.eof()&&file>>i>>j>>k)
    {
        node *p=new node;
        p->next=g.adj_list[i].next;
        g.adj_list[i].next=p;
        p->vertex=j;
        p->weight=k;
        p=new node;
        p->next=g.adj_list[j].next;
        g.adj_list[j].next=p;
        p->vertex=i;
        p->weight=k;
    }
    file.close();
}
void sort(vector<edge> &v)
{
    for(int i=(int)v.size()/2;i<=v.size()-1;i++)
    {
        for(int j=i;j!=1;j=j/2)
        {
            if(v[j].weight<v[j/2].weight)
                swap(v[j],v[j/2]);
        }
    }
}
void swap (edge& e1,edge &e2)
{
    edge temp;
    temp=e1;
    e1=e2;
    e2=temp;
}
void adjust(vector<edge>&v,int i)
{
    if(v[i].weight<v[i/2].weight)
    {
        while(i!=1)
        {
            if(v[i].weight<v[i/2].weight)
            {
                swap(v[i],v[i/2]);
                i=i/2;
            }
            else
                break;
        }
    }
    else
    {
        for(;2*i+1<=v.size()-1;)
        {
            if(v[2*i].weight<v[2*i+1].weight&&v[2*i].weight<v[i].weight)
            {
                swap(v[i],v[2*i]);
                i=2*i;
            }
            else if(v[2*i+1].weight<v[2*i].weight&&v[2*i+1].weight<v[i].weight)
            {
                swap(v[2*i+1],v[i]);
                i=2*i+1;
            }
            else
                break;
        }
        if(2*i<=v.size()-1)
        {
            if(v[2*i].weight<v[i].weight)
            {
                swap(v[i],v[2*i]);
                i=2*i;
            }
        }
        
    }
}
edge pop(vector<edge>&v)
{
    
    edge v0=*(v.begin()+1);
    v.erase(v.begin()+1);
    v.insert(v.begin()+1,*(v.end()-1));
    v.erase(v.end()-1);
    int i=1;
    for(;2*i+1<=v.size()-1;)
    {
        if(v[2*i].weight<v[2*i+1].weight&&v[2*i].weight<v[i].weight)
        {
            swap(v[i],v[2*i]);
            i=2*i;
        }
        else if(v[2*i+1].weight<v[2*i].weight&&v[2*i+1].weight<v[i].weight)
        {
            swap(v[2*i+1],v[i]);
            i=2*i+1;
        }
        else
            break;
    }
    if(2*i<=v.size()-1)
    {
        if(v[2*i].weight<v[i].weight)
        {
            swap(v[i],v[2*i]);
            i=2*i;
        }
    }
    return v0;
}

int min(int a,int b)
{
    return a>b? b:a;
}
int flag[N];
int flag2[N];
void d_graph::Tarjan(int u)
{
    static int dn=0;
    dn++;
    low[u]=dfn[u]=dn;
    s.push(u);
    flag2[u]=1;
    for(node*i=adj_list[u].next;i!=NULL;i=i->next)
    {
        if(!dfn[i->vertex])
        {
            Tarjan(i->vertex);
            low[u]=min(low[u],low[i->vertex]);
        }
        else if(flag2[i->vertex]==1)
        {
            low[u]=min(low[u],dfn[i->vertex]);
        }
    }
    if(low[u]==dfn[u])
    {
        int p;
        vector<int> v;
        do
        {
            p=s.pop();
            v.push_back(p);
            flag2[p]=0;
        }while(p!=u);
        st_connect_component.push_back(v);
        st_connect_num++;
    }

}
void d_graph::D_Tarjan(int u)
{
    Tarjan(u);
    for(int i=0;i!=ver_num;i++)
    {
        if(!dfn[i])
            Tarjan(i);
    }
}
void u_graph::U_vertex_Tarjan(int u,int p)
{
    static int dn=0;
    dn++;
    low[u]=dfn[u]=dn;
    s.push(u);
    flag[u]=1;
    for(node*i=adj_list[u].next;i!=NULL;i=i->next)
    {
        if(!dfn[i->vertex])
        {
            if(flag[u]==0)      {s.push(u); flag[u]=1;}
            U_vertex_Tarjan(i->vertex,u);
            if(low[i->vertex]>low[u]) continue;
            else low[u]=low[i->vertex];
            if(low[u]==dfn[u])
            {
                vector<int> v;
                int p;
                do
                {
                    p=s.pop();
                    v.push_back(p);
                    flag[p]=0;
                }while(p!=u);
                db_vertex_connect_component.push_back(v);
                db_vertex_connect_num++;
            }
        }
        else
        {
            if(i->vertex!=p&&dfn[u]>dfn[i->vertex])
            {
                low[u]=min(low[u],dfn[i->vertex]);
                if(flag[u]==0)
                {s.push(u); flag[u]=1;}
            }
        }
    }
}
void u_graph::U_edge_Tarjan(int u,int p)
{
    static int dn1=0;
    dn1++;
    low1[u]=dfn1[u]=dn1;
    s1.push(u);
    for(node*i=adj_list[u].next;i!=NULL;i=i->next)
    {
        if(!dfn1[i->vertex])
        {
            U_edge_Tarjan(i->vertex,u);
            low1[u]=min(low1[u],low1[i->vertex]);
        }
        else
        {
            if(i->vertex!=p&&dfn1[u]>dfn1[i->vertex])
            {
                low1[u]=min(low1[u],dfn1[i->vertex]);
            }
        }
    }
    if(low1[u]==dfn1[u])
    {
        vector<int> v;
        int p;
        do
        {
            p=s1.pop();
            v.push_back(p);
        }while(p!=u);
        db_edge_connect_component.push_back(v);
        db_edge_connect_num++;
    }
}
void u_graph::Prime()
{
    edge e0;
    e0.v1=0;
    vector<edge> e;
    e.push_back(e0);
    for(int j=1;j!=ver_num;j++)
    {
            e0.v2=j;
            e0.weight=adj_matrix[0][j];
        e.push_back(e0);
    }
    sort(e);
    for(int i=0;i!=ver_num-1;i++)
    {
        e0=pop(e);
        cout<<e0.v1<<'-'<<e0.v2<<' ';
        for(int i=1;i!=e.size();i++)
        {
            if(adj_matrix[e0.v2][e[i].v2]<e[i].weight)
            {
                e[i].weight=adj_matrix[e0.v2][e[i].v2];
                e[i].v1=e0.v2;
                adjust(e,i);
            }
        }
    }
}
void u_graph::sparse_Prime()
{
    int *mark=new int[ver_num]{0};
    int *mark2=new int[ver_num]{0};
    Union u(ver_num);
    for(int i=0;i!=ver_num;i++)
    {
        if(mark[i]==0)
        {
            int min=MAX;
            int k=-1;
            for(node *j=adj_list[i].next;j!=NULL;j=j->next)
            {
                if(min>j->weight)
                {
                    min=j->weight;
                    k=j->vertex;
                }
            }
            u.merge(i,k);
            mark[i]=mark[k]=1;
        }
    }
    vector<int> f;
    for(int i=0;i!=ver_num;i++)
    {
        int k=u.find_set(i);
        if(mark2[k]==0)
        {
            f.push_back(k);
            mark2[k]=1;
        }
    }
    edge e[N][N];
    for(int i=0;i!=ver_num;i++)
    {
        for(node*j=adj_list[i].next;j!=NULL;j=j->next)
        {
            int m=u.find_set(i);
            int n=u.find_set(j->vertex);
            if(m!=n)
            {
                
                if(j->weight<e[m][n].weight)
                {
                    e[m][n].v1=e[n][m].v1=i;
                    e[m][n].v2=e[n][m].v2=j->vertex;
                    e[m][n].weight=e[n][m].weight=j->weight;
                }
            }
        }
    }
    for(auto i=f.begin();i!=f.end();i++)
    {
        for(auto j=f.begin();j!=f.end();j++)
        {
            if(*i>*j)
            {
                cout<<e[*i][*j].v1<<'-'<<e[*i][*j].v2<<' ';
            }
        }
    }
}


void u_graph::Kruskal()
{
    vector<edge> v;
    edge *e;
    edge e2;
    v.push_back(e2);
    for(int i=0;i!=ver_num;i++)
    {
        for(node*j=adj_list[i].next;j!=NULL;j=j->next)
        {
            if(i<j->vertex)
            {
                e=new edge;
                e->v1=i;
                e->v2=j->vertex;
                e->weight=j->weight;
                v.push_back(*e);
            }
        }
    }
    sort(v);
    Union u(ver_num);
    while(v.size()!=1)
    {
        e2=pop(v);
        u.merge(e2.v1, e2.v2);
    }
}
void d_graph::list_to_matrix()
{
    for(int i=0;i!=ver_num;i++)
    {
        for(int j=0;j!=ver_num;j++)
        {
            adj_matrix[i][j]=MAX;
        }
    }
    for(int i=0;i!=ver_num;i++)
    {
        for(node*j=adj_list[i].next;j!=NULL;j=j->next)
        {
            adj_matrix[i][j->vertex]=j->weight;
        }
    }
}
void u_graph::list_to_matrix()
{
    for(int i=0;i!=ver_num;i++)
    {
        for(int j=0;j!=ver_num;j++)
        {
            adj_matrix[i][j]=MAX;
        }
    }
    for(int i=0;i!=ver_num;i++)
    {
        for(node*j=adj_list[i].next;j!=NULL;j=j->next)
        {
            adj_matrix[i][j->vertex]=j->weight;
        }
    }
}
void d_graph::Dijkstra()
{
    cout<<"请输入源点:";
    int i;
    cin>>i;
    edge e0;
    e0.v1=i;
    vector<edge> e;
    e.push_back(e0);
    for(int j=0;j!=ver_num;j++)
    {
        if(j!=i)
        {
        e0.v2=j;
        e0.weight=adj_matrix[i][j];
        e.push_back(e0);
            p[j]=i;
        }
    }
    sort(e);
    for(int i=0;i!=ver_num-1;i++)
    {
        e0=pop(e);
        for(int i=1;i!=e.size();i++)
        {
            if(e0.weight+adj_matrix[e0.v2][e[i].v2]<e[i].weight)
            {
                e[i].weight=e0.weight+adj_matrix[e0.v2][e[i].v2];
                p[e[i].v2]=e0.v2;
                adjust(e,i);
            }
        }
    }
    show_Dijkstra(i);
}
void d_graph::show_Dijkstra(int i)
{
    for(int j=0;j!=ver_num;j++)
    {
        int k=j;
        while(k!=i)
        {
            cout<<k<<'<'<<'-';
            k=p[k];
        }
        cout<<k<<endl;
    }
}
void u_graph::Dijkstra()
{
    cout<<"请输入源点:";
    int i;
    cin>>i;
    flag[i]=1;
    edge e0;
    e0.v1=i;
    vector<edge> e;
    e.push_back(e0);
    for(int j=0;j!=ver_num;j++)
    {
        if(j!=i)
        {
            e0.v2=j;
            e0.weight=adj_matrix[i][j];
            e.push_back(e0);
            p[j]=i;
        }
    }
    sort(e);
    for(int i=0;i!=ver_num-1;i++)
    {
        e0=pop(e);
        for(int i=1;i!=e.size();i++)
        {
            if(e0.weight+adj_matrix[e0.v2][e[i].v2]<e[i].weight)
            {
                e[i].weight=e0.weight+adj_matrix[e0.v2][e[i].v2];
                p[e[i].v2]=e0.v2;
                adjust(e,i);
            }
        }
    }
    show_Dijkstra(i);
}
void u_graph::show_Dijkstra(int i)
{
    for(int j=0;j!=ver_num;j++)
    {
        int k=j;
        while(k!=i)
        {
            cout<<k<<'<'<<'-';
            k=p[k];
        }
        cout<<k<<endl;
    }
}
void d_graph::Floyd()
{
    for(int i=0;i!=ver_num;i++)
    {
        for(int j=0;j!=ver_num;j++)
            p2[i][j]=-1;
    }
    for(int k=0;k!=ver_num;k++)
    {
        for(int i=0;i!=ver_num;i++)
        {
            for(int j=0;j!=ver_num;j++)
            {
                if(adj_matrix[i][k]+adj_matrix[k][j]<adj_matrix[i][j])
                   {
                       adj_matrix[i][j]=adj_matrix[i][k]+adj_matrix[k][j];
                       p2[i][j]=k;
                   }
            }
        }
    }
    show_Floyd();
}
void d_show_Floyd(d_graph&g,int i,int j)
{
    int k=g.p2[i][j];
    if(k!=-1)
    {
        d_show_Floyd(g, i, k);
        cout<<'-'<<'>'<<k;;
        d_show_Floyd(g, k, j);
    }
}
void d_graph::show_Floyd()
{
    for(int i=0;i!=ver_num;i++)
    {
        for(int j=0;j!=ver_num;j++)
        {
            if(j!=i)
            {cout<<i;
            d_show_Floyd(*this, i, j);
            cout<<'-'<<'>'<<j<<endl;
            }
        }
    }
}

void u_graph::Floyd()
{
    for(int i=0;i!=ver_num;i++)
    {
        for(int j=0;j!=ver_num;j++)
            p2[i][j]=-1;
    }
    for(int k=0;k!=ver_num;k++)
    {
        for(int i=0;i!=ver_num;i++)
        {
            for(int j=0;j!=ver_num;j++)
            {
                if(adj_matrix[i][k]+adj_matrix[k][j]<adj_matrix[i][j])
                {
                    adj_matrix[i][j]=adj_matrix[i][k]+adj_matrix[k][j];
                    p2[i][j]=k;
                }
            }
        }
    }
    show_Floyd();
}
void u_show_Floyd(u_graph&g,int i,int j)
{
    int k=g.p2[i][j];
    if(k!=-1)
    {
        u_show_Floyd(g, i, k);
        cout<<'-'<<'>'<<k;;
        u_show_Floyd(g, k, j);
    }
}
void u_graph::show_Floyd()
{
    for(int i=0;i!=ver_num;i++)
    {
        for(int j=0;j!=ver_num;j++)
        {
            if(j!=i)
            {
            cout<<i;
            u_show_Floyd(*this, i, j);
            cout<<'-'<<'>'<<j<<endl;
            }
        }
    }
}
int flag3[N];
int dag_dfn[N];
int dag_low[N];
int d_graph::Topologically_sort(int u)
{
    static int dn=0;
    dn++;
    dag_low[u]=dag_dfn[u]=dn;
    s.push(u);
    flag3[u]=1;
    for(node*i=adj_list[u].next;i!=NULL;i=i->next)
    {
        if(!dag_dfn[i->vertex])
        {
            if(Topologically_sort(i->vertex)==-1)return -1;
            sq.push_back(i->vertex);
            low[u]=min(low[u],low[i->vertex]);
        }
        else if(flag3[i->vertex]==1)
        {
            low[u]=min(low[u],dfn[i->vertex]);
            return -1;
        }
    }
    if(low[u]==dfn[u])
    {
        int p;
        do
        {
            p=s.pop();
            flag3[p]=0;
        }while(p!=u);
    }
    return 1;
}
void d_graph::Dag_shortest_path()
{
    cout<<"请输入源点："<<endl;
    int i;
    cin>>i;
    if(Topologically_sort(i)==-1)
    {
        cout<<"图中存在回路："<<endl;
        return;
    }
    sq.insert(sq.begin(),i);
    for(int j=0;j!=ver_num;j++)
    {
        if(j!=i)
        {
            dag_distance[j]=MAX;
            dag_path[j]=-1;
        }
    }
    dag_distance[i]=0;
    dag_path[i]=i;
    for(auto j=sq.begin();j!=sq.end();j++)
    {
        for(node*k=adj_list[*j].next;k!=NULL;k=k->next)
        {
            if(dag_distance[k->vertex]>dag_distance[*j]+k->weight)
            {
                dag_distance[k->vertex]=dag_distance[*j]+k->weight;
                dag_path[k->vertex]=*j;
            }
        }
    }
    show_dag_path(i);
}
void d_graph::show_dag_path(int i)
{
        for(int j=0;j!=ver_num;j++)
        {
            int k=j;
            while(k!=i)
            {
                cout<<k<<'<'<<'-';
                k=dag_path[k];
            }
            cout<<k<<endl;
        }
}
