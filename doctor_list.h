#ifndef DOCTOR_LIST_H
#define DOCTOR_LIST_H
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct node
{
    string data;
    node *next;
};

class doctor_list
{
private:
    node *head;
public:
    doctor_list();
    void add_doctor(string name);
    void display_doctor();
    bool search(string name);

};


doctor_list::doctor_list()
{
    head=NULL;
}

void doctor_list::add_doctor(string name)
{
    node *newNode = new node;
    newNode->data = name;
    newNode->next = NULL;
    if(head==NULL)
    {
        head=newNode;
        return;
    }
    node *last = head;
    while(last->next!=NULL)
    {
        last=last->next;
    }
    last-> next = newNode;
}

void doctor_list::display_doctor()
{
    node* doc_list = head;
    cout<< "\n";
    while(doc_list!= NULL)
    {
        cout<<"\t"<< doc_list->data <<endl;
        doc_list = doc_list-> next;
    }
    cout<<"\n";
}

bool doctor_list::search(string name)
{
    if(head==NULL)
    {
        cout<<"empty"<<endl;
        return false;
    }
    else
    {
        node *temp=head;
        while(temp!= NULL)
        {
            if(temp->data==name)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
}
#endif // DOCTOR_LIST_H
