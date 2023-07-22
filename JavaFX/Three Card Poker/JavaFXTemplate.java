import java.util.ArrayList;

import javafx.animation.FadeTransition;
import javafx.animation.PauseTransition;
import javafx.animation.RotateTransition;
import javafx.animation.SequentialTransition;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.FontPosture;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.util.Duration;

public class JavaFXTemplate extends Application {
	
	Player playerOne;
	Player playerTwo;
	Dealer theDealer;
	
	Menu menu;
	MenuItem exit;
	MenuItem newlook;
	MenuItem freshstart;
	MenuBar mbar;
	
	Button playbutton;
	Button infobutton;
//	Button menu;
	Button next1, next2, next3, next4, next5, next6, next7, next8, next9;
	Button playagain;
	Button play, fold;
	Button yes_button, no_button;
	
	Text title, title1, title2;
	Text note1, note2, note3;
	Text ante_title, play_title;
	Text pair_title1, pair_title2;
	Text warning, warning1;
	Text player1, dealer1, player2;
	Text p1ante, p1pair, p1play, p1amount1, p1amount2, p1amount3;
	Text p2ante, p2pair, p2play, p2amount1, p2amount2, p2amount3;
	
	TextField antebet_text, playbet_text;
	TextField pairplus_text1, pairplus_text2;
	
	EventHandler<ActionEvent> event1, event2, event3, event4, event5, event6;
	EventHandler<ActionEvent> event7, event8, event9, event10, event11, event12;
	EventHandler<ActionEvent> event13, event14, event15, event16, event17;
	
	PauseTransition pause = new PauseTransition(Duration.seconds(3));
	
	ArrayList<ImageView> handcards;
	ArrayList<ImageView> handcards1;
	ArrayList<ImageView> handcards2;
	ArrayList<ImageView> dealercards;
	ArrayList<String> club_cards;
	ArrayList<String> heart_cards;
	ArrayList<String> spade_cards;
	ArrayList<String> diamond_cards;
	
	Scene scene1;
	Scene antescene, playscene;
	Scene pairscene1;
	Scene pairscene2;
	Scene card1, card2;
	Scene show, show1, show2, show3;
	
	String background_start;// = "-fx-background-color: FORESTGREEN;";
	String background_other;// = "-fx-background-color: DARKSEAGREEN;";
	String start_button = "-fx-font: bold 25pt 'Verdana';"+"-fx-background-color: GOLD;"+"-fx-text-fill: DARKRED;";
	String other_button = "-fx-font: bold 20pt 'Verdana';"+"-fx-background-color: FLORALWHITE;"+"-fx-text-fill: BLACK;";

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		launch(args);
		
	}
	
	public Scene gameinfo() {
		title2 = new Text();
		title2.setText("GAME INFO:");
		title2.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 60));
	    title2.setFill(Color.BLACK);
	    
	 // set up menu
 		menu = new Menu("OPTIONS");
 		menu.setStyle(other_button);
 		
 		exit = new MenuItem("Exit");
 		newlook = new MenuItem("New Look");
 		freshstart = new MenuItem("Fresh Start");
 		
 		freshstart.setOnAction(event14);
 		newlook.setOnAction(event15);
 		exit.setOnAction(event16);
 		
 		menu.getItems().add(exit);
 		menu.getItems().add(freshstart);
 		menu.getItems().add(newlook);
 		
 		mbar = new MenuBar();
 		mbar.getMenus().add(menu);
	    
	    title1 = new Text();
		title1.setText("Your Total Winnings: " + Integer.toString(playerOne.totalWinnings));
		title1.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 30));
	    title1.setFill(Color.BLACK);
	    
	    title = new Text();
		title.setText("Player 1 Total Winnings: " + Integer.toString(playerTwo.totalWinnings));
		title.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 30));
	    title.setFill(Color.BLACK);
	    
	    playagain = new Button("PLAY AGAIN");
	    playagain.setOnAction(event14);
	    playagain.setStyle(start_button);
	    
	    VBox v = new VBox(30, title2, title1, title, playagain, mbar);
		v.setAlignment(Pos.CENTER);
		v.setStyle(background_other);
		
		show3 = new Scene(v, 700, 700);
		return show3;
	}
	
	public Scene showDealer1() {
		dealer1 = new Text();
		dealer1.setText("Dealer");
		dealer1.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		// Text setup
		player1 = new Text();
		player1.setText("YOU");
		player1.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		getcardimgs(playerOne);
		
		// Cards should be horizontally aligned
		HBox cards1 = new HBox(10, handcards.get(0), handcards.get(1), handcards.get(2));
		cards1.setAlignment(Pos.CENTER);
		
		VBox d1 = new VBox(cards1, player1);
		d1.setAlignment(Pos.CENTER);
		
		getdealcardimg(theDealer);
		
		// Cards should be horizontally aligned
		HBox cards2 = new HBox(10, dealercards.get(0), dealercards.get(1), dealercards.get(2));
		cards2.setAlignment(Pos.CENTER);
		
		VBox d2 = new VBox(dealer1, cards2);
		d2.setAlignment(Pos.CENTER);
		
		next5 = new Button("NEXT");
		next5.setStyle(other_button);
		next5.setOnAction(event13);
		next5.setAlignment(Pos.CENTER);
		
		VBox page = new VBox(50, d2, d1, next5);
		BorderPane pane = new BorderPane(page);
		pane.setCenter(page);
		
		show = new Scene(pane, 700, 700);
		return show;
	} 
	

	public Scene pairwinnings() {
		title2 = new Text();
		title2.setText("PAIR PLUS WINNINGS");
		title2.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 60));
	    title2.setFill(Color.BLACK);
	    
	    Text wonamount = new Text();
	    int total = ThreeCardLogic.evalPPWinnings(playerOne.hand, playerOne.pairPlusBet);
		wonamount.setText("$ " + Integer.toString(total));
		wonamount.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 40));
	    wonamount.setFill(Color.BLACK);
	    
	    int total2 = ThreeCardLogic.evalPPWinnings(playerTwo.hand, playerTwo.pairPlusBet);
	    playerTwo.totalWinnings = playerTwo.totalWinnings + total2;
	    
	    playerOne.totalWinnings = playerOne.totalWinnings + total;
	    
	    next9 = new Button("NEXT");
	    next9.setStyle(other_button);
		next9.setOnAction(event13);
		next9.setAlignment(Pos.CENTER);
	    
	    VBox v = new VBox(30, title2, wonamount, next9);
		v.setAlignment(Pos.CENTER);
		v.setStyle(background_other);
		
		show3 = new Scene(v, 700, 700);
		return show3;
	}
	
	public Scene tie() {
		title2 = new Text();
		title2.setText("IT'S A TIE");
		title2.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 60));
	    title2.setFill(Color.BLACK);
	    
	    title = new Text();
	    int p2win = ThreeCardLogic.compareHands(theDealer.dealersHand, playerTwo.hand);
	    if(p2win == 1) {
	    	title.setText("PLAYER TWO LOST");
	    }
	    else if(p2win == 2) {
	    	title.setText("PLAYER TWO WON");
	    	playerTwo.totalWinnings = playerTwo.totalWinnings + ((playerTwo.anteBet + playerTwo.pairPlusBet) * 2);
	    }
	    else 
	    	title.setText("PLAYER TWO TIED");
	    title.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 60));
	    title.setFill(Color.BLACK);
	    
	    next8 = new Button("NEXT");
	    next8.setStyle(other_button);
		next8.setOnAction(event12);
		next8.setAlignment(Pos.CENTER);
		
		VBox v = new VBox(30, title2, title, next8);
		v.setAlignment(Pos.CENTER);
		v.setStyle(background_other);
		
		show3 = new Scene(v, 700, 700);
		return show3;
	}
	
	public Scene playerwon() {
		title2 = new Text();
		title2.setText("YOU WON");
		title2.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 60));
	    title2.setFill(Color.BLACK);
	    
	    title = new Text();
	    int p2win = ThreeCardLogic.compareHands(theDealer.dealersHand, playerTwo.hand);
	    if(p2win == 1) {
	    	title.setText("PLAYER TWO LOST");
	    }
	    else if(p2win == 2) {
	    	title.setText("PLAYER TWO WON");
	    	playerTwo.totalWinnings = playerTwo.totalWinnings + ((playerTwo.anteBet + playerTwo.pairPlusBet) * 2);
	    }
	    else 
	    	title.setText("PLAYER TWO TIED");
	    title.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 60));
	    title.setFill(Color.BLACK);
	    
	    next8 = new Button("NEXT");
	    next8.setStyle(other_button);
		next8.setOnAction(event12);
		next8.setAlignment(Pos.CENTER);
		
		Text wonamount = new Text();
		int total = (playerOne.anteBet + playerOne.playBet) * 2;
		wonamount.setText("$ " + Integer.toString(total));
		wonamount.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 40));
	    wonamount.setFill(Color.BLACK);
	    
	    playerOne.totalWinnings = playerOne.totalWinnings + total;
		
		VBox v = new VBox(30, title2, wonamount, title, next8);
		v.setAlignment(Pos.CENTER);
		v.setStyle(background_other);
		
		show3 = new Scene(v, 700, 700);
		return show3;
	}
	
	public Scene dealerwon() {
		title2 = new Text();
		title2.setText("DEALER WON");
		title2.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 60));
	    title2.setFill(Color.BLACK);
	    
	    next8 = new Button("NEXT");
	    next8.setStyle(other_button);
		next8.setOnAction(event12);
		next8.setAlignment(Pos.CENTER);
		
		title = new Text();
	    int p2win = ThreeCardLogic.compareHands(theDealer.dealersHand, playerTwo.hand);
	    if(p2win == 1) {
	    	title.setText("PLAYER TWO LOST");
	    }
	    else if(p2win == 2) {
	    	title.setText("PLAYER TWO WON");
	    	playerTwo.totalWinnings = playerTwo.totalWinnings + ((playerTwo.anteBet + playerTwo.pairPlusBet) * 2);
	    }
	    else 
	    	title.setText("PLAYER TWO TIED");
	    title.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 60));
	    title.setFill(Color.BLACK);
		
		VBox v = new VBox(30, title2, title, next8);
		v.setAlignment(Pos.CENTER);
		v.setStyle(background_other);
		
		show3 = new Scene(v, 700, 700);
		return show3;
		
	}
	
	public Scene dealernothigh() {
		note1 = new Text();
	    note1.setText("Dealer Does Not Have a Queen High or Better");
	    note1.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 25));
	    note1.setFill(Color.BLACK);
	    
	    note2 = new Text();
	    note2.setText("Play Wager is Returned");
	    note2.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 25));
	    note2.setFill(Color.BLACK);
	    
	    note3 = new Text();
	    note3.setText("Ante-Bet is Pushed to the Next Hand");
	    note3.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 25));
	    note3.setFill(Color.BLACK);
	    
	    next7 = new Button("NEXT");
	    next7.setStyle(other_button);
		next7.setOnAction(event5);
		next7.setAlignment(Pos.CENTER);
		
		playerOne.playBet = 0;
		playerTwo.playBet = 0;
	    
	    VBox d1 = new VBox(30, note1, note2, note3, next7);
	    d1.setAlignment(Pos.CENTER);
	    d1.setStyle(background_other);
	    
	    show2 = new Scene(d1, 700, 700);
	    
	    return show2;
	    
	    
	} 
	
	public Scene dealerhigh() {
		
		title1 = new Text();
		title1.setText("Dealer has Queen High or Better");
		title1.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		dealer1 = new Text();
		dealer1.setText("Dealer");
		dealer1.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		// Text setup
		player1 = new Text();
		player1.setText("YOU");
		player1.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		getcardimgs(playerOne);
		
		// Cards should be horizontally aligned
		HBox cards1 = new HBox(10, handcards.get(0), handcards.get(1), handcards.get(2));
		cards1.setAlignment(Pos.CENTER);
		
		VBox d1 = new VBox(cards1, player1);
		d1.setAlignment(Pos.CENTER);
		
		getdealcardimg(theDealer);
		
		// Cards should be horizontally aligned
		HBox cards2 = new HBox(10, dealercards.get(0), dealercards.get(1), dealercards.get(2));
		cards2.setAlignment(Pos.CENTER);
		
		VBox d2 = new VBox(dealer1, cards2);
		d2.setAlignment(Pos.CENTER);
		
		next6 = new Button("NEXT");
		next6.setStyle(other_button);
		next6.setOnAction(event11);
		next6.setAlignment(Pos.CENTER);
		
		VBox page = new VBox(50, title1, d2, d1, next6);
		BorderPane pane = new BorderPane(page);
		pane.setCenter(page);
		pane.setTop(title1);
		
		show1 = new Scene(pane, 700, 700);
		return show1;
	}
	
	public Scene showDealer() {
		
		dealer1 = new Text();
		dealer1.setText("Dealer");
		dealer1.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		// Text setup
		player1 = new Text();
		player1.setText("YOU");
		player1.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		getcardimgs(playerOne);
		
		// Cards should be horizontally aligned
		HBox cards1 = new HBox(10, handcards.get(0), handcards.get(1), handcards.get(2));
		cards1.setAlignment(Pos.CENTER);
		
		VBox d1 = new VBox(cards1, player1);
		d1.setAlignment(Pos.CENTER);
		
		getdealcardimg(theDealer);
		
		// Cards should be horizontally aligned
		HBox cards2 = new HBox(10, dealercards.get(0), dealercards.get(1), dealercards.get(2));
		cards2.setAlignment(Pos.CENTER);
		
		VBox d2 = new VBox(dealer1, cards2);
		d2.setAlignment(Pos.CENTER);
		
		next5 = new Button("NEXT");
		next5.setStyle(other_button);
		next5.setOnAction(event10);
		next5.setAlignment(Pos.CENTER);
		
		VBox page = new VBox(50, d2, d1, next5);
		BorderPane pane = new BorderPane(page);
		pane.setCenter(page);
		
		show = new Scene(pane, 700, 700);
		return show;
	}
	
	public Scene playwager() {
		play_title = new Text();
		play_title.setText("PLACE YOUR PLAY WAGER:");
		play_title.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 30));
		
		playbet_text = new TextField();
		playbet_text.setPromptText("$5 - $25");
		playbet_text.setMaxWidth(150);
	
		warning1 = new Text();
		warning1.setText("THIS MUST EQUAL ANTEBET");
		warning1.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		next4 = new Button("NEXT");
		next4.setStyle(other_button);
		next4.setOnAction(event9);
		
		VBox v2 = new VBox(10, play_title, playbet_text, warning1, next4);
		v2.setAlignment(Pos.CENTER);
		
		BorderPane pane = new BorderPane(v2);
		background_other = "-fx-background-color: DARKSEAGREEN;";
		pane.setStyle(background_other);
		
		playscene = new Scene(pane, 700, 700);
	     
	    return playscene;
	}
	
	public ArrayList<ImageView> getcardimgs(Player player){
		
		handcards = new ArrayList<ImageView>();
		for(int i = 0; i < 3; i++) {
			if(player.hand.get(i).suit == 'C') {
				Image pic = new Image(club_cards.get(player.hand.get(i).value));
				ImageView v1 = new ImageView(pic);
				v1.setFitHeight(100);
				v1.setFitWidth(70);
				handcards.add(v1);
			}
			
			if(player.hand.get(i).suit == 'H') {
				Image pic = new Image(heart_cards.get(player.hand.get(i).value));
				ImageView v1 = new ImageView(pic);
				v1.setFitHeight(100);
				v1.setFitWidth(70);
				handcards.add(v1);
			}
			
			if(player.hand.get(i).suit == 'D') {
				Image pic = new Image(diamond_cards.get(player.hand.get(i).value));
				ImageView v1 = new ImageView(pic);
				v1.setFitHeight(100);
				v1.setFitWidth(70);
				handcards.add(v1);
			}
			
			if(player.hand.get(i).suit == 'S') {
				Image pic = new Image(spade_cards.get(player.hand.get(i).value));
				ImageView v1 = new ImageView(pic);
				v1.setFitHeight(100);
				v1.setFitWidth(70);
				handcards.add(v1);
			}
			
		}
		return handcards;
	}

	public void getdealcardimg(Dealer dealer) {
		
		dealercards = new ArrayList<ImageView>();
		for(int i = 0; i < 3; i++) {
			if(dealer.dealersHand.get(i).suit == 'C') {
				Image pic = new Image(club_cards.get(dealer.dealersHand.get(i).value));
				ImageView v1 = new ImageView(pic);
				v1.setFitHeight(100);
				v1.setFitWidth(70);
				dealercards.add(v1);
			}
			
			if(dealer.dealersHand.get(i).suit == 'H') {
				Image pic = new Image(heart_cards.get(dealer.dealersHand.get(i).value));
				ImageView v1 = new ImageView(pic);
				v1.setFitHeight(100);
				v1.setFitWidth(70);
				dealercards.add(v1);
			}
			
			if(dealer.dealersHand.get(i).suit == 'D') {
				Image pic = new Image(diamond_cards.get(dealer.dealersHand.get(i).value));
				ImageView v1 = new ImageView(pic);
				v1.setFitHeight(100);
				v1.setFitWidth(70);
				dealercards.add(v1);
			}
			
			if(dealer.dealersHand.get(i).suit == 'S') {
				Image pic = new Image(spade_cards.get(dealer.dealersHand.get(i).value));
				ImageView v1 = new ImageView(pic);
				v1.setFitHeight(100);
				v1.setFitWidth(70);
				dealercards.add(v1);
			}
			
		}
		
	} 
	public void setupcards(){
		
		club_cards = new ArrayList<String>();
		club_cards.add("");
		club_cards.add("");
		club_cards.add("2_club.png");
		club_cards.add("3_club.png");
		club_cards.add("4_club.png");
		club_cards.add("5_club.png");
		club_cards.add("6_club.png");
		club_cards.add("7_club.png");
		club_cards.add("8_club.png");
		club_cards.add("9_club.png");
		club_cards.add("10_club.png");
		club_cards.add("jack_club.png");
		club_cards.add("queen_club.png");
		club_cards.add("king_club.png");
		club_cards.add("Ace_club.png");
		
		heart_cards = new ArrayList<String>();
		heart_cards.add("");
		heart_cards.add("");
		heart_cards.add("2_heart.png");
		heart_cards.add("3_heart.png");
		heart_cards.add("4_heart.png");
		heart_cards.add("5_heart.png");
		heart_cards.add("6_heart.png");
		heart_cards.add("7_heart.png");
		heart_cards.add("8_heart.png");
		heart_cards.add("9_heart.png");
		heart_cards.add("10_heart.png");
		heart_cards.add("jack_heart.png");
		heart_cards.add("queen_heart.png");
		heart_cards.add("king_heart.png");
		heart_cards.add("Ace_heart.png");
		
		spade_cards = new ArrayList<String>();
		spade_cards.add("");
		spade_cards.add("");
		spade_cards.add("2_spade.png");
		spade_cards.add("3_spade.png");
		spade_cards.add("4_spade.png");
		spade_cards.add("5_spade.png");
		spade_cards.add("6_spade.png");
		spade_cards.add("7_spade.png");
		spade_cards.add("8_spade.png");
		spade_cards.add("9_spade.png");
		spade_cards.add("10_spade.png");
		spade_cards.add("jack_spade.png");
		spade_cards.add("queen_spade.png");
		spade_cards.add("king_spade.png");
		spade_cards.add("Ace_spade.png");
		
		diamond_cards = new ArrayList<String>();
		diamond_cards.add("");
		diamond_cards.add("");
		diamond_cards.add("2_diamond.png");
		diamond_cards.add("3_diamond.png");
		diamond_cards.add("4_diamond.png");
		diamond_cards.add("5_diamond.png");
		diamond_cards.add("6_diamond.png");
		diamond_cards.add("7_diamond.png");
		diamond_cards.add("8_diamond.png");
		diamond_cards.add("9_diamond.png");
		diamond_cards.add("10_diamond.png");
		diamond_cards.add("jack_diamond.png");
		diamond_cards.add("queen_diamond.png");
		diamond_cards.add("king_diamond.png");
		diamond_cards.add("Ace_diamond.png");
		
	}

	public Scene card2() {
		
		// Set up play or fold buttons
		
		play = new Button("PLAY");
		play.setStyle(other_button);
		play.setOnAction(event7);
		
		fold = new Button("FOLD");
		fold.setStyle(other_button);
		fold.setOnAction(event8);
		
		HBox options = new HBox(20, play, fold);
		options.setAlignment(Pos.CENTER);
		
		// Set up bet info for player1
		p1ante = new Text();
		p1ante.setText("Ante-Bet: ");
		
		p1pair = new Text();
		p1pair.setText("Pair-Plus: ");
		
		
		p1amount1 = new Text();
		p1amount1.setText(Integer.toString(playerOne.anteBet));
		
		p1amount2 = new Text();
		p1amount2.setText(Integer.toString(playerOne.pairPlusBet));
		
		HBox a1 = new HBox(5, p1ante, p1amount1);
		HBox a2 = new HBox(5, p1pair, p1amount2);
		
		VBox bets1 = new VBox(5, a1, a2);
		bets1.setAlignment(Pos.CENTER_LEFT);
		
		// Set up bet info for player2
		p2ante = new Text();
		p2ante.setText("Ante-Bet: ");
		
		p2pair = new Text();
		p2pair.setText("Pair-Plus: ");
		
		
		p2amount1 = new Text();
		p2amount1.setText(Integer.toString(playerTwo.anteBet));
		
		p2amount2 = new Text();
		p2amount2.setText(Integer.toString(playerTwo.pairPlusBet));
		
		HBox c1 = new HBox(5, p2ante, p2amount1);
		HBox c2 = new HBox(5, p2pair, p2amount2);
		
		VBox bets2 = new VBox(5, c1, c2);
		bets2.setAlignment(Pos.CENTER);
		
		setupcards();
		
		// Text setup
		player1 = new Text();
		player1.setText("YOU");
		player1.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		player2 = new Text();
		player2.setText("Player 2");
		player2.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		dealer1 = new Text();
		dealer1.setText("Dealer");
		dealer1.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		getcardimgs(playerOne);
		
		// Cards should be horizontally aligned
		HBox cards1 = new HBox(10, handcards.get(0), handcards.get(1), handcards.get(2));
		cards1.setAlignment(Pos.CENTER);
		
		getcardimgs(playerTwo);
		
		// Cards should be vertically aligned
		VBox cards2 = new VBox(10, handcards.get(0), handcards.get(1), handcards.get(2));
		cards2.setAlignment(Pos.CENTER);
		
		// Setup the back cards for the dealer
		Image back1 = new Image("back_card.png");
		ImageView b1 = new ImageView(back1);
		
		b1.setFitHeight(100);
		b1.setFitWidth(70);
		
		Image back2 = new Image("back_card.png");
		ImageView b2 = new ImageView(back2);
		
		b2.setFitHeight(100);
		b2.setFitWidth(70);
		
		Image back3 = new Image("back_card.png");
		ImageView b3 = new ImageView(back3);
		
		b3.setFitHeight(100);
		b3.setFitWidth(70);
		
		// Set up page view
		HBox cards3 = new HBox(10, b1, b2, b3);
		cards3.setAlignment(Pos.CENTER);
		
		VBox you = new VBox(10, cards1, player1);
		you.setAlignment(Pos.CENTER);
		
		HBox you1 = new HBox(20, bets1, you);
		you1.setAlignment(Pos.CENTER);
		
		VBox otherplayer = new VBox(10, cards2, player2, bets2);
		otherplayer.setAlignment(Pos.CENTER);
		
		VBox dealer = new VBox(10, cards3, dealer1);
		dealer.setAlignment(Pos.TOP_CENTER);
		
		VBox page = new VBox(10, dealer, options, otherplayer, you1);
		BorderPane pane = new BorderPane(page);
		pane.setTop(dealer);
		pane.setRight(otherplayer);
		pane.setBottom(you1);
		pane.setCenter(options);
		
		pane.setStyle("-fx-background-color: WHITE;");
		
		card2 = new Scene(pane, 700, 700);
		
		return card2;
				
	}
	public Scene card1() {
		
		next3 = new Button("NEXT");
		next3.setStyle(other_button);
		next3.setOnAction(event6);
		next3.setAlignment(Pos.CENTER);
		
		// Set up bet info for player1
		p1ante = new Text();
		p1ante.setText("Ante-Bet: ");
		
		p1pair = new Text();
		p1pair.setText("Pair-Plus: ");
		
		
		p1amount1 = new Text();
		p1amount1.setText(Integer.toString(playerOne.anteBet));
		
		p1amount2 = new Text();
		p1amount2.setText(Integer.toString(playerOne.pairPlusBet));
		
		HBox a1 = new HBox(5, p1ante, p1amount1);
		HBox a2 = new HBox(5, p1pair, p1amount2);
		
		VBox bets1 = new VBox(5, a1, a2);
		bets1.setAlignment(Pos.CENTER_LEFT);
		
		// Set up bet info for player2
		p2ante = new Text();
		p2ante.setText("Ante-Bet: ");
		
		p2pair = new Text();
		p2pair.setText("Pair-Plus: ");
		
		
		p2amount1 = new Text();
		p2amount1.setText(Integer.toString(playerTwo.anteBet));
		
		p2amount2 = new Text();
		p2amount2.setText(Integer.toString(playerTwo.pairPlusBet));
		
		HBox c1 = new HBox(5, p2ante, p2amount1);
		HBox c2 = new HBox(5, p2pair, p2amount2);
		
		VBox bets2 = new VBox(5, c1, c2);
		bets2.setAlignment(Pos.CENTER);
		
		setupcards();

		// Text setup
		player1 = new Text();
		player1.setText("YOU");
		player1.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		player2 = new Text();
		player2.setText("Player 2");
		player2.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		dealer1 = new Text();
		dealer1.setText("Dealer");
		dealer1.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		handcards1 = new ArrayList<ImageView>();
		handcards2 = new ArrayList<ImageView>();
		
		handcards1 = getcardimgs(playerOne);
		
		// Cards should be horizontally aligned
		HBox cards1 = new HBox(10, handcards1.get(0), handcards1.get(1), handcards1.get(2));
		cards1.setAlignment(Pos.CENTER);
		
		handcards2 = getcardimgs(playerTwo);
		
		// Cards should be vertically aligned
		VBox cards2 = new VBox(10, handcards2.get(0), handcards2.get(1), handcards2.get(2));
		cards2.setAlignment(Pos.CENTER);
		
		// Setup the back cards for the dealer
		Image back1 = new Image("back_card.png");
		ImageView b1 = new ImageView(back1);
		
		b1.setFitHeight(100);
		b1.setFitWidth(70);
		
		Image back2 = new Image("back_card.png");
		ImageView b2 = new ImageView(back2);
		
		b2.setFitHeight(100);
		b2.setFitWidth(70);
		
		Image back3 = new Image("back_card.png");
		ImageView b3 = new ImageView(back3);
		
		b3.setFitHeight(100);
		b3.setFitWidth(70);
		
		// Set up page view
		HBox cards3 = new HBox(10, b1, b2, b3);
		cards3.setAlignment(Pos.CENTER);
		
		VBox you = new VBox(10, cards1, player1);
		you.setAlignment(Pos.CENTER);
		
		HBox you1 = new HBox(20, bets1, you);
		you1.setAlignment(Pos.CENTER);
		
		VBox otherplayer = new VBox(10, cards2, player2, bets2);
		otherplayer.setAlignment(Pos.CENTER);
		
		VBox dealer = new VBox(10, cards3, dealer1);
		dealer.setAlignment(Pos.TOP_CENTER);
		
		VBox page = new VBox(10, dealer, next3, otherplayer, you1);
		BorderPane pane = new BorderPane(page);
		pane.setTop(dealer);
		pane.setRight(otherplayer);
		pane.setBottom(you1);
		pane.setCenter(next3);
		
		pane.setStyle("-fx-background-color: WHITE;");
		
		card1 = new Scene(pane, 700, 700);
		
		return card1;
		
	}
	
	public Scene pairplus2() {

		pair_title2 = new Text();
		pair_title2.setText("PLACE YOUR PAIR PLUS BET:");
		pair_title2.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 30));
		
		pairplus_text1 = new TextField();
		pairplus_text1.setPromptText("$5 - $25");
		pairplus_text1.setMaxWidth(150);
	
		warning = new Text();
		warning.setText("*$5 - $25*");
		warning.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		next2 = new Button("NEXT");
		next2.setStyle(other_button);
		next2.setOnAction(event4);
		
		VBox v2 = new VBox(10, pair_title2, pairplus_text1, warning, next2);
		v2.setAlignment(Pos.CENTER);
		
		BorderPane pane = new BorderPane(v2);
		pane.setStyle(background_other);
		
		
		pairscene2 = new Scene(pane, 700, 700);
	     
	    return pairscene2;
	}
	
	public Scene pairplus1() {
		
		pair_title1 = new Text();
		pair_title1.setText("WOULD YOU LIKE TO MAKE A PAIR PLUS BET?");
		pair_title1.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 30));
		
		yes_button = new Button("YES");
		yes_button.setStyle(other_button);
		yes_button.setOnAction(event3);
		
		no_button = new Button("NO");
		no_button.setStyle(other_button);
		no_button.setOnAction(event5);
		
		HBox choice = new HBox(10, yes_button, no_button);
		choice.setAlignment(Pos.CENTER);
		
		VBox page = new VBox(40, pair_title1, choice);
		page.setAlignment(Pos.CENTER);
		
		BorderPane pane = new BorderPane(page);
		pane.setStyle(background_other);
		
		pairscene1 = new Scene(pane, 700, 700);
	     
	    return pairscene1;
		
		
	}
	
	public Scene antebet() {
		
		ante_title = new Text();
		ante_title.setText("PLACE YOUR ANTE-BET:");
		ante_title.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 30));
		
		antebet_text = new TextField();
		antebet_text.setPromptText("$5 - $25");
		antebet_text.setMaxWidth(150);
	
		warning = new Text();
		warning.setText("*$5 - $25*");
		warning.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.REGULAR, 15));
		
		next1 = new Button("NEXT");
		next1.setStyle(other_button);
		
		VBox v2 = new VBox(10, ante_title, antebet_text, warning, next1);
		v2.setAlignment(Pos.CENTER);
		
		BorderPane pane = new BorderPane(v2);
		background_other = "-fx-background-color: DARKSEAGREEN;";
		pane.setStyle(background_other);
		
		next1.setOnAction(event2);
		antescene = new Scene(pane, 700, 700);
	     
	    return antescene;
		
	}

	public Scene startpage() {
		
		playbutton = new Button("PLAY");
	    playbutton.setCenterShape(true);
	    playbutton.setStyle(start_button);
	    
	 // set up menu
 		menu = new Menu("OPTIONS");
 		menu.setStyle(other_button);
 		
 		exit = new MenuItem("Exit");
 		newlook = new MenuItem("New Look");
 		freshstart = new MenuItem("Fresh Start");
 		
 		freshstart.setOnAction(event14);
 		newlook.setOnAction(event15);
 		exit.setOnAction(event16);
 		
 		menu.getItems().add(exit);
 		menu.getItems().add(freshstart);
 		menu.getItems().add(newlook);
 		
 		mbar = new MenuBar();
 		mbar.getMenus().add(menu);
	     
	    title = new Text();
	    title.setText("THREE CARD POKER");
	    title.setFont(Font.font("Monaco", FontWeight.BOLD, FontPosture.ITALIC, 50));
	    title.setFill(Color.DARKRED);
	     
	    VBox startpage = new VBox(50, title, playbutton, mbar);
	    
	    BorderPane pane = new BorderPane(startpage);
	    pane.setCenter(startpage);
	     
	    pane.setStyle(background_start);
	     
	    startpage.setAlignment(Pos.CENTER);
	     
	    playbutton.setOnAction(event1);
	    scene1 = new Scene(pane, 700, 700);
	     
	    return scene1;
	}
	@Override
	public void start(Stage primaryStage) throws Exception {
		// TODO Auto-generated method stub
		primaryStage.setTitle("Three Card Poker");
		
		background_start = "-fx-background-color: FORESTGREEN;";
		background_other = "-fx-background-color: DARKSEAGREEN;";
		
		playerOne = new Player();
		playerTwo = new Player();
		theDealer = new Dealer();
		
		// set up menu
		menu = new Menu("OPTIONS");
		menu.setStyle(other_button);
		
		exit = new MenuItem("Exit");
		newlook = new MenuItem("New Look");
		freshstart = new MenuItem("Fresh Start");
		
		freshstart.setOnAction(event14);
		newlook.setOnAction(event15);
		exit.setOnAction(event16);
		
		menu.getItems().add(exit);
		menu.getItems().add(freshstart);
		menu.getItems().add(newlook);
		
		mbar = new MenuBar();
		mbar.getMenus().add(menu);
		
		
		// Play was pressed on the start page
		event1 = new EventHandler<ActionEvent>(){
			public void handle(ActionEvent event){
				primaryStage.setScene(antebet());
			}
		};
		
		// Next was pressed after placing ante bet
		event2 = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				Integer antebet = Integer.parseInt(antebet_text.getText());
				if(antebet_text.getText().isEmpty()) {
					primaryStage.setScene(antebet());
				}
				if(antebet > 25 || antebet < 5) {
					primaryStage.setScene(antebet());
				}
				else {
					int rand = (int)(Math.random() * 19) + 5;
					playerTwo.anteBet = rand;
					playerOne.anteBet = antebet;
					primaryStage.setScene(pairplus1());
				}
				
			}
		};
		
		// Yes button to pair plus bet pressed
		event3 = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				primaryStage.setScene(pairplus2());
			}
		};
		
		// No button to pair plus bet pressed
		event5 = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				if(theDealer.theDeck.size() > 34) {
					playerOne.hand = theDealer.dealHand();
					playerTwo.hand = theDealer.dealHand();
					theDealer.dealersHand = theDealer.dealHand();
					primaryStage.setScene(card1());
				}
				else {
					theDealer.theDeck.newDeck();
					playerOne.hand = theDealer.dealHand();
					playerTwo.hand = theDealer.dealHand();
					theDealer.dealersHand = theDealer.dealHand();
					primaryStage.setScene(card1());
				}
			}
		};
		
		// Next was pressed after entering pair plus bet
		event4 = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				Integer pairbet = Integer.parseInt(pairplus_text1.getText());
				if(pairplus_text1.getText().isEmpty()) {
					primaryStage.setScene(pairplus2());
				}
				
				if(pairbet > 25 || pairbet < 5) {
					primaryStage.setScene(pairplus2());
				}
				else {
					
					int rand = (int)(Math.random() * 19) + 5;
					playerTwo.pairPlusBet = rand;
					playerOne.pairPlusBet = pairbet;
					
					if(theDealer.theDeck.size() > 34) {
						playerOne.hand = theDealer.dealHand();
						playerTwo.hand = theDealer.dealHand();
						theDealer.dealersHand = theDealer.dealHand();
						primaryStage.setScene(card1());
					}
					else {
						theDealer.theDeck.newDeck();
						playerOne.hand = theDealer.dealHand();
						playerTwo.hand = theDealer.dealHand();
						theDealer.dealersHand = theDealer.dealHand();
						primaryStage.setScene(card1());
					}
				}
				
			}
		};
		
		// Next was pressed after seeing the player cards
		event6 = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				primaryStage.setScene(card2());
			}
		};
		
		// Play button is pressed after deal
		event7 = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				primaryStage.setScene(playwager());
			}
		};
		
		// Next is pressed after entering play wager
		event9 = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				Integer playbet = Integer.parseInt(playbet_text.getText());
				if(playbet != playerOne.anteBet) {
					primaryStage.setScene(playwager());
				}
				else {
					playerTwo.playBet = playerTwo.anteBet;
					playerOne.playBet = playbet;
					primaryStage.setScene(showDealer());
				}
			}
		};
		
		// Fold button is pressed
		event8 = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				playerOne.totalWinnings = 0;
				primaryStage.setScene(showDealer1());
				
			}
		};
		
		event10 = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				if(theDealer.dealersHand.get(0).value > 11 || theDealer.dealersHand.get(1).value > 11 || theDealer.dealersHand.get(2).value > 11) {
					primaryStage.setScene(dealerhigh());	
				}
				else
					primaryStage.setScene(dealernothigh());
			}
		};
		
		// Scenes of who won
		event11 = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				if(ThreeCardLogic.compareHands(theDealer.dealersHand, playerOne.hand) == 1) {
					primaryStage.setScene(dealerwon());
				}
				else if(ThreeCardLogic.compareHands(theDealer.dealersHand, playerOne.hand) == 2) {
					playerOne.totalWinnings = playerOne.totalWinnings + ((playerOne.anteBet + playerOne.playBet) * 2);
					primaryStage.setScene(playerwon());
				}
				else {
					primaryStage.setScene(tie());
				}
			}
		};
		
		// Pair plus winnings is shown
		event12 = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				primaryStage.setScene(pairwinnings());
			}
		};
		
		// Game info is reached
		event13 = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				primaryStage.setScene(gameinfo());
			}
		};
		
		event14 = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				playerOne.totalWinnings = 0;
				playerTwo.totalWinnings = 0;
				primaryStage.setScene(startpage());
			}
		};
		
		event15 = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				background_other = "-fx-background-color: WHITE;";
				background_start = "-fx-background-color: GREEN;";
			}
		};
		
		event16 = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent event) {
				System.exit(0);
			}
		};
		
		
		
		primaryStage.setScene(startpage());
		primaryStage.show();
	}

}
