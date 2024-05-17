#pragma once

#include "Editor/StateMachine/StateMachine.h"
#include "Procedural/FaultFormation/FaultFormation.h"

// I Should put more using for the different Procedural gen available so it will be more easy to use.

#ifndef PROCEDURAL_GEN
#define PROCEDURAL_GEN
using ProceduralGen = My::Variant<FaultFormation, NoGeneration>;
using ProceduralGen_t = typename ProceduralGen::variant_t;
#endif // !PROCEDURAL_GEN
