--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_ListEntry_Scalar_C
local M = UnLua.Class()

--function M:OnInitialized()
--end

function M:PreConstruct(IsDesignTime)
    local SettingSlider = self.AnalogSlider_SettingSlider
    local SliderDefaultColor = self.SliderDefaultColor
    local NewColor
    if SliderDefaultColor then
        
    end
    if SettingSlider and SliderDefaultColor then
        SettingSlider:SetSliderBarColor(SliderDefaultColor)
        SettingSlider:SetSliderHandleColor(SliderDefaultColor)
    end
end

-- function M:Construct()
-- end

--function M:Tick(MyGeometry, InDeltaTime)
--end

--子标题选中时调用
function M:BP_OnListEntryWidgetSelectionChanged(bIsSelected)
    
    self:ToggleHighLightState(bIsSelected)
end

function M:BP_OnListEntryWidgetHovered(bWasHovered, bIsEntryWidgetStillSelected)

    if bWasHovered or not bIsEntryWidgetStillSelected then
        self:ToggleHighLightState(bWasHovered)
    end
    
end

function M:ToggleHighLightState(ShouldHighLight)

    --设置文本样式
    local SettingDisplayName = self.CommonText_SettingDisplayName
    local SettingValue = self.CommonNumeric_SettingValue

    if SettingDisplayName and SettingValue then
        --文本样式
        local DefaultStyle = self.DefaultTextStyle
        local HighLightStyle = self.HighLightTextStyle

        if DefaultStyle and HighLightStyle then
            if ShouldHighLight then
                SettingDisplayName:SetStyle(HighLightStyle)
                SettingValue:SetStyle(HighLightStyle)
            else
                SettingDisplayName:SetStyle(DefaultStyle)
                SettingValue:SetStyle(DefaultStyle)
            end
        end
    end
    --滑块
    local DefaultColor = self.DefaultSliderColor
    local HighLightColor = self.HighLightSliderColor
    local SettingSlider = self.AnalogSlider_SettingSlider

    if SettingSlider and HighLightColor and DefaultColor then
        if ShouldHighLight then
            SettingSlider:SetSliderBarColor(HighLightColor)
        else
            SettingSlider:SetSliderBarColor(DefaultColor)
        end
    end
end
return M
