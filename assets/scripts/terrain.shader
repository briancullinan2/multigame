//	*************************************************
//	*      	
//	*   Vertex Lighting Replacement Shaders
//	*	
//	*************************************************

textures/liquids/calm_poollight2
{
	//	*************************************************
	//	* CALM GREEN WATER POOL may 5 1999
	//    * same as calm water but emits light		*
	//	* IF YOU CHANGE THIS PLEASE COMMENT THE CHANGE	*
	//	*************************************************

	
	qer_editorimage textures/liquids/pool3d_4b.tga
	q3map_globaltexture
	qer_trans .75

	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm water
	surfaceparm nolightmap
	q3map_surfacelight 50

	cull disable
	tesssize 512
	deformVertexes wave 100 sin 1 1 1 .1
	
	
	
	{ 
		map textures/liquids/pool3d_5c2.tga
		blendFunc GL_dst_color GL_zero
		rgbgen identity
		tcmod scale .5 .5
		tcmod transform 1.5 0 1.5 1 1 2
		tcmod scroll -.05 .001
	}
	
	{ 
		map textures/liquids/pool3d_6c2.tga
		blendFunc GL_dst_color GL_zero
		rgbgen identity
		tcmod scale .5 .5
		tcmod transform 0 1.5 1 1.5 2 1
		tcmod scroll .025 -.001
	}

	{ 
		map textures/liquids/pool3d_3c2.tga
		blendFunc GL_dst_color GL_zero
		rgbgen identity
		tcmod scale .25 .5
		tcmod scroll .001 .025
	}
	{
		map textures/liquids/pool3d_4b2.tga
		blendfunc add
		tcmod scale .125 .125	
		rgbgen identity
	}


	//	END
}


textures/skies/terrain1
//used terrain ctf map

{
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm sky

	q3map_sun	1.1 .5 .7 60 130 100
	q3map_surfacelight 55

	qer_editorimage textures/skies/toxicbluesky.tga

	skyparms - 512 -
	
	{
		map textures/skies/bluedimclouds.tga
		tcMod scale 3 2
		tcMod scroll 0.15 0.15
		depthWrite
	}
	{
		map textures/skies/topclouds.tga
		blendFunc GL_ONE GL_ONE
		tcMod scale 3 3
		tcMod scroll 0.05 0.05
	}
}

textures/terrain/vxmpterra2

{
	qer_editorimage textures/stone/pjrock9b_2.tga
	surfaceparm nolightmap
	q3map_novertexshadows
	q3map_forcesunlight


	{

		map textures/stone/pjrock10b_2.tga
		rgbGen vertex
		tcmod scale 0.125 0.125
	}
	
}


textures/terrain/vxmpterra1

{
	qer_editorimage textures/stone/pjrock12c.tga
	surfaceparm nolightmap
	q3map_novertexshadows
	q3map_forcesunlight


	{

		map textures/stone/pjrock12c.tga
		rgbGen vertex
		tcmod scale 0.125 0.125
	}
	
}

textures/terrain/vxmpterra4

{
	qer_editorimage textures/stone/pjrock12c.tga
	surfaceparm nolightmap
	q3map_novertexshadows
	q3map_forcesunlight


	{

		map textures/stone/pjrock12c.tga
		rgbGen vertex
		tcmod scale 0.125 0.125
	}
	
}

// *********************************************************

//	*************************************************
//	*      	
//	*   MPTerra2 terrain shaders (PaulJ)
//	*	
//	*************************************************


textures/terrain/mpterra2_0

{
	qer_editorimage textures/stone/pjrock9b_2.tga
	surfaceparm nolightmap
	q3map_novertexshadows
	q3map_forcesunlight

	{

		map textures/stone/pjrock9b_2.tga
		rgbGen vertex
		tcmod scale 0.125 0.125
	}
	
	{

		map textures/skies2/clouds.tga
		blendfunc filter
		detail
		tcmod scale 0.01 0.01
		tcMod scroll -0.05 0.05
		tcmod transform 1 0 1 1 1 1
		
	}

	
}

textures/terrain/mpterra2_1

{
	qer_editorimage textures/stone/pjrock12b_2.tga
	surfaceparm nolightmap
	q3map_novertexshadows
	q3map_forcesunlight

	{
		
		map textures/stone/pjrock12b_2.tga
		rgbGen vertex
		tcmod scale 0.1 0.1
		
	}

	{
		
		map textures/skies2/clouds.tga
		blendfunc filter
		detail
		tcmod scale 0.01 0.01
		tcMod scroll -0.05 0.05
		tcmod transform 1 0 1 1 1 1
		
	}


}

textures/terrain/mpterra2_2
{
	qer_editorimage textures/stone/pjrock10b_2.tga
	surfaceparm nolightmap
	q3map_novertexshadows
	q3map_forcesunlight

	{
		
		map textures/stone/pjrock10b_2.tga
		tcmod scale 0.05 0.05
		rgbGen vertex
	}

	{
		map textures/skies2/clouds.tga
		blendfunc filter
		detail
		tcmod scale 0.01 0.01
		tcMod scroll -0.05 0.05
		tcmod transform 1 0 1 1 1 1
		
	}

}

textures/terrain/mpterra2_0to1

{
	qer_editorimage textures/stone/pjrock9b_2.tga
	surfaceparm nolightmap
	q3map_novertexshadows
	q3map_forcesunlight

	{
		map textures/stone/pjrock9b_2.tga
		rgbGen vertex
		alphaGen vertex
		tcmod scale 0.125 0.125 
	}

	{
		map textures/stone/pjrock12b_2.tga
		tcmod scale 0.1 0.1
		rgbGen vertex
		alphaGen vertex
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}

	{
		map textures/skies2/clouds.tga
		blendfunc filter
		detail
		tcmod scale 0.01 0.01
		tcMod scroll -0.05 0.05
		tcmod transform 1 0 1 1 1 1		
	}


}

textures/terrain/mpterra2_0to2
{
	qer_editorimage textures/stone/pjrock9b_2.tga
	surfaceparm nolightmap
	q3map_novertexshadows
	q3map_forcesunlight
	{
		map textures/stone/pjrock9b_2.tga
		rgbGen vertex
		alphaGen vertex
		tcmod scale 0.125 0.125
	}
	{
		map textures/stone/pjrock10b_2.tga
		rgbGen vertex
		alphaGen vertex
		tcmod scale 0.05 0.05
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}

	{
		map textures/skies2/clouds.tga
		blendfunc filter
		detail
		tcmod scale 0.01 0.01
		tcMod scroll -0.05 0.05
		tcmod transform 1 0 1 1 1 1
		
	}


}

textures/terrain/mpterra2_1to2
{
	qer_editorimage textures/stone/pjrock12b_2.tga
	surfaceparm nolightmap
	q3map_novertexshadows
	q3map_forcesunlight

	{
		map textures/stone/pjrock12b_2.tga
		rgbGen vertex
		alphaGen vertex
		tcmod scale 0.1 0.1
	}

	{
		map textures/stone/pjrock10b_2.tga
		tcmod scale 0.05 0.05
		rgbGen vertex
		alphaGen vertex
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}

	{
		map textures/skies2/clouds.tga
		blendfunc filter
		detail
		tcmod scale 0.01 0.01
		tcMod scroll -0.05 0.05
		tcmod transform 1 0 1 1 1 1
	}


}

//////////////////////////////////////////////
//                                          //
//                x_mpterra                 //
//                                          //
//////////////////////////////////////////////

textures/terrain/vxmpterra3

{
	qer_editorimage textures/proto2/px02.tga
	surfaceparm nolightmap
	//q3map_novertexshadows
	//q3map_forcesunlight	
	surfaceparm dust
	{
		map textures/proto2/px02.tga
		tcmod scale .1 .1
		rgbGen vertex
	}

}



textures/proto2/xproto_0to1

{
	qer_editorimage textures/proto2/px01.tga
	surfaceparm nolightmap
	//q3map_novertexshadows
	//q3map_forcesunlight	
	surfaceparm dust

	{
		map textures/proto2/px01.tga
		tcmod scale .1 .1
		rgbGen vertex
		
	}

	{
		map textures/proto2/px02.tga
		rgbGen vertex
		alphaGen vertex
		tcmod scale .1 .1
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
	
	
}

textures/proto2/xproto_1to2

{
	qer_editorimage textures/proto2/px02.tga
	surfaceparm nolightmap
	//q3map_novertexshadows
	//q3map_forcesunlight	
	surfaceparm dust
	{
		map textures/proto2/px02.tga
		tcmod scale .1 .1
		rgbGen vertex
		alphaGen vertex
	}

	{
		map textures/proto2/px03.tga
		rgbGen vertex
		alphaGen vertex
		tcmod scale .1 .1
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}


}

textures/proto2/xproto_0to2

{
	qer_editorimage textures/proto2/px02.tga
	surfaceparm nolightmap
	//q3map_novertexshadows
	//q3map_forcesunlight	
	surfaceparm dust

	{
		map textures/proto2/px01.tga
		tcmod scale .1 .1
		rgbGen vertex
	}
	{
		map textures/proto2/px03.tga
		rgbGen vertex
		alphaGen vertex
		tcmod scale .1 .1
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}


}



textures/proto2/xproto_0

{
	qer_editorimage textures/proto2/px01.tga
	surfaceparm nolightmap
	//q3map_novertexshadows
	//q3map_forcesunlight	
	surfaceparm dust


	{
		map textures/proto2/px01.tga
		tcmod scale .1 .1
		rgbGen vertex
	}

	

}

textures/proto2/xproto_1

{
	qer_editorimage textures/proto2/px02.tga
	surfaceparm nolightmap
	//q3map_novertexshadows
	//q3map_forcesunlight	
	surfaceparm dust
	{
		map textures/proto2/px02.tga
		tcmod scale .1 .1
		rgbGen vertex
	}
	
	
	
}

textures/proto2/xproto_2

{
	qer_editorimage textures/proto2/px03.tga
	surfaceparm nolightmap
	//q3map_novertexshadows
	//q3map_forcesunlight	
	surfaceparm dust
	{
		map textures/proto2/px03.tga
		tcmod scale .1 .1
		rgbGen vertex
	}

}



//	*************************************************
//	*      	
//	*   MPTerra1 terrain shaders (Tim)
//	*	
//	*************************************************

textures/terrain/mpterra1_0
{
	qer_editorimage textures/stone/pjrock9c.tga
	surfaceparm nolightmap
	q3map_novertexshadows
	q3map_forcesunlight	
	{
		map textures/stone/pjrock9c.tga
		rgbGen vertex
		tcmod scale 0.125 0.125
	}
	{
		map textures/skies2/clouds2.tga
		blendfunc filter
		tcmod scale 0.01 0.01
		tcMod scroll -0.1 0.1
		
	}
	
}

textures/terrain/mpterra1_1
{
	qer_editorimage textures/stone/pjrock12c.tga
	surfaceparm nolightmap
	q3map_novertexshadows
	q3map_forcesunlight	
	{
		map textures/stone/pjrock12c.tga
		//tcmod transform 1 0 1 1 1 1
		rgbGen vertex
		tcmod scale 0.125 0.125 
	}
	{
		map textures/skies2/clouds2.tga
		blendfunc filter
		tcmod scale 0.01 0.01
		tcMod scroll -0.1 0.1
		
	}

}

textures/terrain/mpterra1_2
{
	qer_editorimage textures/stone/pjrock10c.tga
	surfaceparm nolightmap
	q3map_novertexshadows
	q3map_forcesunlight	
	{
		map textures/stone/pjrock10c.tga
		tcmod scale 0.05 0.05 
		rgbGen vertex
	}
	{
		map textures/skies2/clouds2.tga
		blendfunc filter
		tcmod scale 0.01 0.01
		tcMod scroll -0.1 0.1
		
	}

}

textures/terrain/mpterra1_0to1
{
	qer_editorimage textures/stone/pjrock9c.tga
	surfaceparm nolightmap
	q3map_novertexshadows
	q3map_forcesunlight	
	{
		map textures/stone/pjrock9c.tga	
		rgbGen vertex
		alphaGen vertex
		tcmod scale 0.125 0.125 
	}
	{
		map textures/stone/pjrock12c.tga
		tcmod scale 0.125 0.125 
		rgbGen vertex
		alphaGen vertex
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
	{
		map textures/skies2/clouds2.tga
		blendfunc filter
		tcmod scale 0.01 0.01
		tcMod scroll -0.1 0.1
		
	}

}

textures/terrain/mpterra1_0to2
{
	qer_editorimage textures/stone/pjrock9c.tga
	surfaceparm nolightmap
	q3map_novertexshadows
	q3map_forcesunlight	
	{
		map textures/stone/pjrock9c.tga
		rgbGen vertex
		alphaGen vertex
		tcmod scale 0.125 0.125
	}
	{
		map textures/stone/pjrock10c.tga
		//tcmod transform 1 0 1 1 1 1
		tcmod scale 0.05 0.05 
		rgbGen vertex
		alphaGen vertex
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
	{
		map textures/skies2/clouds2.tga
		blendfunc filter
		tcmod scale 0.01 0.01
		tcMod scroll -0.1 0.1
		
	}

}

textures/terrain/mpterra1_1to2
{
	qer_editorimage textures/stone/pjrock12c.tga
	surfaceparm nolightmap
	q3map_novertexshadows
	q3map_forcesunlight	
	{
		map textures/stone/pjrock12c.tga
		rgbGen vertex
		alphaGen vertex
		tcmod scale 0.125 0.125 
	}
	{
		map textures/stone/pjrock10c.tga
		//tcmod transform 1 0 1 1 1 1
		tcmod scale 0.05 0.05 
		rgbGen vertex
		alphaGen vertex
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
	{
		map textures/skies2/clouds2.tga
		blendfunc filter
		tcmod scale 0.01 0.01
		tcMod scroll -0.1 0.1
		
	}
}




//	*************************************************
//	*      	
//	*   MPTerra1 terrain shaders (Tim)
//	*	
//	*************************************************

textures/terrain/mpterra4_0
{
	qer_editorimage textures/stone/pjrock9c.tga
	surfaceparm nolightmap
	surfaceparm terrain
	q3map_novertexshadows
	q3map_forcesunlight	
	{
		map textures/stone/pjrock9c.tga
		rgbGen vertex
		tcmod scale 0.125 0.125
	}
	{
		map textures/skies2/clouds2.tga
		blendfunc filter
		tcmod scale 0.01 0.01
		tcMod scroll -0.1 0.1
		
	}
	
}

textures/terrain/mpterra4_1
{
	qer_editorimage textures/stone/pjrock12c.tga
	surfaceparm nolightmap
	surfaceparm terrain
	q3map_novertexshadows
	q3map_forcesunlight	
	{
		map textures/stone/pjrock12c.tga
		//tcmod transform 1 0 1 1 1 1
		rgbGen vertex
		tcmod scale 0.125 0.125 
	}
	{
		map textures/skies2/clouds2.tga
		blendfunc filter
		tcmod scale 0.01 0.01
		tcMod scroll -0.1 0.1
		
	}

}

textures/terrain/mpterra4_2
{
	qer_editorimage textures/stone/pjrock10c.tga
	surfaceparm nolightmap
	surfaceparm terrain
	q3map_novertexshadows
	q3map_forcesunlight	
	{
		map textures/stone/pjrock10c.tga
		tcmod scale 0.05 0.05 
		rgbGen vertex
	}
	{
		map textures/skies2/clouds2.tga
		blendfunc filter
		tcmod scale 0.01 0.01
		tcMod scroll -0.1 0.1
		
	}

}

textures/terrain/mpterra4_0to1
{
	qer_editorimage textures/stone/pjrock912c.tga
	surfaceparm nolightmap
	surfaceparm terrain
	q3map_novertexshadows
	q3map_forcesunlight	
	{
		map textures/stone/pjrock9c.tga	
		rgbGen vertex
		alphaGen vertex
		tcmod scale 0.125 0.125 
	}
	{
		map textures/stone/pjrock12c.tga
		tcmod scale 0.125 0.125 
		rgbGen vertex
		alphaGen vertex
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
	{
		map textures/skies2/clouds2.tga
		blendfunc filter
		tcmod scale 0.01 0.01
		tcMod scroll -0.1 0.1
		
	}

}

textures/terrain/mpterra4_0to2
{
	qer_editorimage textures/stone/pjrock9c.tga
	surfaceparm nolightmap
	surfaceparm terrain
	q3map_novertexshadows
	q3map_forcesunlight	
	{
		map textures/stone/pjrock9c.tga
		rgbGen vertex
		alphaGen vertex
		tcmod scale 0.125 0.125
	}
	{
		map textures/stone/pjrock10c.tga
		//tcmod transform 1 0 1 1 1 1
		tcmod scale 0.05 0.05 
		rgbGen vertex
		alphaGen vertex
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
	{
		map textures/skies2/clouds2.tga
		blendfunc filter
		tcmod scale 0.01 0.01
		tcMod scroll -0.1 0.1
		
	}

}

textures/terrain/mpterra4_1to2
{
	qer_editorimage textures/stone/pjrock1210c.tga
	surfaceparm nolightmap
	surfaceparm terrain
	q3map_novertexshadows
	q3map_forcesunlight	
	{
		map textures/stone/pjrock12c.tga
		rgbGen vertex
		alphaGen vertex
		tcmod scale 0.125 0.125 
	}
	{
		map textures/stone/pjrock10c.tga
		//tcmod transform 1 0 1 1 1 1
		tcmod scale 0.05 0.05 
		rgbGen vertex
		alphaGen vertex
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
	{
		map textures/skies2/clouds2.tga
		blendfunc filter
		tcmod scale 0.01 0.01
		tcMod scroll -0.1 0.1
		
	}
}

textures/liquids2/calm_poollight2nt
{


	
	qer_editorimage textures/liquids/pool3d_4b.tga
	q3map_globaltexture
	qer_trans .75

	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm water
	surfaceparm nolightmap
	q3map_surfacelight 50

	cull disable
	
	
	
	{ 
		map textures/liquids/pool3d_5c2.tga
		blendFunc GL_dst_color GL_zero
		rgbgen identity
		tcmod scale .5 .5
		tcmod transform 1.5 0 1.5 1 1 2
		tcmod scroll -.05 .001
	}
	
	{ 
		map textures/liquids/pool3d_6c2.tga
		blendFunc GL_dst_color GL_zero
		rgbgen identity
		tcmod scale .5 .5
		tcmod transform 0 1.5 1 1.5 2 1
		tcmod scroll .025 -.001
	}

	{ 
		map textures/liquids/pool3d_3c2.tga
		blendFunc GL_dst_color GL_zero
		rgbgen identity
		tcmod scale .25 .5
		tcmod scroll .001 .025
	}
	{
		map textures/liquids/pool3d_4b2.tga
		blendfunc add
		tcmod scale .125 .125	
		rgbgen identity
	}


	//	END
}


textures/liquids/x_calm_pool_nolight
{
	//	*************************************************
	//	* CALM GREEN WATER POOL oct.6.2000
	//    * same as calm water but emits NO light -Xian	*
	//	* IF YOU CHANGE THIS PLEASE COMMENT THE CHANGE	*
	//	*************************************************

	
	qer_editorimage textures/liquids/pool3d_4b.tga
	q3map_globaltexture
	qer_trans .75

	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm water
	surfaceparm nolightmap

	cull disable
	tesssize 256
	deformVertexes wave 100 sin 1 1 1 .1
	
	
	
	{ 
		map textures/liquids/pool3d_5c2.tga
		blendFunc GL_dst_color GL_zero
		rgbgen identity
		tcmod scale .5 .5
		tcmod transform 1.5 0 1.5 1 1 2
		tcmod scroll -.05 .001
	}
	
	{ 
		map textures/liquids/pool3d_6c2.tga
		blendFunc GL_dst_color GL_zero
		rgbgen identity
		tcmod scale .5 .5
		tcmod transform 0 1.5 1 1.5 2 1
		tcmod scroll .025 -.001
	}

	{ 
		map textures/liquids/pool3d_3c2.tga
		blendFunc GL_dst_color GL_zero
		rgbgen identity
		tcmod scale .25 .5
		tcmod scroll .001 .025
	}
	{
		map textures/liquids/pool3d_4b2.tga
		blendfunc add
		tcmod scale .125 .125	
		rgbgen identity
	}


	//	END
}



textures/liquids/calm_pool_nolight
{
	//	*************************************************
	//	* CALM GREEN WATER POOL oct.6.2000
	//    * same as calm water but emits NO light -Xian	*
	//	* IF YOU CHANGE THIS PLEASE COMMENT THE CHANGE	*
	//	*************************************************

	
	qer_editorimage textures/liquids/pool3d_4b.tga
	q3map_globaltexture
	qer_trans .75

	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm water
	surfaceparm nolightmap

	cull disable
	tesssize 64
	deformVertexes wave 100 sin 1 1 1 .1
	
	
	
	{ 
		map textures/liquids/pool3d_5c2.tga
		blendFunc GL_dst_color GL_zero
		rgbgen identity
		tcmod scale .5 .5
		tcmod transform 1.5 0 1.5 1 1 2
		tcmod scroll -.05 .001
	}
	
	{ 
		map textures/liquids/pool3d_6c2.tga
		blendFunc GL_dst_color GL_zero
		rgbgen identity
		tcmod scale .5 .5
		tcmod transform 0 1.5 1 1.5 2 1
		tcmod scroll .025 -.001
	}

	{ 
		map textures/liquids/pool3d_3c2.tga
		blendFunc GL_dst_color GL_zero
		rgbgen identity
		tcmod scale .25 .5
		tcmod scroll .001 .025
	}
	{
		map textures/liquids/pool3d_4b2.tga
		blendfunc add
		tcmod scale .125 .125	
		rgbgen identity
	}


	//	END
}

