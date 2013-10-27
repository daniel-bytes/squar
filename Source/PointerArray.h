#ifndef __POINTERARRAY_H__
#define __POINTERARRAY_H__

#include "../JuceLibraryCode/JuceHeader.h"

//
// Array of pointers
//
template <typename ElementType,
          typename TypeOfCriticalSectionToUse = DummyCriticalSection,
          int minimumAllocatedSize = 0>
class PointerArray
	: public Array<ElementType*, TypeOfCriticalSectionToUse, minimumAllocatedSize>
{
};

//
// Array that "owns" its pointers (will delete in constructor)
// 
template <typename ElementType,
          typename TypeOfCriticalSectionToUse = DummyCriticalSection,
          int minimumAllocatedSize = 0>
class OwnedPointerArray
	: public Array<ElementType*, TypeOfCriticalSectionToUse, minimumAllocatedSize>
{
public:
	~OwnedPointerArray()
	{
		for (int i = 0; i < this->size(); i++) {
			delete getUnchecked(i);
		}
	}
};

#endif //__POINTERARRAY_H__