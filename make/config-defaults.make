CNAME               ?= quake3e
DNAME               ?= quake3e.ded

BUILD_CLIENT        ?= 0
BUILD_SLIM_CLIENT   ?= 0
BUILD_SERVER        ?= 0
BUILD_GAME_STATIC   ?= 0
BUILD_GAMES         ?= 0
BUILD_LIBS          ?= 0
BUILD_GAME_QVM      ?= 0
BUILD_GAME_SO       ?= 0
BUILD_RENDERER_OPENGL ?=0
BUILD_RENDERER_JS   ?= 0
BUILD_RENDERER_OPENGL2 ?=0
BUILD_RENDERER_OPENGLES ?=0

USE_GAME_DLOPEN     ?= 0
USE_CURL_DLOPEN     ?= 0
USE_RENDERER_DLOPEN ?= 0
USE_BOTLIB_DLOPEN   ?= 0
SDL_LOADSO_DLOPEN   ?= 0
USE_OPENAL_DLOPEN   ?= 0
USE_RMLUI_DLOPEN    ?= 0
USE_OPUS_DLOPEN     ?= 0
USE_FREETYPE_DLOPEN ?= 0

USE_SDL             ?= 1
USE_CURL            ?= 0
USE_LOCAL_HEADERS   ?= 0
USE_VULKAN          ?= 0
USE_JPEG            ?= 0
USE_VULKAN_API      ?= 1
USE_Q3KEY           ?= 0
USE_IPV6            ?= 0
USE_CODEC_WAV       ?= 1
USE_CODEC_VORBIS    ?= 0
USE_CODEC_OPUS      ?= 0
USE_VIDEO_THEORA    ?= 0
USE_CIN_OGM         ?= 0
USE_CIN_WEBM        ?= 0

USE_FREETYPE        ?= 0
USE_MUMBLE          ?= 0
USE_VOIP            ?= 0
USE_LOCAL_HEADERS   ?= 0
GL_EXT_direct_state_access ?=1
GL_ARB_ES2_compatibility ?=1
GL_GLEXT_PROTOTYPES ?= 1

USE_SYSTEM_ZLIB     ?= 0
USE_SYSTEM_LIBC     ?= 1
USE_SYSTEM_CURL     ?= 0
USE_SYSTEM_JPEG     ?= 0
USE_INTERNAL_JPEG   ?= 1
USE_SYSTEM_BOTLIB   ?= 0
USE_SYSTEM_OGG      ?= 0
USE_SYSTEM_OPUS     ?= 0
USE_SYSTEM_FREETPYE ?= 0

ifndef TEMPDIR
TEMPDIR=/tmp
endif

ifndef GENERATE_DEPENDENCIES
GENERATE_DEPENDENCIES=1
endif

ifndef USE_CCACHE
USE_CCACHE=0
endif
export USE_CCACHE

ifndef USE_LOCAL_HEADERS
USE_LOCAL_HEADERS=1
endif

ifndef USE_CURL_DLOPEN
ifdef MINGW
USE_CURL_DLOPEN=0
else
USE_CURL_DLOPEN=1
endif
endif

ifneq ($(USE_RENDERER_DLOPEN),0)
USE_VULKAN=1
endif

ifneq ($(USE_VULKAN),0)
USE_VULKAN_API=1
endif


###################################################################


CC              ?= gcc
CXX             ?= c++
GXX             ?= g++
ASM             ?= yasm
LD              ?= $(CC)


###################################################################


# common qvm definition
ifeq ($(ARCH),x86_64)
  HAVE_VM_COMPILED ?= true
else
ifeq ($(ARCH),x86)
  HAVE_VM_COMPILED ?= true
else
  HAVE_VM_COMPILED ?= false
endif
endif

ifeq ($(ARCH),arm)
  HAVE_VM_COMPILED ?= true
endif
ifeq ($(ARCH),aarch64)
  HAVE_VM_COMPILED ?= true
endif

BASE_CFLAGS   :=

ifeq ($(USE_DIDYOUMEAN),1)
  BASE_CFLAGS += -DUSE_DIDYOUMEAN
endif

ifeq ($(USE_PRINT_CONSOLE),1)
  BASE_CFLAGS += -DUSE_PRINT_CONSOLE
endif

ifeq ($(USE_PERSIST_CONSOLE),1)
  BASE_CFLAGS += -DUSE_PERSIST_CONSOLE
endif

ifeq ($(USE_NO_CONSOLE),1)
  BASE_CFLAGS += -DUSE_NO_CONSOLE
endif

ifeq ($(USE_ENGINE_TELE),1)
  BASE_CFLAGS += -DUSE_ENGINE_TELE
endif

ifeq ($(USE_LIVE_RELOAD),1)
  BASE_CFLAGS += -DUSE_LIVE_RELOAD
endif

ifeq ($(BUILD_GAME_STATIC),1)
  BASE_CFLAGS += -DBUILD_GAME_STATIC
else
unexport BUILD_GAME_STATIC
endif

ifeq ($(BUILD_EXPERIMENTAL),1)
  BASE_CFLAGS += -DBUILD_EXPERIMENTAL
  USE_MEMORY_MAPS := 1
endif

ifeq ($(USE_UNLOCKED_CVARS),1)
  BASE_CFLAGS += -DUSE_UNLOCKED_CVARS
endif

ifeq ($(USE_ASYNCHRONOUS),1)
  BASE_CFLAGS += -DUSE_ASYNCHRONOUS
endif

ifeq ($(USE_LAZY_LOAD),1)
  BASE_CFLAGS += -DUSE_LAZY_LOAD
endif

ifeq ($(USE_LAZY_MEMORY),1)
  BASE_CFLAGS += -DUSE_LAZY_MEMORY
endif

ifeq ($(USE_MEMORY_MAPS),1)
  BASE_CFLAGS += -DUSE_MEMORY_MAPS
endif

ifeq ($(USE_MV),1)
  BASE_CFLAGS += -DUSE_MV
endif

ifeq ($(USE_MULTIVM_CLIENT),1)
  BASE_CFLAGS += -DUSE_MULTIVM_CLIENT -DUSE_MV
endif

ifeq ($(USE_MULTIVM_SERVER),1)
  BASE_CFLAGS += -DUSE_MULTIVM_SERVER -DUSE_MV
endif

ifeq ($(USE_SERVER_ROLES),1)
  BASE_CFLAGS += -DUSE_SERVER_ROLES
endif

ifeq ($(USE_REFEREE_CMDS),1)
  BASE_CFLAGS += -DUSE_REFEREE_CMDS
endif

ifeq ($(USE_RECENT_EVENTS),1)
  BASE_CFLAGS += -DUSE_RECENT_EVENTS
endif

ifeq ($(USE_CVAR_UNCHEAT),1)
  BASE_CFLAGS += -DUSE_CVAR_UNCHEAT
endif

ifeq ($(USE_SYSTEM_JPEG),1)
  BASE_CFLAGS += -DUSE_SYSTEM_JPEG
  USE_INTERNAL_JPEG :=
endif

ifeq ($(USE_INTERNAL_JPEG),1)
  BASE_CFLAGS += -DUSE_INTERNAL_JPEG
endif

ifeq ($(USE_DYNAMIC_ZIP),1)
  BASE_CFLAGS += -DUSE_DYNAMIC_ZIP
endif

ifeq ($(USE_DEMO_CLIENTS),1)
  BASE_CFLAGS += -DUSE_DEMO_CLIENTS
endif

ifeq ($(USE_DEMO_SERVER),1)
  BASE_CFLAGS += -DUSE_DEMO_CLIENTS
endif
ifeq ($(USE_BOTLIB_DLOPEN),1)
  BASE_CFLAGS += -DUSE_BOTLIB_DLOPEN
  BASE_CFLAGS += -DBOTLIB_PREFIX=$(CNAME)
endif

ifeq ($(USE_RENDERER_DLOPEN),1)
  BASE_CFLAGS += -DUSE_RENDERER_DLOPEN
  BASE_CFLAGS += -DRENDERER_PREFIX=$(CNAME)
endif

ifeq ($(USE_CODEC_WAV),1)
  BASE_CFLAGS += -DUSE_CODEC_WAV=1
endif

ifeq ($(USE_CODEC_VORBIS),1)
  BASE_CFLAGS += -DUSE_CODEC_VORBIS=1
endif

ifeq ($(USE_BSP1),1)
  BASE_CFLAGS += -DUSE_BSP1
endif

ifeq ($(USE_CIN_WEBM),1)
  BASE_CFLAGS += -DUSE_CIN_WEBM=1
endif

ifeq ($(USE_CIN_OGM),1)
  BASE_CFLAGS += -DUSE_CIN_OGM=1
endif

ifeq ($(USE_VIDEO_THEORA),1)
  BASE_CFLAGS += -DUSE_VIDEO_THEORA=1
endif

ifeq ($(USE_VIDEO_XVID),1)
  BASE_CFLAGS += -DUSE_VIDEO_XVID=1
endif

ifeq ($(USE_CIN_VPX),1)
  BASE_CFLAGS += -DUSE_CIN_VPX=1
endif

ifeq ($(DEDICATED),1)
  BASE_CFLAGS += -DDEDICATED
endif
ifeq ($(USE_DEDICATED),1)
  BASE_CFLAGS += -DDEDICATED
endif

ifeq ($(BUILD_SLIM_CLIENT),1)
  BASE_CFLAGS += -DBUILD_SLIM_CLIENT
endif

ifeq ($(USE_RMLUI),1)
  BASE_CFLAGS += -DUSE_RMLUI=1
endif

ifeq ($(USE_RMLUI_DLOPEN),1)
  BASE_CFLAGS += -DUSE_RMLUI_DLOPEN=1
endif

ifeq ($(USE_DRAGDROP),1)
  BASE_CFLAGS += -DUSE_DRAGDROP=1
endif

ifeq ($(USE_LOCAL_HEADERS),1)
  BASE_CFLAGS += -DUSE_LOCAL_HEADERS=1
endif

ifeq ($(USE_VULKAN_API),1)
  BASE_CFLAGS += -DUSE_VULKAN_API
endif

ifeq ($(GENERATE_DEPENDENCIES),1)
  BASE_CFLAGS += -MMD
endif

ifneq ($(HAVE_VM_COMPILED),true)
  BASE_CFLAGS += -DNO_VM_COMPILED
endif

ifeq ($(BUILD_STANDALONE),1)
  BASE_CFLAGS += -DSTANDALONE
endif

ifeq ($(USE_Q3KEY),1)
  BASE_CFLAGS += -DUSE_Q3KEY -DUSE_MD5
endif

ifeq ($(NOFPU),1)
  BASE_CFLAGS += -DNOFPU
endif

ifeq ($(USE_CURL),1)
  BASE_CFLAGS += -DUSE_CURL
ifeq ($(USE_CURL_DLOPEN),1)
  BASE_CFLAGS += -DUSE_CURL_DLOPEN
else
ifeq ($(MINGW),1)
  BASE_CFLAGS += -DCURL_STATICLIB
endif
endif
endif

#ifdef DEFAULT_BASEDIR
#  BASE_CFLAGS += -DDEFAULT_BASEDIR=\\\"$(DEFAULT_BASEDIR)\\\"
#endif
