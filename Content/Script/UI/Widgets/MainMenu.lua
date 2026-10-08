--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

local YCNFunctionLibrary = UE.UYCNFunctionLibrary
---@type WBP_CAW_MainMenu_C
local M = UnLua.Class()

function M:OnInitialized()

    if self.Button_Quit then
        self.Button_Quit.OnButtonBaseClicked:Add(self, M.OnClickedButton_Quit)
    end

    if self.Button_Stroy then
        self.Button_Stroy.OnButtonBaseClicked:Add(self, M.OnClickedButton_Stroy)
    end

    if self.Button_Options then
        self.Button_Options.OnButtonBaseClicked:Add(self, M.OnClickedButton_Option)
    end

    if self.Button_About then
        self.Button_About.OnButtonBaseClicked:Add(self, M.OnClickedButton_About)
    end
end

function M:BP_OnActivated()

    self:SwitchCameraByTagWithBlend("Default", 1, 0.5)
end
--退出游戏回调函数
function M:OnClickedButton_Quit(Button)

    self:SwitchCameraByTagWithBlend("Quit", 1.0, 0.5)

    if UE.UYCNAsyncAction_PushConfirmWindow then
        local AsyncAction = UE.UYCNAsyncAction_PushConfirmWindow.PushConfirmWindow(self, UE.EConfirmWindowType.YesNo, "退出游戏", "确定退出游戏？")
        if AsyncAction then
            AsyncAction.OnButtonClicked:Add(self, M.OnConfirmWindowButtonClicked)
            AsyncAction:Activate()
        end
    end

end

function M:OnConfirmWindowButtonClicked(ButtonType)

    if ButtonType == UE.EConfirmWindowButtonType.Confirm then
        UE.UKismetSystemLibrary.QuitGame(self, nil, UE.EQuitPreference.Quit, false)
    elseif ButtonType == UE.EConfirmWindowButtonType.Cencel or ButtonType == UE.EConfirmWindowButtonType.Closed then
        -- 取消或关闭：对应截图中两根线连到同一个节点
        self:SwitchCameraByTagWithBlend("Default", 1.0, 0.5)
    end

end

--故事回调函数
function M:OnClickedButton_Stroy(Button)

    local CachedOwningPC = self:GetCachedOwningPC()
    local StoryWidgetTag = self.WidgetStackTags:Find("Story")

    if UE.UYCNAsyncAction_PushSoftWidget and CachedOwningPC and YCNFunctionLibrary and StoryWidgetTag then
        local StoryWidgetClass = YCNFunctionLibrary.GetSoftWidgetClassByTag(StoryWidgetTag)
        if StoryWidgetClass then
            local AsyncAction = UE.UYCNAsyncAction_PushSoftWidget.PushSoftWidget(self, CachedOwningPC, StoryWidgetClass, self.WidgetTag, true)
            if AsyncAction then

            if not AsyncAction.OnWidgetCreateBeforePush then
                return
            end                
                AsyncAction.OnWidgetCreateBeforePush:Add(self, M.SwitchCameraByTag_Story)
                AsyncAction:Activate()
            end
        end
    end
end

--选项回调函数
function M:OnClickedButton_Option(Button)

    local CachedOwningPC = self:GetCachedOwningPC()
    local OptionWidgetTag = self.WidgetStackTags:Find("Option")

    if UE.UYCNAsyncAction_PushSoftWidget and CachedOwningPC and YCNFunctionLibrary and OptionWidgetTag then
        local OptionWidgetClass = YCNFunctionLibrary.GetSoftWidgetClassByTag(OptionWidgetTag)
        if OptionWidgetClass then
            local AsyncAction = UE.UYCNAsyncAction_PushSoftWidget.PushSoftWidget(self, CachedOwningPC, OptionWidgetClass, self.WidgetTag, true)
            if AsyncAction then

            if not AsyncAction.OnWidgetCreateBeforePush then
                return
            end
                AsyncAction.OnWidgetCreateBeforePush:Add(self, M.SwitchCameraByTag_Option)
                AsyncAction:Activate()
            end
        end
    end
end

function M:OnClickedButton_About(Button)
    local CachedOwningPC = self:GetCachedOwningPC()
    local OptionWidgetTag = self.WidgetStackTags:Find("About")

    if UE.UYCNAsyncAction_PushSoftWidget and CachedOwningPC and YCNFunctionLibrary and OptionWidgetTag then
        local OptionWidgetClass = YCNFunctionLibrary.GetSoftWidgetClassByTag(OptionWidgetTag)
        if OptionWidgetClass then
            local AsyncAction = UE.UYCNAsyncAction_PushSoftWidget.PushSoftWidget(self, CachedOwningPC, OptionWidgetClass, self.WidgetTag, true)
            if AsyncAction then

            if not AsyncAction.OnWidgetCreateBeforePush then
                return
            end
                AsyncAction.OnWidgetCreateBeforePush:Add(self, M.SwitchCameraByTag_About)
                AsyncAction:Activate()
            end
        end
    end
end

function M:SwitchCameraByTag_Story(PushedWidget)
    self:SwitchCameraByTagWithBlend("Story", 1.0, 0.5)
end

function M:SwitchCameraByTag_Option(PushedWidget)
    self:SwitchCameraByTagWithBlend("Option", 1.0, 0.5)
end

function M:SwitchCameraByTag_About(PushedWidget)
    self:SwitchCameraByTagWithBlend("About", 1.0, 0.5)
end

function M:SwitchCameraByTagWithBlend(CameraTag, InBlendTime, InBlendExp)

    local CameraActorClass = UE.UClass.Load("/Script/Engine.CameraActor")
    if CameraActorClass then

        local CameraActors = UE.TArray(UE.AActor)
        local CameraActorTArray = UE.UGameplayStatics.GetAllActorsOfClassWithTag(self,CameraActorClass, CameraTag, CameraActors)

        -- 没有匹配的摄像机，就不进行切换
        local CameraCount = CameraActors:Num()
        if CameraCount == 0 then
            print("需要切换的摄像机数量为0")
            return
        end

        -- UnLua 的 TArray:Get() 使用从 1 开始的索引
        local RandomIndex = math.random(1, CameraCount)
        local CameraActor = CameraActors:Get(RandomIndex)
        if not CameraActor or not CameraActor:IsValid() then
            return
        end
        if self:GetCachedOwningPC()then
            self:GetCachedOwningPC():SetViewTargetWithBlend(CameraActor, InBlendTime, self.BlendFunc, InBlendExp, false)
        end
    end
end

return M
