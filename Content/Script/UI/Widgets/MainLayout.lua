--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_CUW_MainLayout_C
local M = UnLua.Class()

function M:OnInitialized()

    self:RegisterStack("Frontend", self.WidgetStack_Frontend)
    self:RegisterStack("GameHUD", self.WidgetStack_GameHUD)
    self:RegisterStack("GameMenu", self.WidgetStack_GameMenu)
    self:RegisterStack("Modal", self.WidgetStack_Modal)
    
end

--function M:PreConstruct(IsDesignTime)
--end   

-- function M:Construct()
-- end

--function M:Tick(MyGeometry, InDeltaTime)
--end

function M:RegisterStack(StackName, WidgetStack)

    local Tag = self.StackTag:Find(StackName)

    if Tag and WidgetStack then
        self:RegisteredWidgetStack(Tag, WidgetStack)
    else
        print("注册WidgetStack失败", "StackName =", StackName, "Tag =", Tag, "WidgetStack =", WidgetStack)
    end
end

return M
