import java.util.ArrayList;

public class ThreeCardLogic{
	
	
	// Returns true if the hand has all the same type (suit) of the card
	private static boolean matchType(ArrayList<Card> hand) {
		
		if(hand.get(0).suit == hand.get(1).suit) {
			if(hand.get(1).suit == hand.get(2).suit) {
				return true;
			}
		}
		return false;
	}
	
	// Returns true if the hand is in order by value
	private static boolean matchOrder(ArrayList<Card> hand) {
		
		int order1 = 0;
		int order2 = 0;
		
		order1 = hand.get(0).value - 1;
		order2 = hand.get(2).value - 1;
		
		if(order1 == hand.get(1).value) {
			if(order2 == hand.get(2).value) {
				return true;
			}
		}
		
		order1 = hand.get(2).value - 1;
		order2 = hand.get(1).value - 1;
		
		if(order1 == hand.get(1).value) {
			if(order2 == hand.get(0).value) {
				return true;
			}
		}
		
		order1 = hand.get(1).value - 1;
		order2 = hand.get(0).value - 1;
		
		if(order1 == hand.get(0).value) {
			if(order2 == hand.get(2).value) {
				return true;
			}
		}
		
		order1 = hand.get(0).value - 1;
		order2 = hand.get(2).value - 1;
		
		if(order1 == hand.get(1).value) {
			if(order2 == hand.get(0).value) {
				return true;
			}
		}
		
		return false;
	}
	
	private static boolean mismatchType(ArrayList<Card> hand) {
		if(hand.get(0).suit != hand.get(1).suit) {
			if(hand.get(1).suit != hand.get(2).suit) {
				if(hand.get(0).suit != hand.get(2).suit) {
					return true;
				}
			}
		}
		return false;
	}
	
	private static boolean matchtwoType(ArrayList<Card> hand) {
		
		if(hand.get(0).suit == hand.get(1).suit) {
			return true;
		}
		
		if(hand.get(1).suit == hand.get(2).suit) {
			return true;
		}
		
		if(hand.get(0).suit == hand.get(2).suit) {
			return true;
		}
		
		return false;
	}
	
	private static boolean matchValue(ArrayList<Card> hand) {
		
		if(hand.get(0).value == hand.get(1).value) {
			if(hand.get(1).value == hand.get(2).value) {
				return true;
			}
		}
		return false;
		
	}
	
	public static int evalHand(ArrayList<Card> hand) {
		
//		// Check for High Card
//		for(int i = 0; i < hand.size(); i++) {
//			if(hand.get(i).value >= 12) {
//				return 0;
//			}
//		}
		
		// Check for Straight Flush
		if(matchType(hand)) {
			if(matchOrder(hand)) {
				return 1;
			}
			else {
				// This is a Flush
				return 4;
			}
		}
		
		// Check for Three of a kind
		if(mismatchType(hand)) {
			if(matchValue(hand)) {
				return 2;
			}
			
			// Straight pair
			if(matchOrder(hand)) {
				return 3;
			}
		}
		
		//  Check for pair
		if(matchtwoType(hand)) {
			return 5;
		}
		
		return 0;
		
	}
	
	public static int evalPPWinnings(ArrayList<Card> hand, int bet) {
		int result = 0;
		result = evalHand(hand);
		
		if(result == 1) {
			return (bet * 41);
		}
		
		if(result == 2) {
			return (bet * 31);
		}
		
		if(result == 3) {
			return (bet * 7);
		}
		
		if(result == 4) {
			return (bet * 4);
		}
		
		if(result == 5) {
			return (bet * 2);
		}
		return 0;
	}
	
	public static int compareHands(ArrayList<Card> dealer, ArrayList<Card> player) {
		
		int result1 = 0;
		int result2 = 0;
		
		result1 = evalHand(dealer);
		result2 = evalHand(player);
		
		if(result1 < result2) {
			return 2;
		}
		if(result1 > result2) {
			return 1;
		}
		
		return 0;
	}
	
}