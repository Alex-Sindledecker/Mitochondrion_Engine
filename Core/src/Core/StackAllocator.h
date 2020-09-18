#pragma once

#include "Core.h"
#include "UniquePointer.h"

namespace Engine
{

	class ENGINE_API StackAllocator
	{
	public:
		using Marker = uintptr_t;
	public:
		StackAllocator(u32 capacity = 8, bool fixed = false); //Capacity in bytes
		StackAllocator(const StackAllocator& allocator);
		StackAllocator(StackAllocator&& allocator) noexcept;
		~StackAllocator();

		template<class Ty, class... Tys>
		UniquePtr<Ty> alloc(Tys... args)
		{
			Marker alignedHead = alignAddr(head, sizeof(Ty));
			if (alignedHead + sizeof(Ty) > cap)
				setCapacity(cap * 2);

			Ty* t = new(data + alignedHead)Ty(args...);
			head = alignedHead + sizeof(Ty);

			return UniquePtr<Ty>(t, JanitorType::DESTROY_DATA);
		}

		inline void freeToMarker(Marker marker);

		void setCapacity(u32 newCap);
		const u32 getCapacity() const;
		const u8* getDataPtr() const;
		const Marker getHeadMarker() const;

		const bool operator==(const StackAllocator& compare) const;
		const bool operator!=(const StackAllocator& compare) const;

	private:
		inline uintptr_t alignAddr(uintptr_t addr, u32 alignment);

		u8* data;
		u32 cap;
		Marker head;
	};

}