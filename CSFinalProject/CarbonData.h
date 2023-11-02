#pragma once
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