#include <iostream>
#include<math.h>
using namespace std;
double F(double x)
{
    return x*x-2*x*exp(-x)+exp(-2*x);
}
double DF(double x)
{
    return 2*x+(2*x-2)*exp(-x)-2*exp(-2*x);
}
int main()
{
    double x,x1;
    double e1=10e-6;
    double e2=10e-4;
    double f,df;
    cout<<"请输入初值："<<endl;
    cin>>x;
    for(int i=0;i!=20;i++)
    {
        f=F(x);
        df=DF(x);
        if(fabs(f)<e1) {cout<<x<<endl;break;}
        if(fabs(df)<e2) {cout<<"Failed!"<<endl;break;}
        x1=x;
        x=x-f/df;
        if(fabs(x1-x)<e1) {cout<<x<<endl;break;}
    }
    cout<<F(x);
}
