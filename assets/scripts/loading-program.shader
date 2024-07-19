
textures/skies/portalfog
{
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm sky

	qer_editorimage textures/skies/portalfog.tga

	q3map_surfacelight 400
	q3map_sun	1 1 0.5 150	30 60
//	q3map_sun	1 1 0.5 150	200 85
	skyparms - 512 -

	{
		map textures/skies/portalfog.tga
		tcMod scroll 0.1 0.1
		tcMod scale 3 2
		depthWrite
	}
	{
		map textures/skies/portalfog.tga
		blendFunc GL_ONE GL_ONE
		tcMod scroll 0.05 0.05
		tcMod scale 3 3
	}
}

textures/sfx/fog3
{
	qer_editorimage textures/sfx/fog_grey.tga
	surfaceparm fog
	surfaceparm nolightmap
	surfaceparm nonsolid
	surfaceparm trans
	fogparms ( 0.9 0.9 0.9 ) 4096
	{
		map textures/liquids/kc_fogcloud3.tga
		blendfunc filter
		rgbGen identity
		tcMod scale -0.05 -0.05
		tcMod scroll 0.01 -0.01
	}
	{
		map textures/liquids/kc_fogcloud3.tga
		blendfunc filter
		rgbGen identity
		tcMod scale 0.05 0.05
		tcMod scroll 0.01 -0.01
	}
}
