PImage myImage;
int halfImage;
color[] pixelholder;

void setup() {
  size(10, 10);
  myImage = loadImage("ocean.jpeg");
  myImage.loadPixels();
  
  int dimension = width * height;
  
  pixelholder = new color[dimension];
  
  for(int i = 0; i < height - 1; i+=2){
    int secondrow = i+1;
    
    for (int j = 0; j < width; j++){
        pixelholder[i*width+j] = myImage.pixels[i*width+j];
        //print("("+i+","+j+") ");
    }
    
    //print ("\n\n");
    
    for (int j = width -1; j >=0; j--){
        if (secondrow < height){
          int flip = width - j-1;
          pixelholder[(secondrow)*width+flip] = myImage.pixels[(secondrow)*width+j];
          //print("("+secondrow+","+j+") red: " + red(myImage.pixels[(secondrow)*width +j])+" | ");
        }
    }
    //print("\n\n");
  }  
 
  printArray("red");
  printArray("green");
  printArray("blue");
  
}

void draw() {
  image(myImage, 0, 0);
}

void printArray(String rgbColor){
  int pixelColor;
  
  int dimension = width * height;
  print("uint8_t "+ rgbColor+"pixels[] = {");
  for (int i = 0; i < dimension; i++){
    if (rgbColor=="red"){
//      pixelColor = int(red(myImage.pixels[i]));
      pixelColor = int(red(pixelholder[i]));
    }
    else if (rgbColor =="green"){
//      pixelColor = int(green(myImage.pixels[i]));
      pixelColor = int(green(pixelholder[i]));
    }
    else if (rgbColor =="blue"){
//      pixelColor = int(blue(myImage.pixels[i]));
      pixelColor = int(blue(pixelholder[i]));
    }
    else {
      print("BAD COLOR!");
      return;
    }
    if(i == dimension - 1){
      print(pixelColor);
    }
    else{
      print(pixelColor+", "); 
    }
  }
  print("}; \n\n");
  
}