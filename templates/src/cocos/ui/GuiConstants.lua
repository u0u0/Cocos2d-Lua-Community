if nil == ccui then
	return
end

ccui.BrightStyle = {
	NONE = -1,
	NORMAL = 0,
	HIGHLIGHT = 1,
}

ccui.TextureResType = {
	LOCAL = 0,
	PLIST = 1,
}

ccui.TouchEventType = {
	BEGAN = 0,
	MOVED = 1,
	ENDED = 2,
	CANCELED = 3,
}

ccui.SizeType = {
	ABSOLUTE = 0,
	PERCENT = 1,
}

ccui.PositionType = {
	ABSOLUTE = 0,
	PERCENT = 1,
}

ccui.CheckBoxEventType = {
	SELECTED = 0,
	UNSELECTED = 1,
}

ccui.RadioButtonEventType = {
	SELECTED = 0,
	UNSELECTED = 1
}

ccui.RadioButtonGroupEventType = {
	SELECT_CHANGED = 0
}

ccui.TextFiledEventType = {
	ATTACH_WITH_IME = 0,
	DETACH_WITH_IME = 1,
	INSERT_TEXT = 2,
	DELETE_BACKWARD = 3,
}

ccui.LayoutType = {
	ABSOLUTE = 0,
	VERTICAL = 1,
	HORIZONTAL = 2,
	RELATIVE = 3,
}

ccui.LayoutClippingType = {
	STENCIL = 0,
	SCISSOR = 1,
}

ccui.LayoutBackGroundColorType = {
	NONE = 0,
	SOLID = 1,
	GRADIENT = 2,
}

ccui.LayoutParameterType = {
	NONE = 0,
	LINEAR = 1,
	RELATIVE = 2,
}

ccui.LinearGravity = {
	NONE = 0,
	LEFT = 1,
	TOP = 2,
	RIGHT = 3,
	BOTTOM = 4,
	CENTER_VERTICAL = 5,
	CENTER_HORIZONTAL = 6,
}

ccui.RelativeAlign = {
	NONE = 0,
	PARENT_TOP_LEFT = 1,
	PARENT_TOP_CENTER_HORIZONTAL = 2,
	PARENT_TOP_RIGHT = 3,
	PARENT_LEFT_CENTER_VERTICAL = 4,
	CENTER_IN_PARENT = 5,
	PARENT_RIGHT_CENTER_VERTICAL = 6,
	PARENT_LEFT_BOTTOM = 7,
	PARENT_BOTTOM_CENTER_HORIZONTAL = 8,
	PARENT_RIGHT_BOTTOM = 9,
	LOCATION_ABOVE_LEFTALIGN = 10,
	LOCATION_ABOVE_CENTER = 11,
	LOCATION_ABOVE_RIGHTALIGN = 12,
	LOCATION_LEFT_OF_TOPALIGN = 13,
	LOCATION_LEFT_OF_CENTER = 14,
	LOCATION_LEFT_OF_BOTTOMALIGN = 15,
	LOCATION_RIGHT_OF_TOPALIGN = 16,
	LOCATION_RIGHT_OF_CENTER = 17,
	LOCATION_RIGHT_OF_BOTTOMALIGN = 18,
	LOCATION_BELOW_LEFTALIGN = 19,
	LOCATION_BELOW_CENTER = 20,
	LOCATION_BELOW_RIGHTALIGN = 21,
}

ccui.SliderEventType = {
	ON_PERCENTAGE_CHANGED = 0,
	ON_SLIDEBALL_DOWN = 1,
	ON_SLIDEBALL_UP = 2,
	ON_SLIDEBALL_CANCEL = 3,
}

ccui.LoadingBarDirection = {
	LEFT = 0,
	RIGHT = 1
}

ccui.ScrollViewDirection = {
	NONE = 0,
	VERTICAL = 1,
	HORIZONTAL = 2,
	BOTH = 3,
}

ccui.ScrollViewMoveDirection = {
	TOP = 0,
	BOTTOM = 1,
	LEFT = 2,
	RIGHT = 3,
}

ccui.ScrollviewEventType = {
	SCROLL_TO_TOP = 0,
	SCROLL_TO_BOTTOM = 1,
	SCROLL_TO_LEFT = 2,
	SCROLL_TO_RIGHT = 3,
	SCROLLING = 4,
	BOUNCE_TOP = 5,
	BOUNCE_BOTTOM = 6,
	BOUNCE_LEFT = 7,
	BOUNCE_RIGHT = 8,
	CONTAINER_MOVED = 9,
	SCROLLING_BEGAN = 10,
	SCROLLING_ENDED = 11,
	AUTOSCROLL_ENDED = 12,
}

ccui.ListViewGravity = {
	LEFT = 0,
	RIGHT = 1,
	CENTER_HORIZONTAL = 2,
	TOP = 3,
	BOTTOM = 4,
	CENTER_VERTICAL = 5,
}

ccui.ListViewEventType = {
	ON_SELECTED_ITEM_START = 0,
	ON_SELECTED_ITEM_END = 1,
}

ccui.ListViewMagneticType = {
	NONE = 0,
	CENTER = 1,
	BOTH_END = 2,
	LEFT = 3,
	RIGHT = 4,
	TOP = 5,
	BOTTOM = 6,
}

ccui.PageViewEventType = {
	TURNING = 0,
}

ccui.PageViewTouchDirection = {
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3
}

ccui.TextType = {
	SYSTEM = 0,
	TTF = 1,
}

ccui.LayoutComponentHorizontalEdge = {
	None = 0,
	Left = 1,
	Right = 2,
	Center = 3,
}

ccui.LayoutComponentVerticalEdge = {
	None = 0,
	Bottom = 1,
	Top = 2,
	Center = 3,
}

ccui.VideoPlayerEvent = {
	PLAYING = 0,
	PAUSED = 1,
	STOPPED = 2,
	COMPLETED = 3,
}

ccui.MovementEventType = {
	START = 0,
	COMPLETE = 1,
	LOOP_COMPLETE = 2,
}
