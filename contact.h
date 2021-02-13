#include <iostream>
#include <string.h>
#include <windows.h>
#include "number_tree.h"
#include "linked_list.h"
#include <unistd.h>
#include <fstream>
#include <ctime>
using namespace std;
int check_name2(char *name);
int check_name(char *name);
void get_name(char *name,int o=1)
{
    cout<<"\n\t\t**Name must be within 30 character**\nEnter Name : ";
    if(o==0)
    {
        cin.ignore();
    }
    cin.getline(name,1000);
    while(!check_name(name))
    {
        cout<<"\nName Should Contain Alphabets, Dot('.') or Space(' ') Only :\nRe-Enter    : ";
        cin.getline(name,30);
    }
    while(!check_name2(name))
    {
        cout<<"\nEnter name within 30 character";
        cout<<"\nEnter Name : ";
        cin.getline(name,1000);
    }
}
int check_name2(char *name)
{
    int i,j;
    for(i=0;name[i]!='\0';i++)
    {
        if(name[0]==' ')
        {
            for(j=i;name[j]!='\0';j++)
            {
                name[j]=name[j+1];
            }
            i--;
        }
    }
    for(i=0;name[i]!='\0';i++)
    {
        if(name[i]!=' '&&name[i+1]==' '&&name[i+2]==' ')
        {
            for(j=i+1;name[j]!='\0';j++)
            {
                name[j]=name[j+1];
            }
            i--;
        }
    }
    if(strlen(name)<=30)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}
void append(char *word,char c)
{
    int n=strlen(word);
    if(c==8)
    {
        if(n==0)
        {
            return;
        }
        word[n-1]='\0';
    }
    else
    {

        word[n]=c;
        word[n+1]='\0';
    }
}
struct call_info
{
    char to_person[30];
    char to_number[11];
    char start_time[30];
    float call_time;
};
void display_call_info(call_info info)
{
    if(strcmp(info.to_person,"Unknown Number")==0)
    {
        cout<<info.to_number<<" (UN) - "<<info.start_time<<"  call duration : "<<info.call_time<<" seconds\n";
    }
    else
    {
        cout<<info.to_number<<" ("<<info.to_person<<") -"<<info.start_time<<"  call duration : "<<info.call_time<<" seconds\n";
    }
}
call_info calling(char *to_number,char *to_person=NULL)
{
    float start=clock();
    call_info info;
    if(to_person==NULL)
    {
        strcpy(info.to_person,"Unknown Number");
    }
    else
    {
        strcpy(info.to_person,to_person);
    }
    strcpy(info.to_number,to_number);
    time_t now=time(0);
    strcpy(info.start_time,ctime(&now));
    cout<<"\n----------\n-END CALL-\n----------\n";
    cout<<"\nPress Enter  key to end call...\n";
    cin.ignore();
    cin.get();
    info.call_time=(float)clock()-start;
    info.call_time/=1000.0;
    return info;
}

void to_lower(char *name)
{
    int i;
    for(i=0;name[i]!='\0';i++)
    {
        if(name[i]>='A' && name[i]<='Z')
        {
            name[i]+=32;
        }
    }
}
int get_index(char c)
{
    if(c==' ')
    {
        return 26;
    }
    else if(c=='.')
    {
        return 27;
    }
    else
    {
        return tolower(c)-'a';
    }
}
struct d_node_s;
struct t_node_s
{
    t_node_s *t_num[28];
    d_node_s *d_num;
};
struct d_node_s
{
    char name[30];
    linked_list numbers;
};
t_node_s * create_t_node_s()
{
    t_node_s *N=new t_node_s;
    int i;
    for(i=0;i<28;i++)
    {
        N->t_num[i]=NULL;
    }
    N->d_num=NULL;
    return N;
}
d_node_s * create_d_node_s(char *name,char *num)
{
    d_node_s *N=new d_node_s;
    strcpy(N->name,name);
    N->numbers.insert_end(num);
    return N;
}
d_node_s * create_d_node_s(char *name,linked_list l)
{
    d_node_s *N=new d_node_s;
    strcpy(N->name,name);
    N->numbers=l;
    return N;
}
class contact
{
private:
    number_tree num_tree;
    t_node_s *root;
protected:
    void update_to_file(t_node *);
public:
    number_tree get_numbertree();
    int allowed_entry(char *);
    t_node_s * getRoot();
    contact();
    ~contact();
    char * get_owner(char *);
    int add_to_existing_contact(char *,t_node_s *);
    int insert_person(char *number,char *name,int force=0,int num_check=1);
    int insert_person(linked_list l,char *name,int a=0);
    void display(d_node_s *,int show_no_of_contacts=0);
    void display_all(t_node_s *);
    void search_person(char *,int modfy=1);
    int delete_person(char *,int i=0,int retain_contacts=0);
    int delete_number(char *,char *);
    int delete_number(t_node_s *,char *);
    void display_numTree();
    int call(char *number);
    t_node_s * is_exists(char *);
    int any_contacts_under(t_node_s *);
    void modify_person(t_node_s *);
};
number_tree contact::get_numbertree()
{
    return num_tree;
}
char * contact::get_owner(char *number)
{
    return num_tree.search_number(number,1);
}
void contact::update_to_file(t_node *node)
{
    int i;
    if(node==NULL)
    {
        return;
    }
    if(node->d_num!=NULL)
    {
        ofstream obj;
        obj.open("my_contacts.txt",ios::app);
        obj.write((char *)node->d_num,sizeof(d_node));
        obj.close();
    }
    for(i=0;i<10;i++)
    {
        update_to_file(node->t_num[i]);
    }
}
void contact::display_numTree()
{
    cout<<"\nNumber Tree\n\n";
    num_tree.display_all(num_tree.getRoot());
}
int contact::allowed_entry(char *name)
{
    t_node_s *ptr=root;
    int i;
    for(i=0;name[i]!='\0';i++)
    {
        if(ptr->t_num[get_index(name[i])]!=NULL)
        {
            ptr=ptr->t_num[get_index(name[i])];
        }
        else
        {
            break;
        }
    }
    if(name[i]!='\0' || ptr->d_num==NULL)
    {
        return 1;
    }
    return 0;
}
t_node_s * contact::getRoot()
{
    return root;
}
contact::contact()
{
    root=create_t_node_s();
    ifstream obj("my_contacts.txt");
    if(obj.is_open())
    {
        d_node node;
        obj.read((char *)&node,sizeof(node));
        while(!obj.eof())
        {
            insert_person(node.number,node.name,1,0);
            obj.read((char *)&node,sizeof(node));
        }
        obj.close();
    }
    else
    {
        ofstream obj("my_contacts.txt");
        obj.close();
    }

}
contact::~contact()
{
    remove("my_contacts.txt");
    update_to_file(num_tree.getRoot());
}

int contact::add_to_existing_contact(char *number,t_node_s *node)
{
    t_node *t=num_tree.is_number(number);
    if(t!=NULL)
    {
        cout<<"\nNUMBER : \n";
        num_tree.display(t->d_num);
        cout<<"\nNumber Already Exists...Overwrite Number?...[yes(y) or no(n)] : ";
        char c;
        cin>>c;
        if(c=='n')
        {
            cout<<"\n--Contact Creation Unsuccessful--\n";
            return 0;
        }
        t_node_s *person=is_exists(t->d_num->name);
        person->d_num->numbers.delete_ele(number);
        if(person->d_num->numbers.get_count()==0)
        {
            delete_person(t->d_num->name,1,1);
        }
        cout<<"\nNumber Removed from contact "<<t->d_num->name<<" and is added to "<<node->d_num->name<<endl;
        strcpy(t->d_num->name,node->d_num->name);
    }
    else
    {
        num_tree.insert_number(number,node->d_num->name,1);
    }
    node->d_num->numbers.insert_end(number);

}
int contact::insert_person(char *number,char *name,int a,int num_check)
{
    t_node *t=num_tree.is_number(number);
    if(num_check==1)
    {
        if(t!=NULL)
        {
            cout<<"\nNUMBER :\n";
            num_tree.display(t->d_num);
            cout<<"\nNumber Already Exists...Overwrite Number?...[yes(y) or no(n)] : ";
            char c;
            cin>>c;
            if(c=='n')
            {
                cout<<"\n--Contact Creation Unsuccessful--\n";
                return 0;
            }
        }
    }
    t_node_s *ptr=root;
    int i;
    for(i=0;name[i]!=NULL;i++)
    {
        if(ptr->t_num[get_index(name[i])]==NULL)
        {
            ptr->t_num[get_index(name[i])]=create_t_node_s();
        }
        ptr=ptr->t_num[get_index(name[i])];
    }
    if(ptr->d_num!=NULL)
    {
        char c='y';
        if(a==0)
        {
            display(ptr->d_num);
            cout<<"\nName Already Exists...\n\nAdd to existing contact...[yes(y) or no(n)] : ";
            cin>>c;
        }
        if(c=='y')
        {
            ptr->d_num->numbers.insert_end(number);
            if(t!=NULL)
            {
                delete_number(t->d_num->name,t->d_num->number);
                strcpy(t->d_num->name,ptr->d_num->name);
            }
            else
            {
                num_tree.insert_number(number,ptr->d_num->name,1);
            }
            return 1;
        }
        else
        {
            if(a==0)
            cout<<"\nContact Creation Unsuccessful...\n";
            return 0;
        }
    }
    else
    {
        if(t!=NULL)
        {
            delete_number(t->d_num->name,t->d_num->number);
            strcpy(t->d_num->name,name);
        }
        else
        {
            num_tree.insert_number(number,name,1);
        }
        ptr->d_num=create_d_node_s(name,number);
        return 1;
    }
}
int contact::insert_person(linked_list l,char *name,int a)
{
    int i,n=l.get_count();
    l.display();
    for(i=0;i<n;i++)
    {
        insert_person(l[i],name,1,0);
    }
}
void contact::display(d_node_s *node,int show_no_of_contacts)
{
    if(node!=NULL)
    {
        cout<<"(#)"<<node->name<<endl;
        node->numbers.display();
        if(show_no_of_contacts==1)
        {
            cout<<"|=========>Count : "<<node->numbers.get_count()<<endl;
        }

    }
    else
    {
        cout<<"\nContact Does not Exits...\n";
    }
}
void contact::display_all(t_node_s *node)
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
    for(i=0;i<28;i++)
    {
        display_all(node->t_num[i]);
    }
}
void contact::search_person(char *name,int modfy)
{
    if(name==NULL)
    {
        return;
    }
    t_node_s *ptr=root;
    int i;
    for(i=0;name[i]!='\0';i++)
    {
        if(ptr==NULL)
        {
            cout<<"\nPerson Does Not Exists...\n";
            return;
        }
        if(ptr->t_num[get_index(name[i])]!=NULL)
        {
            ptr=ptr->t_num[get_index(name[i])];
        }
        else
        {
            break;
        }
    }
    if(name[i]!='\0' ||(ptr->d_num==NULL && modfy==1))
    {
        cout<<"\nPerson Does Not Exists...\n";
    }
    else if(ptr->d_num==NULL)
    {
        cout<<"\n-----------\nYOUR CONTACTS\n-----------\n";
        if(any_contacts_under(ptr))
        {
            display_all(ptr);
        }
        else
        {
            cout<<"\n--(NONE)--\n";
        }
    }
    else if(ptr->d_num!=NULL)
    {
        if(modfy==1)
        {
            modify_person(ptr);
        }
        else
        {
            cout<<"\n------------\n";
            cout<<"  CONTACT";
            cout<<"\n------------\n";
            display(ptr->d_num);

            cout<<"\n\n------------\n";
            cout<<"ALL CONTACTS";
            cout<<"\n------------\n";
            display_all(ptr);
        }
    }
}
t_node_s * contact::is_exists(char *name)
{
    t_node_s *ptr=root;
    int i;
    for(i=0;name[i]!='\0';i++)
    {
        if(ptr->t_num[get_index(name[i])]!=NULL)
        {
            ptr=ptr->t_num[get_index(name[i])];
        }
        else
        {
            break;
        }
    }
//    cout<<"done...";
    if(name[i]!='\0' || ptr->d_num==NULL)
    {
        return NULL;
    }
    return ptr;

}
int contact::delete_person(char *name,int a,int retain_contacts)
{
    t_node_s *t=is_exists(name);
    if(t!=NULL)
    {
        if(a==0)
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
        int i,n=t->d_num->numbers.get_count();
        for(i=0;i<n;i++)
        {
            num_tree.delete_number(t->d_num->numbers[i],1);
        }
        if(any_contacts_under(t)==1)
        {
            d_node_s *temp=t->d_num;
            t->d_num=NULL;
            delete(temp);
            return 1;
        }
        t_node_s *ptr=root;
        t_node_s *start_ptr=root;
        int j,start=0;
        for(i=0;name[i]!='\0';i++)
        {
            int count=0;
            for(j=0;j<28;j++)
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
            ptr=ptr->t_num[get_index(name[i])];
        }
        t_node_s *temp1=start_ptr->t_num[get_index(name[start])];
        start_ptr->t_num[get_index(name[start])]=NULL;
        for(i=start+1;name[i]!='\0';i++)
        {
            t_node_s *temp2=temp1->t_num[get_index(name[i])];
            if(temp2==NULL)
            {
                delete(temp1->d_num);
                delete(temp1);
                break;
            }
            delete(temp1);
            temp1=temp2;
        }
        cout<<"\nContact Successfully deleted...\n";
        return 1;
    }
}
int contact::any_contacts_under(t_node_s *node)
{
    if(node==NULL)
    {
        return 0;
    }
    int i,flag=0;
    for(i=0;i<28;i++)
    {
        if(node->t_num[i]!=NULL)
        {
            break;
        }
    }
    //i=10 if all t_num is NULL
    if(i==28)
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
        for(i=0;i<28;i++)
        {
            flag=flag|any_contacts_under(node->t_num[i]);
        }
    }
    return flag;
}
void contact::modify_person(t_node_s *node)
{
    if(node->d_num==NULL)
    {
        cout<<"\nContact Does not Exits...\n";
        return;
    }
    while(1)
    {
        system("cls");
        cout<<"\n-------------\nYOUR CONTACT\n-------------\n\n";
        display(node->d_num,1);
        cout<<"\n(1)Call\n(2)Call Log\n(3)Delete Contact\n(4)Edit\n(5)goto home\n\n: ";
        int opt;
        cin>>opt;
        if(opt==1)
        {
            int index;
            cout<<"\n\nEnter index of Number to call : ";
            cin>>index;
            call(node->d_num->numbers[index-1]);
            continue;
        }
        else if(opt==2)
        {
            ifstream obj("call_log.txt");
            if(obj.is_open())
            {
                cout<<"\n------------\n";
                cout<<"--CALL LOG--";
                cout<<"\n------------\n";
                call_info info;
                obj.read((char *)&info,sizeof(info));
                int count=1;
                while(!obj.eof())
                {
                    if(strcmp(info.to_person,node->d_num->name)==0)
                    {
                        cout<<"("<<count++<<")";
                        display_call_info(info);
                    }
                    obj.read((char *)&info,sizeof(info));
                }
            }
            else
            {
                cout<<"\nNo Call Log\n";
            }
        }
        else if(opt==3)
        {
            cout<<"\nname:"<<node->d_num->name<<endl;
            if(delete_person(node->d_num->name)==1)
            {
                return;
            }
        }
        else if(opt==4)
        {
            system("cls");
            cout<<"\n-------------\nEDIT CONTACT\n-------------\n";
            cout<<"(1)Change Name\n(2)Change Number\n(3)Add New Number\n(4)Delete Number\n(5)Exit\n";
            int op;
            cin>>op;
            if(op==1)
            {
//                display(node->d_num);
                char new_name[30];
                get_name(new_name,0);
                t_node_s *t=is_exists(new_name);
                if(t==NULL)
                {
                    linked_list l=node->d_num->numbers;
                    delete_person(node->d_num->name,1,1);
                    insert_person(l,new_name);
                    node=is_exists(new_name);
                }
                else
                {
                    cout<<"\nContact Already Exists...\n";
                    display(t->d_num);
                    char c;
                    cout<<"\nAdd "<<node->d_num->numbers.get_count()<<" numbers to contact "<<t->d_num->name<<" [yes(y) or no(n)] : ";
                    cin>>c;
                    if(c=='y')
                    {
                        linked_list l=node->d_num->numbers;
                        delete_person(node->d_num->name,1,1);
                        t->d_num->numbers.insert_end(l);
                        t->d_num->numbers.display();
                        int i,n=l.get_count();
                        for(i=0;i<n;i++)
                        {
                            num_tree.insert_number(l[i],t->d_num->name);
                        }
                        node=t;
                    }
                }
            }
            else if(op==2)
            {
                node->d_num->numbers.display();
                char number[11];
                int index;
                cout<<"\n\nEnter index of Number to change : ";
                cin>>index;
                cout<<"\nEnter New Number : ";
                cin>>number;
                while(!check_number(number))
                {
                    cout<<"\nInvalid Number:\nRe-Enter    : ";
                    cin>>number;
                }
                t_node *t=num_tree.is_number(number);
                if(t!=NULL)
                {
                    cout<<"\nNUMBER :\n";
                    num_tree.display(t->d_num);
                    cout<<"\nNumber Already Exists...Overwrite Number?...[yes(y) or no(n)] : ";
                    char c;
                    cin>>c;
                    if(c=='y')
                    {
                        t_node_s *temp=is_exists(t->d_num->name);
                        temp->d_num->numbers.delete_ele(number);
                        num_tree.delete_number(node->d_num->numbers[index],1);
                        node->d_num->numbers.alter(index,number);
                        num_tree.delete_number(number,1);
                        num_tree.insert_number(number,node->d_num->name,1);
                    }
                }
                else
                {
                    num_tree.delete_number(node->d_num->numbers[index],1);
                    num_tree.insert_number(number,node->d_num->name,1);
                    node->d_num->numbers.alter(index,number);
                }
            }
            else if(op==3)
            {
                char number[11];
                cout<<"\nEnter Number : ";
                cin>>number;
                while(!check_number(number))
                {
                    cout<<"\nInvalid Number:\nRe-Enter    : ";
                    cin>>number;
                }
                add_to_existing_contact(number,node);

            }
            else if(op==4)
            {
                int index;
                node->d_num->numbers.display();
                cout<<"\n\nEnter index of Number to delete : ";
                cin>>index;
                if(num_tree.delete_number(node->d_num->numbers[index],1)==1)
                {
                    cout<<"\nnumber deleted from num_tree\n";
                }
                node->d_num->numbers.delete_ele(node->d_num->numbers[index]);

            }
            else if(op==5)
            {
                break;
            }
        }
        else if(opt==5)
        {
            break;
        }
        cin.ignore();
        cout<<"\nPress Enter key to continue...\n";
        cin.get();
    }
}
int contact::delete_number(char *name,char *number)
{
    t_node_s *t=is_exists(name);
    if(t!=NULL)
    {
        t->d_num->numbers.delete_ele(number);
        num_tree.delete_number(number,1);
        return 1;
    }
    else
    {
        return 0;
    }
}
int contact::call(char *number)
{
    if(number[0]=='\0')
    {
        cout<<"\nNumberless...call failed...\n";
    }
    t_node *t=num_tree.is_number(number);
    call_info info;
    if(t!=NULL)
    {
        cout<<"\nCalling "<<t->d_num->name<<"...\n";
        info=calling(number,t->d_num->name);
    }
    else
    {
        cout<<"\nCalling "<<number<<"...\n";
        info=calling(number);
        display_call_info(info);
    }
    ofstream obj;
    obj.open("call_log.txt",ios::app);
    obj.write((char *)&info,sizeof(info));
    obj.close();
    cout<<"written...\n";
}
