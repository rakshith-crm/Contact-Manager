#include <iostream>
#include <string.h>
using namespace std;

struct node
{
    char num[11];
    node *next;
    node *prev;
};
node * create_node(char *num)
{
    node *N=new node;
    strcpy(N->num,num);
    N->next=NULL;
    N->prev=NULL;
    return N;
}
class linked_list
{
private:
    node *start;
    node *end;
    int no_of_numbers;
public:
    void insert_end(char *);
    ~linked_list();
    linked_list(linked_list &l);
    char * operator [](int);
    void insert_end(linked_list);
    int delete_ele(char *);
    node *get_start();
    node * get_end();
    int get_count();
    int is_empty();
    void display();
    char * delete_last(int retain_memory=0);
    void alter(int,char *);
    linked_list();
};
linked_list::linked_list(linked_list &l)
{
    start=NULL;
    end=NULL;
    no_of_numbers=0;
    int i,n=l.get_count();
    for(i=0;i<n;i++)
    {
        insert_end(l[i]);
    }
}
linked_list::~linked_list()
{
    node *ptr=start;
    while(ptr!=NULL)
    {
        node *temp=ptr->next;
        delete(ptr);
        ptr=temp;
    }
}
char * linked_list::operator[](int index)
{
    node *ptr=start;
    if(index>=no_of_numbers)
    {
        return end->num;
    }
    if(index<0)
    {
        return start->num;
    }
    while(index-->0)
    {
        ptr=ptr->next;
    }
    return ptr->num;
}
char * linked_list::delete_last(int retain_memory)
{
    node *temp=end;
    static char num[11];
    strcpy(num,temp->num);
    end=end->prev;
    if(end==NULL)
    {
        start=NULL;
    }
    else
    {
        end->next=NULL;
    }
    if(retain_memory==0)
    {
        delete(temp);
    }
    return num;
}
inline int linked_list::get_count()
{
    return no_of_numbers;
}
node * linked_list::get_end()
{
    return end;
}
node * linked_list::get_start()
{
    return start;
}
linked_list::linked_list()
{
    start=NULL;
    end=NULL;
    no_of_numbers=0;
}
void linked_list::insert_end(char *num)
{
    node *N=create_node(num);
    if(start==NULL)
    {
        start=N;
        end=N;
    }
    else
    {
        end->next=N;
        N->prev=end;
        end=N;
    }
    no_of_numbers++;
}
void linked_list::insert_end(linked_list l)
{
    int i,n=l.get_count();
    for(i=0;i<n;i++)
    {
        insert_end(l[i]);
    }
}
int linked_list::delete_ele(char *num)
{
    node *ptr=start;
    int flag=0;
    while(ptr!=NULL)
    {
        if(strcmp(ptr->num,num)==0)
        {
            flag=1;
            break;
        }
        ptr=ptr->next;
    }
    if(flag==0)
    {
        return 0;
    }
    if(ptr==start && ptr==end)
    {
        delete(ptr);
        start=end=NULL;
    }
    else if(ptr==start)
    {
        ptr=ptr->next;
        delete(ptr->prev);
        ptr->prev=NULL;
        start=ptr;
    }
    else if(ptr==end)
    {
        ptr=ptr->prev;
        delete(ptr->next);
        ptr->next=NULL;
        end=ptr;
    }
    else
    {
        ptr->prev->next=ptr->next;
        ptr->next->prev=ptr->prev;
        delete(ptr);
    }
    no_of_numbers--;
    return 1;
}
void linked_list::display()
{
    node *ptr=start;
    if(ptr==NULL)
    {
        cout<<"  --(NONE)--\n";
        return;
    }
    int count=1;
    while(ptr!=NULL)
    {
        cout<<"  ("<<count++<<")-->"<<ptr->num<<endl;
        ptr=ptr->next;
    }
}
void linked_list::alter(int index,char *num)
{
    node *ptr=start;
    int i;
    if(index>no_of_numbers)
    {
        cout<<"\n--Invalid Number Index--\n";
        return;
    }
    for(i=0;i<index-1;i++)
    {
        ptr=ptr->next;
    }
    strcpy(ptr->num,num);
}
int linked_list::is_empty()
{
    if(start==NULL || end==NULL)
    {
        start=end=NULL;
        return 1;
    }
    return 0;
}
