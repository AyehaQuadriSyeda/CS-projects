// Author: Ayesha Quadri Syeda
// Date: 4/22/2024
import 'dart:ui';

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter/painting.dart';

/*
 * Class needs to be stateful because there will need to be constant
 * updates in title and quote widgets
 */

class Default_text extends StatefulWidget {
  @override
  _Default_text createState() => _Default_text();
}

/*
 * Extend the class WidgetLayoutController
 */
class _Default_text extends State<Default_text>{
  bool selected = false;
  double fsize = 70;
  Color _color = Colors.red.shade500;
  FontWeight b = FontWeight.bold;


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
                        Text("Default Text Style Animation:", style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                        SizedBox(
                          height: 50,
                        ),
                        Text("The Default Text Style Animation transistions between TextStyle parameters.\n\nThis animation was implemented IMPLICITLY",
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
                            AnimatedDefaultTextStyle(
                              
                              duration: Duration(seconds: 1), style: TextStyle(fontSize: fsize, color: _color, fontWeight: b),
                              child: Text("DEMO"),
                            ),
                            Column(
                                children: [
                                  IconButton(onPressed: (){
                                    setState(() {
                                      b = selected ? FontWeight.bold : FontWeight.w100;
                                      fsize = selected ? 80 : 50;
                                      _color = selected ? Colors.red.shade500 : Colors.red.shade900;
                                      selected = !selected;
                                    });
                                  }, icon: Icon(Icons.play_circle_fill, size: 70, color: Colors.cyan,),
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
        title: Text("DEFAULT TEXT STYLE ANIMATION", style: TextStyle(color: Colors.white, fontSize: 30, fontWeight: FontWeight.bold),),
      ),
      body: _tabletLayoutBuilder(),
    );
  }
}
