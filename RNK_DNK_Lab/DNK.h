#pragma once
#include "RNK.h"
#include <exception>

class DNK {
public:
	RNK rnk1;
	RNK rnk2;
	DNK(RNK&, RNK&);
};