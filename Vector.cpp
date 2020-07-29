#ifndef Vector_CPP
#define Vector_CPP

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
	
	class VectorIterator;
	
public:
	
	typedef VectorIterator IteratorType;
	typedef const VectorIterator ConstIteratorType;
	
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
	
	void add_back(const ElementType &value)
	{
		expand_if_needed();
		m_buffer[++m_length] = value;
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
		for(i = m_length; i > pos; )
		{
			m_buffer[i] = m_buffer[--i];
		}
		m_buffer[i] = value;
	}
	
	ElementType &get_back() noexcept
	{
		return m_buffer[m_length - 1];
	}
	
	const ElementType &get_back() const noexcept
	{
		return m_buffer[m_length - 1];
	}
	
	ElementType &get_front() noexcept
	{
		return m_buffer[0];
	}
	
	const ElementType &get_front() const noexcept
	{
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
		--m_length;
		contract_if_needed();
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
		for(SizeType i = m_length; i-- > 0; )
		{
			m_buffer[i] = m_buffer[i - 1];
		}
		contract_if_needed();
	}
	
	void set_back(const ElementType &value) noexcept
	{
		m_buffer[m_length - 1] = value;
	}
	
	void set_front(const ElementType &value) noexcept
	{
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
		return VectorIterator(m_buffer, 0, m_length);
	}
	
	ConstIteratorType cbegin() noexcept
	{
		return VectorIterator(m_buffer + m_length, m_length, m_length);
	}
	
	/* UNIMPLEMENTED
	IteratorType rbegin() noexcept
	{
		return VectorReverseIterator(m_buffer, 0, m_length);
	}
	*/
	
	/* UNIMPLEMENTED
	ConstIteratorType crbegin() noexcept
	{
		return VectorReverseIterator(m_buffer + m_length, m_length, m_length);
	}
	*/
	
private:
	
	
	// FIXME unnecessary, i don't actually want to throw there...
	class VectorIterator
	{
		ElementType *m_element;
		SizeType m_pos;
		const SizeType &m_vector_length;
		
	public:
		
		VectorIterator(ElementType *ptr, SizeType pos, const SizeType &vector_length)
			: m_element(ptr), m_pos(pos), m_vector_length(vector_length)
		{}
		
		const ElementType &operator*(int) const noexcept
		{
			return *m_element;
		}
		
		ElementType &operator*(int) noexcept
		{
			return *m_element;
		}
		
		bool operator==(const VectorIterator &other) const noexcept
		{
			return m_element == other.m_element;
		}
		
		bool operator!=(const VectorIterator &other) const noexcept
		{
			return m_element != other.m_element;
		}
		
		VectorIterator operator++(int)
		{
			if(m_pos == m_vector_length - 1)
			{
				throw std::out_of_range("");
			}
			VectorIterator unincremented(m_element, m_pos, m_vector_length);
			++m_element;
			++m_pos;
			return unincremented;
		}
		
		// TODO write const ref version
		VectorIterator &operator++()
		{
			if(m_pos == m_vector_length - 1)
			{
				throw std::out_of_range("");
			}
			++m_element;
			++m_pos;
			return *this;
		}
		
		VectorIterator operator--(int)
		{
			if(m_pos == 0)
			{
				throw std::out_of_range("");
			}
			VectorIterator undecremented(m_element, m_pos, m_vector_length);
			--m_element;
			--m_pos;
			return undecremented;
		}
		
		// TODO write const ref version
		VectorIterator &operator--()
		{
			if(m_pos == m_vector_length - 1)
			{
				throw std::out_of_range("");
			}
			--m_element;
			--m_pos;
			return *this;
		}
	};
};

#endif
