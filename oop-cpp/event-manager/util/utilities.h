#pragma once
#include <string>
#include <iostream>

// returns -1 if "given" is not a positive integer
int stringToInt(std::string given);

int readIntGracefully();

bool isInt(std::string putOnTrial);

std::string qtDateToDisciplinateDate(std::string qtForm);

std::string monthFromLettersToNumberForm(std::string inLetters);

std::string monthFromIntToString(int month);

std::string randomColorString();