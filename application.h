#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


bool getPatientList(string doc_name, string dept_name, vector<string> &patient_vector);

bool removePatient(string doc_name, string dept_name, vector<string> &patient_vector);
