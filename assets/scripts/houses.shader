
textures/trees/pine_foliage_plane
{	
  // surfaceparm alphashadow
  cull none
  nopicmip
  surfaceparm nolightmap
  surfaceparm nonsolid
  surfaceparm trans
  {
    map textures/trees/pine_foliage_plane.tga
    blendFunc GL_ONE GL_ZERO
    alphaFunc GE128
    rgbGen identityLighting
  }
  {
    map $lightmap
    rgbGen identity
    blendFunc GL_DST_COLOR GL_ZERO
    depthFunc equal
  }
}

textures/house6/Wood_Floor_Light
{
  cull none
  surfaceparm trans
  surfaceparm nolightmap
  {
    map textures/house6/Wood_Floor_Light.tga
  }
}

textures/house6/Polished_Concrete_New
{
  q3map_surfacelight 10

  {
    map textures/house6/Polished_Concrete_New.tga
    blendFunc GL_ONE GL_ZERO
    rgbGen identity
  }
  {
    map $lightmap
    blendFunc filter
    rgbGen identity
  }
}


textures/house6/Polished_Drywall
{
  q3map_surfacelight 10

  {
    map textures/house6/Polished_Drywall.tga
    blendFunc GL_ONE GL_ZERO
    rgbGen identity
  }
  {
    map $lightmap
    blendFunc filter
    rgbGen identity
  }
}


textures/sfx/proto_zzztblu2
{
  surfaceparm nolightmap
  surfaceparm nonsolid
  surfaceparm trans
  q3map_lightimage textures/sfx/proto_zzztblu2.tga
  q3map_surfacelight 300  
  {
    map textures/sfx/proto_zzztblu2.tga
    tcmod rotate 60
    tcMod turb 0 .5 0 0.6
    tcmod scale 0.125 0.125
    tcmod scroll 0.5 0.5
    blendFunc add
    //rgbGen identity
  }
}

textures/house6/quad
{
  deformVertexes wave 100 sin 3 0 0 0
  {
    map textures/effects/envmaprail.tga
    blendfunc GL_ONE GL_ONE
    tcGen environment
    tcmod rotate 30
    //tcMod turb 0 0.2 0 .2
    tcmod scroll 1 .1
  }
}



