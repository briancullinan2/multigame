//
//http://www.planetquake.com/speedy    ... author of andromeda texture pack
//

textures/rota3ctf1_lights/u_trlightline3
{
	qer_editorimage textures/rota3ctf1_lights/u_trlightline3.tga
	q3map_lightimage textures/rota3ctf1_lights/u_trlightline_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_lights/u_trlightline3.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_trlightline_blend.tga
		blendfunc gl_dst_color gl_one
		rgbGen wave sawtooth 0.6 0.1 0 7 
	}
}

textures/rota3ctf1_lights/u_trlightline2_or
{
	qer_editorimage textures/rota3ctf1_lights/u_trlightline2_or.tga
	q3map_lightimage textures/rota3ctf1_lights/u_trlightline2_or_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_lights/u_trlightline2_or.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_trlightline2_or_blend.tga
		blendfunc add
		rgbGen wave sawtooth 0.7 0.1 0 7 
	}
}

textures/rota3ctf1_lights/u_trlightline_or
{
	qer_editorimage textures/rota3ctf1_lights/u_trlightline_or.tga
	q3map_lightimage textures/rota3ctf1_lights/u_trlightline2_or_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_lights/u_trlightline_or.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_trlightline2_or_blend.tga
		blendfunc add
		rgbGen wave sawtooth 0.6 0.1 0 7 
	}
}

textures/rota3ctf1_lights/u_trlightline_blue
{
	qer_editorimage textures/rota3ctf1_lights/u_trlightline_blue.tga
	q3map_lightimage textures/rota3ctf1_lights/u_trlightline_blue_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_lights/u_trlightline_blue.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_trlightline_blue_blend.tga
		blendfunc add
		rgbGen wave sawtooth 0.6 0.1 0 7 
	}
}

textures/rota3ctf1_lights/u_trlightline
{
	qer_editorimage textures/rota3ctf1_lights/u_trlightline.tga
	q3map_lightimage textures/rota3ctf1_lights/u_trlightline_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_lights/u_trlightline.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_trlightline_blend.tga
		blendfunc add
		rgbGen wave sawtooth 0.6 0.1 0 7 
	}
}

textures/rota3ctf1_lights/u_lamp1
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp1.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2200
	{
		map textures/rota3ctf1_lights/u_lamp1.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
	}
}

textures/rota3ctf1_lights/u_lamp1b
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp1b.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2200
	{
		map textures/rota3ctf1_lights/u_lamp1b.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
	}
}

textures/rota3ctf1_lights/u_lamp2
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp2.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2200
	{
		map textures/rota3ctf1_lights/u_lamp2.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp_blend.tga
		blendfunc add
		tcMod rotate 33
	}
}

textures/rota3ctf1_lights/u_lamp2_64
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp2_64.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp2_64_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2200
	{
		map textures/rota3ctf1_lights/u_lamp2_64.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp2_64_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
	}
}

textures/rota3ctf1_lights/u_lamp1_64
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp1_64.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp2_64_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2200
	{
		map textures/rota3ctf1_lights/u_lamp1_64.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp2_64_blend.tga
		blendfunc gl_dst_color gl_one
		rgbGen wave noise 0.7 0.3 13 1 
	}
}

textures/rota3ctf1_lights/u_lamp3
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp3.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp3_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 10000
	{
		map textures/rota3ctf1_lights/u_lamp3.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp3_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
	}
}

textures/rota3ctf1_lights/u_lamp3_blue
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp3_blue.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp3_blue_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_lights/u_lamp3_blue.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp3_blue_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
	}
}

textures/rota3ctf1_lights/u_lamp3_or
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp3_or.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp3_or_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_lights/u_lamp3_or.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp3_or_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
	}
}

textures/rota3ctf1_lights/u_lamp4
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp4.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp4_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_lights/u_lamp4.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp4_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
	}
}

textures/rota3ctf1_lights/u_lamp4_or
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp4_or.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp4_or_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_lights/u_lamp4_or.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp4_or_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
	}
}

textures/rota3ctf1_lights/u_lamp4_or_10k
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp4_or.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp4_or_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 10000
	{
		map textures/rota3ctf1_lights/u_lamp4_or.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp4_or_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
	}
}

textures/rota3ctf1_lights/u_lamp4_blue
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp4_blue.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp4_blue_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_lights/u_lamp4_blue.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp4_blue_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
	}
}

textures/rota3ctf1_lights/u_lamp4_blue_10K
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp4_blue.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp4_blue_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 5000
	{
		map textures/rota3ctf1_lights/u_lamp4_blue.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp4_blue_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
	}
}

textures/rota3ctf1_lights/u_lamp5_blue
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp5_blue.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp5_blue_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_lights/u_lamp5_blue.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp5_blue_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
	}
}

textures/rota3ctf1_lights/u_lamp5
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp5.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp5_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_lights/u_lamp5.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp5_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
	}
}

textures/rota3ctf1_lights/u_lamp5_or
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp5_or.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp5_or_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_lights/u_lamp5_or.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp5_or_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
		rgbGen wave sin 0.92 0.03 0 8 
	}
}


textures/rota3ctf1_lights/u_lamp7
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp7.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp7_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2300
	{
		map textures/rota3ctf1_lights/u_lamp7.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp7_blend.tga
		blendfunc add
		rgbGen wave sin 0.92 0.03 0 8 
	}
}

textures/rota3ctf1_lights/u_lamp7_500
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp7.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp7_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 500
	{
		map textures/rota3ctf1_lights/u_lamp7.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp7_blend.tga
		blendfunc add
		rgbGen wave sin 0.92 0.03 0 8 
	}
}

textures/rota3ctf1_lights/u_lamp7_blue
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp7_blue.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp7_blue_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2300
	{
		map textures/rota3ctf1_lights/u_lamp7_blue.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp7_blue_blend.tga
		blendfunc add
		rgbGen wave sin 0.9 0.05 0 5 
	}
}

textures/rota3ctf1_lights/u_lamplong1b
{
	qer_editorimage textures/rota3ctf1_lights/u_lamplong1b.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamplong1_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2100
	{
		map textures/rota3ctf1_lights/u_lamplong1b.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamplong1_blend.tga
		blendfunc add
		rgbGen wave sin 0.93 0.04 0 5 
	}
}

textures/rota3ctf1_lights/u_lamplong1
{
	qer_editorimage textures/rota3ctf1_lights/u_lamplong1.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamplong1_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2100
	{
		map textures/rota3ctf1_lights/u_lamplong1.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamplong1_blend.tga
		blendfunc add
		rgbGen wave sin 0.93 0.04 0 5 
	}
}

textures/rota3ctf1_lights/u_lamplong1_500
{
	qer_editorimage textures/rota3ctf1_lights/u_lamplong1.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamplong1_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 500
	{
		map textures/rota3ctf1_lights/u_lamplong1.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamplong1_blend.tga
		blendfunc add
		rgbGen wave sin 0.93 0.04 0 5 
	}
}

textures/rota3ctf1_lights/u_lamplong1_blue
{
	qer_editorimage textures/rota3ctf1_lights/u_lamplong1_blue.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamplong1_blue_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_lights/u_lamplong1_blue.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamplong1_blue_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
		rgbGen wave sin 0.9 0.2 0 0.3 
	}
}

textures/rota3ctf1_lights/u_lamplong1_or
{
	qer_editorimage textures/rota3ctf1_lights/u_lamplong1_or.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamplong1_or_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_lights/u_lamplong1_or.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamplong1_or_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
		rgbGen wave sin 0.9 0.09 0 1 
	}
}

textures/rota3ctf1_lights/u_thinline1
{
	qer_editorimage textures/rota3ctf1_lights/u_thinline1.tga
	q3map_lightimage textures/rota3ctf1_lights/u_thinline1_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 1200
	{
		map textures/rota3ctf1_lights/u_thinline1.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_thinline1_blend.tga
		blendfunc gl_dst_color gl_one
		rgbGen wave sawtooth 0.8 0.1 0 7 
	}
}

textures/rota3ctf1_lights/u_thinline1_blue
{
	qer_editorimage textures/rota3ctf1_lights/u_thinline1_blue.tga
	q3map_lightimage textures/rota3ctf1_lights/u_thinline1_blue_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 1200
	{
		map textures/rota3ctf1_lights/u_thinline1_blue.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_thinline1_blue_blend.tga
		blendfunc gl_dst_color gl_one
		rgbGen wave sawtooth 0.7 0.1 0 7 
	}
}

textures/rota3ctf1_lights/u_thinline1_or
{
	qer_editorimage textures/rota3ctf1_lights/u_thinline1_or.tga
	q3map_lightimage textures/rota3ctf1_lights/u_thinline1_or_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 1200
	{
		map textures/rota3ctf1_lights/u_thinline1_or.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_thinline1_or_blend.tga
		blendfunc gl_dst_color gl_one
		rgbGen wave sawtooth 0.7 0.1 0 7 
	}
}

textures/rota3ctf1_lights/u_thinline2_or
{
	qer_editorimage textures/rota3ctf1_lights/u_thinline2_or.tga
	q3map_lightimage textures/rota3ctf1_lights/u_thinline1_or_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 1200
	{
		map textures/rota3ctf1_lights/u_thinline2_or.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_thinline1_or_blend.tga
		blendfunc gl_dst_color gl_one
		rgbGen wave sawtooth 0.8 0.1 0 7 
	}
}

textures/rota3ctf1_lights/u_thinline2
{
	qer_editorimage textures/rota3ctf1_lights/u_thinline2.tga
	q3map_lightimage textures/rota3ctf1_lights/u_thinline1_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 1200
	{
		map textures/rota3ctf1_lights/u_thinline2.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_thinline1_blend.tga
		blendfunc gl_dst_color gl_one
		rgbGen wave sawtooth 0.8 0.1 0 7 
	}
}

textures/rota3ctf1_lights/u_trlight1
{
	qer_editorimage textures/rota3ctf1_lights/u_trlight1.tga
	q3map_lightimage textures/rota3ctf1_lights/u_trlight1_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2100
	{
		map textures/rota3ctf1_lights/u_trlight1.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_trlight1_blend.tga
		blendfunc add
		rgbGen wave sawtooth 0.6 0.1 0 7 
	}
}

textures/rota3ctf1_lights/u_trlight2
{
	qer_editorimage textures/rota3ctf1_lights/u_trlight2.tga
	q3map_lightimage textures/rota3ctf1_lights/u_trlight1_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2100
	{
		map textures/rota3ctf1_lights/u_trlight2.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_trlight1_blend.tga
		blendfunc gl_dst_color gl_one
		rgbGen wave sawtooth 0.9 0.2 0 7 
	}
}

textures/rota3ctf1_lights/u_trlight2_or
{
	qer_editorimage textures/rota3ctf1_lights/u_trlight2_or.tga
	q3map_lightimage textures/rota3ctf1_lights/u_trlight2_or_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2100
	{
		map textures/rota3ctf1_lights/u_trlight2_or.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_trlight2_or_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
		rgbGen wave sawtooth 0.77 0.1 0 7 
	}
}

textures/rota3ctf1_lights/u_trlight3
{
	qer_editorimage textures/rota3ctf1_lights/u_trlight3.tga
	q3map_lightimage textures/rota3ctf1_lights/u_trlight1_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2100
	{
		map textures/rota3ctf1_lights/u_trlight3.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_trlight1_blend.tga
		blendfunc add
		rgbGen wave sawtooth 0.6 0.1 0 7 
	}
}

textures/rota3ctf1_lights/u_trlight3_blue
{
	qer_editorimage textures/rota3ctf1_lights/u_trlight3_blue.tga
	q3map_lightimage textures/rota3ctf1_lights/u_trlight3_blue_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2100
	{
		map textures/rota3ctf1_lights/u_trlight3_blue.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_trlight3_blue_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
		rgbGen wave sawtooth 0.9 0.2 0 7 
	}
}

textures/rota3ctf1_lights/u_trlight3_or
{
	qer_editorimage textures/rota3ctf1_lights/u_trlight3_or.tga
	q3map_lightimage textures/rota3ctf1_lights/u_trlight2_or_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2100
	{
		map textures/rota3ctf1_lights/u_trlight3_or.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_trlight2_or_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
		rgbGen wave sawtooth 0.9 0.2 0 7 
	}
}

textures/rota3ctf1_lights/u_py1_or_2
{
	qer_editorimage textures/rota3ctf1_lights/u_py1_or_2.tga
	q3map_lightimage textures/rota3ctf1_lights/u_py1_or_glow.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2100
	{
		map textures/rota3ctf1_lights/u_py1_or_2.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_py1_or_glow.tga
		blendfunc add
		rgbGen wave sin 0.4 0.4 2 0.2 
	}
}

textures/rota3ctf1_lights/u_py1_or
{
	qer_editorimage textures/rota3ctf1_lights/u_py1_or.tga
	q3map_lightimage textures/rota3ctf1_lights/u_py1_or_glow.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2100
	{
		map textures/rota3ctf1_lights/u_py1_or.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_py1_or_glow.tga
		blendfunc add
		rgbGen wave sin 0.5 0.4 0 0.25 
	}
}

textures/rota3ctf1_lights/u_py1_or128
{
	qer_editorimage textures/rota3ctf1_lights/u_py1_or128.tga
	q3map_lightimage textures/rota3ctf1_lights/u_py1_or_glow.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2100
	{
		map textures/rota3ctf1_lights/u_py1_or128.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_py1_or_glow.tga
		blendfunc add
		rgbGen wave sin 0.8 0.2 0 0.5 
	}
}

textures/rota3ctf1_lights/u_py1_blue128
{
	qer_editorimage textures/rota3ctf1_lights/u_py1_or128.tga
	q3map_lightimage textures/rota3ctf1_lights/u_py1_blue_glow.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2100
	{
		map textures/rota3ctf1_lights/u_py1_or128.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_py1_blue_glow.tga
		blendfunc add
		rgbGen wave sin 0.8 0.2 0 0.5 
	}
}

textures/rota3ctf1_lights/u_py1_blue
{
	qer_editorimage textures/rota3ctf1_lights/u_py1_blue.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_lightsubdivide 128
	q3map_surfacelight 2100
	{
		map textures/rota3ctf1_lights/u_py1_blue.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
		rgbGen wave triangle 0.5 0.4 0 225 
		tcMod stretch sin 1.5 0.1 0 12 
	}
}

///floors
//floors jumppads bounce bounce!//
textures/rota3ctf1_floors/u_floor_des_mark_b
{
	qer_editorimage textures/rota3ctf1_floors/u_floor_des_mark.tga
	q3map_lightimage textures/rota3ctf1_floors/u_floor_mark_blue.tga
	surfaceparm nodamage
	q3map_surfacelight 100
	{
		map textures/rota3ctf1_floors/u_floor_des_mark.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_floors/u_floor_mark_blue.tga
		blendfunc add
		rgbGen wave sin 0.6 0.2 0.2 0.3 
	}
}

textures/rota3ctf1_floors/u_floor_des_mark_or
{
	qer_editorimage textures/rota3ctf1_floors/u_floor_des_mark.tga
	q3map_lightimage textures/rota3ctf1_floors/u_floor_mark_or.tga
	surfaceparm nodamage
	q3map_surfacelight 100
	{
		map textures/rota3ctf1_floors/u_floor_des_mark.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_floors/u_floor_mark_or.tga
		blendfunc add
		rgbGen wave sin 0.6 0.2 0.2 0.3 
	}
}

textures/rota3ctf1_floors/u_floor_mark_or
{
	qer_editorimage textures/rota3ctf1_floors/u_floor_mark.tga
	q3map_lightimage textures/rota3ctf1_floors/u_floor_mark_or.tga
	surfaceparm nodamage
	q3map_surfacelight 100
	{
		map textures/rota3ctf1_floors/u_floor_mark.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_floors/u_floor_mark_or.tga
		blendfunc add
		rgbGen wave sin 0.6 0.2 0.2 0.3 
	}
}

textures/rota3ctf1_floors/u_floor_mark_blue
{
	qer_editorimage textures/rota3ctf1_floors/u_floor_mark.tga
	q3map_lightimage textures/rota3ctf1_floors/u_floor_mark_blue.tga
	surfaceparm nodamage
	q3map_surfacelight 100
	{
		map textures/rota3ctf1_floors/u_floor_mark.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_floors/u_floor_mark_blue.tga
		blendfunc add
		rgbGen wave sin 0.6 0.2 0.2 0.3 
	}
}

textures/rota3ctf1_floors/u_floor_des_pad_7
{
	qer_editorimage textures/rota3ctf1_floors/u_floor_des_pad_7.tga
	q3map_lightimage textures/rota3ctf1_floors/u_floor_pan4_l_blend.tga
	surfaceparm nodamage
	q3map_surfacelight 150
	{
		map textures/rota3ctf1_floors/u_floor_des_pad_7.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_floors/u_floor_pan4_l_blend.tga
		blendfunc add
		rgbGen wave sin 0.6 0.2 0 2 
		tcMod stretch sin 2.5 1 0 1 
		tcMod rotate 90
	}
}

textures/rota3ctf1_floors/u_floor_pad1_or
{
	qer_editorimage textures/rota3ctf1_floors/u_floor_pad1.tga
	q3map_lightimage textures/rota3ctf1_floors/u_floor_pad1_blend.tga
	surfaceparm nodamage
	q3map_surfacelight 150
	{
		map textures/rota3ctf1_floors/u_floor_pad1.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_floors/u_floor_pad1_blend.tga
		blendfunc add
		rgbGen wave triangle 0.5 0.4 3434 1 
		tcMod stretch sin 1 0.01 0 1 
	}
}

textures/rota3ctf1_floors/u_floor_pad1_b
{
	qer_editorimage textures/rota3ctf1_floors/u_floor_pad1.tga
	q3map_lightimage textures/rota3ctf1_floors/u_floor_pad1_blend_b.tga
	surfaceparm nodamage
	q3map_surfacelight 150
	{
		map textures/rota3ctf1_floors/u_floor_pad1.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_floors/u_floor_pad1_blend_b.tga
		blendfunc add
		rgbGen wave triangle 0.5 0.4 3434 1 
		tcMod stretch sin 1 0.01 0 1 
	}
}

textures/rota3ctf1_floors/u_floor3_pad_7b
{
	qer_editorimage textures/rota3ctf1_floors/u_floor3_pad_7b.tga
	q3map_lightimage textures/rota3ctf1_floors/u_floor_pan4_l_blend.tga
	surfaceparm nodamage
	q3map_surfacelight 150
	{
		map textures/rota3ctf1_floors/u_floor3_pad_7b.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_floors/u_floor_pan4_l_blend.tga
		blendfunc add
		rgbGen wave sin 0.6 0.2 0 2 
		tcMod stretch sin 2.5 1 0 1 
		tcMod rotate 90
	}
}

textures/rota3ctf1_floors/u_floor3_pad_6
{
	qer_editorimage textures/rota3ctf1_floors/u_floor3_pad_6.tga
	q3map_lightimage textures/rota3ctf1_floors/u_floor_pan4_l_blend.tga
	surfaceparm nodamage
	q3map_surfacelight 150
	{
		map textures/rota3ctf1_floors/u_floor3_pad_6.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_floors/u_floor_pan4_l_blend.tga
		blendfunc add
		rgbGen const ( 1 0.345098 0.0352941 )
		tcMod stretch sin 1.4 0.6 0 1 
	}
}

textures/rota3ctf1_floors/u_floor3_pad_6b
{
	qer_editorimage textures/rota3ctf1_floors/u_floor3_pad_6.tga
	q3map_lightimage textures/rota3ctf1_floors/u_floor_pan4_l_blend.tga
	surfaceparm nodamage
	q3map_surfacelight 150
	{
		map textures/rota3ctf1_floors/u_floor3_pad_6.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_floors/u_floor_pan4_l_blend.tga
		blendfunc add
		rgbGen const ( 0.0156863 0.537255 0.756863 )
		tcMod stretch sin 1.4 0.6 0 1 
	}
}

textures/rota3ctf1_floors/u_floor3_pad_8
{
	qer_editorimage textures/rota3ctf1_floors/u_floor3_pad_8.tga
	q3map_lightimage textures/rota3ctf1_floors/u_floor_pan4_l_blend.tga
	surfaceparm nodamage
	q3map_surfacelight 150
	{
		map textures/rota3ctf1_floors/u_floor3_pad_8.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_floors/u_floor_pan4_l_blend.tga
		blendfunc add
		rgbGen wave sin 0.8 0.1 0 2 
		tcMod stretch sawtooth 0.83 0.1 1 0 
		tcMod scale 2 2
	}
	{
		map textures/rota3ctf1_floors/u_floor_pan4_l_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
		rgbGen wave sin 0.4 0.1 0 1 
		tcMod stretch sawtooth 1.7 1 1 1 
		tcMod rotate 90
	}
}

textures/rota3ctf1_lights/u_floor_pan3_l
{
	qer_editorimage textures/rota3ctf1_floors/u_floor_pan3_l.tga
	q3map_lightimage textures/rota3ctf1_floors/u_floor_pan3_l_blend.tga
	surfaceparm nodlight
	q3map_surfacelight 2100
	{
		map textures/rota3ctf1_floors/u_floor_pan3_l.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_floors/u_floor_pan3_l_blend.tga
		blendfunc gl_one_minus_dst_color gl_one
		rgbGen wave noise 0.7 0.13 0 2 
	}
}

textures/rota3ctf1_floors/u_floor_pan4_l
{
	qer_editorimage textures/rota3ctf1_floors/u_floor_pan4_l.tga
	q3map_lightimage textures/rota3ctf1_floors/u_floor_pan4_l_blend.tga
	surfaceparm nodlight
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_floors/u_floor_pan4_l.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_floors/u_floor_pan4_l_blend.tga
		blendfunc add
		rgbGen wave noise 0.6 0.06 0 99 
	}
}

textures/rota3ctf1_floors/u_floor3_lamp1
{
	qer_editorimage textures/rota3ctf1_floors/u_floor3_lamp1.tga
	q3map_lightimage textures/rota3ctf1_floors/u_floor_pan4_l_blend.tga
	surfaceparm nodlight
	q3map_surfacelight 2000
	{
		map textures/rota3ctf1_floors/u_floor3_lamp1.tga
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_floors/u_floor_pan4_l_blend.tga
		blendfunc add
		rgbGen wave noise 0.6 0.2 0 1 
		tcMod stretch sin 1 0.4 0 0.09 
	}
}

textures/rota3ctf1_grates/u_gr8_1
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_1.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_1.tga
		rgbGen identity
		depthWrite
		alphaFunc LT128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_1_half
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_1_half.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_1.tga
		rgbGen identity
		depthWrite
		alphaFunc LT128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_10a
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_10.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_10.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_11
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_11.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_11.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_12a
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_12.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_12.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_13a
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_13.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_13.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_13ab
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_13b.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_13b.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_13orangea
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_13orange.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_13orange.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_14a
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_14.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_14.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_2a
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_2.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_2.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_2ba
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_2b.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_2b.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_3a
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_3.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_3.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_4a
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_4.tga
	surfaceparm metalsteps
	surfaceparm trans
	surfaceparm alphashadow
	cull disable
	q3map_shadeangle 180
	q3map_nonplanar
	{
		map textures/rota3ctf1_grates/u_gr8_4.tga
		blendfunc blend
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
	}
	q3map_stylemarker
}

textures/rota3ctf1_grates/u_gr8_5a
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_5.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_5.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_6a
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_6.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_6.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_7a
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_7.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_7.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_8
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_8.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_8.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_7b
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_7b.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_7b.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_8ba
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_8b.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_8b.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_8ca
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_8c.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_8c.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_gr8_9a
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_9.tga
	surfaceparm nomarks
	surfaceparm trans
	nopicmip
	{
		map textures/rota3ctf1_grates/u_gr8_9.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_supp_1
{
	surfaceparm alphashadow
	surfaceparm nomarks
	surfaceparm trans
	cull disable
	nopicmip
	{
		map textures/rota3ctf1_grates/u_supp_1.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}


textures/rota3ctf1_grates/u_supp_2
{
	surfaceparm alphashadow
	surfaceparm nomarks
	surfaceparm trans
	cull disable
	nopicmip
	{
		map textures/rota3ctf1_grates/u_supp_2.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_grates/u_supp_2_sm
{
	surfaceparm alphashadow
	surfaceparm nomarks
	surfaceparm trans
	cull disable
	nopicmip
	{
		map textures/rota3ctf1_grates/u_supp_2_sm.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


textures/rota3ctf1_terrain/alpha_000	// Primary texture ONLY
{
	q3map_alphaMod volume
	q3map_alphaMod set 0
	surfaceparm nodraw
	surfaceparm nonsolid
	surfaceparm trans
	qer_trans 0.75
}

textures/rota3ctf1_terrain/alpha_025
{
	q3map_alphaMod volume
	q3map_alphaMod set 0.25
	surfaceparm nodraw
	surfaceparm nonsolid
	surfaceparm trans
	qer_trans 0.75
}

textures/rota3ctf1_terrain/alpha_050	// Perfect mix of both Primary + Secondary
{
	q3map_alphaMod volume
	q3map_alphaMod set 0.50
	surfaceparm nodraw
	surfaceparm nonsolid
	surfaceparm trans
	qer_trans 0.75
}

textures/rota3ctf1_terrain/alpha_075
{
	q3map_alphaMod volume
	q3map_alphaMod set 0.75
	surfaceparm nodraw
	surfaceparm nonsolid
	surfaceparm trans
	qer_trans 0.75
}

textures/rota3ctf1_terrain/alpha_085
{
	q3map_alphaMod volume
	q3map_alphaMod set 0.85
	surfaceparm nodraw
	surfaceparm nonsolid
	surfaceparm trans
	qer_trans 0.75
}

textures/rota3ctf1_terrain/alpha_100	// Secondary texture ONLY
{
	q3map_alphaMod volume
	q3map_alphaMod set 1.0
	surfaceparm nodraw
	surfaceparm nonsolid
	surfaceparm trans
	qer_trans 0.75
}

textures/rota3ctf1_terrain/ter_rock2
{
	q3map_nonplanar
	q3map_shadeangle 120
        qer_editorimage textures/rota3ctf1_terrain/ter_rock2.tga
	{
		map $lightmap
		rgbGen identity
	}
	{
		map textures/rota3ctf1_terrain/ter_rock2.tga
		blendFunc filter
	}
}


textures/rota3ctf1_terrain/ter_rockrock
{
        qer_editorimage textures/rota3ctf1_terrain/ter_rockrock.tga
	
	q3map_nonplanar
	q3map_shadeangle 120
	q3map_tcGen ivector ( 256 0 0 ) ( 0 256 0 )
	q3map_alphaMod dotproduct2 ( 0.0 0.0 0.75 )
	
	{
		map textures/rota3ctf1_terrain/ter_rock2b.tga	// Primary
		rgbGen identity
	}
	{
		map textures/rota3ctf1_terrain/ter_rock3b.tga	// Secondary
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		alphaFunc GE128
		rgbGen identity
		alphaGen vertex
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
	}
}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////


textures/rota3ctf1_terrain/diry
{
	surfaceparm nosteps
	cull disable
	surfaceparm alphashadow
	{
		map textures/rota3ctf1_terrain/diry.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_terrain/diry2
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_2b.tga
	surfaceparm nosteps
	cull disable
	{
		map textures/rota3ctf1_grates/u_gr8_2b.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}

textures/rota3ctf1_terrain/gril
{
	qer_editorimage textures/rota3ctf1_grates/u_gr8_5.tga
	surfaceparm metalsteps
	surfaceparm trans
	surfaceparm alphashadow
	cull disable
	{
		map textures/rota3ctf1_grates/u_gr8_5.tga
		blendfunc blend
	}
	{
		map $lightmap 
		blendfunc filter
	}
	q3map_stylemarker
}

textures/rota3ctf1_terrain/nebe
{
	qer_editorimage textures/rota3ctf1_terrain/nebe.jpg
	surfaceparm noimpact
	surfaceparm nolightmap
	q3map_surfacelight 150
	q3map_lightsubdivide 1024
	q3map_sun 0.780392 0.792157 0.839216 40 180 38
	skyParms env/dm 128 -
}

textures/rota3ctf1_terrain/sklo2
{
	qer_editorimage textures/rota3ctf1_terrain/sklo2.tga	
	qer_trans 	0.5
     

        {
		map textures/rota3ctf1_terrain/sklo2_efekt.tga
                tcgen environment
		blendFunc GL_ONE GL_ONE
		rgbGen identity
	}

        {
		map $lightmap
		rgbGen identity
		blendFunc filter
	}
}

textures/rota3ctf1_terrain/e6strimlight_s_nolight
{
	qer_editorimage textures/rota3ctf1_terrain/e6strimlight.tga
	surfaceparm nomarks
	q3map_surfacelight 400

	{
		map textures/rota3ctf1_terrain/e6strimlight.tga
	}
	{
		map $lightmap
		blendfunc filter
	}
	{
		map textures/rota3ctf1_terrain/e6strimlight_blend.tga
		blendfunc add
	}
}

textures/rota3ctf1_terrain/e6strimlight_s_nolight_5k
{
	qer_editorimage textures/rota3ctf1_terrain/e6strimlight.tga
	surfaceparm nomarks
	q3map_surfacelight 5000

	{
		map textures/rota3ctf1_terrain/e6strimlight.tga
	}
	{
		map $lightmap
		blendfunc filter
	}
	{
		map textures/rota3ctf1_terrain/e6strimlight_blend.tga
		blendfunc add
	}
}

textures/rota3ctf1_terrain/e6strimlight_s_nolightb
{
	qer_editorimage textures/rota3ctf1_terrain/e6strimlightb.tga
	surfaceparm nomarks
	q3map_surfacelight 400

	{
		map textures/rota3ctf1_terrain/e6strimlightb.tga
	}
	{
		map $lightmap
		blendfunc filter
	}
	{
		map textures/rota3ctf1_terrain/e6strimlight_blendb.tga
		blendfunc add
	}
}

textures/rota3ctf1_terrain/u_lamp3_napicu
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp3_or.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp3_or_blend.tga
	surfaceparm nomarks
	q3map_surfacelight 10000
	q3map_lightstyle 5
	q3map_lightmapFilterRadius 6 64
	{
		map $lightmap 
		tcGen lightmap 
	}
		q3map_stylemarker
	{
		map textures/rota3ctf1_lights/u_lamp3_or.tga
		blendfunc filter
	}
	{
		map textures/rota3ctf1_lights/u_lamp3_or_blend.tga
		blendfunc add
		rgbGen wave noise 0.8 0.5 0 20 
		alphaGen wave square 0.8 0.5 0 20 
	}
}

textures/rota3ctf1_terrain/u_lamp3_napicu_blue
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp3_blue.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp3_blue_blend.tga
	surfaceparm nomarks
	q3map_surfacelight 10000
	q3map_lightstyle 5
	q3map_lightmapFilterRadius 6 64
	{
		map $lightmap 
		tcGen lightmap 
	}
		q3map_stylemarker
	{
		map textures/rota3ctf1_lights/u_lamp3_blue.tga
		blendfunc filter
	}
	{
		map textures/rota3ctf1_lights/u_lamp3_blue_blend.tga
		blendfunc add
		rgbGen wave noise 0.8 0.5 0 20 
		alphaGen wave square 0.8 0.5 0 20 
	}
}


textures/rota3ctf1_lights/pokus
{
	qer_editorimage textures/rota3ctf1_lights/u_lamp7.tga
	q3map_lightimage textures/rota3ctf1_lights/u_lamp7_blend.tga
	surfaceparm nodlight
	surfaceparm nomarks
	q3map_surfacelight 2300
	{
		map textures/rota3ctf1_terrain/sklo2_efekt.tga
                tcgen environment
		blendFunc GL_ONE GL_ONE
		rgbGen identity
	}
	{
		map $lightmap 
		blendfunc filter
		tcGen lightmap 
	}
	{
		map textures/rota3ctf1_lights/u_lamp7_blend.tga
		blendfunc add
		rgbGen wave sin 0.92 0.03 0 8 
	}
}

textures/rota3ctf1_terrain/grate_grey2_noclp

{
	qer_editorimage textures/rota3ctf1_terrain/grate_grey2.tga
	surfaceparm nonsolid

	{
		map textures/rota3ctf1_terrain/grate_grey2.tga
		rgbGen identity
	}
        {
                map $lightmap
                blendfunc filter
                rgbGen identity
                tcGen lightmap
        }
}

textures/rota3ctf1_terrain/u_trm8_3_noclp

{
	qer_editorimage textures/rota3ctf1_trim/u_trm8_3.tga
	surfaceparm nonsolid

	{
		map textures/rota3ctf1_trim/u_trm8_3.tga
		rgbGen identity
	}
        {
                map $lightmap
                blendfunc filter
                rgbGen identity
                tcGen lightmap
        }
}

textures/rota3ctf1_terrain/list
{
	surfaceparm nosteps
	cull disable
	surfaceparm alphashadow
	surfaceparm nonsolid
	{
		map textures/rota3ctf1_terrain/list.tga
		rgbGen identity
		depthWrite
		alphaFunc GE128
	}
	{
		map $lightmap 
		blendfunc filter
		rgbGen identity
		tcGen lightmap 
		depthFunc equal
	}
}


textures/rota3ctf1_terrain/bld_rock2moss1
{
        qer_editorimage textures/rota3ctf1_terrain/bld_rock2moss1.tga
	
	q3map_nonplanar
	q3map_shadeAngle 120
	
	{
		map textures/rota3ctf1_terrain/ter_rock2.tga	// Primary
		rgbGen identity
	}
	{
		map textures/rota3ctf1_terrain/ter_moss1.tga	// Secondary
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		alphaFunc GE128
		rgbGen identity
		alphaGen vertex
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
	}
}

textures/rota3ctf1_terrain/bld_rock2rock3
{
        qer_editorimage textures/rota3ctf1_terrain/bld_rock2rock3.tga
	
	q3map_nonplanar
	q3map_shadeAngle 120
	
	{
		map textures/rota3ctf1_terrain/ter_rock2.tga	// Primary
		rgbGen identity
	}
	{
		map textures/rota3ctf1_terrain/ter_rock3b.tga	// Secondary
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		alphaFunc GE128
		rgbGen identity
		alphaGen vertex
	}
	{
		map $lightmap
		blendFunc GL_DST_COLOR GL_ZERO
		rgbGen identity
	}
}

models/mapobjects/leafa
{
    cull disable
    surfaceparm alphashadow
        {
                map models/mapobjects/leafa.tga
                alphaFunc GE128
		depthWrite
		rgbGen vertex
        }
}

models/mapobjects/leafb
{
    cull disable
    surfaceparm alphashadow
        {
                map models/mapobjects/leafb.tga
                alphaFunc GE128
		depthWrite
		rgbGen vertex
        }
}

models/mapobjects/ferna
{
    cull disable
//    surfaceparm trans
    surfaceparm alphashadow
        {
                map models/mapobjects/ferna.tga
                alphaFunc GE128
		depthWrite
		rgbGen vertex
        }
}

textures/rota3ctf1_terrain/IRIS
{
	surfaceparm trans
	surfaceparm nomarks
	surfaceparm nolightmap
	cull none
	surfaceparm nonsolid
          {
            clampmap textures/rota3ctf1_terrain/IRIS.tga
            blendFunc GL_ONE GL_ONE
          }
}