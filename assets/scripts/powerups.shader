powerups/ammoregen
{
  deformVertexes wave 100 sin 3 0 0 0
  {
    map textures/effects/envmapyel.tga
    blendfunc GL_ONE GL_ONE
    tcGen environment
    tcmod rotate 30
    //tcMod turb 0 0.2 0 .2
    tcmod scroll 1 .1
  }
}
