#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp> // For nlohmann/json library
#include <curl/curl.h> // For libcurl
#include <sstream>
#include <exception>

using namespace std;

// Location class  
class Location
{
private:
	std::string name;
	double latitude;
	double longitude;
public:
	Location(std::string name, double latitude, double longitude)
	{
		this->name = name;
		this->latitude = latitude;
		this->longitude = longitude;
	}

	std::string getName() 
	{ 
		return name; 
	}
	double getLatitude()
	{ 
		return latitude; 
	}
	double getLongitude()
	{
		return longitude;
	}
};

// WeatherVariable class  
class WeatherVariable
{
private:
	std::string name;
	double value;
public:
	WeatherVariable(std::string name, double value)
	{
		this->name = name;
		this->value = value;
	}
	std::string getName() 
	{
		return name; 
	}
	double getValue()
	{ 
		return value; 
	}
};

// WeatherForecastingSystem class  
class WeatherForecastingSystem 
{
private:
	std::string apiKey;
	std::string apiUrl;
public:
	WeatherForecastingSystem(std::string apiKey, std::string apiUrl)
	{
		this->apiKey = apiKey;
		this->apiUrl = apiUrl;
	}

	std::vector fetchWeatherForecast(Location location) 
	{
		// Implement API interaction to fetch weather forecast data  
		// For demonstration purposes, return a sample vector  
		std::vector forecast;
		forecast.push_back(WeatherVariable("Temperature", 25.0));
		forecast.push_back(WeatherVariable("Wind Speed", 10.0));
		return forecast;
	}
};

// HistoricalWeatherSystem class  
class HistoricalWeatherSystem : public WeatherForecastingSystem 
{
public:
	HistoricalWeatherSystem(std::string apiKey, std::string apiUrl) : WeatherForecastingSystem(apiKey, apiUrl)
	{}

	std::vector fetchHistoricalWeather(Location location, std::string date)
	{
		// Implement API interaction to fetch historical weather data  
		// For demonstration purposes, return a sample vector  
		std::vector historicalData;
		historicalData.push_back(WeatherVariable("Temperature", 20.0));
		historicalData.push_back(WeatherVariable("Wind Speed", 15.0));
		return historicalData;
	}
};

// AirQualityForecastingSystem class  
class AirQualityForecastingSystem 
{
private:
	std::string apiKey;
	std::string apiUrl;
public:
	AirQualityForecastingSystem(std::string apiKey, std::string apiUrl)
	{
		this->apiKey = apiKey;
		this->apiUrl = apiUrl;
	}

	std::vector fetchAirQualityForecast(Location location) 
	{
		// Implement API interaction to fetch air quality data  
		// For demonstration purposes, return a sample vector  
		std::vector airQuality;
		airQuality.push_back(WeatherVariable("AQI", 50.0));
		airQuality.push_back(WeatherVariable("PM2.5", 20.0));
		return airQuality;
	}
};

// ExportData class  
class ExportData 
{
public:
	void exportToCSV(std::vector data, std::string filename) 
	{
		std::ofstream file(filename);
		file << "Variable,Value\n";

		for (auto& variable : data)
		{
			file << variable.getName() << "," << variable.getValue() << "\n";
		}
		file.close();
	}

	void exportToJSON(std::vector data, std::string filename)
	{
		Json::Value jsonData;

		for (auto& variable : data)
		{
			jsonData[variable.getName()] = variable.getValue();
		}
		std::ofstream file(filename);
		file << jsonData;
		file.close();
	}
};

int main() 
{
	// Create a location object  
	Location location("New York", 40.7128, -74.0060);

	// Create a weather forecasting system object  
	WeatherForecastingSystem weatherSystem("API_KEY", "https://api.open-meteo.com/v1/forecast");

	// Fetch weather forecast data  
	std::vector forecast = weatherSystem.fetchWeatherForecast(location);

	// Display weather forecast data  
	std::cout << "Weather Forecast:\n";
	for (auto& variable : forecast)
	{
		std::cout << variable.getName() << ": " << variable.getValue() << "\n";
	}

	// Create a historical weather system object  
	HistoricalWeatherSystem historicalSystem("API_KEY", "https://api.open-meteo.com/v1/history");

	// Fetch historical weather data  
	std::vector historicalData = historicalSystem.fetchHistoricalWeather(location, "2022-01-01");

	// Display historical weather data  
	std::cout << "Historical Weather Data:\n";
	for (auto& variable : historicalData)
	{
		std::cout << variable.getName() << ": " << variable.getValue() << "\n";
	}

	// Create an air quality forecasting system object  
	AirQualityForecastingSystem airQualitySystem("API_KEY", "https://api.airqualityapi.com/v1/forecast");

	// Fetch air quality data  
	std::vector airQuality = airQualitySystem.fetchAirQualityForecast(location);

	// Display air quality data  
	std::cout << "Air Quality:\n";
	for (auto& variable : airQuality) 
	{
		std::cout << variable.getName() << ": " << variable.getValue() << "\n";
	}

	// Export data to CSV and JSON  
	ExportData exporter;
	exporter.exportToCSV(forecast, "weather_forecast.csv");
	exporter.exportToJSON(forecast, "weather_forecast.json");

	return 0;
}
