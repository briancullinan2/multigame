ctftrunk
{
	{
		map models/ctftree/ctftree.tga
		rgbGen Vertex
	}
}
ctfleaves
{
	cull disable
	//deformVertexes wave 3 sin 0 1 0 .5
	deformVertexes bulge 3 3 .8
	nopicmip
        surfaceparm pointlight
	{
		map models/ctftree/ctftree.tga
		alphaFunc GE128
		rgbGen vertex
	}
}
