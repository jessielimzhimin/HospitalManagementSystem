#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "patient.h"
#include "application.h"
#include "doctor_list.h"
using namespace std;

int main()
{
    int choice;
    vector <string> patient_vec;
    string department_name, patient_name, doctor_name, description, phone_num, blood;
    char severity, severity_input, med_treatment_input, med_treat;
    int pat_age;
    bool result;
    do
    {
        cout<< "\n\t  Welcome to our Hospital Management System!\t"<<endl;
        cout<< " \t_____________________________________________\n\n";
        cout<< "\t* (1) Provide Queue Number to Patient\t    *\n";
        cout<< "\t* (2) Add Patient\t\t\t    *\n";
        cout<< "\t* (3) Bring Patient To Doctor\t\t    *\n";
        cout<< "\t* (4) Search and Update Patient Data\t    *\n";
        cout<< "\t* (5) Update patient payment fees\t    *\n";
        cout<< "\t* (6) Exit\t\t\t\t    *\n";
        cout<< " \t_____________________________________________\n";
        cout<< "\nPlease select the operation with numbers (1-6): ";
        cin>> choice;
        while(!choice)
        {
            cin.clear();
            cin.ignore();
            cout<<"ERROR! PLEASE INSERT NUMBER FROM 1 TO 6: ";
            cin>>choice;
        }
        if(choice == 1)
        {
            do
            {
                department_name = display_department();
            }
            while(department_name == "Invalid");
            doctor_name = display_doctors(department_name);
            result = getPatientList(doctor_name, department_name, patient_vec);
            if(result)
            {
                cout<< "\nPatient Names are: \n" <<endl;
                for(string & line:patient_vec)
                {
                    cout<<"\t"<<line<<endl;
                }
                patient_name_selection_again:
                cout<< "\nPlease choose a patient: ";
                getline(cin>>ws, patient_name);
                auto results = find(begin(patient_vec), end(patient_vec), patient_name);
                if( results!=patient_vec.end())
                {
                    cout<<"\nPatient Name found"<<endl;
                    cout<<"Generating Number...\n"<<endl;
                    int index = distance(patient_vec.begin(), results);
                    cout<<"Patient Name: "<<*results<<"\nWaiting Number is: "<<index+1<<endl;
                    cout<< "\n*******End Operation For Providing Queue Number******\n\n";
                    patient_vec.clear();
                }
                else
                {
                    cout<< "Wrong Patient Name" <<endl;
                    goto patient_name_selection_again;
                }
            }
            else
            {
                cout<<"\n*******No Patient at the moment********\n\n";
            }
        }
        else if(choice==2)
        {
            bool validate;
            str_again:
            cout<< "Enter Patient Name: ";
            getline(cin>>ws, patient_name);
            bool validate_input = check_userInput_str(patient_name);
            if(!validate_input)
                goto str_again;
            cout << "\nEnter Patient Age: ";
            cin >> pat_age;
            while(!cin)
            {
                cin.clear();
                cin.ignore();
                cout<<"ERROR! AGE SHOULD NOT CONTAIN CHARACTERS: ";
                cin>> pat_age;
            }
            int_again:
            cout<< "\nPhone Number: ";
            getline(cin>>ws, phone_num);
            validate = check_userInput_phone(phone_num);
            if(!validate)
                goto int_again;
            cout<< "\nMedical History: ";
            getline(cin>>ws, description);
blood_again:
            cout<< "\nBlood Type (A+, A-, B+, B-, AB+, AB-, O+, O-): ";
            getline(cin>>ws, blood);
            if((blood!="A+")&&(blood!="a+")&&(blood!="A-")&&(blood!="a-")&&(blood!="B+")&&(blood!="b+")&&(blood!="B-")&&(blood!="b-")
                    &&(blood!="AB+")&&(blood!="ab+")&&(blood!="AB-")&&(blood!="ab-")&&(blood!="O+")&&(blood!="o+")
                    &&(blood!="O-")&&(blood!="o-"))
            {
                cout<<"Invalid Selection"<<endl;
                goto blood_again;
            }
            cout<< "\nSeverity of Illness\nBAD-B\nNORMAL-N\n";
            do
            {
                cout<< "Please choose the severity (B or N): ";
                cin>>severity_input;
                severity = toupper(severity_input);
                if((severity!='B')&&(severity!='N'))
                {
                    cout<<"Invalid Selection"<<endl;
                }
            }
            while((severity!='B')&&(severity!='N'));
            do
            {
                department_name = display_department();
            }
            while(department_name == "Invalid");
            doctor_name = display_doctors(department_name);
            cout<< "\n\n*******Patient Successfully Added To Database.*******\n\n";
            Patient newpatient(patient_name, pat_age, description,  phone_num, blood, severity, department_name, doctor_name);
            newpatient.createRecord(patient_name, pat_age, description,  phone_num, blood, severity, department_name, doctor_name);
            newpatient.assignDoctor(department_name, doctor_name, patient_name);
            newpatient.sort_patientlist(department_name, doctor_name, patient_name, severity);
            newpatient.payment(department_name, patient_name);

        }
        else if(choice==3)
        {
            do
            {
                department_name = display_department();
            }
            while(department_name == "Invalid");
            doctor_name = display_doctors(department_name);
            result = getPatientList(doctor_name, department_name, patient_vec);
            if(result)
            {
                patient_name = patient_vec.front();
                cout<<"Current Patient: "<<patient_name<<endl;
                patient_vec.erase(patient_vec.begin());
                if(patient_vec.empty())
                   {
                    cout<<"No more Patients"<<endl;
                    removePatient(doctor_name, department_name, patient_vec);
                   }
                else
                {
                    cout<<"\nNext In Line: "<<patient_vec.front()<<" Please Get Ready.\n"<<endl;
                    removePatient(doctor_name, department_name, patient_vec);
                    cout<<"\n******End Operation For Bring Patient To Doctor******\n\n";
                }
                patient_vec.clear();
            }
            else
                cout<<"\n*******No Patient at the moment********\n\n";
        }
        else if(choice == 4)
        {
            Patient patient_data;
            cout<<"Enter Patient Name: ";
            getline(cin>>ws, patient_name);
            result = patient_data.displayPatientInformation(patient_name, patient_vec);
            if(result)
            {
                cout<< endl;
                for(string & line:patient_vec)
                {
                    cout<<line<<endl;
                }
                do
                {
med_treatment_input_again:
                    cout<< "Do you want to add medical treatment for this patient?\nPress 'Y' for Yes; 'N' for No:";
                    cin>> med_treatment_input;
                    med_treat = toupper(med_treatment_input);
                    if(med_treat=='Y')
                    {
                        bool success = patient_data.updatePatient(patient_name);
                        if(success)
                        {
                            cout<<"\n*******Medical Record Successfully Added*******\n\n";
                            break;
                        }

                    }
                    else if(med_treat=='N')
                    {
                        cout<< "\n\n********Back To Main Menu********\n\n";
                        break;
                    }
                    else
                        cout<< "\nInvalid Input.Please Select 'Y' for Yes; 'N' for No\n";
                    cin.clear();
                    cin.ignore();
                }
                while((med_treat!='Y')&&(med_treat!='N')&&(!cin));
            }
            else
            {
                cout<<"Patient Record Not Found! Please Ensure The Name Is Correct! \nIf Error Persists, Please Check If Patient Has Been Registered To Database!";
                cout<<"\n\n********Back To Main Menu********\n\n";
            }
            patient_vec.clear();
        }

        else if(choice == 5)
        {
            Patient payment;
            cout<<"Enter Patient Name: ";
            getline(cin>>ws, patient_name);
            payment.update_payment(patient_name);
            remove("payment_list.txt");
            rename("temp_list.txt","payment_list.txt");
            cout<< "******"<<patient_name <<" Paid!******\n";
        }
    }
    while(choice!=6);
    if(choice==6)
    {
        cout<<"Thank you and see you soon!"<<endl;
    }
    return 0;
}
