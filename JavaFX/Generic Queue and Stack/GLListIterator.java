/*
 * Author: Ayesha Quadri Syeda
 * NetID: asyed71
 * Date: 10/2/2022
 * Purpose: class to implement the ListIterator interface
 */

import java.util.ListIterator;

class GLListIterator<E> implements ListIterator<E>{
	
	Node<E> currentfor;
	Node<E> current;
	Node<E> currentprev;
	Node<E> head;
	int index;
	
	//  Sets the Head of the list
	public GLListIterator(GenericList<E> list) {
		index = 0;
		head = list.getHead();
		current = head;
		currentfor = head;
		currentprev = head;
	}

	//  Checks if there is a value after the current one
	@Override
	public boolean hasNext() {
		
		if(current != null) {
			return true;
		}
		
		return false;
	}

	//  Changes the current node to the next node
	@Override
	public E next() {
		E val = current.data;
	    currentprev = current;
	    index++;
	    current = current.next;
		return val;
	}

	//  Checks if there is a previous node
	@Override
	public boolean hasPrevious() {
		if((index-1) >= 0) {
			return true;
		}
		return false;
	}

	//  sets the current node equal to the previous node
	@Override
	public E previous() {
		current = currentprev;
		index--;
		if(index > 0) {
			int count = 0;
			currentprev = head;
			while(currentprev != null && count != (index - 1)) {
				currentprev = currentprev.next;
			}
		}else if(index == 0) {
			currentprev = head;
		}
		return current.data;
	}

	//  return the next Index
	@Override
	public int nextIndex() {
		return index + 1;
	}

	//  returns the previous index
	@Override
	public int previousIndex() {
		return index - 1;
	}
	
//  Unimplemented methods
	
	@Override
	public void remove() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void set(E e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void add(E e) {
		// TODO Auto-generated method stub
		
	}
	
}