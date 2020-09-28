#include "pch.h"
#include "StackAllocator.h"

namespace Engine
{

	StackAllocator::StackAllocator(u32 capacity, bool fixed)
	{
		data = new u8[capacity];
		cap = capacity;
		head = 0;
	}

	StackAllocator::StackAllocator(const StackAllocator& allocator)
	{
		cap = allocator.cap;
		head = allocator.head;
		data = new u8[cap];
		memcpy(data, allocator.data, cap);
	}

	StackAllocator::StackAllocator(StackAllocator&& allocator) noexcept
	{
		delete[] data;

		data = allocator.data;
		cap = allocator.cap;
		head = allocator.head;

		allocator.data = nullptr;
		allocator.cap = 0;
		allocator.head = 0;
	}

	StackAllocator::~StackAllocator()
	{
		delete[] data;
	}

	inline void StackAllocator::freeToMarker(Marker marker)
	{
		head = marker;
	}

	void StackAllocator::setCapacity(u32 newCap)
	{
		if (newCap == cap)
			return;

		u8* newBuffer = new u8[newCap];
		if (newCap > cap)
			memcpy(newBuffer, data, cap);
		else
			memcpy(newBuffer, data, newCap);
		delete[] data;
		data = newBuffer;
	}

	const u32 StackAllocator::getCapacity() const
	{
		return cap;
	}

	u8* StackAllocator::getDataPtr() const
	{
		return data;
	}

	const StackAllocator::Marker StackAllocator::getHeadMarker() const
	{
		return head;
	}

	const bool StackAllocator::operator==(const StackAllocator& compare) const
	{
		if (cap != compare.cap || head != compare.head)
			return false;
		return memcmp(data, compare.data, head);
	}

	const bool StackAllocator::operator!=(const StackAllocator& compare) const
	{
		return !operator==(compare);
	}

	inline uintptr_t StackAllocator::alignAddr(uintptr_t addr, u32 alignment)
	{
		const u32 mask = alignment - 1;
		return (addr + mask) & ~mask;
	}

}