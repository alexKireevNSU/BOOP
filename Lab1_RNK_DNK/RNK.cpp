#include "RNK.h"
using namespace std;

biology_lib::RNK::RNK(Nucleotide N, size_t length) {
	this->chain_length = (length / nucs_in_element) + (length % nucs_in_element >= 1);

	chain = new size_t[chain_length];
	for (auto i = 0; i < chain_length; ++i) {
		chain[i] = 0;
	}
	this->length = length;
	
	for (auto i = 0; i < this->length; ++i) {
		chain[i / nucs_in_element] |= (size_t)(N << ((sizeof(size_t) * 8) - 2 - (i % nucs_in_element) * 2));
	}
}

biology_lib::RNK::RNK(size_t length, Nucleotide N...) {
	size_t* chain_t;
	this->chain_length = (length / nucs_in_element) + (length % nucs_in_element >= 1);

	chain_t = new size_t[chain_length];
	for (auto i = 0; i < chain_length; ++i) {
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

biology_lib::RNK::RNK(size_t length) {
	size_t* chain_t;
	this->chain_length = (length / nucs_in_element) + (length % nucs_in_element >= 1);

	chain_t = new size_t[(length / nucs_in_element) + (length % nucs_in_element >= 1)];
	for (auto i = 0; i < (length / nucs_in_element) + (length % nucs_in_element >= 1); ++i) {
		chain_t[i] = 0;
	}
	this->chain = chain_t;
	this->length = length;
	
}

biology_lib::RNK::RNK() {
	this->chain = nullptr;
	this->length = 0;
	this->chain_length = 0;
}

biology_lib::RNK::~RNK() {
	if (chain) {
		delete[] chain;
		chain = nullptr;
	}
}

size_t biology_lib::RNK::get_length() const {
	return length;
}

biology_lib::Nucleotide biology_lib::RNK::get(size_t i) const {
	return (*this)[i];
}

void biology_lib::RNK::reverse() {

	if (chain == nullptr) throw exception("Chain is nullptr!");

	for (unsigned int i = 0; i < ((this->length) / 2); i++) {
		Nucleotide tmp = (Nucleotide)(*this)[i];
		(*this)[i] = (Nucleotide)(*this)[this->length - i - 1];
		(*this)[this->length - i - 1] = tmp;
	}

}

void biology_lib::RNK::push_back(Nucleotide N) {
	size_t new_length = this->length + 1;
	/*if (!this->chain) {
		this->chain = new size_t[1];
		this->chain[0] = 0;
		(*this)[0] = N;
		this->length = 1;
		this->chain_length = 1;
		return;
	}
	if (new_length / nucs_in_element - (new_length%nucs_in_element >= 1) >= this->chain_length) {
		size_t *new_chain = new size_t[this->chain_length * 2];
		for (auto i = 0; i < this->chain_length*2; ++i)
			new_chain[i] = 0;
		for (auto i = 0; i < this->chain_length; i++) {
			new_chain[i] = this->chain[i];
		}
		delete[] this->chain;
		this->chain = new_chain;
		this->chain_length = this->chain_length * 2;
	}*/
	if (new_length / nucs_in_element + (new_length%nucs_in_element >= 1) > this->chain_length) {
		this->resize_chain();
	}

	this->length = new_length;
	(*this)[this->length-1] = N;
}

void biology_lib::RNK::push_back(size_t length, Nucleotide N...) {
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

void biology_lib::RNK::trim(size_t index) {
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

biology_lib::RNKS biology_lib::RNK::split(size_t index) {
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

size_t biology_lib::RNK::cardinality(Nucleotide N) {
	size_t counter = 0;
	for (auto i = 0; i < this->length; i++) {
		N == (*this)[i] ? counter++ : 0;
	}
	return counter;
}

std::unordered_unordered_unordered_map<biology_lib::Nucleotide, size_t> biology_lib::RNK::cardinality() {
	std::unordered_unordered_unordered_map<Nucleotide, size_t> unordered_unordered_map;
	unordered_unordered_map[A] = cardinality(A);
	unordered_unordered_map[G] = cardinality(G);
	unordered_unordered_map[C] = cardinality(C);
	unordered_unordered_map[T] = cardinality(T);
	return unordered_unordered_map;
}

const biology_lib::RNK::Iterator biology_lib::RNK::operator[](size_t i) const {
	if (i >= this->length || i < 0) throw std::exception("Out of range");
	return Iterator(this, i);
}

biology_lib::RNK::Iterator biology_lib::RNK::operator[](size_t i){
	if (i >= this->length || i < 0) throw std::exception("Out of range");
	return Iterator(this, i);
}

bool biology_lib::RNK::operator==(RNK r) {
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

bool biology_lib::RNK::operator!=(RNK &r) {
	return !((*this) == r);
}

biology_lib::Nucleotide get_comp_nucl(biology_lib::Nucleotide N) {
	switch (N)
	{
	case biology_lib::A:
		return biology_lib::T;
	case biology_lib::G:
		return biology_lib::C;
	case biology_lib::C:
		return biology_lib::G;
	case biology_lib::T:
		return biology_lib::A;
	}
	return biology_lib::A;
}

biology_lib::RNK::RNK(const RNK& rnk) {
	this->length = rnk.length;
	this->chain_length = (rnk.chain_length);
	size_t* chain_t = new size_t[rnk.chain_length];
	for (auto i = 0; i < rnk.chain_length; i++) {
		chain_t[i] = 0;
	}
	for (auto i = 0; i < rnk.chain_length; i++) {
		chain_t[i] = rnk.chain[i];
	}
	if (this->chain != nullptr) delete[] this->chain;
	this->chain = chain_t;

}

biology_lib::RNK biology_lib::RNK::operator!() {
	RNK result_rnk(*this);
	for (auto i = 0; i < this->get_length(); ++i) {
		(result_rnk)[i] = (get_comp_nucl((Nucleotide)(*this)[i]));
	}
	return result_rnk;
}

biology_lib::RNK& biology_lib::RNK::operator=(const RNK& rnk) {
	this->length = rnk.length;
	this->chain_length = rnk.chain_length;
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

bool biology_lib::RNK::is_complimentary(RNK& r) {
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

biology_lib::RNK biology_lib::RNK::operator+(const RNK& r) {
	RNK result_rnk(*this);
	for (auto i = 0; i < r.get_length(); i++) {
		result_rnk.push_back((Nucleotide)r[i]);
	}
	return result_rnk;
};

void biology_lib::RNK::resize_chain() {
	if (!this->chain) {
		this->chain = new size_t[1];
		this->chain[0] = 0;
		this->length = 1;
		this->chain_length = 1;
		return;
	}
	else {
		size_t *new_chain = new size_t[this->chain_length * 2];
		for (auto i = 0; i < this->chain_length * 2; ++i)
			new_chain[i] = 0;
		for (auto i = 0; i < this->chain_length; i++) {
			new_chain[i] = this->chain[i];
		}
		delete[] this->chain;
		this->chain = new_chain;
		this->chain_length = this->chain_length * 2;
	}
}