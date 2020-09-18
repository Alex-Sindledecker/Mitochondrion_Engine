#pragma once

#include "Core.h"

namespace Engine
{

	enum class ENGINE_API JanitorType
	{
		DELETE_DATA,
		DESTROY_DATA,
		MOVE_DATA //Doesn not actually move the pointer and rather just chooses not to delete it
	};
	
	template<class Ty>
	class UniquePtr
	{
	public:
		explicit UniquePtr(Ty* mem, JanitorType janitor = JanitorType::DELETE_DATA)
		{
			ptr = mem;
			this->janitor = janitor;
		}

		UniquePtr(UniquePtr&& ptr)
		{
			//Moving into this
			this->ptr = ptr.ptr;
			this->janitor = ptr.janitor;

			//Hollowing old ptr
			ptr.ptr = nullptr;
			ptr.janitor = JanitorType::MOVE_DATA;
		}

		~UniquePtr()
		{
			reset();
		}

		inline Ty* get() { return ptr; }

		void release()
		{
			this->ptr = nullptr;
		}

		void reset()
		{
			if (janitor == JanitorType::DELETE_DATA)
				delete ptr;
			else if (janitor == JanitorType::DESTROY_DATA)
				ptr->~Ty();

			ptr = nullptr;
		}

		Ty* operator->() const { return ptr; }
		bool operator==(const UniquePtr& ptr) const { return *this->ptr == *ptr->ptr; }
		bool operator==(const Ty* ptr) const { return *this->ptr == *ptr; }
		bool operator==(const Ty& ref) const { return *ptr == ref; }
		bool operator!=(const UniquePtr& ptr) const { return *this->ptr != *ptr->ptr; }
		bool operator!=(const Ty* ptr) const { return *this->ptr != *ptr; }
		bool operator!=(const Ty& ref) const { return *ptr != ref; }

		UniquePtr& operator=(UniquePtr&& ptr) 
		{
			if (this->ptr == ptr.ptr)
				return *this;

			reset();

			//Moving into this
			this->ptr = ptr.ptr;
			this->janitor = ptr.janitor;

			//Hollowing old ptr
			ptr.ptr = nullptr;
			ptr.janitor = JanitorType::MOVE_DATA;

			return *this;
		}

		UniquePtr(const UniquePtr&) = delete;
		UniquePtr& operator=(const UniquePtr&) = delete;

	private:
		Ty* ptr;
		JanitorType janitor;
	};
}