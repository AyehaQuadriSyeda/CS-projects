/*
 * Author: Ayesha Quadri Syeda
 * NetID: asyed71
 * Date: 10/2/2022
 * Purpose: class to implement the Iterator interface but with reverse iteration
 */

import java.util.Iterator;

class ReverseGLLIterator<T> implements Iterator<T>{
	Node<T> current;
	Node<T> head;
	int index;
	
	//  Sets the Head
	//  Sets the index
	//  Iterates to find the last node and set to current
	public ReverseGLLIterator(GenericList<T> L1) {
		index = L1.getLength();
		head = L1.getHead();
		
		current = head;
		while(current != null) {
			current = current.next;
		}
	}
	
	//  Checks if a next node exists
	public boolean hasNext() {
		if((index - 1) >= 0) {
			return true;
		}
		return false;
	}
	
	//  moves the current to the node before the current one
	public T next() {
		index -= 1;
		current = head;
		int count = 0;
		
		//  Iterate through the list
		while(current != null && count != index) {
			current = current.next;
			count++;
		}
		return current.data;
	}
}