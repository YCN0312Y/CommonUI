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

function M:Construct()
    self:DebugCreateTabsEditorOnly()
end

--function M:Tick(MyGeometry, InDeltaTime)
--end

--仅在蓝图编辑器中调用
function M:DebugCreateTabsEditorOnly()

    local TabCount = self.DebugEditorPreviewTabCount
    local TabButtonClass = self.TabButtonEntryWidgetClass

    if TabCount > 0 and TabButtonClass:IsValidClass() then
        for i = 1, TabCount, 1 do
            self:AddTabToHorizontalBoxContainer()
            print("调用2")
        end
    end

end

return M
