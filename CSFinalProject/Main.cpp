#include <iostream>
#include <string>
#include <fmt/format.h>
#include <sqlite3.h>
class CarbonData 
{
public:
	int id;
	double energy_emission,
	       transport_emission,
	       waste_emission;
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
	void create_table(sqlite3* db, const char* sql, char* zErrMsg) {
		int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << zErrMsg << std::endl;
			sqlite3_free(zErrMsg);
		}
		else {
			std::cout << "Table created successfully" << std::endl;
		}
	}
	void insert_records(sqlite3* db, const char* sql, char* zErrMsg) {
		int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << zErrMsg << std::endl;
			sqlite3_free(zErrMsg);
		}
		else {
			std::cout << "Records inserted successfully" << std::endl;
		}
	}
	void read_records(sqlite3* db, const char* sql, char* zErrMsg) {
		int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << zErrMsg << std::endl;
			sqlite3_free(zErrMsg);
		}
		else {
			std::cout << "Records read successfully" << std::endl;
		}
	}
	void update_record(sqlite3* db, const char* sql, char* zErrMsg) {
		int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << zErrMsg << std::endl;
			sqlite3_free(zErrMsg);
		}
		else {
			std::cout << "Record updated successfully" << std::endl;
		}
	}
	void delete_record(sqlite3* db, const char* sql, char* zErrMsg) {
		int rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << zErrMsg << std::endl;
			sqlite3_free(zErrMsg);
		}
		else {
			std::cout << "Record deleted successfully" << std::endl;
		}
	}
	//Enter some functions below
	void CalculateEnergyEmission(CarbonData &data){
		char input;
		double energy_emission;
		int number_of_appliances;
		std::cout << "Do you own a television (Y/n)";
		std::cin >> input;
		if (input == 'Y') {
			std::cout << "How many?";
			std::cin >> number_of_appliances;
			energy_emission = number_of_appliances * 8.91;
		}

	}
	void CalculateTransportEmission(){}
	void CalculateWasteEmission(){}
	void CalculateTotalEmission(){}
	void SuggestionFunction(){}

	
public:

	int Main()
	{
		//use input in every function
		double input;
		CarbonData data;
		sqlite3* db;
		char* zErrMsg = 0;
		int rc;
		const char* sql;
		sqlite3_stmt* stmt;
		
		rc = sqlite3_open("calculator.db", &db);
		if (rc) {
			std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
			return (0);
		}
		sql = "CREATE TABLE IF NOT EXISTS carbondata(" \
			"id INTEGER PRIMARY KEY," \
			"energy_emission DOUBLE," \
			"gas_emission DOUBLE," \
			"waste_emission DOUBLE);";

		create_table(db, sql, zErrMsg);
		data.energy_emission = 13.32;
		data.id = 1;
		data.transport_emission = 13.31;
		data.waste_emission = 14.14;
		sql = "INSERT INTO carbondata VALUEs (?, ?, ?, ?);";
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			return(-1);
		}
		rc = sqlite3_bind_int(stmt, 1, data.id); // bind the id value to the first placeholder
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			return(-1);
		}
		rc = sqlite3_bind_double(stmt, 2, data.energy_emission); // bind the name value to the second placeholder
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			return(-1);
		}
		rc = sqlite3_bind_double(stmt, 3, data.energy_emission); // bind the age value to the third placeholder
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			return(-1);
		}
		rc = sqlite3_bind_double(stmt, 4, data.waste_emission); // bind the email value to the fourth placeholder
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			return(-1);
		}
		rc = sqlite3_step(stmt); // execute the statement and check for errors
		if (rc != SQLITE_DONE) {
			std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
			return(-1);
		}
		else {
			std::cout << "Record inserted successfully" << std::endl;
		}
		sqlite3_finalize(stmt);

		sql = "SELECT * FROM carbondata;";
		read_records(db, sql, zErrMsg);
		return 0;
			

		std::cout << "CarbonFootprint Calculator\n";
		return 0;
	}
};

int main()
{
	Program program;
	program.Main();
	return 0;
}