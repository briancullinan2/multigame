
gfx/misc/snow
{
	cull none
	entitymergable
	//nofog
	//nomipmaps
	nopicmip
	sort decal
	{
		clampmap gfx/misc/snowflake.tga
		blendfunc blend
		//alphafunc GE128
		rgbgen vertex
	}
}

gfx/misc/raindrop
{
	cull none
	nomipmaps
	nopicmip
	{
		map gfx/misc/raindrop.tga
		blendfunc blend
		alphagen vertex
	}
}

snowflake
{
	nopicmip
	sort nearest

	{
		clampmap gfx/misc/raildisc_mono2.tga 
		blendFunc GL_ONE GL_ONE
		rgbGen vertex
	}
}

rain
{
	nopicmip
	cull none
	sort nearest

	{
		map gfx/misc/raindrop.tga
		blendFunc GL_ONE GL_ONE
		rgbGen vertex
	}
}
