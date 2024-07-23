
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
	skyparms env/portalfog 256 -

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

textures/sfx2/bluegoal2
{
	surfaceparm nolightmap
	surfaceparm nonsolid
	surfaceparm trans
	cull twosided
	{
		map textures/sfx2/bluegoal2.tga
		tcGen environment
		tcmod scale 2 2
		blendfunc GL_ONE GL_ONE
		tcMod turb 0 0.25 0 0.5
	}
}

textures/sfx/swirl_b1
{
	deformVertexes wave 100 sin 1 2 .1 1
	q3map_surfacelight	300

	surfaceparm	trans
	surfaceparm nomarks
	surfaceparm nolightmap
	surfaceparm nonsolid
	cull none
	
	{
		clampmap textures/sfx/swirl_b1.tga
		blendFunc GL_ONE GL_ONE
		tcMod rotate -188
	}	
	{
		clampmap textures/sfx/swirl_b2.tga
		blendFunc GL_ONE GL_ONE
		tcMod rotate 333
	}
	//{
		//	clampmap textures/sfx/swirl_b2.tga
		//	blendFunc GL_ONE GL_ONE
		//        tcMod rotate 20
	//}
	
}

textures/skies2/nebula2
{
	qer_editorimage textures/skies2/nebula3.tga
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm sky
	q3map_lightimage textures/skies/stars.tga
	q3map_sun	.90 .90 .95 80 315 40	
	q3map_surfacelight 60
	
	skyparms textures/skies2/env/nebula2 - -
	
}


textures/common/portal
{
	qer_editorimage textures/common/qer_portal.tga
	portal
	surfaceparm nolightmap
	surfaceparm nomarks
	surfaceparm nodamage
	{
		map textures/common/mirror1.tga
		tcMod turb 0 0.25 0 0.05
		blendfunc GL_ONE GL_ONE_MINUS_SRC_ALPHA
		depthWrite
		alphagen portal 512
	}
}



textures/skies/tim_hell
{
	qer_editorimage textures/skies/stars_red.tga
	surfaceparm noimpact
	surfaceparm nomarks
	surfaceparm nolightmap
	surfaceparm sky

	q3map_sun 1 .77 .77 80 315 70
	//q3map_sun .5 .37 .19 80 315 70

	//q3map_sun 1 .37 .19 85 30 70
	q3map_surfacelight 130
	skyparms - 384 -

	//cloudparms 512 full
	//lightning

	{
		map textures/skies/killsky_1.tga
		tcMod scroll 0.05 .1
		tcMod scale 2 2
		depthWrite
	}
	{
		map textures/skies/killsky_2.tga
		blendfunc GL_ONE GL_ONE
		tcMod scroll 0.05 0.06
		tcMod scale 3 2
	}
}


