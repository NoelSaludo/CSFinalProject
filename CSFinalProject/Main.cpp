#include <iostream>
#include <conio.h>

using namespace std;

double ElectricEmission(double electricBill)
{
	return (electricBill / 56.98) * 105;
}
//add more calculations
//remember that we are going to also check which emission causes the high emission 
//so we can create a custom suggestion based on the calculation

void TotalCarbonFootprint()
{
	//calculates total carbon footprint
}

int main()
{
	//use input in every function
	double input,
		electricEmission,
		gasEmission,
		oilEmission,
		carEmission;
	int flightsOverFourHours,
		flightsUnderFourHours;
	bool doesUserRecycleNewspaper,
		doesUserRecycleAluminum;
	//request for the user input
	cout << "CarbonFootprin Calculator\n";
	cout << "Enter Electric Bill\n";
	cin >> input;
	electricEmission = ElectricEmission(input);
	cout << " Output " << electricEmission; //logs the Outpput for testing

	cin.get();
	return 0;
}