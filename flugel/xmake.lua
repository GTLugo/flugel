-- GLOBAL --
set_allowedarchs("x64")
set_languages("c17", "cxx20")
add_rules("mode.debug", "mode.release")
if is_mode("debug") then
  add_defines("DEBUG")
elseif is_mode("release") then
  add_defines("NDEBUG")
end

-- ENGINE --
add_requires("glew", "glfw", "glm", "spdlog")
engine_name = "flugel_engine"
target(engine_name)
  -- Info --
  set_default(false)
  set_kind("shared")
  set_basename("flugel")
  add_defines("FLUGEL_BUILD_DLL")
  -- Files & Headers --
  add_includedirs(engine_name .. "/src", {interface = true})
  add_files(engine_name .. "/src/**.cpp")
  -- Dependencies --
  add_packages("glew", "glfw", "glm", "spdlog", {public = true})

-- APP --
app_name = "alpha_app"
target(app_name)
  -- Info --
  set_default(true)
  set_kind("binary")
  set_basename("ALPHA")
  -- Files & Headers --
  add_includedirs(app_name .. "/src")
  add_files(app_name .. "/src/**.cpp")
  -- Dependencies --
  add_deps(engine_name)