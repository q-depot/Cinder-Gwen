#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "cigwen/CinderGwen.h"

#include "Gwen/Controls/Button.h"
#include "Gwen/Controls/WindowControl.h"

#include "CustomControl.h"

#define SKIN_NAME "DefaultSkin.png"
//#define SKIN_NAME "obscureskin.png"

using namespace ci;
using namespace ci::app;
using namespace std;

class CustomControlWindowApp : public AppNative {
  public:
	void prepareSettings( Settings *settings );
	void setup();
	void draw();

private:
	void buttonPressed();

	cigwen::GwenInterfaceRef mGwenInterface;
};

void CustomControlWindowApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 800, 600 );
}

void CustomControlWindowApp::setup()
{
	getWindow()->setTitle( "Gwen CustomControlWindow" );

	// TODO: find a better way..
#if defined( CINDER_COCOA )
	fs::path rootPath = getAppPath().parent_path().parent_path().parent_path().parent_path().parent_path().parent_path();
#else
	fs::path rootPath = getAppPath().parent_path().parent_path().parent_path().parent_path().parent_path();
#endif
	addAssetDirectory( rootPath / "assets" );

	mGwenInterface = cigwen::GwenInterface::create( loadAsset( SKIN_NAME ) );


	// add controls:
	
	Gwen::Controls::Button *btn = new Gwen::Controls::Button( mGwenInterface->getCanvas() );
	btn->SetBounds( getWindowCenter().x - 40, getWindowCenter().y - 20, 80, 40 );
	btn->SetText( "Click Me" );
	btn->AddAccelerator( "x" ); // hit key x to trigger this

	Gwen::Controls::Button *btn2 = new Gwen::Controls::Button( mGwenInterface->getCanvas() );
	btn2->SetBounds( btn->X(), btn->Bottom() + 10, 80, 40 );
	btn2->SetText( "Me too" );
	btn2->AddAccelerator( "c" ); // hit key c to trigger this

	// ???: ambiguous?
	//	mGwenInterface->addCallback( &btn->onPress, bind( &CustomControlWindowApp::buttonPressed, this ) );

	mGwenInterface->addCallback( &btn->onPress, [&] {
 		console() << "btn onPress callback" << endl;
	} );

	// FIXME: adding this blocks the first callback
	mGwenInterface->addCallback( &btn2->onPress, [&] ( Gwen::Controls::Base *ctl ) {
		dynamic_cast<Gwen::Controls::Button *>( ctl )->SetText( "Thanks!" );
		console() << "btn2 onPress callback" << endl;
	} );
}

void CustomControlWindowApp::buttonPressed()
{
	console() << "button pressed" << endl;

	auto window = new Gwen::Controls::WindowControl( mGwenInterface->getCanvas() );
	window->SetTitle( "This is CustomControl" );
	window->SetSize( 300, 400 );
	window->SetPos( randInt( 50, 450 ), randInt( 50, 250 ) );
	window->SetDeleteOnClose( true );
	window->SetClampMovement( false );

	CustomControl *control = new CustomControl( window );
	control->SetPos( 0, 0 );
	control->Dock( Gwen::Pos::Fill );
}

void CustomControlWindowApp::draw()
{
	gl::clear();
	mGwenInterface->draw();
}

CINDER_APP_NATIVE( CustomControlWindowApp, RendererGl )
