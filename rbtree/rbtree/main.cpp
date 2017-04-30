#include "rbtree.h"
int main()
{
    rbtree* t=Creat_RB_tree();
    print(t);
    int k;
    while(1)
    {
        cin>>k;
        t=RB_delete(t,k);
        print(t);
    }
}
