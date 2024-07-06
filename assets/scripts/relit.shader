textures/ctf2/blueteam02
{      
  light 1
  qer_editorimage textures/ctf2/blueteam01.tga 	
  cull none
  surfaceparm alphashadow
  surfaceparm nomarks
  q3map_surfacelight 2000
  q3map_lightimage textures/base_light/light1blue.blend.tga
  {
    map textures/ctf2/blueteam01.tga
    alphaFunc GE128
    depthWrite
    rgbGen identity
    
  }
  {
    map $lightmap
    rgbGen identity
    blendFunc GL_DST_COLOR GL_ZERO
    depthFunc equal
  }

}

textures/ctf2/xblueteam01
// non flashy version
{       	
  qer_editorimage textures/ctf2/blueteam01.tga
  q3map_surfacelight 2000
  cull none
  surfaceparm nolightmap
  surfaceparm trans
  surfaceparm nomarks
  {
    map textures/ctf2/blueteam01.tga
    blendFunc Add
    rgbgen identity                  
  }

}


textures/ctf2/blueteam01
{       	
  cull none
  q3map_surfacelight 2000
  surfaceparm nolightmap
  surfaceparm trans
  surfaceparm nomarks
  {
    map textures/ctf2/blueteam01.tga
    blendFunc Add
    //rgbgen wave triangle 0.2 0.5 0 0.2
    rgbGen wave sin 1 .8 0 .2
    
  }

}

textures/gothic_wall/iron01_e_solid
{
  q3map_surfacelight 2000
  {
    map textures/gothic_wall/iron01_e_solid.tga
  }
}

textures/gothic_trim/tower_side2blu
{
  q3map_surfacelight 2000
  {
    map textures/gothic_trim/tower_side2blu.tga
  }
}
