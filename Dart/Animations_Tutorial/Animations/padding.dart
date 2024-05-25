// Author: Ayesha Quadri Syeda
// Date: 4/22/2024
import 'dart:ui';

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter/painting.dart';
import 'package:flutter/widgets.dart';

/*
 * Class needs to be stateful because there will need to be constant
 * updates in title and quote widgets
 */

class Padding_animation extends StatefulWidget {
  @override
  _Padding_animation createState() => _Padding_animation();
}

/*
 * Extend the class WidgetLayoutController
 */
class _Padding_animation extends State<Padding_animation>{
  bool selected = false;
  double fsize = 10;


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
                        Text("Padding Animation:", style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                        SizedBox(
                          height: 50,
                        ),
                        Text("The Padding Animation transistions between different padding parameters.\n\nThis animation was implemented IMPLICITLY",
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
                            AnimatedPadding(
                              duration: Duration(seconds: 1),
                              padding: EdgeInsets.all(fsize),
                              child: Container(
                                color: Colors.cyan,
                                child: Icon(Icons.add, size: 50)
                              ),
                            ),
                            Column(
                                children: [
                                  IconButton(onPressed: (){
                                    setState(() {
                                      fsize = selected ? 10 : 50;
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
        title: Text("PADDING ANIMATION", style: TextStyle(color: Colors.white, fontSize: 30, fontWeight: FontWeight.bold),),
      ),
      body: _tabletLayoutBuilder(),
    );
  }
}
