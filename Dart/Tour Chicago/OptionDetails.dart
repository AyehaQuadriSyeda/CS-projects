import 'package:flutter/material.dart';

// Author: Ayesha Quadri Syeda
// NetID: asyed71
// Date: 3/18/2024
// Purpose: Creates and Updates the different states across the application

class OptionDetails extends StatefulWidget{
  const OptionDetails({super.key, required this.name, required this.img, required this.img2, required this.address, required this.data, required this.description, required this.tag});
  final String name;
  final String img2;
  final String img;
  final String address;
  final String data;
  final String description;
  final String tag;

  @override
  State<OptionDetails> createState() => _OptionDetails(image: img, info: description);

}

class _OptionDetails extends State<OptionDetails>{
  _OptionDetails({Key? key, required this.image, required this.info});
  String image;
  String info;
  Icon icon = const Icon(Icons.info, size: 60);

  int _counter = 1;
  @override
  Widget build(BuildContext context){

    void changescreen(){
      setState(() {
        _counter++;

        image = ((_counter%2 == 0) ? widget.img2 : widget.img);
        info = ((_counter%2 == 0) ? widget.data : widget.description);
        icon = ((_counter%2 == 0) ? const Icon(Icons.arrow_back, size:60) : const Icon(Icons.info, size: 60));
      });
    }

    // Options Details Screen
    return Scaffold(
      backgroundColor: Colors.deepOrangeAccent,
      appBar: AppBar(
          toolbarHeight: 85.0,
          centerTitle: true,
          title: Text(widget.name, style: const TextStyle(color: Colors.white, fontSize: 25, fontWeight: FontWeight.w900), textAlign: TextAlign.center,),
          backgroundColor: Theme.of(context).colorScheme.inversePrimary,
          elevation: 10.0,
          shadowColor: Colors.amberAccent,
          shape: const RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(60))),
          flexibleSpace: Container(
            decoration: const ShapeDecoration(
              shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(60))),
              image: DecorationImage(
                  image: AssetImage('images/beam.jpg'),
                  fit: BoxFit.fill
              ),
            ),
          )
      ),
      body:
      Center(
          child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
                Hero(
                    tag: widget.tag,
                    child:
                    ElevatedButton(
                      style: ElevatedButton.styleFrom(shape:
                      const CircleBorder()),
                      onPressed: (){},
                      // shape: const CircleBorder(),
                      child: Container(
                        height: 300,
                        width: 300,
                        foregroundDecoration: BoxDecoration(
                            shape: BoxShape.circle, color: Colors.redAccent,
                            image: DecorationImage(image: AssetImage(image), fit: BoxFit.fill),
                            border: Border.all(color: Colors.amber, width: 5),
                            boxShadow: const [BoxShadow(
                                color: Colors.amberAccent,
                                blurRadius: 5.0,
                                spreadRadius: 5.0
                            )]
                        ),
                      ),
                    )
                ),
                Padding(padding: const EdgeInsets.all(10.0),
                    child: Text(widget.name, style: const TextStyle(fontSize: 38, fontWeight: FontWeight.w500, color: Colors.white), textAlign: TextAlign.center,)),
                Padding(padding: const EdgeInsets.all(10.0),
                    child: Text(info,
                      style: const TextStyle(fontSize: 20, fontWeight: FontWeight.w500, color: Colors.white), textAlign: TextAlign.center,)),
                Padding(padding: const EdgeInsets.all(10.0),
                    child: Text(widget.address,
                      style: const TextStyle(fontSize: 20, fontWeight: FontWeight.w500, color: Colors.white), textAlign: TextAlign.center,))

              ]
          )
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: changescreen,
        shape: const CircleBorder(),
        backgroundColor: Colors.deepOrangeAccent,
        child: icon,
      ),
    );

  }

}

