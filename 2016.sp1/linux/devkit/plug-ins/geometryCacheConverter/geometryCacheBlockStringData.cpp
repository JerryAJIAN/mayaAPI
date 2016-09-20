//-
// ==========================================================================
// Copyright 2015 Autodesk, Inc.  All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================
//+

///////////////////////////////////////////////////////////////////////////////
//
// File Name : geometryCacheBlockStringData.cpp
//
// Description : 
//		Stores and outputs cache blocks that carry string data
//
///////////////////////////////////////////////////////////////////////////////

// Project includes
//
#include "geometryCacheBlockStringData.h"

///////////////////////////////////////////////////////////////////////////////
//
// Methods
//
///////////////////////////////////////////////////////////////////////////////

geometryCacheBlockStringData::geometryCacheBlockStringData( 
		const MString& tag, 
		const MString& value )
		: stringData( value )
///////////////////////////////////////////////////////////////////////////////
//
// Description : ( public method )
//		Constructor
//
///////////////////////////////////////////////////////////////////////////////
{
	blockTag = tag;
	group = false;
}

geometryCacheBlockStringData::~geometryCacheBlockStringData()
///////////////////////////////////////////////////////////////////////////////
//
// Description : ( public method )
//		Destructor
//
///////////////////////////////////////////////////////////////////////////////
{	
}

const MString& geometryCacheBlockStringData::data()
///////////////////////////////////////////////////////////////////////////////
//
// Description : ( public method )
//		Returns the block tag as an MString
//
///////////////////////////////////////////////////////////////////////////////
{	
	return stringData;
}

void geometryCacheBlockStringData::outputToAscii( ostream& os )
///////////////////////////////////////////////////////////////////////////////
//
// Description : ( public method )
//		Outputs the data of this block to Ascii
//
///////////////////////////////////////////////////////////////////////////////
{
	MString tabs = "";
	if( !group )
		tabs = "\t";

	os << tabs << "[" << blockTag << "]\n" << tabs << tabs <<
		stringData << "\n";
}
