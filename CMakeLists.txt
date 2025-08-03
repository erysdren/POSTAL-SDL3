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
add_compile_definitions(ALLOW_TWINSTICK PLATFORM_UNIX LOCALE=US TARGET=POSTAL_2015)

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

add_executable(postal1
	${PROJECT_SOURCE_DIR}/AnimThing.cpp
	${PROJECT_SOURCE_DIR}/ball.cpp
	${PROJECT_SOURCE_DIR}/barrel.cpp
	${PROJECT_SOURCE_DIR}/bouy.cpp
	${PROJECT_SOURCE_DIR}/character.cpp
	${PROJECT_SOURCE_DIR}/chunk.cpp
	${PROJECT_SOURCE_DIR}/deathWad.cpp
	${PROJECT_SOURCE_DIR}/demon.cpp
	${PROJECT_SOURCE_DIR}/dispenser.cpp
	${PROJECT_SOURCE_DIR}/doofus.cpp
	${PROJECT_SOURCE_DIR}/dude.cpp
	${PROJECT_SOURCE_DIR}/explode.cpp
	${PROJECT_SOURCE_DIR}/fire.cpp
	${PROJECT_SOURCE_DIR}/fireball.cpp
	${PROJECT_SOURCE_DIR}/firebomb.cpp
	${PROJECT_SOURCE_DIR}/flag.cpp
	${PROJECT_SOURCE_DIR}/flagbase.cpp
	${PROJECT_SOURCE_DIR}/grenade.cpp
	${PROJECT_SOURCE_DIR}/heatseeker.cpp
	${PROJECT_SOURCE_DIR}/hood.cpp
	${PROJECT_SOURCE_DIR}/item3d.cpp
	${PROJECT_SOURCE_DIR}/mine.cpp
	${PROJECT_SOURCE_DIR}/napalm.cpp
	${PROJECT_SOURCE_DIR}/navnet.cpp
	${PROJECT_SOURCE_DIR}/ostrich.cpp
	${PROJECT_SOURCE_DIR}/person.cpp
	${PROJECT_SOURCE_DIR}/PowerUp.cpp
	${PROJECT_SOURCE_DIR}/pylon.cpp
	${PROJECT_SOURCE_DIR}/rocket.cpp
	${PROJECT_SOURCE_DIR}/sentry.cpp
	${PROJECT_SOURCE_DIR}/SndRelay.cpp
	${PROJECT_SOURCE_DIR}/SoundThing.cpp
	${PROJECT_SOURCE_DIR}/thing.cpp
	${PROJECT_SOURCE_DIR}/Thing3d.cpp
	${PROJECT_SOURCE_DIR}/trigger.cpp
	${PROJECT_SOURCE_DIR}/warp.cpp
	${PROJECT_SOURCE_DIR}/weapon.cpp
	${PROJECT_SOURCE_DIR}/alphablitforpostal.cpp
	${PROJECT_SOURCE_DIR}/Anim3D.cpp
	${PROJECT_SOURCE_DIR}/BufQ.cpp
	${PROJECT_SOURCE_DIR}/bulletFest.cpp
	${PROJECT_SOURCE_DIR}/camera.cpp
	${PROJECT_SOURCE_DIR}/crawler.cpp
	${PROJECT_SOURCE_DIR}/cutscene.cpp
	${PROJECT_SOURCE_DIR}/encrypt.cpp
	${PROJECT_SOURCE_DIR}/gameedit.cpp
	${PROJECT_SOURCE_DIR}/GameSettings.cpp
	${PROJECT_SOURCE_DIR}/grip.cpp
	${PROJECT_SOURCE_DIR}/IdBank.cpp
	${PROJECT_SOURCE_DIR}/InputSettings.cpp
	${PROJECT_SOURCE_DIR}/InputSettingsDlg.cpp
	${PROJECT_SOURCE_DIR}/keys.cpp
	${PROJECT_SOURCE_DIR}/Log.cpp
	${PROJECT_SOURCE_DIR}/logtab.cpp
	${PROJECT_SOURCE_DIR}/MemFileFest.cpp
	${PROJECT_SOURCE_DIR}/MenuSettings.cpp
	${PROJECT_SOURCE_DIR}/MenuTrans.cpp
	${PROJECT_SOURCE_DIR}/net.cpp
	${PROJECT_SOURCE_DIR}/NetBrowse.cpp
	${PROJECT_SOURCE_DIR}/NetClient.cpp
	${PROJECT_SOURCE_DIR}/NetDlg.cpp
	${PROJECT_SOURCE_DIR}/netmsgr.cpp
	${PROJECT_SOURCE_DIR}/NetServer.cpp
	${PROJECT_SOURCE_DIR}/organ.cpp
	${PROJECT_SOURCE_DIR}/Personatorium.cpp
	${PROJECT_SOURCE_DIR}/ProtoBSDIP.cpp
	${PROJECT_SOURCE_DIR}/realm.cpp
	${PROJECT_SOURCE_DIR}/scene.cpp
	${PROJECT_SOURCE_DIR}/score.cpp
	${PROJECT_SOURCE_DIR}/settings.cpp
	${PROJECT_SOURCE_DIR}/smash.cpp
	${PROJECT_SOURCE_DIR}/socket.cpp
	${PROJECT_SOURCE_DIR}/StockPile.cpp
	${PROJECT_SOURCE_DIR}/TexEdit.cpp
	${PROJECT_SOURCE_DIR}/toolbar.cpp
	${PROJECT_SOURCE_DIR}/TriggerRegions.cpp
	${PROJECT_SOURCE_DIR}/update.cpp
	${PROJECT_SOURCE_DIR}/yatime.cpp
	${PROJECT_SOURCE_DIR}/aivars.cpp
	${PROJECT_SOURCE_DIR}/band.cpp
	${PROJECT_SOURCE_DIR}/credits.cpp
	${PROJECT_SOURCE_DIR}/game.cpp
	${PROJECT_SOURCE_DIR}/input.cpp
	${PROJECT_SOURCE_DIR}/localize.cpp
	${PROJECT_SOURCE_DIR}/main.cpp
	${PROJECT_SOURCE_DIR}/menus.cpp
	${PROJECT_SOURCE_DIR}/play.cpp
	${PROJECT_SOURCE_DIR}/SampleMaster.cpp
	${PROJECT_SOURCE_DIR}/title.cpp
)
target_link_libraries(postal1 PRIVATE WishPiX RSPiX SDL3::SDL3)

if(BUILD_EXTRAS)
	add_executable(saktool ${PROJECT_SOURCE_DIR}/saktool.c)
endif()
