#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "patient.h"
#include "application.h"
using namespace std;

int main()
{

    int choice;
    vector <string> patient_vec;
    bool result;
    do
    {
        cout<< "Welcome to our Hospital Management System!"<<endl;
        cout<< "Please choose an operation\n";
        cout<< "(1) Provide Queue Number to Patient\n";
        cout<< "(2) Add Patient\n";
        cout<< "(3) Bring Patient To Doctor\n";
        cout<< "(4) Exit";
        cin>> choice;

        if(choice == 1)
        {
            string department_name, doc_name, pat_name;
            cout<<"Please choose a department;";
            cin>>department_name;
            cout<<"Please choose a doc:";
            cin>>doc_name;
            result = getPatientList(doc_name, department_name, patient_vec);
            if(result)
            {
                cout<< "\nPatient Names are: " <<endl;
                for(string & line:patient_vec)
                {
                    cout<<line<<endl;
                }
            }
            cout<< "Please choose a patient: "<<endl;
            cin >>pat_name;
            auto results = find(begin(patient_vec), end(patient_vec), pat_name);
            if( results!=patient_vec.end())
            {
                cout<<"Patient Name found"<<endl;
                cout<<"Generating Number..."<<endl;
                int index = distance(patient_vec.begin(), results);
                cout<<*results<<" Waiting Number is: "<<index+1<<endl;
                patient_vec.clear();
            }

        }
        else if(choice==2)
        {
            string pat_name;
            int pat_age;
            string department, doc_name;
            cout<< "Enter Patient Name:"<<endl;
            cin >> pat_name;
            cout << "Enter Patient Age:"<<endl;
            cin >> pat_age;
            cout << "Please Choose the department:" <<endl;
            cin>>department;
            cout<< "Please choose the doctor:"<<endl;
            cin>>doc_name;
            Patient newpatient(pat_name, pat_age);
            newpatient.createRecord(pat_name, pat_age);
            newpatient.assignDoctor(department, doc_name, pat_name);
        }
        else if(choice==3)
        {
            string departments, doc_name, pat_name;
            cout<<"choose a department"<<endl;
            cin>>departments;
            cout<<"choose a doc"<<endl;
            cin>>doc_name;
            result = getPatientList(doc_name, departments, patient_vec);
            if(result)
            {
                pat_name = patient_vec.front();
                cout<<"Current Patient: "<<pat_name<<endl;
                patient_vec.erase(patient_vec.begin());
                cout<<"Next In Line: "<<patient_vec.front()<<" Please Get Ready."<<endl;
                removePatient(doc_name, departments, patient_vec);
                patient_vec.clear();
            }
        }
    }
    while(choice!=4);
    return 0;
}

