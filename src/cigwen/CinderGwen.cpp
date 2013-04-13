#include "cigwen/CinderGwen.h"
#include "cigwen/GwenInput.h"
#include "cigwen/GwenRendererGl.h"

#include "Gwen/Skins/TexturedBase.h"

using namespace std;

namespace cigwen {

	GwenInterface::GwenInterface( ci::DataSourceRef skinSource, ci::ColorA backgroundColor )
	{
		mRenderer = new cigwen::GwenRendererGl();
		mRenderer->Init();

		Gwen::Skin::TexturedBase* skin = new Gwen::Skin::TexturedBase( mRenderer );
		skin->Init( skinSource->getFilePath().string() );

		mCanvas = new Gwen::Controls::Canvas( skin );
		if( backgroundColor != ci::ColorA::zero() ) {
			mCanvas->SetDrawBackground( true );
			mCanvas->SetBackgroundColor( toGwen( backgroundColor ) );
		}
		mGwenInput = cigwen::GwenInput::create( mCanvas );
	}

	void GwenInterface::setSize( ci::Vec2i size )
	{
		mCanvas->SetSize( size.x, size.y );
	}

	void GwenInterface::draw()
	{
		mCanvas->RenderCanvas();
	}
	
} // namespace cigwen


