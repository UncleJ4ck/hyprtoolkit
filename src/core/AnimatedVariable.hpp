#pragma once

#include <hyprtoolkit/palette/Color.hpp>
#include <hyprtoolkit/palette/Gradient.hpp>
#include <hyprutils/animation/AnimatedVariable.hpp>
#include <hyprutils/math/Vector2D.hpp>

#include "../helpers/Memory.hpp"

namespace Hyprtoolkit {

    enum eAnimatedVarType : int8_t {
        AVARTYPE_INVALID = -1,
        AVARTYPE_FLOAT,
        AVARTYPE_VECTOR,
        AVARTYPE_COLOR,
        AVARTYPE_GRADIENT,
    };

    // Utility to bind a type with its corresponding eAnimatedVarType
    template <class T>
    // NOLINTNEXTLINE(readability-identifier-naming)
    struct STypeToAnimatedVarType_t {
        static constexpr eAnimatedVarType value = AVARTYPE_INVALID;
    };

    template <>
    struct STypeToAnimatedVarType_t<float> {
        static constexpr eAnimatedVarType value = AVARTYPE_FLOAT;
    };

    template <>
    struct STypeToAnimatedVarType_t<Hyprutils::Math::Vector2D> {
        static constexpr eAnimatedVarType value = AVARTYPE_VECTOR;
    };

    template <>
    struct STypeToAnimatedVarType_t<CHyprColor> {
        static constexpr eAnimatedVarType value = AVARTYPE_COLOR;
    };

    template <>
    struct STypeToAnimatedVarType_t<CGradientValueData> {
        static constexpr eAnimatedVarType value = AVARTYPE_GRADIENT;
    };

    template <class T>
    inline constexpr eAnimatedVarType typeToeAnimatedVarType = STypeToAnimatedVarType_t<T>::value;

    template <class T, class... U>
    concept OneOf = (... or std::same_as<T, U>);

    template <class T>
    concept Animable = OneOf<T, Hyprutils::Math::Vector2D, float, CHyprColor, CGradientValueData>;

    struct SAnimationContext {};

    template <Animable VarType>
    using CAnimatedVariable = Hyprutils::Animation::CGenericAnimatedVariable<VarType, SAnimationContext>;

    template <Animable VarType>
    using PHLANIMVAR = UP<CAnimatedVariable<VarType>>;

    template <Animable VarType>
    using PHLANIMVARREF = WP<CAnimatedVariable<VarType>>;
}
