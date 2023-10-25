#include <iostream>

// Function to convert data to a yearly basis
double convertToYearly(double data, std::string interval) {
    if (interval == "weekly") {
        return data * 52.0;  // Assuming 52 weeks in a year
    }
    else if (interval == "monthly") {
        return data * 12.0;  // Assuming 12 months in a year
    }
    return data;  // If yearly or invalid input, return as is
}

// Function to calculate the carbon footprint for a family in the Philippines
double calculateCarbonFootprint(int numPeople, double electricityUsage, double gasUsage, double carMileage) {
    // Define some adjusted constants for emission factors in the Philippines (in metric tons per year)
    const double ELECTRICITY_EMISSION_FACTOR = 0.440; // Adjusted for the Philippines
    const double GAS_EMISSION_FACTOR = 2.68; // Adjusted for the Philippines
    const double CAR_EMISSION_FACTOR = 2.30; // Assuming a typical car for the Philippines

    // Calculate emissions
    double electricityEmissions = electricityUsage * ELECTRICITY_EMISSION_FACTOR;
    double gasEmissions = gasUsage * GAS_EMISSION_FACTOR;
    double carEmissions = carMileage * CAR_EMISSION_FACTOR;

    // Total emissions for the family
    double totalEmissions = (electricityEmissions + gasEmissions + carEmissions) * numPeople;

    return totalEmissions;
}

int main() {
    int numPeople;
    double electricityUsage, gasUsage, carMileage;
    std::string dataInterval;

    // Select the time interval for data input
    std::cout << "Select the time interval for data input (weekly, monthly, or yearly): ";
    std::cin >> dataInterval;

    // Input data
    std::cout << "Enter the number of people in the family: ";
    std::cin >> numPeople;

    // Ask for and convert electricity usage (in kilowatts)
    std.cout << "Enter the electricity usage (in kilowatts): ";
    std::cin >> electricityUsage;
    electricityUsage = convertToYearly(electricityUsage, dataInterval);

    // Ask for and convert gas usage (in cubic meters)
    std::cout << "Enter the gas usage (in cubic meters): ";
    std::cin >> gasUsage;
    gasUsage = convertToYearly(gasUsage, dataInterval);

    // Ask for and convert car mileage (in miles)
    std::cout << "Enter the car mileage (in miles): ";
    std::cin >> carMileage;
    carMileage = convertToYearly(carMileage, dataInterval);

    // Calculate the carbon footprint
    double carbonFootprint = calculateCarbonFootprint(numPeople, electricityUsage, gasUsage, carMileage);

    // Output the result
    std::cout << "The estimated carbon footprint for your family in the Philippines is: " << carbonFootprint << " metric tons per year." << std::endl;

    return 0;
}