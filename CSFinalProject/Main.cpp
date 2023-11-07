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
	void CalculateEnergyEmission(){}
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
		std::cout << "Enter Electric Bill\n";
		std::cin >> input;
		data.set_energy_emission(input);//logs the Outpput for testing
	}
};

int main()
{
	Program program;
	program.Main();
	return 0;
}