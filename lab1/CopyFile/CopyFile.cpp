﻿// CopyFile.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "CopyFile.h"

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage CopyFile.exe <input file name> <output file name>\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	return args;
}

void CopyStreams(std::istream& input, std::ostream& output)
{
	char ch;
	while (input.get(ch))
	{
		if (!output.put(ch))
		{
			break;
		}
	}
}

bool CopyFile(const std::string inputFileName, std::string outputFileName)
{
	// Открываем входной файл
	std::ifstream input;
	input.open(inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << inputFileName << "' for reading\n";
		return false;
	}
	// Открываем выходной файл
	std::ofstream output;
	output.open(outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open '" << outputFileName << "' for writing\n";
		return false;
	}

	// Копируем содержимое входного файла в выходной
	CopyStreams(input, output);

	if (input.bad())
	{
		std::cout << "Failed to read data from input file\n";
		return false;
	}

	if (!output.flush())
	{
		std::cout << "Failed to write data to output file\n";
		return 1;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	// Проверка правильности аргументов командной строки
	if (!args)
	{
		return 1;
	}

	if (!CopyFile(args->inputFileName, args->outputFileName))
	{
		return 1;
	}

	return 0;
}
