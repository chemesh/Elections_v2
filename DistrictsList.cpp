#include "DistrictsList.h"

namespace elc
{
	bool DistrictsList::setSize(const int& _size)
	{
		District** temp = new District*[_size];

		for (int i = 0; i < size; i++)
			temp[i] = list[i];
		this->size = _size;
		//delete[] list;
		list = temp;
		return true;
	}

	bool DistrictsList::setLength(const int& len)
	{
		this->length = len;
		return true;
	}

	bool DistrictsList::setDistrict(char* _DistrictName, int numOfReps, bool div)
	{
		//District* temp;
		if (isFull())
		{
			setSize(size * 2);
		}
		if (div)
			list[length] = new Divided(_DistrictName, numOfReps);
			//temp = new Divided(_DistrictName, numOfReps);
		else 
			list[length] = new District(_DistrictName, numOfReps);
			//temp = new District(_DistrictName, numOfReps);
		//list[length]->setDistrict(_DistrictName, numOfReps);
		//list[length] = temp;
		list[length]->setDistID(length);
		setLength(length + 1);
		return true;
	}

	bool DistrictsList::setDistrict(const District& _dist)
	{
		if (isFull())
		{
			setSize(size * 2);
		}
		*(list[length]) = _dist;
		list[length]->setDistID(length);
		setLength(length + 1);
		return true;
	}

	//added
	bool DistrictsList::setCitizenInDist(const Citizen& resident, const District& dist)
	{
		list[dist.getDistID()]->setDistCitizenInList(resident);
		return true;
	}

	int DistrictsList::getSize() const
	{
		return this->size;
	}

	int DistrictsList::getLength() const
	{
		return this->length;
	}

	bool DistrictsList::isFull()
	{
		if (length == size)
			return true;
		return false;
	}

	void DistrictsList::operator=(const DistrictsList& o)
	{
		setSize(o.size);
		setLength(o.length);
		for (int i = 0; i < o.length; i++)
		{
			list[i] = o.list[i];
		}
	}

}