#include "std.h"
#include <cmath>
#include <numeric>

Std::Std() : m_seq{}, m_std{0} {}

void Std::update(double next) {
	double numerator = 0; // numerator
	double mean = 0;

	m_seq.push_back(next);

	mean = std::accumulate(m_seq.begin(), m_seq.end(), 0) / m_seq.size();
		
	for (double item : m_seq) {
		numerator += (item - mean) * (item - mean);
	}

	 m_std = std::sqrt(numerator / m_seq.size());
}

double Std::eval() const {
	return m_std;
}

const char *  Std::name() const {
	return "std";
}
