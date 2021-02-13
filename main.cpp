#include <iostream>
#include "contact.h"
#include <conio.h>
#include<string.h>
using namespace std;
int main()
{
    char number[15];
    char name[1000];
    contact tree;
    char d[100];
    int opt;
    while(1)
    {
        system("cls");
        cout<<"\n(1)New Person\n(2)Add to existing contact\n(3)Display All\n(4)Search\n(5)Delete Contact\n(6)Call\n(7)Call Log\n(8)Exit\n\nEnter your Option : ";
        cin.getline(d,100);
     //   cout<<strlen(d);
        while(1)
        {
            if(strlen(d)==1&&!check_name1(d))
            {
                break;
            }
            cout<<"\nEnter valid option:";
            cin.getline(d,100);
        }
        opt=d[0];
        if(opt=='1')
        {
            get_name(name);
            cout<<"\nEnter Number       : ";
            cin>>number;
            while(!check_number(number))
            {
                cout<<"\nInvalid Number.\nRe-Enter    : ";
                cin>>number;
            }
            tree.insert_person(number,name);
        }
        else if(opt=='2')
        {
            char buffer[30];
            buffer[0]='\0';
            char key_press;
            int modfy=0;
            system("cls");
            cout<<"\nSearch Contact : \n";
            cout<<"\n-----------\nYOUR CONTACTS\n-----------\n";
            tree.display_all(tree.getRoot());
            while(1)
            {
                key_press=getch();
                system("cls");
                cout<<"\nSearch Contact : ";
                if(key_press==13)
                {
                    modfy=1;
                }
                else
                {
                    append(buffer,key_press);
                }
                cout<<buffer<<endl;
                tree.search_person(buffer,0);
                if(modfy==1)
                {
                    break;
                }
            }
            t_node_s *t=tree.is_exists(buffer);
            if(t!=NULL)
            {
                cout<<"\nNumber       : ";
                cin>>number;
                while(!check_number(number))
                {
                    cout<<"\nInvalid Number:\nRe-Enter    : ";
                    cin>>number;
                }
                tree.add_to_existing_contact(number,t);
            }
            else
            {
                cout<<"\nNo such contact...\n";
            }
        }
        else if(opt=='3')
        {
            system("cls");
            cout<<"\n--------------\nYOUR CONTACTS\n--------------\n";
            tree.display_all(tree.getRoot());
        }
        else if(opt=='4')
        {
            char buffer[30];
            buffer[0]='\0';
            char key_press;
            int modfy=0;
            system("cls");
            cout<<"\nEnter Name or Number : \n";
            cout<<"\n--------------\nYOUR CONTACTS\n--------------\n";
            tree.display_all(tree.getRoot());
            while(1)
            {
                key_press=getch();
                system("cls");
                cout<<"\nEnter Name or Number : ";
                if(key_press==13)
                {
                    modfy=1;
                }
                else
                {
                    append(buffer,key_press);
                }
                cout<<buffer<<endl;
                if(all_num(buffer))
                {
                    tree.search_person(tree.get_owner(buffer),modfy);
                }
                else
                {
                    tree.search_person(buffer,modfy);
                }
                if(modfy==1)
                {
                    break;
                }
            }
        }
        else  if(opt=='5')
        {
            char buffer[30];
            buffer[0]='\0';
            char key_press;
            int modfy=0;
            system("cls");
            cout<<"\nDelete Contact : \n";
            cout<<"\n-----------\nYOUR CONTACTS\n-----------\n";
            tree.display_all(tree.getRoot());
            while(1)
            {
                key_press=getch();
                system("cls");
                cout<<"\nDelete Contact : ";
                if(key_press==13)
                {
                    modfy=1;
                }
                else
                {
                    append(buffer,key_press);
                }
                cout<<buffer<<endl;
                tree.search_person(buffer,0);
                if(modfy==1)
                {
                    break;
                }
            }
            if(tree.delete_person(buffer,0)==1)
            {
                cout<<"\nContact Deleted...\n";
            }
            else
            {
                cout<<"\nNo Contact Exists...\n";
            }
        }
        else if(opt=='6')
        {
            char buffer[30];
            buffer[0]='\0';
            char key_press;
            int modfy=0;
            system("cls");
            cout<<"\nNumber : ";
            cout<<"\n-----------\nYOUR CONTACTS\n-----------\n";
            tree.display_all(tree.getRoot());
            while(1)
            {
                key_press=getch();
                system("cls");
                cout<<"\nNumber : ";
                if(key_press==13)
                {
                    modfy=1;
                }
                else
                {
                    append(buffer,key_press);
                }
                cout<<buffer<<endl;
                tree.search_person(tree.get_owner(buffer),0);
                if(modfy==1)
                {
                    break;
                }
            }
            tree.call(buffer);
        }
        else if(opt=='7')
        {
            system("cls");
            ifstream obj("call_log.txt");
            cout<<"\n------------\n";
            cout<<"--CALL LOG--";
            cout<<"\n------------\n";
            if(obj.is_open())
            {
                call_info info;
                obj.read((char *)&info,sizeof(info));
                int count=1;
                while(!obj.eof())
                {
                    cout<<"("<<count++<<")";
                    display_call_info(info);
                    obj.read((char *)&info,sizeof(info));
                }
            }
            else
            {
                cout<<"\n--(NONE)--\n";
            }
            obj.close();
        }
        else if(opt=='8')
        {
            cout<<"\nExiting Contact Manager...\n";
            break;
        }
        cout<<"\nPress Enter key to continue...\n";
        if(opt!=6 )
        {
            cin.ignore();
        }
        cin.get();
    }
    return 0;
}
