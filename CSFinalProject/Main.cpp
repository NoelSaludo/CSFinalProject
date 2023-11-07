#include <iostream>
#include <fmt/format.h>

class CarbonData 
{
	double _energy_emission,
	       _transport_emission,
	       _waste_emission;
public:
	double energy_emission() const
	{
		return _energy_emission;
	}

	void set_energy_emission(double energy_emission)
	{
		this->_energy_emission = energy_emission;
	}

	double transport_emission1() const
	{
		return _transport_emission;
	}

	void set_transport_emission(double transport_emission)
	{
		this->_transport_emission = transport_emission;
	}

	double waste_emission1() const
	{
		return _waste_emission;
	}

	void set_waste_emission(double waste_emission)
	{
		this->_waste_emission = waste_emission;
	}
};
class Program
{
	//Enter some functions below
	void CalculateEnergyEmission(CarbonData &data){
		char input;
		double energy_emission;
		int number_of_appliances;
		std::cout << "Do you own a television (Y/n)";
		std::cin >> input;
		if (input == 'Y') {
			std::cout << "How many?";
			std::cin >> number_of_appliances;
			energy_emission = number_of_appliances * 8.91;
		}

	}
	void CalculateTransportEmission(){}
	void CalculateWasteEmission(){}
	void CalculateTotalEmission(){}
	void SuggestionFunction(){}
	
public:
	void Main()
	{
		//use input in every function
		double input;
		CarbonData data;

		std::cout << "CarbonFootprint Calculator\n";
	}
};

int main()
{
	Program program;
	program.Main();
	return 0;
}