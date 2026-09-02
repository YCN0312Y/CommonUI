--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_TabList_Option_C
local M = UnLua.Class()

--function M:OnInitialized()
--end

function M:PreConstruct(IsDesignTime)
    if IsDesignTime then
        self:DebugCreateTabsEditorOnly()
    else
        if self.CommonActionWidget_LastTab and self.CommonActionWidget_NextTab then
            self.CommonActionWidget_LastTab:SetInputAction(self.PreviousTabInputActionData)
            self.CommonActionWidget_NextTab:SetInputAction(self.NextTabInputActionData)
            print("aaaaaaaa")
        end
    end
end

--function M:Construct()
--end

--function M:Tick(MyGeometry, InDeltaTime)
--end

function M:HandleTabCreation(TabNameID, TabButton)

    self:AddTabToHorizontalBoxContainer(TabButton)

end
--仅在蓝图编辑器中调用
function M:DebugCreateTabsEditorOnly()

    local TabCount = self.DebugEditorPreviewTabCount
    local TabButtonClass = self.TabButtonEntryWidgetClass

    if TabCount > 0 and UE.UKismetSystemLibrary.IsValidClass(TabButtonClass) then
        for i = 1, TabCount, 1 do
            self:AddTabToHorizontalBoxContainer(nil)
        end
    end

end

return M
