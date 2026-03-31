// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillSlot.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "PaperSprite.h"

void USkillSlot::NativePreConstruct()
{
    if (SkillIcon && Sprite)
    {
        SkillIcon->SetBrushFromAtlasInterface(Sprite);
    }
}

void USkillSlot::NativeConstruct()
{
    if (PreviousSkill)
    {
        PreviousSkill->OnUnlocked.AddUObject(this, &USkillSlot::SetWidgetColor, FLinearColor::White);

        if (!PreviousSkill->IsUnlocked)
        {
            SetWidgetColor(BlockedColor);
        }
    }

    if (IsPermanentlyUnlocked)
    {
        Unlock();
    }

    if (!IsUnlocked)
    {
        OuterBorder->SetVisibility(ESlateVisibility::Hidden);
    }
}

int32 USkillSlot::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
    LayerId = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

    if (!PreviousSkill)
    {
        return LayerId;
    }

    // Draw line to previous skill
    FGeometry widgetGeometry{ GetCachedGeometry() };
    FGeometry parentGeometry{ PreviousSkill->GetCachedGeometry() };

    float widgetRadius{ widgetGeometry.GetAbsoluteSize().X / 2.f };
    float parentRadius{ parentGeometry.GetAbsoluteSize().X / 2.f };
    FVector2D widgetCenter{ widgetGeometry.GetAbsolutePosition() + widgetGeometry.GetAbsoluteSize() / 2.f };
    FVector2D parentCenter{ parentGeometry.GetAbsolutePosition() + parentGeometry.GetAbsoluteSize() / 2.f };

    FVector2D direction = parentCenter - widgetCenter;
    if (direction.SquaredLength() <= (widgetRadius + parentRadius) * (widgetRadius + parentRadius))
    {
        // Widgets are too close, no need to draw a line between them
        return LayerId;
    }
    direction.Normalize();

    FVector2D start = widgetGeometry.AbsoluteToLocal(widgetCenter + direction * widgetRadius);
    FVector2D end = widgetGeometry.AbsoluteToLocal(parentCenter - direction * parentRadius);
    
    FSlateDrawElement::MakeLines(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(), {start, end}, ESlateDrawEffect::None, CurrentColor, true, 2.f);

    return LayerId + 1;
}

void USkillSlot::Unlock()
{
    if (IsUnlocked)
    {
        return;
    }

    IsUnlocked = true;
    PlayAnimation(UnlockAnim);
    SetWidgetColor(UnlockedColor);
}

void USkillSlot::SetWidgetColor(FLinearColor NewColor)
{
    CurrentColor = NewColor;

    SkillIcon->SetColorAndOpacity(NewColor);
}
