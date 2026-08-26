--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type BP_YCNPlayerController_C
local M = UnLua.Class()

-- function M:Initialize(Initializer)
-- end

-- function M:UserConstructionScript()
-- end

-- function M:ReceiveBeginPlay()
-- end

-- function M:ReceiveEndPlay()
-- end

-- function M:ReceiveTick(DeltaSeconds)
-- end

-- function M:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
-- end

-- function M:ReceiveActorBeginOverlap(OtherActor)
-- end

-- function M:ReceiveActorEndOverlap(OtherActor)
-- end

function M:ReceivePossess(PossessedPawn)

    if self.MainLayoutClass then
        local MainLayout = UE.UWidgetBlueprintLibrary.Create(self, self.MainLayoutClass, self)

        if MainLayout then
            MainLayout:AddToViewport(0)

            local WidgetSubsystem = UE.USubsystemBlueprintLibrary.GetGameInstanceSubsystem(self, UE.UYCNWidgetSubsystem)
            if WidgetSubsystem then
               print("WidgetSubsystem有效")
               WidgetSubsystem:RegisterCreateMainLayoutWidget(MainLayout) 
            end
        end
    end

end

return M
