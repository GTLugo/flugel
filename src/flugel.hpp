#pragma once

// ONLY FOR USE BY EXTERNAL APPS

#include <memory>
// entry
//#include "entry_point.hpp"
// utility
#include "util/types.hpp"
#include "util/utilities.hpp"
#include "util/logging/log.hpp"
// app
#include "core/app.hpp"
#include "core/layers/layer.hpp"
#include "core/input/input.hpp"
#include "core/input/mouse_codes.hpp"
#include "core/input/key_codes.hpp"
#include "core/ecs/components/transform.hpp"
#include "core/ecs/components/camera.hpp"
// events
#include "core/callbacks/event_system.hpp"
// rendering
#include "core/renderer/renderer.hpp"