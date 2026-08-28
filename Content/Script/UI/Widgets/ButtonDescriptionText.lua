--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--


---@type WBP_Text_ButtonDescriptioText_C
local M = UnLua.Class()

function M:OnInitialized()

    self.WidgetSubsystem = UE.USubsystemBlueprintLibrary.GetGameInstanceSubsystem(self, UE.UYCNWidgetSubsystem)

    if self.WidgetSubsystem then
        print("YCNWidgetSubsystem有效")
        self.WidgetSubsystem.OnButtonDescriptionTextUpdate:Add(self, M.OnButtonDescriptionTextUpdate)
    end

end

--function M:PreConstruct(IsDesignTime)
--end

function M:Construct()

    if self.CommonText_ButtonDescription then
        self.CommonText_ButtonDescription:SetText("")
    end

end

--function M:Tick(MyGeometry, InDeltaTime)
--end

function M:OnButtonDescriptionTextUpdate(BroadCastingButton, DescriptionText)
    if self.CommonText_ButtonDescription then
        self.CommonText_ButtonDescription:SetText(DescriptionText)
    end
end

return M
