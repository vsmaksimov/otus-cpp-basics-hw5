#include "pct90.h"
#include <algorithm>
#include <cmath>

Pct90::Pct90() : m_seq{}, m_prob{0.9} {}

void Pct90::update(double next) {
	m_seq.push_back(next);
	std::sort(m_seq.begin(), m_seq.end());
}

double Pct90::eval() const {
	int index = floor(m_prob * m_seq.size());
	return m_seq[index];
}

const char * Pct90::name() const {
	return "pct90";
}