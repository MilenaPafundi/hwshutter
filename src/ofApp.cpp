#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
  	ofSetLogLevel(OF_LOG_VERBOSE);
  	ofSetLogLevel("ofThread", OF_LOG_ERROR);
	ofSetVerticalSync(false);
	ofEnableAlphaBlending();
	printer.open("/dev/serial0");

	consoleListener.setup(this);
		
	omxCameraSettings.width = 1280;
	omxCameraSettings.height = 720;
	omxCameraSettings.framerate = 30;
	omxCameraSettings.enableTexture = true;
	
	videoGrabber.setup(omxCameraSettings);
	//filterCollection.setup();

	doShader = true;
	shader.load("shaderExample");
	
	fbo.allocate(omxCameraSettings.width, omxCameraSettings.height);
	fbo.begin();
		ofClear(0, 0, 0, 0);
	fbo.end();

	font.load("fonts/DejaVuSansMono.ttf", 60);
	snapShot = false;
	clientTyping = "hola hola esta es una prueba con texto más grande ";

	gpio18.setup("17");
	gpio18.export_gpio();
	gpio18.setdir_gpio("in");
	imprime = 0;
	
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
  shader.setUniformTexture("tex0", videoGrabber.getTextureReference(), videoGrabber.getTextureID());
  shader.setUniform1f("time", ofGetElapsedTimef());
  shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
  videoGrabber.draw();
  shader.end();
  fbo.end();

  gpio18.getval_gpio(imprime);
  
  if(imprime == 1){
    snapShot = true;
    img.resize(400, 225);
    printer.print(img, 127);
    printer.println(" ");
    printer.println(" ");
  }

}


//--------------------------------------------------------------
void ofApp::draw(){
	
	if (doShader)
	{
		fbo.draw(0, 0);		
	}else 
	{
		videoGrabber.draw();
	}

	text = wrapString(clientTyping, 700);
	rect = font.getStringBoundingBox(text, 0, 0);
	//ofSetColor(0);
	font.drawString(text, (ofGetWidth()*0.5)-(rect.width*0.5), ((ofGetHeight()* 0.5)-(rect.height*0.5)));
  

	if (snapShot == true){
	  // grab a rectangle at 200,200, width and height of 300,180
	  img.grabScreen(0,0, ofGetWidth(),ofGetHeight());
	  
	  string fileName = "imagen.jpg";
	  img.save(fileName, OF_IMAGE_QUALITY_LOW);
	  snapShot = false;
	}

	//img.resize(300, 180);
	img.draw(0, 0, 300, 200);

	
}

//--------------------------------------------------------------

void ofApp::keyPressed  (int key)
{
  if(key ==  'c')
    {
    snapShot = true;
    img.resize(350, 300);
  } else if (key == 'p')
    {
    img.resize(350, 285);
    printer.print(img, 127);
  } else if (key == 's'){
    printer.println(" ");
  }
}


void ofApp::onCharacterReceived(KeyListenerEventData& e)
{
	keyPressed((int)e.character);
}

