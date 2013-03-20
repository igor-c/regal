# glut.inc
#
# Generic gnumake .inc for building GLUT
#

# Sources

# NOT for windows...

GLUT.C += src/glut/src/capturexfont.c
GLUT.C += src/glut/src/glut_glxext.c
GLUT.C += src/glut/src/glut_menu.c
GLUT.C += src/glut/src/glut_menu2.c
GLUT.C += src/glut/src/layerutil.c

# Windows and Linux...

GLUT.C += src/glut/src/glut_8x13.c
GLUT.C += src/glut/src/glut_9x15.c
GLUT.C += src/glut/src/glut_bitmap.c
GLUT.C += src/glut/src/glut_bwidth.c
GLUT.C += src/glut/src/glut_cindex.c
GLUT.C += src/glut/src/glut_cmap.c
GLUT.C += src/glut/src/glut_cursor.c
GLUT.C += src/glut/src/glut_dials.c
GLUT.C += src/glut/src/glut_dstr.c
GLUT.C += src/glut/src/glut_event.c
GLUT.C += src/glut/src/glut_ext.c
GLUT.C += src/glut/src/glut_fcb.c
GLUT.C += src/glut/src/glut_fullscrn.c
GLUT.C += src/glut/src/glut_gamemode.c
GLUT.C += src/glut/src/glut_get.c
GLUT.C += src/glut/src/glut_hel10.c
GLUT.C += src/glut/src/glut_hel12.c
GLUT.C += src/glut/src/glut_hel18.c
GLUT.C += src/glut/src/glut_init.c
GLUT.C += src/glut/src/glut_input.c
GLUT.C += src/glut/src/glut_joy.c
GLUT.C += src/glut/src/glut_key.c
GLUT.C += src/glut/src/glut_keyctrl.c
GLUT.C += src/glut/src/glut_keyup.c
GLUT.C += src/glut/src/glut_mesa.c
GLUT.C += src/glut/src/glut_modifier.c
GLUT.C += src/glut/src/glut_mroman.c
GLUT.C += src/glut/src/glut_overlay.c
GLUT.C += src/glut/src/glut_roman.c
GLUT.C += src/glut/src/glut_shapes.c
GLUT.C += src/glut/src/glut_space.c
GLUT.C += src/glut/src/glut_stroke.c
GLUT.C += src/glut/src/glut_swap.c
GLUT.C += src/glut/src/glut_swidth.c
GLUT.C += src/glut/src/glut_tablet.c
GLUT.C += src/glut/src/glut_teapot.c
GLUT.C += src/glut/src/glut_tr10.c
GLUT.C += src/glut/src/glut_tr24.c
GLUT.C += src/glut/src/glut_util.c
GLUT.C += src/glut/src/glut_vidresize.c
GLUT.C += src/glut/src/glut_warp.c
GLUT.C += src/glut/src/glut_win.c
GLUT.C += src/glut/src/glut_winmisc.c
GLUT.C += src/glut/src/glut_ppm.c
