#include "DistrictsList.h"

namespace elc
{
	bool DistrictsList::setSize(const int& _size)
	{
		District* temp = new District[_size];

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

	bool DistrictsList::setDistrict(char* _DistrictName, int numOfReps)
	{
		if (isFull())
		{
			setSize(size * 2);
		}
		list[length].setDistrict(_DistrictName, numOfReps);
		list[length].setDistID(length);
		setLength(length + 1);
		return true;
	}

	//added
	bool DistrictsList::setCitizenInDist(const Citizen& resident, int distID)
	{
		list[distID].setDistCitizenInList(resident);
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
}