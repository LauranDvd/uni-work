#pragma once
#include <string>

class Equation {
private:
	int a, b, c;

public:
	Equation(int a, int b, int c) : a{ a }, b{ b }, c{ c } {}

	int getA() const { return a; }
	int getB() const { return b; }
	int getC() const { return c; }

	double getDelta() const;
	bool hasRealSolution() const;

	std::string toString() const;
};