#include <iostream>
#include <string.h>
#include <windows.h>
using namespace std;

//////////////////////////////////////////////////
int all_num(char *number)
{
    int i,f=0;
    for(i=0;number[i]!='\0';i++)
    {
        if(!(number[i]>='0'&&number[i]<='9'))
        {
            f=1;
            break;
        }
    }
    if(f==0)
    {
        return 1;
    }
    return 0;

}
int check_number(char *number)
{
    int i;
    for(i=0;number[i]!='\0';i++)
    {
        if(!(number[i]>='0'&&number[i]<='9'))
        {
            break;
        }
    }
    if(i!=10)
    {
        return 0;
    }
return 1;
}
int convert(char c)
{
    return c-'0';
}


//////////////////////////////////////////////////

struct d_node;
struct t_node
{
    t_node *t_num[10];
    d_node *d_num;

};
struct d_node
{
    char name[30];
};
t_node * createTnode()
{
    t_node *N=new t_node;
    int i;
    for(i=0;i<10;i++)
    {
        N->d_num=NULL;
        N->t_num[i]=NULL;
    }
    return N;
}
d_node * createDnode()
{
    d_node *N=new d_node;
    return N;
}
d_node * createDnode(char *n)
{
    d_node *N=new d_node;
    strcpy(N->name,n);
    return N;
}
/////////////////////////////////////////////////
class contact_tree
{
private:
    t_node *root;
public:
    void insert_number(char *,char *);
    void display_all(t_node *node);
    void display(d_node *);
    contact_tree();
    t_node * getRoot();
    void search_number(char *);
    void delete_number(char *);
    void modify_contact(t_node *);
};
t_node * contact_tree::getRoot()
{
    return root;
}
contact_tree::contact_tree()
{
    root=createTnode();
}
void contact_tree::insert_number(char *number,char *name)
{
    t_node *ptr=root;
    int i;
    for(i=0;i<10;i++)
    {
        if(ptr->t_num[convert(number[i])]==NULL)
        {
            ptr->t_num[convert(number[i])]=createTnode();
        }
        ptr=ptr->t_num[convert(number[i])];
    }
    if(ptr->d_num==NULL)
    {
        ptr->d_num=createDnode(name);
        cout<<"\nContact Successfully Added...\n";
    }
    else
    {
        cout<<"\nNumber Already Exists...\n";
    }
}
void contact_tree::display(d_node *node)
{
    if(node!=NULL)
    {
        cout<<"(#)"<<node->name<<endl;
    }
    else
    {
        cout<<"\nContact Does not Exits...\n";
    }
}
void contact_tree::modify_contact(t_node *node)
{
    if(node->d_num==NULL)
    {
        cout<<"\nContact Does not Exits...\n";
        return;
    }
    while(1)
    {
        system("cls");
        cout<<"\n-------------\nYOUR CONTACT\n-------------\n";
        cout<<"\n(1)View Contact\n(2)Delete Contact\n(3)Edit\n(4)goto home\n";
        int opt;
        cin>>opt;
        if(opt==1)
        {
            cout<<"\n-------------\nYOUR CONTACT\n-------------\n";
            display(node->d_num);
        }
        else if(opt==2)
        {
            delete(node->d_num);
            node->d_num=NULL;
            cout<<"\nContact Deleted Successfuly...\n";
        }
        else if(opt==3)
        {
            system("cls");
            cout<<"(1)Change Name\n(2)Exit\n";
            int op;
            cin>>op;
            if(op==1)
            {
                char name[30];
                cout<<"\nEnter New Name : ";
                cin.ignore();
                cin.getline(name,30);
                strcpy(node->d_num->name,name);

            }
            else if(op==2)
            {
                break;
            }
        }
        else if(opt==4)
        {
            break;
        }
        if(node->d_num==NULL)
        {
            cout<<"\nReturning to home...\n";
            break;
        }
        if(opt!=3)
        {
            cin.ignore();
        }
        cout<<"\nEnter any key to continue...\n";
        cin.get();
    }
}
void contact_tree::display_all(t_node *node)
{
    int i;
    if(node==NULL)
    {
        return;
    }
    if(node->d_num!=NULL)
    {
        display(node->d_num);
    }
    for(i=0;i<10;i++)
    {
        display_all(node->t_num[i]);
    }
}
void contact_tree::search_number(char *number)
{
    int i;
    t_node *ptr=root;
    if(check_number(number))
    {
        for(i=0;i<10;i++)
        {
            if(ptr->t_num[convert(number[i])]!=NULL)
            {
                ptr=ptr->t_num[convert(number[i])];
            }
            else
            {
                break;
            }
        }
        if(i==10 && ptr->d_num!=NULL)
        {
            modify_contact(ptr);
        }
        else
        {
            cout<<"\nContact Number Does not Exits...\n";
        }
    }
    else if(all_num(number))
    {
        for(i=0;number[i]!='\0';i++)
        {
            if(ptr->t_num[convert(number[i])]!=NULL)
            {
                ptr=ptr->t_num[convert(number[i])];
            }
            else
            {
                break;
            }
        }
        display_all(ptr);
    }
}

void contact_tree::delete_number(char *number)
{
    int i;
    t_node *ptr=root;
    for(i=0;i<9;i++)
    {
        if(ptr->t_num[convert(number[i])]!=NULL)
        {
            ptr=ptr->t_num[convert(number[i])];
        }
        else
        {
            break;
        }
    }
    if(i==10)
    {
        if(ptr->d_num!=NULL)
        {
            cout<<"\n-------------\nYOUR CONTACT\n-------------\n";
            display(ptr->d_num);
            char c;
            cout<<"\n\nAre you are you want to delete contact (y or n) : ";
            cin>>c;
            if(c=='y')
            {
                delete(ptr->d_num);
                ptr->d_num=NULL;
                cout<<"\nContact Deleted...\n";
            }
        }
    }
    else
    {
        cout<<"\nContact Number Does not Exits...\n";
    }
}






