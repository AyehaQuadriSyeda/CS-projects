/*
 * Author: Ayesha Quadri Syeda
 * NetID: asyed71
 * Date: 10/2/2022
 * Purpose: Create the GenericStack class, extends the GenericList<T> class
 */

class GenericStack<T> extends GenericList<T>{

	Node<T> tail;
	
	//  sets the head and tail of the list
	public GenericStack(T val) {
		
		//  Set Head node
		setHead(val , null);
		tail = getHead();
		
		//  Update List Length
		int l = getLength();
		l = l + 1;
		setLength(getLength() + 1);
	}
	
	//  Adds the elements from the head of the list
	@Override
	public void add(T data) {
		
		//  Add element
		Node<T> curHead = getHead();
		setHead(data, curHead);
		
		//  Update list length
		int l = getLength();
		l = l + 1;
		setLength(getLength() + 1);
	}
	
	//  Removes the tail node
	//  Updates the tail pointer to last second node
	public T removeTail() {
		
		int index = getLength() - 2;
		int count = 0;
		
		//  Iterate througn the list
		Node<T> current = getHead();
		while(current != null && count != index) {
			current = current.next;
			count++;
		}
		
		//  Update the tail node
		T val = tail.data;
		tail = current;
		tail.next = null;
		
		//  Update the length
		setLength(getLength() - 1);
		
		return val;
	}
	
	//  Calls the add function 
	public void push(T data) {
		add(data);
	}
	
	//  Calls the delete function
	public T pop() {
		T val;
		val = delete();
		return val;
	}
	
	
}