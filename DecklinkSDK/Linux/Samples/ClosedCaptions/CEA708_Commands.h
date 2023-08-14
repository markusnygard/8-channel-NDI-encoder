/* -LICENSE-START-
 ** Copyright (c) 2016 Blackmagic Design
 **  
 ** Permission is hereby granted, free of charge, to any person or organization 
 ** obtaining a copy of the software and accompanying documentation (the 
 ** "Software") to use, reproduce, display, distribute, sub-license, execute, 
 ** and transmit the Software, and to prepare derivative works of the Software, 
 ** and to permit third-parties to whom the Software is furnished to do so, in 
 ** accordance with:
 ** 
 ** (1) if the Software is obtained from Blackmagic Design, the End User License 
 ** Agreement for the Software Development Kit (“EULA”) available at 
 ** https://www.blackmagicdesign.com/EULA/DeckLinkSDK; or
 ** 
 ** (2) if the Software is obtained from any third party, such licensing terms 
 ** as notified by that third party,
 ** 
 ** and all subject to the following:
 ** 
 ** (3) the copyright notices in the Software and this entire statement, 
 ** including the above license grant, this restriction and the following 
 ** disclaimer, must be included in all copies of the Software, in whole or in 
 ** part, and all derivative works of the Software, unless such copies or 
 ** derivative works are solely in the form of machine-executable object code 
 ** generated by a source language processor.
 ** 
 ** (4) THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 ** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 ** FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT 
 ** SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE 
 ** FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE, 
 ** ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 ** DEALINGS IN THE SOFTWARE.
 ** 
 ** A copy of the Software is available free of charge at 
 ** https://www.blackmagicdesign.com/desktopvideo_sdk under the EULA.
 ** 
 ** -LICENSE-END-
 */

#ifndef __CEA708_COMMANDS_H__
#define __CEA708_COMMANDS_H__
#include "CEA708_Types.h"
#include <stdint.h>

namespace CEA708
{

/* Defines the commands used to manipulate the CEA-708 (DTVCC) GUI.
 * References below refer to CEA-708.
 *
 * Refer to "8 DTVCC Interpretation Layer" for a high-level overview of how these commands influence the DTVCC Caption Components.
 */

// 7 DTVCC Coding Layer - Caption Data Services (Services 1 - 63)
class SyntacticElement
{
private:
	enum
	{
		kMaxElementLength = 7
	};
	uint8_t	m_buffer[kMaxElementLength];
	uint8_t	m_len;
	
public:
	explicit SyntacticElement(uint8_t len);

	uint8_t operator[](uint8_t i) const;
	uint8_t& operator[](uint8_t i);

	const uint8_t* data() const;
	uint8_t size() const;
};

// 8.9.3 Reset Command
SyntacticElement Reset();

// 8.10.4 Caption Text
SyntacticElement EndOfText();

// 8.10.5.1 SET CURRENT WINDOW - (CWx)
SyntacticElement SetCurrentWindow(WindowID windowID);

// 8.10.5.2 DEFINE WINDOW - (DF0 ... DF7)
SyntacticElement DefineWindow(WindowID windowID, Priority priority, Anchor anchorPoint, bool relativePositioning, uint8_t anchorVertical, uint8_t anchorHorizontal, uint8_t rowCount, uint8_t columnCount, bool rowLock, bool columnLock, bool visible, WindowStyle windowStyle, PenStyle penStyle);

// 8.10.5.4 DELETE WINDOWS - (DLW)
SyntacticElement DeleteWindows();

// 8.10.5.5 DISPLAY WINDOWS - (DSW)
SyntacticElement DisplayWindows(uint8_t windowMask);

// 8.10.5.6 HIDE WINDOWS - (HDW)
SyntacticElement HideWindows();

// 8.10.5.8 SET WINDOW ATTRIBUTES - (SWA)
SyntacticElement SetWindowAttributes(Justify justify, PrintDirection printDirection, ScrollDirection scrollDirection, bool wordwrap, DisplayEffect displayEffect, EffectDirection effectDirection, uint8_t effectSpeed, Colour fillColour, Opacity fillOpacity, BorderType borderType, Colour borderColour);

// 8.10.5.9 SET PEN ATTRIBUTES - (SPA)
SyntacticElement SetPenAttributes(PenSize penSize, Font font, TextTag textTag, TextOffset offset, bool italic, bool underline, EdgeType edgeType);

// 8.10.5.10 SET PEN COLOR - (SPC)
SyntacticElement SetPenColour(Colour foregroundColour, Opacity foregroundOpacity, Colour backgroundColour, Opacity backgroundOpacity, Colour edgeColour);

// 8.10.5.11 SET PEN LOCATION - (SPL)
SyntacticElement SetPenLocation(uint8_t row, uint8_t column);

}

#endif

