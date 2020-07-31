#include "assert.hpp"
#include "Vector.hpp"

void get_when_empty()
{
	Vector<int> vec;
	ASSERT_THROWS(vec.get_back(), std::out_of_range)
	ASSERT_THROWS(vec.get_front(), std::out_of_range)
	ASSERT_THROWS(vec.get(0), std::out_of_range)
	ASSERT_THROWS(vec.get(1), std::out_of_range)
	ASSERT_THROWS(vec.get(2), std::out_of_range)
}

void get_after_add_back()
{
	constexpr Vector<int>::ElementType A = 42, B = 1337;
	Vector<int> vec;
	
	ASSERT_NOTHROW(vec.add_back(A))
	
	ASSERT_NOTHROW(vec.get_back())
	ASSERT(vec.get_back() == A)
	ASSERT_NOTHROW(vec.get_front())
	ASSERT(vec.get_front() == A)
	ASSERT_NOTHROW(vec.get(0))
	ASSERT(vec.get(0) == A)
	
	ASSERT_THROWS(vec.get(1), std::out_of_range)
	ASSERT_THROWS(vec.get(2), std::out_of_range)
	
	ASSERT_NOTHROW(vec.add_back(B))
	
	ASSERT_NOTHROW(vec.get_front())
	ASSERT(vec.get_front() == A)
	ASSERT_NOTHROW(vec.get(0))
	ASSERT(vec.get(0) == A)
	
	ASSERT_NOTHROW(vec.get_back())
	ASSERT(vec.get_back() == B)
	ASSERT_NOTHROW(vec.get(1))
	ASSERT(vec.get(1) == B)
	
	ASSERT_THROWS(vec.get(2), std::out_of_range)
	ASSERT_THROWS(vec.get(3), std::out_of_range)
}

void get_after_add_front()
{
	constexpr Vector<int>::ElementType A = 424242, B = 999;
	Vector<int> vec;
	
	ASSERT_NOTHROW(vec.add_front(A))
	
	ASSERT_NOTHROW(vec.get_back())
	ASSERT(vec.get_back() == A)
	ASSERT_NOTHROW(vec.get_front())
	ASSERT(vec.get_front() == A)
	ASSERT_NOTHROW(vec.get(0))
	ASSERT(vec.get(0) == A)
	
	ASSERT_THROWS(vec.get(1), std::out_of_range)
	ASSERT_THROWS(vec.get(2), std::out_of_range)
	
	ASSERT_NOTHROW(vec.add_front(B))
	
	ASSERT_NOTHROW(vec.get_back())
	ASSERT(vec.get_back() == A)
	ASSERT_NOTHROW(vec.get(1))
	ASSERT(vec.get(1) == A)
	
	ASSERT_NOTHROW(vec.get_front())
	ASSERT(vec.get_front() == B)
	ASSERT_NOTHROW(vec.get(0))
	ASSERT(vec.get(0) == B)
	
	ASSERT_THROWS(vec.get(2), std::out_of_range)
	ASSERT_THROWS(vec.get(3), std::out_of_range)
}

void get_after_initializer_list()
{
	{
		Vector<int> vec{};
		ASSERT_THROWS(vec.get_back(), std::out_of_range)
		ASSERT_THROWS(vec.get_front(), std::out_of_range)
		ASSERT_THROWS(vec.get(0), std::out_of_range)
		ASSERT_THROWS(vec.get(1), std::out_of_range)
		ASSERT_THROWS(vec.get(2), std::out_of_range)
	}
	
	{
		Vector<int> vec{1, 3, 3, 7, 4, 2, 0};
		constexpr auto LEN = 7;
		ASSERT_NOTHROW(vec.get_back())
		ASSERT(vec.get_back() == 0)
		ASSERT_NOTHROW(vec.get_front())
		ASSERT(vec.get_front() == 1)
		ASSERT_NOTHROW(vec.get(0))
		ASSERT(vec.get(0) == 1)
		ASSERT_NOTHROW(vec.get(1))
		ASSERT(vec.get(1) == 3)
		ASSERT_NOTHROW(vec.get(LEN - 2))
		ASSERT(vec.get(LEN - 2) == 2)
		ASSERT_NOTHROW(vec.get(LEN - 1))
		ASSERT(vec.get(LEN - 1) == 0)
		ASSERT_THROWS(vec.get(LEN), std::out_of_range)
	}
}

int main()
{
	get_when_empty();
	get_after_add_back();
	get_after_add_front();
	get_after_initializer_list();
}