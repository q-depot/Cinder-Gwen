#include "Gwen/Platform.h"

#include "cinder/app/App.h"
#include "cinder/app/Window.h"

// FIXME: Utilities.h cannot be included with Boost 1.53
namespace cinder {
	void sleep( float milliseconds );
}

//! Implement platform-specific methods declared in the Gwen::Platform namespace
namespace Gwen { namespace Platform {

	void Sleep( unsigned int iMS )
	{
		ci::sleep( static_cast<float>( iMS ) ); // FIXME: cinder/Utilities.h is causing this to break
	}

	void SetCursor( unsigned char iCursor )
	{
#if defined( CINDER_MAC )
		switch( iCursor ) {
			case Gwen::CursorType::Normal:		[[NSCursor arrowCursor] set];			break;
			case Gwen::CursorType::Beam:		[[NSCursor IBeamCursor] set];			break;
			case Gwen::CursorType::SizeNS:		[[NSCursor resizeUpDownCursor] set];	break;
			case Gwen::CursorType::SizeWE:		[[NSCursor resizeLeftRightCursor] set];	break;
			case Gwen::CursorType::SizeNWSE:	[[NSCursor crosshairCursor] set];		break; // note: mac doesn't have one
			case Gwen::CursorType::SizeNESW:	[[NSCursor crosshairCursor] set];		break; // note: mac doesn't have one
			case Gwen::CursorType::SizeAll:		[[NSCursor crosshairCursor] set];		break;
			case Gwen::CursorType::No:			[[NSCursor arrowCursor] set];			break; // note: mac doesn't have one
			case Gwen::CursorType::Wait:		[[NSCursor arrowCursor] set];			break; // note: mac doesn't have one
			case Gwen::CursorType::Finger:		[[NSCursor pointingHandCursor] set];	break;
			default: {
				ci::app::console() << __PRETTY_FUNCTION__ << " | could not find iCursor: " << (int) iCursor << std::endl;
				[[NSCursor arrowCursor] set];;
			}
		}
#else
		// TODO: windows is already done in gwen's Windows.cpp
#endif
	}

	void GetCursorPos( Gwen::Point & p )
	{
		// TODO: is there a cinder specific way to get this, without tying into GwenInput?
		
	}

	void GetDesktopSize( int & w, int & h )
	{
		ci::DisplayRef display = ci::app::getWindow()->getDisplay();
		w = display->getWidth();
		h = display->getHeight();
	}

	UnicodeString GetClipboardText()
	{
		return L""; // TODO
	}

	bool SetClipboardText( const UnicodeString & str )
	{
		return false; // TODO
	}

	float GetTimeInSeconds()
	{
		return ci::app::getElapsedSeconds();
	}

	bool FileOpen( const String & Name, const String & StartPath, const String & Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback )
	{
//		ci::app::getOpenFilePath();
		return false; // TODO
	}

	bool FileSave( const String & Name, const String & StartPath, const String & Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback )
	{
		return false; // TODO
	}

	bool FolderOpen( const String & Name, const String & StartPath, Gwen::Event::Handler* pHandler, Event::Handler::FunctionWithInformation fnCallback )
	{
		return false; // TODO
	}

	void *CreatePlatformWindow( int x, int y, int w, int h, const Gwen::String & strWindowTitle )
	{
		return NULL; // TODO
	}

	void DestroyPlatformWindow( void* pPtr )
	{
		// TODO
	}

	void SetBoundsPlatformWindow( void* pPtr, int x, int y, int w, int h )
	{
		// TODO
	}

	void MessagePump( void* pWindow, Gwen::Controls::Canvas* ptarget )
	{
		 // TODO
	}

	bool HasFocusPlatformWindow( void* pPtr )
	{
		return false; // TODO
	}

	void SetWindowMaximized( void* pPtr, bool bMaximized, Gwen::Point & pNewPos, Gwen::Point & pNewSize )
	{
		 // TODO
	}

	void SetWindowMinimized( void* pPtr, bool bMinimized )
	{
		 // TODO
	}

} } // namespace Gwen::Platform