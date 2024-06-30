models/flags/k_flag2
{

        deformVertexes wave 100 sin 4 3 0 0.3
        deformVertexes wave 30 sin 0 3 0 .8
        deformVertexes normal .3 .2
        cull none

        {
                map models/flags/k_flag2.tga
                rgbGen identity
        }
        {
                map models/flags/gold_fx.tga
                tcGen environment
                //tcmod scale 9 3
                //tcmod scroll .1 .7

                blendFunc GL_ONE GL_ONE
                rgbGen identity
        }
        {
                map models/flags/k_flag2.tga
                blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
                rgbGen identity
        }
        {
                map textures/sfx/shadow.tga
                tcGen environment 
                //blendFunc GL_ONE GL_ONE            
                blendFunc GL_DST_COLOR GL_ZERO
                rgbGen identity
        }
}
models/flags/g_flag2
{

        deformVertexes wave 100 sin 4 3 0 0.3
        deformVertexes wave 30 sin 0 3 0 .8
        deformVertexes normal .3 .2
        cull none

        {
                map models/flags/g_flag2.tga
                rgbGen identity
        }
        {
                map models/flags/green_fx.tga
                tcGen environment
                //tcmod scale 9 3
                //tcmod scroll .1 .7
                blendFunc GL_ONE GL_ONE
                rgbGen identity
        }
        {
                map models/flags/g_flag2.tga
                blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
                rgbGen identity
        }
        {
                map textures/sfx/shadow.tga
                tcGen environment 
                //blendFunc GL_ONE GL_ONE            
                blendFunc GL_DST_COLOR GL_ZERO
                rgbGen identity
        }
}


icons/iconf_gold1
{
	sort opaque
	nopicmip
	{
		map icons/iconf_gold1.tga
		blendFunc blend
	}
}

icons/iconf_green1
{
	sort opaque
	nopicmip
	{
		map icons/iconf_green1.tga
		blendFunc blend
	}
}


