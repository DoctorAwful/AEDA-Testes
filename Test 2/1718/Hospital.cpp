/*
 * Hospital.cpp
 */

#include "Hospital.h"
//
#include <algorithm>
#include <iostream>

Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{
	list<Doctor> aux = doctors;
	list<Doctor>::iterator it;
	unsigned numPatient;
	numPatient = 0;
	for (it = aux.begin(); it != aux.end(); it++)
	{
		if (medicalSpecialty == it->getMedicalSpecialty())
		{
			queue<Patient> auxPatients = it->getPatients();

			while (!(auxPatients.empty()))
			{
				numPatient++;
				auxPatients.pop();
			}
		}

	}


	return numPatient;

}

bool compareDoctors(const Doctor &d1, const Doctor &d2)
{
	if (d1.getPatients().size() < d2.getPatients().size())
		return true;
	else if (d1.getPatients().size() == d2.getPatients().size())
	{ 
		if (d1.getMedicalSpecialty() < d2.getMedicalSpecialty())
			return true;
		else if (d1.getMedicalSpecialty() == d2.getMedicalSpecialty())
		{
			if (d1.getCode() < d2.getCode())
				return true;
			return false;
		}
		else return false;

	}
	else return false;
		


}

void Hospital::sortDoctors() {

	doctors.sort(compareDoctors);

}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
	
	Doctor novo(codM1, medicalSpecialty1);
	unsigned int especialidade = 0;
	list<Doctor>::iterator it;

	for (it = doctors.begin(); it != doctors.end(); it++)
	{
		if (it->getMedicalSpecialty() == medicalSpecialty1)
			especialidade++;
	}

	if (especialidade < 3)
	{
		doctors.push_back(novo);
		return true;
	}
	return false;

}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {

	list<Doctor>::iterator it;
	queue<Patient> p1;
	bool notfound = true;

	for (it = doctors.begin(); it != doctors.end(); it++)
	{
		if (it->getCode() == codM1)
		{
			notfound = false;
			p1 = it->getPatients();
			doctors.erase(it);
			return p1;
		}
	}

	if (notfound)
	{
		throw(DoctorInexistent());
	}
	
	return p1;

}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {
	
	
	bool entrou = false;
	Patient novopaciente(cod1, medicalSpecialty1);

	list<Doctor>::iterator it;
	list<Doctor>::iterator currentdoctor;

	for (it = doctors.begin(); it != doctors.end(); it++)
	{
		if (it->getMedicalSpecialty() == medicalSpecialty1)
		{
		
			
			if (!(entrou))
			{
				entrou = true;
				currentdoctor = it;

			}
			else
			{
				if (currentdoctor->getPatients().size() > it->getPatients().size())
				{
					currentdoctor = it;
				}
			}
		}

	}
	
	if (entrou)
	{
		currentdoctor->addPatient(novopaciente);
	
	}
	
	return entrou;

}



void Hospital::processPatient(unsigned codM1) {
	

	Patient removedPatient(0, "");
	bool nospace = true;
	bool founddoctor = false;
	bool nopatients = true;

	stack<Patient> novastack;
	list<Doctor>::iterator it;
	list<stack<Patient> >::iterator iterator;

	for (it = doctors.begin(); it != doctors.end(); it++)
	{
		if (it->getCode() == codM1)
		{
			founddoctor = true;

			if (!(it->getPatients().empty()))
			{
				nopatients = false;
				removedPatient = it->removeNextPatient();

			}

		}	

	}
	
	if (founddoctor && !(nopatients)) {
		for (iterator = letterTray.begin(); iterator != letterTray.end(); iterator++)
		{
			if (iterator->size() < trayCapacity)
			{

				nospace = false;
				iterator->push(removedPatient);
				return;
			}
		}

		if (nospace)
		{
			novastack.push(removedPatient);
			addTrays(novastack);
		}
	}
}


unsigned Hospital::removePatients(unsigned codP1) {
	
	
	unsigned int contador = 0;


	for (auto iterator = letterTray.begin(); iterator != letterTray.end(); iterator++)
	{
		if (!(iterator->empty()))
		{
			if (iterator->top().getCode() == codP1)
			{
				iterator->pop();
				contador++;
			}
		}

		if (iterator->empty()) 
			iterator = letterTray.erase(iterator);
	}
	return contador;

}



