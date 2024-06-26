// models/weapons3/shotgun/f_shotgun
//{
//	sort additive
//	cull disable
//	{
//		map	models/weapons3/shotgun/f_shotgun.tga
//		blendfunc add
//	}
//} 

muzzleSprite
{
	sort additive
	cull disable
	deformVertexes autosprite
	{
		map	models/weapons3/shotgun/shotgun_flash.tga
		blendfunc add
	}
}
muzzleSide
{
	sort additive
	deformVertexes autosprite2
	{
		map	models/weapons3/shotgun/shotgun_flashside.tga
		blendfunc add
	}
}

muzzleSphere
{
	sort additive
	cull disable
	{
		map	models/weapons3/shotgun/shotgun_flash.tga
		blendfunc add
	}
}

rocketProjectile
{

	{
		map	models/ammo/rocket/rocket.tga
	rgbGen lightingDiffuse
	}
	{
		map models/weapons3/machinegun/woodspec.tga
		blendfunc gl_dst_color gl_src_color
		//rgbGen lightingDiffuse
		tcGen environment 
	}
}

rocketThrustf
{
	deformVertexes autosprite2
	{
		map models/weapons3/machinegun/f_machinegun.tga
		blendfunc add
		tcMod rotate 1246
	}
	{
		map models/weapons3/machinegun/f_machinegun.tga
		blendfunc add
		tcMod rotate -1246
	}
}

rocketThrust
{
	{
	// do nothing.
	}
}
rocketFlare
{
	deformVertexes autosprite
	{
		map textures/oafx/rocketflare.tga
		blendfunc add
		
	}
	
}
