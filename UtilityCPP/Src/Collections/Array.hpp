#pragma once
#include <cstddef>
#include <stdexcept>
#include <algorithm>

namespace BenScr {
	template<typename T, std::size_t size>
	class Array {
	public:
		Array() {
			m_Data = new T[size]();
		}
		Array(const T& fill) {
			m_Data = new T[size];
			std::fill_n(m_Data, size, fill);
		}
		~Array() {
			Destroy();
		}

		Array(const Array&) = delete;
		Array& operator=(const Array&) = delete;
		Array& operator=(const Array&& other) {
			if (other != this) {
				Destroy();
				m_Data = other.m_Data;
				other.m_Data = nullptr;
			}
			return *this;
		}

		void Destroy() {
			delete[] m_Data;
			m_Data = nullptr;
		}

		T& operator[](std::size_t index) { return m_Data[index]; }
		const T& operator[](std::size_t index) const { return m_Data[index]; }

		template<std::size_t otherSize>
		Array<T, size + otherSize> operator+(const Array<T, otherSize>& other) const
		{
			Array<T, size + otherSize> temp;

			std::size_t i = 0;

			for (; i < size; ++i) {
				temp[i] = m_Data[i];
			}
			for (std::size_t j = 0; j < otherSize; ++j, ++i) {
				temp[i] = other[j];
			}

			return temp;
		}

		T& At(std::size_t index) {
			if (index >= size) throw std::out_of_range("Index out of range");
			return m_Data[index];
		}
		const T& At(std::size_t index) const {
			if (index >= size) throw std::out_of_range("Index out of range");
			return m_Data[index];
		}

		void Insert(std::size_t index, const T& element) {
			At(index) = element;
		}

		const std::size_t GetSize() const { return size; }

		friend std::ostream& operator<<(std::ostream& os, const Array& arr) {
			os << '[';
			for (std::size_t i = 0; i < size; ++i) {
				if (i) os << ", ";
				os << arr[i];
			}
			os << ']';
			return os;
		}
	private:
		T* m_Data;
	};
}