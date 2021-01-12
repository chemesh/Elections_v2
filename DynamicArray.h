#pragma once
#include <iostream>
using namespace std;
namespace d_array {

	template <class T >
	class DynamicArray {
	private:
		int logSize;
		int phySize;
		T* arr;
		void resize() {
			phySize *= 2;
			T* temp = new T[phySize];
			for (int i = 0; i < logSize; i++)
				temp[i] = arr[i];

			delete[] arr;
			arr = temp;
		}
	public:
		DynamicArray() : logSize(0), phySize(1), arr(new T[1]) {}
		DynamicArray(int p_size, int l_size) : logSize(l_size), phySize(p_size), arr(new T[p_size]) {}

		DynamicArray(const DynamicArray& other) : arr(nullptr) { *this = other; }
		~DynamicArray() { delete[] arr; }

		bool operator==(const DynamicArray& other) const {
			return (arr == other.arr);
		}
		friend ostream& operator<<(ostream& out, const DynamicArray& other)
		{
			cout << other;
			return out;
		}

		bool operator!=(const DynamicArray& other) {
			return !(*this == other);
		}
		const DynamicArray& operator=(const DynamicArray& other) {
			if (*this != other)
			{
				//template <class T int DynamicArray<T>::phySize
				logSize = other.logSize;
				phySize = other.phySize;
				delete[] arr;
				arr = new T[phySize];
				for (int i = 0; i < logSize; i++)
					arr[i] = other.arr[i];
			}
			return *this;
		}

		// operator []:
		const T& operator[](int i) const { return arr[i]; }
		T& operator[](int i) { return arr[i]; }

		// add to end of array
		void push_back(const T& value) {
			if (logSize == phySize)
				resize();
			arr[logSize++] = value;
		}
		void push_back(T* value) {
			if (logSize == phySize)
				resize();
			arr[logSize++] = *value;
		}
		void push_back()
		{
			if (logSize == phySize)
				resize();
			logSize++;
		}

		T* get_by_id(int id) const {
			for (int i = 0; i < logSize; i++)
			{
				if (id == arr[i].getID())
					return &arr[i];
			}
		}
		T* get_by_index(int index)const {
			return &arr[index];
		}

		int      size(int i)const { return arr[i].size(); }
		const T& front()    const { return arr[0]; }
		int      size()     const { return logSize; }
		int      capacity() const { return phySize; }
		bool     empty()    const { return logSize == 0; }
		void     clear() { logSize = 0; }

		void set_size(int size) { logSize = size; }
		void set_capacity(int size) { phySize = size; }

		template <bool is_const>
		class base_iterator
		{
		public:
			using ds_type = std::conditional_t<is_const, const DynamicArray, DynamicArray>;
			using iterator_category = std::bidirectional_iterator_tag;
			using different_type = std::ptrdiff_t;
			using value_type = std::conditional_t<is_const, const T, T>;
			using pointer = value_type*;
			using reference = value_type&;

			base_iterator(ds_type& arr, int i) : _da(&arr), _i(i) {}

			// we want to use the default copy constructor
			base_iterator(const base_iterator&) = default;

			// and the default assignment operator
			constexpr base_iterator& operator=(const base_iterator&) = default;

			// we want to allow construction of const_iterator from iterator
			friend class base_iterator<true>;
			template <bool _is_const = is_const, class = std::enable_if_t<_is_const>>
			base_iterator(const base_iterator<false>& other) : _da(other._da), _i(other._i) {}

			bool operator==(const base_iterator& other) const {
				return (_da == other._da) && (_i == other._i);
			}
			bool operator!=(const base_iterator& other) const {
				return !(*this == other);
			}

			reference operator*() {
				return _da->_arr[_i];
			}
			pointer operator->() {
				return &_da->_arr[_i];
			}

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
			ds_type* _da;
			int			_i;
		};
		using iterator = base_iterator<false>;
		using const_iterator = base_iterator<true>;

		// should return iterator to new element
		void insert(const iterator& pos, const T& val) {
			if (logSize == phySize)
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
			++logSize;
		}

		// returns iterator to first element after deleted element/s
		iterator erase(const iterator& pos) {

			T* temp = new T[phySize];
			iterator iter = begin();

			for (; iter != pos; iter++)
			{
				temp[iter._i] = arr[iter._i];
			}
			for (iter = pos + 1; iter != end(); iter++)
			{
				temp[iter._i - 1] = arr[iter._i];
			}
			delete[] arr;
			logSize--;
			arr = temp;
			return begin();
		}
		iterator erase(const iterator& first, const iterator& last)
		{
			int count = 0;
			T* temp = new T[phySize];
			iterator iter = begin();
			for (; iter != first; iter++)
			{
				temp[iter._i] = arr[iter._i];
			}
			count = last._i - first._i;

			for (iter = last; iter != end(); iter++)
			{
				temp[iter._i - count] = arr[iter._i];
			}
			delete[] arr;
			logSize -= count;
			arr = temp;
			return begin();
		}
		iterator begin() {
			return iterator(*this, 0);
		}
		iterator end() {
			return iterator(*this, logSize);
		}

		const_iterator begin() const {
			return const_iterator(*this, 0);
		}
		const_iterator end() const {
			return const_iterator(*this, logSize);
		}
		const_iterator cbegin() const {
			return const_iterator(*this, 0);
		}
		const_iterator cend() const {
			return const_iterator(*this, logSize);
		}

		/*
			- rbegin()/rend()		- reverse iterators (end to start)
		פונקציות C מחזירות קונסט איטרטור

		*/

		void print() const {
			for (int i = 0; i < logSize; i++)
				cout << arr[i] << endl;
		}

		void print(int _i) const {
			for (int i = 0; i < logSize; i++) {
				if (i == _i);
				//cout << arr[i] << endl;
			}
		}
	};
}