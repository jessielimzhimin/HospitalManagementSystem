#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <cctype>
#include <algorithm>
#include "doctor_list.h"
using namespace std;


bool getPatientList(string doc_name, string dept_name, vector<string> &patient_vector);

void removePatient(string doc_name, string dept_name, vector<string> &patient_vector);

string display_doctors(string dept_name);

string display_department();

bool check_userInput_str(string str_input);

bool check_userInput_phone(string phone_input);

bool getPatientList(string doc_name, string dept_name, vector<string> & patient_vector)
{
    string fileName = "./Departments/"+dept_name+"/Dr. "+doc_name+"/patient_list.txt";
    fstream read_patientList(fileName, ios:: in);
    if(read_patientList.is_open())
    {
        if(read_patientList.peek()==EOF)
        {
            return false;
        }
        string patient_names;
        while(getline(read_patientList, patient_names)) //storing the values into list
        {
            patient_vector.push_back(patient_names);
        }
    }
    read_patientList.close();
    return true;
}

void removePatient(string doc_name, string dept_name, vector<string> &patient_vector)
{
    string fileName = "./Departments/"+dept_name+"/Dr. "+doc_name+"/patient_list.txt";
    ofstream update_patientlist(fileName, ios::out);
    if(update_patientlist.is_open())
    {
        for(int i=0; i<patient_vector.size(); i++)
        {
            update_patientlist<<patient_vector[i]<<endl;
        }
    }
    update_patientlist.close();
}

string display_doctors(string dept_name)
{
    doctor_list doctors;
    string doc_name;
    string fileName = "./Departments/"+dept_name+"/Doctor DB.txt";
    ifstream read_docList(fileName, ios::in);
    if(read_docList.is_open())
    {
        string name;
        while(getline(read_docList, name))
        {
            doctors.add_doctor(name);
        }
    }
    read_docList.close();
    cout<<"\n\tDoctor Menu\n";
    cout<<"\t___________\n";
    doctors.display_doctor();
    again:
    cout<<"Please Choose a doctor (Please Type The Name Exactly Listed As Above!): ";
    getline(cin>>ws, doc_name);

    bool validate = doctors.search(doc_name);
    if(!validate)
    {
        cout<<"invalid input"<<endl;
        goto again;
    }
    return doc_name;
}

string display_department()
{
    int size  = 5;
    string department;
    string department_choice[size] = {"Cardiology", "General", "Geriatrics", "Pediatrics", "Spine Surgery"};
    int dept_choice;
    cout<<"\n\tDepartment Menu\n";
    cout<<"\t________________\n\n";
    for(int i =0; i<size; i++)
    {
        cout<<"\t"<<"("<<i+1<<")"<<department_choice[i]<<endl;
    }
    cout<<"\nPlease choose a department, and write your choice in number format (1-5): ";

    cin>>dept_choice;
    while(!cin){
        cin.clear();
        cin.ignore();
        cout<<"ERROR! PLEASE INSERT NUMBER FROM 1 TO 5: ";
        cin>>dept_choice;
    }
    switch(dept_choice)
    {
    case 1:
        department = department_choice[0];
        break;
    case 2:
        department = department_choice[1];
        break;
    case 3:
        department = department_choice[2];
        break;
    case 4:
        department = department_choice[3];
        break;
    case 5:
        department =department_choice[4];
        break;
    default:
        cout<< "\n***ERROR! PLEASE SELECT NUMBER FROM 1 TO 6!***"<<endl;
        department = "Invalid";
        break;
    }
    return department;
}

bool check_userInput_str(string str_input)
{
    for(auto i: str_input)
    {
        if((i<='9') && (i >='0'))
            return false;
    }
    return true;
}

bool check_userInput_phone(string phone_num)
{
    for(auto i: phone_num)
    {
        if(isalpha(i))
            return false;
    }
    return true;
}
