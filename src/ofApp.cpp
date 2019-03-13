#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetLogLevel("ofThread", OF_LOG_ERROR);
	//ofSetVerticalSync(false);
	ofEnableAlphaBlending();
	
	doDrawInfo	= true;
		
	consoleListener.setup(this);
	printer.open("/dev/serial0");
	
	settings.sensorWidth = 1280;
	settings.sensorHeight = 720;
	settings.framerate = 20;
	settings.enableTexture = true;
	
	videoGrabber.setup(settings);
	filterCollection.setup();

	doShader = true;
	shader.load("shaderExample");
	
	fbo.allocate(settings.sensorWidth, settings.sensorHeight);
	fbo.begin();
		ofClear(0, 0, 0, 0);
	fbo.end();
	
	font.load("fonts/DejaVuSansMono.ttf", 60);
	snapShot = false;
	clientTyping = "hola hola esta es una prueba con texto más grande ";
		
}	

//--------------------------------------------------------------
void ofApp::update()
{
	if (!doShader || !videoGrabber.isFrameNew())
	{
		return;
	}
	fbo.begin();
		ofClear(0, 0, 0, 0);
		shader.begin();

		//ofDisableDepthTest();

		shader.setUniformTexture("tex0", videoGrabber.getTextureReference(), videoGrabber.getTextureID());
		shader.setUniform1f("time", ofGetElapsedTimef());
		shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
		videoGrabber.draw();
		shader.end();
	fbo.end();

}


//--------------------------------------------------------------
void ofApp::draw(){
	
  //if (doShader)
  //	{

  ofScale(0.25, 0.25);
		fbo.draw(0, 0);		
		//	}else 
		//{
		//videoGrabber.draw();
		//}
		ofDisableArbTex();
		text = wrapString(clientTyping, 700);
		rect = font.getStringBoundingBox(text, 0, 0);
		font.drawString(text, (ofGetWidth()*0.5)-(rect.width*0.5), ((ofGetHeight()* 0.5)-(rect.height*0.5)));

		if (snapShot == true){
		  // grab a rectangle at 200,200, width and height of 300,180
		  img.grabScreen(0,0, ofGetWidth()/4,ofGetHeight()/4);

		  string fileName = "imagen.jpg";
		  img.save(fileName, OF_IMAGE_QUALITY_MEDIUM);
		  snapShot = false;
	}

	//img.draw(0, 0, , 180);
	//
}

void ofApp::exit(){
    printer.close();
}


void ofApp::keyPressed  (int key){
  if(key == 'c'){
    snapShot = true;
    //imprimir.load("snapshot.jpg");
    //img.resize(329, 185);
  } else if (key == 'p'){
    //img.resize(329, 185);
//    printer.print(img, 127);
    //snapShot = true;
    //printer.println("hola algo no funciona esta es una proeba");
    printer.print(img);
  }
}

void ofApp::onCharacterReceived(KeyListenerEventData& e)
{
        keyPressed((int)e.character);
}


