#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "application.h"
using namespace std;

bool getPatientList(string doc_name, string dept_name, vector<string> & patient_vector)
{
    string fileName = "./Departments/"+dept_name+"/Dr. "+doc_name+"/patient_list.txt";
    fstream read_patientList(fileName, ios:: in);
    if(read_patientList.is_open())
    {
        string patient_names;
        while(getline(read_patientList, patient_names)){//storing the values into list
            patient_vector.push_back(patient_names);
        }
    }
    read_patientList.close();
    return true;
}

bool removePatient(string doc_name, string dept_name, vector<string> &patient_vector)
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


