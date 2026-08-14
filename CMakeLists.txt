# Configure with [fxsdk build-fx] or [fxsdk build-cg], which provide the
# toolchain file and module path of the fxSDK

cmake_minimum_required(VERSION 3.15)
project(PrizmCraft)

include(GenerateG1A)
include(GenerateG3A)
include(GenerateHH2Bin)
include(Fxconv)
find_package(Gint 2.9 REQUIRED)

set(SOURCES
  src/vector.c
  src/menu.c
  src/camera.c
  src/world.c
  src/block.c
  src/cursor.c
  src/prizm_maths.c
  src/gint-extras/image.c
  src/gint-extras/display.c
  src/main.c
  # ...
)
# Shared assets, fx-9860G-only assets and fx-CG-50-only assets
set(ASSETS
  # ...
)
set(ASSETS_fx
  assets-fx/example.png
  # ...
)
set(ASSETS_cg
  assets-cg/example.png
  assets-cg/textures.png
  # ...
)

fxconv_declare_assets(${ASSETS} ${ASSETS_fx} ${ASSETS_cg} WITH_METADATA)

add_executable(prizmcraft ${SOURCES} ${ASSETS} ${ASSETS_${FXSDK_PLATFORM}})
target_include_directories(prizmcraft PRIVATE include)
target_compile_options(prizmcraft PRIVATE -Wall -Wextra -Os -g -flto)
target_link_libraries(prizmcraft Gint::Gint)

if("${FXSDK_PLATFORM_LONG}" STREQUAL fx9860G)
  generate_g1a(TARGET prizmcraft OUTPUT "PrizmCraft.g1a"
    NAME "PrizmCraft" ICON assets-fx/icon.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fxCG50)
  generate_g3a(TARGET prizmcraft OUTPUT "PrizmCraft.g3a"
    NAME "PrizmCraft" ICONS assets-cg/icon-uns.png assets-cg/icon-sel.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fx9860G_G3A)
  generate_g3a(TARGET prizmcraft OUTPUT "PrizmCraft-fx.g3a"
    NAME "PrizmCraft-fx" ICONS assets-cg/icon-uns.png assets-cg/icon-sel.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fxCP)
  generate_hh2_bin(TARGET prizmcraft OUTPUT "PrizmCraft-hh2.bin")
endif()
