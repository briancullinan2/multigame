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


textures/ctf/ctf_greenflag
{
        tessSize 64
        deformVertexes wave 194 sin 0 3 0 .4
        deformVertexes normal .5 .1
        surfaceparm nomarks
        cull none
        
        {
                map textures/ctf/ctf_greenflag.tga
                rgbGen identity
        }
        {
                map textures/effects/redflagmap.tga
                tcGen environment
                tcmod scale 9 3
                tcmod scroll .1 .7
                
                blendFunc GL_ONE GL_ONE
                rgbGen identity
        }
        {
                map textures/ctf/ctf_greenflag.tga
                blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
                rgbGen identity
        }
        {
                map $lightmap
                blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
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
textures/ctf/ctf_goldflag
{
        tessSize 64
        deformVertexes wave 194 sin 0 3 0 .4
        deformVertexes normal .5 .1
        surfaceparm nomarks
        cull none
        
        {
                map textures/ctf/ctf_goldflag.tga
                rgbGen identity
        }
        {
                map textures/effects/redflagmap.tga
                tcGen environment
                tcmod scale 9 3
                tcmod scroll .1 .7
                
                blendFunc GL_ONE GL_ONE
                rgbGen identity
        }
        {
                map textures/ctf/ctf_goldflag.tga
                blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
                rgbGen identity
        }
        {
                map $lightmap
                blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
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

textures/ctf/killblockctf_gold
{
        qer_editorimage   textures/gothic_block/killblockgeomtrn.tga

        {
                map textures/sfx/fire_ctfgold.tga
                tcmod scroll 0 1
                tcMod turb 0 .25 0 1.6
                tcmod scale 2 2
                blendFunc GL_ONE GL_ZERO
                rgbGen identity
        }
        {
                map textures/gothic_block/blocks18cgeomtrn2.tga
                //blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
                blendFunc blend
                tcmod rotate 30
                tcMod stretch sin .8 0.2 0 .2
                rgbGen identity
        }
        {
                map textures/gothic_block/blocks18cgeomtrn2.tga
                blendFunc blend
                tcmod rotate 20
                tcMod stretch sin .8 0.2 0 .1
                rgbGen identity
        }
        {
                map textures/gothic_block/killblockgeomtrn.tga
                blendFunc blend
                rgbGen identity
        }
        {
                map $lightmap
                blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
                rgbGen identity
        }
}
textures/ctf/killblockctf_g
{
        qer_editorimage   textures/gothic_block/killblockgeomtrn.tga

        {
                map textures/sfx/fire_ctfgreen.tga
                tcmod scroll 0 1
                tcMod turb 0 .25 0 1.6
                tcmod scale 2 2
                blendFunc GL_ONE GL_ZERO
                rgbGen identity
        }
        {
                map textures/gothic_block/blocks18cgeomtrn2.tga
                //blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
                blendFunc blend
                tcmod rotate 30
                tcMod stretch sin .8 0.2 0 .2
                rgbGen identity
        }
        {
                map textures/gothic_block/blocks18cgeomtrn2.tga
                blendFunc blend
                tcmod rotate 20
                tcMod stretch sin .8 0.2 0 .1
                rgbGen identity
        }
        {
                map textures/gothic_block/killblockgeomtrn.tga
                blendFunc blend
                rgbGen identity
        }
        {
                map $lightmap
                blendFunc GL_DST_COLOR GL_ONE_MINUS_DST_ALPHA
                rgbGen identity
        }
}
