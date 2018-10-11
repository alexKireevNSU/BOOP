#include "DNK.h"
#include <exception>

DNK::DNK(RNK& rnk1, RNK& rnk2) {
	if (!(rnk1.is_complimentary(rnk2))) throw std::exception("rnk1 is not complimentary to rnk2");
	this->rnk1 = rnk1;
	this->rnk2 = rnk2;
}