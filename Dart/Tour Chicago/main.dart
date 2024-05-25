import 'package:flutter/material.dart';
import 'OptionDetails.dart';

// Author: Ayesha Quadri Syeda
// NetID: asyed71
// Date: 3/18/2024
// Purpose: Create the base layer of the application

void main() {
  runApp(MaterialApp(title: 'In Class Routes', initialRoute: '/', routes: {
    '/': (context) => const HomeScreen(),
  }));
}

class HomeScreen extends StatelessWidget {
  const HomeScreen({super.key});

  // Returns a row widget with the given data appropriately placed in the right widgets and formatted.
  Widget row(BuildContext context, {required tag, required String name, required String img, required String img2, required String address, required String description, required String data}){
    return Row(
      children: <Widget>[
        Hero(
            tag: tag,
            child:
            ElevatedButton(
              style: ElevatedButton.styleFrom(shape:
              const CircleBorder()),
              onPressed: (){
                Navigator.push(context, MaterialPageRoute(builder: (context) => OptionDetails(tag: tag, name: name, img: img, img2: img2,address: address, description: description ,data: data)));},
              child: Container(
                height: 125,
                width: 125,
                foregroundDecoration: BoxDecoration(
                    shape: BoxShape.circle, color: Colors.redAccent,
                    image: DecorationImage(image: AssetImage(img), fit: BoxFit.fill),
                    border: Border.all(color: Colors.amber, width: 5),
                    boxShadow: const [BoxShadow(
                        color: Colors.amberAccent,
                        blurRadius: 5.0,
                        spreadRadius: 5.0
                    )]
                ),
              ),
            )
        ),
        Text(name.toUpperCase(), style: const TextStyle(fontSize: 35, color: Colors.white),)
      ],
    );
  }

  @override
  Widget build(BuildContext context) {

    return DefaultTabController(length: 3, child: Scaffold(
      backgroundColor: Colors.deepOrange,
        appBar: AppBar(
          toolbarHeight: 85.0,
          bottom: const TabBar(
            tabs: [
              Tab(child: Text("NEIGHBORHOODS", style: TextStyle(color: Colors.white, fontSize: 12, fontWeight: FontWeight.w900))),
              Tab(child: Text("EVENTS", style: TextStyle(color: Colors.white, fontSize: 15, fontWeight: FontWeight.w900))),
              Tab(child: Text("SPORTS", style: TextStyle(color: Colors.white, fontSize: 15, fontWeight: FontWeight.w900))),
            ],
          ),
          centerTitle: true,
          title: const Text("Welcome to Chicago", style: TextStyle(color: Colors.white, fontSize: 30, fontWeight: FontWeight.w900)),
          backgroundColor: Theme.of(context).colorScheme.inversePrimary,
          elevation: 10.0,
          shadowColor: Colors.amberAccent,
          shape: const RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(60))),
          flexibleSpace: Container(
            decoration: const ShapeDecoration(
              shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(60))),
              image: DecorationImage(
                  image: AssetImage('images/beam.jpg'),
                  fit: BoxFit.fill
              ),
            ),)
        ),
      body:
        TabBarView(children: [

          // Neighborhoods tab
          ListView(children: <Widget>[
              const Padding(padding: EdgeInsets.all(35.0)),

              // first option
              row(context, tag: "options1", name: "South Side", img: "images/south_side1.jpg", img2: "images/south_side2.jpg",
                  address: "Location: South Side Chicago, IL\n", description: "The South Side has a varied ethnic composition and a great variety of income levels and other demographic measures.",
                  data: "It is the largest of the three Sides of the city that radiate from downtown."),
              const Padding(padding: EdgeInsets.all(35.0)),

              // Second option
              row(context, tag: "options2", name: "China Town", img: "images/chinatown.png", img2: "images/chinatown2.jpg",
                  address: "Location: China Town Chicago, IL\n", description: "Chicago's own Chinatown features beautiful Chinese-style buildings, as well as exotic dining and shopping experiences that have made the neighborhood a popular destination for visitors and locals alike.",
                  data: "Over a third of Chicago's Chinese population resides in this ethnic enclave."),
              const Padding(padding: EdgeInsets.all(35.0)),

              // Third option
              row(context, tag: "options3", name: "West Loop", img: "images/westloop.jpg", img2: "images/westloop2.jpg",
                  address: "Location: West Loop Chicago, IL\n", description: "The West Loop includes a portion of the core office market area as well as residential buildings and supporting retail uses",
                  data: "It is home to some of the top restaurants in the city, and the nation.")
          ]),

          // Events tab
          ListView(children: <Widget>[
            const Padding(padding: EdgeInsets.all(35.0)),

            // first option
            row(context, tag: "options4", name: "Sueños \nMusic \nFestival", img: "images/concert.jpg",
                img2: "images/suenos_people.jpg",
                data: "Sueños was started in 2022 by the producers of the Baja Beach Fest in collaboration with C3 Presents, the production team of Lollapalooza, and Reventon, a local entertainment company",
                description: "Sueños takes pride in bringing Reggaeton & Latin Artists from all across the globe to Grant Park, Chicago to unapologetically celebrate la cultura Latina!", address: "Location: Grant Park Chicago, IL\nDate: 25 May 2024\n"),
            const Padding(padding: EdgeInsets.all(35.0)),

            // Second option
            row(context, tag: "options5", name: "Little Big", img: "images/littlebig_concert.jpg",
                img2: "images/littlebig_zoom.jpg", address: "Location: 2047 N Milwaukee Ave, Chicago, IL 60647\nDate: 31 May 2024",
                data: "Their first full-length album, With Russia from Love, was released on 17 March 2014.",
                description: "Little Big is a Russian rave band founded in Saint Petersburg in 2013. The band currently consists of Ilya 'Ilich' Prusikin and Sonya Tayurskaya"),
            const Padding(padding: EdgeInsets.all(35.0)),

            // Third option
            row(context, tag: "options6", name: "Gunna", img: "images/gunna_concert.jpg",
                img2: "images/gunna.jpg", address: "Location: 1106 W Lawrence Ave, Chicago, IL 60640\n\nDate: 8 May 2024",
                data: "Rapper Gunna, who was released from Fulton County Jail in 2022 after serving seven months, released a new single, 'Bittersweet' last week.",
                description: "The Bittersweet Tour will feature Flo Milli as an opening act. The tour opens in Columbus, Ohio, in May and ends with an Atlanta stop at State Farm Arena on June 11"),
          ],),

          // Sports tab
          ListView(children: <Widget>[
            const Padding(padding: EdgeInsets.all(35.0)),

            // first option
            row(context, tag: "options7", name: "Bulls", img: "images/bull1.png", img2: "images/bull2.jpg",
                address: "Location: 1901 W Madison St, Chicago, IL 60612\n",
                description: "The Chicago Bulls are an American professional basketball team based in Chicago. ",
                data: "The team owner Richard Klein was brainstorming nicknames for his new franchise in 1966 and wanted a name that portrayed Chicago's status as the meat capital of the world then settled on Chicago Bulls."),
            const Padding(padding: EdgeInsets.all(35.0)),

            // Second option
            row(context, tag: "options8", name: "White Sox", img: "images/sox1.png", img2: "images/sox2.jpg",
                address: "Location: 333 W 35th St, Chicago, IL 60616\n", description: "The Chicago White Sox are an American professional baseball team based in Chicago.",
                data: "The White Sox have won the World Series three times in their history"),
            const Padding(padding: EdgeInsets.all(35.0)),

            // Third option
            row(context, tag: "options9", name: "Fire", img: "images/fire1.png", img2: "images/fire2.jpg",
                address: "Location: 1 North Dearborn St. Suite 1300 Chicago, IL 60602\n",
                description: "Chicago Fire Football Club is an American professional soccer club based in Chicago, Illinois, United States.",
                data: "Chicago Fire FC, founded in 1997, won the MLS Cup in their inaugural season and boasts a passionate fanbase known as 'Section 8 Chicago'.")
          ])
        ])
       )
    );
  }
}
