#include "pct95.h"
#include <algorithm>
#include <cmath>


Pct95::Pct95() : m_seq{}, m_prob{0.95} {}

void Pct95::update(double next) {
	m_seq.push_back(next);
	std::sort(m_seq.begin(), m_seq.end());
}

double Pct95::eval() const {
	int index = floor(m_prob * m_seq.size());
	return m_seq[index];
}

const char * Pct95::name() const {
	return "pct95";
}