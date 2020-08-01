#ifndef HashMap_HPP
#define HashMap_HPP

#include <cstddef>
#include <utility>

#include "LinkedList.hpp"
#include "Vector.hpp"

template<class Key, class Value, class HashFunc>
class HashMap
{
public:
	
	typedef std::size_t SizeType;
	typedef Key KeyType;
	typedef Value ValueType;
	typedef std::pair<Key, Value> ElementType;
	typedef HashFunc HasherType;
	
private:
	
	Vector<LinkedList<ElementType>> m_buckets;
	HasherType m_hasher;
	float m_max_load_factor;

public:
	
	HashMap(const HasherType &hash_function, SizeType initial_bucket_count = 10, float max_load_factor = 0.75f)
		: m_buckets(initial_bucket_count),
		m_hasher(hash_function),
		m_max_load_factor(max_load_factor)
	{
		for(auto &bucket : m_buckets)
		{
			bucket = LinkedList<ElementType>();
		}
	}
	
private:
	
	//void rehash()
};

#endif
