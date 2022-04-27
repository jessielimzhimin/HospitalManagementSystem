#ifndef PATIENT_H_INCLUDED
#define PATIENT_H_INCLUDED
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;


class Patient
{
private:
    string name, medical_history, medical_treatment, blood, phone_num, department, doctor_incharged;
    char severity;
    int age;
public:
    Patient()=default;
    Patient(string Name, int Age, string Medical_History, string phone_number, string Blood, char Severity, string Department, string Doctor_InCharged);
    // to declare the value from user

    void createRecord(string name, int age, string med_history, string phone_num, string blood, char Severity, string department, string Dr_InCharged);
    // to create a permanent medical data into the db

    void assignDoctor(string department, string doc, string patient_name);
    // to add in patient's record  doctor's list file (txt);

    bool updatePatient(string name);

    bool displayPatientInformation(string name, vector<string>& data_vec);

    void payment(string dept_choice, string patient_name);

    void update_payment(string patient_name);

    void sort_patientlist(string dept_name, string doc_name, string pat_name, char Severity);
};


Patient::Patient(string Name, int Age, string Medical_History, string Phone_Num, string Blood, char Severity, string Department, string Doctor_InCharged)
{
    name = Name;
    age = Age;
    medical_history = Medical_History;
    blood = Blood;
    department = Department;
    doctor_incharged = Doctor_InCharged;
    phone_num = Phone_Num;
    severity = Severity;
}

void Patient::createRecord(string name, int age, string med_history, string phone, string blood, char severity, string department, string Dr_InCharged)
{
    ofstream newPatient;
    newPatient.open("./Patient DB/"+name+".txt");
    newPatient << "Name: " << name <<endl;
    newPatient << "Age: " << age <<endl;
    newPatient << "Medical History: " << med_history <<endl;
    newPatient << "Phone Number: " <<phone<<endl;
    newPatient << "Blood Type: " << blood <<endl;
    if(severity == 'B')
        newPatient << "Condition: " << "Bad" <<endl;
    else
        newPatient << "Condition: " << "Normal" <<endl;
    newPatient << "Department: " << department <<endl;
    newPatient << "Doctor In Charged: " << Dr_InCharged <<endl;
    newPatient.close();
}

void Patient::assignDoctor(string department, string doc, string patient_name)
{

    string fileName = "./Departments/"+department+"/Dr. "+doc+"/patient_list.txt";
    ofstream assigndoc;
    assigndoc.open(fileName, ios_base::app);
    if(assigndoc.is_open())
    {
        assigndoc<<patient_name<<endl;
    }

    assigndoc.close();

}

bool Patient::updatePatient(string name)
{
    string med_treatment;
    string med_condition_description;
    string fileName = "./Patient DB/"+name+".txt";
    ifstream check_patientFile(fileName, ios::in);
    if(check_patientFile.is_open())
    {
        ofstream update_treatment(fileName, ios_base::app);
        if(update_treatment.is_open())
        {
            cout<<"Medical Condition: ";
            getline(cin>>ws, med_condition_description);
            cout<<"Medical Treatment: ";
            getline(cin>>ws, med_treatment);
            update_treatment<<"Medical Condition: " << med_condition_description<<endl;
            update_treatment<<"Treatment: "<<med_treatment<<endl;
        }
        update_treatment.close();
        return true;
    }
    check_patientFile.close();
    return false;

}

bool Patient::displayPatientInformation(string name, vector<string>& data_vec)
{
    string data;
    string fileName = "./Patient DB/"+name+".txt";
    ifstream check_patientFile(fileName, ios::in);
    if(!check_patientFile.is_open())
        return false;
    while(getline(check_patientFile, data))
    {
        data_vec.push_back(data);
    }
    return true;
}


void Patient::payment(string dept_choice, string patient_name)
{
    int price;
    if (dept_choice == "Cardiology")
    {
        price = 500;
    }
    else if (dept_choice == "General")
    {
        price = 180;
    }
    else if (dept_choice == "Geriatrics")
    {
        price = 350;
    }
    else if (dept_choice == "Pediatrics")
    {
        price = 450;
    }
    else if (dept_choice == "Spine Surgery")
    {
        price = 500;
    }

    string fileName = "payment_list.txt";
    ofstream payment_file;
    payment_file.open(fileName, ios:: app);
    if(payment_file.is_open())
    {
        payment_file << patient_name<<",";
        payment_file << "\tRM " << price << "\n";
        payment_file.close();
    }
}

void Patient :: update_payment(string patient_name)
{
    system("CLS");
    fstream input;
    ofstream tempfile;
    string fileName = "payment_list.txt";
    string tempFile = "temp_list.txt";
    vector<string> name_list, price_list;
    string temp_name,temp_price;
    input.open(fileName, ios:: in);
    //getting the input
    if(input.is_open())
    {

        while(getline(input,temp_name))
        {
            name_list.push_back(temp_name);
        }
    }
    input.close();
    tempfile.open(tempFile, ios:: out);//creating a file
    auto check = find(begin(name_list), end(name_list), patient_name);

    if(tempfile.is_open()) //writing to the file
    {
        for(int i =0; i <name_list.size(); i++)
        {
            if(name_list[i].find(patient_name))
            {
                tempfile << name_list[i] << endl;
            }
        }
    }
    tempfile.close();
}

void Patient::sort_patientlist(string dept_name, string doc_name, string pat_name, char Severity)
{
    string fileName, tempFile;
    vector<string> temp_vect, patient_vect;
    fileName = "./Departments/"+dept_name+"/Dr. "+doc_name+"/patient_list.txt";
    tempFile = "./Departments/"+dept_name+"/Dr. "+doc_name+"/temp.txt";
    fstream update_file;
    ifstream read_file;
    read_file.open(fileName, ios::in);
    if(read_file.is_open())
    {
        string names;
        while(getline(read_file, names))
        {
            temp_vect.push_back(names);
        }
    }
    read_file.close();
    if(Severity=='B')
    {
        auto results = find(begin(temp_vect), end(temp_vect), pat_name);
        if(results!=temp_vect.end())
        {
            patient_vect.push_back(pat_name);
            temp_vect.pop_back();
        }
        for(int i=0; i<temp_vect.size(); i++)
            patient_vect.push_back(temp_vect[i]);
    }
    else
    {
        for(int i =0; i<temp_vect.size();i++)
            patient_vect.push_back(temp_vect[i]);
    }
    update_file.open(fileName, ios_base::out);
    if(update_file.is_open())
    {
        for(int i=0; i<patient_vect.size(); i++)
        {
            update_file<<patient_vect[i]<<endl;
        }
    }
    update_file.close();
    patient_vect.clear();
    temp_vect.clear();
}
#endif // PATIENT_H_INCLUDED
