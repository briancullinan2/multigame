
textures/liquids/watertest
	{
		//	*************************************************
		//	* CALM GREEN WATER POOL Feb 19, 1998		*
		//	* IF YOU CHANGE THIS PLEASE COMMENT THE CHANGE	*
		//	*************************************************

		// Added to g3map_global texture on May 11, 1999
		qer_editorimage textures/liquids/pool2.tga
		qer_trans .5
		q3map_globaltexture

		surfaceparm trans
		surfaceparm nonsolid
		surfaceparm water
		surfaceparm nolightmap

		cull disable
		tesssize 64
	
    {
      map textures/common/invisible.tga
      alphaFunc GE128
      depthWrite
      rgbGen vertex
    }
	
  }

textures/common/transwater
	{
		//	*************************************************
		//	* CALM GREEN WATER POOL Feb 19, 1998		*
		//	* IF YOU CHANGE THIS PLEASE COMMENT THE CHANGE	*
		//	*************************************************

		// Added to g3map_global texture on May 11, 1999
		qer_editorimage textures/liquids/pool2.tga
		qer_trans .5
		q3map_globaltexture

		surfaceparm trans
		surfaceparm nonsolid
		surfaceparm water
		surfaceparm nolightmap

		cull disable
		tesssize 64
		deformVertexes wave 100 sin 1 1 1 .1
		
	
	
		{
			map textures/liquids/pool2.tga
			blendfunc GL_ONE GL_SRC_COLOR	
			tcMod scale .03 .03
			tcMod scroll .001 .001
		}
	
		{
			map textures/liquids/pool3d_3.tga
			blendfunc GL_DST_COLOR GL_ONE
			tcMod turb .1 .1 0 .01
			tcMod scale .5 .5
			tcMod scroll -.025 .02
		}


		//	END
	}

textures/sfx/blitzfog
//**************************************
//New death fog that must be in all maps with death fog
//**************************************
{
	qer_editorimage textures/sfx/hellfog.tga
	surfaceparm	trans
	surfaceparm	nonsolid
	surfaceparm	fog
	surfaceparm 	nodrop
	surfaceparm 	nolightmap
	q3map_globaltexture
	q3map_surfacelight 100
	fogparms ( .11 .11 .1 ) 1024
	
	

	
	{
		map textures/liquids/kc_fogcloud3.tga
		blendfunc gl_dst_color gl_zero
		tcmod scale -.05 -.05
		tcmod scroll .01 -.01
		rgbgen identity
	}

	{
		map textures/liquids/kc_fogcloud3.tga
		blendfunc gl_dst_color gl_zero
		tcmod scale .05 .05
		tcmod scroll .01 -.01
		rgbgen identity
	}
		
}


textures/common/sky1
{
	qer_editorimage textures/skies/myskydark.jpg
//	q3map_lightimage textures/skies/killsky_2.tga
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm nomarks
	q3map_surfacelight 50
//	q3map_surfacelight 130
//	q3map_sun 1 1 1 80 315 70
	skyParms textures/14gate_xt/env/filter 384 -
	{
		map textures/skies/myskydark.jpg
		blendfunc filter
		tcMod scroll 0.05 0.1
		tcMod scale 2 2
	}
}


textures/sfx/bouncepad01_diamond2cTGA
{
	qer_editorimage textures/sfx/bouncepad01_diamond2cTGA.tga
	//q3map_surfacelight 2000
	surfaceparm nodamage
	q3map_lightimage textures/sfx/jumppadsmall.tga	
	q3map_surfacelight 500

	
	{
		map textures/sfx/bouncepad01_diamond2cTGA.tga
		rgbGen identity
	}
	
	{
		map $lightmap
		rgbGen identity
		blendfunc gl_dst_color gl_zero
	}
	
	{
		map textures/sfx/bouncepad01b_layer1.tga
		blendfunc gl_one gl_one
		rgbGen wave sin .5 .5 0 1.5	
	}

	{
		clampmap textures/sfx/jumppadsmall.tga
		blendfunc gl_one gl_one
		tcMod stretch sin 1.2 .8 0 1.5
		rgbGen wave square .5 .5 .25 1.5
	}

	//	END
}
