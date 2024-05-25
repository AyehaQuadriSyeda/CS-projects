import 'package:flutter/material.dart';

class Details extends StatelessWidget {
  const Details({super.key, required this.details, required this.title});
  final String details;
  final String title;
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
                child: Text(details, style: TextStyle(fontSize: 25, fontWeight: FontWeight.bold),),
                  )
              ),
        backgroundColor: Colors.purpleAccent));
  }
}