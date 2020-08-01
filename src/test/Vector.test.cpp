#include "assert.hpp"
#include "Vector.hpp"

void get_when_empty()
{
	Vector<int> vec;
	
	// expect to throw when accessing empty vector
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
	
	// check if A is stored correctly
	ASSERT_NOTHROW(vec.get_back())
	ASSERT(vec.get_back() == A)
	ASSERT_NOTHROW(vec.get_front())
	ASSERT(vec.get_front() == A)
	ASSERT_NOTHROW(vec.get(0))
	ASSERT(vec.get(0) == A)
	
	ASSERT_THROWS(vec.get(1), std::out_of_range)
	ASSERT_THROWS(vec.get(2), std::out_of_range)
	
	ASSERT_NOTHROW(vec.add_back(B))
	
	// check if A is stored correctly
	ASSERT_NOTHROW(vec.get_front())
	ASSERT(vec.get_front() == A)
	ASSERT_NOTHROW(vec.get(0))
	ASSERT(vec.get(0) == A)
	
	// check if B is stored correctly
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
	
	// check if A is correctly stored
	ASSERT_NOTHROW(vec.get_back())
	ASSERT(vec.get_back() == A)
	ASSERT_NOTHROW(vec.get_front())
	ASSERT(vec.get_front() == A)
	ASSERT_NOTHROW(vec.get(0))
	ASSERT(vec.get(0) == A)
	
	ASSERT_THROWS(vec.get(1), std::out_of_range)
	ASSERT_THROWS(vec.get(2), std::out_of_range)
	
	ASSERT_NOTHROW(vec.add_front(B))
	
	// check if A is still in its correct place
	ASSERT_NOTHROW(vec.get_back())
	ASSERT(vec.get_back() == A)
	ASSERT_NOTHROW(vec.get(1))
	ASSERT(vec.get(1) == A)
	
	// check if B is in its correct place
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
		
		// expect to throw when accessing an empty vector
		ASSERT_THROWS(vec.get_back(), std::out_of_range)
		ASSERT_THROWS(vec.get_front(), std::out_of_range)
		ASSERT_THROWS(vec.get(0), std::out_of_range)
		ASSERT_THROWS(vec.get(1), std::out_of_range)
		ASSERT_THROWS(vec.get(2), std::out_of_range)
	}
	
	{
		Vector<int> vec{1, 3, 3, 7, 4, 2, 0};
		constexpr auto LEN = 7;
		
		// checks if the edge values are correct
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
		ASSERT_THROWS(vec.get(LEN + 1), std::out_of_range)
		ASSERT_THROWS(vec.get(LEN + 2), std::out_of_range)
	}
}

void get_after_add_after_initializer_list()
{
	Vector<int> vec{};
	
	// throw assertions here get covered in get_after_initializer_list
	
	ASSERT_NOTHROW(vec.add_back(4))   // 4
	ASSERT_NOTHROW(vec.add(1, 2))     // 4 2
	ASSERT_NOTHROW(vec.add(2, 5))     // 4 2 5
	ASSERT_NOTHROW(vec.add_front(42)) // 42 4 2 5
	ASSERT_NOTHROW(vec.add_back(2))   // 42 4 2 5 2
	ASSERT_NOTHROW(vec.add(3, 52))    // 42 4 2 52 5 2
	ASSERT(vec.count() == 6)
	ASSERT_THROWS(vec.add(7, 1337), std::out_of_range)
}

void get_set_after_initializer_list()
{
	Vector<int> vec{2, 3, 5, 7, 11, 13, 17, 19, 23};
	
	// change around values in the vector
	ASSERT_NOTHROW(vec.set_back(32))
	ASSERT_NOTHROW(vec.set_front(0))
	ASSERT_NOTHROW(vec.set(7, 20))
	
	// check if the changes are reflected
	ASSERT(vec.get_front() == 0)
	ASSERT(vec.get_back() == 32)
	ASSERT(vec.get(7) == 20)
}

void remove_after_count_after_initializer_list()
{
	Vector<int> vec{1, 2, 4, 8, 16, 32, 64};
	
	// test the count method
	ASSERT_NOTHROW(vec.count())
	ASSERT(vec.count() == 7)
	
	// remove front/back/at-pos and check if it changes the vector values and length correctly
	ASSERT_NOTHROW(vec.remove_back())
	ASSERT(vec.count() == 6)
	ASSERT(vec.get_back() == 32)
	ASSERT_NOTHROW(vec.remove_front())
	ASSERT(vec.count() == 5)
	ASSERT(vec.get_front() == 2)
	ASSERT_NOTHROW(vec.remove(1))
	ASSERT(vec.count() == 4)
	ASSERT(vec.get(0) == 2)
	ASSERT(vec.get(1) == 8)
}

void resize_after_initializer_list()
{
	Vector<int> vec{1, 3, 5, 7, 9, 11, 13};
	
	// resize in a way that should shorten the vector length
	ASSERT_NOTHROW(vec.resize(4)) // 1 3 5 7
	ASSERT(vec.capacity() == 4)
	ASSERT(vec.count() == 4)
	ASSERT(vec.get_front() == 1)
	ASSERT(vec.get(1) == 3)
	ASSERT(vec.get(2) == 5)
	ASSERT(vec.get_back() == 7)
	
	// * this test assumes that the vector adjusts its size both when adding and removing elements from it
	// resize in a way that makes the vector a lot longer than necessary,
	// it should resize back to a normal capacity by itself, and it shouldn't throw when doing it.
	// current capcaity: 4; new capacity: 64 = 4*2^4; it should take four actions to resize back.
	ASSERT_NOTHROW(vec.resize(64))
	ASSERT(vec.count() == 4)          // the length should stay the same
	ASSERT(vec.capacity() == 64)
	ASSERT_NOTHROW(vec.remove(2))     // now length = 3, capacity = 32
	ASSERT(vec.count() == 3)
	ASSERT(vec.capacity() == 32)
	ASSERT_NOTHROW(vec.add(2, 3))     // now length = 4, capacity = 16
	ASSERT(vec.count() == 4)
	ASSERT(vec.capacity() == 16)
	ASSERT_NOTHROW(vec.add_back(42))  // now length = 5, capacity = 8
	ASSERT(vec.count() == 5)
	ASSERT(vec.capacity() == 8)
	ASSERT_NOTHROW(vec.remove_back()) // not resizing here yet, because the length == capacity / 2, and the criterion is <
	ASSERT_NOTHROW(vec.remove_back()) // now length = 3, capacity = 4
	ASSERT(vec.count() == 3)
	ASSERT(vec.capacity() == 4)
}

void clear()
{
	{
		Vector<int> vec{1, 3, 3, 7};
		ASSERT(vec.count() == 4)
		ASSERT_NOTHROW(vec.clear())
		ASSERT(vec.count() == 0)
	}
	
	{
		Vector<int> vec{};
		ASSERT(vec.count() == 0)
		ASSERT_NOTHROW(vec.clear())
		ASSERT(vec.count() == 0)
	}
	
	{
		Vector<int> vec;
		ASSERT(vec.count() == 0)
		ASSERT_NOTHROW(vec.clear())
		ASSERT(vec.count() == 0)
	}
	
	{
		Vector<int> vec(0x6FFFFFFF); // should be quite a bit, but it should manage to allocate a buffer this size (it's < 2^31 - 1)
		ASSERT(vec.capacity() == 0x6FFFFFFF)
		ASSERT(vec.count() == 0)
		ASSERT_NOTHROW(vec.clear())
		ASSERT(vec.count() == 0)
	}
}

int main()
{
	get_when_empty();
	get_after_add_back();
	get_after_add_front();
	get_after_initializer_list();
	get_after_add_after_initializer_list();
	get_set_after_initializer_list();
	remove_after_count_after_initializer_list();
	resize_after_initializer_list();
	clear();
}
