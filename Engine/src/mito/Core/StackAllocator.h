#pragma once

#include "MitchondiraAPI.h"
#include "UniquePointer.h"

namespace mito
{

	class MITO_API StackAllocator
	{
	public:
		using Marker = uintptr_t;
	public:
		StackAllocator(u32_t capacity = 8, bool fixed = false); //Capacity in bytes
		StackAllocator(const StackAllocator& allocator);
		StackAllocator(StackAllocator&& allocator) noexcept;
		~StackAllocator();

		template<class Ty, class... Tys>
		UniquePtr<Ty> alloc(Tys... args)
		{
			Marker alignedHead = alignAddr(head, sizeof(Ty));
			if (alignedHead + sizeof(Ty) > cap)
				setCapacity((cap + sizeof(Ty)) * 2);

			Ty* t = new(data + alignedHead)Ty(args...);
			head = alignedHead + sizeof(Ty);

			return UniquePtr<Ty>(t, JanitorType::DESTROY_DATA);
		}

		void clear();
		inline void freeToMarker(Marker marker);
		void setCapacity(u32_t newCap);
		u8_t* getDataPtr() const;
		const u32_t getCapacity() const;
		const Marker getHeadMarker() const;

		const bool operator==(const StackAllocator& compare) const;
		const bool operator!=(const StackAllocator& compare) const;

	private:
		inline uintptr_t alignAddr(uintptr_t addr, u32_t alignment);

		u8_t* data;
		u32_t cap;
		Marker head;
	};

}