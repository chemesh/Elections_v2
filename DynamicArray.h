#pragma once
#include <iostream>

using namespace std;

template <class T>
class DynamicArray
{
public:
	DynamicArray(int size = 2) : _logicalSize(0), _physicalSize(size), _arr(new T[size]) {}

	DynamicArray(const DynamicArray& other) : _arr(nullptr) {
		*this = other;
	}
	~DynamicArray() {
		delete[] _arr;
	}

	const DynamicArray& operator=(const DynamicArray& other) {
		if (this != &other) {
			_logicalSize = other._logicalSize;
			_physicalSize = other._physicalSize;
			delete[] _arr;
			_arr = new T[_physicalSize];
			for (int i = 0; i < _logicalSize; i++)
				_arr[i] = other._arr[i];
		}
		return *this;
	}

	const T& operator[](int i) const { return _arr[i]; }
	T& operator[](int i) { return _arr[i]; }


	//--!! need to impliment at function?


	void push_back(const T& value) {
		if (_logicalSize == _physicalSize)
			resize();
		_arr[_logicalSize++] = value;
	}

	const T& front()    const { return _arr[0]; }
	int      size()     const { return _logicalSize; }
	int      capacity() const { return _physicalSize; }
	bool     empty()    const { return _logicalSize == 0; }
	void     clear() { _logicalSize = 0; }

	// standard STL iterator implementation:
	// (no duplication for const)
	template <bool is_const>
	class base_iterator
	{
	public:
		using ds_type = std::conditional_t<is_const, const DynamicArray, DynamicArray>;

		using iterator_category = std::bidirectional_iterator_tag;
		// other options exist, e.g., std::forward_iterator_tag
		using different_type	 = std::ptrdiff_t;
		using value_type		 = std::conditional_t<is_const, const T, T>;
		using pointer			 = value_type*;
		using reference			 = value_type&;

		base_iterator(ds_type& arr, int i) : _da(&arr), _i(i) {}

		// we want to use the default constructor
		base_iterator(const base_iterator&) = default; 

		// and the default assignment operator
		constexpr base_iterator& operator=(const base_iterator&) = default;

		// we want to allow construction of const_iterator from iterator
		friend class base_iterator<true>;
		template <bool _is_const = is_const, class = std::enable_if_t<_is_const>>
		base_iterator(const base_iterator<false>& other) : _da(other._da), _i(other._i) {}

		//--!! alon added this func.
		const base_iterator& operator=(const base_iterator& other) {
			_da = other._da;
			_i = other._i;
			return *this;
		}

		// comparison with another iterator
		bool operator==(const base_iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const base_iterator& other) const {
			return !(*this == other);
		}

		// smart-pointer iterator methods
		//--!! suppose to return const for cosnt_iterator
		reference operator*() {
			return _da->_arr[_i];
		}
		pointer operator->() {
			return &_da->_arr[_i];
		}

		// increment-decrement iterator methods
		base_iterator& operator++() {
			++_i;
			return *this;
		}
		base_iterator operator++(int) {
			base_iterator temp(*this);
			++_i;
			return temp;
		}
		base_iterator& operator--() {
			--_i;
			return *this;
		}
		base_iterator operator--(int) {
			base_iterator temp(*this);
			--_i;
			return temp;
		}

	private:
		ds_type* _da; //pointer to the dinamic array
		int		 _i; //index
	};

	using iterator = base_iterator<false>;
	using const_iterator = base_iterator<true>;

	void insert(const iterator& pos, const T& val) {
		if (_logicalSize == _physicalSize)
			resize();

		iterator itrEnd = end();
		iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
		while (itrCurrent != pos)
		{
			*itrCurrent = *itrPrev;
			itrCurrent = itrPrev--;
		}

		iterator p = pos;
		*p = val;
		++_logicalSize;
	}

	const iterator& erase(const iterator& iter);
	const iterator& erase(const iterator& first, const iterator& last);

	iterator begin() {
		return iterator(*this, 0);
	}
	iterator end() {
		return iterator(*this, _logicalSize);
	}

	const_iterator begin() const {
		return const_iterator(*this, 0);
	}
	const_iterator end() const {
		return const_iterator(*this, _logicalSize);
	}

	//--!! functions added by alon
	const_iterator cbegin() const {
		return const_iterator(*this, 0);
	}

	const_iterator cend() const {
		return const_iterator(*this, _logicalSize);
	}
	/*
		cbegin()/cend()		- for const iterator
		rbegin()/rend()		- for reverse iterator (end to start)
	*/

	void print() const {
		for (int i = 0; i < _logicalSize; i++)
			cout << _arr[i] << " ";
		cout << endl;
	}

private:
	void resize() {
		_physicalSize *= 2;
		T* temp = new T[_physicalSize];
		for (int i = 0; i < _logicalSize; i++)
			temp[i] = _arr[i];

		delete[] _arr;
		_arr = temp;
	}

	T* _arr;
	int _logicalSize;
	int _physicalSize;
};


