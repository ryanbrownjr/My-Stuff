import processing.serial.*;
Serial myPort;
int SteveX = 500;
int SteveY = 500;
int SteveWidth = 30;
int SteveHeight = 30;
int foodWidth = 10;
int foodHeight = 10;
float foodX = random(1000-foodWidth);
float foodY = random(1000-foodHeight);
int buttonVal = 0;
int speed = 5;
color bgcolor = color(255,204,100);

void setup(){
    size(1000,1000);
    strokeWeight(4);
    println("Available serial ports:");
    println(Serial.list());
    myPort= new Serial(this, "COM3", 9600);
}

void draw(){
  background(bgcolor);
    if(myPort.available() > 0){
      buttonVal=myPort.read();
      println(buttonVal);
    }

rect(SteveX, SteveY, SteveWidth, SteveHeight);

  if(buttonVal >= 254){
    SteveX=SteveX-speed;
  }

  else if((buttonVal >= 249) && (buttonVal <= 251)){
    SteveY=SteveY-speed;
  }

  else if((buttonVal >= 126) && (buttonVal <= 129)){
    SteveX=SteveX+speed;
  }

  else if((buttonVal < 3) && (buttonVal > 0)){
    SteveY=SteveY+speed;
  }

rect(foodX, foodY, foodWidth, foodHeight);

  if((foodX > SteveX-foodWidth) && (foodX < SteveX+SteveWidth) && (foodY < SteveY+SteveHeight) && (foodY > SteveY-foodHeight)){
    foodX = random(1000-foodWidth);
    foodY = random(1000-foodHeight);
  }

if(SteveX<0){
  SteveX=0;
}

if(SteveX>1000-SteveWidth){
  SteveX=1000-SteveWidth;
}

if(SteveY<0){
  SteveY=0;
}

if(SteveY>1000-SteveHeight){
  SteveY=1000-SteveHeight;
}
}
