
import netP5.*;
import oscP5.*;
import beads.*;
import processing.net.*; 

PImage img[];

int images;
int countPartyobj;

float slowTime;
float maxMotion;
float speed;

OscP5 oscP5;
AudioContext ac;
SamplePlayer sp1;
Gain sampleGain;
Glide gainRate;

final String WHERE_OSC_ADDRESS = "/MakeItArt/Where";

final int LISTENING_PORT = 8888;


void setup()
{
   
  size(600, 600);
  background(255, 227, 227);
  fill(0);
  text("press p to change volume with motion", 10,10);
  text("press n to set volume back to standard", 30,30);
  speed =1;
  ac= new AudioContext();
 

  try {  //load audio, if you cant find escape
    sp1 =  new SamplePlayer(ac, new Sample(sketchPath("")+"Party.mp3"));
  }
  catch (Exception e) {
    println("couldn't find music");
    e.printStackTrace();
  }

  sp1.setKillOnEnd(false);  //once the song is done playing, dont repeat
  gainRate= new Glide(ac, speed);
  sampleGain = new Gain(ac, 1, gainRate);
  sampleGain.addInput(sp1);

  ac.out.addInput(sampleGain);
  ac.start(); //setup features and start processing sound
  //sp1.setToLoop(); if you wanted to
  oscP5 = new OscP5(this, LISTENING_PORT);

  images=8;
  img=new PImage [images];  //create image array of size 8
  img[0]=loadImage("hat1.png");
  img[1]=loadImage("hat2.png");
  img[2]=loadImage("hat3.png");
  img[3]=loadImage("yellow.png");
  img[4]=loadImage("purple.png");
  img[5]=loadImage("blue.png");
  img[6]=loadImage("ppink.png");
  img[7]=loadImage("green.png");
}


void oscEvent(OscMessage msg)
{
  String addr = msg.addrPattern();
 
  if (addr.equals(WHERE_OSC_ADDRESS))
  {

    slowTime = msg.get(0).floatValue();  //get slowest time change
    maxMotion = msg.get(1).floatValue();  //count max motion
  }


  println("max time:" +slowTime +"max motion"+maxMotion );
}

void draw() {
 
  if (maxMotion>0) {  //if there are values, draw the images and track how many
    partyObject();
    countPartyobj++;
  }

  if (key=='o') {
    speed=slowTime;
    gainRate.setValue(speed);  //sets the sound to start taking in the values
    println("speed="+speed);
  }
  
  if(key=='n'){
  gainRate.setValue(1);  //set volume to normal
  }

  if (countPartyobj>50) {  //clears the screen if there are too many objects on at once
    background(255, 227, 227);
    fill(0);
    text("press p to change volume with motion", 10,10);
    text("press n to set volume back to standard", 10,30);
    countPartyobj=0;
  }
}




void partyObject() {  //randomly picks an image and places it randomly on the screen
  int index = int(random(img.length));
  image(img[index], random
    (0, 590), random(40, 590));
}
