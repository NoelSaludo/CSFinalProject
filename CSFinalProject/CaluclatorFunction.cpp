#include <iostream>
#include <fmt/format.h>
#include "CarbonFootprintCalculator.h"
#include "CarbonData.h"

double Program::ElectricEmission(double electricBill)
{
	return floor((electricBill / 56.98) * 105);
}
//add more calculations
//remember that we are going to also check which emission causes the high emission 
//so we can create a custom suggestion based on the calculation

void Program::TotalEmission()
{
	//calculates total carbon footprint
}
