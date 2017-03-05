#pragma once

#pragma warning (disable:4239) //Nonstandard extensions
#pragma warning (disable:4996) //Unsafe functions

#include <iostream>
#include <unordered_map>
#include <string>
#include <bitset>

#include "../../CommonUtilities/GrowingArray.h"
#include "../../CommonUtilities/VectorOnStack.h"
#include "../../CommonUtilities/Matrix44.h"
#include "../../CommonUtilities/Intersection.h"
#include "../../CommonUtilities/Macro.h"

#include "../../Input/InputManager.h"

#include "../../Time/Time.h"

#include "../../Engine/Engine.h"
#include "../../Engine/Instance.h"
#include "../../Engine/ModelLoader.h"
#include "../../Engine/Animation.h"

#include "CardFactory.h"
#include "XMLReader.h"
#include "AbilityStack.h"
#include "AnimationManager.h"