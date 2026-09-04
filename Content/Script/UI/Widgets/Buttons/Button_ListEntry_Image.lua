--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_Button_ListEntry_Image_C
local M = UnLua.Class()

function M:OnInitialized()

    local ButtonImage = self.CommonImage_ButtonImage
    local ButtonImageStyle = self.ButtonImageStyle
    local DefaultButtonImageColor = self.DefaultButtonImageColor
    
    if ButtonImage and ButtonImageStyle and DefaultButtonImageColor then
        ButtonImage:SetBrushFromLazyTexture(ButtonImageStyle, false)
        ButtonImage:SetColorAndOpacity(DefaultButtonImageColor)
    end

end

--function M:PreConstruct(IsDesignTime)
--end

-- function M:Construct()
-- end

--function M:Tick(MyGeometry, InDeltaTime)
--end

return M
