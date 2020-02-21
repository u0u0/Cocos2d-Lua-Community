if nil == fairygui then
    return
end

fairygui.UIEventType = {
	Enter = 0,
	Exit = 1,
	Changed = 2,
	Submit = 3,
	
	TouchBegin = 10,
	TouchMove = 11,
	TouchEnd = 12,
	Click = 13,
	RollOver = 14,
	RollOut = 15,
	MouseWheel = 16,
	RightClick = 17,
	MiddleClick = 18,
	
	PositionChange = 20,
	SizeChange = 21,
	
	KeyDown = 30,
	KeyUp = 31,
	
	Scroll = 40,
	ScrollEnd = 41,
	PullDownRelease = 42,
	PullUpRelease = 43,
	
	ClickItem = 50,
	ClickLink = 51,
	ClickMenu = 52,
	RightClickItem = 53,
	
	DragStart = 60,
	DragMove = 61,
	DragEnd = 62,
	Drop = 63,
	
	GearStop = 70,
}

fairygui.PackageItemType = {
	IMAGE = 0,
	MOVIECLIP = 1,
	SOUND = 2,
	COMPONENT = 3,
	ATLAS = 4,
	FONT = 5,
	SWF = 6,
	MISC = 7,
	UNKNOWN = 8
}

fairygui.ObjectType = {
	IMAGE = 0,
	MOVIECLIP = 1,
	SWF = 2,
	GRAPH = 3,
	LOADER = 4,
	GROUP = 5,
	TEXT = 6,
	RICHTEXT = 7,
	INPUTTEXT = 8,
	COMPONENT = 9,
	LIST = 10,
	LABEL = 11,
	BUTTON = 12,
	COMBOBOX = 13,
	PROGRESSBAR = 14,
	SLIDER = 15,
	SCROLLBAR = 16,
	TREE = 17
}

fairygui.ButtonMode = {
	COMMON = 0,
	CHECK = 1,
	RADIO = 2
}

fairygui.ChildrenRenderOrder = {
	ASCENT = 0,
	DESCENT = 1,
	ARCH = 2,
}

fairygui.OverflowType = {
	VISIBLE = 0,
	HIDDEN = 1,
	SCROLL = 2
}

fairygui.ScrollType = {
	HORIZONTAL = 0,
	VERTICAL = 1,
	BOTH = 2
}

fairygui.ScrollBarDisplayType = {
	DEFAULT = 0,
	VISIBLE = 1,
	AUTO = 2,
	HIDDEN = 3
}

fairygui.LoaderFillType = {
	NONE = 0,
	SCALE = 1,
	SCALE_MATCH_HEIGHT = 2,
	SCALE_MATCH_WIDTH = 3,
	SCALE_FREE = 4,
	SCALE_NO_BORDER = 5
}

fairygui.ProgressTitleType = {
	PERCENT = 0,
	VALUE_MAX = 1,
	VALUE = 2,
	MAX = 3
}

fairygui.ListLayoutType = {
	SINGLE_COLUMN = 0,
	SINGLE_ROW = 1,
	FLOW_HORIZONTAL = 2,
	FLOW_VERTICAL = 3,
	PAGINATION = 4
}

fairygui.ListSelectionMode = {
	SINGLE = 0,
	MULTIPLE = 1,
	MULTIPLE_SINGLECLICK = 2,
	NONE = 3
}

fairygui.GroupLayoutType = {
	NONE = 0,
	HORIZONTAL = 1,
	VERTICAL = 2
}

fairygui.PopupDirection = {
	AUTO = 0,
	UP = 1,
	DOWN = 2
}

fairygui.AutoSizeType = {
	NONE = 0,
	BOTH = 1,
	HEIGHT = 2,
	SHRINK = 3
}

fairygui.FlipType = {
	NONE = 0,
	HORIZONTAL = 1,
	VERTICAL = 2,
	BOTH = 3
}

fairygui.TransitionActionType = {
	XY = 0,
	Size = 1,
	Scale = 2,
	Pivot = 3,
	Alpha = 4,
	Rotation = 5,
	Color = 6,
	Animation = 7,
	Visible = 8,
	Sound = 9,
	Transition = 10,
	Shake = 11,
	ColorFilter = 12,
	Skew = 13,
	Text = 14,
	Icon = 15,
	Unknown = 16
}

fairygui.FillMethod = {
	None = 0,
	Horizontal = 1,
	Vertical = 2,
	Radial90 = 3,
	Radial180 = 4,
	Radial360 = 5,
}

fairygui.FillOrigin = {
	Top = 0,
	Bottom = 1,
	Left = 2,
	Right = 3
}

fairygui.ObjectPropID = {
	Text = 0,
	Icon = 1,
	Color = 2,
	OutlineColor = 3,
	Playing = 4,
	Frame = 5,
	DeltaTime = 6,
	TimeScale = 7,
	FontSize = 8,
	Selected = 9
}
