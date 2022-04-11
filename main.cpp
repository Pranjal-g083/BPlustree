#include <bits/stdc++.h>
using namespace std;
int data_node,index_node;

class BPlustreenode
{
public:
    bool is_data;
    int d_size,t_size;
    vector<int> v;
    vector<BPlustreenode*> child;
    BPlustreenode* parent;
    

    BPlustreenode(int s,bool flag,int t_size)
    {
        is_data=flag;


        d_size=s;
        parent=NULL;
        this->t_size=t_size;
        if(flag)
        {
            child.assign(1,NULL);
        }
    }
    bool isfull()
    {
        if(is_data)
        return v.size()==2*d_size;
        else
        return v.size()==2*t_size+1;
    }
    bool isleaf()
    {
        return is_data;
    }
    bool insert(int x,BPlustreenode*p=NULL)
    {

        if(isfull())
        {
            if(isleaf())
            {
//                 cout<<"HELLO"<<endl;
//                 cout<<v[0]<<endl;
                BPlustreenode* newnode=new BPlustreenode(d_size,true,t_size);
                int i=0;
                while(i!=v.size()&&v[i]<x) {
                    i++;
                }
                int num=v[d_size];
                v.insert(v.begin()+i,x);
                for(int i=d_size;i<=2*d_size;i++)
                {
                    newnode->insert(v[i]);
                }
                v.resize(d_size);
                data_node++;
//                cout<<"HELLO"<<endl;
                if(!parent)
                {
                    BPlustreenode* newroot=new BPlustreenode(d_size,false,t_size);

                    newroot->v.push_back(num);
//                    cout<<num<<endl;
                    newroot->child.push_back(this);
                    newroot->child.push_back(newnode);
                    this->parent=newroot;
                    newnode->parent=newroot;
//                    cout<<1<<endl;
                    newroot->parent=NULL;
//                    cout<<"DONE"<<endl;
                    index_node++;
                    return true;
                }
                else
                {
//                    cout<<"OI"<<endl;
//                    cout<<x<<endl;
                    return parent->insert(v[d_size],newnode);

                }
            }
            else
            {
                BPlustreenode* newnode=new BPlustreenode(d_size,false,t_size);
//                cout<<"OI"<<endl;
                index_node++;
                int i=0;
                while(i!=v.size()&&v[i]<x) {
                    i++;
                }

                v.insert(v.begin()+i,x);
                child.insert(child.begin()+i+1,p);
//                cout<<"OYE"<<endl;

                p->parent=this;
                int num=v[t_size];
//                cout<<"ohoi"<<endl;
                for(int i=t_size+1;i<=2*t_size+1;i++)
                {
                    newnode->v.push_back((v[i]));
                    newnode->child.push_back(child[i]);
//                    cout<<child[i]->v[0]<<endl;
                    child[i]->parent=newnode;
                }
//                cout<<"ohoi"<<endl;
                newnode->child.push_back(child[2*t_size+2]);
                child[2*t_size+2]->parent=newnode;
                v.resize(t_size);
                child.resize(t_size+1);
                if(!parent)
                {
                    BPlustreenode* newroot=new BPlustreenode(d_size,false,t_size);
                    newroot->v.push_back(num);
                    newroot->child.push_back(this);
                    newroot->child.push_back(newnode);
                    newnode->parent=newroot;
                    this->parent=newroot;
                    newroot->parent=NULL;
                    index_node++;
//                    cout<<"true"<<endl;
                    return true;
                }
                else
                {
                    return parent->insert(v[d_size],newnode);

                }
            }
        }
        else
        {
            if(isleaf())
            {
//                cout<<v.size()<<endl;

                int i=0;
                if(v.size()==0)
                {
                    v.push_back(x);
                    return false;
                }
                while(i!=v.size()&&v[i]<x)
                {
                    i++;
                }
//                cout<<i<<endl;
                v.insert(v.begin()+i,x);
                // cout<<"DONE"<<endl;
                return false;
            }
            else
            {
//                cout<<x<<endl;
                int i=0;
                while(i!=v.size()&&v[i]<x) {
                    i++;
                }
                v.insert(v.begin()+i,x);
                child.insert(child.begin()+i+1,p);
                p->parent=this;
                return false;
            }
        }
    }
    ~BPlustreenode();
};



BPlustreenode::~BPlustreenode()
{
}

class BPlustree
{
public:
    BPlustreenode* root;
    int d_size,t_size;
    BPlustree(int s,int t)
    {
        d_size=s;
        t_size=t;
        root=nullptr;
        data_node=0;
        index_node=0;
    }
    void insert(int x)
    {
        if(!root)
        {
            root=new BPlustreenode(d_size,true,t_size);
            data_node++;
            root->insert(x);
        }
        else
        {
            if(root->isleaf())
            {
//                root->insert(x);
                bool flag=root->insert(x);
//                cout<<flag<<endl<<"true"<<endl;
                if(flag)
                {
//                    cout<<"cspro"<<endl;
                    while(root->parent)
                    {
//                        cout<<root->parent->v[0]<<endl;
                        root=root->parent;
                    }
//                    root=it;
                }
            }
            else
            {
                auto it=root;
                while(!it->isleaf())
                {
                    if(x<it->v[0])
                    {
                        it=it->child[0];
                    }
                    else
                    {
                        bool flag=false;
                        for(int i=0;i<it->v.size();i++)
                        {
                            if(x<it->v[i])
                            {
                                it=it->child[i];
                                flag=true;
                                break;
                            }
                        }
                        if(flag)
                        {
                            continue;
                        }
                        else
                        {
                            it=it->child.back();
                        }
                    }
                }
//                cout<<it->v[0]<<endl;
                bool flag=it->insert(x);
//                cout<<flag<<endl<<"true"<<endl;
                if(flag)
                {
//                    cout<<"cspro"<<endl;
                    while(it->parent)
                    {
//                        cout<<it->parent->v[0]<<endl;
                        it=it->parent;
                    }
                    root=it;
                }
                
            }
        }
        
    }
    ~BPlustree()
    {
    }
};

int main()
{
    int n,m,x;
    cin>>n>>m;
    BPlustree bp(n,m);
    while (cin>>x)
    {
        if(x==1)
        {
            int num;
            cin>>num;
//            cout<<num<<endl;
            bp.insert(num);
        }
        else if(x==2)
        {
            
            cout<<index_node<<" "<<data_node<<" ";
            for(auto a:bp.root->v)
            {
                cout<<a<<" ";
            }
            cout<<endl;
        }
        else
        break;
    }
    
    
    return 0;
}