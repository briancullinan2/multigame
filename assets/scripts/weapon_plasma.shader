models/weapons3/plasma/f_plasmagun2
{
	cull disable
	{
		clampmap textures/flares/lava.tga
		blendfunc add
		rgbGen const ( 0 0.0862745 0.235294 )
		tcMod rotate 8455
		tcMod stretch sin 0 1 0 2 
	}
	{
		clampmap textures/flares/flarey.tga
		blendfunc add
		rgbGen const ( 0.447059 0.623529 0.921569 )
		tcMod rotate 1466
		tcMod stretch sin 0 1 0 1 
	}
	{
		clampmap textures/flares/twilightflare.tga
		blendfunc add
		rgbGen const ( 0.447059 0.623529 0.921569 )
		tcMod rotate -6455
	}
}

models/weapons3/plasma/f_plasmagun3
{
	deformVertexes autosprite
	{
		clampmap textures/flares/twilightflare.tga
		blendfunc add
		tcMod rotate 1246
	}
	{
		clampmap textures/flares/twilightflare.tga
		blendfunc add
		tcMod rotate -1246
	}
}

models/weapons3/plasma/muzzlecenter
{
	deformVertexes autosprite
	{
		clampmap textures/flares/twilightflare.tga
		blendfunc add
		tcMod rotate 1246
	}
	{
		clampmap textures/flares/twilightflare.tga
		blendfunc add
		tcMod rotate -1246
	}
}

models/weapons3/plasma/blackchrome
{
	{
		map models/weapons3/plasma/blackchrome.tga
		rgbGen lightingDiffuse
		tcGen environment 
	}
}

models/weapons3/plasma/skin
{
	{
		map models/weapons3/plasma/skin.tga
		rgbGen identity
	}
	{
		map textures/effects/tinfx2d.tga
		blendfunc add
		rgbGen identity
		tcMod scroll 1 0
		tcMod scale 2 2
	}
	{
		map models/weapons3/plasma/skin.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/weapons3/plasma/blackhandle
{
	{
		map models/weapons3/plasma/blackhandle.tga
		rgbGen lightingDiffuse
		tcGen environment 
	}
}

models/weapons3/plasma/muzzlside
{
	cull disable
	{
		map models/weapons3/plasma/muzzlside.tga
		blendfunc add
	}
}

models/weapons3/plasma/muzzlecenter
{
	deformVertexes autosprite
	{
		clampmap models/weapons3/plasma/f_plasma.tga
		blendfunc add
		tcMod rotate 1246
	}
	{
		clampmap models/weapons3/plasma/f_plasma.tga
		blendfunc add
		tcMod rotate -1246
	}
}

models/weapons3/plasma/flare
{
	deformVertexes autosprite
	{
		map models/weapons3/plasma/flare.tga
		blendfunc add
	}
}

