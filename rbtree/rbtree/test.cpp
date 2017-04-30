#include "md5.h"
#include <iostream>
using namespace std;
int main()
{
    string s;
    s=MD5("a").toString();
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
    cout<<(m1+m2+m3+m4)%100;
}
