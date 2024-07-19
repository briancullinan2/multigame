models/mapobjects/spotlamp1/spotlamp
{
	qer_editorimage map models/mapobjects/spotlamp1/spotlamp.tga
        cull disable
        surfaceparm alphashadow
        {
                map models/mapobjects/spotlamp/spotlamp.tga
                alphaFunc GE128
		depthWrite
		rgbGen vertex
        }


}

models/mapobjects/spotlamp1/beam
{
	qer_editorimage map models/mapobjects/spotlamp1/beam.tga
        surfaceparm trans	
        surfaceparm nomarks	
        surfaceparm nonsolid
	surfaceparm nolightmap
	cull none
        nomipmaps
	{
		map models/mapobjects/spotlamp/beam.tga
                tcMod Scroll .3 0
                blendFunc GL_ONE GL_ONE
        }
        //{
	//	map models/mapobjects/spotlamp/beam.tga
         //       tcMod Scroll -.3 0
         //       blendFunc GL_ONE GL_ONE
        //}
     
}

models/mapobjects/spotlamp1/beam_red
{
	surfaceparm trans	
        surfaceparm nomarks	
        surfaceparm nonsolid
	surfaceparm nolightmap
	cull none
        nomipmaps
	{
		map textures/sfx/beam_red.tga
                tcMod Scroll .3 0
                blendFunc GL_ONE GL_ONE
        }
        //{
	//	map textures/sfx/beam_red.tga
         //       tcMod Scroll -.3 0
         //       blendFunc GL_ONE GL_ONE
        //}
     
}

models/mapobjects/spotlamp1/beam_blue
{
        surfaceparm trans	
        surfaceparm nomarks	
        surfaceparm nonsolid
	surfaceparm nolightmap
	cull none
        nomipmaps
	{
		map models/mapobjects/spotlamp1/beam_blue.tga
                tcMod Scroll .3 0
                blendFunc GL_ONE GL_ONE
        }
        //{
	//	map models/mapobjects/spotlamp1/beam_blue.tga
         //       tcMod Scroll -.3 0
         //       blendFunc GL_ONE GL_ONE
        //}
     
}

models/mapobjects/spotlamp1/spotlamp_l
{
	qer_editorimage map models/mapobjects/spotlamp1.tga
        cull disable
        q3map_surfacelight	200

        {
                map models/mapobjects/spotlamp/spotlamp_l.tga
		rgbGen identity
        }


}

models/mapobjects/spotlamp1/spotlamp_lred
{
	qer_editorimage map textures/base_light/light1red.tga
      	cull disable
      	q3map_surfacelight	200

        {
                map textures/base_light/light1red.tga
		rgbGen identity
        }


}

models/mapobjects/spotlamp1/spotlamp_lblue
{
	qer_editorimage map textures/base_light/light1blue.tga
      	cull disable
      	q3map_surfacelight	200

        {
                map textures/base_light/light1blue.tga
		rgbGen identity
        }


}

