#ifndef _M_PC_IMPL_TYPES_H
#define _M_PC_IMPL_TYPES_H

// blending modes
enum M_BLENDING_MODES
{
	M_BLENDING_NONE = 0,
	M_BLENDING_ALPHA,
	M_BLENDING_ADD,
	M_BLENDING_SUB,
	M_BLENDING_LIGHT,
	M_BLENDING_PRODUCT
};

// depth modes
enum M_DEPTH_MODES
{
	M_DEPTH_NONE = 0,
	M_DEPTH_ALWAYS,
	M_DEPTH_LESS,
	M_DEPTH_GREATER,
	M_DEPTH_EQUAL,
	M_DEPTH_LEQUAL,
	M_DEPTH_GEQUAL,
	M_DEPTH_NOTEQUAL
};

// matrix modes
enum M_MATRIX_MODES
{
	M_MATRIX_MODELVIEW = 0,
	M_MATRIX_PROJECTION,
	M_MATRIX_TEXTURE,
};

// primitives types
enum U_PRIMITIVE_TYPES
{
	U_PRIMITIVE_POINTS = 0,
	U_PRIMITIVE_LINES,
	U_PRIMITIVE_LINE_LOOP,
	U_PRIMITIVE_LINE_STRIP,
	U_PRIMITIVE_TRIANGLES,
	U_PRIMITIVE_TRIANGLE_STRIP,
	U_PRIMITIVE_TRIANGLE_FAN
};

// buffer types
enum M_BUFFER_TYPES
{
	M_BUFFER_COLOR = 2,
	M_BUFFER_DEPTH = 4,
	M_BUFFER_STENCIL = 8
};

// texture image mode
enum M_TEX_MODES
{
	M_DEPTH = 0,
	M_R = 1,
	M_RG = 2,
	M_RGB = 3,
	M_RGBA = 4
};

// texture gen modes
enum M_TEX_GEN_MODES
{
	M_TEX_GEN_NONE = 0,
	M_TEX_GEN_SPHERE_MAP,
	M_TEX_GEN_CUBE_MAP
};

// texture combine modes
enum M_TEX_COMBINE_MODES
{
	M_TEX_COMBINE_REPLACE = 0,
	M_TEX_COMBINE_MODULATE,
	M_TEX_COMBINE_ALPHA,
	M_TEX_COMBINE_ADD,
	M_TEX_COMBINE_SUB,
	M_TEX_COMBINE_DOT
};

// texture filtering modes
enum M_TEX_FILTER_MODES
{
	M_TEX_FILTER_NEAREST = 0,
	M_TEX_FILTER_NEAREST_MIPMAP_NEAREST,
	M_TEX_FILTER_NEAREST_MIPMAP_LINEAR,
	M_TEX_FILTER_LINEAR,
	M_TEX_FILTER_LINEAR_MIPMAP_NEAREST,
	M_TEX_FILTER_LINEAR_MIPMAP_LINEAR,
};

// wrap modes
enum M_WRAP_MODES
{
	M_WRAP_REPEAT = 0,
	M_WRAP_CLAMP
};

// cull modes
enum U_CULL_MODES
{
	U_CULL_NONE = 0,
	U_CULL_FRONT,
	U_CULL_BACK,
	U_CULL_FRONT_BACK
};

// types
enum U_TYPES
{
	M_BOOL = 0,
	M_BYTE,
	M_UBYTE,
	U_SHORT,
	U_USHORT,
	U_INT,
	U_UINT,
	M_FLOAT,
	M_DOUBLE
};

enum M_FRAME_BUFFER_ATTACHMENT
{
	M_ATTACH_DEPTH = 0,
	M_ATTACH_STENCIL,
	M_ATTACH_COLOR0,
	M_ATTACH_COLOR1,
	M_ATTACH_COLOR2,
	M_ATTACH_COLOR3,
	M_ATTACH_COLOR4,
	M_ATTACH_COLOR5,
	M_ATTACH_COLOR6,
	M_ATTACH_COLOR7
};

enum M_RENDER_BUFFER_MODES
{
	M_RENDER_DEPTH = 0,
	M_RENDER_STENCIL,
	M_RENDER_DEPTH_STENCIL
};

// stencil funcs
enum M_STENCIL_FUNCS
{
	M_STENCIL_ALWAYS = 0,
	M_STENCIL_NEVER,
	M_STENCIL_EQUAL,
	M_STENCIL_NOTEQUAL,
	M_STENCIL_LESS,
	M_STENCIL_LEQUAL,
	M_STENCIL_GREATER,
	M_STENCIL_GEQUAL
};

// stencil ops
enum M_STENCIL_OPS
{
	M_STENCIL_KEEP = 0,
	M_STENCIL_INVERT,
	M_STENCIL_DECR,
	M_STENCIL_INCR,
	M_STENCIL_REPLACE
};

// VBO types
enum M_VBO_TYPES
{
	M_VBO_ARRAY = 0,
	M_VBO_ELEMENT_ARRAY
};

// VBO modes
enum M_VBO_MODES
{
	M_VBO_STATIC = 0,
	M_VBO_DYNAMIC,
	M_VBO_STREAM
};






// align modes
enum U_ALIGN_MODES
{
	U_ALIGN_LEFT = 0,
	U_ALIGN_RIGHT,
	U_ALIGN_CENTER
};


enum gui_align{
    GUI_ALIGN_LEFT = U_ALIGN_LEFT,
    GUI_ALIGN_RIGHT = U_ALIGN_RIGHT,
    GUI_ALIGN_CENTER = U_ALIGN_CENTER,
    GUI_ALIGN_LEFT_OUTER,
    GUI_ALIGN_RIGHT_OUTER,
    GUI_ALIGN_DOWN,
    GUI_ALIGN_UP,
    GUI_ALIGN_DOWN_OUTER,
    GUI_ALIGN_UP_OUTER
};

enum gui_align_v{
    GUI_ALIGN_V_CENTER,
    GUI_ALIGN_V_UP_
};

enum gui_object_type{
    GUI_NONE,
    GUI_TEXT,
    GUI_PICTURE
};

enum component_space{
    GUI_SPACE_2D,
    GUI_SPACE_3D
};

#endif