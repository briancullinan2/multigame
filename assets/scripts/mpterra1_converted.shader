
textures/common/terrain
{
  qer_editorimage textures/stone/pjrock10bc.tga
  q3map_terrain
  surfaceparm nodraw
  surfaceparm nomarks
  surfaceparm nolightmap
}

textures/common/terrain2
{
  q3map_terrain
  qer_editorimage textures/common/terrain.tga
  surfaceparm dust
  surfaceparm nodraw
  surfaceparm nomarks
  surfaceparm nolightmap
}

textures/terrain/vxmpterra1_converted

{
  surfaceparm terrain
  qer_editorimage textures/stone/pjrock10bc.tga
  surfaceparm nolightmap
  q3map_novertexshadows
  q3map_forcesunlight


  {

    map textures/stone/pjrock10b_2.tga
    rgbGen vertex
    tcmod scale 0.125 0.125
  }
  
}


textures/terrain/mpterra1_converted_0
{
  qer_editorimage textures/stone/pjrock9c.tga
  surfaceparm nolightmap
  surfaceparm terrain
  q3map_novertexshadows
  q3map_forcesunlight	
  {
    map textures/stone/pjrock9c.tga
    rgbGen vertex
    tcmod scale 0.125 0.125
  }
  {
    map textures/skies2/clouds2.tga
    blendfunc filter
    tcmod scale 0.01 0.01
    tcMod scroll -0.1 0.1
    
  }
  
}

textures/terrain/mpterra1_converted_1
{
  qer_editorimage textures/stone/pjrock12c.tga
  surfaceparm nolightmap
  surfaceparm terrain
  q3map_novertexshadows
  q3map_forcesunlight	
  {
    map textures/stone/pjrock12c.tga
    //tcmod transform 1 0 1 1 1 1
    rgbGen vertex
    tcmod scale 0.125 0.125 
  }
  {
    map textures/skies2/clouds2.tga
    blendfunc filter
    tcmod scale 0.01 0.01
    tcMod scroll -0.1 0.1
    
  }

}

textures/terrain/mpterra1_converted_2
{
  qer_editorimage textures/stone/pjrock10c.tga
  surfaceparm nolightmap
  surfaceparm terrain
  q3map_novertexshadows
  q3map_forcesunlight	
  {
    map textures/stone/pjrock10c.tga
    tcmod scale 0.05 0.05 
    rgbGen vertex
  }
  {
    map textures/skies2/clouds2.tga
    blendfunc filter
    tcmod scale 0.01 0.01
    tcMod scroll -0.1 0.1
    
  }

}

textures/terrain/mpterra1_converted_0to1
{
  qer_editorimage textures/stone/pjrock912c.tga
  surfaceparm nolightmap
  surfaceparm terrain
  q3map_novertexshadows
  q3map_forcesunlight	
  {
    map textures/stone/pjrock9c.tga	
    rgbGen vertex
    alphaGen vertex
    tcmod scale 0.125 0.125 
  }
  {
    map textures/stone/pjrock12c.tga
    tcmod scale 0.125 0.125 
    rgbGen vertex
    alphaGen vertex
    blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
  }
  {
    map textures/skies2/clouds2.tga
    blendfunc filter
    tcmod scale 0.01 0.01
    tcMod scroll -0.1 0.1
    
  }

}

textures/terrain/mpterra1_converted_0to2
{
  qer_editorimage textures/stone/pjrock9c.tga
  surfaceparm nolightmap
  surfaceparm terrain
  q3map_novertexshadows
  q3map_forcesunlight	
  {
    map textures/stone/pjrock9c.tga
    rgbGen vertex
    alphaGen vertex
    tcmod scale 0.125 0.125
  }
  {
    map textures/stone/pjrock10c.tga
    //tcmod transform 1 0 1 1 1 1
    tcmod scale 0.05 0.05 
    rgbGen vertex
    alphaGen vertex
    blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
  }
  {
    map textures/skies2/clouds2.tga
    blendfunc filter
    tcmod scale 0.01 0.01
    tcMod scroll -0.1 0.1
    
  }

}

textures/terrain/mpterra1_converted_1to2
{
  qer_editorimage textures/stone/pjrock1210c.tga
  surfaceparm nolightmap
  surfaceparm terrain
  q3map_novertexshadows
  q3map_forcesunlight	
  {
    map textures/stone/pjrock12c.tga
    rgbGen vertex
    alphaGen vertex
    tcmod scale 0.125 0.125 
  }
  {
    map textures/stone/pjrock10c.tga
    //tcmod transform 1 0 1 1 1 1
    tcmod scale 0.05 0.05 
    rgbGen vertex
    alphaGen vertex
    blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
  }
  {
    map textures/skies2/clouds2.tga
    blendfunc filter
    tcmod scale 0.01 0.01
    tcMod scroll -0.1 0.1
    
  }
}
