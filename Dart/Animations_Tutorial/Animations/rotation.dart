// Author: Ayesha Quadri Syeda
// Date: 4/22/2024

import 'package:flutter/material.dart';

/*
 * Class needs to be stateful because there will need to be constant
 * updates in title and quote widgets
 */

class Rotation extends StatefulWidget {
  @override
  _Rotation createState() => _Rotation();
}

/*
 * Extend the class WidgetLayoutController
 */
class _Rotation extends State<Rotation> with TickerProviderStateMixin{
  IconData pause = Icons.pause_circle_filled;
  bool selected = false;

  void changeicon(){
    setState(() {
      pause = selected ? Icons.play_circle_filled : Icons.pause_circle_filled;
      if(selected){
        _controller.reset();
      }
      else
        _controller.repeat();
      selected = !selected;
    });
  }

  void changedirection(){
    setState(() {
      turn_tween = selected ? turn_tween1 : turn_tween_reverse;
      selected = !selected;
    });
  }
  late final AnimationController _controller = AnimationController(
      vsync: this,
  duration: Duration(seconds: 5))..repeat(reverse: false);
  late final Animation<double> _animation = CurvedAnimation(parent: _controller, curve: Curves.bounceInOut);

  Tween<double> turn_tween_reverse = Tween<double>(
      begin: 1.0,
      end: 0.0
  );
  Tween<double> turn_tween1 = Tween<double> (
      begin: 0.0,
      end: 1.0
  );
  Tween<double> turn_tween = Tween<double> (
      begin: 0.0,
      end: 1.0
  );

  void dispose(){
    _controller.dispose();
    super.dispose();
  }

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
                  child:
                  Column(
                    children: [
                      Text("Rotation Transition:", style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                      SizedBox(
                        height: 50,
                      ),
                      Text("The Rotation Transition is an animation which rotates it's child Widget.\n\nThis explicitly created to turn clockwise infinetely.",
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
                      height: 50,
                    ),
                    RotationTransition(turns: turn_tween.animate(_animation),
                    child: Icon(Icons.sports_basketball, size: 150)
                ),
                  Row(
                    children: [
                      SizedBox(
                        width: 190,
                      ),
                      IconButton(onPressed: changeicon, icon: Icon(pause, size: 70),
                        color: Colors.cyan
                      ),
                      SizedBox(
                        width: 40,
                      ),
                      IconButton(onPressed: changedirection, icon: Icon(Icons.fast_rewind, size: 70),
                      color: Colors.cyan)
                    ],
                  )]
              ))
          )
        )
        // titleIndex is not valid, display a blank
      ],
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
        title: Text("ROTATION TRANSITION", style: TextStyle(color: Colors.white, fontSize: 30, fontWeight: FontWeight.bold),),
      ),
      body: _tabletLayoutBuilder(),
    );
  }
}
