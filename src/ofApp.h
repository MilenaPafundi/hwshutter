#pragma once

#include "ofMain.h"
#include "ofAppEGLWindow.h"
#include "TerminalListener.h"
#include "ofxOMXVideoGrabber.h"
#include "ImageFilterCollection.h"
#include "ofxThermalPrinter.h"

class ofApp : public ofBaseApp, public KeyListener{

	public:

		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void exit();

	void onCharacterReceived(KeyListenerEventData& e);
	TerminalListener consoleListener;
	ofxOMXVideoGrabber videoGrabber;
	ofxThermalPrinter printer;
	

	  ofImage imprimir;
	
	ImageFilterCollection filterCollection;
	
	bool doDrawInfo;
	
	ofFbo fbo;
	ofShader shader;
	bool doShader;
		
	ofxOMXCameraSettings settings;

	string clientTyping;
	ofTrueTypeFont font;
	string text;
	ofRectangle rect;
	ofImage img;
	bool snapShot;

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

