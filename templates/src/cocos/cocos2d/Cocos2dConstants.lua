
cc = cc or {}

-- TMX
cc.TMX_ORIENTATION_ORTHO     = 0x0
cc.TMX_ORIENTATION_HEX       = 0x1
cc.TMX_ORIENTATION_ISO       = 0x2
cc.TMX_ORIENTATION_STAGGERED = 0x3
cc.TMX_STAGGER_AXIS_X = 0x0
cc.TMX_STAGGER_AXIS_Y = 0x1
cc.TMX_STAGGER_INDEX_ODD = 0x0
cc.TMX_STAGGER_INDEX_EVEN = 0x1
cc.TMX_TILE_HORIZONTAL_FLAG = 0x80000000
cc.TMX_TILE_VERTICAL_FLAG   = 0x40000000
cc.TMX_TILE_DIAGONAL_FLAG   = 0x20000000
cc.TMX_TILE_FLIPED_ALL      = 0xE0000000
cc.TMX_TILE_FLIPPEDMASK     = 0x1FFFFFFF
-- cc ZipUtils
cc.Z_COMPRESSION_ZLIB   = 0x0
cc.Z_COMPRESSION_BZIP2  = 0x1
cc.Z_COMPRESSION_GZIP   = 0x2
cc.Z_COMPRESSION_NONE   = 0x3
-- tag
cc.ACTION_TAG_INVALID   = -1
cc.NODE_TAG_INVALID = -1
-- director
cc.DIRECTOR_PROJECTION_2D   = 0x0
cc.DIRECTOR_PROJECTION_3D   = 0x1
cc.DIRECTOR_PROJECTION_CUSTOM   = 0x2
cc.DIRECTOR_PROJECTION_DEFAULT  = 0x1
cc.ResolutionPolicy =
{
    EXACT_FIT = 0,
    NO_BORDER = 1,
    SHOW_ALL  = 2,
    FIXED_HEIGHT  = 3,
    FIXED_WIDTH  = 4,
    UNKNOWN  = 5,
}
cc.MATRIX_STACK_TYPE =
{
    MODELVIEW = 0,
    PROJECTION = 1,
    TEXTURE = 2,
}
-- particle
cc.PARTICLE_DURATION_INFINITY   = -1
cc.PARTICLE_START_SIZE_EQUAL_TO_END_SIZE    = -1
cc.PARTICLE_START_RADIUS_EQUAL_TO_END_RADIUS    = -1
cc.PARTICLE_MODE_GRAVITY = 0x0
cc.PARTICLE_MODE_RADIUS  = 0x1
cc.POSITION_TYPE_FREE   = 0x0
cc.POSITION_TYPE_RELATIVE   = 0x1
cc.POSITION_TYPE_GROUPED    = 0x2
-- ProgressTimer
cc.PROGRESS_TIMER_TYPE_RADIAL = 0x0
cc.PROGRESS_TIMER_TYPE_BAR    = 0x1
-- Text
cc.TEXT_ALIGNMENT_LEFT   = 0x0
cc.TEXT_ALIGNMENT_CENTER = 0x1
cc.TEXT_ALIGNMENT_RIGHT  = 0x2
cc.VERTICAL_TEXT_ALIGNMENT_TOP    = 0x0
cc.VERTICAL_TEXT_ALIGNMENT_CENTER = 0x1
cc.VERTICAL_TEXT_ALIGNMENT_BOTTOM = 0x2
-- Touch
cc.TOUCHES_ALL_AT_ONCE  = 0x0
cc.TOUCHES_ONE_BY_ONE   = 0x1
cc.EventCode =
{
    BEGAN = 0,
    MOVED = 1,
    ENDED = 2,
    CANCELLED = 3,
}
-- TransitionScene
cc.TRANSITION_ORIENTATION_LEFT_OVER  = 0x0
cc.TRANSITION_ORIENTATION_RIGHT_OVER = 0x1
cc.TRANSITION_ORIENTATION_UP_OVER    = 0x0
cc.TRANSITION_ORIENTATION_DOWN_OVER  = 0x1
-- Application
cc.PLATFORM_OS_WINDOWS = 0
cc.PLATFORM_OS_LINUX   = 1
cc.PLATFORM_OS_MAC     = 2
cc.PLATFORM_OS_ANDROID = 3
cc.PLATFORM_OS_IPHONE  = 4
cc.PLATFORM_OS_IPAD    = 5
-- Language Type
cc.LANGUAGE_ENGLISH    = 0
cc.LANGUAGE_CHINESE    = 1
cc.LANGUAGE_FRENCH     = 2
cc.LANGUAGE_ITALIAN    = 3
cc.LANGUAGE_GERMAN     = 4
cc.LANGUAGE_SPANISH    = 5
cc.LANGUAGE_DUTCH      = 6
cc.LANGUAGE_RUSSIAN    = 7
cc.LANGUAGE_KOREAN     = 8
cc.LANGUAGE_JAPANESE   = 9
cc.LANGUAGE_HUNGARIAN  = 10
cc.LANGUAGE_PORTUGUESE = 11
cc.LANGUAGE_ARABIC     = 12
cc.LANGUAGE_NORWEGIAN  = 13
cc.LANGUAGE_POLISH     = 14
cc.LANGUAGE_TURKISH    = 15
cc.LANGUAGE_UKRAINIAN  = 16
cc.LANGUAGE_ROMANIAN   = 17
cc.LANGUAGE_BULGARIAN  = 18
cc.LANGUAGE_BELARUSIAN = 19
-- Handler Type
cc.Handler = cc.Handler or {}
cc.Handler.NODE = 0
cc.Handler.CALLFUNC = 1
cc.Handler.WEBSOCKET_OPEN = 2
cc.Handler.WEBSOCKET_MESSAGE = 3
cc.Handler.WEBSOCKET_CLOSE = 4
cc.Handler.WEBSOCKET_ERROR = 5
cc.Handler.LUANODE_DRAW = 6
cc.Handler.ARMATURE_EVENT = 7
cc.Handler.EVENT_ACC = 8
cc.Handler.EVENT_CUSTIOM = 9
cc.Handler.EVENT_KEYBOARD_PRESSED = 10
cc.Handler.EVENT_KEYBOARD_RELEASED = 11
cc.Handler.EVENT_TOUCH_BEGAN = 12
cc.Handler.EVENT_TOUCH_MOVED = 13
cc.Handler.EVENT_TOUCH_ENDED = 14
cc.Handler.EVENT_TOUCH_CANCELLED = 15
cc.Handler.EVENT_TOUCHES_BEGAN = 16
cc.Handler.EVENT_TOUCHES_MOVED = 17
cc.Handler.EVENT_TOUCHES_ENDED = 18
cc.Handler.EVENT_TOUCHES_CANCELLED = 19
cc.Handler.EVENT_MOUSE_DOWN = 20
cc.Handler.EVENT_MOUSE_UP = 21
cc.Handler.EVENT_MOUSE_MOVE = 22
cc.Handler.EVENT_MOUSE_SCROLL = 23
cc.Handler.EVENT_PHYSICS_CONTACT_BEGIN = 24
cc.Handler.EVENT_PHYSICS_CONTACT_PRESOLVE = 25
cc.Handler.EVENT_PHYSICS_CONTACT_POSTSOLVE = 26
cc.Handler.EVENT_PHYSICS_CONTACT_SEPARATE = 27
cc.Handler.EVENT_FOCUS = 28
cc.Handler.EVENT_CONTROLLER_CONNECTED = 29
cc.Handler.EVENT_CONTROLLER_DISCONNECTED = 30
cc.Handler.EVENT_CONTROLLER_KEYDOWN = 31
cc.Handler.EVENT_CONTROLLER_KEYUP = 32
cc.Handler.EVENT_CONTROLLER_KEYREPEAT = 33
cc.Handler.EVENT_CONTROLLER_AXIS = 34
cc.Handler.EVENT_SPINE_ANIMATION_START = 35
cc.Handler.EVENT_SPINE_ANIMATION_INTERRUPT = 36
cc.Handler.EVENT_SPINE_ANIMATION_END = 37
cc.Handler.EVENT_SPINE_ANIMATION_DISPOSE = 38
cc.Handler.EVENT_SPINE_ANIMATION_COMPLETE = 39
cc.Handler.EVENT_SPINE_ANIMATION_EVENT = 40
cc.Handler.EVENT_SPINE_ANIMATION_PREUPDATE = 41
cc.Handler.EVENT_SPINE_ANIMATION_POSTUPDATE = 42
-- EventListener Type
cc.EVENT_UNKNOWN               = 0
cc.EVENT_TOUCH_ONE_BY_ONE      = 1
cc.EVENT_TOUCH_ALL_AT_ONCE     = 2
cc.EVENT_KEYBOARD              = 3
cc.EVENT_MOUSE                 = 4
cc.EVENT_ACCELERATION          = 5
cc.EVENT_FOCUS                 = 6
cc.EVENT_GAME_CONTROLLER       = 7
cc.EVENT_CUSTOM                = 8
-- physics
cc.PHYSICSSHAPE_MATERIAL_DEFAULT = {density = 0.0, restitution = 0.0, friction = 0.0}
cc.PHYSICSBODY_MATERIAL_DEFAULT = {density = 0.1, restitution = 0.5, friction = 0.5}
-- Label
cc.GLYPHCOLLECTION_DYNAMIC = 0
cc.GLYPHCOLLECTION_NEHE    = 1
cc.GLYPHCOLLECTION_ASCII   = 2
cc.GLYPHCOLLECTION_CUSTOM  = 3
cc.LabelEffect =
{
    NORMAL = 0,
    OUTLINE = 1,
    SHADOW = 2,
    GLOW = 3,
    ITALICS = 4,
    BOLD = 5,
    UNDERLINE = 6,
    STRIKETHROUGH = 7,
    ALL = 8
}
cc.LabelOverflow =
{
    NONE = 0,
    CLAMP = 1,
    SHRINK = 2,
    RESIZE_HEIGHT = 3
};
-- keyboard
cc.KeyCodeKey =
{
    "KEY_NONE",
    "KEY_PAUSE",
    "KEY_SCROLL_LOCK",
    "KEY_PRINT",
    "KEY_SYSREQ",
    "KEY_BREAK",
    "KEY_ESCAPE",
    "KEY_BACKSPACE",
    "KEY_TAB",
    "KEY_BACK_TAB",
    "KEY_RETURN",
    "KEY_CAPS_LOCK",
    "KEY_SHIFT",
    "KEY_RIGHT_SHIFT",
    "KEY_CTRL",
    "KEY_RIGHT_CTRL",
    "KEY_ALT",
    "KEY_RIGHT_ALT",
    "KEY_MENU",
    "KEY_HYPER",
    "KEY_INSERT",
    "KEY_HOME",
    "KEY_PG_UP",
    "KEY_DELETE",
    "KEY_END",
    "KEY_PG_DOWN",
    "KEY_LEFT_ARROW",
    "KEY_RIGHT_ARROW",
    "KEY_UP_ARROW",
    "KEY_DOWN_ARROW",
    "KEY_NUM_LOCK",
    "KEY_KP_PLUS",
    "KEY_KP_MINUS",
    "KEY_KP_MULTIPLY",
    "KEY_KP_DIVIDE",
    "KEY_KP_ENTER",
    "KEY_KP_HOME",
    "KEY_KP_UP",
    "KEY_KP_PG_UP",
    "KEY_KP_LEFT",
    "KEY_KP_FIVE",
    "KEY_KP_RIGHT",
    "KEY_KP_END",
    "KEY_KP_DOWN",
    "KEY_KP_PG_DOWN",
    "KEY_KP_INSERT",
    "KEY_KP_DELETE",
    "KEY_F1",
    "KEY_F2",
    "KEY_F3",
    "KEY_F4",
    "KEY_F5",
    "KEY_F6",
    "KEY_F7",
    "KEY_F8",
    "KEY_F9",
    "KEY_F10",
    "KEY_F11",
    "KEY_F12",
    "KEY_SPACE",
    "KEY_EXCLAM",
    "KEY_QUOTE",
    "KEY_NUMBER",
    "KEY_DOLLAR",
    "KEY_PERCENT",
    "KEY_CIRCUMFLEX",
    "KEY_AMPERSAND",
    "KEY_APOSTROPHE",
    "KEY_LEFT_PARENTHESIS",
    "KEY_RIGHT_PARENTHESIS",
    "KEY_ASTERISK",
    "KEY_PLUS",
    "KEY_COMMA",
    "KEY_MINUS",
    "KEY_PERIOD",
    "KEY_SLASH",
    "KEY_0",
    "KEY_1",
    "KEY_2",
    "KEY_3",
    "KEY_4",
    "KEY_5",
    "KEY_6",
    "KEY_7",
    "KEY_8",
    "KEY_9",
    "KEY_COLON",
    "KEY_SEMICOLON",
    "KEY_LESS_THAN",
    "KEY_EQUAL",
    "KEY_GREATER_THAN",
    "KEY_QUESTION",
    "KEY_AT",
    "KEY_CAPITAL_A",
    "KEY_CAPITAL_B",
    "KEY_CAPITAL_C",
    "KEY_CAPITAL_D",
    "KEY_CAPITAL_E",
    "KEY_CAPITAL_F",
    "KEY_CAPITAL_G",
    "KEY_CAPITAL_H",
    "KEY_CAPITAL_I",
    "KEY_CAPITAL_J",
    "KEY_CAPITAL_K",
    "KEY_CAPITAL_L",
    "KEY_CAPITAL_M",
    "KEY_CAPITAL_N",
    "KEY_CAPITAL_O",
    "KEY_CAPITAL_P",
    "KEY_CAPITAL_Q",
    "KEY_CAPITAL_R",
    "KEY_CAPITAL_S",
    "KEY_CAPITAL_T",
    "KEY_CAPITAL_U",
    "KEY_CAPITAL_V",
    "KEY_CAPITAL_W",
    "KEY_CAPITAL_X",
    "KEY_CAPITAL_Y",
    "KEY_CAPITAL_Z",
    "KEY_LEFT_BRACKET",
    "KEY_BACK_SLASH",
    "KEY_RIGHT_BRACKET",
    "KEY_UNDERSCORE",
    "KEY_GRAVE",
    "KEY_A",
    "KEY_B",
    "KEY_C",
    "KEY_D",
    "KEY_E",
    "KEY_F",
    "KEY_G",
    "KEY_H",
    "KEY_I",
    "KEY_J",
    "KEY_K",
    "KEY_L",
    "KEY_M",
    "KEY_N",
    "KEY_O",
    "KEY_P",
    "KEY_Q",
    "KEY_R",
    "KEY_S",
    "KEY_T",
    "KEY_U",
    "KEY_V",
    "KEY_W",
    "KEY_X",
    "KEY_Y",
    "KEY_Z",
    "KEY_LEFT_BRACE",
    "KEY_BAR",
    "KEY_RIGHT_BRACE",
    "KEY_TILDE",
    "KEY_EURO",
    "KEY_POUND",
    "KEY_YEN",
    "KEY_MIDDLE_DOT",
    "KEY_SEARCH",
    "KEY_DPAD_LEFT",
    "KEY_DPAD_RIGHT",
    "KEY_DPAD_UP",
    "KEY_DPAD_DOWN",
    "KEY_DPAD_CENTER",
    "KEY_ENTER",
    "KEY_PLAY",
}

cc.KeyCode = {}
for k,v in ipairs(cc.KeyCodeKey) do
    cc.KeyCode[v] = k - 1
end

cc.KeyCode.KEY_BACK = cc.KeyCode.KEY_ESCAPE
cc.KeyCode.KEY_LEFT_SHIFT = cc.KeyCode.KEY_SHIFT
cc.KeyCode.KEY_LEFT_CTRL  = cc.KeyCode.KEY_CTRL
cc.KeyCode.KEY_LEFT_ALT   = cc.KeyCode.KEY_ALT

-- camera
cc.CameraFlag =
{
    DEFAULT = 1,
    USER1 = 2,
    USER2 = 4,
    USER3 = 8,
    USER4 = 16,
    USER5 = 32,
    USER6 = 64,
    USER7 = 128,
    USER8 = 256,
}
cc.CameraBackgroundBrush.BrushType = 
{
    NONE = 0,
    DEPTH = 1,
    COLOR = 2,
    SKYBOX = 3,
}
-- 3D BillBoard
cc.BillBoard_Mode =
{
    VIEW_POINT_ORIENTED = 0,
    VIEW_PLANE_ORIENTED = 1,
}
-- light
cc.LightType = 
{
    DIRECTIONAL = 0,
    POINT = 1,
    SPOT = 2,
    AMBIENT = 3,
}
cc.LightFlag = 
{
    LIGHT0  = math.pow(2,0),
    LIGHT1  = math.pow(2,1),
    LIGHT2  = math.pow(2,2),
    LIGHT3  = math.pow(2,3),
    LIGHT4  = math.pow(2,4),
    LIGHT5  = math.pow(2,5),
    LIGHT6  = math.pow(2,6),
    LIGHT7  = math.pow(2,7),
    LIGHT8  = math.pow(2,8),
    LIGHT9  = math.pow(2,9),
    LIGHT10 = math.pow(2,10),
    LIGHT11 = math.pow(2,11),
    LIGHT12 = math.pow(2,12),
    LIGHT13 = math.pow(2,13),
    LIGHT14 = math.pow(2,14),
    LIGHT15 = math.pow(2,15),
}
-- color
cc.RED = cc.c3b(255,0,0)
cc.GREEN = cc.c3b(0,255,0)
cc.BLUE = cc.c3b(0,0,255)
cc.BLACK = cc.c3b(0,0,0)
cc.WHITE = cc.c3b(255,255,255)
cc.YELLOW = cc.c3b(255,255,0)
