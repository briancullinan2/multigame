models/weapons3/grenadel/grenadel
{
	{
		map models/weapons3/grenadel/grenadel.tga
		rgbGen lightingDiffuse

	}
	{
		map models/weapons3/grenadel/chromey.tga
		rgbGen lightingDiffuse
		tcGen environment 
		blendfunc add
	}
	{
		map models/weapons3/grenadel/grenadel.tga
		rgbGen lightingDiffuse
		blendfunc blend
	}
}

models/weapons3/grenadel/newgren.tga
{
	{
		map models/weapons3/grenadel/newgren.tga
		rgbGen lightingDiffuse

	}
	{
		map models/weapons3/grenadel/chromey.tga
		rgbGen lightingDiffuse
		tcGen environment 
		blendfunc add
	}
	{
		map models/weapons3/grenadel/newgren.tga
		rgbGen lightingDiffuse
		blendfunc blend
	}
}
models/weapons3/grenadel/blackhandle
{
	{
		map models/weapons3/grenadel/blackhandle.tga
		rgbGen lightingDiffuse
		tcGen environment 
	}

}

models/weapons3/grenadel/muzside
{
//	deformVertexes autosprite2
	cull disable
	{
		map models/weapons3/grenadel/muzzlside.tga
		blendfunc add
	}
}

models/weapons3/grenadel/muzcenter
{
	deformVertexes autosprite
	{
		clampmap models/weapons3/grenadel/f_plasma.tga
		blendfunc add
		tcMod rotate 1246
	}
	{
		clampmap models/weapons3/grenadel/f_plasma.tga
		blendfunc add
		tcMod rotate -1246
	}
}

models/weapons3/grenadel/flare
{
	deformVertexes autosprite
	{
		map models/weapons3/grenadel/flare.tga
		blendfunc add
		rgbGen wave noise 0.5 0.5 0 1 
	}
}
