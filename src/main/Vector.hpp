#ifndef Vector_HPP
#define Vector_HPP

#include <cstddef>
#include <stdexcept>
#include <initializer_list>

template<class Elem>
class Vector
{
public:
	
	typedef std::size_t SizeType;
	typedef Elem ElementType;
	
private:
	
	class VectorReverseIterator;
	class VectorConstReverseIterator;
	
public:
	
	typedef ElementType * IteratorType;
	typedef const ElementType * ConstIteratorType;
	typedef VectorReverseIterator ReverseIteratorType;
	typedef VectorConstReverseIterator ConstReverseIteratorType;
	
private:
	
	SizeType m_capacity, m_length;
	ElementType *m_buffer;
	
public:
	
	Vector(SizeType initial_capacity = 1)
		: m_capacity(initial_capacity), m_length(0), m_buffer(new ElementType[initial_capacity])
	{}
	
	Vector(std::initializer_list<ElementType> elements)
		: Vector(elements.size())
	{
		for(const ElementType &value : elements)
		{
			add_back(value);
		}
	}
	
	~Vector()
	{
		delete[] m_buffer;
	}
	
private:
	
	void expand_if_needed()
	{
		if(m_length == m_capacity)
		{
			resize(m_capacity * 2);
		}
	}
	
	void contract_if_needed()
	{
		if(m_length < m_capacity / 2)
		{
			resize(m_capacity / 2);
		}
	}
	
public:
	
	void resize(SizeType new_capacity)
	{
		ElementType *new_buffer = new ElementType[new_capacity];
		SizeType new_length = m_length < new_capacity ? m_length : new_capacity;
		for(SizeType i = 0; i < new_length; ++i)
		{
			new_buffer[i] = m_buffer[i];
		}
		m_capacity = new_capacity;
		m_length = new_length;
		delete[] m_buffer;
		m_buffer = new_buffer;
	}
	
	SizeType count() const noexcept
	{
		return m_length;
	}
	
	SizeType capacity() const noexcept
	{
		return m_capacity;
	}
	
	void clear()
	{
		resize(0);
	}
	
	void add_back(const ElementType &value)
	{
		expand_if_needed();
		m_buffer[m_length++] = value;
		contract_if_needed();
	}
	
	void add_front(const ElementType &value)
	{
		add(0, value);
	}
	
	void add(SizeType pos, const ElementType &value)
	{
		if(pos > m_length)
		{
			throw std::out_of_range("");
		}
		expand_if_needed();
		SizeType i;
		for(i = m_length; i > pos; --i)
		{
			m_buffer[i] = m_buffer[i - 1];
		}
		m_buffer[i] = value;
		++m_length;
		contract_if_needed();
	}
	
	ElementType &get_back()
	{
		if(m_length == 0)
		{
			throw std::out_of_range("");
		}
		return m_buffer[m_length - 1];
	}
	
	const ElementType &get_back() const
	{
		if(m_length == 0)
		{
			throw std::out_of_range("");
		}
		return m_buffer[m_length - 1];
	}
	
	ElementType &get_front()
	{
		if(m_length == 0)
		{
			throw std::out_of_range("");
		}
		return m_buffer[0];
	}
	
	const ElementType &get_front() const
	{
		if(m_length == 0)
		{
			throw std::out_of_range("");
		}
		return m_buffer[0];
	}
	
	ElementType &get(SizeType pos)
	{
		if(pos >= m_length)
		{
			throw std::out_of_range("");
		}
		return m_buffer[pos];
	}
	
	const ElementType &get(SizeType pos) const
	{
		if(pos >= m_length)
		{
			throw std::out_of_range("");
		}
		return m_buffer[pos];
	}
	
	void remove_back()
	{
		if(m_length == 0)
		{
			throw std::out_of_range("");
		}
		--m_length;
		contract_if_needed();
		expand_if_needed();
	}
	
	void remove_front()
	{
		remove(0);
	}
	
	void remove(SizeType pos)
	{
		if(pos >= m_length)
		{
			throw std::out_of_range("");
		}
		--m_length;
		for(SizeType i = pos; i < m_length; ++i)
		{
			m_buffer[i] = m_buffer[i + 1];
		}
		contract_if_needed();
		expand_if_needed();
	}
	
	void set_back(const ElementType &value)
	{
		if(m_length == 0)
		{
			throw std::out_of_range("");
		}
		m_buffer[m_length - 1] = value;
	}
	
	void set_front(const ElementType &value)
	{
		if(m_length == 0)
		{
			throw std::out_of_range("");
		}
		m_buffer[0] = value;
	}
	
	void set(SizeType pos, const ElementType &value)
	{
		if(pos >= m_length)
		{
			throw std::out_of_range("");
		}
		m_buffer[pos] = value;
	}
	
	IteratorType begin() noexcept
	{
		return m_buffer;
	}
	
	ConstIteratorType cbegin() const noexcept
	{
		return m_buffer;
	}
	
	ReverseIteratorType rbegin() noexcept
	{
		return VectorReverseIterator(m_buffer + m_length - 1);
	}
	
	ConstReverseIteratorType crbegin() const noexcept
	{
		return VectorConstReverseIterator(m_buffer + m_length - 1);
	}
	
	IteratorType end() noexcept
	{
		return m_buffer + m_length;
	}
	
	ConstIteratorType cend() const noexcept
	{
		return m_buffer + m_length;
	}
	
	ReverseIteratorType rend() noexcept
	{
		return VectorReverseIterator(m_buffer - 1);
	}
	
	ConstReverseIteratorType crend() const noexcept
	{
		return VectorConstReverseIterator(m_buffer - 1);
	}
	
private:
	
	class VectorReverseIterator
	{
		ElementType *m_ptr;
		
	public:
		
		VectorReverseIterator(ElementType *ptr)
			: m_ptr(ptr)
		{}
		
		const ElementType &operator*() const
		{
			return *m_ptr;
		}
		
		ElementType &operator*()
		{
			return *m_ptr;
		}
		
		bool operator==(const VectorReverseIterator &other) const noexcept
		{
			return m_ptr == other.m_ptr;
		}
		
		bool operator!=(const VectorReverseIterator &other) const noexcept
		{
			return m_ptr != other.m_ptr;
		}
		
		VectorReverseIterator operator++(int) noexcept
		{
			VectorReverseIterator unincremented(m_ptr);
			--m_ptr;
			return unincremented;
		}
		
		const VectorReverseIterator &operator++() noexcept
		{
			--m_ptr;
			return *this;
		}
		
		VectorReverseIterator operator--(int) noexcept
		{
			VectorReverseIterator undecremented(m_ptr);
			++m_ptr;
			return undecremented;
		}
		
		const VectorReverseIterator &operator--() noexcept
		{
			++m_ptr;
			return *this;
		}
	};
	
	class VectorConstReverseIterator
	{
		ElementType *m_ptr;
		
	public:
		
		VectorConstReverseIterator(ElementType *ptr)
			: m_ptr(ptr)
		{}
		
		const ElementType &operator*() const
		{
			return *m_ptr;
		}
		
		bool operator==(const VectorConstReverseIterator &other) const noexcept
		{
			return m_ptr == other.m_ptr;
		}
		
		bool operator!=(const VectorConstReverseIterator &other) const noexcept
		{
			return m_ptr != other.m_ptr;
		}
		
		VectorConstReverseIterator operator++(int) noexcept
		{
			VectorConstReverseIterator unincremented(m_ptr);
			--m_ptr;
			return unincremented;
		}
		
		const VectorConstReverseIterator &operator++() noexcept
		{
			--m_ptr;
			return *this;
		}
		
		VectorConstReverseIterator operator--(int) noexcept
		{
			VectorConstReverseIterator undecremented(m_ptr);
			++m_ptr;
			return undecremented;
		}
		
		const VectorConstReverseIterator &operator--() noexcept
		{
			++m_ptr;
			return *this;
		}
	};
};

#endif
