import 'package:flutter/material.dart';
import 'package:url_launcher/url_launcher.dart';

class Picture extends StatelessWidget {
  const Picture({super.key, required this.img, required this.title, required this.link});
  final String img;
  final String title;
  final String link;
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        home: Scaffold(
            appBar: AppBar(
              backgroundColor: Colors.amberAccent,
              leading: BackButton(
                onPressed: (){
                  Navigator.pop(context);
                },
              ),
              title: Text(title),
              centerTitle: true,
            ),
          body:
              Center(
                child:
                Container(
                  height: 600,
                  width: 350,
                  child: FloatingActionButton(onPressed: () {
                    launchUrl(Uri.parse(link));
                  },
                    child: Container(
                        height: 600,
                        width: 350,
                        margin: EdgeInsets.all(2.0),
                        decoration: BoxDecoration(
                        image: DecorationImage(image: AssetImage("images/"+img), fit: BoxFit.fill),
                        borderRadius: BorderRadius.circular(25.0)
                        ),
                    // child: Image(image: AssetImage("images/"+img), fit: BoxFit.fill)
                    )
                  )
                ),
        ),
            backgroundColor: Colors.purpleAccent
        )
    );
  }
}