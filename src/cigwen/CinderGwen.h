// Part of Cinder-Gwen, a block for cinder (www.libcinder.org)
// Created by Richard Eakin

#pragma once

#include "cinder/Rect.h"
#include "Gwen/Structures.h"
#include "Gwen/Events.h"

#include <functional>

namespace cigwen {

	inline Gwen::Color toGwen( const ci::ColorA &c )	{ return Gwen::Color( c.r * 255, c.g * 255, c.b * 255, c.a * 255 ); }
	inline ci::ColorA fromGwen( const Gwen::Color &c )	{ return ci::ColorA( c.r / 255.0f, c.g / 255.0f, c.b / 255.0f, c.a / 255.0f ); }

	inline ci::Vec2f fromGwen( const Gwen::Point &p )	{ return ci::Vec2f( p.x, p.y ); }
	inline ci::Rectf fromGwen( const Gwen::Rect &r )	{ return ci::Rectf( r.x, r.y, r.x + r.w, r.y + r.h ); }

	//! Helper class that maintains a std::function callback for a Gwen control
	struct ControlCallback : public Gwen::Event::Handler {
		typedef std::function<void ()> Callback;
		typedef std::function<void ( Gwen::Controls::Base *control  )> ParamCallback;

		ControlCallback() {}
		ControlCallback( Gwen::Event::Caller *caller, Callback cb )			{ set( caller, cb ); }
		ControlCallback( Gwen::Event::Caller *caller, ParamCallback cb )	{ set( caller, cb ); }

		void set( Gwen::Event::Caller *caller, Callback cb )		{ caller->Add( this, &ControlCallback::onEvent ); mCallback = cb; }
		void set( Gwen::Event::Caller *caller, ParamCallback cb )	{ caller->Add( this, &ControlCallback::onEventWithParam ); mParamCallback = cb; }

		void onEvent()			{
			mCallback();
		}
		void onEventWithParam( Gwen::Controls::Base *control )	{
			mParamCallback( control );
		}
	private:
		Callback mCallback;
		ParamCallback mParamCallback;
	};

} // namespace cigwen
