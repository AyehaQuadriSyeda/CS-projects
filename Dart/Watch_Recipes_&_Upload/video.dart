import 'package:flutter/material.dart';
import 'main.dart';
import 'package:youtube_player_flutter/youtube_player_flutter.dart';

// Author: Ayesha Quadri Syeda
// NetID: asyed71
// Date: 4/28/2024
// Purpose: This file creates the pages for the recipe videos

class Video extends StatefulWidget {
  Video({super.key, required this.name, required this.link});
  String name;
  String link;
  @override
  createState() => _Video(name1: name, link1: link);
}

class _Video extends State<Video> {
  _Video({Key? key, required this.name1, required this.link1});

  String name1;
  String link1;

  late YoutubePlayerController _controller;

  @override
  void initState() {
    super.initState();
    String? url;
    url = YoutubePlayer.convertUrlToId(link1);
    _controller = YoutubePlayerController(initialVideoId: url!,
    flags: YoutubePlayerFlags(
      autoPlay: false,
      loop: true
    ));
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Video Demo',
      home: YoutubePlayerBuilder(
        player: YoutubePlayer(
          controller: _controller,
          showVideoProgressIndicator: true,
        ),
        builder: (context, player) =>
            Scaffold(
              backgroundColor: Colors.black,
              appBar: AppBar(
                leading: BackButton(
                  onPressed: (){
                    Navigator.pop(context);
                    // Navigator.push(context, MaterialPageRoute(builder: (context) => HomeScreen()));
                  },
                  color: Colors.white,
                ),
              toolbarHeight: 85.0,
              centerTitle: true,
              title: Text(name1.toUpperCase(), style: TextStyle(color: Colors.white, fontSize: 25, fontWeight: FontWeight.w900)),
              backgroundColor: Colors.black,
              elevation: 10.0,
              shadowColor: Colors.amberAccent,
              shape: const RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(60))),
              flexibleSpace: Container(
                decoration: const ShapeDecoration(
                  shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(60))),
                ),
              ),
              ),
              body: Center(
                child: Column(
                    children: [
                      SizedBox(
                        height: 150,
                      ),
                      Container(child: player,
                      decoration: BoxDecoration(
                        borderRadius: BorderRadius.circular(25),
                        border: Border.all(
                          color: Colors.yellow.shade700,
                          width: 20
                        )
                      ),),
                      SizedBox(
                        height: 30,
                      ),
                      IconButton(onPressed: (){
                        setState(() {
                          _controller.value.isPlaying ? _controller.pause() : _controller.play();
                        });
                        },
                          icon:
                          Icon(_controller.value.isPlaying ? Icons.pause: Icons.play_arrow, size: 80, color: Colors.yellow.shade800)),
                      SizedBox(
                        height: 30,
                      ),
                      Card(
                        color: Colors.yellow.shade800,
                        child:
                          ListTile(
                            leading: Icon(Icons.info, size: 50, color: Colors.white,),
                            title: Text("To PLAY the video press the play/pause icon.\n\n To PAUSE the video press on the play/pause icon again.",
                            style: TextStyle(color: Colors.white, fontSize: 18))
                          )
                      )
                    ])
              ),
            )),
    );
  }

  // @override
  // void dispose() {
  //   _controller.dispose();
  //   super.dispose();
  // }
}