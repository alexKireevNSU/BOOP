#include "RNK.h"
using namespace std;

RNK::RNK(Nucleotide N, size_t length) {

	chain = new size_t[(length / nucs_in_element) + (length % nucs_in_element >= 1)];
	for (auto i = 0; i < (length / nucs_in_element) + (length % nucs_in_element >= 1); ++i) {
		chain[i] = 0;
	}
	this->length = length;
	
	for (auto i = 0; i < this->length; ++i) {
		chain[i / nucs_in_element] |= (size_t)(N << ((sizeof(size_t) * 8) - 2 - (i % nucs_in_element) * 2));
	}
}

RNK::RNK(size_t length, Nucleotide N...) {
	size_t* chain_t;
	chain_t = new size_t[(length / nucs_in_element) + (length % nucs_in_element >= 1)];
	for (auto i = 0; i < (length / nucs_in_element) + (length % nucs_in_element >= 1); ++i) {
		chain_t[i] = 0;
	}
	Nucleotide* N_ptr = &N;
	for (unsigned int i = 0; i < length; i++) {
		chain_t[i / nucs_in_element] |= (size_t)((*N_ptr) << (size_t)(nucs_in_element * 2 - 2 - 2 * (i % nucs_in_element)));
		N_ptr += sizeof(Nucleotide*);
	}

	this->chain = chain_t;
	this->length = length;
}

RNK::RNK(size_t length) {
	size_t* chain_t;
	chain_t = new size_t[(length / nucs_in_element) + (length % nucs_in_element >= 1)];
	for (auto i = 0; i < (length / nucs_in_element) + (length % nucs_in_element >= 1); ++i) {
		chain_t[i] = 0;
	}
	this->chain = chain_t;
	this->length = length;
}

RNK::RNK() {
	this->chain = nullptr;
	this->length = 0;
}

RNK::~RNK() {
	if (chain) {
		delete[] chain;
		chain = nullptr;
	}
}

size_t RNK::get_length() const {
	return length;
}

Nucleotide RNK::get(size_t i) const {
	return (*this)[i];
}

void RNK::reverse() {

	if (chain == nullptr) throw exception("Chain is nullptr!");

	for (unsigned int i = 0; i < ((this->length) / 2); i++) {
		Nucleotide tmp = (Nucleotide)(*this)[i];
		(*this)[i] = (Nucleotide)(*this)[this->length - i - 1];
		(*this)[this->length - i - 1] = tmp;
	}

}

void RNK::push_back(Nucleotide N) {
	size_t length = this->length + 1;

	if (!this->chain) {
		size_t* chain = new size_t[1];
		chain[0] = N << ((sizeof(size_t) * 8) - 2 - (2 * (this->length % nucs_in_element)));
		this->chain = chain;
		this->length = length;
		return;
	}

	if (this->get_length() % nucs_in_element == 0) {
		size_t* chain = new size_t[(length / nucs_in_element) + (length % nucs_in_element >= 1)];
		for (int i = 0; i < (length / nucs_in_element) + (length % nucs_in_element >= 1); ++i)
			chain[i] = 0;

		if (this->length != 0) {
			for (int i = 0; i < (this->length / nucs_in_element) + (this->length % nucs_in_element >= 1); i++)
				chain[i] = this->chain[i];
		}
		chain[length / nucs_in_element] |= N << ((sizeof(size_t) * 8) - 2 - (2 * (this->length % nucs_in_element)));

		delete[] this->chain;
		this->chain = chain;
	}
	else {
		this->chain[this->length / nucs_in_element] |= N << ((sizeof(size_t) * 8) - 2 - (2 * (this->length % nucs_in_element)));
	}
	this->length = length;


}

void RNK::push_back(size_t length, Nucleotide N...) {
	Nucleotide* p_arg = (&N);
	size_t* chain_t = new size_t[((this->length + length) / nucs_in_element) + ((this->length + length) % nucs_in_element >= 1)];
	for (int i = 0; i < (length / nucs_in_element) + (length % nucs_in_element >= 1); ++i) {
		chain_t[i] = 0;
	}

	if (!this->chain) {
		this->length = length;
		Nucleotide* p_arg = (&N);
		for (unsigned int i = 0; i < length; i++) {
			chain_t[i / nucs_in_element] |= *p_arg << ((sizeof(size_t) * 8) - 2 - 2 * (i % nucs_in_element));
			p_arg += sizeof(Nucleotide*);
		}
		this->chain = chain_t;
	}
	else {
		for (auto i = 0; i < (this->length / nucs_in_element + (this->length % nucs_in_element >= 1)); ++i) {
			chain_t[i] = chain[i];
		}

		Nucleotide* p_arg = (&N);
		for (unsigned int i = 0; i < length; ++i) {
			chain_t[((this->length + i) / nucs_in_element)] |= *p_arg << ((sizeof(size_t) * 8) - 2 - 2 * ((this->length + i) % nucs_in_element));
			p_arg += sizeof(Nucleotide*);
		}

		this->length = this->length + length;
		delete[] this->chain;
		this->chain = chain_t;
	}

}

void RNK::trim(size_t index) {
	size_t result_chain_length = ((this->length - index) / nucs_in_element) + ((this->length - index) % nucs_in_element >= 1);

	size_t* buff = new size_t[index + 1];
	for (unsigned int i = 0; i < index / nucs_in_element + 1; i++) {
		buff[i] = this->chain[i];
	}
	buff[index % nucs_in_element] = (buff[index % nucs_in_element] >> (((sizeof(size_t) * 8) - 2 - (index % nucs_in_element) * 2))) << (((sizeof(size_t) * 8) - 2 - (index % nucs_in_element) * 2));
	delete[] this->chain;
	this->chain = buff;
	this->length = index;
}

RNKS RNK::split(size_t index) {
	RNKS rnks;
	RNK* second = new RNK(A, this->length - index);
	for (auto i = 0; i < this->length - index; i++) {
		(*second)[i] = (*this)[i + index];
	}
	rnks.second = second;
	this->trim(index);
	rnks.first = new RNK(*this);
	return rnks;
}

size_t RNK::cardinality(Nucleotide N) {
	size_t counter = 0;
	for (auto i = 0; i < this->length; i++) {
		N == (*this)[i] ? counter++ : 0;
	}
	return counter;
}

std::unordered_map<Nucleotide, size_t> RNK::cardinality() {
	std::unordered_map<Nucleotide, size_t> map;
	map[A] = cardinality(A);
	map[G] = cardinality(G);
	map[C] = cardinality(C);
	map[T] = cardinality(T);
	return map;
}

const RNK::Iterator RNK::operator[](size_t i) const {
	if (i >= this->length || i < 0) throw std::exception("Out of range");
	return Iterator(this, i);
}

RNK::Iterator RNK::operator[](size_t i){
	if (i >= this->length || i < 0) throw std::exception("Out of range");
	return Iterator(this, i);
}

bool RNK::operator==(RNK r) {
	if (this->get_length() != r.get_length()) return false;
	bool result = true;
	for (auto i = 0; i < r.get_length(); ++i)
		if ((*this)[i] != (Nucleotide)r[i]) {
			result = false;
			break;
		}
	bool reversed_result = true;
	for (auto i = 0; i < r.get_length(); ++i)
		if ((*this)[i] != (Nucleotide)r[r.get_length() - i - 1]) {
			reversed_result = false;
			break;
		}
	return (result || reversed_result);
}

bool RNK::operator!=(RNK &r) {
	return !((*this) == r);
}

Nucleotide get_comp_nucl(Nucleotide N) {
	switch (N)
	{
	case A:
		return T;
	case G:
		return C;
	case C:
		return G;
	case T:
		return A;
	}
	return A;
}

RNK::RNK(const RNK& rnk) {
	this->length = rnk.length;
	size_t* chain_t = new size_t[rnk.length / nucs_in_element + (rnk.length % nucs_in_element >= 1)];
	for (auto i = 0; i < rnk.length / nucs_in_element + (rnk.length % nucs_in_element >= 1); i++) {
		chain_t[i] = 0;
	}
	for (auto i = 0; i < rnk.length / nucs_in_element + (rnk.length % nucs_in_element >= 1); i++) {
		chain_t[i] = rnk.chain[i];
	}
	if (this->chain != nullptr) delete[] this->chain;
	this->chain = chain_t;

}

RNK RNK::operator!() {
	RNK result_rnk(*this);
	for (auto i = 0; i < this->get_length(); ++i) {
		(result_rnk)[i] = (get_comp_nucl((Nucleotide)(*this)[i]));
	}
	return result_rnk;
}

RNK operator+(RNK l, RNK r) {
	RNK result_rnk(l);
	for (auto i = 0; i < r.get_length(); i++) {
		result_rnk.push_back((Nucleotide)r[i]);
	}
	return result_rnk;
}

RNK& RNK::operator=(const RNK& rnk) {
	this->length = rnk.length;
	size_t* chain_t = new size_t[rnk.length / nucs_in_element + (rnk.length % nucs_in_element >= 1)];
	for (auto i = 0; i < rnk.length / nucs_in_element + (rnk.length % nucs_in_element >= 1); i++) {
		chain_t[i] = 0;
	}
	for (auto i = 0; i < rnk.length / nucs_in_element + (rnk.length % nucs_in_element >= 1); i++) {
		chain_t[i] = rnk.chain[i];
	}
	if (this->chain != nullptr) delete[] this->chain;
	this->chain = chain_t;
	return *this;
}

bool RNK::is_complimentary(RNK& r) {
	if (this->length != r.length) return false;
	bool result = true;
	for (auto i = 0; i < this->length; i++) {
		if ((*this)[i] != get_comp_nucl((Nucleotide)r[i])) {
			result = false;
			break;
		}
	}
	bool reversed_result = true;
	for (auto i = 0; i < this->length; i++) {
		if ((*this)[i] != get_comp_nucl((Nucleotide)r[this->length - i - 1])) {
			reversed_result = false;
			break;
		}
	}
	return result || reversed_result;
}