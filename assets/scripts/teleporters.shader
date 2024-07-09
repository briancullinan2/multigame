



textures/liquids/clear_calm1

//	*********************************************************
//	*      Medium clear calm water. Created September 9	*
//	*********************************************************
		
	{
		qer_editorimage textures/liquids/pool3d_3e.tga
		qer_trans .5
		q3map_globaltexture
		surfaceparm trans
		surfaceparm nonsolid
		surfaceparm water
	
		cull disable
		deformVertexes wave 64 sin .25 .25 0 .5	
		{ 
			map textures/liquids/pool3d_5e.tga
			blendFunc GL_dst_color GL_one
			rgbgen identity
			tcmod scale .5 .5
			tcmod scroll .025 .01
		}
	
		{ 
			map textures/liquids/pool3d_3e.tga
			blendFunc GL_dst_color GL_one
			tcmod scale -.5 -.5
			tcmod scroll .025 .025
		}

	
		{
			map $lightmap
			blendFunc GL_dst_color GL_zero
			rgbgen identity		
		}
	
	

//	END
	}



//**********************************************************************//
// LIGHT BAND 64 - 02 : ZigZag glowing stripe 256x64			//
//**********************************************************************//
textures/egyptsoc_sfx/lig_b064-02a
{
	qer_editorimage textures/egyptsoc_sfx/lig_b064-02a.tga
	{
		map textures/egyptsoc_sfx/lig_b064-02a.tga
		rgbGen identity
	}
	{
		map $lightmap
		rgbGen identity
		blendfunc filter
	}
	{
		map textures/egyptsoc_sfx/lig_b064-02b.blend.tga
		blendfunc add	
    rgbgen wave sin .5 .3 0 1
	}
}
