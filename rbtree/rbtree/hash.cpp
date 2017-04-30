#include "hash.h"
int main()
{
    fstream file("hash.txt",ios::in);
    Hash hash;
    hash.Init_server();
    int data;
    for(int i=0;i!=20;i++)
    {
        file>>data;
        hash.Add_data(data);
    }
    for(int j=0;j!=hash.virtual_server_pos.size();j++)
    {
        int i=hash.virtual_server_pos[j];
        if(hash.node[i].flag==1)
        {
            cout<<hash.node[i].virtual_service.virtual_server_mark<<"   "<<i<<endl;
            print(hash.node[i].virtual_service.server->machine);
        }
    }
    cout<<"增加一个服务器示例如下："<<endl;
    hash.Add_server();
    for(int j=0;j!=hash.virtual_server_pos.size();j++)
    {
        int i=hash.virtual_server_pos[j];
        if(hash.node[i].flag==1)
        {
            cout<<hash.node[i].virtual_service.virtual_server_mark<<"   "<<i<<endl;
            print(hash.node[i].virtual_service.server->machine);
        }
    }
    cout<<"减少一个服务器示例如下："<<endl;
    string s;
    cout<<"输入删减服务器的编号"<<endl;
    cin>>s;
    hash.Delete_server(s);
    for(int j=0;j!=hash.virtual_server_pos.size();j++)
    {
        int i=hash.virtual_server_pos[j];
        if(hash.node[i].flag==1)
        {
            cout<<hash.node[i].virtual_service.virtual_server_mark<<"   "<<i<<endl;
            print(hash.node[i].virtual_service.server->machine);
        }
    }
    cout<<"删除数据示例如下："<<endl;
    int data2;
    cin>>data2;
    hash.Delete_data(data2);
        for(int j=0;j!=hash.virtual_server_pos.size();j++)
        {
            int i=hash.virtual_server_pos[j];
            if(hash.node[i].flag==1)
            {
                cout<<hash.node[i].virtual_service.virtual_server_mark<<"   "<<i<<endl;
                print(hash.node[i].virtual_service.server->machine);
            }
        }
    cout<<"查找数据示例如下："<<endl;
    cin>>data2;
    hash.Find(data2);

}
