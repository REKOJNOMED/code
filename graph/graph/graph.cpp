#include "graph.hpp"
int main()
{
    u_graph ug(7,8);
    Creat_ug_list(ug);
    ug.list_to_matrix();
    cout<<"无向图点双连通展示如下："<<endl;
    ug.U_vertex_Tarjan(0,0);
    for(int i=0;i!=ug.db_vertex_connect_component.size();i++)
    {
        cout<<"双连通分量"<<i+1<<':'<<endl;
        for(auto j=ug.db_vertex_connect_component[i].begin();j!=ug.db_vertex_connect_component[i].end();j++)
        {
            cout<<*j<<' ';
        }
        cout<<endl;
    }
    cout<<"无向图边双连通展示如下："<<endl;
    ug.U_edge_Tarjan(0,0);
    for(int i=0;i!=ug.db_edge_connect_component.size();i++)
    {
        cout<<"双连通分量"<<i+1<<':'<<endl;
        for(auto j=ug.db_edge_connect_component[i].begin();j!=ug.db_edge_connect_component[i].end();j++)
        {
            cout<<*j<<' ';
        }
        cout<<endl;
    }
    cout<<"无向图Prime算法最小生成树如下："<<endl;
    ug.Prime();
    cout<<endl;
    cout<<"稀疏图Prime算法如下："<<endl;
    ug.sparse_Prime();
    cout<<endl;
    cout<<"无向图Kruskal算法最小生成树如下："<<endl;
    ug.Kruskal();
    cout<<endl;
    cout<<"无向图Dijkstra算法最短路径如下："<<endl;
    ug.Dijkstra();
    cout<<"无向图Floyd算法最短路径如下："<<endl;
    ug.Floyd();
    d_graph dg(5,8);
    Creat_dg_list(dg);
    dg.list_to_matrix();
    cout<<"有向图强连通展示如下："<<endl;
    dg.D_Tarjan(0);
    for(int i=0;i!=dg.st_connect_component.size();i++)
    {
        cout<<"强连通分量"<<i+1<<':'<<endl;
        for(auto j=dg.st_connect_component[i].begin();j!=dg.st_connect_component[i].end();j++)
        {
            cout<<*j<<' ';
        }
        cout<<endl;
    }
    cout<<"有向图Dijkstra算法最短路径如下："<<endl;
    dg.Dijkstra();
    cout<<"有向图Floyd算法最短路径如下："<<endl;
    dg.Floyd();
    cout<<"有向无环图最短路径如下："<<endl;
    dg.Dag_shortest_path();
}
