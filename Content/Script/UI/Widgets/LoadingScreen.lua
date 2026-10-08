--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_LoadingScreen_C
local M = UnLua.Class()

--function M:Initialize(Initializer)
--end

--function M:PreConstruct(IsDesignTime)
--end

function M:Construct()
    self.LoadingScreenSubsystem = UE.USubsystemBlueprintLibrary.GetGameInstanceSubsystem(self, UE.UYCNLoadingScreenSubsystem)

    local Subsystem = self.LoadingScreenSubsystem
    if Subsystem and Subsystem:IsValid() then
        Subsystem.OnLoadingReasonUpdate:Add(self, M.OnLoadingReasonUpdateEvent)
    end
end

--function M:Tick(MyGeometry, InDeltaTime)
--end

function M:Destruct()

    local Subsystem = self.LoadingScreenSubsystem

    if Subsystem and Subsystem:IsValid() then
        Subsystem.OnLoadingReasonUpdate:Remove(self, M.OnLoadingReasonUpdateEvent)
    end

    self.LoadingScreenSubsystem = nil
end

function M:OnActivated()
    AboutDisplayString = "About"
end

function M:OnLoadingReasonUpdateEvent(CurrendLoadingReason)
    if self.CommonText_LoadingReason then
        local Text = UE.UKismetTextLibrary.Conv_StringToText(CurrendLoadingReason)
        self.CommonText_LoadingReason:SetText(Text)
    end
end

return M
