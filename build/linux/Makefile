#
# edawn Makefile
#
# GNU Make required
#

LAST_MAKEFILE :=  $(lastword $(MAKEFILE_LIST))
COMPILE_PLATFORM=$(shell uname | sed -e 's/_.*//' | tr '[:upper:]' '[:lower:]' | sed -e 's/\//_/g')
COMPILE_ARCH=$(shell uname -m | sed -e 's/i.86/x86/' | sed -e 's/^arm.*/arm/')

ifeq ($(COMPILE_PLATFORM),mingw32)
  ifeq ($(COMPILE_ARCH),i386)
    COMPILE_ARCH=x86
  endif
endif

#############################################################################
#
# If you require a different configuration from the defaults below, create a
# new file named "Makefile.local" in the same directory as this file and define
# your parameters there. This allows you to change configuration without
# causing problems with keeping up to date with the repository.
#
#############################################################################
-include Makefile.local

ifndef MOD
MOD=multigame
endif
ifdef MISSIONPACK
MOD=multigame-ta
endif

ifeq ($(COMPILE_PLATFORM),cygwin)
  PLATFORM=mingw32
endif

ifndef PLATFORM
PLATFORM=$(COMPILE_PLATFORM)
endif
export PLATFORM

ifeq ($(PLATFORM),mingw32)
  MINGW=1
endif
ifeq ($(PLATFORM),mingw64)
  MINGW=1
endif

ifeq ($(COMPILE_ARCH),i86pc)
  COMPILE_ARCH=x86
endif

ifeq ($(COMPILE_ARCH),amd64)
  COMPILE_ARCH=x86_64
endif
ifeq ($(COMPILE_ARCH),x64)
  COMPILE_ARCH=x86_64
endif

ifndef ARCH
ARCH=$(COMPILE_ARCH)
endif
export ARCH

ifneq ($(PLATFORM),$(COMPILE_PLATFORM))
  CROSS_COMPILING=1
else
  CROSS_COMPILING=0

  ifneq ($(ARCH),$(COMPILE_ARCH))
    CROSS_COMPILING=1
  endif
endif
export CROSS_COMPILING

#ifndef MOD_CFLAGS
#MOD_CFLAGS= -std=c99
#endif

ifndef BUILD_DIR
BUILD_DIR=build
endif

ifndef TEMPDIR
TEMPDIR=/tmp
endif

ifndef MOUNT_DIR
MOUNT_DIR=../../code
endif

ifndef DEBUG_CFLAGS
DEBUG_CFLAGS=-g -O0
endif

#############################################################################

BD=$(BUILD_DIR)/debug-$(PLATFORM)-$(ARCH)
BR=$(BUILD_DIR)/release-$(PLATFORM)-$(ARCH)

QADIR=$(MOUNT_DIR)/game
CGDIR=$(MOUNT_DIR)/cgame
UIDIR=$(MOUNT_DIR)/ui
QUIDIR=$(MOUNT_DIR)/q3_ui
SYSCALL=$(MOUNT_DIR)/../build/win32-qvm

bin_path=$(shell which $(1) 2> /dev/null)

#############################################################################
# SETUP AND BUILD -- LINUX
#############################################################################

## Defaults
LIB=lib

INSTALL=install
MKDIR=mkdir
LD := $(CC)
ZIP = zip -9 -r

QVM_CFLAGS := -DQ3_VM 
QVM_LDFLAGS := -vq3 -r -m -v 
QVM_CC ?= ../../../q3lcc -v 
QVM_LD ?= ../../../q3asm

ifeq ($(PLATFORM),darwin)

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes -pipe

  OPTIMIZE = -O2 -fvisibility=hidden -fomit-frame-pointer # -ffast-math

  SHLIBEXT         := dylib
  SHLIBCFLAGS      := -fPIC -fvisibility=hidden -fno-common
  SHLIBLDFLAGS     := -dynamiclib -rdynamic -shared $(LDFLAGS)

  LIBS= -lm

endif

ifeq ($(PLATFORM),linux)

  ifeq ($(ARCH),x86_64)
    LIB=lib64
  endif

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes -pipe

  OPTIMIZE = -O2 -fvisibility=hidden -fomit-frame-pointer -ffast-math

  SHLIBEXT=so
  SHLIBCFLAGS=-fPIC -fvisibility=hidden
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  LIBS= -lm

  ifeq ($(ARCH),x86)
    BASE_CFLAGS += -m32
  endif

endif #Linux


ifdef MINGW

  ifeq ($(CROSS_COMPILING),1)
    # If CC is already set to something generic, we probably want to use
    # something more specific
    ifneq ($(findstring $(strip $(CC)),cc gcc),)
      CC=
    endif

    # We need to figure out the correct gcc and windres
    ifeq ($(ARCH),x86_64)
      MINGW_PREFIXES=x86_64-w64-mingw32 amd64-mingw32msvc
      STRIP=x86_64-w64-mingw32-strip
    endif
    ifeq ($(ARCH),x86)
      MINGW_PREFIXES=i686-w64-mingw32 i586-mingw32msvc i686-pc-mingw32
    endif

    ifndef CC
      CC=$(firstword $(strip $(foreach MINGW_PREFIX, $(MINGW_PREFIXES), \
         $(call bin_path, $(MINGW_PREFIX)-gcc))))
    endif

#   STRIP=$(MINGW_PREFIX)-strip -g

    ifndef WINDRES
      WINDRES=$(firstword $(strip $(foreach MINGW_PREFIX, $(MINGW_PREFIXES), \
         $(call bin_path, $(MINGW_PREFIX)-windres))))
    endif
  else
    # Some MinGW installations define CC to cc, but don't actually provide cc,
    # so check that CC points to a real binary and use gcc if it doesn't
    ifeq ($(call bin_path, $(CC)),)
      CC=gcc
    endif

  endif

  BASE_CFLAGS = -Wall -fno-strict-aliasing -Wimplicit -Wstrict-prototypes -pipe

  OPTIMIZE = -O2 -fvisibility=hidden -fomit-frame-pointer -ffast-math

  SHLIBEXT=dll
  SHLIBCFLAGS=-fPIC -fvisibility=hidden
  SHLIBLDFLAGS=-shared $(LDFLAGS)

  LIBS= -lm

  ifeq ($(ARCH),x86)
    BASE_CFLAGS += -m32
  endif

endif


TARGETS =

ifndef FULLBINEXT
  FULLBINEXT=.$(ARCH)$(BINEXT)
endif

ifndef SHLIBNAME
  SHLIBNAME=$(ARCH).$(SHLIBEXT)
endif

ifeq ($(PLATFORM),qvms)
TARGET_QVMS = \
  $(B)/$(MOD)/vm/cgame.qvm \
  $(B)/$(MOD)/vm/qagame.qvm \
  $(B)/$(MOD)/vm/ui.qvm

TARGETS += $(TARGET_QVMS) xxx-$(MOD).pk3
else
TARGETS += \
  $(B)/$(MOD)/cgame$(SHLIBNAME) \
  $(B)/$(MOD)/qagame$(SHLIBNAME) \
  $(B)/$(MOD)/ui$(SHLIBNAME)
endif

ifdef MISSIONPACK
BASE_CFLAGS += -DMISSIONPACK=1
QVM_CFLAGS += -DMISSIONPACK=1
endif

ifeq ("$(CC)", $(findstring "$(CC)", "clang" "clang++"))
  BASE_CFLAGS += -Qunused-arguments
endif

ifdef DEFAULT_BASEDIR
  BASE_CFLAGS += -DDEFAULT_BASEDIR=\\\"$(DEFAULT_BASEDIR)\\\"
endif

ifeq ($(NO_STRIP),1)
  STRIP_FLAG =
else
  STRIP_FLAG = -s
endif

BASE_CFLAGS += -Wformat=2 -Wno-format-zero-length -Wformat-security -Wno-format-nonliteral
BASE_CFLAGS += -Wstrict-aliasing=2 -Wmissing-format-attribute
BASE_CFLAGS += -Wdisabled-optimization
BASE_CFLAGS += -Werror-implicit-function-declaration

ifeq ($(V),1)
echo_cmd=@:
Q=
else
echo_cmd=@echo
Q=@
endif

define DO_CC
$(echo_cmd) "CC $<"
$(Q)$(CC) $(NOTSHLIBCFLAGS) $(CFLAGS) $(OPTIMIZE) -o $@ -c $<
endef

define DO_SHLIB_CC
$(echo_cmd) "SHLIB_CC $<"
$(Q)$(CC) $(MOD_CFLAGS) $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZE) -o $@ -c $<
endef

define DO_GAME_LCC
$(echo_cmd) "GAME_LCC $<"
$(Q)$(QVM_CC) $(QVM_CFLAGS) -DQAGAME -o $@ -c $<
endef

define DO_CGAME_LCC
$(echo_cmd) "CGAME_LCC $<"
$(Q)$(QVM_CC) $(QVM_CFLAGS) -DCGAME -o $@ -c $<
endef

define DO_UI_LCC
$(echo_cmd) "UI_LCC $<"
$(Q)$(QVM_CC) $(QVM_CFLAGS) -DUI -o $@ -c $<
endef

define DO_GAME_CC
$(echo_cmd) "GAME_CC $<"
$(Q)$(CC) $(MOD_CFLAGS) -DQAGAME $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZE) -o $@ -c $<
endef

define DO_CGAME_CC
$(echo_cmd) "CGAME_CC $<"
$(Q)$(CC) $(MOD_CFLAGS) -DCGAME $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZE) -o $@ -c $<
endef

define DO_UI_CC
$(echo_cmd) "UI_CC $<"
$(Q)$(CC) $(MOD_CFLAGS) -DUI $(SHLIBCFLAGS) $(CFLAGS) $(OPTIMIZE) -o $@ -c $<
endef

#############################################################################
# MAIN TARGETS
#############################################################################

default: release
all: debug release

debug:
	@$(MAKE)  targets B=$(BD) CFLAGS="$(CFLAGS) $(BASE_CFLAGS)" \
	  OPTIMIZE="$(DEBUG_CFLAGS)" V=$(V)

release:
	@$(MAKE)  targets B=$(BR) CFLAGS="$(CFLAGS) $(BASE_CFLAGS)" \
	  OPTIMIZE="-DNDEBUG $(OPTIMIZE)" V=$(V)

# Create the build directories, check libraries and print out
# an informational message, then start building
targets: makedirs
	@echo ""
	@echo "Building $(CLIENTBIN) in $(B):"
	@echo "  PLATFORM: $(PLATFORM)"
	@echo "  ARCH: $(ARCH)"
	@echo "  COMPILE_PLATFORM: $(COMPILE_PLATFORM)"
	@echo "  COMPILE_ARCH: $(COMPILE_ARCH)"
	@echo "  CC: $(CC)"
	@echo ""
	@echo "  CFLAGS:"
	-@for i in $(CFLAGS); \
	do \
		echo "    $$i"; \
	done
	-@for i in $(OPTIMIZE); \
	do \
		echo "    $$i"; \
	done
	@echo ""
	@echo "  LDFLAGS:"
	-@for i in $(LDFLAGS); \
	do \
		echo "    $$i"; \
	done
	@echo ""
	@echo "  LIBS:"
	-@for i in $(LIBS); \
	do \
		echo "    $$i"; \
	done
	@echo ""
	@echo "  Output:"
	-@for i in $(TARGETS); \
	do \
		echo "    $$i"; \
	done
	@echo ""

ifneq ($(TARGETS),)
	@$(MAKE)  $(TARGETS) V=$(V)
endif

makedirs:
	@if [ ! -d $(BUILD_DIR) ];then $(MKDIR) $(BUILD_DIR);fi
	@if [ ! -d $(B) ];then $(MKDIR) $(B);fi
	@if [ ! -d $(B)/$(MOD) ];then $(MKDIR) $(B)/$(MOD);fi
	@if [ ! -d $(B)/$(MOD)/cgame ];then $(MKDIR) $(B)/$(MOD)/cgame;fi
	@if [ ! -d $(B)/$(MOD)/game ];then $(MKDIR) $(B)/$(MOD)/game;fi
	@if [ ! -d $(B)/$(MOD)/q3_ui ];then $(MKDIR) $(B)/$(MOD)/q3_ui;fi
	@if [ ! -d $(B)/$(MOD)/ui ];then $(MKDIR) $(B)/$(MOD)/ui;fi
	@if [ ! -d $(B)/$(MOD)/vm ];then $(MKDIR) $(B)/$(MOD)/vm;fi
	@if [ ! -d $(B)/$(MOD)/vm/cgame ];then $(MKDIR) $(B)/$(MOD)/vm/cgame;fi
	@if [ ! -d $(B)/$(MOD)/vm/game ];then $(MKDIR) $(B)/$(MOD)/vm/game;fi
	@if [ ! -d $(B)/$(MOD)/vm/q3_ui ];then $(MKDIR) $(B)/$(MOD)/vm/q3_ui;fi
	@if [ ! -d $(B)/$(MOD)/vm/ui ];then $(MKDIR) $(B)/$(MOD)/vm/ui;fi

#############################################################################
## BASEQ3 CGAME
#############################################################################
# $(B)/$(MOD)/cgame/cg_particles.o \

CGOBJ_ = \
  $(B)/$(MOD)/cgame/cg_main.o \
  $(B)/$(MOD)/cgame/bg_lib.o \
  $(B)/$(MOD)/cgame/bg_misc.o \
  $(B)/$(MOD)/cgame/bg_pmove.o \
  $(B)/$(MOD)/cgame/bg_pmove_ball.o \
  $(B)/$(MOD)/cgame/bg_physics.o \
  $(B)/$(MOD)/cgame/bg_wheel_forces.o \
  $(B)/$(MOD)/cgame/bg_slidemove.o \
  $(B)/$(MOD)/cgame/bg_tracemap.o \
  $(B)/$(MOD)/cgame/cg_atmospheric.o \
  $(B)/$(MOD)/cgame/cg_consolecmds.o \
  $(B)/$(MOD)/cgame/cg_draw.o \
  $(B)/$(MOD)/cgame/cg_newdraw.o \
  $(B)/$(MOD)/cgame/cg_drawtools.o \
  $(B)/$(MOD)/cgame/cg_effects.o \
  $(B)/$(MOD)/cgame/cg_ents.o \
  $(B)/$(MOD)/cgame/cg_event.o \
  $(B)/$(MOD)/cgame/cg_info.o \
  $(B)/$(MOD)/cgame/cg_localents.o \
  $(B)/$(MOD)/cgame/cg_marks.o \
  $(B)/$(MOD)/cgame/cg_players.o \
  $(B)/$(MOD)/cgame/cg_playerstate.o \
  $(B)/$(MOD)/cgame/cg_polybus.o \
  $(B)/$(MOD)/cgame/cg_predict.o \
  $(B)/$(MOD)/cgame/cg_rally.o \
  $(B)/$(MOD)/cgame/cg_runes.o \
  $(B)/$(MOD)/cgame/cg_scoreboard.o \
  $(B)/$(MOD)/cgame/cg_servercmds.o \
  $(B)/$(MOD)/cgame/cg_snapshot.o \
  $(B)/$(MOD)/cgame/cg_trails.o \
  $(B)/$(MOD)/cgame/cg_timer.o \
  $(B)/$(MOD)/cgame/cg_view.o \
  $(B)/$(MOD)/cgame/cg_weapons.o \
  $(B)/$(MOD)/cgame/cg_weapons2.o \
  $(B)/$(MOD)/cgame/cg_weaporder.o \
  \
  $(B)/$(MOD)/cgame/q_math.o \
  $(B)/$(MOD)/cgame/q_shared.o


CGOBJ   = $(CGOBJ_) $(B)/$(MOD)/cgame/cg_syscalls.o
CGASM   = $(subst /cgame/,/vm/cgame/,$(CGOBJ_:.o=.asm)) $(CGDIR)/cg_syscalls.asm
#ifdef MISSIONPACK
CGOBJ  += $(B)/$(MOD)/cgame/ui_shared.o
CGASM  += $(B)/$(MOD)/vm/cgame/ui_shared.asm
#endif

$(B)/$(MOD)/vm/cgame.qvm: $(CGASM)
	$(echo_cmd) "LD $@"
	$(Q)$(QVM_LD) $(QVM_LDFLAGS) -o $@ $(CGASM)

$(B)/$(MOD)/cgame$(SHLIBNAME): $(CGOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(CGOBJ)

#############################################################################
## BASEQ3 GAME
#############################################################################

QAOBJ_ = \
  $(B)/$(MOD)/game/g_main.o \
  $(B)/$(MOD)/game/ai_chat.o \
  $(B)/$(MOD)/game/ai_cmd.o \
  $(B)/$(MOD)/game/ai_dmnet.o \
  $(B)/$(MOD)/game/ai_dmq3.o \
  $(B)/$(MOD)/game/ai_main.o \
  $(B)/$(MOD)/game/ai_team.o \
  $(B)/$(MOD)/game/ai_vcmd.o \
  $(B)/$(MOD)/game/bg_lib.o \
  $(B)/$(MOD)/game/bg_misc.o \
  $(B)/$(MOD)/game/bg_pmove.o \
  $(B)/$(MOD)/game/bg_pmove_ball.o \
  $(B)/$(MOD)/game/bg_physics.o \
  $(B)/$(MOD)/game/bg_wheel_forces.o \
  $(B)/$(MOD)/game/bg_slidemove.o \
  $(B)/$(MOD)/game/g_active.o \
  $(B)/$(MOD)/game/g_arenas.o \
  $(B)/$(MOD)/game/g_bot.o \
  $(B)/$(MOD)/game/g_client.o \
  $(B)/$(MOD)/game/g_cmds.o \
  $(B)/$(MOD)/game/g_combat.o \
  $(B)/$(MOD)/game/g_items.o \
  $(B)/$(MOD)/game/g_mem.o \
  $(B)/$(MOD)/game/g_misc.o \
  $(B)/$(MOD)/game/g_portal.o \
  $(B)/$(MOD)/game/g_powerup.o \
  $(B)/$(MOD)/game/g_missile.o \
  $(B)/$(MOD)/game/g_mover.o \
  $(B)/$(MOD)/game/g_rotation.o \
  $(B)/$(MOD)/game/g_session.o \
  $(B)/$(MOD)/game/g_spawn.o \
  $(B)/$(MOD)/game/g_svcmds.o \
  $(B)/$(MOD)/game/g_target.o \
  $(B)/$(MOD)/game/g_team.o \
  $(B)/$(MOD)/game/g_trigger.o \
  $(B)/$(MOD)/game/g_utils.o \
  $(B)/$(MOD)/game/g_unlagged.o \
  $(B)/$(MOD)/game/g_weapon.o \
  $(B)/$(MOD)/game/g_weapon2.o \
  $(B)/$(MOD)/game/g_telefrag.o \
  \
  $(B)/$(MOD)/game/q_math.o \
  $(B)/$(MOD)/game/q_shared.o

QAOBJ   = $(QAOBJ_) $(B)/$(MOD)/game/g_syscalls.o
QAASM   = $(subst /game/,/vm/game/,$(QAOBJ_:.o=.asm)) $(QADIR)/g_syscalls.asm

$(B)/$(MOD)/vm/qagame.qvm: $(QAASM)
	$(echo_cmd) "LD $@"
	$(Q)$(QVM_LD) $(QVM_LDFLAGS) -o $@ $(QAASM)

$(B)/$(MOD)/qagame$(SHLIBNAME): $(QAOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(QAOBJ)

#############################################################################
## BASEQ3 UI
#############################################################################

#ifdef MISSIONPACK
#$(B)/$(MOD)/ui/bg_misc.o
#$(B)/$(MOD)/ui/bg_lib.o
UIOBJ_ += \
  $(B)/$(MOD)/ui/sui_main.o \
  $(B)/$(MOD)/ui/sui_atoms.o \
  $(B)/$(MOD)/ui/sui_gameinfo.o \
  $(B)/$(MOD)/ui/sui_players.o \
  $(B)/$(MOD)/ui/ui_shared.o
#endif


UIOBJ_ +=   \
  $(B)/$(MOD)/q3_ui/ui_main.o \
  $(B)/$(MOD)/q3_ui/bg_misc.o \
  $(B)/$(MOD)/q3_ui/bg_lib.o \
  $(B)/$(MOD)/q3_ui/ui_atoms.o \
  $(B)/$(MOD)/q3_ui/ui_gameinfo.o \
  $(B)/$(MOD)/q3_ui/ui_players.o \
  $(B)/$(MOD)/q3_ui/ui_addbots.o \
  $(B)/$(MOD)/q3_ui/ui_cdkey.o \
  $(B)/$(MOD)/q3_ui/ui_cinematics.o \
  $(B)/$(MOD)/q3_ui/ui_confirm.o \
  $(B)/$(MOD)/q3_ui/ui_connect.o \
  $(B)/$(MOD)/q3_ui/ui_controls2.o \
  $(B)/$(MOD)/q3_ui/ui_credits.o \
  $(B)/$(MOD)/q3_ui/ui_demo2.o \
  $(B)/$(MOD)/q3_ui/ui_display.o \
  $(B)/$(MOD)/q3_ui/ui_ingame.o \
  $(B)/$(MOD)/q3_ui/ui_loadconfig.o \
  $(B)/$(MOD)/q3_ui/ui_menu.o \
  $(B)/$(MOD)/q3_ui/ui_mfield.o \
  $(B)/$(MOD)/q3_ui/ui_mods.o \
  $(B)/$(MOD)/q3_ui/ui_network.o \
  $(B)/$(MOD)/q3_ui/ui_options.o \
  $(B)/$(MOD)/q3_ui/ui_playermodel.o \
  $(B)/$(MOD)/q3_ui/ui_playersettings.o \
  $(B)/$(MOD)/q3_ui/ui_preferences.o \
  $(B)/$(MOD)/q3_ui/ui_qmenu.o \
  $(B)/$(MOD)/q3_ui/ui_removebots.o \
  $(B)/$(MOD)/q3_ui/ui_saveconfig.o \
  $(B)/$(MOD)/q3_ui/ui_serverinfo.o \
  $(B)/$(MOD)/q3_ui/ui_servers2.o \
  $(B)/$(MOD)/q3_ui/ui_setup.o \
  $(B)/$(MOD)/q3_ui/ui_sound.o \
  $(B)/$(MOD)/q3_ui/ui_sparena.o \
  $(B)/$(MOD)/q3_ui/ui_specifyserver.o \
  $(B)/$(MOD)/q3_ui/ui_splevel.o \
  $(B)/$(MOD)/q3_ui/ui_sppostgame.o \
  $(B)/$(MOD)/q3_ui/ui_spskill.o \
  $(B)/$(MOD)/q3_ui/ui_startserver.o \
  $(B)/$(MOD)/q3_ui/ui_team.o \
  $(B)/$(MOD)/q3_ui/ui_teamorders.o \
  $(B)/$(MOD)/q3_ui/ui_video.o


UIOBJ_ +=   \
  $(B)/$(MOD)/q3_ui/q_math.o \
  $(B)/$(MOD)/q3_ui/q_shared.o

UIOBJ   = $(UIOBJ_) $(B)/$(MOD)/q3_ui/ui_syscalls.o
_UIASM   = $(subst /q3_ui/,/vm/q3_ui/,$(UIOBJ_:.o=.asm))
UIASM   = $(subst /ui/,/vm/ui/,$(_UIASM:.o=.asm))
UIASM   += $(QUIDIR)/ui_syscalls.asm

$(B)/$(MOD)/vm/ui.qvm: $(UIASM)
	$(echo_cmd) "LD $@"
	$(Q)$(QVM_LD) $(QVM_LDFLAGS) -o $@ $(UIASM)

$(B)/$(MOD)/ui$(SHLIBNAME): $(UIOBJ)
	$(echo_cmd) "LD $@"
	$(Q)$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(UIOBJ)

#############################################################################
## GAME MODULE RULES
#############################################################################

$(B)/$(MOD)/vm/cgame/bg_%.asm: $(QADIR)/bg_%.c
	$(DO_CGAME_LCC)

$(B)/$(MOD)/vm/cgame/q_%.asm: $(QADIR)/q_%.c
	$(DO_CGAME_LCC)

$(B)/$(MOD)/vm/cgame/%.asm: $(CGDIR)/%.c
	$(DO_CGAME_LCC)

$(B)/$(MOD)/vm/cgame/ui_%.asm: $(UIDIR)/ui_%.c
	$(DO_CGAME_LCC)

$(B)/$(MOD)/vm/game/%.asm: $(QADIR)/%.c
	$(DO_GAME_LCC)

$(B)/$(MOD)/vm/ui/bg_%.asm: $(QADIR)/bg_%.c
	$(DO_UI_LCC)

$(B)/$(MOD)/vm/q3_ui/bg_%.asm: $(QADIR)/bg_%.c
	$(DO_UI_LCC)

$(B)/$(MOD)/vm/ui/q_%.asm: $(QADIR)/q_%.c
	$(DO_UI_LCC)

$(B)/$(MOD)/vm/q3_ui/q_%.asm: $(QADIR)/q_%.c
	$(DO_UI_LCC)

$(B)/$(MOD)/vm/ui/%.asm: $(UIDIR)/%.c
	$(DO_UI_LCC)

$(B)/$(MOD)/vm/q3_ui/%.asm: $(QUIDIR)/%.c
	$(DO_UI_LCC)

$(B)/$(MOD)/cgame/bg_%.o: $(QADIR)/bg_%.c
	$(DO_CGAME_CC)

$(B)/$(MOD)/cgame/q_%.o: $(QADIR)/q_%.c
	$(DO_CGAME_CC)

$(B)/$(MOD)/cgame/%.o: $(CGDIR)/%.c
	$(DO_CGAME_CC)

$(B)/$(MOD)/cgame/ui_%.o: $(UIDIR)/ui_%.c
	$(DO_CGAME_CC)

$(B)/$(MOD)/game/%.o: $(QADIR)/%.c
	$(DO_GAME_CC)

$(B)/$(MOD)/q3_ui/bg_%.o: $(QADIR)/bg_%.c
	$(DO_UI_CC)

$(B)/$(MOD)/q3_ui/q_%.o: $(QADIR)/q_%.c
	$(DO_UI_CC)

$(B)/$(MOD)/q3_ui/%.o: $(QUIDIR)/%.c
	$(DO_UI_CC)

$(B)/$(MOD)/ui/%.o: $(UIDIR)/%.c
	$(DO_UI_CC)

#############################################################################
# MISC
#############################################################################

OBJ = $(QAOBJ) $(CGOBJ) $(UIOBJ)

clean: clean-debug clean-release

clean-debug:
	@$(MAKE) clean2 B=$(BD)

clean-release:
	@$(MAKE) clean2 B=$(BR)

clean2:
	@echo "CLEAN $(B)"
	@rm -f $(OBJ)
	@rm -f $(TARGETS)

distclean: clean
	@rm -rf $(BUILD_DIR)


xxx-$(MOD).pk3: $(TARGET_QVMS)
	$(echo_cmd) "ZIPPING $<"
	$(Q)cd $(B)/$(MOD) && \
		$(ZIP) ../../../xxx-$(MOD).pk3 vm/*.qvm && \
		$(ZIP) -u ../../../xxx-$(MOD).pk3 vm/*.map && \
		$(ZIP) -u ../../../xxx-$(MOD).pk3 vm/*.jts
	$(Q)cd ../../assets && \
		$(ZIP) -u ../build/linux/xxx-$(MOD).pk3 ./*


#############################################################################
# DEPENDENCIES
#############################################################################

.PHONY: all clean clean2 clean-debug clean-release \
	debug default distclean makedirs \
	release targets \
	$(OBJ_D_FILES)
