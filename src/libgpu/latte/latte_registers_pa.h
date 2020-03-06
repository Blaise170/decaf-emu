#pragma once
#include "latte_enum_spi.h"
#include "latte_enum_pa.h"

#include <common/bitfield.h>
#include <cstdint>

namespace latte
{

// Clipper Control Bits
BITFIELD_BEG(PA_CL_CLIP_CNTL, uint32_t)
   BITFIELD_ENTRY(0, 1, bool, UCP_ENA_0)
   BITFIELD_ENTRY(1, 1, bool, UCP_ENA_1)
   BITFIELD_ENTRY(2, 1, bool, UCP_ENA_2)
   BITFIELD_ENTRY(3, 1, bool, UCP_ENA_3)
   BITFIELD_ENTRY(4, 1, bool, UCP_ENA_4)
   BITFIELD_ENTRY(5, 1, bool, UCP_ENA_5)
   BITFIELD_ENTRY(13, 1, bool, PS_UCP_Y_SCALE_NEG)
   BITFIELD_ENTRY(14, 2, PA_PS_UCP_MODE, PS_UCP_MODE)
   BITFIELD_ENTRY(16, 1, bool, CLIP_DISABLE)
   BITFIELD_ENTRY(17, 1, bool, UCP_CULL_ONLY_ENA)
   BITFIELD_ENTRY(18, 1, bool, BOUNDARY_EDGE_FLAG_ENA)
   BITFIELD_ENTRY(19, 1, bool, DX_CLIP_SPACE_DEF)
   BITFIELD_ENTRY(20, 1, bool, DIS_CLIP_ERR_DETECT)
   BITFIELD_ENTRY(21, 1, bool, VTX_KILL_OR)
   BITFIELD_ENTRY(22, 1, bool, RASTERISER_DISABLE)
   BITFIELD_ENTRY(24, 1, bool, DX_LINEAR_ATTR_CLIP_ENA)
   BITFIELD_ENTRY(25, 1, bool, VTE_VPORT_PROVOKE_DISABLE)
   BITFIELD_ENTRY(26, 1, bool, ZCLIP_NEAR_DISABLE)
   BITFIELD_ENTRY(27, 1, bool, ZCLIP_FAR_DISABLE)
BITFIELD_END

// Horizontal Guard Band Clip Adjust Register
BITFIELD_BEG(PA_CL_GB_HORZ_CLIP_ADJ, uint32_t)
   BITFIELD_ENTRY(0, 32, float, DATA_REGISTER)
BITFIELD_END

// Horizontal Guard Band Discard Adjust Register
BITFIELD_BEG(PA_CL_GB_HORZ_DISC_ADJ, uint32_t)
   BITFIELD_ENTRY(0, 32, float, DATA_REGISTER)
BITFIELD_END

// Vertical Guard Band Clip Adjust Register
BITFIELD_BEG(PA_CL_GB_VERT_CLIP_ADJ, uint32_t)
   BITFIELD_ENTRY(0, 32, float, DATA_REGISTER)
BITFIELD_END

// Vertical Guard Band Discard Adjust Register
BITFIELD_BEG(PA_CL_GB_VERT_DISC_ADJ, uint32_t)
   BITFIELD_ENTRY(0, 32, float, DATA_REGISTER)
BITFIELD_END

BITFIELD_BEG(PA_CL_NANINF_CNTL, uint32_t)
   BITFIELD_ENTRY(0, 1, bool, VTE_XY_INF_DISCARD)
   BITFIELD_ENTRY(1, 1, bool, VTE_Z_INF_DISCARD)
   BITFIELD_ENTRY(2, 1, bool, VTE_W_INF_DISCARD)
   BITFIELD_ENTRY(3, 1, bool, VTE_0XNANINF_IS_0)
   BITFIELD_ENTRY(4, 1, bool, VTE_XY_NAN_RETAIN)
   BITFIELD_ENTRY(5, 1, bool, VTE_Z_NAN_RETAIN)
   BITFIELD_ENTRY(6, 1, bool, VTE_W_NAN_RETAIN)
   BITFIELD_ENTRY(7, 1, bool, VTE_W_RECIP_NAN_IS_0)
   BITFIELD_ENTRY(8, 1, bool, VS_XY_NAN_TO_INF)
   BITFIELD_ENTRY(9, 1, bool, VS_XY_INF_RETAIN)
   BITFIELD_ENTRY(10, 1, bool, VS_Z_NAN_TO_INF)
   BITFIELD_ENTRY(11, 1, bool, VS_Z_INF_RETAIN)
   BITFIELD_ENTRY(12, 1, bool, VS_W_NAN_TO_INF)
   BITFIELD_ENTRY(13, 1, bool, VS_W_INF_RETAIN)
   BITFIELD_ENTRY(14, 1, bool, VS_CLIP_DIST_INF_DISCARD)
   BITFIELD_ENTRY(20, 1, bool, VTE_NO_OUTPUT_NEG_0)
BITFIELD_END

// Point Sprite X Radius Expansion
BITFIELD_BEG(PA_CL_POINT_X_RAD, uint32_t)
   BITFIELD_ENTRY(0, 32, uint32_t, DATA_REGISTER)
BITFIELD_END

// Point Sprite Y Radius Expansion
BITFIELD_BEG(PA_CL_POINT_Y_RAD, uint32_t)
   BITFIELD_ENTRY(0, 32, uint32_t, DATA_REGISTER)
BITFIELD_END

// Point Sprite Constant Size
BITFIELD_BEG(PA_CL_POINT_SIZE, uint32_t)
   BITFIELD_ENTRY(0, 32, uint32_t, DATA_REGISTER)
BITFIELD_END

// Point Sprite Culling Radius Expansion
BITFIELD_BEG(PA_CL_POINT_CULL_RAD, uint32_t)
   BITFIELD_ENTRY(0, 32, uint32_t, DATA_REGISTER)
BITFIELD_END

// Viewport Transform X Scale Factor
BITFIELD_BEG(PA_CL_VPORT_XSCALE_N, uint32_t)
   BITFIELD_ENTRY(0, 32, float, VPORT_XSCALE)
BITFIELD_END

// Viewport Transform X Offset
BITFIELD_BEG(PA_CL_VPORT_XOFFSET_N, uint32_t)
   BITFIELD_ENTRY(0, 32, float, VPORT_XOFFSET)
BITFIELD_END

// Viewport Transform Y Scale Factor
BITFIELD_BEG(PA_CL_VPORT_YSCALE_N, uint32_t)
   BITFIELD_ENTRY(0, 32, float, VPORT_YSCALE)
BITFIELD_END

// Viewport Transform Y Offset
BITFIELD_BEG(PA_CL_VPORT_YOFFSET_N, uint32_t)
   BITFIELD_ENTRY(0, 32, float, VPORT_YOFFSET)
BITFIELD_END

// Viewport Transform Z Scale Factor
BITFIELD_BEG(PA_CL_VPORT_ZSCALE_N, uint32_t)
   BITFIELD_ENTRY(0, 32, float, VPORT_ZSCALE)
BITFIELD_END

// Viewport Transform Z Offset
BITFIELD_BEG(PA_CL_VPORT_ZOFFSET_N, uint32_t)
   BITFIELD_ENTRY(0, 32, float, VPORT_ZOFFSET)
BITFIELD_END

// Vertex Shader Output Control
BITFIELD_BEG(PA_CL_VS_OUT_CNTL, uint32_t)
   BITFIELD_ENTRY(0, 1, bool, CLIP_DIST_ENA_0)
   BITFIELD_ENTRY(1, 1, bool, CLIP_DIST_ENA_1)
   BITFIELD_ENTRY(2, 1, bool, CLIP_DIST_ENA_2)
   BITFIELD_ENTRY(3, 1, bool, CLIP_DIST_ENA_3)
   BITFIELD_ENTRY(4, 1, bool, CLIP_DIST_ENA_4)
   BITFIELD_ENTRY(5, 1, bool, CLIP_DIST_ENA_5)
   BITFIELD_ENTRY(6, 1, bool, CLIP_DIST_ENA_6)
   BITFIELD_ENTRY(7, 1, bool, CLIP_DIST_ENA_7)
   BITFIELD_ENTRY(8, 1, bool, CULL_DIST_ENA_0)
   BITFIELD_ENTRY(9, 1, bool, CULL_DIST_ENA_1)
   BITFIELD_ENTRY(10, 1, bool, CULL_DIST_ENA_2)
   BITFIELD_ENTRY(11, 1, bool, CULL_DIST_ENA_3)
   BITFIELD_ENTRY(12, 1, bool, CULL_DIST_ENA_4)
   BITFIELD_ENTRY(13, 1, bool, CULL_DIST_ENA_5)
   BITFIELD_ENTRY(14, 1, bool, CULL_DIST_ENA_6)
   BITFIELD_ENTRY(15, 1, bool, CULL_DIST_ENA_7)
   BITFIELD_ENTRY(16, 1, bool, USE_VTX_POINT_SIZE)
   BITFIELD_ENTRY(17, 1, bool, USE_VTX_EDGE_FLAG)
   BITFIELD_ENTRY(18, 1, bool, USE_VTX_RENDER_TARGET_INDX)
   BITFIELD_ENTRY(19, 1, bool, USE_VTX_VIEWPORT_INDX)
   BITFIELD_ENTRY(20, 1, bool, USE_VTX_KILL_FLAG)
   BITFIELD_ENTRY(21, 1, bool, VS_OUT_MISC_VEC_ENA)
   BITFIELD_ENTRY(22, 1, bool, VS_OUT_CCDIST0_VEC_ENA)
   BITFIELD_ENTRY(23, 1, bool, VS_OUT_CCDIST1_VEC_ENA)
   BITFIELD_ENTRY(24, 1, bool, VS_OUT_MISC_SIDE_BUS_ENA)
   BITFIELD_ENTRY(25, 1, bool, USE_VTX_GS_CUT_FLAG)
BITFIELD_END

// Viewport Transform Engine Control
BITFIELD_BEG(PA_CL_VTE_CNTL, uint32_t)
   BITFIELD_ENTRY(0, 1, bool, VPORT_X_SCALE_ENA)
   BITFIELD_ENTRY(1, 1, bool, VPORT_X_OFFSET_ENA)
   BITFIELD_ENTRY(2, 1, bool, VPORT_Y_SCALE_ENA)
   BITFIELD_ENTRY(3, 1, bool, VPORT_Y_OFFSET_ENA)
   BITFIELD_ENTRY(4, 1, bool, VPORT_Z_SCALE_ENA)
   BITFIELD_ENTRY(5, 1, bool, VPORT_Z_OFFSET_ENA)
   BITFIELD_ENTRY(8, 1, bool, VTX_XY_FMT)
   BITFIELD_ENTRY(9, 1, bool, VTX_Z_FMT)
   BITFIELD_ENTRY(10, 1, bool, VTX_W0_FMT)
   BITFIELD_ENTRY(11, 1, bool, PERFCOUNTER_REF)
BITFIELD_END

// Multisample AA Mask
BITFIELD_BEG(PA_SC_AA_MASK, uint32_t)
   BITFIELD_ENTRY(0, 8, uint8_t, AA_MASK_ULC)
   BITFIELD_ENTRY(8, 8, uint8_t, AA_MASK_URC)
   BITFIELD_ENTRY(16, 8, uint8_t, AA_MASK_LLC)
   BITFIELD_ENTRY(24, 8, uint8_t, AA_MASK_LRC)
BITFIELD_END

// OpenGL Clip boolean function
BITFIELD_BEG(PA_SC_CLIPRECT_RULE, uint32_t)
   BITFIELD_ENTRY(0, 16, uint16_t, CLIP_RULE)
BITFIELD_END

// Line Drawing Control
BITFIELD_BEG(PA_SC_LINE_CNTL, uint32_t)
   BITFIELD_ENTRY(0, 8, uint8_t, BRES_CNTL)
   BITFIELD_ENTRY(8, 1, bool, USE_BRES_CNTL)
   BITFIELD_ENTRY(9, 1, bool, EXPAND_LINE_WIDTH)
   BITFIELD_ENTRY(10, 1, bool, LAST_PIXEL)
BITFIELD_END

// Line Stipple Control
BITFIELD_BEG(PA_SC_LINE_STIPPLE, uint32_t)
   BITFIELD_ENTRY(0, 16, uint16_t, LINE_PATTERN)
   BITFIELD_ENTRY(16, 8, uint8_t, REPEAT_COUNT)
   BITFIELD_ENTRY(28, 1, bool, PATTERN_BIT_ORDER)
   BITFIELD_ENTRY(29, 2, uint8_t, AUTO_RESET_CNTL)
BITFIELD_END

// SC Mode Control Register for Various Enables
BITFIELD_BEG(PA_SC_MODE_CNTL, uint32_t)
   BITFIELD_ENTRY(0, 1, bool, MSAA_ENABLE)
   BITFIELD_ENTRY(1, 1, bool, CLIPRECT_ENABLE)
   BITFIELD_ENTRY(2, 1, bool, LINE_STIPPLE_ENABLE)
   BITFIELD_ENTRY(3, 1, bool, MULTI_CHIP_PRIM_DISCARD_ENABLE)
   BITFIELD_ENTRY(4, 1, bool, WALK_ORDER_ENABLE)
   BITFIELD_ENTRY(5, 1, bool, HALVE_DETAIL_SAMPLE_PERF)
   BITFIELD_ENTRY(6, 1, bool, WALK_SIZE)
   BITFIELD_ENTRY(7, 1, bool, WALK_ALIGNMENT)
   BITFIELD_ENTRY(8, 1, bool, WALK_ALIGN8_PRIM_FITS_ST)
   BITFIELD_ENTRY(9, 1, bool, TILE_COVER_NO_SCISSOR)
   BITFIELD_ENTRY(10, 1, bool, KILL_PIX_POST_HI_Z)
   BITFIELD_ENTRY(11, 1, bool, KILL_PIX_POST_DETAIL_MASK)
   BITFIELD_ENTRY(12, 1, bool, MULTI_CHIP_SUPERTILE_ENABLE)
   BITFIELD_ENTRY(13, 1, bool, TILE_COVER_DISABLE)
   BITFIELD_ENTRY(14, 1, bool, FORCE_EOV_CNTDWN_ENABLE)
   BITFIELD_ENTRY(15, 1, bool, FORCE_EOV_TILE_ENABLE)
   BITFIELD_ENTRY(16, 1, bool, FORCE_EOV_REZ_ENABLE)
   BITFIELD_ENTRY(17, 1, bool, PS_ITER_SAMPLE)
BITFIELD_END

// Multi-Pass Pixel Shader Control Register
BITFIELD_BEG(PA_SC_MPASS_PS_CNTL, uint32_t)
   BITFIELD_ENTRY(0, 20, uint32_t, MPASS_PIX_VEC_PER_PASS)
   BITFIELD_ENTRY(31, 1, bool, MPASS_PS_ENA)
BITFIELD_END

// Screen Scissor rectangle specification
BITFIELD_BEG(PA_SC_SCREEN_SCISSOR_BR, uint32_t)
   BITFIELD_ENTRY(0, 14, uint32_t, BR_X)
   BITFIELD_ENTRY(16, 14, uint32_t, BR_Y)
BITFIELD_END

// Screen Scissor rectangle specification
BITFIELD_BEG(PA_SC_SCREEN_SCISSOR_TL, uint32_t)
   BITFIELD_ENTRY(0, 14, uint32_t, TL_X)
   BITFIELD_ENTRY(16, 14, uint32_t, TL_Y)
BITFIELD_END

// Generic Scissor rectangle specification
BITFIELD_BEG(PA_SC_GENERIC_SCISSOR_BR, uint32_t)
   BITFIELD_ENTRY(0, 14, uint32_t, BR_X)
   BITFIELD_ENTRY(16, 14, uint32_t, BR_Y)
BITFIELD_END

// Generic Scissor rectangle specification
BITFIELD_BEG(PA_SC_GENERIC_SCISSOR_TL, uint32_t)
   BITFIELD_ENTRY(0, 14, uint32_t, TL_X)
   BITFIELD_ENTRY(16, 14, uint32_t, TL_Y)
   BITFIELD_ENTRY(31, 1, bool, WINDOW_OFFSET_DISABLE)
BITFIELD_END

// WGF ViewportId Scissor rectangle specification (0-15).
BITFIELD_BEG(PA_SC_VPORT_SCISSOR_0_BR, uint32_t)
   BITFIELD_ENTRY(0, 14, uint32_t, BR_X)
   BITFIELD_ENTRY(16, 14, uint32_t, BR_Y)
BITFIELD_END

// WGF ViewportId Scissor rectangle specification (0-15).
BITFIELD_BEG(PA_SC_VPORT_SCISSOR_0_TL, uint32_t)
   BITFIELD_ENTRY(0, 14, uint32_t, TL_X)
   BITFIELD_ENTRY(16, 14, uint32_t, TL_Y)
   BITFIELD_ENTRY(31, 1, bool, WINDOW_OFFSET_DISABLE)
BITFIELD_END

// Viewport Transform Z Min Clamp
BITFIELD_BEG(PA_SC_VPORT_ZMIN_N, uint32_t)
   BITFIELD_ENTRY(0, 32, float, VPORT_ZMIN)
BITFIELD_END

// Viewport Transform Z Max Clamp
BITFIELD_BEG(PA_SC_VPORT_ZMAX_N, uint32_t)
   BITFIELD_ENTRY(0, 32, float, VPORT_ZMAX)
BITFIELD_END

// Offset from screen coords to window coords.
BITFIELD_BEG(PA_SC_WINDOW_OFFSET, uint32_t)
   BITFIELD_ENTRY(0, 14, uint32_t, WINDOW_X_OFFSET)
   BITFIELD_ENTRY(16, 14, uint32_t, WINDOW_Y_OFFSET)
BITFIELD_END

// Window Scissor rectangle specification.
BITFIELD_BEG(PA_SC_WINDOW_SCISSOR_TL, uint32_t)
   BITFIELD_ENTRY(0, 14, uint32_t, TL_X)
   BITFIELD_ENTRY(16, 14, uint32_t, TL_Y)
   BITFIELD_ENTRY(31, 1, bool, WINDOW_OFFSET_DISABLE)
BITFIELD_END

// Window Scissor rectangle specification.
BITFIELD_BEG(PA_SC_WINDOW_SCISSOR_BR, uint32_t)
   BITFIELD_ENTRY(0, 14, uint32_t, BR_X)
   BITFIELD_ENTRY(16, 14, uint32_t, BR_Y)
BITFIELD_END

// Line control
BITFIELD_BEG(PA_SU_LINE_CNTL, uint32_t)
   BITFIELD_ENTRY(0, 16, uint32_t, WIDTH) // 16.0 fixed
BITFIELD_END

// Specifies maximum and minimum point & sprite sizes for per vertex size specification
BITFIELD_BEG(PA_SU_POINT_MINMAX, uint32_t)
   BITFIELD_ENTRY(0, 16, uint32_t, MIN_SIZE) // 12.4 fixed
   BITFIELD_ENTRY(16, 16, uint32_t, MAX_SIZE) // 12.4 fixed
BITFIELD_END

// Dimensions for Points
BITFIELD_BEG(PA_SU_POINT_SIZE, uint32_t)
   BITFIELD_ENTRY(0, 16, uint32_t, HEIGHT) // 12.4 fixed
   BITFIELD_ENTRY(16, 16, uint32_t, WIDTH) // 12.4 fixed
BITFIELD_END

// Clamp Value for Polygon Offset
BITFIELD_BEG(PA_SU_POLY_OFFSET_CLAMP, uint32_t)
   BITFIELD_ENTRY(0, 32, float, CLAMP)
BITFIELD_END

// Back-Facing Polygon Offset Scale
BITFIELD_BEG(PA_SU_POLY_OFFSET_BACK_SCALE, uint32_t)
   BITFIELD_ENTRY(0, 32, float, SCALE)
BITFIELD_END

// Back-Facing Polygon Offset Scale
BITFIELD_BEG(PA_SU_POLY_OFFSET_BACK_OFFSET, uint32_t)
   BITFIELD_ENTRY(0, 32, float, OFFSET)
BITFIELD_END

// Front-Facing Polygon Offset Scale
BITFIELD_BEG(PA_SU_POLY_OFFSET_FRONT_SCALE, uint32_t)
   BITFIELD_ENTRY(0, 32, float, SCALE)
BITFIELD_END

// Front-Facing Polygon Offset Scale
BITFIELD_BEG(PA_SU_POLY_OFFSET_FRONT_OFFSET, uint32_t)
   BITFIELD_ENTRY(0, 32, float, OFFSET)
BITFIELD_END

// SU/SC Controls for Facedness Culling, Polymode, Polygon Offset, and various Enables
BITFIELD_BEG(PA_SU_SC_MODE_CNTL, uint32_t)
   BITFIELD_ENTRY(0, 1, bool, CULL_FRONT)
   BITFIELD_ENTRY(1, 1, bool, CULL_BACK)
   BITFIELD_ENTRY(2, 1, PA_FACE, FACE)
   BITFIELD_ENTRY(3, 2, uint32_t, POLY_MODE)
   BITFIELD_ENTRY(5, 3, PA_PTYPE, POLYMODE_FRONT_PTYPE)
   BITFIELD_ENTRY(8, 3, PA_PTYPE, POLYMODE_BACK_PTYPE)
   BITFIELD_ENTRY(11, 1, bool, POLY_OFFSET_FRONT_ENABLE)
   BITFIELD_ENTRY(12, 1, bool, POLY_OFFSET_BACK_ENABLE)
   BITFIELD_ENTRY(13, 1, bool, POLY_OFFSET_PARA_ENABLE)
   BITFIELD_ENTRY(16, 1, bool, VTX_WINDOW_OFFSET_ENABLE)
   BITFIELD_ENTRY(19, 1, bool, PROVOKING_VTX_LAST)
   BITFIELD_ENTRY(20, 1, bool, PERSP_CORR_DIS)
   BITFIELD_ENTRY(21, 1, bool, MULTI_PRIM_IB_ENA)
BITFIELD_END

// Polygon Offset Depth Buffer Format Control
BITFIELD_BEG(PA_SU_POLY_OFFSET_DB_FMT_CNTL, uint32_t)
   BITFIELD_ENTRY(0, 8, uint32_t, POLY_OFFSET_NEG_NUM_DB_BITS)
   BITFIELD_ENTRY(8, 1, bool, POLY_OFFSET_DB_IS_FLOAT_FMT)
BITFIELD_END

// Miscellaneous SU Control
BITFIELD_BEG(PA_SU_VTX_CNTL, uint32_t)
   BITFIELD_ENTRY(0, 1, PA_SU_VTX_CNTL_PIX_CENTER, PIX_CENTER)
   BITFIELD_ENTRY(1, 2, PA_SU_VTX_CNTL_ROUND_MODE, ROUND_MODE)
   BITFIELD_ENTRY(3, 3, PA_SU_VTX_CNTL_QUANT_MODE, QUANT_MODE)
BITFIELD_END

} // namespace latte