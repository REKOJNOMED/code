#include<iostream>
#include <math.h>
using namespace std;
double F(double x,double y)
{
    return -20*(y-x*x)+2*x;
}
double f(double x)
{
    return x*x+exp(-20*x)/3;
}
int main()
{
    double x,y,h;
    double k1,k2,k3,k4;
    cout<<"输入初值下x0，y0:"<<endl;
    cin>>x>>y;
    cout<<"输入区间上界及步数:"<<endl;
    double n,N;
    cin>>n>>N;
        h=(n-x)/N;
    do
    {
        k1=h*F(x,y);
        k2=h*F(x+h/2,y+k1/2);
        k3=h*F(x+h/2,y+k2/2);
        k4=h*F(x+h,y+k3);
        y=y+(k1+2*k2+2*k3+k4)/6;
        x=x+h;
        cout<<x<<"解析解"<<y<<"准确解"<<f(x)<<endl;
    }while(x<n);
}
