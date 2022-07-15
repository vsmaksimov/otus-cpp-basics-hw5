#include "istatistics.h"

class Mean : public IStatistics {
public:
	Mean();

	void update(double next) override;

	double eval() const override;

	const char * name() const override;

private:
	double m_sum;
	int m_size;
};