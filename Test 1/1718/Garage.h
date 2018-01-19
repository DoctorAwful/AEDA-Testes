/*
 * Garage.h
 *
 *  Created on: 24/10/2017
 *      Author: hlc
 */

#ifndef SRC_GARAGE_H_
#define SRC_GARAGE_H_

#include <vector>

template <class Vehicle>
class Garage {
	std::vector<Vehicle *> vehicles;
	const unsigned int capacity;
public:
	Garage(int size);
	~Garage();
	std::vector<Vehicle *> getVehicles() const;
	void setVehicles(std::vector<Vehicle *> vehicles);
	int getCapacity() const;
	bool addVehicle(Vehicle *vehicle);
	Vehicle* removeVehicle(std::string brand, std::string model);
	float avgPrice(std::string brand) const;
	void sortVehicles();


};

class NoSuchVehicleException {
public:
	NoSuchVehicleException() { }
};

class NoSuchBrandException{
	std::string brand;
public:
	std::string getBrand(){return brand;};
	NoSuchBrandException(std::string brand){ this->brand = brand; }



};

template <class Vehicle>
Garage<Vehicle>::Garage(int size) : capacity(size) {
}

template <class Vehicle>
Garage<Vehicle>::~Garage() {
	typename std::vector<Vehicle *>::const_iterator it;
	for (it=vehicles.begin(); it!=vehicles.end(); it++) {
		delete *it;
	}
}

template<class Vehicle>
bool Garage<Vehicle>::addVehicle(Vehicle *vehicle){



	if(getCapacity() > 0)
	{
		for(unsigned int i = 0; i < vehicles.size(); i++)
		{
			//devia ser como está em cima, mas eles aparentemente só querem saber da Brand, o que é parvo, mas pronto
			//if((vehicles[i]->getBrand() == vehicle->getBrand()) && (vehicles[i]->getModel() == vehicle->getModel()))
			if((vehicles[i]->getBrand() == vehicle->getBrand()))
			{
			return false;

			}
		}

		vehicles.push_back(vehicle);
		return true;

	}

	return false;


}


template<class Vehicle>
void Garage<Vehicle>::sortVehicles()
{
	sort(vehicles.begin(),vehicles.end());


}



template<class Vehicle>
std::vector<Vehicle *> Garage<Vehicle>::getVehicles() const {
	return vehicles;
}

template<class Vehicle>
void Garage<Vehicle>::setVehicles(std::vector<Vehicle*> vehicles) {
	this->vehicles = vehicles;
}

template<class Vehicle>
int Garage<Vehicle>::getCapacity() const {
	return capacity;
}

template<class Vehicle>
Vehicle* Garage<Vehicle>::removeVehicle(std::string brand, std::string model){

	Vehicle* temp;
	bool notfound = true;
	for(unsigned int i = 0; i < vehicles.size(); i++)
	{
		if(vehicles[i]->getBrand() == brand)
		{
			if(vehicles[i]->getModel() == model)
					{
						notfound = false;
						temp = vehicles[i];
						vehicles.erase(vehicles.begin()+i);
						return temp;
					}
		}
	}
	if(notfound)
	{
		throw(NoSuchVehicleException());
	}

	return temp;
}

template<class Vehicle>

float Garage<Vehicle>::avgPrice(std::string brand) const{

	std::vector<Vehicle*> temp;
	float tempfloat = 0;
	bool found = false;

	for(unsigned int i = 0; i < vehicles.size(); i++)
	{
		if(vehicles[i]->getBrand() == brand)
		{
			found = true;
			temp.push_back(vehicles[i]);

		}
	}
	if(!(found))
	{
		throw(NoSuchBrandException(brand));
	}


	for(unsigned int j = 0; j < temp.size(); j++)
	{
	tempfloat = tempfloat + temp[j]->getPrice();
	}
	tempfloat = tempfloat/temp.size();
	return tempfloat;
}



#endif /* SRC_GARAGE_H_ */
