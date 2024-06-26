
//
// weapon icons
//
icons3/iconw_gauntlet
{
	sort opaque
	nopicmip
	{
		map icons3/iconw_gauntlet.tga
		blendFunc blend

	}
}

icons3/iconw_machinegun
{
	sort opaque
	nopicmip
	{
		map icons3/iconw_machinegun.tga
		blendFunc blend

	}
}

icons3/iconw_rocket
{
	sort opaque
	nopicmip
	{
		map icons3/iconw_rocket.tga
		blendFunc blend

	}
}

icons3/iconw_shotgun
{
	sort opaque
	nopicmip
	{
		map icons3/iconw_shotgun.tga
		blendFunc blend
		rgbgen identitylighting

	}
}

icons3/iconw_grenade
{
	sort opaque
	nopicmip
	{
		map icons3/iconw_grenade.tga
		blendFunc blend

	}
}

icons3/iconw_lightning
{
	sort opaque
	nopicmip
	{
		map icons3/iconw_lightning.tga
		blendFunc blend

	}
}

icons3/iconw_plasma
{
	sort opaque
	nopicmip
	{
		map icons3/iconw_plasma.tga
		blendFunc blend

	}
}

icons3/iconw_railgun
{
	sort opaque
	nopicmip
	{
		map icons3/iconw_railgun.tga
		blendFunc blend

	}
}

icons3/iconw_bfg
{
	sort opaque
	nopicmip
	{
		map icons3/iconw_bfg.tga
		blendFunc blend

	}
}

icons3/iconw_grapple
{
	sort opaque
	nopicmip
	{
		map icons3/iconw_grapple.tga
		blendFunc blend

	}
}

//
// ammo icons
//
icons3/icona_machinegun
{
	sort opaque
	nopicmip
	{
		map icons3/icona_machinegun.tga
		blendFunc blend

	}
}

icons3/icona_rocket
{
	sort opaque
	nopicmip
	{
		map icons3/icona_rocket.tga
		blendfunc blend

	}
}

icons3/icona_shotgun
{
	sort opaque
	nopicmip
	{
		map icons3/icona_shotgun.tga
		blendFunc blend
		rgbgen identitylighting

	}
}

icons3/icona_grenade
{
	sort opaque
	nopicmip
	{
		map icons3/icona_grenade.tga
		blendFunc blend

	}
}

icons3/icona_lightning
{
	sort opaque
	nopicmip
	{
		map icons3/icona_lightning.tga
		blendFunc blend

	}
}

icons3/icona_plasma
{
	sort opaque
	nopicmip
	{
		map icons3/icona_plasma.tga
		blendFunc blend

	}
}

icons3/icona_railgun
{
	sort opaque
	nopicmip
	{
		map icons3/icona_railgun.tga
		blendFunc blend

	}
}

icons3/icona_bfg
{
	sort opaque
	nopicmip
	{
		map icons3/icona_bfg.tga
		blendFunc blend

	}
}

// // // // SHADERS FOR OPEN ARENA AMMOBOX POWERUPS 
// // // //  jzero --> johnzero@verizon.net
// 1.machinegun
models/powerup3/ammo/machammo
{
	{
		map models/powerup3/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerup3/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 1 1 0 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerup3/ammo/machammo2
{
	{
		map models/powerup3/ammo/machammo2.tga
		rgbGen identity
	}
}

// 2.shotgun
models/powerup3/ammo/shotammo
{
	{
		map models/powerup3/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerup3/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 1 0.5 0 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerup3/ammo/shotammo2
{
	{
		map models/powerup3/ammo/shotammo2.tga
		rgbGen identity
	}
}

// 3.grenade launcher
models/powerup3/ammo/grenammo
{
	{
		map models/powerup3/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerup3/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 0 0.56 0 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerup3/ammo/grenammo2
{
	{
		map models/powerup3/ammo/grenammo2.tga
		rgbGen identity
	}
}

// 4.lightning gun
models/powerup3/ammo/lighammo
{
	{
		map models/powerup3/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerup3/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 1 1 0.69 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerup3/ammo/lighammo2
{
	{
		map models/powerup3/ammo/lighammo2.tga
		rgbGen identity
	}
}

// 5.plasma gun
models/powerup3/ammo/plasammo
{
	{
		map models/powerup3/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerup3/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 0.8 0 1 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerup3/ammo/plasammo2
{
	{
		map models/powerup3/ammo/plasammo2.tga
		rgbGen identity
	}
}

//6.rocket launcher
models/powerup3/ammo/rockammo
{
	{
		map models/powerup3/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerup3/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 1 0 0 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerup3/ammo/rockammo2
{
	{
		map models/powerup3/ammo/rockammo2.tga
		rgbGen identity
	}
}

//7. railgun
models/powerup3/ammo/railammo
{
	{
		map models/powerup3/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerup3/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 0 1 0 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerup3/ammo/railammo2
{
	{
		map models/powerup3/ammo/railammo2.tga
		rgbGen identity
	}
}

//8. BFG
models/powerup3/ammo/bfgammo
{
	{
		map models/powerup3/ammo/ammobox.tga
		rgbGen lightingDiffuse
	}
	{
		map models/powerup3/ammo/ammolights.tga
		blendfunc blend
		rgbGen const ( 0 0.4 1 )
		alphaGen wave sawtooth 0 1 0 1 
	}
}

models/powerup3/ammo/bfgammo2
{
	{
		map models/powerup3/ammo/bfgammo2.tga
		rgbGen identity
	}
}

