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
	//
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
	cin >> input;
	cout << "Enter Electric Bill\n";
	electricEmission = ElectricEmission(input);
	//logs electricEmission
	cout << " Output " << electricEmission;

	cin.get();
	return 0;
}