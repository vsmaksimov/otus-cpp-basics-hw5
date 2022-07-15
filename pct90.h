#include "istatistics.h"
#include <vector>

class Pct90 : public IStatistics {
public:
	Pct90();

	void update(double next) override;
	double eval() const override;
	const char * name() const override;

private:
	std::vector<double> m_seq;
	double m_prob;
};