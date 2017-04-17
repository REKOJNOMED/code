#include<iostream>
#include<vector>
using namespace std;
double f(double x)
{
    return x*x*x;
}
int main()
{
    double x,y;
    vector<double> xi;
    vector<double> yi;
    int n;
    cout<<"请输入数据数目"<<endl;
    cin>>n;
    cout<<"请输入点："<<endl;
    for(int i=0;i!=n;i++)
    {
        cin>>x>>y;
        xi.push_back(x);
        yi.push_back(y);
    }
    cout<<"请输入待求函数值的自变量："<<endl;
    while(1)
    {
        cin>>x;
        double y=0;
        for(int i=0;i!=xi.size();i++)
        {
            double l=1;
            for(int j=0;j!=xi.size();j++)
            {
                if(j!=i)
                {
                    l*=(x-xi[j])/(xi[i]-xi[j]);
                }
            }
            y+=yi[i]*l;
        }
        cout<<"函数值为："<<y<<endl;
    }
}
