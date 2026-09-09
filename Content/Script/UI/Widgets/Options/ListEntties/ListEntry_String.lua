--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_ListEntry_SubTab_String_C
local M = UnLua.Class()

--function M:Initialize(Initializer)
--end

--function M:PreConstruct(IsDesignTime)
--end

-- function M:Construct()
-- end

--function M:Tick(MyGeometry, InDeltaTime)
--end

--子标题选中时调用
function M:BP_OnListEntryWidgetSelectionChanged(bIsSelected)
    --条目控件会被列表池化复用，缓存的 bEntryHovered 可能是上一个标签页遗留的，
    --这里以控件自身的真实悬停状态重新同步一次
    self.bEntryHovered = self:IsHovered() == true
    self:ToggleHighLightState(bIsSelected or self.bEntryHovered)
end

function M:BP_OnListEntryWidgetHovered(bWasHovered, bIsEntryWidgetStillSelected)
    self.bEntryHovered = bWasHovered
    --（选中/悬停）那就高亮
    self:ToggleHighLightState(bWasHovered or bIsEntryWidgetStillSelected)
end

function M:ToggleHighLightState(ShouldHighLight)
    --字体样式
    local TextStyle = self.SubTabTextStyle
    local NewTextStyle
    if ShouldHighLight then
        NewTextStyle = TextStyle:Find("HighLight")
    else
        NewTextStyle = TextStyle:Find("Normal")
    end
    if not NewTextStyle then
        return
    end

    --旋转器
    local AvailableOptions = self.CommonRotator_AvailableOptions
    local MyText
    if AvailableOptions then
        MyText = AvailableOptions.MyText
    end
    if not MyText then
        return
    end

    local SettingDisplayName = self.CommonText_SettingDisplayName
    local Last = self.CommonButton_Last
    local Next = self.CommonButton_Next

    if SettingDisplayName and Last and MyText and Next then

        SettingDisplayName:SetStyle(NewTextStyle)
        MyText:SetStyle(NewTextStyle)

        Last:TaggleButtonImageHighLight(ShouldHighLight)
        Next:TaggleButtonImageHighLight(ShouldHighLight)
    end
end

return M
