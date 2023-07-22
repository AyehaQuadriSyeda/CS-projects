/*
 * Author: Ayesha Quadri Syeda
 * NetID: asyed71
 * Date: 10/2/2022
 * Purpose: class to implement the Iterator interface
 */

import java.util.Iterator;

class GLLIterator<T> implements Iterator<T>{
	
	Node<T> current;
	
	//  Set the head of the list to current 
	public GLLIterator(Node<T> head) {
		current = head;
		current.next = head.next;
	}
	
	//  Checks if there is a next node
	public boolean hasNext() {
		if(current != null) {
			return true;
		}
		return false;
	}
	
	//  moves the current node to the next node
	public T next() {
		T val = current.data;
		current = current.next;
		return val;
	}
}