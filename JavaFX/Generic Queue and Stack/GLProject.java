/*
 * Author: Ayesha Quadri Syeda
 * NetID: asyed71
 * Date: 10/2/2022
 * Purpose: Project to learn Interfaces and Class inheritance
 */

import java.util.Iterator;
import java.util.ListIterator;

public class GLProject {

	public static void main(String[] args) {
		
		//  Test the different functions of GenericQueue class
		GenericQueue<Integer> list1 = new GenericQueue<> (10);
		
		//  Test add()
		System.out.println("Test generic queues");
		list1.add(20);
		list1.add(30);
		list1.add(40);
		list1.print();
		
		//  Test set()
		System.out.println("Test set()");
		//System.out.println(list1.getLength());
		list1.set(2, 100);
		list1.print();
		
		//  Test Iterator()
		System.out.println("Test iterator");
		Iterator<Integer> it1 = list1.iterator();
		while(it1.hasNext()) {
			System.out.println(it1.next());
		}
		
		//  Test descendingIterator()
		System.out.println("Test Reverse iterator");
		Iterator<Integer> it2 = list1.descendingIterator();
		while(it2.hasNext()) {
			System.out.println(it2.next());
		}
		
		//  Test for each loop
		System.out.println("Test foreach()");
		for(int a : list1){
			System.out.println(a);
		}
		
		//  Test List-Iterator
		System.out.println("Original List:");
		list1.print();
		System.out.println("Test List Iterator");
		ListIterator<Integer> LI1 =	list1.listIterator(1);
		while(LI1.hasNext()) {
			System.out.println(LI1.next());
		}
		
		//  Test functions of GenericStack class
		System.out.println("Test generic stack");
		GenericStack<Integer> list2 = new GenericStack<>(10);
		
		//  Test add()
		list2.add(20);
		list2.add(30);
		list2.add(40);
		list2.print();
		
		//  Test pop()
		System.out.println("Test pop()");
		list2.pop();
		System.out.println(list2.getLength());
		list2.print();
	}
}
