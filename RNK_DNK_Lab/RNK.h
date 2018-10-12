#pragma once
#include <iostream>
#include <unordered_map>

namespace biology_lib {

	const size_t nucs_in_element = (sizeof(size_t) * 4);

	enum Nucleotide : unsigned char {
		A, G, C, T
	};

	struct RNKS;

	class RNK {
	private:
		size_t* chain = nullptr;
		size_t chain_length = 0;
		size_t length = 0;



		class Iterator {
		private:
			size_t index;
			size_t nuc_index;
			size_t shift;
			const RNK* rnk;
		public:
			Nucleotide operator=(Nucleotide N) {
				rnk->chain[nuc_index] = ((rnk->chain[(index / nucs_in_element)]) & (~(size_t)(3 << shift))) | (N << shift);
				return (Nucleotide)((rnk->chain[nuc_index] & ((size_t)(3 << shift))) >> shift);
			}

			operator Nucleotide() const {
				return (Nucleotide)((rnk->chain[nuc_index] & ((size_t)(3 << shift))) >> shift);
			}

			Iterator(const RNK* rnk, size_t index) {
				this->rnk = rnk;
				this->index = index;
				this->nuc_index = index / nucs_in_element;
				this->shift = (size_t)((sizeof(size_t) * 8) - 2 - (index % nucs_in_element) * 2);
			}

			~Iterator() {
				rnk = nullptr;
			}
		};

	public:

		RNK(Nucleotide N, std::size_t length);

		RNK(std::size_t length, Nucleotide N...);

		RNK(const RNK& rnk);

		RNK(size_t length);

		RNK();

		~RNK();

		const Iterator operator[](size_t i) const;

		Iterator operator[](size_t i);

		std::size_t get_length() const;

		Nucleotide get(size_t i) const;

		void reverse();

		void push_back(Nucleotide N);

		void push_back(std::size_t length, Nucleotide N...);

		RNKS split(size_t index);

		void trim(size_t index);

		size_t cardinality(Nucleotide N);

		std::unordered_map<Nucleotide, size_t> cardinality();

		bool operator==(RNK);

		bool operator!=(RNK&);

		RNK operator!();

		RNK& operator=(const RNK&);

		bool is_complimentary(RNK&);

		RNK operator+(const RNK& r) {
			RNK result_rnk(*this);
			for (auto i = 0; i < r.get_length(); i++) {
				result_rnk.push_back((Nucleotide)r[i]);
			}
			return result_rnk;
		};
	};

	struct RNKS {
		RNK *first;
		RNK *second;
	};

}