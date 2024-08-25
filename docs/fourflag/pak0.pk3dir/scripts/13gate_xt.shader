textures/13gate_xt/pitted_rust3_spec
{
	qer_editorimage textures/gothic_trim/pitted_rust3.tga
	surfaceparm trans
	{
		map $lightmap 
		rgbGen identity
		tcGen lightmap 
	}
	{
		map textures/gothic_trim/pitted_rust3.tga
		blendfunc filter
		rgbGen identity
	}
}

textures/13gate_xt/lava_red
{
	qer_editorimage textures/liquids/lavahell.tga
	surfaceparm lava
	surfaceparm nolightmap
	surfaceparm trans
	deformVertexes wave 100 sin 3 2 0.1 0.1 
	q3map_lightsubdivide 32
	q3map_surfacelight 400
	q3map_globaltexture
	{
		map textures/liquids/lavahell.tga
		tcMod turb 0 0.2 0 0.1
	}
}

textures/13gate_xt/lava_blue
{
	qer_editorimage textures/liquids/pool2.tga
	surfaceparm lava
	surfaceparm nolightmap
	surfaceparm trans
	deformVertexes wave 100 sin 3 2 0.1 0.1 
	q3map_lightsubdivide 32
	q3map_surfacelight 400
	q3map_globaltexture
	{
		map textures/liquids/pool2.tga
		tcMod turb 0 0.2 0 0.1
	}
}

textures/13gate_xt/fog
{
	qer_editorimage textures/sfx/fog_grey.tga
	surfaceparm fog
	surfaceparm nolightmap
	surfaceparm nonsolid
	surfaceparm trans
	fogparms ( 0.7 0.7 0.7 ) 1024
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

textures/13gate_xt/sky
{
	qer_editorimage textures/13gate_xt/sky.tga
	q3map_lightimage textures/skies/stars_red.tga
	surfaceparm noimpact
	surfaceparm nolightmap
	surfaceparm nomarks
	q3map_surfacelight 130
	q3map_sun 1 0.77 0.77 80 315 70
	skyParms textures/13gate_xt/env/filter 384 -
	{
		map textures/13gate_xt/sky.tga
		blendfunc filter
		tcMod scroll 0.05 0.1
		tcMod scale 2 2
	}
}

textures/13gate_xt/slick_clip
{
	qer_editorimage textures/common/slick.tga
	surfaceparm nodraw
	surfaceparm nolightmap
	surfaceparm nomarks
	surfaceparm nonsolid
	surfaceparm playerclip
	surfaceparm slick
	qer_trans 0.4
}

models/mapobjects/13/torch/flame
{
	qer_editorimage models/mapobjects/13/torch/flame.tga
	q3map_lightimage textures/sfx/flame1.tga
	surfaceparm nolightmap
	surfaceparm nomarks
	surfaceparm trans
	cull disable
	q3map_surfacelight 2000
	{
		animmap 10 textures/sfx/flame1.tga textures/sfx/flame2.tga textures/sfx/flame3.tga textures/sfx/flame4.tga textures/sfx/flame5.tga textures/sfx/flame6.tga textures/sfx/flame7.tga textures/sfx/flame8.tga 
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 10 
	}
	{
		animmap 10 textures/sfx/flame2.tga textures/sfx/flame3.tga textures/sfx/flame4.tga textures/sfx/flame5.tga textures/sfx/flame6.tga textures/sfx/flame7.tga textures/sfx/flame8.tga textures/sfx/flame1.tga 
		blendfunc add
		rgbGen wave sawtooth 0 1 0 10 
	}
	{
		map textures/sfx/flameball.tga
		blendfunc add
		rgbGen wave sin 0.6 0.2 0 0.6 
	}
}

models/mapobjects/13/torch/grate
{
	q3map_lightimage textures/sfx/flame1.tga
	surfaceparm trans
	cull disable
	q3map_surfacelight 4000
	{
		map models/mapobjects/gratelamp/gratetorch2b.tga
		rgbGen Vertex
		depthWrite
		alphaFunc GE128
	}
}

models/mapobjects/13/torch_blue/flame
{
	qer_editorimage models/mapobjects/13/torch_blue/flame.tga
	q3map_lightimage textures/sfx/proto_zzztblu3.tga
	surfaceparm nolightmap
	surfaceparm nomarks
	surfaceparm trans
	cull disable
	q3map_surfacelight 4000
	{
		animmap 10 textures/sfx/b_flame1.tga textures/sfx/b_flame2.tga textures/sfx/b_flame3.tga textures/sfx/b_flame4.tga textures/sfx/b_flame5.tga textures/sfx/b_flame6.tga textures/sfx/b_flame7.tga textures/sfx/b_flame8.tga 
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 10 
	}
	{
		animmap 10 textures/sfx/b_flame2.tga textures/sfx/b_flame3.tga textures/sfx/b_flame4.tga textures/sfx/b_flame5.tga textures/sfx/b_flame6.tga textures/sfx/b_flame7.tga textures/sfx/b_flame8.tga textures/sfx/b_flame1.tga 
		blendfunc add
		rgbGen wave sawtooth 0 1 0 10 
	}
	{
		map textures/sfx/b_flameball.tga
		blendfunc add
		rgbGen wave sin 0.6 0.2 0 0.6 
	}
}

models/mapobjects/13/torch_blue/grate
{
	q3map_lightimage textures/sfx/proto_zzztblu3.tga
	surfaceparm trans
	cull disable
	q3map_surfacelight 4000
	{
		map models/mapobjects/gratelamp/gratetorch2b.tga
		rgbGen Vertex
		depthWrite
		alphaFunc GE128
	}
}

