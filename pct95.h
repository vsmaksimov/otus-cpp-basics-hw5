#include "istatistics.h"
#include <vector>

class Pct95 : public IStatistics {
public:
	Pct95();

	void update(double next) override;
	double eval() const override;
	const char * name() const override ;

private:
	std::vector<double> m_seq;
	double m_prob;
};