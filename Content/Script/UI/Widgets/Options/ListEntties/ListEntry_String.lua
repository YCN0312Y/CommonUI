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

function M:BP_OnToggleEntryWidgetHighLightState(bIsSelected)

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

        --字体样式
        local Default = self.DefaultTextStyle
        local HighLight = self.HighLightTextStyle

        if HighLight and HighLight then
            if bIsSelected then
                SettingDisplayName:SetStyle(HighLight)
                MyText:SetStyle(HighLight)
            else
                SettingDisplayName:SetStyle(Default)
                MyText:SetStyle(Default)
            end
        end
        Last:TaggleButtonImageHighLight(bIsSelected)
        Next:TaggleButtonImageHighLight(bIsSelected)
    end
    
end

return M
