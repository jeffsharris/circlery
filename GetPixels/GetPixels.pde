PImage myImage;
int halfImage;
color[] pixelholder;
boolean flipped = false;
PrintWriter output;
String filename = "alinea";

int side = 32;
int numpixels = side * side;

int[] hilbert = new int[numpixels];

//0 = RBG, 1 = HSB
int mode = 1;

void setup() {
  if (mode ==0){
    colorMode(RGB, 255, 255,255);
  }
  if(mode==1){
    colorMode(HSB, 255, 255, 255);
  }
  
  surface.setSize(side, side);
  myImage = loadImage("circlery/"+filename+".jpg");
  myImage.loadPixels();
  
  pixelholder = new color[numpixels];
  
  //for every two rows, set up the pixelholder array to hold the pixels in the right snaking order
  for(int i = 0; i < height - 1; i+=2){
    //the lower row
    int secondrow = i+1;
    
    //copy the top row without changing
    for (int j = 0; j < width; j++){
        pixelholder[i*width+j] = myImage.pixels[i*width+j];
    }
    //print the bottom row backwards
    for (int j = width -1; j >=0; j--){
        if (secondrow < height){
          int flip = width - j-1;
          pixelholder[(secondrow)*width+flip] = myImage.pixels[(secondrow)*width+j];
        }
    }
  }  
  
  String[] lines = loadStrings("32hilbert.txt");
  
  //populate with array from text file
  for (int i =0; i< numpixels; i++){
    hilbert[i] = int(lines[i]);
  }

  
 /*
  printArray("red", flipped);
  printArray("green", flipped);
  printArray("blue", flipped);
  */
  
  printHilbert("output/"+filename+".txt", 1);
}

void draw() {
  color[] hilbertPixels = new color[numpixels];
  for (int i = 0; i< numpixels;i++){
    int index = hilbert[i];
    hilbertPixels[index] = myImage.pixels[i];
  }
  
  for(int i = 0; i< side; i++){
    for (int j =0; j< side; j++){
      set(i, j, hilbertPixels[i*side+j]);
    }
  }
}


void printHilbert(String filename, int iterations){
  color[] hilbertPixels = new color[numpixels];
  
  output = createWriter(filename);
  
  for (int i = 0; i< numpixels;i++){
    int index = hilbert[i];
    hilbertPixels[index] = myImage.pixels[i];
  }
  
  printArray(filename, hilbertPixels, iterations, mode);
  
}

void printArray(String filename, color[] array, int iterations, int mode){
  int pixelColor;
  color pixel;
  
  output = createWriter(filename); 
  
//  output.print ("uint8_t allColors[][]= {");
//  print ("uint8_t allColors[][]= {");


  output.print ("{");
  
    for (int i = 0; i < numpixels; i++){  
      for (int x = 0; x < iterations; x++){
        pixel = array[i];
        if(mode ==0){
          output.print ("{"+int(red(pixel))+","+int(green(pixel))+","+int(blue(pixel))+"}");
        }
        else if(mode == 1){
          output.print ("{"+int(hue(pixel))+","+int(saturation(pixel))+","+int(brightness(pixel))+"}");
        }
        if ((i == numpixels - 1) && (x==iterations-1)){
          output.print("};");
        }
        else{
          output.print(",");
        }
    }
  }
  output.flush();
  output.close();
}

void printAll(boolean flipped, String filename){
  int pixelColor;
  color pixel;
  
  output = createWriter(filename); 
  
//  output.print ("uint8_t allColors[][]= {");
//  print ("uint8_t allColors[][]= {");

  output.print ("{");
  
  for (int i = 0; i < numpixels; i++){
    if (flipped ==true){
      pixel = pixelholder[i];
    }
    else{
      pixel = myImage.pixels[i];
    }
    output.print ("{"+int(red(pixel)/2)+","+int(green(pixel)/2)+","+int(blue(pixel)/2)+"}");
    if (i == numpixels - 1){
      output.print("};");
    }
    else{
      output.print(",");
    }
  }
  output.flush();
  output.close();
}

void printArray(String rgbColor, boolean flipped){
  int pixelColor;
  color pixel;

  print("uint8_t "+ rgbColor+"pixels[] = {");
  
  for (int i = 0; i < numpixels; i++){
    if (flipped ==true){
      pixel = pixelholder[i];
    }
    else{
      pixel = myImage.pixels[i];
    }
    
    if (rgbColor=="red"){
      pixelColor = int(red(pixel));
    }
    else if (rgbColor =="green"){
      pixelColor = int(green(pixel));    
    }
    else if (rgbColor =="blue"){
      pixelColor = int(blue(pixel));    
    }
    else {
      print("BAD COLOR!");
      return;
    }
    
    if(i == numpixels - 1){
      print(pixelColor);
    }
    else{
      print(pixelColor+", "); 
    }
  }
  print("}; \n\n");
  
}