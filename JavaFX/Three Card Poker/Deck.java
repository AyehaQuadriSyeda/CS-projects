import java.util.ArrayList;
import java.util.Collections;

public class Deck extends ArrayList<Card>{
	
	private static final long serialVersionUID = 1L;
	ArrayList<Character> characters;
	ArrayList<Card> d1;
	
	Deck(){
		characters = new ArrayList<>();
		characters.add('C');
		characters.add('D');
		characters.add('S');
		characters.add('H');
		
//		d1 = new ArrayList<>();
		
		for(int i = 0; i < characters.size(); i++) {
			for(int j = 2; j < 15; j++) {
				Card n1 = new Card(characters.get(i), j);
				this.add(n1);
			}
		}
		Collections.shuffle(this);
	}
	void newDeck(){
		this.clear();
		
		for(int i = 0; i < characters.size(); i++) {
			for(int j = 2; j < 15; j++) {
				Card n1 = new Card(characters.get(i), j);
				this.add(n1);
			}
		}
		Collections.shuffle(this);
	}
	
}
