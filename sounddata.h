/* Generated by conqinit on 13:23:06 04Jun07 */
/* $Id$ */


#ifndef _SOUNDDATA_H
#define _SOUNDDATA_H

static cqiSoundConfRec_t defaultSoundConf = {
  44100,
  1,
  16,
  512
};

static int defaultNumSoundMusic = 0;

static cqiSoundRec_t *defaultSoundMusic = NULL;


static int defaultNumSoundEffects = 52;

static cqiSoundRec_t defaultSoundEffects[52] = {
 { "doomsday-beam", "TOS-doombeam", 70, 0, 0, 0, 1, 1, 0, 1000 },
 { "explosion", "explosion", 45, 0, 0, 0, 1, 0, 2, 0 },
 { "bombing", "TOS-bomb", 100, 0, 0, 1000, 0, 1, 0, 0 },
 { "engines", "engines", 100, 0, 1000, 2000, 0, 1, 0, 0 },
 { "beep-alert", "beep-alert", 60, 0, 0, 0, 1, 1, 0, 1500 },
 { "beep-err", "beep-err", 65, 0, 0, 0, 1, 1, 0, 0 },
 { "beep-msg", "beep-msg", 40, 0, 0, 0, 1, 1, 0, 0 },
 { "torp-alert", "torpalert", 70, 0, 0, 0, 2, 1, 0, 3000 },
 { "shipF-phaser", "TOS-fphaz", 60, 0, 0, 0, 1, 2, 0, 0 },
 { "shipF-torp", "TOS-fphoton", 50, 0, 0, 0, 1, 0, 0, 100 },
 { "shipF-torp3", "TOS-fphoton3", 50, 0, 0, 0, 1, 3, 0, 100 },
 { "shipF-alert", "TOS-falert", 35, 0, 0, 0, 0, 1, 0, 0 },
 { "shipF-beam-down", "TOS-fbeamd", 100, 0, 0, 1000, 1, 1, 0, 0 },
 { "shipF-beam-up", "TOS-fbeamu", 100, 0, 0, 1000, 1, 1, 0, 0 },
 { "shipF-hit", "TOS-fblast", 100, 0, 0, 1000, 1, 1, 0, 0 },
 { "shipF-info", "TOS-finfo", 70, 0, 0, 0, 1, 1, 0, 60000 },
 { "shipF-mag", "TOS-fmag", 70, 0, 0, 0, 1, 1, 0, 60000 },
 { "shipF-warp-up", "TOS-fwarpu", 70, 0, 0, 3000, 1, 1, 0, 0 },
 { "shipF-warp-down", "TOS-fwarpd", 50, 0, 0, 3000, 1, 1, 0, 0 },
 { "shipR-phaser", "TOS-fphaz", 60, 0, 0, 0, 1, 2, 0, 0 },
 { "shipR-torp", "TOS-rphoton", 50, 0, 0, 0, 1, 0, 0, 100 },
 { "shipR-torp3", "TOS-rphoton3", 50, 0, 0, 0, 1, 1, 0, 100 },
 { "shipR-alert", "TOS-falert", 35, 0, 0, 0, 0, 1, 0, 0 },
 { "shipR-beam-down", "TOS-fbeamd", 100, 0, 0, 1000, 1, 1, 0, 0 },
 { "shipR-beam-up", "TOS-fbeamu", 100, 0, 0, 1000, 1, 1, 0, 0 },
 { "shipR-hit", "TOS-fblast", 100, 0, 0, 1000, 1, 1, 0, 0 },
 { "shipR-info", "TOS-finfo", 70, 0, 0, 0, 1, 1, 0, 60000 },
 { "shipR-mag", "TOS-fmag", 70, 0, 0, 0, 1, 1, 0, 60000 },
 { "shipR-warp-up", "TOS-fwarpu", 70, 0, 0, 3000, 1, 1, 0, 0 },
 { "shipR-warp-down", "TOS-fwarpd", 50, 0, 0, 3000, 1, 1, 0, 0 },
 { "shipK-phaser", "TOS-fphaz", 60, 0, 0, 0, 1, 2, 0, 0 },
 { "shipK-torp", "TOS-fphoton", 50, 0, 0, 0, 1, 0, 0, 100 },
 { "shipK-torp3", "TOS-fphoton3", 50, 0, 0, 0, 1, 1, 0, 100 },
 { "shipK-alert", "TOS-falert", 35, 0, 0, 0, 0, 1, 0, 0 },
 { "shipK-beam-down", "TOS-fbeamd", 100, 0, 0, 1000, 1, 1, 0, 0 },
 { "shipK-beam-up", "TOS-fbeamu", 100, 0, 0, 1000, 1, 1, 0, 0 },
 { "shipK-hit", "TOS-fblast", 100, 0, 0, 1000, 1, 1, 0, 0 },
 { "shipK-info", "TOS-finfo", 70, 0, 0, 0, 1, 1, 0, 60000 },
 { "shipK-mag", "TOS-fmag", 70, 0, 0, 0, 1, 1, 0, 60000 },
 { "shipK-warp-up", "TOS-fwarpu", 70, 0, 0, 3000, 1, 1, 0, 0 },
 { "shipK-warp-down", "TOS-fwarpd", 50, 0, 0, 3000, 1, 1, 0, 0 },
 { "shipO-phaser", "TOS-fphaz", 60, 0, 0, 0, 1, 2, 0, 0 },
 { "shipO-torp", "TOS-fphoton", 40, 0, 0, 0, 1, 0, 0, 100 },
 { "shipO-torp3", "TOS-fphoton3", 50, 0, 0, 0, 1, 1, 0, 100 },
 { "shipO-alert", "TOS-falert", 35, 0, 0, 0, 0, 1, 0, 0 },
 { "shipO-beam-down", "TOS-fbeamd", 100, 0, 0, 1000, 1, 1, 0, 0 },
 { "shipO-beam-up", "TOS-fbeamu", 100, 0, 0, 1000, 1, 1, 0, 0 },
 { "shipO-hit", "TOS-fblast", 100, 0, 0, 1000, 1, 1, 0, 0 },
 { "shipO-info", "TOS-finfo", 70, 0, 0, 0, 1, 1, 0, 60000 },
 { "shipO-mag", "TOS-fmag", 70, 0, 0, 0, 1, 1, 0, 60000 },
 { "shipO-warp-up", "TOS-fwarpu", 70, 0, 0, 3000, 1, 1, 0, 0 },
 { "shipO-warp-down", "TOS-fwarpd", 50, 0, 0, 3000, 1, 1, 0, 0 },
};

#endif /* _SOUNDDATA_H */
