cmake_minimum_required(VERSION 3.21)
project(postal LANGUAGES C CXX)

option(USE_STATIC_SDL "Statically link SDL3" OFF)
option(BUILD_EXTRAS "Build extras" ON)

if(USE_STATIC_SDL)
	find_package(SDL3 CONFIG COMPONENTS SDL3-static)
else()
	find_package(SDL3 CONFIG COMPONENTS SDL3-shared)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	add_compile_definitions(DEBUG _DEBUG)
else()
	add_compile_definitions(NDEBUG _NDEBUG)
endif()

include_directories(${PROJECT_SOURCE_DIR})
add_compile_options(-fsigned-char -Wno-write-strings)
add_compile_definitions(ALLOW_TWINSTICK PLATFORM_UNIX)

add_library(RSPiX STATIC
	${PROJECT_SOURCE_DIR}/RSPiX/Src/BLUE/unix/Bdebug.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/BLUE/unix/Bjoy.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/BLUE/unix/Bkey.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/BLUE/unix/Bmain.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/BLUE/unix/Bmouse.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/BLUE/unix/Btime.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/BLUE/unix/Bdisp.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/BLUE/unix/Bsound.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/Hot/hot.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/Image/Image.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/Image/Imagecon.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/Image/ImageFile.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/InputEvent/InputEvent.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/Mix/mix.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/Mix/MixBuf.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/Image/pal.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/Image/PalFile.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/Sample/sample.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/Snd/snd.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/SndFx/SndFx.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/Task/task.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/3D/pipeline.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/3D/render.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/3D/types3d.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/3D/zbuffer.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/BLiT/alphablit.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/BLiT/BLIT.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/BLiT/BLITINIT.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/BLiT/BLiTT.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/BLiT/CFNT.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/BLiT/Fspr1.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/BLiT/FSPR8.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/BLiT/line.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/BLiT/mono.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/BLiT/Rotate96.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/BLiT/RPrint.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/GREEN/BLiT/ScaleFlat.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/GameLib/ANIMSPRT.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/Attribute/attribute.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/GUI/btn.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/Channel/channel.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/color/colormatch.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/DirtRect/DirtRect.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/color/dithermatch.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/GUI/dlg.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/GUI/edit.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/File/file.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/QuickMath/FixedPoint.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/GUI/guiItem.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/IFF/iff.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/ImageTools/lasso.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/Laymage/laymage.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/GUI/ListBox.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/GUI/ListContents.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/Meter/meter.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/MsgBox/MsgBox.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/GUI/MultiBtn.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/MultiGrid/MultiGrid.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/MultiGrid/MultiGridIndirect.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/GUI/ProcessGui.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/Debug/profile.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/GUI/PushBtn.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/QuickMath/QuickMath.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/GameLib/Region.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/RString/rstring.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/GUI/scrollbar.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/GameLib/SHAPES.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/Parse/SimpleBatch.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/GameLib/SPRITE.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/str/str.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/ORANGE/GUI/txt.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/CYAN/Unix/uDialog.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/CYAN/Unix/uColors.cpp
	${PROJECT_SOURCE_DIR}/RSPiX/Src/CYAN/Unix/uPath.cpp
)

target_include_directories(RSPiX PUBLIC
	${PROJECT_SOURCE_DIR}/RSPiX/Inc/
	${PROJECT_SOURCE_DIR}/RSPiX/Src/
	${PROJECT_SOURCE_DIR}/RSPiX/Src/BLUE/
)

add_library(WishPiX STATIC
	${PROJECT_SOURCE_DIR}/WishPiX/Menu/menu.cpp
	${PROJECT_SOURCE_DIR}/WishPiX/Prefs/prefline.cpp
	${PROJECT_SOURCE_DIR}/WishPiX/Prefs/prefs.cpp
	${PROJECT_SOURCE_DIR}/WishPiX/ResourceManager/resmgr.cpp
	${PROJECT_SOURCE_DIR}/WishPiX/Spry/spry.cpp
)
target_link_libraries(WishPiX PRIVATE RSPiX)

if(BUILD_EXTRAS)
	add_executable(saktool ${PROJECT_SOURCE_DIR}/saktool.c)
endif()
