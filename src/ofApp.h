#pragma once

#include "ofMain.h"
#include "ofAppEGLWindow.h"
#include "TerminalListener.h"
#include "ofxRPiCameraVideoGrabber.h"
#include "ImageFilterCollection.h"
#include "ofxThermalPrinter.h"
#include "ofxGPIO.h"

//class ofApp : public ofBaseApp{
class ofApp : public ofBaseApp, public KeyListener{

 public:

  void setup();
  void update();
  void draw();
  void keyPressed(int key);
  void setBrightness(ofImage &image, const int brightness);
  void setContrast(ofImage &image, const int contrast);
  
  void onCharacterReceived(KeyListenerEventData& e);
  TerminalListener consoleListener;
  ofxRPiCameraVideoGrabber videoGrabber;
  ofxThermalPrinter printer;
  GPIO gpio18;
  std::vector < std::string > frases;
  	
  ofFbo fbo;
  ofShader shader;
  bool doShader;
  int imprime;
  int salta;
  
  string clientTyping;
  string text;
  ofTrueTypeFont font;
  ofRectangle rect;
  ofImage img;
  ofImage img2; 
  bool snapShot;
  ofBuffer buffer;
  
  OMXCameraSettings omxCameraSettings;
  
  string wrapString(string text, int width) {
    
    string typeWrapped = "";
    string tempString = "";
    vector <string> words = ofSplitString(text, " ");
		  
    for(int i=0; i<words.size(); i++) {
      
      string wrd = words[i];
      cout << wrd << endl;
		    
      tempString += wrd + " ";
      int stringwidth = font.stringWidth(tempString);
      if(stringwidth >= width) {
	tempString = "";
	typeWrapped += "\n";
      }
      
      typeWrapped += wrd + " ";
    }
    
    return typeWrapped;
    
  }

};

