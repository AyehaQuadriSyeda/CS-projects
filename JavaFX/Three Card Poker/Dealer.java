import java.util.ArrayList;

public class Dealer{
	
	Deck theDeck;
	ArrayList<Card> dealersHand;
	
	Dealer(){
		theDeck = new Deck();
	}
	
	public ArrayList<Card> dealHand(){
		dealersHand = new ArrayList<Card>();
		for(int i = 0; i < 3; i++) {
			if(theDeck.size() >= 3) {
				dealersHand.add(theDeck.get(i));
				theDeck.remove(i);
			}
		}
		
		return dealersHand;
	}
}