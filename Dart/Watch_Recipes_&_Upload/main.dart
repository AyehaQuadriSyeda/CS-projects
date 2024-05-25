

import 'dart:io';

import 'package:flutter/material.dart';
import 'package:image_gallery_saver/image_gallery_saver.dart';
import 'package:image_picker/image_picker.dart';
import 'video.dart';


// Author: Ayesha Quadri Syeda
// NetID: asyed71
// Date: 4/28/2024

/*
* The Tabs on the Main screen are as follows:
* 1. RECIPES VIDEOS: Select different recipes and watch their recipe videos
* 2. CAMERA: Pick picture from the camera and either upload them to the application gallery or
* store them in the phone gallery.
* 3. UPLOADS: Pick pictures from the phone gallery to upload to the application.
* This tab displays the images in gridview.
* NOTE: In the phone gallery, initially there are no pictures,
* you have to take the picture in order to save it to the gallery.
* The pictures are saved in the 'Pictures' folder of the gallery
*
* I've used the following packages for my project:
*   image_picker: ^0.8.6
*   image_gallery_saver: ^2.0.3
*   youtube_player_flutter: ^9.0.1
*   flutter_inappwebview: ^6.0.0
*/

void main() {
  // runApp(Home());
  runApp(MaterialApp(title: 'In Class Routes', initialRoute: '/', routes: {
    '/': (context) => HomeScreen(),
  }));
}

// class Home extends StatelessWidget{
//   @override
//   Widget build(BuildContext context) {
//     return MaterialApp(
//       home: HomeScreen()
//     );
//   }
//
// }

class HomeScreen extends StatefulWidget {
  @override
  createState() => _HomeScreen();
}
class _HomeScreen extends State<HomeScreen>{

  // late GoogleMapController _controller;
  // final LatLng _uic_location = const LatLng(41.789722, -87.599724);

  XFile? _selectedimage;
  List<String> imagelist = [];
  List<String> recipe_names = ["Mac and Cheese", "Pizza", "Grilled Cheese"];
  List<String> vid_link = ["https://youtu.be/YxVZuuxxXxk?si=QlWXzH4PTKLaNVk4", "https://youtu.be/sv3TXMSv6Lw?si=kGHLu7acR0eKLvbS", "https://youtu.be/5iRnHiX6oTw?si=DEZjrYqo1G3QZz4i"];

  @override
  Widget build(BuildContext context) {
    return DefaultTabController(length: 3, child: Scaffold(
        backgroundColor: Colors.black,
        appBar: AppBar(
            toolbarHeight: 85.0,
            bottom: const TabBar(
              tabs: [
                Tab(child: Text("RECIPES VIDEOS", style: TextStyle(color: Colors.white, fontSize: 15, fontWeight: FontWeight.w900))),
                Tab(child: Text("CAMERA", style: TextStyle(color: Colors.white, fontSize: 15, fontWeight: FontWeight.w900))),
                Tab(child: Text("UPLOADS", style: TextStyle(color: Colors.white, fontSize: 15, fontWeight: FontWeight.w900))),
              ],
            ),
            centerTitle: true,
            title: const Text("Recipes Locations Uploads", style: TextStyle(color: Colors.white, fontSize: 25, fontWeight: FontWeight.w900)),
            backgroundColor: Colors.black,
            elevation: 10.0,
            shadowColor: Colors.amberAccent,
            shape: const RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(60))),
            flexibleSpace: Container(
              decoration: const ShapeDecoration(
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.all(Radius.circular(60))),
              ),)
        ),
        body:
        TabBarView(children: [
          // Recipes tab
          ListView.builder(
            itemCount: recipe_names.length,
            itemBuilder: (BuildContext context, int index){
              return Padding(padding: EdgeInsets.all(50),
              child: TextButton(onPressed: () async {
                await Navigator.push(context, MaterialPageRoute(builder: (context) => Video(name: recipe_names[index], link: vid_link[index],)));
              },
                  child: Text(recipe_names[index], style: TextStyle(fontSize: 30, color: Colors.white)),
                  style: TextButton.styleFrom(
                      minimumSize: Size(20.0, 15.0),
                      maximumSize: const Size(20.0, 60.0),
                      backgroundColor: Colors.yellow.shade800
                  ),));
            },),

          // Location tab
          Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              TextButton(onPressed: _pickImageFromCamera, child: Text("Camera", style: TextStyle(fontSize: 30, color: Colors.white)),
                style: TextButton.styleFrom(
                    backgroundColor: Colors.yellow.shade800
                ),),
              SizedBox(height: 20,),
              Row(
                children: [
                  SizedBox(
                    width: 25,
                  ),
                  TextButton(onPressed: (){
                    if(_selectedimage!= null){

                      ImageGallerySaver.saveFile(_selectedimage!.path);
                      final snackBar = SnackBar(content: Text("Saved to Gallery"));
                      ScaffoldMessenger.of(context).showSnackBar(snackBar);

                    }
                    setState(() {
                    });
                  }, child: Text("Save to Gallery", style: TextStyle(fontSize: 30, color: Colors.white)),
                    style: TextButton.styleFrom(
                        backgroundColor: Colors.yellow.shade800
                    ),),
                  SizedBox(
                    width: 15,
                  ),
                  TextButton(onPressed: (){
                    setState(() {
                      if(_selectedimage != null) {
                        imagelist.add(_selectedimage!.path);
                        final snackBar = SnackBar(content: Text("Uploaded"), );
                        ScaffoldMessenger.of(context).showSnackBar(snackBar);
                      }
                    });
                  }, child: Text("Upload", style: TextStyle(fontSize: 30, color: Colors.white)),
                    style: TextButton.styleFrom(
                        backgroundColor: Colors.yellow.shade800,
                        minimumSize: Size(40.0, 15.0),
                      // maximumSize: const Size(20.0, 60.0),
                    ),),
                ],
              ),
              Padding(padding: EdgeInsets.all(15),
                  child:
                  _selectedimage == null ? SizedBox(height: 150,) :
                  Container(
                      height: 200,
                      width: 200,
                      decoration: BoxDecoration(
                        border: Border.all(
                          width: 10,
                          color: Colors.white
                        ),
                        borderRadius: BorderRadius.circular(25)
                      ),
                      child: Image.file(File(_selectedimage!.path), fit: BoxFit.fill,))),
              Card(
                  color: Colors.yellow.shade800,
                  child:
                  ListTile(
                      leading: Icon(Icons.info, size: 50, color: Colors.white,),
                      title: Text("To take a Picture, press on the CAMERA button.\n\nTo save the picture to GALLERY, press SAVE TO GALLERY.\n\nTo Upload the picture, press UPLOAD",
                          style: TextStyle(color: Colors.white, fontSize: 18))
                  )
              )
            ],
          ),
          // Images tab
          ListView(children: <Widget>[

            SizedBox(height: 30,),

            TextButton(onPressed: _pickImageFromGallery,
              child: Text("Gallery", style: TextStyle(fontSize: 30, color: Colors.white)),
              style: TextButton.styleFrom(
                  minimumSize: Size(20.0, 15.0),
                  maximumSize: const Size(20.0, 60.0),
                  backgroundColor: Colors.yellow.shade800
            ),),
            const SizedBox(height: 20,),

            TextButton(onPressed: _pickImageFromCamera, child: Text("Camera", style: TextStyle(fontSize: 30, color: Colors.white)),
              style: TextButton.styleFrom(
                  backgroundColor: Colors.yellow.shade800
              ),),

            const SizedBox(height: 20,),
            Container(
              height: 600,
                child:
            GridView.builder(
              itemCount: imagelist.length,
              itemBuilder: (BuildContext context, int index) {
                return Container(
                  height: 200,
                    width: 100,
                    child: Padding(
                        padding: EdgeInsets.all(15),
                        child:
                        imagelist.isEmpty ? const Text("Please select an image", style: TextStyle(color: Colors.white)) : Image.file(File(imagelist[index]), fit: BoxFit.fill,)));},
              gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
                crossAxisCount: 2,
              ),))

            ]),
        ])
    ));
  }

  Future _pickImageFromGallery() async{
    final returnedimage = await ImagePicker().pickImage(source: ImageSource.gallery);
    final snackBar = SnackBar(content: Text("Gallery_clicked"));
    ScaffoldMessenger.of(context).showSnackBar(snackBar);

    if(returnedimage == null) return;
    setState(() {
      imagelist.add(returnedimage!.path);
      _selectedimage = XFile(returnedimage!.path);
    });
  }

  Future _pickImageFromCamera() async{
    final returnedimage = await ImagePicker().pickImage(source: ImageSource.camera);
    final snackBar = SnackBar(content: Text("Picture added to Gallery"));
    ScaffoldMessenger.of(context).showSnackBar(snackBar);

    if(returnedimage == null) return;
    setState(() {
      _selectedimage = XFile(returnedimage.path);
    });
  }
}
