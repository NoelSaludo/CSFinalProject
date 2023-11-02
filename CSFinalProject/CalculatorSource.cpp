#include <iostream>
#include <fmt/format.h>
#include "CarbonFootprintCalculator.h"
#include "CarbonData.h"

using namespace std;

void Program::Main()
{
	//use input in every function
	double input;
	CarbonData data;
	//request for the user input
	cout << "CarbonFootprin Calculator\n";
	cout << "Enter Electric Bill\n";
	cin >> input;
	data.electricEmission = ElectricEmission(input);
	fmt::print("Output: {0}", data.electricEmission); //logs the Outpput for testing
}