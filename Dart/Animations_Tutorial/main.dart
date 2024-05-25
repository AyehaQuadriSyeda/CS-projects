// Author: Ayesha Quadri Syeda
// Date: 4/22/2024

import 'package:flutter/material.dart';
import 'menu.dart';

void main() {
  runApp(FlutterFragments());
}

class FlutterFragments extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: Menu(),
    );
  }
}


