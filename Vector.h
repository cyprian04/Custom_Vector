#pragma once
#include <iostream>
#include <iterator>
#include <cstddef>
#include <initializer_list>


template <typename T>
class Vector
{
public:
	explicit Vector()
		:
		m_size(0),
		m_capacity(2),
		m_buffer(allocate(m_capacity))
	{}
	explicit Vector(const int size)
		:
		m_size(size),
		m_capacity(2 * m_size),
		m_buffer(allocate(m_capacity))
	{}
	explicit Vector(const std::initializer_list<T> list)
		:
		m_size(0),
		m_capacity(2 * list.size()),
		m_buffer(allocate(m_capacity))
	{
		for (auto element : list) push_back(element);
	}
	~Vector() 
	{ 
		deallocate(m_buffer); 
	}
	/*
	Vector(const Vector& src)
		:
		m_size(src.m_size),
		m_capacity(src.m_capacity),
		m_buffer(new T[m_capacity]{ 0 })
	{
		for (std::size_t i = 0; i < m_size; i++) m_buffer[i] = src.m_buffer[i];
	}
	Vector& operator=(const Vector& src) {

		if (this != &src) {
			delete[] m_buffer;
			m_buffer = nullptr;

			m_size = src.m_size;
			m_capacity = src.m_capacity;
			m_buffer = new T[m_capacity];

			for (std::size_t i = 0; i < m_size; i++) m_buffer[i] = src.m_buffer[i];
		}
		return *this;
	}
	Vector(Vector&& src) noexcept
		:
		m_size(src.m_size),
		m_capacity(src.m_capacity),
		m_buffer(src.m_buffer)
	{
		src.m_size = 0;
		src.m_capacity = 0;
		src.m_buffer = nullptr;
	}
	Vector& operator=(Vector&& src) noexcept{
		if (this != &src) {
			delete[] m_buffer;
			m_buffer = nullptr;

			m_size = src.m_size;
			m_capacity = src.m_capacity;
			m_buffer = src.m_buffer;

			src.m_size = 0;
			src.m_capacity = 0;
			src.m_buffer = nullptr;
		}
		return *this;
	}
	*/
public:
	T& at(const std::size_t index) {
		if (index >= m_size || index < 0) throw std::out_of_range("Index out of bounds");
		return m_buffer[index];
	}
	const T& at(const std::size_t index) const {
		if (index >= m_size || index < 0) throw std::out_of_range("Index out of bounds");
		return m_buffer[index];
	}
	void push_back(const T& value) {
		enlarge_capacity_if_need(m_size + 1);
		::new(m_buffer + m_size) T(value);
		m_size++;
	}
	void push_back(T&& value) {
		enlarge_capacity_if_need(m_size + 1);
		::new(m_buffer + m_size) T(std::move(value));
		m_size++;
	}
	void pop_back() { 
		if (m_size == 0) return;
		(m_buffer + (--m_size))->~T();
	}
	bool empty() const { return m_size == 0; }
	std::size_t size() const { return m_size; }
	std::size_t capacity() const { return m_capacity; }
public:
	T& operator[](const std::size_t index) 
	{
		return m_buffer[index]; 
	}
	const T& operator[](const std::size_t index) const 
	{ 
		return m_buffer[index]; 
	}
	friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
		for (const auto element : vec) os << element << ", ";
		return os;
	}
public:
	class Iterator
	{
	public:
		explicit Iterator(T* m_ptr) : m_ptr(m_ptr) {}
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using refernce = T&;
		using pointer = T*;
		bool operator==(const Iterator& rhs) const {
			return m_ptr == rhs.m_ptr;
		}
		bool operator!=(const Iterator& rhs) const {
			return m_ptr != rhs.m_ptr;
		}
		refernce operator*() {
			return *m_ptr;
		}
		Iterator& operator++() {
			m_ptr++;
			return *this;
		}
		Iterator operator++(int) {
			auto old_ptr = m_ptr;
			m_ptr++;
			return old_ptr;
		}
	private:
		T* m_ptr;
	};
public:
	Iterator begin() const {
		return Iterator(&m_buffer[0]);
	}
	Iterator end() const {
		return Iterator(&m_buffer[m_size]);
	}
private:
	T* allocate(std::size_t size) {
		return static_cast<T*>(::operator new(sizeof(T) * size));
	}
	void deallocate(T* ptr) {
		::operator delete (ptr);
	}
	void enlarge_capacity_if_need(std::size_t minCapacity) {
		if (minCapacity + 1 > m_capacity) {
			std::size_t newCapacity = m_capacity * 2;
			reallocate(newCapacity);
		}
	}
	void reallocate(std::size_t newCapacity) {
		T* newBuffer = allocate(newCapacity);
		for (std::size_t i = 0; i < m_size ;i++) {
			::new (newBuffer + i) T(std::move(m_buffer[i]));
			(m_buffer + i)->~T();
		}
		deallocate(m_buffer);
		m_buffer = newBuffer;
		m_capacity = newCapacity;
	}
private:
	std::size_t m_size;
	std::size_t m_capacity;
	T* m_buffer;
};

