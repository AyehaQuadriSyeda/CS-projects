/*
 * Author: Ayesha Quadri Syeda
 * NetID: asyed71
 * Date: 10/2/2022
 * Purpose: Create the GenericList class, implements Iterable<T> interface
 */

import java.util.ArrayList;
import java.util.Iterator;
import java.util.ListIterator;

abstract class GenericList<T> implements Iterable<T>{

	private Node<T> head;
	private int length;
	
	//  Prints the list
	public void print() {
		if(length != 0){
			Node<T> current = head;
			while(current != null) {
				System.out.println(current.data);
				current = current.next;
			}
		}else {
			System.out.println("Empty List");
		}
		
	}
	
	//  abstract method to be implemented
	public abstract void add(T data);
	
	//  Deletes and returns the first element in the list
	public T delete() {
		
		//  check if the list exists
		if(length == 0){
			return null;
		}
		
		//  update length
		length = length - 1;
		
		//  delete the head
		T val = head.data;
		head = head.next;
		
		return val;
	}
	
	//  Stores and returns the list into an ArrayList
	//  Also empties the list in the process
	public ArrayList<T> dumplist(){
		ArrayList<T> store = new ArrayList<>();
		
		while(head != null)
		{
			// store the data
			store.add(head.data);
			
			// delete the node
			delete();
		}
		return store;
	}
	
	//  return the value stored at the given index
	public T get(int index) {
		
		//  Check if index within bounds
		if(index >= length) {
			return null;
		}
		
		//  iterate through the list
		Node <T> current = head;
		for(int i = 0; i < index; i++) {
			current = current.next;
		}
		
		return current.data;
	}
	
	//  Set the node value at the given index to the given element
	//  It returns the old value at the index
	public T set(int index, T element) {
		
		//  Check if index is within bounds
		if(index >= length) {
			return null;
		}
		
		//  Iterate through the list
		Node <T> current = head;
		int count = 0;
		
		while(current != null && count != index) {
			current = current.next;
			count++;
		}
		
		//  Change the value
		T val = current.data;
		current.data = element;
		
		return val;
	}
	
	//  Getter for length
	public int getLength() {
		return length;
	}
	
	//  Setter for length
	public void setLength(int l) {
		length = l;
	}
	
	//  Getter for head
	public Node<T> getHead(){
		return head;
	}
	
	//  Setter for head
	public void setHead(T data, Node<T> next) {
		head = new Node<T>(data);
		head.next = next;
	}
	
	//  Returns an iterator starting from the given index
	public ListIterator<T> listIterator(int index){
		
		ListIterator<T> iterator = new GLListIterator<T>(this);
		
		if(index == 0) {
			return iterator;
		}
		//  Iterate to the index
		while(iterator.hasNext() && iterator.nextIndex() <= index) {
			iterator.next();
		}
		
		return iterator;
	}
	
	//  Returns an iterator that iterates in the descending order
	public Iterator<T> descendingIterator(){
		
		Iterator<T> iterator = new ReverseGLLIterator<T>(this);
		return iterator;
	}
	
	//  Returns an iterator to iterate through the list
	@Override
	public Iterator<T> iterator() {
		Iterator<T> iterator = new GLLIterator<T>(head);
		return iterator;
	}
	
}

//  Inner class to create nodes
class Node<T>{
	
	T data;
	Node<T> next;
	
	public Node(T val) {
		data = val;
		next = null;
	}
	
}