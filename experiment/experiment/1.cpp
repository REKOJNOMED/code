#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
double f(double x)
{
    return 2/(1+x*x);
}
int main()
{
    vector<double> T;
    double a ,b,e;
    cin>>a>>b;
    e=10e-6;
    double h,H,temp;
    int m,i;
    h=b-a;
    m=4;
    i=1;
    T.push_back((h*f(a)+h*f(b))/2);
    cout<<T[0]<<endl;
    do
    {
        temp=T[0];
        int k=1;
        H=0;
        while(a+(2*k-1)*h/2<b)
        {
            H+=h*f(a+(2*k-1)*h/2);
            k++;
        }
        T.push_back((T[i-1]+H)/2);
        cout<<T[i]<<' ';
        for(int j=i-1;j>=0;j--)
        {
            T[j]=(m*T[j+1]-T[j])/(m-1);
            cout<<T[j]<<' ';
        }
        cout<<endl;
        h=h/2;
        m*=4;
        i++;
    }while(fabs(temp-T[0])>=e);
}
