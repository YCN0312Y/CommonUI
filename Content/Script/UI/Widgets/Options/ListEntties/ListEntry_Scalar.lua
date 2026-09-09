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

    if SettingSlider and SliderDefaultColor then
        SettingSlider:SetSliderBarColor(SliderDefaultColor)
        SettingSlider:SetSliderHandleColor(SliderDefaultColor)
    end
end

-- function M:Construct()
-- end

--function M:Tick(MyGeometry, InDeltaTime)
--end

return M
