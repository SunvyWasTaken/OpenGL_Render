#pragma once

#include "Editor/StateMachine/StateMachine.h"
#include "Procedural/FaultFormation/FaultFormation.h"

// I Should put more using for the different Procedural gen available so it will be more easy to use.

using ProceduralGen = My::Variant<FaultFormation, NoErrosion>;
using ProceduralGen_t = ProceduralGen::variant_t;
