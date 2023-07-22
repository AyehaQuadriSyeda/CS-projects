/*
 * Author: Ayesha Quadri Syeda
 * NetID: asyed71
 * Date: 10/2/2022
 * Purpose: Create the GenericQueue class, extends GenericList<T>
 */

class GenericQueue<T> extends GenericList<T>{

	Node<T> tail;
	
	//  sets the head and tail of the list
	public GenericQueue(T val) {
		
	//  Set Head node
		setHead(val , null);
		tail = getHead();
		
		//  Update List Length
		int l = getLength();
		l = l + 1;
		setLength(1);
	}
	
	//  Add the elements to the back of the list
	@Override
	public void add(T data) {
		
		//  Create a new node and change tail
		Node<T> newnode = new Node<T>(data);
		newnode.next = null;
		tail.next = newnode;
		tail = newnode;
		
		//  Update Length
		setLength(getLength() + 1);
	}
	
	//  Removes the tail node
	//  Updates the tail pointer to last second node
	public T removeTail() {
		int index = getLength() - 2;
		int count = 0;
		
		//  Iterate through the list
		Node<T> current = getHead();
		while(current != null && count != index) {
			current = current.next;
			count++;
		}
		
		// Update the tail
		T val = tail.data;
		tail = current;
		tail.next = null;
		
		// Update the length
		setLength(getLength() - 1);
		
		return val;
	}
	
	//  Calls the add function to add the elements to the back of the list
	public void enqueue(T data) {
		add(data);
	}
	
	//  Calls the delete function to remove the first element in the list
	public T dequeue() {
		T val = delete();
		return val;
	}
}