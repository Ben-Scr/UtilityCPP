#pragma once
#include <stddef.h>

namespace BenScr {

	template<typename T>
	class List {
	public:
		List() {

		}

	private:
		T* m_Data;
		std::size_t m_Capacity;
	};
}