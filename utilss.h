#pragma once
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>

template <typename T>
T GetCorrectNumber(T min = 0, T max = 10000000)
{
	T x;
	while ((std::cin >> x).fail() || x<min || x>max)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Please, type number (" << min << "-" << max << "): ";
	}
	return x;
}

template <typename T>
int Proverka(std::unordered_map<int, T>& map, std::string textIN, std::string textError, int min, int max, int NEravno)
{
	int x;
	std::cout << textIN;
	while ((std::cin >> x).fail() || x < min || x > max || x == NEravno)
	{

		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << textError << "\n";
		if (map.count(x) == 0)
			std::cout << "Произошла ошибка! Объекта с таким id не существует! ";
	}

	return x;
}
