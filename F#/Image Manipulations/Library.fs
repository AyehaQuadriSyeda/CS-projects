//
// F# image processing functions.
//
// Author: Ayesha Quadri Syeda
// Project 5
// Purpose: Manipulate the pixels in an image
// Date: 12/2/2022
//

namespace ImageLibrary

module Operations =
  //
  // all functions must be indented
  //

  // graycalc
  // returns the calculated grayscale
  let rec graycalc (l:(int*int*int)) = 
      let r, g, b = l
      let s = ((float r)*(float 0.299)) + ((float g)*(float 0.587)) + ((float b)*(float 0.114))
      ((int)s, (int)s, (int)s)


  //
  // Grayscale:
  //
  // Converts the image into grayscale and returns the 
  // resulting image as a list of lists. Pixels in grayscale
  // have the same value for each of the Red, Green and Blue
  // values in the RGB value.  Conversion to grayscale is done
  // by using a WEIGHTED AVERAGE calculation.  A normal average
  // (adding the three values and dividing by 3) is not the best,
  // since the human eye does not perceive the brightness of 
  // red, green and blue the same.  The human eye perceives 
  // green as brighter than red and it perceived red as brighter
  // than blue.  Research has shown that the following weighted
  // values should be used when calculating grayscale.
  //  - the green value should account for 58.7% of the grayscale.
  //  - the red value should account for   29.9% of the grayscale.
  //  - the blue value should account for  11.4% of the grayscale.
  //
  // So if the RGB values were (25, 75, 250), the grayscale amount 
  // would be 80, (25 * 0.299 + 75 * 0.587 + 250 * 0.114 => 80)
  // and then all three RGB values would become 80 or (80, 80, 80).
  // We will use truncation to cast from the floating point result 
  // to the integer grayscale value.
  //
  // Returns: updated image.
  //

  let rec Grayscale (width:int) 
                    (height:int) 
                    (depth:int) 
                    (image:(int*int*int) list list) = 
    match image with 
    |[]  -> []
    |h1::t1 -> (List.map (graycalc) h1)::Grayscale width height depth t1


  //calcthreshold 
  //compares the RGB values with the threshold and changes them 
  // accordingly

  let calcthreshold (l: int*int*int) (threshold:int) (depth:int)=
    let r, g, b = l
    if((float r) > (float threshold)) then
      let r1 = depth
      if((float g) > (float threshold)) then 
        let g1 = depth
        if((float b) > (float threshold)) then    
          let b1 = depth
          (r1, g1, b1)
        else  
          let b1 = 0
          (r1, g1, b1)
      else
        let g1 = 0
        if((float b) > (float threshold)) then    
          let b1 = depth
          (r1, g1, b1)
        else  
          let b1 = 0
          (r1, g1, b1)
    else
      let r1 = 0
      if((float g) > (float threshold)) then 
        let g1 = depth
        if((float b) > (float threshold)) then    
          let b1 = depth
          (r1, g1, b1)
        else  
          let b1 = 0
          (r1, g1, b1)
      else
        let g1 = 0
        if((float b) > (float threshold)) then    
          let b1 = depth
          (r1, g1, b1)
        else  
          let b1 = 0
          (r1, g1, b1)

//
  // Threshold
  //
  // Thresholding increases image separation --- dark values 
  // become darker and light values become lighter. Given a 
  // threshold value in the range 0 < threshold < color depth,
  // each RGB value is compared to see if it's > threshold.
  // If so, that RGB value is replaced by the color depth;
  // if not, that RGB value is replaced with 0. 
  //
  // Example: if threshold is 100 and depth is 255, then given 
  // a pixel (80, 120, 160), the new pixel is (0, 255, 255).
  //
  // Returns: updated image.
  //
      
  let rec Threshold (width:int) 
                    (height:int)
                    (depth:int)
                    (image:(int*int*int) list list)
                    (threshold:int) = 
    match image with
    |[] -> []
    |h1::t1 -> (List.map (fun e -> calcthreshold e threshold depth) h1)::Threshold width height depth t1 threshold


  // removelast
  // removes the last element of the List
  
  let rec removelast (l: (int*int*int) list) = 
    match l with 
    |[] -> []
    |h1::[] -> []
    |h1::t1 -> h1::(removelast t1)

  // getlast 
  // returns the last element of the List
  let rec getlast (l: (int*int*int) list) =
    match l with  
    |[] -> []
    |h1::[] -> [h1]
    |(r, g, b)::rest -> getlast rest

  // changepix
  // manipulates the order of the pixels
  let rec changepix (l: (int*int*int) list) = 
    match l with
    |[] -> []
    |h1::t1 -> let t2 = removelast t1
               let last = getlast t1
               (last)@(changepix t2)@[h1]

//
  // FlipHorizontal:
  //
  // Flips an image so that what’s on the left is now on 
  // the right, and what’s on the right is now on the left. 
  // That is, the pixel that is on the far left end of the
  // row ends up on the far right of the row, and the pixel
  // on the far right ends up on the far left. This is 
  // repeated as you move inwards toward the row's center.
  //
  // Returns: updated image.
  //
    
  let rec FlipHorizontal (width:int)
                         (height:int)
                         (depth:int)
                         (image:(int*int*int) list list) = 
    match image with 
    |[] -> []
    |h1::t1 -> (changepix h1)::FlipHorizontal width height depth t1
    

//calcsig 
// calculates the distance between two points 
// returns true if there is edge significance, otherwise false
  let calcsig (p1:(int*int*int))(p2: (int*int*int))(threshold:int) =
    let r1, g1, b1 = p1
    let r2, g2, b2 = p2
    let i = (float(r1 - r2))**2.0 + (float(g1 - g2))**2.0 + (float(b1 - b2))**2.0
    let j = sqrt i
    if(j > (float threshold)) then 
      true
    else 
      false

// checkright
// checks the right pixel for edge-significance

  let checkright (l:(int*int*int) list) (threshold:int) = 
    let h1 = List.head l
    let t1 = List.tail l
    let h2 = List.head t1
    let r = calcsig h1 h2 threshold
    if(r = true) then
      true
    else
      false

// checkbelow
// checks the pixel below for edge-significance
  let checkbelow (l1:(int*int*int) list)(l2:(int*int*int) list) (threshold:int) = 
    let h1 = List.head l1
    let h2 = List.head l2
    let r = calcsig h1 h2 threshold
    if(r = true) then
      true
    else
      false

//pieces
//checks for edge-significance and changes the RGB values
  let rec  pieces (l1:(int*int*int) list)(l2:(int*int*int) list)(threshold:int)(depth:int) = 
    match l1, l2 with
    |[], [] -> []
    |h1::[], _ -> []
    |_, h1::[] -> []
    |[], _ -> []
    |_, [] -> []
    |h1::t1, h2::t2 when (checkright l1 threshold) || (checkbelow l1 l2 threshold) -> (0, 0, 0)::pieces t1 t2 threshold depth
    |h1::t1, h2::t2 -> (depth, depth, depth):: pieces t1 t2 threshold depth
    
  //
  // Edge Detection:
  //
  // Edge detection is an algorithm used in computer vision to help
  // distinguish different objects in a picture or to distinguish an
  // object in the foreground of the picture from the background.
  //
  // Edge Detection replaces each pixel in the original image with
  // a black pixel, (0, 0, 0), if the original pixel contains an 
  // "edge" in the original image.  If the original pixel does not
  // contain an edge, the pixel is replaced with a white pixel 
  // (255, 255, 255).
  //
  // An edge occurs when the color of pixel is "signigicantly different"
  // when compared to the color of two of its neighboring pixels. 
  // We only compares each pixel in the image with the 
  // pixel immediately to the right of it and with the pixel
  // immediately below it. If either pixel has a color difference
  // greater than a given threshold, then it is "significantly
  // different" and an edge occurs. Note that the right-most column
  // of pixels and the bottom-most column of pixels can not perform
  // this calculation so the final image contain one less column
  // and one less row than the original image.
  //
  // To calculate the "color difference" between two pixels, we
  // treat the each pixel as a point on a 3-dimensional grid and
  // we calculate the distance between the two points using the
  // 3-dimensional extension to the Pythagorean Theorem.
  // Distance between (x1, y1, z1) and (x2, y2, z2) is
  //  sqrt ( (x1-x2)^2 + (y1-y2)^2 + (z1-z2)^2 )
  //
  // The threshold amount will need to be given, which is an 
  // integer 0 < threshold < 255.  If the color distance between
  // the original pixel either of the two neighboring pixels 
  // is greater than the threshold amount, an edge occurs and 
  // a black pixel is put in the resulting image at the location
  // of the original pixel. 
  //
  // Returns: updated image.
  //
  let rec EdgeDetect (width:int)
               (height:int)
               (depth:int)
               (image:(int*int*int) list list)
               (threshold:int) = 
    match image with 
    |[] -> []
    |h1::[] -> []
    |h1::t1 -> let h2 = List.head t1
               (pieces h1 h2 threshold depth)::EdgeDetect width height depth t1 threshold

// reverse2
// reverses the pixel order
  let rec reverse2 (l:(int*int*int)list ) = 
    match l with 
    |[]->[]
    |h1::t1 -> (reverse2 t1)@[h1]

// reverse1 
// calls reverse2 recursively to reverse the pixels 
  let rec reverse1 (l:(int*int*int)list list) = 
    match l with
    |[] -> []
    |h1::t1 -> (reverse2 h1)::reverse1 t1


//
  // RotateRight90:
  //
  // Rotates the image to the right 90 degrees.
  //
  // Returns: updated image.
  //  
  let rec RotateRight90 (width:int)
                        (height:int)
                        (depth:int)
                        (image:(int*int*int) list list) = 
    let t = List.transpose image
    reverse1 t

