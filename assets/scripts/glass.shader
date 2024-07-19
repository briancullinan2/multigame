//**********************************
//   		GLASS    
//**********************************
//      Make sure you have the 3 glass textures in baseq3/textures/glass/ or this will not work.
//	darkglass.tga, blueglass.tga, plainglass.tga
//	MISC Glass types
// 	Best way to make glass is to create a brush with the NODRAW texture on all sides, then to select the face you want to
//	have the glass on and apply it.  The glass is viewable from both sides of the brush. 



//	Blue, bright glass.  Light swirl pattern to it.

textures/glass/blueglass
{
	surfaceparm nolightmap
	surfaceparm nonsolid
	cull twosided
	{
		map textures/glass/blueglass.tga
		tcGen environment
		tcMod turb 0 0.01 0 0.01	        
		tcmod scroll .0 .0
		blendfunc GL_ONE GL_ONE
                }
}

//	Foggy, stained glass with a cool chrome like finish when you walk by. 

textures/glass/darkglass
                      {
                      qer_trans .5
                      surfaceparm trans
		      surfaceparm solid
			surfaceparm glass

                      cull disable
                      {
                      map textures/effects/tinfx.tga
                      tcgen environment
                      blendfunc gl_one gl_one
                      rgbGen identity
                      }
                      {
                      map $lightmap
                      blendFunc gl_dst_color gl_zero
                      rgbgen identity
                      }
                      }

// 	Plain glass.

textures/glass/plainglass
{
	surfaceparm nolightmap
	surfaceparm nonsolid
	cull twosided
	{
		map textures/glass/plainglass.tga
		tcGen environment
		blendfunc GL_ONE GL_ONE
                }
}

textures/glass/darkglass2
{
	qer_trans .5
	surfaceparm trans
	surfaceparm nonsolid
	surfaceparm glass

	cull disable
	{
		map textures/glass/darkglass.tga
		tcgen environment
		blendfunc gl_one gl_one
		rgbGen identity
	}
	{
		map $lightmap
		blendFunc gl_dst_color gl_zero
		rgbgen identity
	}
}

//Created by Louie "KnightBK" Doulias for Black Knights Productions, Prisoners of War Q3 Mod.  
//Please check out our mod site at http://www.og-world.com/bkp/

//
// LADDERCLIP
//
textures/urban_terror/ladderclip
{
	qer_trans 0.40
	surfaceparm nolightmap
	surfaceparm nomarks
	surfaceparm nodraw
	surfaceparm nonsolid
	surfaceparm playerclip
	surfaceparm noimpact
	surfaceparm ladder
}


textures/ut_subway/subway_sky
{
	surfaceparm noimpact
	qer_editorimage textures/ut_subway/subway_sky_blend.tga
	surfaceparm nolightmap
	surfaceparm sky
//	q3map_skyambientlight 6
	q3map_sun 1.000000 0.947734 0.735540 225 300 60  //old values q3map_sun 1.0 0.947734 0.735540 75 300 60
	q3map_surfacelight 300 //old value 100
	q3map_globaltexture
	q3map_lightsubdivide 512
	skyparms env/ut_subway 256 -
}

