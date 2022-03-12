#pragma once

// ONLY FOR USE BY EXTERNAL APPS

// entry
//#include "entry_point.hpp"
// utility
#include "util/utilities.hpp"
#include "util/logging/log.hpp"
// app
#include "core/app.hpp"
#include "core/layers/layer.hpp"
#include "core/input/input.hpp"
#include "core/input/mouse_codes.hpp"
#include "core/input/key_codes.hpp"
// events
#include "core/callbacks/events/event.hpp"
#include "core/callbacks/events/app_event.hpp"
#include "core/callbacks/events/render_event.hpp"
#include "core/callbacks/events/logic_event.hpp"
#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/keyboard_event.hpp"
#include "core/callbacks/events/mouse_event.hpp"
// rendering
#include "core/renderer/renderer.hpp"