
icons/iconw_nailgun
{
	nopicmip
	{
		map icons/nailgun128.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

icons/iconw_chaingun
{
	nopicmip
	{
		map icons/chaingun128.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

icons/iconw_proxlauncher
{
	nopicmip
	{
		map icons/proxmine.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

icons/icona_nailgun
{
	nopicmip
	{
		map icons/ammo_nailgun.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

icons/icona_chaingun
{
	nopicmip
	{
		map icons/ammo_chaingun.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

icons/icona_proxlauncher
{
	nopicmip
	{
		map icons/ammo_proxmine.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

models/weaphits/proxminet
{
        cull disable  
        {
                map models/weaphits/proxmine.tga
                rgbGen lightingdiffuse
        }
        {
                map models/weaphits/proxminebt.tga
                blendFunc add
                rgbGen wave sin .5 .5 0 2
        }

}

models/weaphits/proxmine2t
{
        cull disable  
        nomipmaps
        {
                clampmap models/weaphits/proxmine2t.tga
                blendFunc add
                tcmod rotate 200
                tcMod stretch sin .6 0.2 0 .11
                rgbGen identity
        }
        {
                clampmap models/weaphits/proxmine2t.tga
                blendFunc add
                tcmod rotate -200
                tcMod stretch sin .6 0.2 0 .2
                rgbGen identity
        }

}

models/powerups/ammo/chaingammo
{
       {
	        map textures/effects/tinfx2d.tga
		tcGen environment
		blendfunc GL_ONE GL_ZERO
                rgbGen identity
       }
       {
	        map models/powerups/ammo/chaingammo.tga
		blendfunc blend
                rgbGen lightingDiffuse
       }
}
models/powerups/ammo/chaingammo2
{
       {
	        map models/powerups/ammo/chaingammo2.tga
		blendfunc GL_ONE GL_ZERO
                rgbGen identity
       }
}

models/powerups/ammo/nailgammo
{
       {
	        map textures/effects/tinfx2d.tga
		tcGen environment
		blendfunc GL_ONE GL_ZERO
                rgbGen identity
       }
       {
	        map models/powerups/ammo/nailgammo.tga
		blendfunc blend
                rgbGen lightingDiffuse
       }
}
models/powerups/ammo/nailgammo2
{
       {
	        map models/powerups/ammo/nailgammo2.tga
		blendfunc GL_ONE GL_ZERO
                rgbGen identity
       }
}

models/weapons/proxmine/f_proxmine
{
        cull disable  
        {
                map models/weapons/proxmine/f_proxmine.tga
                blendFunc add
                rgbGen identity
        }


}

models/weapons/proxmine/proxmine2
{
        cull disable  
        {
                map models/weapons/proxmine/proxmine2.tga
                rgbGen lightingdiffuse
        }
        {
                map models/weapons/proxmine/proxmine2b.tga
                blendFunc add
                rgbGen wave sin .5 .5 0 2
        }

}

models/weapons/proxmine/proxmine1
{
        cull disable  
        {
                map models/weapons/proxmine/proxmine1b.tga
                tcmod scroll 0 2
                rgbGen lightingdiffuse
        }
        {
                map models/weapons/proxmine/proxmine1.tga
                blendFunc Blend
                rgbGen lightingdiffuse
        }

}
models/weaphits/proxmine
{
        cull disable  
        {
                map models/weaphits/proxmine.tga
                rgbGen lightingdiffuse
        }
        {
                map models/weaphits/proxmineb.tga
                blendFunc add
                rgbGen wave sin .5 .5 0 2
        }

}

models/weaphits/proxmine2
{
        cull disable  
        nomipmaps
        {
                clampmap models/weaphits/proxmine2.tga
                blendFunc add
                tcmod rotate 200
                tcMod stretch sin .6 0.2 0 .11
                rgbGen identity
        }
        {
                clampmap models/weaphits/proxmine2.tga
                blendFunc add
                tcmod rotate -200
                tcMod stretch sin .6 0.2 0 .2
                rgbGen identity
        }

}

models/weapons/nailgun/nail
{
     
     cull disable

        {
                map models/weapons/nailgun/nail.tga
                alphaFunc GE128
		depthWrite
                rgbGen identity
        }
}

models/weapons/nailgun/nail2
{
     cull disable

        {
                map models/weapons/nailgun/nail2.tga
                alphaFunc GE128
		depthWrite
                rgbGen identity
        }
}

models/weapons/nailgun/f_nailgun
{
     cull disable

        {
                map models/weapons/nailgun/f_nailgun.tga
                Blendfunc Add
                rgbGen identity
        }
}

models/weapons/nailgun/nailgun
{
     //deformVertexes normal .2 .1
     cull disable

        {
                map models/weapons/nailgun/nailgun_env.tga
                //tcMod scale 2 2
                tcGen environment
                rgbGen lightingdiffuse
        }
        {
                map models/weapons/nailgun/nailgun.tga
                blendFunc blend
                rgbGen lightingdiffuse
        }
}

models/weapons/vulcan/f_vulcan
{
	sort additive
	cull disable
	{
		map	models/weapons/vulcan/f_vulcan.tga
		blendfunc GL_ONE GL_ONE
	}
}


nailtrail
{
	sort nearest
	cull none
	{
		clampmap models/weaphits/nailtrail.tga 
		blendFunc Add
		rgbGen vertex
                tcMod rotate -30
	}

}