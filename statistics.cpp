#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {

public:
	Min() : m_min{std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

// Max - Max value

class Max : public IStatistics {
public:
	Max() : m_max{std::numeric_limits<double>::min()} {
	}

	void update(double next) override {
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		return m_max;
	}

	const char * name() const override {
		return "max";
		}

private:
	double m_max;
};

// Mean - Arithmetic mean

class Mean : public IStatistics {
public:
	Mean() : m_mean{0}, m_seq{} {
	}

	void update(double next) override {
		m_seq.push_back(next);
		m_mean = std::accumulate(m_seq.begin(), m_seq.end(), 0) / m_seq.size();
	}

	double eval() const override {
		return m_mean;
	}

	const char * name() const override {
		return "mean";
	}

private:
	double m_mean;
	std::vector<double> m_seq;
};

// Std - Standard deviation

class Std : public IStatistics {
public:
	Std() : m_seq{}, m_std{0} {
	}

	void update(double next) override {
		double numerator = 0; // numerator
		double mean = 0;

		m_seq.push_back(next);

		mean = std::accumulate(m_seq.begin(), m_seq.end(), 0) / m_seq.size();
		
		for (double item : m_seq) {
			numerator += (item - mean) * (item - mean);
		}

	 	m_std = std::sqrt(numerator / m_seq.size());

	}

	double eval() const override {
		return m_std;
	}

	const char * name() const override {
		return "std";
	}

private:
	std::vector<double> m_seq;
	double m_std;
};

// Pct90 - 90th percentile

class Pct90 : public IStatistics {
public:
	Pct90() : m_seq{}, m_pct90{0}, m_prob{0.9} {
	}

	void update(double next) override {
		m_seq.push_back(next);
		std::sort(m_seq.begin(), m_seq.end());
		int index = floor(m_prob * m_seq.size());
		m_pct90 = m_seq[index];
	}

	double eval() const override {
		return m_pct90;
	}

	const char * name() const override {
		return "pct90";
	}

private:
	std::vector<double> m_seq;
	double m_pct90;
	double m_prob;
};

// Pct95 - 95th percentile

class Pct95 : public IStatistics {
public:
	Pct95() : m_seq{}, m_pct95{0}, m_prob{0.95} {
	}

	void update(double next) override {
		m_seq.push_back(next);
		std::sort(m_seq.begin(), m_seq.end());
		int index = floor(m_prob * m_seq.size());
		m_pct95 = m_seq[index];
	}

	double eval() const override {
		return m_pct95;
	}

	const char * name() const override {
		return "pct95";
	}

private:
	std::vector<double> m_seq;
	double m_pct95;
	double m_prob;
};

int main() {

	const size_t statistics_count = 6;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new Std{};
	statistics[4] = new Pct90{};
	statistics[5] = new Pct95{};

	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}