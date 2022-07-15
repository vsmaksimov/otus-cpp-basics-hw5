#include "istatistics.h"
#include <vector>

class Std : public IStatistics {
public:
	Std();
	void update(double next) override;
	double eval() const override;
	const char * name() const override;

private:
	std::vector<double> m_seq;
	double m_std;
};