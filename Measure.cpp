#pragma once
#include "Measure.h"
using namespace std;


//Member Functions
int Measure::getLittle() {
	return little;
}

int Measure::getLot() {
	return lot;
}

int Measure::getHeap() {
	return heap;
}

void Measure::setLittle(int num) {
	little = num;
}

void Measure::setLot(int num) {
	lot = num;
}

void Measure::setHeap(int num) {
	heap = num;
}

//constructors 
Measure::Measure() : little(0), lot(0), heap(0) {}
Measure::Measure(int num) : little(num), lot(0), heap(0) {}
Measure::Measure(int num1, int num2, int num3) : little(num1), lot(num2), heap(num3) {}

// overloads
Measure Measure::operator+(const Measure& obj) const {
	Measure result;
	result.little = little + obj.little;
	result.lot = lot + obj.lot;
	result.heap = heap + obj.heap;

	// constraints/conversions
	while (result.little >= 7) {
		result.little -= 7;
		result.lot++;
	}

	while (result.lot >= 23) {
		result.lot -= 23;
		result.heap++;
	}

	return result;
}

Measure Measure::operator-(const Measure& obj) const {
	Measure result;

	if (little < obj.little) {
		cerr << "Can't have negative measurements." << endl;
		return result;
	}

	result.little = little - obj.little;
	result.lot = lot - obj.lot;
	result.heap = heap - obj.heap;

	// constraints/conversions
	while (result.little >= 7) {
		result.little -= 7;
		result.lot++;
	}

	while (result.lot >= 23) {
		result.lot -= 23;
		result.heap++;
	}

	return result;
}

Measure Measure::operator/(const Measure& obj) const {
	Measure result;
	if (obj.little == 0 && obj.lot == 0 && obj.heap == 0) {
		cerr << "Division by zero is not allowed.\n";
		return result;
	}

	result.little = static_cast<double>(little) / static_cast<double>(obj.little);
	result.lot = static_cast<double>(lot) / static_cast<double>(obj.lot);
	result.heap = static_cast<double>(heap) / static_cast<double>(obj.heap);

	// constraints/conversions
	while (result.little >= 7) {
		result.little -= 7;
		result.lot++;
	}

	while (result.lot >= 23) {
		result.lot -= 23;
		result.heap++;
	}

	return result;
}

Measure Measure::operator*(const Measure& obj) const {
	Measure result;
	result.little = little * obj.little;
	result.lot = lot * obj.lot;
	result.heap = heap * obj.heap;

	// constraints/conversions
	while (result.little >= 7) {
		result.little -= 7;
		result.lot++;
	}

	while (result.lot >= 23) {
		result.lot -= 23;
		result.heap++;
	}

	return result;
}

bool Measure::operator==(const Measure& obj) const {
	return (little == obj.little) && (lot == obj.lot) && (heap == obj.heap);
}

Measure::operator string() const {
	return "Littles: " + to_string(little) + ", Lots: " + to_string(lot) + ", Heaps: "
		+ to_string(heap);
}

