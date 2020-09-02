#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderProjectTestApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void CinderProjectTestApp::setup()
{
}

void CinderProjectTestApp::mouseDown( MouseEvent event )
{
}

void CinderProjectTestApp::update()
{
}

void CinderProjectTestApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( CinderProjectTestApp, RendererGl )
