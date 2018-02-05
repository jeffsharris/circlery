PImage myImage;
int halfImage;
color[] pixelholder;
boolean flipped = false;

void setup() {
  size(10, 10);
  myImage = loadImage("ocean.jpeg");
  myImage.loadPixels();
  
  int dimension = width * height;
  
  pixelholder = new color[dimension];
  
  //for every two rows
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
 
  printArray("red", flipped);
  printArray("green", flipped);
  printArray("blue", flipped);
  
}

void draw() {
  image(myImage, 0, 0);
}

void printArray(String rgbColor, boolean flipped){
  int pixelColor;
  color pixel;

  
  int dimension = width * height;
  print("uint8_t "+ rgbColor+"pixels[] = {");
  for (int i = 0; i < dimension; i++){
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
    if(i == dimension - 1){
      print(pixelColor);
    }
    else{
      print(pixelColor+", "); 
    }
  }
  print("}; \n\n");
  
}