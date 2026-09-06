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

function M:TaggleButtonImageHighLight(ShouldHighLight)
    local ButtonImage = self.CommonImage_ButtonImage
    local DefaultButtonImageColor = self.DefaultButtonImageColor
    local HighLightButtonImageColor = self.HighLightButtonImageColor

    if ButtonImage and DefaultButtonImageColor and HighLightButtonImageColor then
        if ShouldHighLight then
            ButtonImage:SetColorAndOpacity(HighLightButtonImageColor)
        else
            ButtonImage:SetColorAndOpacity(DefaultButtonImageColor)
        end
        
    end
end

return M
