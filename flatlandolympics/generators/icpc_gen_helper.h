#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <type_traits>
#include <unordered_map>

#ifndef ICPC_GEN_HELPER
#define ICPC_GEN_HELPER

#define SEED_FLAG "--seed"
#define MAX_UINT uint64_t


namespace icpc_gen_helper {

	std::mt19937_64 rng;
	char **_argv;
	int _argc;

	char *getParam(const char *param) {
		for(int i = 1; i < _argc - 1; ++i) {
			if(strcmp(param, _argv[i]) == 0) return _argv[i + 1];
		}
		return nullptr;
	}
	
	char *getParam(const std::string &param) {
		return getParam(param.c_str());
	}


	bool hasFlag(const char *flag) {
		for(int i = 1; i < _argc; ++i) {
			if(strcmp(flag, _argv[i]) == 0) return true;
		}
		return false;
	}

	void Init(int argc, char** argv) {
		_argc = argc;
		_argv = argv;
		const char *seed = getParam(SEED_FLAG);
		if(seed == nullptr) return;
		rng.seed(std::stoull(seed));
	}

	template <typename... >
	using void_t = void;

	template <class T, class = void>
	struct is_iterator : std::false_type { };

	template <class T>
	struct is_iterator<T, void_t<typename std::iterator_traits<T>::iterator_category>> : std::true_type { };


	// Generate a random integer or float in [low, high].
	template <typename T>
		T uniform_number(T low, T high) {
			assert(low <= high);
			if constexpr(std::is_integral<T>::value)
				return std::uniform_int_distribution<T>(low, high)(rng);
			else
				return std::uniform_real_distribution<T>(low, high)(rng);
		}
	
	// Generates a random unique sequence
	template<typename T>
	class Random_Generation {
		public:
			class iterator;
			class index_iterator;

			Random_Generation(const T &low, const T &high, MAX_UINT k = 0) : _low(low), _high(high) {
				if constexpr(is_iterator<T>::value) {
					auto diff = std::distance(_low, _high);
					assert(diff >= 0);
					_range = (MAX_UINT) diff;
				} else {
					auto diff = _high - low;
					assert(diff >= 0);
					_range = (MAX_UINT) diff;
				}
				Reset();

				if(k != 0) {
					_generateFast(_range, k);
					_manual_gen_pos.insert(_fast_gen_pos.begin(), _fast_gen_pos.end());
					for(auto &p : _manual_gen_pos) {
						_manual_gen_num[p.second] = p.first;
					}
				}
			}

			void Reset() {
				_fast_gen_num.clear();
				_fast_gen_pos.clear();
				_manual_gen_num.clear();
				_manual_gen_pos.clear();
				_next_swap = 0;
				_max = 0;
			}

			MAX_UINT Size() const {
				return _next_swap;
			}

			MAX_UINT Generate(const T &low, const T &high, MAX_UINT k) {
				// TODO
				assert(high == _high && low == _low && "Not implemented yet");
				const MAX_UINT low_ = _toDiff(low);
				const MAX_UINT high_ = _toDiff(high);
				assert(high_ > low_);
				const MAX_UINT range = high_ - low_ - _next_swap;
				if(range < k) k = std::max(range, (MAX_UINT) 0);
				for(MAX_UINT i = k; i > 0; --i) {
					_select(uniform_number(_next_swap, range));
				}
				return k;
			}

			bool Select(const T &element) {
				MAX_UINT diff = _toDiff(element);
				assert(diff < _range);
				if(!_isSelected(diff)) {
					auto ptr = _manual_gen_num.insert({diff, diff});
					return _select((*ptr.first).second);
				}
				return false;
			}

			bool IsSelected(const T &element) const {
				return _isSelected((_toDiff(element)));
			}

			index_iterator iBegin() {
				return index_iterator(_manual_gen_pos.begin());
			}

			index_iterator iEnd() {
				if(_next_swap == 0)
					return iBegin();
				return index_iterator(++_manual_gen_pos.find(_next_swap - 1));
			}

			iterator begin() {
				return iterator(_low, iBegin());
			}

			iterator end() {
				return iterator(_low, iEnd());
			}

			
			virtual void print(std::ostream &out = std::cout, bool endLine = true, const std::string &sep = " ") {
				if constexpr(is_iterator<T>::value) {
					// TODO
					assert(false && "NOT YET IMPLEMENTED");
				} else {
				iterator it = this->begin(), end_it = this->end();
				if(it != end_it) {
					if constexpr(is_iterator<T>::value)
						out << (**it);
					else
						out << (*it);

					++it;
				}

				while(it != end_it) {
					out << sep;
					if constexpr(is_iterator<T>::value)
						out << (**it);
					else
						out << (*it);

					++it;
				}

				if(endLine)
					out << '\n';
				}
			}

		protected:
			// Not selected yet
			bool _select(const MAX_UINT idx) {
				auto pos_ptr_0 = _manual_gen_pos.insert({idx, idx});
				auto num_ptr_0 = _manual_gen_num.insert({(*pos_ptr_0.first).second, idx});
				auto pos_ptr_1 = _manual_gen_pos.insert({_next_swap, _next_swap});
				auto num_ptr_1 = _manual_gen_num.insert({(*pos_ptr_1.first).second, _next_swap});

				std::swap((*pos_ptr_0.first).second, (*pos_ptr_1.first).second);
				std::swap((*num_ptr_0.first).second, (*num_ptr_1.first).second);
				++_next_swap;
				return true;
			}
			
			bool _isSelected(const MAX_UINT element) const {
				auto ptr = _manual_gen_num.find(element);
				return  ptr != _manual_gen_num.end() && ptr->second < _next_swap;
			}

			inline MAX_UINT _toDiff(const T &element) const {
				if constexpr(is_iterator<T>::value) {
					auto diff = std::distance(_low, element);
					assert(diff >= 0);
					return (MAX_UINT) diff;
				} else {
					auto diff = element - _low;
					assert(diff >= 0);
					return (MAX_UINT) diff;
				}
			}


			MAX_UINT _generateFast(MAX_UINT max, MAX_UINT k) {
				assert(max >= _max && "Fast generation only works if range is kept or extended");
				_max = max;
				max = std::max(_range, max);
				const MAX_UINT range = max - _next_swap;
				if(range < k) k = range;
				for(MAX_UINT i = k; i > 0; --i) {
					const MAX_UINT idx = uniform_number(_next_swap, max - 1);
					auto pos_ptr_0 = _fast_gen_pos.insert({idx, idx});
					auto pos_ptr_1 = _fast_gen_pos.insert({_next_swap, _next_swap});
					std::swap((*pos_ptr_0.first).second, (*pos_ptr_1.first).second);
					++_next_swap;
				}
				return k;
			}


			std::unordered_map<MAX_UINT, MAX_UINT> _fast_gen_num;
			const T _low, _high;
			MAX_UINT _range, _max;
			std::unordered_map<MAX_UINT, MAX_UINT> _fast_gen_pos;
			std::map<MAX_UINT, MAX_UINT> _manual_gen_num;
			std::map<MAX_UINT, MAX_UINT> _manual_gen_pos;
			MAX_UINT _next_swap;

			public:
			class index_iterator{
				public:
					index_iterator(std::map<MAX_UINT, MAX_UINT>::iterator it) : _it(it) {}

        	using value_type = MAX_UINT;
        	using reference = const MAX_UINT&;
        	using pointer = const MAX_UINT*;
        	using difference_type = std::ptrdiff_t;
        	using iterator_category	= std::forward_iterator_tag;

					inline index_iterator operator++(int) { index_iterator tmp(*this); ++_it; return tmp;}
					inline index_iterator &operator++() {++_it; return *this;}

					inline bool operator== (const index_iterator &other) const {
						return _it == other._it;
					}

					
					inline bool operator!= (const index_iterator &other) const {
						return !(*this == other);
					}
					inline reference operator *() const {
						return (*_it).second;
					}

					inline pointer operator ->() const {
						return &**this;
					}


				private:
					std::map<MAX_UINT, MAX_UINT>::const_iterator _it;
			};

			class iterator{
				public:
					iterator(const T low, index_iterator it) : _low(low), _it(it) {
						if constexpr(is_iterator<T>::value) {
							_cur = _low;
							std::advance(_cur, *_it);
						} else {
							_cur = _low + *_it;
						}
					}

        	using value_type = T;
        	using reference = T&;
        	using pointer = T*;
        	using difference_type = std::ptrdiff_t;
        	using iterator_category	= std::input_iterator_tag;

					inline iterator &operator++() {
						++_it;
						if constexpr(is_iterator<T>::value) {
							_cur = _low;
							std::advance(_cur, *_it);
						} else {
							_cur = _low + *_it;
						}
						return *this;
					}
					inline iterator operator++(int) { index_iterator tmp(*this); ++(*this); return tmp;}

					inline bool operator== (const iterator &other) const {
						return _it == other._it && _low == other._low;
					}
					
					inline bool operator!= (const iterator &other) const {
						return !(*this == other);
					}

					inline reference operator *() {
						return _cur;
					}

				private:
				T _low;
				T _cur;
				index_iterator _it;
			};

	};

	template<typename T>
	std::ostream& operator<<(std::ostream &os, Random_Generation<T> &gen) {
		gen.print(os, false);
		return os;
	}

	// Generates a random selection on a STL container
	template<typename T, template<typename, typename = std::allocator<T>> class Container>
	class Random_Selection : public Random_Generation<typename Container<T>::iterator>{
		public:
			Random_Selection(Container<T> &container, MAX_UINT k = 0) : Random_Generation<typename Container<T>::iterator>(container.begin(), container.end(), k), _container(container) {}

			Random_Selection(const Random_Selection &) = delete;
			Random_Selection &operator=(const Random_Selection &) = delete;
			Random_Selection(Random_Selection &&) = default;
			Random_Selection &operator=(Random_Selection&&) = default;


		private:
			const Container<T> &_container;
	};

	// Generates random mapping for indices in range [0; n[ or [low; high]
	class Random_Mapping : public Random_Generation<MAX_UINT> {
		public:
			Random_Mapping(MAX_UINT max) : Random_Generation<MAX_UINT>((MAX_UINT)0, max, max) {}
			Random_Mapping(MAX_UINT low, MAX_UINT high) : Random_Generation<MAX_UINT>(low, high + 1, high - low) {}

			MAX_UINT operator[] (MAX_UINT element) {
				MAX_UINT offset = _toDiff(element);
				return _low + _manual_gen_pos[offset];
			}
	};

	template<class Container>
	void do_shuffle(Container &container) {
		std::shuffle(container.begin(), container.end(), rng);
	}
}

#endif
