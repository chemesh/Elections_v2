#include "CitizenList.h"

namespace elc
{
	bool CitizensList::setSize(const int& _size)
	{
		Citizen* temp = new Citizen[_size];

		for (int i = 0; i < size; i++)
			temp[i] = list[i];
		this->size = _size;
		//delete[] list; 
		list = temp;
		return true;
	}

	bool CitizensList::setLength(const int& len)
	{
		this->length = len;
		return true;
	}

	bool CitizensList::setCitizen(const char* name, int id, int yob, const District& district)
	{
		if (isFull())
		{
			setSize(size * 2);
		}
		list[length].setCitizen(name, id, district, yob);
		setLength(length + 1);
		return true;
	}

	bool CitizensList::setCitizen(const Citizen& citizen)
	{
		setCitizen(citizen.getName(), citizen.getID(), citizen.getYOB(), citizen.getDistrict());
		return true;
	}

	int CitizensList::getSize() const
	{
		return this->size;
	}

	int CitizensList::getLength() const
	{
		return this->length;
	}

	Citizen* const CitizensList::getCitizen(int id)
	{
		int index = getCitizenIndex(id);
		if (index != -1)
			return &list[index];
		return nullptr;
	}

	int CitizensList::getCitizenIndex(int id)
	{
		int start = 0, end = length;
		int mid;

		while (start < end)
		{
			mid = (start + end) / 2;
			if (id < list[mid].getID())
				end = mid;
			else if (id > list[mid].getID())
				start = mid + 1;
			else		//id == list[mid].id
				return mid;
		}
		return -1;
	}

	const Citizen* const CitizensList::getList()
	{
		return list;
	}

	bool CitizensList::removeCitizen(const Citizen& _citizen)
	{
		int index = getCitizenIndex(_citizen.getID());
		int i;

		for (i = index; i < length; i++)
		{
			list[i] = list[i + 1];
		}
		setLength(length - 1);
		return true;
	}

	bool CitizensList::isFull()
	{
		if (length == size)
			return true;
		return false;
	}


	void CitizensList::mergeSort(Citizen* arr, int l, int r)
	{

		int m;

		if (l > r)
		{
			m = (l + r) / 2;
			mergeSort(arr, l, m);
			mergeSort(arr, m + 1, r);
			merge(arr, l, m, r);
		}
	}

	void CitizensList::merge(Citizen* arr, int l, int m, int r)
	{
		int idx1 = l, idx2 = m + 1;
		int j = 0, _size = (r - l + 1);
		Citizen* temp = new Citizen[_size];


		while (idx1 < m && idx2 < r)
		{
			if (arr[idx1].getID() <= arr[idx2].getID())
			{
				temp[j++] = arr[idx1++];
			}

			else
				temp[j++] = arr[idx2++];
		}

		while (idx1 < m)
			temp[j++] = arr[idx1++];
		while (idx2 < r)
			temp[j++] = arr[idx2++];

		for (int i = l; i < r; i++)
			arr[i] = temp[i];

		delete[] temp;
	}

	void CitizensList::operator=(const CitizensList& o)
	{
		setSize(o.size);
		setLength(o.length);
		for (int i = 0; i < o.length; i++)
		{
			list[i] = o.list[i];
		}

	}

	/**************************serialiazion***************************/
	void CitizensList::save(ofstream& out) const
	{
		out.write(rcastcc(&length), sizeof(length));
		for (int i = 0; i < length; ++i)
		{
		//	list[i].save(out);
		}
	}

	void CitizensList::load(ifstream& in)
	{
		in.read(rcastc(&length), sizeof(length));
		list = new Citizen[length];
		for (int i = 0; i < length; i++)
		{
		//	list[i].load(in);
		}
	}
}