--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_ListEntry_KeyRemap_C
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

    --显示名称
    local SettingDisplayName = self.CommonText_SettingDisplayName

    if SettingDisplayName and self.DefaultStyle and self.HighLightStyle then
        if bIsSelected then
            SettingDisplayName:SetStyle(self.HighLightStyle)
        else
            SettingDisplayName:SetStyle(self.DefaultStyle)
        end
    end
    
end

return M
