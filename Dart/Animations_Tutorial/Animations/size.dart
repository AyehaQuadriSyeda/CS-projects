// Author: Ayesha Quadri Syeda
// Date: 4/22/2024
import 'package:flutter/material.dart';

/*
 * Class needs to be stateful because there will need to be constant
 * updates in title and quote widgets
 */

class SizeAnimation extends StatefulWidget {
  @override
  _SizeAnimation createState() => _SizeAnimation();
}

/*
 * Extend the class WidgetLayoutController
 */
class _SizeAnimation extends State<SizeAnimation>{
  bool selected = false;
  double _size = 100;

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
                        Text("Size Animation:", style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                        SizedBox(
                          height: 50,
                        ),
                        Text("The Size Animation transistions between two sizes for the same widget.\n\nThis animation was implemented IMPLICITLY",
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
                            AnimatedSize(
                              child: Icon(Icons.star_border, size: _size, color: Colors.white),
                              duration: Duration(seconds: 5),
                            ),
                            Column(
                                children: [
                                  IconButton(onPressed: (){
                                    setState(() {
                                      _size = selected ? 100 : 150;
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
        title: Text("SIZE ANIMATION", style: TextStyle(color: Colors.white, fontSize: 30, fontWeight: FontWeight.bold),),
      ),
      body: _tabletLayoutBuilder(),
    );
  }
}
