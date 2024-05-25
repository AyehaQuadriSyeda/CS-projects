// Author: Ayesha Quadri Syeda
// Date: 4/22/2024

import 'package:flutter/material.dart';
import 'package:ui_fragmets_works/Animations/crossfade.dart';
import 'package:ui_fragmets_works/Animations/default_text.dart';
import 'package:ui_fragmets_works/Animations/opacity.dart';
import 'package:ui_fragmets_works/Animations/padding.dart';
import 'package:ui_fragmets_works/Animations/scale.dart';
import 'package:ui_fragmets_works/Animations/size.dart';
import 'package:ui_fragmets_works/Animations/slide.dart';
import '/Animations/rotation.dart';

class Menu extends StatelessWidget {
  const Menu({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    List<Color> choose_color = [Colors.red.shade200, Colors.red.shade300, Colors.red.shade400,
    Colors.red.shade500, Colors.red.shade600, Colors.red.shade700, Colors.red.shade800, Colors.red.shade900];

    return Scaffold(
      backgroundColor: Colors.cyan,
      appBar: AppBar(
        backgroundColor: Colors.cyan,
          centerTitle: true,
          title: const Text('Menu', style: TextStyle(fontSize: 30, fontWeight: FontWeight.bold, color: Colors.white),)),
      body: Center (
        child: Container(
              // margin: EdgeInsets.only(left: 35, right: 35, bottom: 20.0),
              // width: 400,
              child: ListView(
              children: [
                // first button
              Container(
                height: 70,
                width: 400,
                decoration: BoxDecoration(
                  boxShadow: [BoxShadow(
                    color: Colors.pinkAccent,
                    spreadRadius: 3,
                    blurRadius: 4
                  )],
                  border: Border.all(
                    color: Colors.pinkAccent,
                    width: 10
                  ),
                  borderRadius: BorderRadius.circular(35),
                  color: choose_color[0],
                ),
                  margin: EdgeInsets.only(left: 100, right: 100, bottom: 20.0),
              child:
               OutlinedButton(
                style: OutlinedButton.styleFrom(
                  maximumSize: Size(100, 70),
                  side: BorderSide(
                    color: Colors.pinkAccent
                  )
                ),
                child: const Text('CROSS FADE', style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                onPressed: () {
               Navigator.of(context).push(
                   PageRouteBuilder(
                   pageBuilder: (context, animation, anotherAnimation) {
                     return Cross_Fade();
                   },
                   barrierColor: Colors.blue,
                   transitionDuration: Duration(seconds: 1),
                   transitionsBuilder:
                       (context, animation, anotherAnimation, child) {
                     animation =
                         CurvedAnimation(curve: Curves.decelerate, parent: animation);
                     return RotationTransition(turns: animation, child: child,);
                   })
               );
               },
                )),

                // Second button
                Container(
                    height: 70,
                    width: 400,
                    decoration: BoxDecoration(
                      boxShadow: [BoxShadow(
                          color: Colors.pinkAccent,
                          spreadRadius: 3,
                          blurRadius: 4
                      )],
                      border: Border.all(
                          color: Colors.pinkAccent,
                          width: 10
                      ),
                      borderRadius: BorderRadius.circular(35),
                      color: choose_color[1],
                    ),
                    margin: EdgeInsets.only(left: 100, right: 100, bottom: 20.0),
                    child:
                    OutlinedButton(
                      style: OutlinedButton.styleFrom(
                          maximumSize: Size(100, 70),
                          side: BorderSide(
                              color: Colors.pinkAccent
                          )
                      ),
                      child: const Text('SIZE ANIMATION', style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                      onPressed: () {
                        Navigator.of(context).push(
                            PageRouteBuilder(
                                pageBuilder: (context, animation, anotherAnimation) {
                                  return SizeAnimation();
                                },
                                barrierColor: Colors.blue,
                                transitionDuration: Duration(seconds: 2),
                                transitionsBuilder:
                                    (context, animation, anotherAnimation, child) {
                                  animation =
                                      CurvedAnimation(curve: Curves.bounceInOut, parent: animation);
                                  return RotationTransition(turns: animation, child: child,);
                                })
                        );
                      },
                    )),

                //third button
                Container(
                    height: 70,
                    width: 400,
                    decoration: BoxDecoration(
                      boxShadow: [BoxShadow(
                          color: Colors.pinkAccent,
                          spreadRadius: 3,
                          blurRadius: 4
                      )],
                      border: Border.all(
                          color: Colors.pinkAccent,
                          width: 10
                      ),
                      borderRadius: BorderRadius.circular(35),
                      color: choose_color[2],
                    ),
                    margin: EdgeInsets.only(left: 100, right: 100, bottom: 20.0),
                    child:
                    OutlinedButton(
                      style: OutlinedButton.styleFrom(
                          maximumSize: Size(100, 70),
                          side: BorderSide(
                              color: Colors.pinkAccent
                          )
                      ),
                      child: const Text('OPACITY ANIMATION', style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                      onPressed: () {
                        Navigator.of(context).push(
                            PageRouteBuilder(
                                pageBuilder: (context, animation, anotherAnimation) {
                                  return Opacity_Animation();
                                },
                                barrierColor: Colors.blue,
                                transitionDuration: Duration(seconds: 5),
                                transitionsBuilder:
                                    (context, animation, anotherAnimation, child) {
                                  animation =
                                      CurvedAnimation(curve: Curves.decelerate, parent: animation);
                                  return ScaleTransition(scale: animation,
                                      child: child);
                                })
                        );
                      },
                    )),

                //fourth button
                Container(
                    height: 70,
                    width: 400,
                    decoration: BoxDecoration(
                      boxShadow: [BoxShadow(
                          color: Colors.pinkAccent,
                          spreadRadius: 3,
                          blurRadius: 4
                      )],
                      border: Border.all(
                          color: Colors.pinkAccent,
                          width: 10
                      ),
                      borderRadius: BorderRadius.circular(35),
                      color: choose_color[3],
                    ),
                    margin: EdgeInsets.only(left: 100, right: 100, bottom: 20.0),
                    child:
                    OutlinedButton(
                      style: OutlinedButton.styleFrom(
                          maximumSize: Size(100, 70),
                          side: BorderSide(
                              color: Colors.pinkAccent
                          )
                      ),
                      child: const Text('SLIDE', style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                      onPressed: () {
                        Navigator.of(context).push(
                            PageRouteBuilder(
                                pageBuilder: (context, animation, anotherAnimation) {
                                  return Slide();
                                },
                                barrierColor: Colors.blue,
                                transitionDuration: Duration(seconds: 5),
                                transitionsBuilder:
                                    (context, animation, anotherAnimation, child) {
                                  animation =
                                      CurvedAnimation(curve: Curves.bounceOut, parent: animation);
                                  return ScaleTransition(scale: animation,
                                      child: child);
                                })
                        );
                      },
                    )),

                //fifth button
                Container(
                    height: 70,
                    width: 400,
                    decoration: BoxDecoration(
                      boxShadow: [BoxShadow(
                          color: Colors.pinkAccent,
                          spreadRadius: 3,
                          blurRadius: 4
                      )],
                      border: Border.all(
                          color: Colors.pinkAccent,
                          width: 10
                      ),
                      borderRadius: BorderRadius.circular(35),
                      color: choose_color[4],
                    ),
                    margin: EdgeInsets.only(left: 100, right: 100, bottom: 20.0),
                    child:
                    OutlinedButton(
                      style: OutlinedButton.styleFrom(
                          maximumSize: Size(100, 70),
                          side: BorderSide(
                              color: Colors.pinkAccent
                          )
                      ),
                      child: const Text('SCALE TRANSITION', style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                      onPressed: () {
                        Navigator.of(context).push(
                            PageRouteBuilder(
                                pageBuilder: (context, animation, anotherAnimation) {
                                  return Scale();
                                },
                                barrierColor: Colors.blue,
                                transitionDuration: Duration(seconds: 5),
                                transitionsBuilder:
                                    (context, animation, anotherAnimation, child) {
                                  animation =
                                      CurvedAnimation(curve: Curves.bounceOut, parent: animation);
                                  return FadeTransition(opacity: animation, child: child,);
                                })
                        );
                      },
                    )),

                //sixth button
                Container(
                    height: 70,
                    width: 400,
                    decoration: BoxDecoration(
                      boxShadow: [BoxShadow(
                          color: Colors.pinkAccent,
                          spreadRadius: 3,
                          blurRadius: 4
                      )],
                      border: Border.all(
                          color: Colors.pinkAccent,
                          width: 10
                      ),
                      borderRadius: BorderRadius.circular(35),
                      color: choose_color[5],
                    ),
                    margin: EdgeInsets.only(left: 100, right: 100, bottom: 20.0),
                    child:
                    OutlinedButton(
                      style: OutlinedButton.styleFrom(
                          maximumSize: Size(100, 70),
                          side: BorderSide(
                              color: Colors.pinkAccent
                          )
                      ),
                      child: const Text('DEFAULT TEXT STYLE ANIMATION', style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                      onPressed: () {
                        Navigator.of(context).push(
                            PageRouteBuilder(
                                pageBuilder: (context, animation, anotherAnimation) {
                                  return Default_text();
                                },
                                barrierColor: Colors.blue,
                                transitionDuration: Duration(seconds: 5),
                                transitionsBuilder:
                                    (context, animation, anotherAnimation, child) {
                                  animation =
                                      CurvedAnimation(curve: Curves.ease, parent: animation);
                                  return FadeTransition(opacity: animation, child: child,);
                                })
                        );
                      },
                    )),

                //seventh button
                Container(
                    height: 70,
                    width: 400,
                    decoration: BoxDecoration(
                      boxShadow: [BoxShadow(
                          color: Colors.pinkAccent,
                          spreadRadius: 3,
                          blurRadius: 4
                      )],
                      border: Border.all(
                          color: Colors.pinkAccent,
                          width: 10
                      ),
                      borderRadius: BorderRadius.circular(35),
                      color: choose_color[6],
                    ),
                    margin: EdgeInsets.only(left: 100, right: 100, bottom: 20.0),
                    child:
                    OutlinedButton(
                      style: OutlinedButton.styleFrom(
                          maximumSize: Size(100, 70),
                          side: BorderSide(
                              color: Colors.pinkAccent
                          )
                      ),
                      child: const Text('PADDING ANIMATION', style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                      onPressed: () {
                        Navigator.of(context).push(
                            PageRouteBuilder(
                                pageBuilder: (context, animation, anotherAnimation) {
                                  return Padding_animation();
                                },
                                barrierColor: Colors.blue,
                                transitionDuration: Duration(seconds: 5),
                                transitionsBuilder:
                                    (context, animation, anotherAnimation, child) {
                                  animation =
                                      CurvedAnimation(curve: Curves.bounceOut, parent: animation);
                                  return SlideTransition(
                                        position:
                                        Tween(begin: Offset(0.0, 1.0), end: Offset(0.0, 0.0)).animate(animation),
                                        child: child,
                                      );
                                })
                        );
                      },
                    )),

                //eighth button
                Container(
                    height: 70,
                    width: 400,
                    decoration: BoxDecoration(
                      boxShadow: [BoxShadow(
                          color: Colors.pinkAccent,
                          spreadRadius: 3,
                          blurRadius: 4
                      )],
                      border: Border.all(
                          color: Colors.pinkAccent,
                          width: 10
                      ),
                      borderRadius: BorderRadius.circular(35),
                      color: choose_color[7],
                    ),
                    margin: EdgeInsets.only(left: 100, right: 100, bottom: 20.0),
                    child:
                    OutlinedButton(
                      style: OutlinedButton.styleFrom(
                          maximumSize: Size(100, 70),
                          side: BorderSide(
                              color: Colors.pinkAccent
                          )
                      ),
                      child: const Text('ROTATION TRANSITION', style: TextStyle(color: Colors.white, fontSize: 20, fontWeight: FontWeight.bold),),
                      onPressed: () {
                        Navigator.of(context).push(
                            PageRouteBuilder(
                                pageBuilder: (context, animation, anotherAnimation) {
                                  return Rotation();
                                },
                                barrierColor: Colors.blue,
                                transitionDuration: Duration(seconds: 5),
                                transitionsBuilder:
                                    (context, animation, anotherAnimation, child) {
                                  animation =
                                      CurvedAnimation(curve: Curves.decelerate, parent: animation);
                                  return SlideTransition(
                                    position:
                                    Tween(begin: Offset(0.0, 1.0), end: Offset(0.0, 0.0)).animate(animation),
                                    child: child,
                                  );
                                })
                        );
                      },
                    ))
              ]))));
  }
}
