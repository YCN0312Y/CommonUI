--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--
local YCNFunctionLibrary = UE.UYCNFunctionLibrary

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
        --主控件
        local MainLayout = UE.UWidgetBlueprintLibrary.Create(self, self.MainLayoutClass, self)
        --控件子系统
        local WidgetSubsystem = UE.USubsystemBlueprintLibrary.GetGameInstanceSubsystem(self, UE.UYCNWidgetSubsystem)
        
        if MainLayout and WidgetSubsystem then
            
            MainLayout:AddToViewport(0)
            print("WidgetSubsystem有效")
            WidgetSubsystem:RegisterCreateMainLayoutWidget(MainLayout)

            --函数库
            if YCNFunctionLibrary then
                local PressAnyKeyWidget = YCNFunctionLibrary.GetSoftWidgetClassByTag(self.SoftWidgetTag)

                --任意键控件
                if PressAnyKeyWidget then
                    local AsyncAction = UE.UYCNAsyncAction_PushSoftWidget.PushSoftWidget(self, self, PressAnyKeyWidget, self.WidgetTag, true)
                    if AsyncAction then
                        AsyncAction:Activate()
                    end
                end

            end

        end
    end
end

return M
