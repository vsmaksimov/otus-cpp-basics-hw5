#include "mean.h"
#include <numeric>

Mean::Mean() : m_sum{0}, m_size{0} {}

void Mean::update(double next) {
	m_sum += next;
	m_size += 1;
}

double Mean::eval() const {
	return m_sum / m_size;
}

const char * Mean::name() const {
	return "mean";
}