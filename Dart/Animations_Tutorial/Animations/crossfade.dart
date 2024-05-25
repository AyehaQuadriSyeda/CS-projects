// Author: Ayesha Quadri Syeda
// Date: 4/22/2024

import 'package:flutter/material.dart';

class Cross_Fade extends StatefulWidget {
  @override
  _Cross_Fade createState() => _Cross_Fade();
}

class _Cross_Fade extends State<Cross_Fade>{
  bool selected = false;


  // Returns a layout for a tablet or when
  // phone is in landscape mode
  Widget _tabletLayoutBuilder() {

    return Row(
      children: [
        Flexible(
          flex: 1,
          child: Material(
              shadowColor: Colors.red,
              borderRadius: BorderRadius.all(Radius.circular(25)),
              color: Colors.redAccent,
              elevation: 20.0,
              child: Container(
                padding: EdgeInsets.all(15),
                  child: Column(
                children: [
                  Text("Cross Fade Animation:", style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                  SizedBox(
                    height: 50,
                  ),
                  Text("The Cross Fade Animation uses the Fade transistion to transistion between two widgets.\n\nThis animation was implemented IMPLICITLY",
                    style: TextStyle(color: Colors.white, fontSize: 15),)
                ],
              ))),
        ),

        Flexible(
            flex: 2,
            child: Material(
                color: Colors.red.shade300,
                borderRadius: BorderRadius.all(Radius.circular(25)),
                child: Center(
                    child: Column(
                        children: [
                          SizedBox(
                            height: 20,
                          ),
                          AnimatedCrossFade(
                            firstChild: Icon(Icons.star_border, size: 150, color: Colors.white),
                            secondChild: Icon(Icons.shield_moon, size: 150, color: Colors.white70),
                            crossFadeState: selected ? CrossFadeState.showFirst : CrossFadeState.showSecond,
                            duration: Duration(seconds: 1),
                          ),
                          Column(
                            children: [
                              IconButton(onPressed: (){
                                setState(() {
                                  selected = !selected;
                                });
                              }, icon: Icon(Icons.play_circle_fill, size: 70, color: Colors.cyan,),
                              ),
                              SizedBox(
                                height: 3,
                              ),
                              Text("PLAY", style: TextStyle(color: Colors.white, fontSize: 30, fontWeight: FontWeight.bold))]
                          )])))
        ),]
    );
  }

  // Here, a layout for a mobile phone can be chosen
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.cyan,
      appBar: AppBar(
        shape: const RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(50))),
        backgroundColor: Colors.red,
        centerTitle: true,
        title: Text("CROSS FADE ANIMATION", style: TextStyle(color: Colors.white, fontSize: 30, fontWeight: FontWeight.bold),),
      ),
      body: _tabletLayoutBuilder(),
    );
  }
}
