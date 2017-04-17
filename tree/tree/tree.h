#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;
#define N  1000
template <typename T>
class   Queue
{
public:
    vector<T> queue;
    void enqueue(T t){queue.push_back(t);}
    T dequeue(){ T t=*queue.begin();queue.erase(queue.begin());return t;}
    int empty(){if(queue.size()==0)return 1;else return 0;}
    int size(){return (int)queue.size();}
};
class tree
{
public:
	char data;
	tree*lchild;
	tree* rchild;
	tree* parent;
	char ltag;
	char rtag;
	tree() { data = 0; lchild = NULL; rchild = NULL; ltag = 0; rtag = 0; parent = NULL; }
};
typedef tree btree;
tree *p=NULL;
tree *t0[N] = { NULL };
tree* Creat_tree()
{
	fstream file("tree.txt", ios::in);
	int i=0; char t;
	while (!file.eof())
	{
		file >> i >> t;
		t0[i] = new tree;
		t0[i]->data = t;
	}
	for (int j = 1; j <= i; j++)
	{
		if (t0[j] != NULL)
		{
			if (t0[2 * j] != NULL)
			{
				t0[j]->lchild = t0[2 * j];
				t0[2 * j]->parent = t0[j];
			}
			if (t0[2 * j + 1] != NULL)
			{
				t0[j]->rchild = t0[2 * j + 1];
				t0[2 * j + 1]->parent = t0[j];
			}
		}
	}
	return t0[1];
}
void Preorder_tree1(tree *t)
{
	if (t != NULL)
	{
		if (t->lchild == NULL&&t->ltag==0)
		{
			t->lchild = p;
			t->ltag = 1;
		}
		if (p->rchild == NULL&&p->rtag==0)
		{
			p->rchild = t;
			p->rtag = 1;
		}
		p = t;
        if(t->ltag==0)
		Preorder_tree1(t->lchild);
        if(t->rtag==0)
		Preorder_tree1(t->rchild);
	}
}
btree* Preorder_tree(tree*t)
{
	tree * head = new tree;
	p = head;
	Preorder_tree1(t);
	p->rchild = head;
    p->rtag=1;
	return head;
}
btree* Pre_next(btree* t)
{
	if(t->rtag==1)
        return t->rchild;
    else if(t->ltag==0)
        return t->lchild;
    else
        return t->rchild;
}
void Pre_ergodic(btree *t)
{
	tree* h = t;
    cout<<t->data<<' ';
	t = Pre_next(t);
	while (t != h)
	{
		cout << t->data<<' ';
		t = Pre_next(t);
	}
    cout<<endl;
}
void Postorder_tree1(tree* t)
{
	if (t != NULL)
	{
		Postorder_tree1(t->lchild);
		Postorder_tree1(t->rchild);
		if (t->lchild == NULL&&t->ltag==0)
		{
			t->lchild = p;
			t->ltag = 1;
		}
		if(p->rchild ==NULL&&p->rtag==0)
		{
			p->rchild = t;
			p->rtag = 1;
		}
		p = t;
	}
}
tree* Postorder_tree(tree *t)
{
	tree *head = new tree;
	p = head;
	Postorder_tree1(t);
    p->rchild=head;
    p->rtag=1;
	return head;
}
tree* Post_next(tree *t)
{
	if (t->rtag == 1)
		return t->rchild;
	else
    {
        if(t->parent->ltag==0&&t->parent->lchild==t&&t->parent->rtag==0)
        {
            t=t->parent->rchild;
            while(t->ltag==0||t->rtag==0)
            {
                while(t->ltag==0) t=t->lchild;
                if(t->rtag==0)
                    t=t->rchild;
            }
            return t;
        }
        else
            return t->parent;
    }
}
void Post_ergodic(tree *t)
{
	tree *h = t;
	t = Post_next(t);
	while (t != h)
	{
		cout << t->data<<' ';
		t = Post_next(t);
	}
    cout<<t->data<<' ';
    cout<<endl;
}
int Height(tree *t)
{
    if(t!=NULL)
    {
        int m,n;
        m=Height(t->lchild);
        n=Height(t->rchild);
        return m>n? m+1:n+1;
    }
    else
        return 0;
}
void print(tree *t)
{
    int h=Height(t);
    Queue<tree*> q;
    int w=(int)pow(2,h);
    q.enqueue(t);
    while(w!=1)
    {
        int flag=0;
        for(int i=q.size();i!=0;i--)
        {
            tree * t=q.dequeue();
            if(t!=NULL)
            {
                if(flag==0)
                {cout<<setw(w)<<t->data; flag=1;}
                else
                    cout<<setw(2*w)<<t->data;
                q.enqueue(t->lchild);
                q.enqueue(t->rchild);
            }
            else
            {
                if(flag==0)
                {cout<<setw(w)<<' '; flag=1;}
                else
                    cout<<setw(2*w)<<' ';
                q.enqueue(NULL);
                q.enqueue(NULL);
            }
        }
        cout<<endl;
        w=w/2;
    }
}
class forest
{
public:
    char data;
    forest* lchild;
    forest* rbrother;
    int brother_num;
    forest() { data = 0; lchild = rbrother = NULL; }
};
forest* Creat_forest()
{
    fstream file("forest.txt",ios::in);
    int count;
    char c;
    forest *f,*p=NULL;
    Queue<forest*> q;
    file>>count;
    forest*head=NULL;
    for(int i=count;i!=0;i--)
    {
        file>>c;
        f=new forest;
        if(p==NULL) head=f;
        else p->rbrother=f;
        f->data=c;
        p=f;
        q.enqueue(f);
    }
    while(!file.eof()&&file>>count)
    {
        p=NULL;
        forest* t=q.dequeue();
        for(int i=count;i!=0;i--)
        {
            
        if(p==NULL)
        {
            file>>c;
            f=new forest;
            t->lchild=f;
            f->data=c;
            p=f;
            q.enqueue(f);
        }
        else
        {
            file>>c;
            f=new forest;
            if(p!=NULL) p->rbrother=f;
            f->data=c;
            p=f;
            q.enqueue(f);
        }
        }
    }
    return head;
}
void tree_to_forest(tree *t,forest* &f)
{
	if (t != NULL)
	{
		f = new forest;
		f->data = t->data;
        if(t->ltag==0)
		tree_to_forest(t->lchild, f->lchild);
        if(t->rtag==0)
		tree_to_forest(t->rchild, f->rbrother);
	}
}
void print(forest* f)
{
    Queue<forest*> q;
    forest *t=f;
    while(t!=NULL)
    {
        q.enqueue(t);
        t=t->rbrother;
    }
    int count=1;
    while(!q.empty())
    {
        int i=count;
        count=0;
        for(;i!=0;i--)
        {
            cout<<'|';
            int flag=0;
            t=q.dequeue();
            int count2=0;
            for(forest*i =t;i!=NULL;i=i->rbrother)
            {
                count2++;
            }
            for(int j=count2;j!=0;j--)
            {
                if(flag==0) flag=1;
                else t=q.dequeue();
                cout<<t->data;
                forest *p=t->lchild;
                if(p==NULL) q.enqueue(p);
                while(p!=NULL)
                {
                    q.enqueue(p);
                    p=p->rbrother;
                }
                count++;
            }
            cout<<'|'<<' ';
        }
        cout<<endl;
    }
}
void forest_to_tree(forest *f, tree*&t)
{
	if (f != NULL)
	{
		t = new tree;
		t->data = f->data;
		forest_to_tree(f->lchild, t->lchild);
		forest_to_tree(f->rbrother, t->rchild);
	}
}
class huffman_tree
{
public:
    char data;
    huffman_tree* lchild;
    huffman_tree* rbrother;
    int frequency;
    string code;
    huffman_tree(){data=frequency=0; lchild=rbrother=NULL;}
};
void swap(huffman_tree *&h1,huffman_tree *&h2)
{
    huffman_tree *temp;
    temp=h1;
    h1=h2;
    h2=temp;
}
void sort(vector<huffman_tree*> & H)
{
    for(int i=(int)H.size()/2;i<=H.size()-1;i++)
    {
        for(int j=i;j!=1;j=j/2)
        {
            if(H[j]->frequency<H[j/2]->frequency)
                swap(H[j],H[j/2]);
        }
    }
}
huffman_tree* pop(vector<huffman_tree*>&H)
{
    huffman_tree *h=*(H.begin()+1);
    H.erase(H.begin()+1);
    H.insert(H.begin()+1,*(H.end()-1));
    H.erase(H.end()-1);
    for(int i=1;2*i<=H.size()-1;)
    {
        if(2*i+1<=H.size()-1)
        {
            if(H[2*i]->frequency<H[2*i+1]->frequency&&H[2*i]->frequency<H[i]->frequency)
        {
            swap(H[i],H[2*i]);
            i=2*i;
        }
        else if(H[2*i+1]->frequency<H[2*i]->frequency&&H[2*i+1]->frequency<H[i]->frequency)
        {
            swap(H[2*i+1],H[i]);
            i=2*i+1;
        }
        else
            break;
        }
        else
        {
            if(H[2*i]->frequency<H[i]->frequency) {swap(H[2*i],H[i]); i=2*i;}
            else
                break;
        }
    }
    return h;
}
huffman_tree huffman_tree_c[256];
void init_huffman_tree()
{
    fstream file("source.txt",ios::in);
    fstream file1("huffman_tree.txt",ios::out);
    char c;
    while(!file.eof()&&file.get(c))
    {
        huffman_tree_c[c].data=c;
        huffman_tree_c[c].frequency++;
    }
    for(int i=0;i!=N;i++)
    {
        if(huffman_tree_c[i].frequency!=0)
        file1<<huffman_tree_c[i].data;
    }
    file.close();
    file1.close();
}
void huffman_encoding(huffman_tree *h,int k)
{
    if(h!=NULL)
    {
        huffman_tree* p=h->lchild;
        if(p!=NULL)
        for(char i='0';i!=k+'0';i++)
        {
            p->code+=h->code+i;
            huffman_encoding(p,k);
            p=p->rbrother;
        }
    }
}
void Txt_huffman_encoding()
{
    fstream file1("source.txt",ios::in);
    fstream file2("Txt_huffman_encoding.txt",ios::out);
    char c;
    while(!file1.eof()&&file1.get(c))
    {
        file2<<huffman_tree_c[c].code;
    }
    file1.close();
    file2.close();
}
void Txt_huffman_decoding(huffman_tree* h)
{
    fstream file1("Txt_huffman_encoding.txt",ios::in);
    fstream file2("Txt_huffman_decoding.txt",ios::out);
    char c;
    huffman_tree *p=h;
    while(!file1.eof()&&file1>>c)
    {
        int j=c-'0';
        p=p->lchild;
        for(;j!=0;j--)
        {
            p=p->rbrother;
        }
        if(p->data!=0)
        {
            file2<<p->data;
            p=h;
        }
    }
    file1.close();
    file2.close();
}
void insert(vector<huffman_tree*>&H,huffman_tree *h)
{
    H.push_back(h);
    for(int i=(int)H.size()-1;i!=1;i=i/2)
    {
        if(H[i]->frequency<H[i/2]->frequency)
            swap(H[i],H[i/2]);
    }
}
huffman_tree* Creat_huffman_tree()
{
    init_huffman_tree();
    fstream file("huffman_tree.txt",ios::in);
    vector<huffman_tree*> H;
    huffman_tree *h=NULL;
    H.push_back(h);
    int count=0;
    char c;
    while(!file.eof()&&file.get(c))
    {
        H.push_back(&huffman_tree_c[c]);
        count++;
    }
    cout<<"请输入哈夫曼树的度"<<endl;
    int k;
    cin>>k;
    int k0=(count-1)%(k-1);
    if(k0!=0)
    {
        h=new huffman_tree;
        h->data=0;
        h->frequency=0;
        for(int j=k-1-k0;j!=0;j--)
        {
            H.push_back(h);
        }
    }
    sort(H);
    while(H.size()!=2)
    {
        h=new huffman_tree;
        h->data=0;
        h->frequency=0;
        huffman_tree *h1=pop(H);
        h->lchild=h1;
        h->frequency+=h1->frequency;
        for(int i=1;i!=k;i++)
        {
            h1->rbrother=pop(H);
            h1=h1->rbrother;
            h->frequency+=h1->frequency;
        }
        insert(H, h);
    }
    huffman_encoding(H[1], k);
    return H[1];
}
void print(huffman_tree *f)
{
    Queue<huffman_tree*> q;
    huffman_tree *t=f;
    while(t!=NULL)
    {
        q.enqueue(t);
        t=t->rbrother;
    }
    int count=1;
    while(!q.empty())
    {
        int i=count;
        count=0;
        for(;i!=0;i--)
        {
            cout<<'|';
            int flag=0;
            t=q.dequeue();
            int count2=0;
            for(huffman_tree*i =t;i!=NULL;i=i->rbrother)
            {
                count2++;
            }
            for(int j=count2;j!=0;j--)
            {
                if(flag==0) flag=1;
                else t=q.dequeue();
                cout<<t->data;
                huffman_tree *p=t->lchild;
                if(p==NULL) q.enqueue(p);
                while(p!=NULL)
                {
                    q.enqueue(p);
                    p=p->rbrother;
                }
                count++;
            }
            cout<<'|'<<' ';
        }
        cout<<endl;
    }
}
class adp_huffman_tree
{
public:
    char val;
    int frequency;
    int order;
    
    adp_huffman_tree* lchild;
    adp_huffman_tree* rchild;
    adp_huffman_tree* parent;
    
    adp_huffman_tree(){val=frequency=order=0; lchild=rchild=parent=NULL;}
};
adp_huffman_tree chr[256];
vector<vector<adp_huffman_tree*>> adp_huffman_tree_order;
void swap(adp_huffman_tree &ah1,adp_huffman_tree &ah2)
{
    adp_huffman_tree* t1,*t2=NULL;
    auto i=adp_huffman_tree_order[ah1.frequency].begin();
    for(;i!=adp_huffman_tree_order[ah1.frequency].end();i++)
    {
        if((*i)->order==ah1.order) {break;}
    }
    if(ah1.parent->lchild->order==ah1.order && ah2.parent->lchild->order==ah2.order)
    {
        t1=ah1.parent->lchild;
        t2=ah1.parent;
        ah1.parent->lchild=ah2.parent->lchild;
        ah1.parent=ah2.parent;
        ah2.parent->lchild=t1;
        ah2.parent=t2;
    }
    else if(ah1.parent->lchild->order==ah1.order && ah2.parent->rchild->order==ah2.order)
    {
        t1=ah1.parent->lchild;
        t2=ah1.parent;
        ah1.parent->lchild=ah2.parent->rchild;
        ah1.parent=ah2.parent;
        ah2.parent->rchild=t1;
        ah2.parent=t2;
    }
    else if(ah1.parent->rchild->order==ah1.order && ah2.parent->lchild->order==ah2.order)
    {
        t1=ah1.parent->rchild;
        t2=ah1.parent;
        ah1.parent->rchild=ah2.parent->lchild;
        ah1.parent=ah2.parent;
        ah2.parent->lchild=t1;
        ah2.parent=t2;
    }
    else
    {
        t1=ah1.parent->rchild;
        t2=ah1.parent;
        ah1.parent->rchild=ah2.parent->rchild;
        ah1.parent=ah2.parent;
        ah2.parent->rchild=t1;
        ah2.parent=t2;
    }
    int temp;
    temp=ah1.order;
    ah1.order=ah2.order;
    ah2.order=temp;
    *i=*(adp_huffman_tree_order[ah1.frequency].end()-1);
}
void init()
{
    vector<adp_huffman_tree *> v;
    for(int i=0;i!=256;i++)
        adp_huffman_tree_order.push_back(v);
    return;
}
void order_insert(adp_huffman_tree *ah)
{
    while(ah->parent!=NULL)
    {
        if(ah->frequency!=0)
        {
             if(ah->order!=(*(adp_huffman_tree_order[ah->frequency].end()-1))->order&&ah->parent->order!=(*(adp_huffman_tree_order[ah->frequency].end()-1))->order)
           {
              swap(*ah,*(*(adp_huffman_tree_order[ah->frequency].end()-1)));
           }
                adp_huffman_tree_order[ah->frequency].erase(adp_huffman_tree_order[ah->frequency].end()-1);
        }
        ah->frequency++;
        if(adp_huffman_tree_order[ah->frequency].size()!=0)
        for(auto i=adp_huffman_tree_order[ah->frequency].begin();i!=adp_huffman_tree_order[ah->frequency].end();i++)
        {
            if((*i)->order>ah->order) { adp_huffman_tree_order[ah->frequency].insert(i,ah);break;}
        }
        else
            adp_huffman_tree_order[ah->frequency].push_back(ah);
        ah=ah->parent;
    }
    ah->frequency++;
}
void encoding(fstream &file,adp_huffman_tree *ah,int flag)
{
    string s,s1;
    while(ah->parent!=NULL)
    {
        if(ah->parent->lchild==ah)
            s+='0';
        else
            s+='1';
        ah=ah->parent;
    }
    for( int i=(int)s.size()-1;i>=flag+0;i--)
    {
        s1+=s[i];
    }
    file<<s1;
    return;
}
void adp_huffman_tree_Encoding()
{
    init();
    fstream file("adaptive_huffman_tree.txt",ios::in);
    fstream file2("encoding.txt",ios::out);
    char c;
    adp_huffman_tree *nty=new adp_huffman_tree;
    nty->order=255;
    while(!file.eof()&&file.get(c))
    {
        if(chr[c].val==0)
        {
            chr[c].val=c;
            nty->lchild=new adp_huffman_tree;
            nty->lchild->order=nty->order-2;
            nty->lchild->parent=nty;
            nty->rchild=&chr[c];
            chr[c].order=nty->order-1;
            chr[c].parent=nty;
            nty=nty->lchild;
            encoding(file2,&chr[c],1);
            order_insert(&chr[c]);
            file2<<c;
        }
        else
        {
            encoding(file2,&chr[c],0);
            order_insert(&chr[c]);
        }
    }
    file.close();
    file2.close();
    
}
adp_huffman_tree chr2[N];
void adp_huffman_tree_Decoding()
{
    adp_huffman_tree_order.clear();
    init();
    fstream file("encoding.txt",ios::in);
    fstream file1("decoding.txt",ios::out);
    char c;
    adp_huffman_tree *nty=new adp_huffman_tree;
    adp_huffman_tree *root=nty;
    nty->order=255;
    while(!file.eof())
    {
        adp_huffman_tree *p=root;
        if(p->frequency==0&&file.get(c))
        {
            file1<<c;
            chr2[c].val=c;
            nty->lchild=new adp_huffman_tree;
            nty->lchild->order=nty->order-2;
            nty->lchild->parent=nty;
            nty->rchild=&chr2[c];
            chr2[c].order=nty->order-1;
            chr2[c].parent=nty;
            nty=nty->lchild;
            order_insert(&chr2[c]);
        }
        else
        {
            while(!(p->lchild==NULL&&p->rchild==NULL)&&file.get(c))
            {
                if(c=='1')
                    p=p->rchild;
                if(c=='0')
                    p=p->lchild;
            }
            if(p->frequency==0&&file.get(c))
            {
                file1<<c;
                chr2[c].val=c;
                nty->lchild=new adp_huffman_tree;
                nty->lchild->order=nty->order-2;
                nty->lchild->parent=nty;
                nty->rchild=&chr2[c];
                chr2[c].order=nty->order-1;
                chr2[c].parent=nty;
                nty=nty->lchild;
                order_insert(&chr2[c]);
            }
            else
            {
                file1<<p->val;
                order_insert(&chr2[p->val]);
            }
        }
    }
}
