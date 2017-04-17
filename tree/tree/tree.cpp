#include "tree.h"
typedef tree btree;
int main()
{
    tree *t=Creat_tree();
//    btree *Pre_btree=Preorder_tree(t);
//    Pre_ergodic(Pre_btree);
//    tree *t1=Creat();
//    btree *Post_btree=Postorder_tree(t1);
//    Post_ergodic(Post_btree);
    forest*f;
    tree_to_forest(t,f);
    tree *t1;
    forest_to_tree(f, t1);
}
