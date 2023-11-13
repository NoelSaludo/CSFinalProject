#include <iostream>
#include <string>
#include <fmt/format.h>
#include <sqlite3.h>
#include <ctime>
class CarbonData 
{
public:
	double energy_emission,
	       transport_emission,
	       waste_emission,
			totalemission;
	std::string suggestion;
	time_t Date = time(0);
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
		else {
			std::cout << "Execution Success" << std::endl;
		}
	}
	//Enter some functions below
	void CalculateEnergyEmission(CarbonData &data){
		double KWH;
		std::cout << "Energy Emission\n";
		std::cout << "---------------------------------------------\n";
		std::cout << "Please check your Electricity Bill and find KWH used\nEnter KWH : ";
		std::cin >> KWH;
		KWH = KWH * 0.6032;
		data.energy_emission = KWH;
		std::cout << fmt::format("{}kg of CO2 per Month",data.energy_emission);
	}
	void CalculateTransportEmission(CarbonData& data){}
	void CalculateWasteEmission(CarbonData& data){}
	void CalculateTotalEmission(CarbonData& data){}
	void SuggestionFunction(CarbonData& data)
	{
		double average_threshold = 201.58, bad_threshold = 277.19;
		std::string Suggestion = "Suggestion to reduce your monthly carbon emission:\n";
		if (data.energy_emission > bad_threshold){
			Suggestion += "";//5 suggestion
		}
		else if(data.energy_emission > average_threshold){

			Suggestion += "";//3 suggestion
		}
		else {

			Suggestion += "";//1 suggestion
		}
		if (data.transport_emission > bad_threshold) {

			Suggestion += "";//same here
		}
		else if (data.transport_emission > average_threshold) {

			Suggestion += "";//same here
		}
		else {

			Suggestion += "";//same here
		}
		if (data.waste_emission > bad_threshold) {

			Suggestion += "";//same here
		}
		else if (data.waste_emission > average_threshold) {

			Suggestion += "";//same here
		}
		else {

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
		SuggestionFunction(data);


		//do not touch please
		rc = sqlite3_open("calculator.db", &db);
		if (rc) {
			std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
			return (0);
		}
		sql = "CREATE TABLE IF NOT EXISTS carbondata(" 
			"id INTEGER PRIMARY KEY AUTOINCREMENT," 
			"energy_emission DOUBLE NOT NULL," 
			"gas_emission DOUBLE NOT NULL," 
			"waste_emission DOUBLE NOT NULL,"
			"total_emission DOUBLE NOT NULL,"
			"suggestions TEXT,"
			"date TEXT NOT NULL);";

		Execute(db, sql, zErrMsg);
		sql = "INSERT INTO carbondata (energy_emission, gas_emission, waste_emission, total_emission, suggestion) VALUEs ( ?, ?, ?, ?, ?);";
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
		rc = sqlite3_bind_double(stmt, 2, data.energy_emission); 
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
		rc = sqlite3_bind_text(stmt, 5, std::to_string(data.Date).c_str(), -1, NULL);
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

		sql = "SELECT energy_emission, transport_emission, waste_emission, total_emission FROM carbondata;";
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