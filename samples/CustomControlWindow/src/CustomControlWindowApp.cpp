#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "cigwen/GwenRendererGl.h"
#include "cigwen/GwenInput.h"
#include "cigwen/CinderGwen.h"

#include "Gwen/Skins/Simple.h"
#include "Gwen/Skins/TexturedBase.h"
#include "Gwen/Controls/Button.h"
#include "Gwen/Controls/WindowControl.h"

#include "CustomControl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CustomControlWindowApp : public AppNative {
  public:
	void prepareSettings( Settings *settings );
	void setup();
	void draw();

	void buttonPressed( Gwen::Controls::Button *button );

private:
	void addControls();

	cigwen::GwenRendererGl *mRenderer;
	cigwen::GwenInputRef mGwenInput;
	Gwen::Controls::Canvas *mCanvas;

	cigwen::ControlCallback<Gwen::Controls::Button> mButtonCallback;
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

	mRenderer = new cigwen::GwenRendererGl();
	mRenderer->Init();

	Gwen::Skin::TexturedBase* skin = new Gwen::Skin::TexturedBase( mRenderer );
	skin->Init( "DefaultSkin.png" );
//	skin->Init( "obscureskin.png" );

	mCanvas = new Gwen::Controls::Canvas( skin );
	mCanvas->SetSize( 998, 650 - 24 );
	mCanvas->SetDrawBackground( true );
	mCanvas->SetBackgroundColor( cigwen::toGwen( Color::gray( 0.2f ) ) );

	mGwenInput = cigwen::GwenInput::create( mCanvas );

	addControls();
}

void CustomControlWindowApp::addControls()
{
	Gwen::Controls::Button *btn = new Gwen::Controls::Button( mCanvas );
	btn->SetBounds( getWindowCenter().x - 40, getWindowCenter().y - 20, 80, 40 );
	btn->SetText( L"Click Me" );
	btn->AddAccelerator( L"x" );

	//btn->onPress.Add( this, &CustomControlWindowApp::buttonPressed ); // NOTE: you could do this too, but be careful with multiple inheritance
	mButtonCallback.setCallback( btn, bind( &CustomControlWindowApp::buttonPressed, this, std::_1 ) );
}

void CustomControlWindowApp::buttonPressed( Gwen::Controls::Button* button )
{
	console() << "button pressed" << endl;

	auto window = new Gwen::Controls::WindowControl( mCanvas );
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
	mCanvas->RenderCanvas();
}

CINDER_APP_NATIVE( CustomControlWindowApp, RendererGl )
