models/mapobjects/videocamera/videocamerasupport
{
    cull disable
    surfaceparm alphashadow
        {
                map models/mapobjects/videocamera/videocamerasupport.tga
                alphaFunc GE128
		depthWrite
		rgbGen vertex
        }
}
