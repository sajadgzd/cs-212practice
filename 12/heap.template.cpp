#include <algorithm>   // Provides swap
#include <cassert>

namespace heap_zhu
{
  template <class Item>
  heap<Item>::size_type heap<Item>::parent(heap<Item>::size_type k) const
  {
	assert(k>0);
	return (k-1)/2;
  }

  template <class Item>
  heap<Item>::size_type heap<Item>::left_child(heap<Item>::size_type k) const
  {
	//assert(k < (used-1)/2);
        // no precondition since we are going to use this as the stopping condition
	return 2*k+1;
  }

  template <class Item>
  heap<Item>::size_type heap<Item>::right_child(heap<Item>::size_type k) const
  {
	//assert(k < (used-2)/2);
        // no precondition since we are going to use this as the stopping condition
	return 2*k+2;
  }

  template <class Item>
  void heap<Item>::push(const Item& entry)
  {
	assert(used < CAPACITY);

	size_type current = used++;
	data[current] = entry;

	while ((current != 0) && (data[current] > data[parent(current)]))
	{
		swap(data[current], data[parent(current)]);
		current = parent(current);
	}
  }


  template <class Item>
  void heap<Item>::pop()
  {
	assert(used >0);

	bool done = false;
        size_type lchild, rchild, larger_child;

        swap(data[0],data[--used]);//save the return value to data[used]

	if (used!= 0)
	{
		size_type k = 0;

		while (!done && (lchild = left_child(k)) < used ) // child of k exists
		{
			larger_child = lchild;
      rchild = right_child(k);

      // right child exists and larger
			if ( (rchild < used) && (data[lchild] < data[rchild]) )
				larger_child = rchild;

			if (data[k] >= data [larger_child]) // swap?
			{
				done = true;
			}
			else
			{
				swap(data[k],data[larger_child]);
				k = larger_child;
			}

		}
	}
  }

  // friend of the class
  template <class Item>
  void heap<Item>::heap_sort()
  {
        // Sorting by Popping : from the last one to the first one
        sorted = 0;
	while (heap_size() != 0)
	{
		pop(); // in the pop function we have  h.data[h.used] == h.pop();
		sorted++;
	}
  }

  template <class Item>
  Item& heap<Item>::operator[](const heap<Item>::size_type index)
  {
        assert(index < sorted);
        return data[index];
  }
}
