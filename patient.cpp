#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "patient.h"
using namespace std;

Patient::Patient(string Name, int Age)
{
    name = Name;
    age = Age;
}

string Patient:: getName()
{
    return name;
}

int Patient::getAge()
{
    return age;
}


void Patient::createRecord(string name, int age)
{
        ofstream newPatient;
        newPatient.open("./Patient DB/"+name+".txt");
        newPatient << name <<endl;
        newPatient << age <<endl;
        newPatient.close();
}

void Patient::assignDoctor(string department, string doc, string patient_name)
{

    string fileName = "./Departments/"+department+"/Dr. "+doc+"/patient_list.txt";
    ofstream assigndoc;
    //ifstream read_file(fileName);
    //assigndoc.open(fileName, ios:: app| ios::in);
    assigndoc.open(fileName, ios_base::app);
    if(assigndoc.is_open())
    {
        assigndoc<<patient_name<<endl;
    }

    assigndoc.close();

}
