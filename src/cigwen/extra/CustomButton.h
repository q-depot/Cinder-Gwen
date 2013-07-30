

#pragma once

#include "CinderGwen.h"
#include "Gwen/Controls/Button.h"


class CustomButton : public Gwen::Controls::Button {
    
public:
    
    CustomButton( std::string name, bool *var, Gwen::Controls::Base *parent ) : Gwen::Controls::Button(parent)
    {
        
        mVar = var;
        
        SetText( name );
        
//        onPress.Add( this, &CustomButton::onChange );
    }

    virtual ~CustomButton() {}

    void Render( Gwen::Skin::Base* skin )
    {
        SetToggleState( *mVar );
        Gwen::Controls::Button::Render( skin );
    }
    
private:
    
    void OnPress()
    {
        Gwen::Controls::Button::OnPress();
        
        *mVar = GetToggleState();
    }
    
private:
    
    bool *mVar;
    
};

