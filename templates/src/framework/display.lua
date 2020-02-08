--[[
  The module provide display related functions

  constant:
    display.sizeInPixels      , Screen pixel size
    display.widthInPixels     , Screen pixel width
    display.heightInPixels    , Screen pixel height
    display.contentScaleFactor, design resolution scale factor
    display.size              , design resolution size
    display.width             , design resolution width
    display.height            , design resolution height
    display.cx                , half screen width
    display.cy                , half screen height
    display.left              , left Coordinate X of screen
    display.top               , top Coordinate X of screen
    display.right             , right Coordinate X of screen
    display.bottom            , bottom Coordinate X of screen
    display.c_left            , left Coordinate X of screen when origin is at sreen center
    display.c_top             , top Coordinate X of screen when origin is at sreen center
    display.c_right           , right Coordinate X of screen when origin is at sreen center
    display.c_bottom          , bottom Coordinate X of screen when origin is at sreen center

  color constant:
    display.COLOR_WHITE       , cc.c3b(255, 255, 255)
    display.COLOR_YELLOW      , cc.c3b(255, 255, 0)
    display.COLOR_GREEN       , cc.c3b(0, 255, 0)
    display.COLOR_BLUE        , cc.c3b(0, 0, 255)
    display.COLOR_RED         , cc.c3b(255, 0, 0)
    display.COLOR_MAGENTA     , cc.c3b(255, 0, 255)
    display.COLOR_BLACK       , cc.c3b(0, 0, 0)
    display.COLOR_ORANGE      , cc.c3b(255, 127, 0)
    display.COLOR_GRAY        , cc.c3b(166, 166, 166)
]]--

local display = {}

local sharedDirector         = cc.Director:getInstance()
local sharedTextureCache     = cc.Director:getInstance():getTextureCache()
local sharedSpriteFrameCache = cc.SpriteFrameCache:getInstance()
local sharedAnimationCache   = cc.AnimationCache:getInstance()

-- check device screen size
local glview = sharedDirector:getOpenGLView()
assert(glview ~= nil, "Error: GLView not inited!")
local size = glview:getFrameSize()
display.sizeInPixels = {width = size.width, height = size.height}

local w = display.sizeInPixels.width
local h = display.sizeInPixels.height

if CONFIG_SCREEN_WIDTH == nil or CONFIG_SCREEN_HEIGHT == nil then
    CONFIG_SCREEN_WIDTH = w
    CONFIG_SCREEN_HEIGHT = h
end

if not CONFIG_SCREEN_AUTOSCALE then
    if w > h then
        CONFIG_SCREEN_AUTOSCALE = "FIXED_HEIGHT"
    else
        CONFIG_SCREEN_AUTOSCALE = "FIXED_WIDTH"
    end
else
    CONFIG_SCREEN_AUTOSCALE = string.upper(CONFIG_SCREEN_AUTOSCALE)
end

local scale, scaleX, scaleY

if CONFIG_SCREEN_AUTOSCALE and CONFIG_SCREEN_AUTOSCALE ~="NONE" then
	if type(CONFIG_SCREEN_AUTOSCALE_CALLBACK) == "function" then
		scaleX, scaleY = CONFIG_SCREEN_AUTOSCALE_CALLBACK(w, h, device.model)
	end

	if CONFIG_SCREEN_AUTOSCALE == "EXACT_FIT" then
		scale = 1.0
		glview:setDesignResolutionSize(CONFIG_SCREEN_WIDTH, CONFIG_SCREEN_HEIGHT, cc.ResolutionPolicy.EXACT_FIT)
	elseif CONFIG_SCREEN_AUTOSCALE == "FILL_ALL" then
		CONFIG_SCREEN_WIDTH = w
		CONFIG_SCREEN_HEIGHT = h
		scale = 1.0
		glview:setDesignResolutionSize(CONFIG_SCREEN_WIDTH, CONFIG_SCREEN_HEIGHT, cc.ResolutionPolicy.SHOW_ALL)
	else
		if not scaleX or not scaleY then
			scaleX, scaleY = w / CONFIG_SCREEN_WIDTH, h / CONFIG_SCREEN_HEIGHT
		end

		if CONFIG_SCREEN_AUTOSCALE == "FIXED_WIDTH" then
			scale = scaleX
			CONFIG_SCREEN_HEIGHT = h / scale
		elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_HEIGHT" then
			scale = scaleY
			CONFIG_SCREEN_WIDTH = w / scale
		elseif CONFIG_SCREEN_AUTOSCALE == "FIXED_AUTO" then
			if scaleX < scaleY then
				scale = scaleX
				CONFIG_SCREEN_HEIGHT = h / scale
			else
				scale = scaleY
				CONFIG_SCREEN_WIDTH  = w / scale
			end
		else
			scale = 1.0
			printError(string.format("display - invalid CONFIG_SCREEN_AUTOSCALE \"%s\"", CONFIG_SCREEN_AUTOSCALE))
		end
		glview:setDesignResolutionSize(CONFIG_SCREEN_WIDTH, CONFIG_SCREEN_HEIGHT, cc.ResolutionPolicy.NO_BORDER)
	end
else
	CONFIG_SCREEN_WIDTH = w
	CONFIG_SCREEN_HEIGHT = h
	scale = 1.0
end

local winSize = sharedDirector:getWinSize()
display.screenScale        = 2.0
display.contentScaleFactor = scale
display.size               = {width = winSize.width, height = winSize.height}
display.width              = display.size.width
display.height             = display.size.height
display.cx                 = display.width / 2
display.cy                 = display.height / 2
display.c_left             = -display.width / 2
display.c_right            = display.width / 2
display.c_top              = display.height / 2
display.c_bottom           = -display.height / 2
display.left               = 0
display.right              = display.width
display.top                = display.height
display.bottom             = 0
display.widthInPixels      = display.sizeInPixels.width
display.heightInPixels     = display.sizeInPixels.height

printInfo(string.format("# CONFIG_SCREEN_AUTOSCALE      = %s", CONFIG_SCREEN_AUTOSCALE))
printInfo(string.format("# CONFIG_SCREEN_WIDTH          = %0.2f", CONFIG_SCREEN_WIDTH))
printInfo(string.format("# CONFIG_SCREEN_HEIGHT         = %0.2f", CONFIG_SCREEN_HEIGHT))
printInfo(string.format("# display.widthInPixels        = %0.2f", display.widthInPixels))
printInfo(string.format("# display.heightInPixels       = %0.2f", display.heightInPixels))
printInfo(string.format("# display.contentScaleFactor   = %0.2f", display.contentScaleFactor))
printInfo(string.format("# display.width                = %0.2f", display.width))
printInfo(string.format("# display.height               = %0.2f", display.height))
printInfo(string.format("# display.cx                   = %0.2f", display.cx))
printInfo(string.format("# display.cy                   = %0.2f", display.cy))
printInfo(string.format("# display.left                 = %0.2f", display.left))
printInfo(string.format("# display.right                = %0.2f", display.right))
printInfo(string.format("# display.top                  = %0.2f", display.top))
printInfo(string.format("# display.bottom               = %0.2f", display.bottom))
printInfo(string.format("# display.c_left               = %0.2f", display.c_left))
printInfo(string.format("# display.c_right              = %0.2f", display.c_right))
printInfo(string.format("# display.c_top                = %0.2f", display.c_top))
printInfo(string.format("# display.c_bottom             = %0.2f", display.c_bottom))
printInfo("#")

display.COLOR_WHITE   = cc.c3b(255, 255, 255)
display.COLOR_YELLOW  = cc.c3b(255, 255, 0)
display.COLOR_GREEN   = cc.c3b(0, 255, 0)
display.COLOR_BLUE    = cc.c3b(0, 0, 255)
display.COLOR_RED     = cc.c3b(255, 0, 0)
display.COLOR_MAGENTA = cc.c3b(255, 0, 255)
display.COLOR_BLACK   = cc.c3b(0, 0, 0)
display.COLOR_ORANGE  = cc.c3b(255, 127, 0)
display.COLOR_GRAY    = cc.c3b(166, 166, 166)

display.AUTO_SIZE      = 0
display.FIXED_SIZE     = 1
display.LEFT_TO_RIGHT  = 0
display.RIGHT_TO_LEFT  = 1
display.TOP_TO_BOTTOM  = 2
display.BOTTOM_TO_TOP  = 3

display.CENTER        = 1
display.LEFT_TOP      = 2; display.TOP_LEFT      = 2
display.CENTER_TOP    = 3; display.TOP_CENTER    = 3
display.RIGHT_TOP     = 4; display.TOP_RIGHT     = 4
display.CENTER_LEFT   = 5; display.LEFT_CENTER   = 5
display.CENTER_RIGHT  = 6; display.RIGHT_CENTER  = 6
display.BOTTOM_LEFT   = 7; display.LEFT_BOTTOM   = 7
display.BOTTOM_RIGHT  = 8; display.RIGHT_BOTTOM  = 8
display.BOTTOM_CENTER = 9; display.CENTER_BOTTOM = 9

display.ANCHOR_POINTS = {
    cc.p(0.5, 0.5),  -- CENTER
    cc.p(0, 1),      -- TOP_LEFT
    cc.p(0.5, 1),    -- TOP_CENTER
    cc.p(1, 1),      -- TOP_RIGHT
    cc.p(0, 0.5),    -- CENTER_LEFT
    cc.p(1, 0.5),    -- CENTER_RIGHT
    cc.p(0, 0),      -- BOTTOM_LEFT
    cc.p(1, 0),      -- BOTTOM_RIGHT
    cc.p(0.5, 0),    -- BOTTOM_CENTER
}

display.SCENE_TRANSITIONS = {
    CROSSFADE       = {cc.TransitionCrossFade, 2},
    FADE            = {cc.TransitionFade, 3, cc.c3b(0, 0, 0)},
    FADEBL          = {cc.TransitionFadeBL, 2},
    FADEDOWN        = {cc.TransitionFadeDown, 2},
    FADETR          = {cc.TransitionFadeTR, 2},
    FADEUP          = {cc.TransitionFadeUp, 2},
    FLIPANGULAR     = {cc.TransitionFlipAngular, 3, cc.TRANSITION_ORIENTATION_LEFT_OVER},
    FLIPX           = {cc.TransitionFlipX, 3, cc.TRANSITION_ORIENTATION_LEFT_OVER},
    FLIPY           = {cc.TransitionFlipY, 3, cc.TRANSITION_ORIENTATION_UP_OVER},
    JUMPZOOM        = {cc.TransitionJumpZoom, 2},
    MOVEINB         = {cc.TransitionMoveInB, 2},
    MOVEINL         = {cc.TransitionMoveInL, 2},
    MOVEINR         = {cc.TransitionMoveInR, 2},
    MOVEINT         = {cc.TransitionMoveInT, 2},
    PAGETURN        = {cc.TransitionPageTurn, 3, false},
    ROTOZOOM        = {cc.TransitionRotoZoom, 2},
    SHRINKGROW      = {cc.TransitionShrinkGrow, 2},
    SLIDEINB        = {cc.TransitionSlideInB, 2},
    SLIDEINL        = {cc.TransitionSlideInL, 2},
    SLIDEINR        = {cc.TransitionSlideInR, 2},
    SLIDEINT        = {cc.TransitionSlideInT, 2},
    SPLITCOLS       = {cc.TransitionSplitCols, 2},
    SPLITROWS       = {cc.TransitionSplitRows, 2},
    TURNOFFTILES    = {cc.TransitionTurnOffTiles, 2},
    ZOOMFLIPANGULAR = {cc.TransitionZoomFlipAngular, 2},
    ZOOMFLIPX       = {cc.TransitionZoomFlipX, 3, cc.TRANSITION_ORIENTATION_LEFT_OVER},
    ZOOMFLIPY       = {cc.TransitionZoomFlipY, 3, cc.TRANSITION_ORIENTATION_UP_OVER},
}

display.TEXTURES_PIXEL_FORMAT = {}

display.DEFAULT_TTF_FONT        = "Arial"
display.DEFAULT_TTF_FONT_SIZE   = 24

--[[
  Create a new scene, auto enable Node event(true)
  @function newScene
  @param string name, scene name
]]--
function display.newScene(name)
    local scene = cc.Scene:create()
    scene.name = name or "<unknown-scene>"
	scene:setNodeEventEnabled(true)
    return scene
end

--[[
  Create a new physics scene, auto enable Node event(true)
  @function newPhysicsScene
  @param string name, scene name
]]--
function display.newPhysicsScene(name)
    local scene = cc.Scene:createWithPhysics()
    scene.name = name or "<unknown-scene>"
    scene:setNodeEventEnabled(true)
    return scene
end

--[[
  Create a new transition scene, auto enable Node event(true)
  @function wrapSceneWithTransition
  @param Scene scene, cc.Scene
  @param string transitionType,  transition type name
  @param number time, transition time
  @param string more, more param needed by some transition type
  @return Scene ret, cc.Scene

  example:
  local nextScene = display.newScene("NextScene")
  local transition = display.wrapSceneWithTransition(nextScene, "fade", 0.5)
  display.replaceScene(transition)

  transitionType:
  crossFade      , fadeOut curren scene and fadeIn next scene.
  fade           , fadeOut with specified color, which can set by param "more".
  fadeBL         , fadeOut start from lower left corner.
  fadeDown       , fadeOut start from bottom.
  fadeTR         , fadeOut start from upper right corner.
  fadeUp         , fadeOut start from top.
  flipAngular    , flip then into next scene, flip angular set by param "more" which value can be:
    cc.TRANSITION_ORIENTATION_LEFT_OVER
    cc.TRANSITION_ORIENTATION_RIGHT_OVER
    cc.TRANSITION_ORIENTATION_UP_OVER
    cc.TRANSITION_ORIENTATION_DOWN_OVER
  flipX          , flip horizontally.
  flipY          , flip vertically.
  zoomFlipAngular, flip and zoomIn, flip angular set by param "more" which value can be:
    cc.TRANSITION_ORIENTATION_LEFT_OVER
    cc.TRANSITION_ORIENTATION_RIGHT_OVER
    cc.TRANSITION_ORIENTATION_UP_OVER
    cc.TRANSITION_ORIENTATION_DOWN_OVER
  zoomFlipX      , flip horizontally and zoomIn
  zoomFlipY      , flip vertically abd zoomIn.
  jumpZoom       , jump and zoomIn.
  moveInB        , the new scene coming in from bottom, cover the old scene.
  moveInL        , the new scene coming in from left, cover the old scene.
  moveInR        , the new scene coming in from right, cover the old scene.
  moveInT        , the new scene coming in from top, cover the old scene.
  pageTurn       , pageTune effect, default from right to left, if param "more" set to true, from left to right
  rotoZoom       , roation and zoomIn.
  shrinkGrow     , shrink grow and cross fade.
  slideInB       , the new scene coming in from bottom, the old exit from top.
  slideInL       , the new scene coming in from left, the old exit from right.
  slideInR       , the new scene coming in from right, the old exit from left.
  slideInT       , the new scene coming in from top, the old exit from bottom.
  splitCols      , split into cols to enter new scene, like a shuttered window.
  splitRows      , split into rows to enter new scene, like a shuttered window.
  turnOffTiles   , split into tiles, replace by new scene gradually.
]]--
function display.wrapSceneWithTransition(scene, transitionType, time, more)
    local key = string.upper(tostring(transitionType))
    if string.sub(key, 1, 12) == "CCTRANSITION" then
        key = string.sub(key, 13)
    end

    if key == "RANDOM" then
        local keys = table.keys(display.SCENE_TRANSITIONS)
        key = keys[math.random(1, #keys)]
    end

    if display.SCENE_TRANSITIONS[key] then
        local cls, count, default = unpack(display.SCENE_TRANSITIONS[key])
        time = time or 0.2

        if count == 3 then
            scene = cls:create(time, scene, more or default)
        else
            scene = cls:create(time, scene)
        end
    else
        printError("display.wrapSceneWithTransition() - invalid transitionType %s", tostring(transitionType))
    end
    return scene
end

--[[
  Enter a new scene, remove the old scene. And can set transitionType when do replaceScene.
  inner auto call wrapSceneWithTransition
  @function replaceScene
  @param string transitionType, transition type name
  @param number time, transition time
  @param mixed more, param needed be some transition type

  example:
  display.replaceScene(nextScene, "fade", 0.5, cc.c3b(255, 0, 0))
]]--
function display.replaceScene(newScene, transitionType, time, more)
    if sharedDirector:getRunningScene() then
        if transitionType then
            newScene = display.wrapSceneWithTransition(newScene, transitionType, time, more)
        end
        sharedDirector:replaceScene(newScene)
    else
        sharedDirector:runWithScene(newScene)
    end
end

--[[
  Get current running scene.
  @function getRunningScene
  @return Scene ret, cc.Scene
]]--
function display.getRunningScene()
    return sharedDirector:getRunningScene()
end

--[[
  Pause Game.
  @function pause
]]--
function display.pause()
    sharedDirector:pause()
end

--[[
  Resume Game.
  @function resume
]]--
function display.resume()
    sharedDirector:resume()
end

--[[
  New a layer. In 4.0, cc.Layer removed, cc.Node do the same things.
  @function newLayer
  @return Node ret, cc.Node
]]--
function display.newLayer()
    local node = cc.Node:create()
	node:setContentSize(cc.size(display.width, display.height))
	return node
end

--[[
  New a color layer.
  @function newColorLayer
  @return LayerColor ret, cc.LayerColor
]]--
function display.newColorLayer(color)
    return cc.LayerColor:create(color)
end

--[[
  New a node.
  @function newNode
  @return Node ret, cc.Node
]]--
function display.newNode()
    return cc.Node:create()
end

if cc.ClippingRectangleNode then
    cc.ClippingRegionNode = cc.ClippingRectangleNode
else
    cc.ClippingRectangleNode = cc.ClippingRegionNode
end

--[[
  New a ClippingRectangleNode.
  @function newClippingRectangleNode
  @param Rect cc.Rect, clip rect
  @return Node ret, cc.ClippingRegionNode

  example:
  local layer = display.newColorLayer(cc.c4b(255, 255, 0, 255))
  local clipnode = display.newClippingRectangleNode(cc.rect(0, 0, 100, 100))
  layer:addTo(clipnode)
  clipnode:addTo(scene)
]]--
function display.newClippingRectangleNode(rect)
	return cc.ClippingRegionNode:create(rect)
end

--[[
  New a Sprite.
  @function newSprite
  @param mixed, image path or cc.SpriteFrame
  @param number x
  @param number y
  @param table params
  @return Sprite ret, cc.Sprite

  example:
  local sprite1 = display.newSprite("hello1.png") -- from file
  local sprite2 = display.newSprite("#frame0001.png") -- from SpriteFrame cache
  local frame = display.newFrame("frame0002.png") -- new cc.SpriteFrame then create sprite
  local sprite3 = display.newSprite(frame)
]]--
function display.newSprite(filename, x, y, params)
    local spriteClass = nil
    local size = nil

    if params then
        spriteClass = params.class
        size = params.size
    end
    if not spriteClass then spriteClass = cc.Sprite end

    local t = type(filename)
    if t == "userdata" then t = tolua.type(filename) end
    local sprite

    if not filename then
        sprite = spriteClass:create()
    elseif t == "string" then
        if string.byte(filename) == 35 then -- first char is #
            local frame = display.newSpriteFrame(string.sub(filename, 2))
            if frame then
                if params and params.capInsets then
                    sprite = spriteClass:createWithSpriteFrame(frame, params.capInsets)
                else
                    sprite = spriteClass:createWithSpriteFrame(frame)
                end
            end
        else
            if display.TEXTURES_PIXEL_FORMAT[filename] then
                cc.Texture2D:setDefaultAlphaPixelFormat(display.TEXTURES_PIXEL_FORMAT[filename])
                sprite = spriteClass:create(filename)
                cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2D_PIXEL_FORMAT_RGBA8888)
            else
                if params and params.capInsets then
                    sprite = spriteClass:create(filename, params.capInsets)
                else
                    sprite = spriteClass:create(filename)
                end
            end
        end
    elseif t == "cc.SpriteFrame" then
        sprite = spriteClass:createWithSpriteFrame(filename)
    elseif t == "cc.Texture2D" then
        sprite = spriteClass:createWithTexture(filename)
    else
        printError("display.newSprite() - invalid filename value type")
        sprite = spriteClass:create()
    end

    if sprite then
        if x and y then sprite:setPosition(x, y) end
        if size then sprite:setContentSize(size) end
    else
        printError("display.newSprite() - create sprite failure, filename %s", tostring(filename))
        sprite = spriteClass:create()
    end

    return sprite
end

--[[
  New a Scale9Sprite.
  @function newScale9Sprite
  @param string filename, image path
  @param integer x, positionX
  @param integer y, positionY
  @param table size, scale to size
  @param table capInsets, scale9 param
  @return Scale9Sprite ret, ccui.Scale9Sprite

  example:
  local sprite = display.newScale9Sprite("bg.png", 0, 0, cc.size(200, 100), cc.rect(10, 10, 20, 20))
]]--
function display.newScale9Sprite(filename, x, y, size, capInsets)
    return display.newSprite(filename, x, y, {
		class = ccui.Scale9Sprite,
		size = size,
		capInsets = capInsets
	})
end

--[[
  New a Tiled sprite.
  @function newTilesSprite
  @param string filename, image path
  @param cc.rect rect, Tiling rect
  @return Sprite ret, cc.Sprite

  example:
  local sprite = display.newTilesSprite("bg.png", cc.rect(10, 10, 20, 20))
]]--
function display.newTilesSprite(filename, rect)
    if not rect then
        rect = cc.rect(0, 0, display.width, display.height)
    end
    local sprite = cc.Sprite:create(filename, rect)
    if not sprite then
        printError("display.newTilesSprite() - create sprite failure, filename %s", tostring(filename))
        return
    end

    sprite:getTexture():setTexParameters(cc.backendSamplerFilter.LINEAR, cc.backendSamplerFilter.LINEAR, cc.backendSamplerAddressMode.REPEAT, cc.backendSamplerAddressMode.REPEAT)

    display.align(sprite, display.LEFT_BOTTOM, 0, 0)

    return sprite
end

--[[
  Create a tiled SpriteBatchNode
  @function newTiledBatchNode
  @param mixed filename, As same a the first parameter for display.newSprite
  @param string plistFile, Texture(plist) image filename, filename must be a part of the texture.
  @param size size, The tiled node size, use cc.size create it please.
  @param integer hPadding, Horizontal padding.
  @param integer vPadding, Vertical padding.
  @return SpriteBatchNode ret, cc.SpriteBatchNode
]]--
function display.newTiledBatchNode(filename, plistFile, size, hPadding, vPadding)
    size = size or cc.size(display.width, display.height)
    hPadding = hPadding or 0
    vPadding = vPadding or 0
    local __sprite = display.newSprite(filename)
    local __sliceSize = __sprite:getContentSize()
    __sliceSize.width = __sliceSize.width - hPadding
    __sliceSize.height = __sliceSize.height - vPadding
    local __xRepeat = math.ceil(size.width/__sliceSize.width)
    local __yRepeat = math.ceil(size.height/__sliceSize.height)
    -- How maney sprites we need to fill in tiled node?
    local __capacity = __xRepeat * __yRepeat
    local __batch = display.newBatchNode(plistFile, __capacity)
    local __newSize = cc.size(0,0)

    for y=0,__yRepeat-1 do
        for x=0,__xRepeat-1 do
            __newSize.width = __newSize.width + __sliceSize.width
            __sprite = display.newSprite(filename)
                :align(display.LEFT_BOTTOM,x*__sliceSize.width, y*__sliceSize.height)
                :addTo(__batch)
        end
        __newSize.height = __newSize.height + __sliceSize.height
    end
    __batch:setContentSize(__newSize)

    return __batch, __newSize.width, __newSize.height
end

--[[
  Create a DrawNode
  @function newDrawNode
  @return DrawNode ret, cc.DrawNode
]]--
function display.newDrawNode()
    return cc.DrawNode:create()
end

--[[
  Create a solid circle DrawNode
  @function newSolidCircle
  @param number radius, radius of the circle
  @param table params, {x, y, color}
  @return DrawNode ret, cc.DrawNode

  example:
  local circle = display.newSolidCircle(10, {x = 150, y = 150, color = cc.c4f(1, 1, 1, 1)})
]]--
function display.newSolidCircle(radius, params)
    local circle = display.newDrawNode()
    circle:drawSolidCircle(cc.p(params.x or 0, params.y or 0),
        radius or 0,
        params.angle or 0,
        params.segments or 50,
        params.scaleX or 1.0,
        params.scaleY or 1.0,
        params.color or cc.c4f(0, 0, 0, 1)
    )
    return circle
end

--[[
  Create a circle DrawNode
  @function newCircle
  @param number radius, radius of the circle
  @param table params, {x, y, fillColor, borderColor, borderWidth}
  @return DrawNode ret, cc.DrawNode

  example:
  local circle = display.newCircle(50, {
    x = 100,
	y = 100,
    fillColor = cc.c4f(1, 0, 0, 1), -- if set, be a solid circle
    borderColor = cc.c4f(0, 1, 0, 1),
    borderWidth = 2
  })
]]--
function display.newCircle(radius, params)
    params = checktable(params)

    local function makeVertexs(radius)
        local segments = params.segments or 32
        local startRadian = 0
        local endRadian = math.pi * 2
        local posX = params.x or 0
        local posY = params.y or 0
        if params.startAngle then
            startRadian = math.angle2radian(params.startAngle)
        end
        if params.endAngle then
            endRadian = startRadian + math.angle2radian(params.endAngle)
        end
        local radianPerSegm = 2 * math.pi / segments
        local points = {}
        for i = 1, segments do
            local radii = startRadian + i * radianPerSegm
            if radii > endRadian then break end
            points[#points + 1] = {posX + radius * math.cos(radii), posY + radius * math.sin(radii)}
        end
        return points
    end

    local points = makeVertexs(radius)
    local circle = display.newPolygon(points, params)
    if circle then
        circle.radius = radius
        circle.params = params

        function circle:setRadius(radius)
            self:clear()
            local points = makeVertexs(radius)
            display.newPolygon(points, params, self)
        end

        function circle:setLineColor(color)
            self:clear()
            local points = makeVertexs(radius)
            params.borderColor = color
            display.newPolygon(points, params, self)
        end
    end
    return circle
end

--[[
  Create a rect DrawNode
  @function newRect
  @param table rect
  @param table params, {fillColor, borderColor, borderWidth}
  @return DrawNode ret, cc.DrawNode

  example:
  local rect = display.newRect(cc.rect(100, 100, 40, 40), {
    fillColor = cc.c4f(1,0,0,1),
	borderColor = cc.c4f(0,1,0,1),
	borderWidth = 5
  })
]]--
function display.newRect(rect, params)
    local x, y, width, height = 0, 0
    x = rect.x or 0
    y = rect.y or 0
    height = rect.height
    width = rect.width

    local points = {
        {x,y},
        {x + width, y},
        {x + width, y + height},
        {x, y + height}
    }
    return display.newPolygon(points, params)
end

--[[
  Create a rounded rect DrawNode
  @function newRoundedRect
  @param size size
  @param integer radius, rounded corner radius
  @param table params, {fillColor, borderColor, borderWidth}
  @return DrawNode ret, cc.DrawNode

  example:
  local rect = display.newRoundedRect(cc.size(200, 100), 40, {
    fillColor = cc.c4f(1,0,0,1),
    borderColor = cc.c4f(0,1,0,1),
    borderWidth = 1
  })
]]--
function display.newRoundedRect(size, radius, params)
    local radius = radius or 1
    local segments = math.ceil(radius)
    local radianPerSegment = math.pi * 0.5 / segments
    local radianVertices = {}

    for i = 0, segments do
        local radian = i * radianPerSegment
        radianVertices[i] = cc.p(math.round(math.cos(radian) * radius * 10) / 10, math.round(math.sin(radian) * radius * 10) / 10)
    end

    local points = {}
    local tagCenter = cc.p(0, 0)

    -- left up
    tagCenter = cc.p(radius, size.height - radius)
    for i = 0, segments do
        local ri = i
        points[#points + 1] = cc.p(tagCenter.x - radianVertices[ri].x, tagCenter.y + radianVertices[ri].y)
    end

    -- right up
    tagCenter = cc.p(size.width - radius, size.height - radius)
    for i = 0, segments do
        local ri = segments - i
        points[#points + 1] = cc.p(tagCenter.x + radianVertices[ri].x, tagCenter.y + radianVertices[ri].y)
    end

    -- right bottom
    tagCenter = cc.p(size.width - radius, radius)
    for i = 0, segments do
        local ri = i
        points[#points + 1] = cc.p(tagCenter.x + radianVertices[ri].x, tagCenter.y - radianVertices[ri].y)
    end

    -- left bottom
    tagCenter = cc.p(radius, radius)
    for i = 0, segments do
        local ri = segments - i
        points[#points + 1] = cc.p(tagCenter.x - radianVertices[ri].x, tagCenter.y - radianVertices[ri].y)
    end
    points[#points + 1] = cc.p(points[1].x, points[1].y)

	params = checktable(params)
    local borderWidth = params.borderWidth or 0.5
    local fillColor = params.fillColor or cc.c4f(1, 1, 1, 1)
    local borderColor = params.borderColor or cc.c4f(1, 1, 1, 1)
    local drawNode = cc.DrawNode:create()
    drawNode:drawPolygon(points, #points, fillColor, borderWidth, borderColor)
    drawNode:setContentSize(size)
	drawNode:setAnchorPoint(cc.p(0.5, 0.5))

    return drawNode
end

--[[
  Create a line DrawNode
  @function newLine
  @param table points
  @param table params, {borderColor, borderWidth}
  @return DrawNode ret, cc.DrawNode

  example:
  local line = display.newLine({{10, 10}, {100,100}}, {
    borderColor = cc.c4f(1.0, 0.0, 0.0, 1.0),
    borderWidth = 1
  })
]]--
function display.newLine(points, params)
    local radius
    local borderColor
    local scale

    if not params then
        borderColor = cc.c4f(0,0,0,1)
        radius = 0.5
        scale = 1.0
    else
        borderColor = params.borderColor or cc.c4f(0,0,0,1)
        radius = (params.borderWidth and params.borderWidth/2) or 0.5
        scale = checknumber(params.scale or 1.0)
    end

    for i, p in ipairs(points) do
        p = cc.p(p[1] * scale, p[2] * scale)
        points[i] = p
    end

    local drawNode = cc.DrawNode:create()
    drawNode:drawSegment(points[1], points[2], radius, borderColor)

    return drawNode
end

--[[
  Create a polygon DrawNode
  @function newPolygon
  @param table points
  @param table params, {scale, borderWidth, fillColor, borderColor}
  @param DrawNode drawNode
  @return DrawNode ret, cc.DrawNode

  example:
  local line = display.newPolygon({{30, 30}, {30, 60}, {60, 60}}, {
    scale = 1,
    borderWidth = 1,
    fillColor = cc.c4f(0.0, 1.0, 0.0, 1.0),
    borderColor = cc.c4f(1.0, 0.0, 0.0, 1.0),
  })
]]--
function display.newPolygon(points, params, drawNode)
    params = checktable(params)
    local scale = checknumber(params.scale or 1.0)
    local borderWidth = checknumber(params.borderWidth or 0.5)
    local fillColor = params.fillColor or cc.c4f(1, 1, 1, 0)
    local borderColor = params.borderColor or cc.c4f(0, 0, 0, 1)

    local pts = {}
    for i, p in ipairs(points) do
        pts[i] = {x = p[1] * scale, y = p[2] * scale}
    end

    drawNode = drawNode or cc.DrawNode:create()
    drawNode:drawPolygon(pts, #pts, fillColor, borderWidth, borderColor)
    return drawNode
end

--[[
  Create a bmfont label
  @function newBMFontLabel
  @param table params, {text, font, align, maxLineWidth, offsetX, offsetY, x, y}
  @return Label ret, cc.Label

  example:
  local label = display.newBMFontLabel({
    text = "Hello",
    font = "UIFont.fnt",
  })
]]--
function display.newBMFontLabel(params)
    assert(type(params) == "table",
           "[framework.display] newBMFontLabel() invalid params")

    local text      = tostring(params.text)
    local font      = params.font
    local textAlign = params.align or cc.TEXT_ALIGNMENT_LEFT
    local maxLineW  = params.maxLineWidth or 0
    local offsetX   = params.offsetX or 0
    local offsetY   = params.offsetY or 0
    local x, y      = params.x, params.y
    assert(font ~= nil, "framework.display.newBMFontLabel() - not set font")

    local label = cc.Label:createWithBMFont(font, text, textAlign, maxLineW, cc.p(offsetX, offsetY));
    if not label then return end

    if type(x) == "number" and type(y) == "number" then
        label:setPosition(x, y)
    end

    return label
end

--[[
  Create a TTF label
  @function newTTFLabel
  @param table params, {text, font, size, color, align, valign, dimensions, x, y}
  @return Label ret, cc.Label

  align can be:
  cc.TEXT_ALIGNMENT_LEFT
  cc.TEXT_ALIGNMENT_CENTER
  cc.TEXT_ALIGNMENT_RIGHT

  valign can be:
  cc.VERTICAL_TEXT_ALIGNMENT_TOP
  cc.VERTICAL_TEXT_ALIGNMENT_CENTER
  cc.VERTICAL_TEXT_ALIGNMENT_BOTTOM

  example:
  local label = display.newTTFLabel({
    text = "Hello, World\n您好，世界",
    font = "Arial",
    size = 64,
    color = cc.c3b(255, 0, 0),
    align = cc.TEXT_ALIGNMENT_LEFT,
    valign = cc.VERTICAL_TEXT_ALIGNMENT_TOP,
    dimensions = cc.size(400, 200)
  })
]]--
function display.newTTFLabel(params)
    assert(type(params) == "table",
           "[framework.display] newTTFLabel() invalid params")

    local text       = tostring(params.text)
    local font       = params.font or display.DEFAULT_TTF_FONT
    local size       = params.size or display.DEFAULT_TTF_FONT_SIZE
    local color      = params.color or display.COLOR_WHITE
    local textAlign  = params.align or cc.TEXT_ALIGNMENT_LEFT
    local textValign = params.valign or cc.VERTICAL_TEXT_ALIGNMENT_TOP
    local x, y       = params.x, params.y
    local dimensions = params.dimensions or cc.size(0, 0)

    assert(type(size) == "number",
           "[framework.display] newTTFLabel() invalid params.size")

    local label
    if cc.FileUtils:getInstance():isFileExist(font) then
        label = cc.Label:createWithTTF(text, font, size, dimensions, textAlign, textValign)
        if label then
            label:setColor(color)
        end
    else
        label = cc.Label:createWithSystemFont(text, font, size, dimensions, textAlign, textValign)
        if label then
            label:setTextColor(color)
        end
    end

    if label then
        if x and y then label:setPosition(x, y) end
    end

    return label
end

--[[
  setAnchorPoint for specified target with specified type, and setPosition.
  @function align
  @param Node target
  @param integer anchorPointType
  @param integer x
  @param integer y

  anchorPointType can be:
  display.CENTER
  display.LEFT_TOP
  display.TOP_LEFT
  display.CENTER_TOP
  display.TOP_CENTER
  display.RIGHT_TOP
  display.TOP_RIGHT
  display.CENTER_LEFT
  display.LEFT_CENTER
  display.CENTER_RIGHT
  display.RIGHT_CENTER
  display.BOTTOM_LEFT
  display.LEFT_BOTTOM
  display.BOTTOM_RIGHT
  display.RIGHT_BOTTOM
  display.BOTTOM_CENTER
  display.CENTER_BOTTOM

  example:
  display.align(node, display.LEFT_TOP, 0, 0)
]]--
function display.align(target, anchorPoint, x, y)
    target:setAnchorPoint(display.ANCHOR_POINTS[anchorPoint])
    if x and y then target:setPosition(x, y) end
end

--[[
  Load a image into TextureCache Async.
  @function addImageAsync
  @param string imagePath
  @param function callback
]]--
function display.addImageAsync(imagePath, callback)
    sharedTextureCache:addImageAsync(imagePath, callback)
end

--[[
  Load SpriteFrames from plist(TexturePacker).
  @function addSpriteFrames
  @param string plistFilename
  @param string imageName
  @param function handler, if set, load Async

  example:
  display.addSpriteFrames("Sprites.plist", "Sprites.png")
]]--
function display.addSpriteFrames(plistFilename, image, handler)
    local async = type(handler) == "function"
    local asyncHandler = nil
    if async then
        asyncHandler = function()
            local texture = sharedTextureCache:getTextureForKey(image)
            assert(texture, string.format("The texture %s, %s is unavailable.", plistFilename, image))
            sharedSpriteFrameCache:addSpriteFrames(plistFilename, texture)
            handler(plistFilename, image)
        end
    end

    if display.TEXTURES_PIXEL_FORMAT[image] then
        cc.Texture2D:setDefaultAlphaPixelFormat(display.TEXTURES_PIXEL_FORMAT[image])
        if async then
            sharedTextureCache:addImageAsync(image, asyncHandler)
        else
            sharedSpriteFrameCache:addSpriteFrames(plistFilename, image)
        end
        cc.Texture2D:setDefaultAlphaPixelFormat(cc.backendPixelFormat.BGRA8888)
    else
        if async then
            sharedTextureCache:addImageAsync(image, asyncHandler)
        else
            sharedSpriteFrameCache:addSpriteFrames(plistFilename, image)
        end
    end
end

--[[
  Unload SpriteFrames from plist(TexturePacker).
  @function removeSpriteFramesWithFile
  @param string plistFilename
  @param string imageName
]]--
function display.removeSpriteFramesWithFile(plistFilename, imageName)
    sharedSpriteFrameCache:removeSpriteFramesFromFile(plistFilename)
    if imageName then
        display.removeSpriteFrameByImageName(imageName)
    end
end

--[[
  Set Texture PixelFormat when Texture file load by display functions.
  @function setTexturePixelFormat
  @param string filename
  @param integer format (cc.backendPixelFormat)
]]--
function display.setTexturePixelFormat(filename, format)
    display.TEXTURES_PIXEL_FORMAT[filename] = format
end

--[[
  Remove image from SpriteFrameCache & TextureCache.
  @function removeSpriteFrameByImageName
  @param string imageName
]]--
function display.removeSpriteFrameByImageName(imageName)
    sharedSpriteFrameCache:removeSpriteFrameByName(imageName)
    cc.Director:getInstance():getTextureCache():removeTextureForKey(imageName)
end

--[[
  Create a batch node base no texture.
  @function newBatchNode
  @param string image
  @param integer capacity
]]--
function display.newBatchNode(image, capacity)
    return cc.SpriteBatchNode:create(image, capacity or 100)
end

--[[
  Create or Get SpriteFrame.
  @function newSpriteFrame
  @param string frameName
  @return frame cc.SpriteFrame
]]--
function display.newSpriteFrame(frameName)
    local frame = sharedSpriteFrameCache:getSpriteFrame(frameName)
    if not frame then
        printError("display.newSpriteFrame() - invalid frameName %s", tostring(frameName))
    end
    return frame
end

--[[
  Create a table contain SpriteFrames.
  @function newFrames
  @param string pattern
  @param integer begin
  @param integer length
  @param boolean isReversed
  @return table ret

  example:
  local frames = display.newFrames("Walk%04d.png", 1, 8)
]]--
function display.newFrames(pattern, begin, length, isReversed)
    local frames = {}
    local step = 1
    local last = begin + length - 1
    if isReversed then
        last, begin = begin, last
        step = -1
    end

    for index = begin, last, step do
        local frameName = string.format(pattern, index)
        local frame = sharedSpriteFrameCache:getSpriteFrame(frameName)
        if not frame then
            printError("display.newFrames() - invalid frame, name %s", tostring(frameName))
            return
        end

        frames[#frames + 1] = frame
    end
    return frames
end

--[[
  Create a cc.Animation from SpriteFrames.
  @function newAnimation
  @param table frames, get from display.newFrames()
  @param number time
  @return Animation ret, cc.Animation

  example:
  local animation = display.newAnimation(frames, 0.5 / 8)
]]--
function display.newAnimation(frames, time)
    time = time or 1.0 / #frames
    return cc.Animation:createWithSpriteFrames(frames, time)
end

--[[
  Cache cc.Animation by name.
  @function setAnimationCache
  @param string name
  @param Animation animation

  example:
  display.setAnimationCache("Walk", animation)
]]--
function display.setAnimationCache(name, animation)
    sharedAnimationCache:addAnimation(animation, name)
end

--[[
  Get cached cc.Animation by name.
  @function getAnimationCache
  @param string name
  @return Animation ret, cc.Animation

  example:
  local animation = display.getAnimationCache("Walk")
]]--
function display.getAnimationCache(name)
    return sharedAnimationCache:getAnimation(name)
end

--[[
  Remove cached cc.Animation by name.
  @function removeAnimationCache
  @param string name
]]--
function display.removeAnimationCache(name)
    sharedAnimationCache:removeAnimation(name)
end

--[[
  Remove Unused Sprite Frames.
  @function removeUnusedSpriteFrames
]]--
function display.removeUnusedSpriteFrames()
    sharedSpriteFrameCache:removeUnusedSpriteFrames()
    sharedTextureCache:removeUnusedTextures()
end

display.PROGRESS_TIMER_RADIAL = 0
display.PROGRESS_TIMER_BAR = 1

--[[
  Create progress timer node.
  @function newProgressTimer
  @param mixed image
  @param number progressType
]]--
function display.newProgressTimer(image, progresssType)
    if type(image) == "string" then
        image = display.newSprite(image)
    end

    local progress = cc.ProgressTimer:create(image)
    progress:setType(progresssType)
    return progress
end

--[[
  Capture Screen and save to file.
  @function captureScreen
  @param function callback
  @param string fileName

  example:
  display.captureScreen(function(bSuc, filePath)
    print(bSuc, filePath)
  end, "screen.png")
]]--
function display.captureScreen(callback, fileName)
	cc.utils:captureScreen(callback, fileName)
end

return display
