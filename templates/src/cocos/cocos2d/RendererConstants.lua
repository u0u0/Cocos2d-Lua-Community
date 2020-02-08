
cc = cc or {}

cc.backendPixelFormat = {
    AUTO = 0,
    BGRA8888 = 1,
    RGBA8888 = 2,
    RGB888 = 3,
    RGB565 = 4,
    A8 = 5,
    I8 = 6,
    AI88 = 7,
    RGBA4444 = 8,
    RGB5A1 = 9,
    PVRTC4 = 10,
    PVRTC4A = 11,
    PVRTC2 = 12,
    PVRTC2A = 13,
    ETC = 14,
    S3TC_DXT1 = 15,
    S3TC_DXT3 = 16,
    S3TC_DXT5 = 17,
    ATC_RGB = 18,
    ATC_EXPLICIT_ALPHA = 19,
    ATC_INTERPOLATED_ALPHA = 20,
    MTL_B5G6R5 = 21,
    MTL_BGR5A1 = 22,
    MTL_ABGR4 = 23,
    D24S8 = 24,
    DEFAULT = 0,
    NONE = -1
}

cc.backendSamplerAddressMode = {
    REPEAT = 0,
    MIRROR_REPEAT = 1,
    CLAMP_TO_EDGE = 2,
    DONT_CARE = 3,
}

cc.backendSamplerFilter = {
    NEAREST = 0,
    NEAREST_MIPMAP_NEAREST = 1,
    NEAREST_MIPMAP_LINEAR = 2,
    LINEAR = 3,
    LINEAR_MIPMAP_LINEAR = 4,
    LINEAR_MIPMAP_NEAREST = 5,
    DONT_CARE = 6,
}

cc.backendBlendFactor = {
    ZERO = 0,
    ONE = 1,
    SRC_COLOR = 2,
    ONE_MINUS_SRC_COLOR = 3,
    SRC_ALPHA = 4,
    ONE_MINUS_SRC_ALPHA = 5,
    DST_COLOR = 6,
    ONE_MINUS_DST_COLOR = 7,
    DST_ALPHA = 8,
    ONE_MINUS_DST_ALPHA = 9,
    CONSTANT_ALPHA = 10,
    SRC_ALPHA_SATURATE = 11,
    ONE_MINUS_CONSTANT_ALPHA = 12,
    BLEND_CLOLOR = 13
}
