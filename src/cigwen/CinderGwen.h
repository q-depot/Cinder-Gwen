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
	// \note ControlT should be of type Gwen::Controls::Base
	template <typename ControlT>
	struct ControlCallback : public Gwen::Event::Handler {
		typedef std::function<void ( ControlT *control  )> Callback;

		// TODO: this should not just be for type onPress, but for all Gwen::Event::Caller's
		void set( ControlT *control, Callback cb )	{ control->onPress.Add( this, &ControlCallback::onPressed ); mCallback = cb; }
		void onPressed( Gwen::Controls::Base *control )	{ mCallback( static_cast<ControlT *>( control ) ); }
	private:
		Callback mCallback;
	};

} // namespace cigwen
