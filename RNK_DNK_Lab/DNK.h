#pragma once
#include "RNK.h"
#include <exception>
class DNK {
public:
	biology_lib::RNK rnk1;
	biology_lib::RNK rnk2;
	DNK(biology_lib::RNK&, biology_lib::RNK&);
};