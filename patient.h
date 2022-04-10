#ifndef DOCTOR_H_INCLUDED
#define DOCTOR_H_INCLUDED
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


class Patient{
private:
    string name;
    int age;
public:

    Patient(string Name, int Age);
    // to declare the value from user

    string getName();
    // to get the name (?)

    int getAge();
    // to get the age (?)


    //Maybe can change the system to doc as folder and the patient record will be created twice
   // one in permanent database
   // another one for queue folder

    void createRecord(string name, int age);
    // to create a permanent medical data into the db

    void assignDoctor(string department, string doc, string patient_name);
    // to add in patient's record  doctor's list file (txt);


};


#endif // DOCTOR_H_INCLUDED
