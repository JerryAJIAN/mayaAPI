#ifndef _hwDecalBumpShader_NV20
#define _hwDecalBumpShader_NV20

//-
// ==========================================================================
// Copyright (C) 1995 - 2006 Autodesk, Inc. and/or its licensors.  All 
// rights reserved.
//
// The coded instructions, statements, computer programs, and/or related 
// material (collectively the "Data") in these files contain unpublished 
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its 
// licensors, which is protected by U.S. and Canadian federal copyright 
// law and by international treaties.
//
// The Data is provided for use exclusively by You. You have the right 
// to use, modify, and incorporate this Data into other products for 
// purposes authorized by the Autodesk software license agreement, 
// without fee.
//
// The copyright notices in the Software and this entire statement, 
// including the above license grant, this restriction and the 
// following disclaimer, must be included in all copies of the 
// Software, in whole or in part, and all derivative works of 
// the Software, unless such copies or derivative works are solely 
// in the form of machine-executable object code generated by a 
// source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED 
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF 
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
// PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE, OR 
// TRADE PRACTICE. IN NO EVENT WILL AUTODESK AND/OR ITS LICENSORS 
// BE LIABLE FOR ANY LOST REVENUES, DATA, OR PROFITS, OR SPECIAL, 
// DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK 
// AND/OR ITS LICENSORS HAS BEEN ADVISED OF THE POSSIBILITY 
// OR PROBABILITY OF SUCH DAMAGES.
//
// ==========================================================================
//+

///////////////////////////////////////////////////////////////////
//
// NOTE: PLEASE READ THE README.TXT FILE FOR INSTRUCTIONS ON
// COMPILING AND USAGE REQUIREMENTS.
//
// DESCRIPTION: NV20-specific (Geforce3) sample shader.
//				This shader can simultaneously display both decal 
//				(base color) and bump textures.
//
//  This shader builds on the foundation demonstrated in the 
//  hwUnlitShader.
//
//	Additionally, this sample demonstrates how to:
//		- Use vendor-specific extensions, namely vertex programs,
//		  texture shaders and register combiners, to achieve
//		  effects that are impossible in standard OpenGL.
//		- Convert height field bump format (used by Maya) into
//		  a normal map format, for real-time rendering.
//
//  Many parameters are easily customizable:
//		- The MNormalMapConverter::convertToNormalMap_InPlace()
//        bumpScale parameter is currently constant. You can change
//		  it to a different value to increase or decrease the 
//		  bumpiness.
//
///////////////////////////////////////////////////////////////////

#include <maya/MPxHwShaderNode.h>
#include "MTextureCache.h"


class hwDecalBumpShader_NV20 : public MPxHwShaderNode
{
public:
                    hwDecalBumpShader_NV20();
    virtual         ~hwDecalBumpShader_NV20();
	void			releaseEverything();

    virtual MStatus compute( const MPlug&, MDataBlock& );
	virtual void    postConstructor();

	virtual MStatus	bind(const MDrawRequest& request,
						 M3dView& view);

	virtual MStatus	unbind(const MDrawRequest& request,
						   M3dView& view);

	virtual MStatus	geometry( const MDrawRequest& request,
							  M3dView& view,
							  int prim,
							  unsigned int writable,
							  int indexCount,
							  const unsigned int * indexArray,
							  int vertexCount,
							  const int * vertexIDs,
							  const float * vertexArray,
							  int normalCount,
							  const float ** normalArrays,
							  int colorCount,
							  const float ** colorArrays,
							  int texCoordCount,
							  const float ** texCoordArrays);

	virtual int		normalsPerVertex();

	virtual int		texCoordsPerVertex();

    static  void *  creator();
    static  MStatus initialize();
    static  MTypeId id;

	MTextureCache	*m_pTextureCache;

	void			loadVertexProgramGL();
	float*			computeBinormals(int indexCount, const unsigned int * indexArray, 
									 int vertexCount, const float* vertexArray, 
									 const float* normalsArray, 
									 const float* texCoordsArray);

	GLuint			vertex_program_id;		// handle for the Vertex Program

	void			printGlError( const char *call );

	void			init_ext(const char *ext);
	MStatus			getFloat3(MObject colorAttr, float colorValue[3]);
	MStatus			getString(MObject attr, MString &str);

	vec3f			lightRotation;
	vec3f			cameraPos;

	boolean			isDirectionalLight;	// when light's rotation is on the lightPos attr

protected:
    static MObject  colorR;
	static MObject  colorG;
	static MObject  colorB;
	static MObject  color;
    static MObject  bumpR;
	static MObject  bumpG;
	static MObject  bumpB;
	static MObject  bump;
	static MObject	lightX;
	static MObject	lightY;
	static MObject	lightZ;
	static MObject	light;
	static MObject	cameraX;
	static MObject	cameraY;
	static MObject	cameraZ;
	static MObject	camera;
    static MObject  uCoord;
	static MObject  vCoord;
	static MObject  uvCoord;
    static MObject  uBias;
	static MObject  vBias;
    static MObject  uvFilterSize;
    static MObject  uvFilterSizeX;
    static MObject  uvFilterSizeY;

    static MObject  shininess;
	static MObject  lightColorR;
	static MObject  lightColorG;
	static MObject  lightColorB;
	static MObject  lightColor;

	static MObject  decalTextureName;
	static MObject	bumpTextureName;

// CURRENTLY UNUSED:    
//	static MObject  bumpScale;
//  static MObject  heightfieldMap;

	// Shininess value/scale, used to generate the lookup texture.
	float currentShininessValue, currentShininessScale;
	tex_object_2D *lookup_texture;
	unsigned char *lookup_table;
	static const unsigned int lookup_texture_size;
	bool fLookupTextureReprocessed;

	// Create the look-up texture.
	// This texture encodes the diffuse (u-axis) and
	// specular (v-axis) coefficients of the blinn equation.
	// This function will automatically set the fLookupTextureReprocessed
	// flag if the texture changed and need to be reloaded by OpenGL.
	void make_lookup_texture();

	// Bind the look-up texture in the current GL texture unit.
	// This function automatically calls make_lookup_texture,
	// and reloads the texture in video memory if it needs to.
	void bind_lookup_table();

	// Release the memory occupied by the look-up texture.
	void release_lookup_texture();

	// Callbacks that we monitor so we can release OpenGL-dependant resources before
	// their context gets destroyed.
	MCallbackId fBeforeNewCB;
	MCallbackId fBeforeOpenCB;
	MCallbackId fBeforeRemoveReferenceCB;
	MCallbackId fMayaExitingCB;

	void attachSceneCallbacks();
	void detachSceneCallbacks();

	static void releaseCallback(void* clientData);
};

#endif /* _hwDecalBumpShader_NV20 */
