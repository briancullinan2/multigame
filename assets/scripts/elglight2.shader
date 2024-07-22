//      Yves Allaire aka evil lair         //
//   http://www.planetquake.com/hfx       //
//       hfx@planetquake.com             //

models/lighting/elglight2/elglight2
{
	surfaceparm alphashadow
	surfaceparm trans
	surfaceparm solid
	q3map_surfacelight 2000
	cull none
	//nopicmip
	{
		map models/lighting/elglight2/elglight2.tga
		rgbGen vertex
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
