

#pragma once

#include "CinderGwen.h"
#include "Gwen/Controls/HorizontalSlider.h"


class HorizontalSliderWithLabel : public Gwen::Controls::Base {
    
public:
    
    HorizontalSliderWithLabel( std::string name, float *var, Gwen::Controls::Base *parent ) : Gwen::Controls::Base(parent)
    {
        mVar = var;
        
        SetHeight( 50 );
        
        // Param name
        Gwen::Controls::Label *pLabel = new Gwen::Controls::Label( this );
        pLabel->SetText( name );
        pLabel->SetHeight( 15 );
        pLabel->Dock( Gwen::Pos::Top );
        pLabel->SetTextColorOverride( cigwen::toGwen( ci::Color::gray( 0.3f ) ) );

        mValueLabel = new Gwen::Controls::Label( this );
        mValueLabel->SetText( "0.0" );
        mValueLabel->SetHeight( 15 );
        mValueLabel->Dock( Gwen::Pos::Top );
        mValueLabel->SetTextColorOverride( cigwen::toGwen( ci::Color::gray( 0.3f ) ) );
        
        // Slider
        mSlider = new Gwen::Controls::HorizontalSlider( this );
        mSlider->SetHeight( 20 );
        mSlider->Dock( Gwen::Pos::Top );
        mSlider->SetFloatValue( 0.0f );
        mSlider->onValueChanged.Add( this, &HorizontalSliderWithLabel::onChange );
    }

    virtual ~HorizontalSliderWithLabel() {}
    
    void SetValue( float val )
    {
        mSlider->SetFloatValue( val );
        
    }
    void SetRange( float min, float max )
    {
        mSlider->SetRange( min, max );
    }
    
    void Render( Gwen::Skin::Base* skin )
    {
        mSlider->SetFloatValue( *mVar );
    }
    
private:
    
    void onChange( Gwen::Controls::Base* pControl )
    {
        float val = ((Gwen::Controls::Slider*)pControl)->GetFloatValue();
        mValueLabel->SetText( std::to_string( val ) );
        *mVar = val;
    }
    
private:
    
    Gwen::Controls::HorizontalSlider    *mSlider;
    Gwen::Controls::Label               *mValueLabel;
    float                               *mVar;
};

