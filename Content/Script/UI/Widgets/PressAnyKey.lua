--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_CAW_PressAnyKey_C
local M = UnLua.Class()

--function M:OnInitialized()
--end

--function M:PreConstruct(IsDesignTime)
--end

function M:Construct()
    if self.Anim_PressAntKey then
        self:PlayAnimation(self.Anim_PressAntKey, 0.0, 0, UE.EUMGSequencePlayMode.Forward, 0.5, false)
    end
end

--function M:Tick(MyGeometry, InDeltaTime)
--end

function M:OnMouseButtonDown(MyGeometry, MouseEvent)
    self:PushMainMenu()
    return self:Handled()
end

function M:OnKeyDown(MyGeometry, InKeyEvent)
    self:PushMainMenu()
    return self:Handled()
end

function M:BP_GetDesiredFocusTarget()
    return self
end

return M
