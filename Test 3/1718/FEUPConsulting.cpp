/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"
#include <iostream>

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for(; it1 != it2; it1++) {
			ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for(int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
	
	bool existe = false;
	
		BSTItrIn<Expertize> it(expertizes);


		while (!(it.isAtEnd()))
		{

			if( (it.retrieve().getName() == expertizeAvailable)&&(it.retrieve().getCost() == cost))
			{
				
				existe = true;
				it.retrieve().addConsultant(student);
			}
			it.advance();
		}

		if (!existe)
		{
			
			Expertize nova(expertizeAvailable, cost);
			nova.addConsultant(student);
			addNewExpertize(nova);
		}


}

vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
	
	BSTItrIn<Expertize> it(expertizes);


	while (!(it.isAtEnd()))
	{

		if ((it.retrieve().getName() == project->getExpertize()) && (it.retrieve().getCost() == project->getCost()))
		{

			
			for (unsigned int i = 0; i < it.retrieve().getConsultants().size(); i++)
			{
				if (it.retrieve().getConsultants()[i]->getCurrentProject() == "")
					temp.push_back(it.retrieve().getConsultants()[i]);
			}

		}
		it.advance();
	}


	return temp;

}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
	bool naoassociado = true;
	bool interessado = false;
	vector<Student*> temp;	
	
	if (project->getConsultant() != NULL) {
		naoassociado = false;
	}

	temp = getCandidateStudents(project);
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		if (temp[i] == student)
		{
			interessado = true;
			
		}
	}

	if (naoassociado && interessado)
	{
		student->addProject(project->getTitle());
		project->setConsultant(student);
		return true;
	}
	return false;

}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
	
	students.insert(student);

}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	HashTabStudentPtr::iterator it, it2;

	for (it = students.begin(); it != students.end(); it++)
	{
		if (it->getEMail() == student->getEMail())
		{
			
			student->setEMail(newEMail);
			students.insert(student);
			it2 = it;
		}
	}
	students.erase(it2);
}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
	
	for(unsigned int i = 0; i < candidates.size(); i++)
	{
		if (candidates.at(i).getPastProjects().size() >= min)
			activeStudents.push(candidates.at(i));

	}

}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
	
	//alternativamente, pode-se não fazer o aux e o dux, e em vez disso copiar só para auxqueue, fazer pop a esta e comparar os tops
	if (!activeStudents.empty()) {
		priority_queue<Student> auxqueue = activeStudents;
		auto aux = activeStudents.top();
		auxqueue.pop();
		Student dux = auxqueue.top();

		if (aux.getPastProjects().size() == dux.getPastProjects().size())
			return 0;
		else {
		studentMaximus = aux;
		return activeStudents.size();
	}
	}
	return 0;
	
}





















