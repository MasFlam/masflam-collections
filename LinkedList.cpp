#ifndef LinkedList_CPP
#define LinkedList_CPP

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <new>

template<class Elem>
class LinkedList
{
public:
	
	typedef std::size_t SizeType;
	typedef Elem ElementType;
	
private:
	
	struct ChainLink
	{
		ElementType &value;
		ChainLink *next, *prev;
	};
	
	class LinkedListIterator;
	
public:
	
	typedef LinkedListIterator IteratorType;
	typedef const LinkedListIterator ConstIteratorType;
	
private:
	
	ChainLink *m_front, *m_back;
	SizeType m_length;
	
public:
	
	LinkedList() noexcept
		: m_front(nullptr), m_back(nullptr), m_length(0)
	{}
	
	LinkedList(std::initializer_list<ElementType> elements)
		: LinkedList()
	{
		for(const ElementType &value : elements)
		{
			add_back(value);
		}
	}
	
	~LinkedList()
	{
		clear();
	}
	
	void add_back(const ElementType &value)
	{
		if(m_length == 0)
		{
			ChainLink *chain_link = new ChainLink{ .value = value, .next = nullptr, .prev = nullptr};
			m_front = chain_link;
			m_back = chain_link;
		}
		else
		{
			ChainLink *chain_link = new ChainLink{ .value = value, .next = nullptr, .prev = m_back};
			m_back -> next = chain_link;
			m_back = chain_link;
		}
	}
	
	void add_front(const ElementType &value)
	{
		if(m_length == 0)
		{
			ChainLink *chain_link = new ChainLink{ .value = value, .next = nullptr, .prev = nullptr};
			m_front = chain_link;
			m_back = chain_link;
		}
		else
		{
			ChainLink *chain_link = new ChainLink{ .value = value, .next = m_front, .prev = nullptr};
			m_front -> next = chain_link;
			m_front = chain_link;
		}
	}
	
	void clear()
	{
		while(m_length > 0)
		{
			remove_back();
		}
	}
	
	SizeType count() const noexcept
	{
		return m_length;
	}
	
	void remove_back()
	{
		if(m_length == 0)
		{
			throw std::out_of_range("");
		}
		else
		{
			ChainLink *old_back = m_back;
			m_back = m_back -> prev;
			delete old_back;
		}
	}
	
	void remove_front()
	{
		if(m_length == 0)
		{
			throw std::out_of_range("");
		}
		else
		{
			ChainLink *old_front = m_front;
			m_front = m_front -> next;
			delete old_front;
		}
	}
	
	IteratorType begin() noexcept
	{
		return LinkedListIterator(*m_front);
	}
	
	ConstIteratorType cbegin() const noexcept
	{
		return LinkedListIterator(*m_front);
	}
	
	/* UNIMPLEMENTED
	IteratorType rbegin() noexcept
	{
		return LinkedListReverseIterator(*m_front);
	}
	*/
	
	/* UNIMPLEMENTED
	ConstIteratorType crbegin() const noexcept
	{
		return LinkedListReverseIterator(*m_front);
	}
	*/
	
	IteratorType end() noexcept
	{
		return LinkedListIterator(*m_back);
	}
	
	ConstIteratorType cend() const noexcept
	{
		return LinkedListIterator(*m_back);
	}
	
	/* UNIMPLEMENTED
	IteratorType rend() noexcept
	{
		return LinkedListReverseIterator(*m_back);
	}
	*/
	
	/* UNIMPLEMENTED
	ConstIteratorType crend() const noexcept
	{
		return LinkedListReverseIterator(*m_back);
	}
	*/
	
private:
	
	// FIXME don't throw
	class LinkedListIterator
	{
		ChainLink &m_chain_link;
		
	public:
		
		LinkedListIterator(const ChainLink &chain_link)
			: m_chain_link(chain_link)
		{}
		
		const ElementType &operator*(int) const noexcept
		{
			return m_chain_link.value;
		}
		
		ElementType &operator*(int) noexcept
		{
			return m_chain_link.value;
		}
		
		bool operator==(const LinkedListIterator &other) const noexcept
		{
			return &m_chain_link == &other.m_chain_link;
		}
		
		bool operator!=(const LinkedListIterator &other) const noexcept
		{
			return &m_chain_link != &other.m_chain_link;
		}
		
		LinkedListIterator operator++(int)
		{
			if(m_chain_link -> next == nullptr)
			{
				throw std::out_of_range("");
			}
			LinkedListIterator unincremented(m_chain_link);
			m_chain_link = *(m_chain_link -> next);
			return unincremented;
		}
		
		// TODO write const ref version
		LinkedListIterator &operator++()
		{
			if(m_chain_link -> next == nullptr)
			{
				throw std::out_of_range("");
			}
			m_chain_link = *(m_chain_link -> next);
			return *this;
		}
		
		LinkedListIterator operator--(int)
		{
			if(m_chain_link -> prev == nullptr)
			{
				throw std::out_of_range("");
			}
			LinkedListIterator undecremented(m_chain_link);
			m_chain_link = *(m_chain_link -> prev);
			return undecremented;
		}
		
		// TODO write const ref version
		LinkedListIterator &operator--()
		{
			if(m_chain_link -> prev == nullptr)
			{
				throw std::out_of_range("");
			}
			m_chain_link = *(m_chain_link -> prev);
			return *this;
		}
	};
};

#endif
