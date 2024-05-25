import 'package:flutter/cupertino.dart';
import 'package:flutter/gestures.dart';
import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import '_sliverscroll.dart';
import 'details.dart';
import 'package:url_launcher/url_launcher.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: MyHomePage(),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({super.key});

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  List<String> titles_action =["Damsel", "Lift", "Land of Bad"];
  List<String> details_action = ["Director: Juan Carlos Fresnadillo, Year: 2024", "Director: F. Gary Gray, Year: 2024", "Director: William Eubank, Year: 2024"];
  List<String> imgs_action = ["damsel.jpg", "lift.jpeg", "land_of_bad.jpeg"];
  List<String> link_action = ["https://www.imdb.com/title/tt13452446/", "https://www.imdb.com/title/tt14371878/", "https://www.imdb.com/title/tt19864802/"];
  List<String> link2_action = ["https://en.wikipedia.org/wiki/Damsel_(2024_film)", "https://en.wikipedia.org/wiki/Lift_(2024_film)", "https://en.wikipedia.org/wiki/Land_of_Bad"];
  List<String> details2_action = ["Director: Juan Carlos Fresnadillo\n\n"+
      "Actors: \n\tMillie Bobby Brown\n\tRay Winstone\n\tNick Robinson\n\tShohreh Aghdashloo\n\tAngela Bassett\n\tRobin Wright\n\n"+
  "Duration: 1 hr 50 mins\n\nRatings: \n\tRotten Tomatoes: 4.1/5.0\n\tIMDb: 6.1/10",
  "Director: F. Gary Gray\n\n"+
      "Actors: \n\tKevin Hart\n\tGugu Mbatha-Raw\n\tVincent D'Onofrio\n\tÚrsula Corberó\n\tBilly Magnussen\n\tJacob Batalon\n\tJean Reno\n\tSam Worthington\n\n" +
      "Duration: 1 hr 47 mins\n\nRatings: \n\tRotten Tomatoes: 2.8/5.0\n\tIMDb: 5.5/10",
  "Director: 	William Eubank\n\n" +
      "Actors: \n\tLiam Hemsworth\n\tRussell Crowe\n\tLuke Hemsworth\n\tRicky Whittle\n\tMilo Ventimiglia" +
      "Duration: 1 hr 50 mins\n\nRatings: \n\tRotten Tomatoes: 4.3/5.0\n\tIMDb: 6.5/10"];

  List<String> titles_comedy =["The Hangover", "Green Book", "We're The Millers"];
  List<String> details_comedy = ["Director: Todd Phillips, Year: 2009", "Director: Peter Farrelly, Year: 2018", "Director: Rawson Marshall Thurber, Year: 2013"];
  List<String> imgs_comedy = ["hangover.jpeg", "green_book.jpeg", "we're_the_millers.jpeg"];
  List<String> link_comedy = ["https://www.imdb.com/title/tt1119646/", "https://www.imdb.com/title/tt6966692/", "https://www.imdb.com/title/tt1723121/"];
  List<String> link2_comedy = ["https://en.wikipedia.org/wiki/The_Hangover", "https://en.wikipedia.org/wiki/Green_Book_(film)", "https://en.wikipedia.org/wiki/We%27re_the_Millers"];
  List<String> details2_comedy = ["Director: Todd Phillips\n\n"+
      "Actors: \n\tBradley Cooper\n\tEd Helms\n\tZach Galifianakis\n\tHeather Graham\n\tJustin Bartha\n\tJeffrey Tambor\n\n" + ""
      "Duration: 1 hr 40 mins\n\nRatings: \n\tRotten Tomatoes: 4.7/5.0\n\tIMDb: 7.7/10.0",
  "Director: Peter Farrelly\n\n" +
      "Actors: \n\tViggo Mortensen\n\tMahershala Ali\n\tLinda Cardellini\n\n" +
      "Duration: 2 hrs 10 mins\n\nRatings: \n\tRotten Tomatoes: 4.9/5.0\n\tIMDb: 8.2/10.0",
  "Director: Rawson Marshall Thurber\n\n" +
      "Actors: \n\tJennifer Aniston\n\tJason Sudeikis\n\tEmma Roberts\n\tNick Offerman\n\tKathryn Hahn\n\tEd Helms\n\n" +
      "Duration: 1 hr 50 mins\n\nRatings: \n\tRotten Tomatoes: 4.6/5.0\n\tIMDb: 7.0/10.0"];

  List<String> titles_romance =["Upgraded", "Players", "Anyone But You"];
  List<String> details_romance = ["Director: Carlson Young, Year: 2024", "Director: Trish Sie, Year: 2024", "Director: Will Gluck, Year: 2023"];
  List<String> imgs_romance = ["upgraded.jpeg", "players.jpeg", "anyone_but_you.jpeg"];
  List<String> link_romance = ["https://www.imdb.com/title/tt21830902/", "https://www.imdb.com/title/tt14833464/", "https://www.imdb.com/title/tt26047818/"];
  List<String> link2_romance = ["https://en.wikipedia.org/wiki/Upgraded_(film)", "https://en.wikipedia.org/wiki/Players_(2024_film)", "https://en.wikipedia.org/wiki/Anyone_but_You"];
  List<String> details2_romance = ["Director: Carlson Yound\n\n" +
      "Actors: \n\tCamila Mendes\n\tArchie Renaux\n\tThomas Kretschmann\n\tGrégory Montel\n\tLena Olin\n\tMarisa Tomei\n\n" +
      "Duration: 1 hr 44 mins\n\nRatings: \n\tRotten Tomatoes: 3.9/5.0\n\tIMDb: 6.1/10.0",
  "Director: Trish Sie\n\n" +
      "Actors: \n\tGina Rodriguez\n\tDamon Wayans Jr.\n\tJoel Courtney\n\tAugustus Prew\n\tLiza Koshy\n\tEgo Nwodim\n\tMarin Hinkle\n\tTom Ellis\n\n" +
      "Duration: 1 hr 45 mins\n\nRatings: \n\tRotten Tomatoes: 3.1/5.0\n\tIMDb: 5.7/10.0",
  "Director: Will Gluck\n\n" +
      "Actors: \n\tSydney Sweeney\n\tGlen Powell\n\tAlexandra Shipp\n\tGaTa\n\tHadley Robinson\n\tMichelle Hurd\n\tDermot Mulroney\n\tDarren Barnet\n\tRachel Griffiths\n\n" +
      "Duration: 1 hr 43 mins\n\nRatings: \n\tRotten Tomatoes: 3.5/5.0\n\tIMDb: 6.2/10.0"];

  List<String> titles_horror =["Ready or Not", "The Menu", "The Voices"];
  List<String> details_horror = ["Director: Tyler Gillett, Year: 2019", "Director: Mark Mylod, Year: 2022", "Director: Marjane Satrapi, Year: 2015"];
  List<String> imgs_horror = ["ready_or_not.jpeg", "the_menu.jpeg", "the_voices.jpeg"];
  List<String> link_horror = ["https://www.imdb.com/title/tt7798634/", "https://www.imdb.com/title/tt9764362/", "https://www.imdb.com/title/tt1567437/"];
  List<String> link2_horror = ["https://en.wikipedia.org/wiki/Ready_or_Not_(2019_film)", "https://en.wikipedia.org/wiki/The_Menu_(2022_film)", "https://en.wikipedia.org/wiki/The_Voices"];
  List<String> details2_horror = ["Director: Tyler Gillett\n\n" +
      "Actors: 	\n\tSamara Weaving\n\tAdam Brody\n\tMark O'Brien\n\tElyse Levesque\n\tNicky Guadagni\n\tHenry Czerny\n\tAndie MacDowell\n\n" +
      "Duration: 1 hr 30 mins\n\nRatings: \n\tRotten Tomatoes: 4.3/5.0\n\tIMDb: 6.9/10.0",
  "Director: Mark Mylod\n\n" +
      "Actors: \n\tRalph Fiennes\n\tAnya Taylor-Joy\n\tNicholas Hoult\n\tHong Chau\n\tJanet McTeer\n\tJudith Light\n\tJohn Leguizamo\n\n" +
      "Duration: 1 hr 47 mins\n\nRatings: \n\tRotten Tomatoes: 3.5/5.0\n\tIMDb: 7.2/10.0",
  "Director: Marjane Satrapi\n\n" +
      "Actors: \n\tRyan Reynolds\n\tGemma Arterton\n\tAnna Kendrick\n\tJacki Weaver\n\n" +
      "Duration: 1 hr 44 mins\n\nRatings: \n\tRotten Tomatoes: 3.3/5.0\n\tIMDb: 6.5/10.0"];

  List<String> titles_thriller =["Leave the World Behind", "The BeeKeeper", "Out of Darkness"];
  List<String> details_thriller = ["Director: Sam Esmail, Year: 2023", "Director: David Ayer, Year: 2024", "Director: Andrew Cumming, Year: 2022"];
  List<String> imgs_thriller = ["leave_the_word_behind.jpeg", "the_beekeeper.jpeg", "out_of_darkness.jpeg"];
  List<String> link_thriller = ["https://www.imdb.com/title/tt12747748/", "https://www.imdb.com/title/tt15314262/", "https://www.imdb.com/title/tt7527682/"];
  List<String> link2_thriller = ["https://en.wikipedia.org/wiki/Leave_the_World_Behind_(film)", "https://en.wikipedia.org/wiki/The_Beekeeper_(2024_film)", "https://en.wikipedia.org/wiki/Out_of_Darkness_(2022_film)"];
  List<String> details2_thriller = ["Director: Sam Esmail\n\n" +
      "Actors: \n\tJulia Roberts\n\tMahershala Ali\n\tEthan Hawke\n\tMyha'la\n\tKevin Bacon\n\n" +
      "Duration: 2 hrs 20 mins\n\nRatings: \n\tRotten Tomatoes: 2.0/5.0\n\tIMDb: 6.5/10.0",
  "Director: David Ayer\n\n" +
      "Actors: \n\tJason Statham\n\tEmmy Raver-Lampman\n\tJosh Hutcherson\n\tBobby Naderi\n\tPhylicia Rashad\n\tJeremy Irons\n\n" +
      "Duration: 1 hr 45 mins\n\nRatings: \n\tRotten Tomatoes: 4.3/5.0\n\tIMDb: 6.4/10.0",
  "Director: Andrew Cumming\n\n" +
      "Actors: \n\tSafia Oakley-Green\n\tChuku Modu\n\tKit Young\n\n" +
      "Duration: 1 hr 27 mins\n\nRatings: \n\tRotten Tomatoes:2.9/5.0 \n\tIMDb: 5.6/10.0"];


  _showPopupMenu(Offset offset, String img, String title, String link, String link2, String details) async{
    final screenSize = MediaQuery.of(context).size;
    double left = offset.dx;
    double top = offset.dy;
    double right = screenSize.width - offset.dx;
    double bottom = screenSize.height - offset.dy;

    await showMenu(
        context: context,
        position: RelativeRect.fromLTRB(left, top, right, bottom), items: [
        PopupMenuItem(
              child: Container(
                child: TextButton(
                  onPressed: () {Navigator.push(context, MaterialPageRoute(builder: (context) => Details(details: details, title: title)));}, child: Text("Details", style: TextStyle(fontSize: 15),),)
              ),),
          PopupMenuItem(
              child: Container(
                child: TextButton(
                  onPressed: () {launchUrl(Uri.parse(link2));}, child: Text("Wiki", style: TextStyle(fontSize: 15),),)
              ),),
          PopupMenuItem(
              child: Container(
                child: TextButton(
                  onPressed: () {Navigator.push(context, MaterialPageRoute(builder: (context) => Picture(img: img, link: link, title: title)));}, child: Text("IMDb", style: TextStyle(fontSize: 15),),)
              )
          )]);
  }
  SliverList list({required List<String> titles, required List<String> details, required List<String> imgs, required List<String> details2, required List<String> link, required List<String> link2}){
    return SliverList(
        delegate: SliverChildBuilderDelegate(
          childCount: 1,
              (BuildContext context, int index){
            return Container(
                color: Colors.white,
                height: 200.0,
                margin: EdgeInsets.only(bottom: 10.0),
                child: ListView.builder(
                    scrollDirection: Axis.horizontal,
                    itemCount: 3,
                    itemBuilder: (BuildContext context, int index){
                      return Container(
                        height: 150,
                        width: 350,
                        margin: EdgeInsets.all(2.0),
                        child: Card(
                      child:
                        ListTile(
                          shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(25.0)
                          ),
                          onTap: (){
                            Navigator.push(context, MaterialPageRoute(builder: (context) => Picture(img: imgs[index], link: link[index], title: titles[index])));
                          },
                          onLongPress: (){
                            RenderObject? getBox = context.findRenderObject();
                              _showPopupMenu(Offset(50.0, 300.0), imgs[index], titles[index], link[index], link2[index], details2[index]);
                          },
                          leading: Container(
                            width: 50,
                            height: 200,
                            decoration: BoxDecoration(
                                image: DecorationImage(image: AssetImage("images/" + imgs[index]), fit: BoxFit.fill),
                                borderRadius: BorderRadius.circular(15.0)
                            ),),
                          title: Text(titles[index], style: TextStyle(fontSize: 25, fontWeight: FontWeight.bold),),
                          subtitle: Text(details[index], style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold)),
                          tileColor: index.isOdd ? Colors.amberAccent : Colors.purpleAccent,
                        ),
                      ));
                    })
            );
          },
        ));
  }
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body:
            CustomScrollView(
                slivers: <Widget>[
                  SliverAppBar(
                    centerTitle: true,
                  title: Text('MOVIES', style: TextStyle(fontSize: 30, fontWeight: FontWeight.bold, color: Colors.white)),
                  backgroundColor: Colors.purpleAccent,
                  shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(10)),
                  expandedHeight: 200.0,
                  pinned: true,
                  elevation: 0,
                  flexibleSpace: FlexibleSpaceBar(
                    background: Image(image: AssetImage("images/beam.jpg"), fit: BoxFit.fill,),
                  ),
                  ),
                  SliverPersistentHeader(pinned: true, delegate: _sliverscroll(genre: "Action")),
                  list(titles: titles_action, details: details_action, imgs: imgs_action, details2: details2_action, link: link_action, link2: link2_action),
                  SliverPersistentHeader(pinned: true, delegate: _sliverscroll(genre: "Comedy")),
                  list(titles: titles_comedy, details: details_comedy, imgs: imgs_comedy, details2: details2_comedy, link: link_comedy, link2: link2_comedy),
                  SliverPersistentHeader(pinned: true, delegate: _sliverscroll(genre: "Romance")),
                  list(titles: titles_romance, details: details_romance, imgs: imgs_romance, details2: details2_romance, link: link_romance, link2: link2_romance),
                  SliverPersistentHeader(pinned: true, delegate: _sliverscroll(genre: "Horror")),
                  list(titles: titles_horror, details: details_horror, imgs: imgs_horror, details2: details2_horror, link: link_horror, link2: link2_horror),
                  SliverPersistentHeader(pinned: true, delegate: _sliverscroll(genre: "Thriller")),
                  list(titles: titles_thriller, details: details_thriller, imgs: imgs_thriller, details2: details2_thriller, link: link_thriller, link2: link2_thriller)
    ],

      ),
        backgroundColor: Colors.purpleAccent
    );
  }
}

class _sliverscroll extends SliverPersistentHeaderDelegate{
  _sliverscroll({Key?key, required this.genre});

  final String genre;
  @override
  // TODO: implement maxExtent
  double get maxExtent => 100;

  @override
  // TODO: implement minExtent
  double get minExtent => 90;

  @override
  bool shouldRebuild(covariant SliverPersistentHeaderDelegate oldDelegate) {
    // TODO: implement shouldRebuild
    return oldDelegate.maxExtent != 100 || oldDelegate.minExtent != 50;
  }

  @override
  Widget build(BuildContext context, double shrinkOffset, bool overlapsContent) {
    // TODO: implement build
    return Card(
      // margin: EdgeInsets.all(10),
      color: Colors.pink,
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Padding(padding: EdgeInsets.only(left: 20),
            child: Text(genre, style: TextStyle(fontSize: 50, fontWeight: FontWeight.bold))),]),);
  }
}