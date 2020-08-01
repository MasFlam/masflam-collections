#ifndef LinkedList_HPP
#define LinkedList_HPP

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
		ElementType value;
		ChainLink *next, *prev;
	};
	
	class LinkedListIterator;
	class LinkedListReverseIterator;
	
public:
	
	typedef LinkedListIterator IteratorType;
	typedef const LinkedListIterator ConstIteratorType;
	typedef LinkedListReverseIterator ReverseIteratorType;
	typedef const LinkedListReverseIterator ConstReverseIteratorType;
	
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
			ChainLink *chain_link = new ChainLink{ .value = value, .next = nullptr, .prev = nullptr };
			m_front = chain_link;
			m_back = chain_link;
			++m_length;
		}
		else
		{
			ChainLink *chain_link = new ChainLink{ .value = value, .next = nullptr, .prev = m_back };
			m_back -> next = chain_link;
			m_back = chain_link;
			++m_length;
		}
	}
	
	void add_front(const ElementType &value)
	{
		if(m_length == 0)
		{
			ChainLink *chain_link = new ChainLink{ .value = value, .next = nullptr, .prev = nullptr };
			m_front = chain_link;
			m_back = chain_link;
			++m_length;
		}
		else
		{
			ChainLink *chain_link = new ChainLink{ .value = value, .next = m_front, .prev = nullptr };
			m_front -> prev = chain_link;
			m_front = chain_link;
			++m_length;
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
			--m_length;
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
			--m_length;
		}
	}
	
	IteratorType begin() noexcept
	{
		return LinkedListIterator(m_front);
	}
	
	ConstIteratorType cbegin() const noexcept
	{
		return LinkedListIterator(m_front);
	}
	
	IteratorType rbegin() noexcept
	{
		return LinkedListReverseIterator(m_back);
	}
	
	ConstIteratorType crbegin() const noexcept
	{
		return LinkedListReverseIterator(m_back);
	}
	
	IteratorType end() noexcept
	{
		return LinkedListIterator(nullptr);
	}
	
	ConstIteratorType cend() const noexcept
	{
		return LinkedListIterator(nullptr);
	}
	
	IteratorType rend() noexcept
	{
		return LinkedListReverseIterator(nullptr);
	}
	
	ConstIteratorType crend() const noexcept
	{
		return LinkedListReverseIterator(nullptr);
	}
	
private:
	
	class LinkedListIterator
	{
		ChainLink *m_chain_link;
		
	public:
		
		LinkedListIterator(ChainLink *chain_link)
			: m_chain_link(chain_link)
		{}
		
		const ElementType &operator*() const
		{
			if(m_chain_link == nullptr)
			{
				throw std::out_of_range("");
			}
			return m_chain_link -> value;
		}
		
		ElementType &operator*()
		{
			if(m_chain_link == nullptr)
			{
				throw std::out_of_range("");
			}
			return m_chain_link -> value;
		}
		
		bool operator==(const LinkedListIterator &other) const noexcept
		{
			return m_chain_link == other.m_chain_link;
		}
		
		bool operator!=(const LinkedListIterator &other) const noexcept
		{
			return m_chain_link != other.m_chain_link;
		}
		
		LinkedListIterator operator++(int)
		{
			LinkedListIterator unincremented(m_chain_link);
			m_chain_link = m_chain_link -> next;
			return unincremented;
		}
		
		const LinkedListIterator &operator++() const
		{
			m_chain_link = m_chain_link -> next;
			return *this;
		}
		
		LinkedListIterator &operator++()
		{
			m_chain_link = m_chain_link -> next;
			return *this;
		}
		
		LinkedListIterator operator--(int)
		{
			LinkedListIterator undecremented(m_chain_link);
			m_chain_link = m_chain_link -> prev;
			return undecremented;
		}
		
		const LinkedListIterator &operator--() const
		{
			m_chain_link = m_chain_link -> prev;
			return *this;
		}
		
		LinkedListIterator &operator--()
		{
			m_chain_link = m_chain_link -> prev;
			return *this;
		}
	};
	
	class LinkedListReverseIterator
	{
		ChainLink *m_chain_link;
		
	public:
		
		LinkedListReverseIterator(ChainLink *chain_link)
			: m_chain_link(chain_link)
		{}
		
		const ElementType &operator*() const
		{
			if(m_chain_link == nullptr)
			{
				throw std::out_of_range("");
			}
			return m_chain_link -> value;
		}
		
		ElementType &operator*()
		{
			if(m_chain_link == nullptr)
			{
				throw std::out_of_range("");
			}
			return m_chain_link -> value;
		}
		
		bool operator==(const LinkedListReverseIterator &other) const noexcept
		{
			return m_chain_link == other.m_chain_link;
		}
		
		bool operator!=(const LinkedListReverseIterator &other) const noexcept
		{
			return m_chain_link != other.m_chain_link;
		}
		
		LinkedListReverseIterator operator++(int)
		{
			LinkedListReverseIterator unincremented(m_chain_link);
			m_chain_link = m_chain_link -> prev;
			return unincremented;
		}
		
		LinkedListReverseIterator &operator++()
		{
			m_chain_link = m_chain_link -> prev;
			return *this;
		}
		
		const LinkedListReverseIterator &operator++() const
		{
			m_chain_link = m_chain_link -> prev;
			return *this;
		}
		
		LinkedListReverseIterator operator--(int)
		{
			LinkedListReverseIterator undecremented(m_chain_link);
			m_chain_link = m_chain_link -> next;
			return undecremented;
		}
		
		LinkedListReverseIterator &operator--()
		{
			m_chain_link = m_chain_link -> next;
			return *this;
		}
		
		const LinkedListReverseIterator &operator--() const
		{
			m_chain_link = m_chain_link -> next;
			return *this;
		}
	};
};

#endif
