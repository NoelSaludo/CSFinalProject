#include "Main.h"

auto _time = std::chrono::system_clock::now();
std::time_t Time = std::chrono::system_clock::to_time_t(_time);
class CarbonData 
{

public:
	double energy_emission,
	       transport_emission,
	       waste_emission,
			totalemission;
	std::string suggestion;
	std::string DateTime = std::ctime(&Time);
	
};
class Program
{
	static int callback(void* data, int argc, char** argv, char** azColName) {
		int i;
		for (i = 0; i < argc; i++) {
			std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
		}
		std::cout << std::endl;
		return 0;
	}
	void Execute(sqlite3* db, const char* sql, char* zErrMsg) {
		int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << zErrMsg << std::endl;
			sqlite3_free(zErrMsg);
		}
	}
	double calculateDailyEmissions(double time, double averageSpeed, double emissionsFactor[]) {
		double distance = time * averageSpeed;

		if (averageSpeed < 10.0) {
			return distance / emissionsFactor[0];
		}
		else if (averageSpeed <= 20.0) {
			return distance / emissionsFactor[1];
		}
		else {
			return distance / emissionsFactor[2];
		}
	}
	void CalculateEnergyEmission(CarbonData &data)
	{
		double KWH;
		std::cout << "---------------------------------------------\n";
		std::cout << "Please check your Electricity Bill and find KWH used\nEnter KWH : ";
		std::cin >> KWH;
		KWH = KWH * 0.6032;
		data.energy_emission = KWH;
		std::cout << fmt::format("{}kg of CO2 per Month\n",data.energy_emission);
	}
	void CalculateTransportEmission(CarbonData& data) {
		const double gasCarSpeed = 29.9;
		const double dieselCarSpeed = 29.9;
		const double dieselJeepneySpeed = 17.57;
		const double dieselBusSpeed = 14.18;

		double gasCarEmissions[] = { 58.1, 49.5, 39.4 };
		double dieselCarEmissions[] = { 3.0, 2.5, 2.3 };
		double dieselJeepneyEmissions[] = { 2.9, 2.5, 2.3 };
		double dieselBusEmissions[] = { 11.3, 12.4, 11.3 };


		double timeOfTravel;
		char vehicleType;

		std::cout << "Enter time of travel (min): ";
		std::cin >> timeOfTravel;
		CarType:
		std::cout << "Enter type of vehicle (g for Gas Car, d for Diesel Car, j for Diesel Jeepney, b for Diesel Bus): ";
		std::cin >> vehicleType;

		vehicleType = toupper(vehicleType);

		double dailyEmissions = 0;
		timeOfTravel /= 60;
		if (vehicleType == 'G') {
			dailyEmissions = calculateDailyEmissions(timeOfTravel, gasCarSpeed, gasCarEmissions);
		}
		else if (vehicleType == 'D') {
			dailyEmissions = calculateDailyEmissions(timeOfTravel, dieselCarSpeed, dieselCarEmissions);
		}
		else if (vehicleType == 'J') {
			dailyEmissions = calculateDailyEmissions(timeOfTravel, dieselJeepneySpeed, dieselJeepneyEmissions);
		}
		else if (vehicleType == 'B') {
			dailyEmissions = calculateDailyEmissions(timeOfTravel, dieselBusSpeed, dieselBusEmissions);
		}
		else {
			std::cout << "Invalid vehicle type. Please enter G, D, J, or B." << std::endl;
			goto CarType;
		}
			std::cout << "Monthly Emissions: " << dailyEmissions * 30 << " kilograms of CO2" << std::endl;
			data.transport_emission = dailyEmissions * 30;
	}
	void CalculateWasteEmission(CarbonData& data){

		double fdw, pw, gw, ww, tw, waste,
			docf, mcf, f, gwp, fd,
			paper, garden, wood, textile;

		std::cout << "Input the mass(kg) per month of the waste in terms of: \n" << "Food waste: ";
		std::cin >> fdw;
		std::cout << "Paper: ";
		std::cin >> pw;
		std::cout << "Garden: ";
		std::cin >> gw;
		std::cout << "Wood: ";
		std::cin >> ww;
		std::cout << "Textile: ";
		std::cin >> tw;

		docf = 0.5;
		mcf = 1;
		f = 0.5;
		gwp = 28;
		fd = fdw * 0.15 * 0.77 * docf * mcf * f * gwp;
		paper = pw * 0.4 * 0.98 * docf * mcf * f * gwp;
		garden = gw * 0.17 * 0.77 * docf * mcf * f * gwp;
		wood = ww * 0.43 * 0.98 * docf * mcf * f * gwp;
		textile = tw * 0.24 * 0.77 * docf * mcf * f * gwp;
		waste = fd + paper + garden + wood + textile;

		std::cout << "Your total waste emission is: " << waste << " kg CO2.\n";
		data.waste_emission = waste;
	}
	void CalculateTotalEmission(CarbonData& data){
		data.transport_emission = 30;
		data.totalemission = data.energy_emission + data.transport_emission + data.waste_emission;
	}
	void SuggestionFunction(CarbonData& data)
	{
		double average_threshold = 201.58, bad_threshold = 277.19;
		std::string Suggestion = "Suggestion to reduce your monthly carbon emission:\n";
		if (data.energy_emission > bad_threshold)
		{
			Suggestion += "";//5 suggestion
		}
		else if(data.energy_emission > average_threshold)
		{

			Suggestion += "";//3 suggestion
		}
		else 
		{

			Suggestion += "";//1 suggestion
		}
		if (data.transport_emission > bad_threshold) 
		{

			Suggestion += "";//same here
		}
		else if (data.transport_emission > average_threshold) 
		{

			Suggestion += "";//same here
		}
		else 
		{

			Suggestion += "";//same here
		}
		if (data.waste_emission > bad_threshold) 
		{

			Suggestion += "";//same here
		}
		else if (data.waste_emission > average_threshold) 
		{

			Suggestion += "";//same here
		}
		else 
		{

			Suggestion += "";//same here
		}

		data.suggestion = Suggestion;
	}

	
public:

	int Main()
	{
		CarbonData data;
		sqlite3* db;
		char* zErrMsg = 0;
		int rc;
		const char* sql;
		sqlite3_stmt* stmt;
			

		std::cout << "CarbonFootprint Calculator\n";
		CalculateEnergyEmission(data);
		CalculateTransportEmission(data);
		CalculateWasteEmission(data);
		CalculateTotalEmission(data);
		SuggestionFunction(data);


		//do not touch please
		rc = sqlite3_open("calculator.db", &db);
		if (rc) {
			std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
			return (0);
		}
		sql = "CREATE TABLE IF NOT EXISTS carbondata(" \
			"id INTEGER PRIMARY KEY AUTOINCREMENT," \
			"energy_emission DOUBLE NOT NULL," \
			"transport_emission DOUBLE NOT NULL," \
			"waste_emission DOUBLE NOT NULL,"\
			"total_emission DOUBLE NOT NULL,"\
			"suggestions TEXT,"\
			"date TEXT NOT NULL);";

		Execute(db, sql, zErrMsg);
		sql = "INSERT INTO carbondata (energy_emission, transport_emission, waste_emission, total_emission, suggestions, date) VALUEs ( ?, ?, ?, ?, ?, ?);";
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			return(-1);
		}
		rc = sqlite3_bind_double(stmt, 1, data.energy_emission); 
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			return(-1);
		}
		rc = sqlite3_bind_double(stmt, 2, data.transport_emission); 
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			return(-1);
		}
		rc = sqlite3_bind_double(stmt, 3, data.waste_emission); 
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			return(-1);
		}
		rc = sqlite3_bind_double(stmt, 4, data.totalemission);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			return(-1);
		}
		rc = sqlite3_bind_text(stmt, 5, data.suggestion.c_str(), -1, NULL);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			return(-1);
		}
		rc = sqlite3_bind_text(stmt, 6, data.DateTime.c_str(), -1, NULL);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			return(-1);
		}
		rc = sqlite3_step(stmt); 
		if (rc != SQLITE_DONE) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			return(-1);
		}
		else {
			std::cout << "Record inserted successfully" << std::endl;
		}
		sqlite3_finalize(stmt);

		sql = "SELECT energy_emission, transport_emission, waste_emission, total_emission, suggestions, date FROM carbondata;";
		Execute(db, sql, zErrMsg);
		sql = "DELETE FROM carbondata;";
		Execute(db, sql, zErrMsg);
		sqlite3_close(db);
		return 0;
	}
};

int main()
{
	Program program;
	program.Main();
	return 0;
}