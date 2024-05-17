#pragma once

#include "Editor/StateMachine/StateMachine.h"
#include "Procedural/FaultFormation/FaultFormation.h"
#include "Procedural/MidpointDisplacement/MidpointDisplacement.h"

// I Should put more using for the different Procedural gen available so it will be more easy to use.

using ProceduralGen = My::Variant<FaultFormation, MidpointDispTerrain, NoGeneration>;

using ProceduralGen_t = typename ProceduralGen::variant_t;
using DefaultGenType = typename std::variant_alternative_t<0, ProceduralGen_t>;

template <int index>
using ProceduralGenTypeAt = typename std::variant_alternative_t<index, ProceduralGen_t>;
