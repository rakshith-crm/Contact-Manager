#include <iostream>
#include <string.h>
#include <windows.h>
using namespace std;

//////////////////////////////////////////////////
int check_name(char *name)
{
    int i;
    for(i=0;name[i]!='\0';i++)
    {
        char c=tolower(name[i]);
        if(!((c>='a'&&c<='z') || (c=='.') || (c==' ')))
        {
            return 0;
        }
    }
    return 1;
}
int check_name1(char *name)
{
    int i;
    for(i=0;name[i]!='\0';i++)
    {
        char c=tolower(name[i]);
        if(!((c>='a'&&c<='z') || (c=='.') || (c==' ')||(c=='9')||(c=='0')))
        {
            return 0;
        }
    }
    return 1;
}
int all_num(char *number)
{
    int i;
    for(i=0;number[i]!='\0';i++)
    {
        if(!(number[i]>='0'&&number[i]<='9'))
        {
            return 0;
        }
    }
    return 1;
}
int check_number(char *number)
{
    int i;
    for(i=0;number[i]!='\0';i++)
    {
        if(!(number[i]>='0'&&number[i]<='9'))
        {
            return 0;
        }
    }
    if(i!=10)
    {
        if(i<10)
        {
            cout<<"\nThe number is less than 10 digit";
        }
        if(i>10)
        {
            cout<<"\nThe number is greater than 10 digits";
        }
        return 0;
    }
return 1;
}
inline int convert(char c)
{
    return c-'0';
}


//////////////////////////////////////////////////
//1234567890
//1234567899
struct d_node;
struct t_node
{
    t_node *t_num[10];
    d_node *d_num;

};
struct d_node
{
    char name[30];
    char number[11];
};
t_node * createTnode()
{
    t_node *N=new t_node;
    int i;
    for(i=0;i<10;i++)
    {
        N->t_num[i]=NULL;
    }
    N->d_num=NULL;
    return N;
}
d_node * createDnode()
{
    d_node *N=new d_node;
    return N;
}
d_node * createDnode(char *name,char *num)
{
    d_node *N=new d_node;
    strcpy(N->name,name);
    strcpy(N->number,num);
    return N;
}
/////////////////////////////////////////////////
class number_tree
{
private:
    t_node *root;
public:
    int insert_number(char *,char *,int i=0);
    void display_all(t_node *node);
    void display(d_node *);
    number_tree();
    t_node * getRoot();
    char * search_number(char *,int i=0);
    int delete_number(char *,int i=0);
    void modify_contact(t_node *);
    int check_for_dnode(t_node *);
    int change_name(char *,char *);
    t_node * is_number(char *);
};
int number_tree::change_name(char *number,char *to_name)
{
    t_node *t=is_number(number);
    if(t!=NULL)
    {
        strcpy(t->d_num->name,to_name);
        return 1;
    }
    else
    {
        return 0;
    }
}
t_node * number_tree::getRoot()
{
    return root;
}
number_tree::number_tree()
{
    root=createTnode();
}
int number_tree::insert_number(char *number,char *name,int a)
{
    //1234567890
    //1234567899
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
        ptr->d_num=createDnode(name,number);
        if(a==0)
        cout<<"\nContact Successfully Added...\n";
        return 1;
    }
    else
    {
        if(a==0)
        cout<<"\nNumber Already Exists...\n";
        return 0;
    }
}
void number_tree::display(d_node *node)
{
    if(node!=NULL)
    {
        cout<<"(#)"<<node->name<<endl;
        cout<<"  (*)-->"<<node->number<<endl;
    }
    else
    {
        cout<<"\nContact Does not Exits...\n";
    }
}
void number_tree::modify_contact(t_node *node)
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
            display(node->d_num);
        }
        else if(opt==2)
        {
            if(delete_number(node->d_num->number)==1)
            {
                return;
            }
        }
        else if(opt==3)
        {
            system("cls");
            cout<<"\n-------------\nEDIT CONTACT\n-------------\n";
            cout<<"(1)Change Name\n(2)Change Number\n(3)Exit\n";
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
                char number[15];
                cout<<"\nEnter New Number       : ";
                cin>>number;
                while(!check_number(number))
                {
                    cout<<"\nInvalid Number:\nRe-Enter    : ";
                    cin>>number;
                }
//                cout<<"hii";
                t_node *exists=is_number(number);
  //              cout<<"helloo...";
                if(exists==NULL)
                {
                    insert_number(number,node->d_num->name);
                    delete_number(node->d_num->number);
                    node=is_number(number);
                    cout<<"\nContact Number Updated...\n";
                }
                else
                {
                    cout<<"\nContact Already Exists...\n";
                    cout<<"\n---------------\nEXISTING CONTACT\n---------------\n";
                    display(exists->d_num);
                    cout<<"\nDo you wish to overwrite contact [yes(y) or no(n)] : ";
                    char c;
                    cin>>c;
                    if(c=='y'||c=='Y')
                    {
                        strcpy(exists->d_num->name,node->d_num->name);
                        delete_number(node->d_num->number);
                        cout<<"\nContact Overwritten Successfully...\n";
                        node=is_number(number);
                    }
                }
            }
            else if(op==3)
            {
                break;
            }
        }
        else if(opt==4)
        {
            break;
        }
        cin.ignore();
        cout<<"\nPress Enter key to continue...\n";
        cin.get();
    }
}
void number_tree::display_all(t_node *node)
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
char * number_tree::search_number(char *number,int a)
{
    int i;
    t_node *ptr=root;
    if(check_number(number))
    {
        for(i=0;i<10;i++)
        {
            if(ptr==NULL)
            {
                return NULL;
            }
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
            return ptr->d_num->name;
        }
        else
        {
            if(a==0)
            cout<<"\nContact Number Does not Exits...\n";
            return NULL;
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
        cout<<"\n\n-----------\nYOUR CONTACTS\n-----------\n\n";
        display_all(ptr);
    }
    return NULL;
}

int number_tree::check_for_dnode(t_node *node)
{
    if(node==NULL)
    {
        return 0;
    }
    int i,flag=0;
    for(i=0;i<10;i++)
    {
        if(node->t_num[i]!=NULL)
        {
            break;
        }
    }
    //i=10 if all t_num is NULL
    if(i==10)
    {
        if(node->d_num==NULL)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        for(i=0;i<10;i++)
        {
            flag=flag|check_for_dnode(node->t_num[i]);
        }
    }
    return flag;
}
int number_tree::delete_number(char *number,int i)
{
    t_node *t=is_number(number);
    if(t!=NULL)
    {
        if(i==0)
        {
            cout<<"\nAre you Sure you want to delete contact...\n";
            display(t->d_num);
            char c;
            cout<<"\nyes(y) or no(n) : ";
            cin>>c;
            if(c=='n'||c=='N')
            {
                return 0;
            }
        }
        t_node *ptr=root;
        t_node *start_ptr=root;
        int i,j,start=0;
        for(i=0;i<10;i++)
        {
            int count=0;
            for(j=0;j<10;j++)
            {
                if(ptr->t_num[j]!=NULL)
                {
                    count++;
                }
            }
//            cout<<count<<endl;
            if(count!=1)
            {
                start_ptr=ptr;
                start=i;
            }
            ptr=ptr->t_num[convert(number[i])];
        }
        t_node *temp1=start_ptr->t_num[convert(number[start])];
        start_ptr->t_num[convert(number[start])]=NULL;
        for(i=start+1;number[i]!='\0';i++)
        {
            t_node *temp2=temp1->t_num[convert(number[i])];
            if(temp2==NULL)
            {
                delete(temp1->d_num);
                delete(temp1);
                break;
            }
            delete(temp1);
            temp1=temp2;
        }
        if(i==0)
        cout<<"\nContact Successfully deleted...\n";
        return 1;
    }
}

t_node * number_tree::is_number(char *number)
{
    t_node *ptr=root;
    int i;
    for(i=0;i<10;i++)
    {
        if(ptr==NULL)
        {
            return NULL;
        }
        if(ptr->t_num[convert(number[i])]!=NULL)
        {
            ptr=ptr->t_num[convert(number[i])];
        }
        else
        {
            return 0;
        }
    }
    if(ptr->d_num!=NULL)
    {
        return ptr;
    }
    return NULL;
}


