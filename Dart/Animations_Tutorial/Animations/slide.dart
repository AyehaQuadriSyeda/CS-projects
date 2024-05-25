// Author: Ayesha Quadri Syeda
// Date: 4/22/2024

import 'package:flutter/animation.dart';
import 'package:flutter/material.dart';

/*
 * Class needs to be stateful because there will need to be constant
 * updates in title and quote widgets
 */

class Slide extends StatefulWidget {
  @override
  _Slide createState() => _Slide();
}

/*
 * Extend the class WidgetLayoutController
 */
class _Slide extends State<Slide> with TickerProviderStateMixin{
  IconData pause = Icons.pause_circle_filled;
  IconData mid = Icons.swipe_down_alt;
  bool selected = false;

  void changeicon(){
    setState(() {
      pause = selected ? Icons.play_circle_filled : Icons.pause_circle_filled;
      if(selected){
        _controller.reset();
      }
      else{
        _controller.repeat();
      }
      selected = !selected;
    });
  }

  void changedirection(){
    setState(() {
      mid = selected ? Icons.swipe_down_alt : Icons.swipe_up_alt;
      turn_tween = selected ? turn_tween1 : turn_tween_reverse;
      selected = !selected;
    });
  }
  late final AnimationController _controller = AnimationController(
      vsync: this,
      duration: Duration(seconds: 3))..repeat();
  late final Animation<double> _animation = CurvedAnimation(parent: _controller, curve: Curves.fastOutSlowIn);

  late Animation<Offset> turn_tween_reverse = Tween<Offset> (
      begin: Offset(0.0, 2.0),
      end: Offset(0.0, 0.0)
  ).animate(_animation);

  late Animation<Offset> turn_tween1 = Tween<Offset> (
      begin: Offset(0.0, 0.0),
      end: Offset(0.0, 2.0)
  ).animate(_animation);

  late Animation<Offset> turn_tween = Tween<Offset> (
      begin: Offset(0.0, 0.0),
      end: Offset(0.0, 2.0)
  ).animate(_animation);

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
                      Text("Slide Animation:", style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                      SizedBox(
                        height: 50,
                      ),
                      Text("The Slide Animation slides the child widget from begin offset to end offset.\n\nThis explicitly created to slide left to right infinetly.",
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
                          SlideTransition(
                          position: turn_tween,
                          child: Icon(mid, size: 150, color: Colors.cyan)),
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
        title: Text("SLIDE ANIMATION", style: TextStyle(color: Colors.white, fontSize: 30, fontWeight: FontWeight.bold),),
      ),
      body: _tabletLayoutBuilder(),
    );
  }
}
