#include <iostream>
#include <fmt/format.h>

class CarbonData 
{
public:
	double electricEmission,
		gasEmission,
		oilEmission,
		carEmission;
	int flightsOverFourHours,
		flightsUnderFourHours;
	bool doesUserRecycleNewspaper,
		doesUserRecycleAluminum;
};
class Program
{
public:
	double ElectricEmission(double ElectricBill)
	{
		return floor((ElectricBill / 56.98) * 105);
	}
	double GasEmission(double GasBill)
	{

	}
	double OilEmission(double OilBill)
	{

	}
	double CarEmission(double CarBill)
	{

	}
	int FlightsOverFourHours(int numberOfFlights)
	{

	}
	int FlightsUnderFourHours(double numberOfFlights)
	{

	}
	int DoesUserRecycleNewspaper(bool recycles)
	{

	}
	int DoesUserRecycleAluminum(bool recycles)
	{

	}
	void TotalEmission()
	{

	}
	void Suggestion()
	{
		
	}
	void Main()
	{
		//use input in every function
		double input;
		CarbonData data;

		std::cout << "CarbonFootprint Calculator\n";
		std::cout << "Enter Electric Bill\n";
		std::cin >> input;
		data.electricEmission = ElectricEmission(input);
		fmt::print("Output: {0}", data.electricEmission); //logs the Outpput for testing
	}
};

int main()
{
	Program program;
	program.Main();
	return 0;
}