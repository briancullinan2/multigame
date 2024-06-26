models/weapons3/shotgun/skinoa
{
    {
        map models/weapons3/shotgun/shotgun.tga
        rgbGen lightingDiffuse
    }
    {
        map models/weapons3/shotgun/shotgun_spec.jpg
        blendFunc GL_SRC_ALPHA GL_ONE
        detail
        alphaGen lightingSpecular
    }
}

models/weapons3/shotgun/shotgun_laser
{
	
	{
		map	models/weapons3/shotgun/shotgun_laser.tga
		blendfunc add
	}
}

models/weapons3/shells/sgunshell_2
{
	deformVertexes autosprite
    {
        map models/weapons3/shells/sgunshell_2
        rgbGen lightingDiffuse
	blendFunc blend
    }

}

