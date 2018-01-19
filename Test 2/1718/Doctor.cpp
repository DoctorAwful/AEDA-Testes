/*
 * Doctor.cpp
 */

#include "Doctor.h"


Patient::Patient(unsigned codP, string mS): codeP(codP), medicalSpecialty(mS)
{}

string Patient::getMedicalSpecialty() const {
	return medicalSpecialty;
}

unsigned Patient::getCode() const {
	return codeP;
}

Doctor::Doctor(unsigned codM, string mS): codeM(codM), medicalSpecialty(mS)
{}


Doctor::Doctor(unsigned codM, string mS, queue<Patient> patients1): codeM(codM), medicalSpecialty(mS), patients(patients1)
{}

unsigned Doctor::getCode() const {
	return codeM;
}

string Doctor::getMedicalSpecialty() const {
	return medicalSpecialty;
}

queue<Patient> Doctor::getPatients() const {
	return patients;
}

void Doctor::addPatient(const Patient &p1) {
	patients.push(p1);
}

Patient Doctor::removeNextPatient() {
	if (!patients.empty()) {
		Patient p1 = patients.front();
		patients.pop();
		return p1;
	}
	else throw PatientInexistent();
}




void Doctor::moveToFront(unsigned codP1) {
	
	queue<Patient>aux = patients;
	queue<Patient>temp;
	Patient auxPatient(0, "");
	bool found = false;
	
	while (!(aux.empty()))
	{
	
		if (aux.front().getCode() == codP1)
		{	
			found = true;
			auxPatient = aux.front();
		}
		aux.pop();
	}
	
		
	if (found)
	{
		temp.push(auxPatient);
		
		while (!(patients.empty()))
		{
			if (patients.front().getCode() != codP1)
				temp.push(patients.front());
			patients.pop();

		} 
		patients = temp;
	} 


}

