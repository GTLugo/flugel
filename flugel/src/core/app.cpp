#include "app.hpp"

#include "core/input/input.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
// #include <boost/gil.hpp>
// #include <boost/gil/extension/io/png.hpp>
#include <boost/range/adaptor/reversed.hpp>

namespace fge {
  App* App::instance_ = nullptr;

  App::App(const WindowProperties& props) {
    FGE_DEBUG_ENG("Current working directory: {}", std::filesystem::current_path());
    FGE_TRACE_ENG("Constructing App...");
    instance_ = this;
    window_ = Window::create(props);
    window_->setEventCallback(FGE_BIND(eventDispatch));
    
    int32_t width, height;
    // boost::gil::rgb8_image_t icon;
    // boost::gil::
    uint8_t* icon = stbi_load("res/flugel/icon.png", &width, &height, 0, 4);
    window_->setIcon(icon, width, height);
    stbi_image_free(icon);
    
    // engine layer should be first layer (last to check)
    engineLayer_ = new EngineLayer{};
    pushLayer(engineLayer_);
  }

  App::~App() {
    FGE_TRACE_ENG("Destructing App...");
  }

  void App::pushLayer(Layer* layer) {
    layerStack_.pushLayer(layer);
  }

  void App::pushOverlay(Layer* overlay) {
    layerStack_.pushOverlay(overlay);
  }

  void App::run() {
    FGE_TRACE_ENG("Started main thread (ID: {})", std::this_thread::get_id());
    threadPool_.initialize();
    threadPool_.pushJob(FGE_BIND(gameLoop));
    threadPool_.pushJob(FGE_BIND(renderLoop));

    // MAIN THREAD
    AppStartMainEvent mainStartEvent{};
    eventDispatch(mainStartEvent);
    while (!shouldClose_) {
      AppPollEvent pollEvent{};
      eventDispatch(pollEvent);

      AppUpdateMainEvent mainUpdateEvent{};
      eventDispatch(mainUpdateEvent);
    }
    AppEndMainEvent mainEndEvent{};
    eventDispatch(mainEndEvent);

    renderCondition_.notify_all();
    threadPool_.shutdown();
    FGE_TRACE_ENG("Ended main thread");
  }

  void App::close() {
    shouldClose_ = true;
  }
  
  void App::renderLoop() {
    FGE_TRACE_ENG("Started render thread (ID: {})", std::this_thread::get_id());
    window_->context().setCurrent(true);
    
    // RENDER THREAD
    AppStartRenderEvent renderStartEvent{};
    eventDispatch(renderStartEvent);
    while (!shouldClose_) {
      waitForRenderJob();
    }
    AppEndRenderEvent renderEndEvent{};
    eventDispatch(renderEndEvent);

    FGE_TRACE_ENG("Ended render thread");
  }
  
  void App::gameLoop() {
    FGE_TRACE_ENG("Started game thread (ID: {})", std::this_thread::get_id());

    // GAME THREAD
    AppStartGameEvent startEvent{};
    eventDispatch(startEvent);
    while (!shouldClose_) {
      // This loop will only occur once every fixedTimeStep, being skipped for every
      // frame which happens between each timestep. If the deltaTime per frame is too
      // long, then for each frame, this loop will occur more than once in order to
      // "catch up" with the proper pacing of physics.
      // Source: https://gameprogrammingpatterns.com/game-loop.html#play-catch-up
      //FGE_TRACE_ENG("UPDATE");
      while (time_.shouldDoTick()) {
        // Physics & timestep sensitive stuff happens in here, where timestep is fixed
        AppTickGameEvent tickEvent{};
        eventDispatch(tickEvent);

        time_.tick();
      }
      // Timestep INSENSITIVE stuff happens out here, where pacing goes as fast as possible
      AppUpdateGameEvent updateEvent{};
      eventDispatch(updateEvent);

      AppUpdateRenderEvent renderUpdateEvent{};
      pushRenderJob(renderUpdateEvent);

      time_.update();
    }
    AppEndGameEvent endEvent{};
    eventDispatch(endEvent);

    FGE_TRACE_ENG("Ended game thread");
  }

  void App::waitForRenderJob() {
    AppUpdateRenderEvent event;

    {
      std::unique_lock<std::mutex> lock{renderMutex_};
      //FGE_DEBUG_ENG("Render thread waiting...");
      renderCondition_.wait(lock, [this]{
        return !renderQueue_.empty() || shouldClose_;
      });

      if (!shouldClose_) {
        event = renderQueue_.front();
        renderQueue_.pop();
      }
      //FGE_INFO_ENG("Render thread done waiting!");
    }

    if (!shouldClose_) {
      //FGE_TRACE_ENG("Starting render job!");
      eventDispatch(event);
    }
  }

  void App::pushRenderJob(AppUpdateRenderEvent& event) {
    { // Mutex lock scope
      std::unique_lock<std::mutex> lock{renderMutex_};
      if (renderQueue_.size() < 2) {
        renderQueue_.push(event);
      }
    } // Unlock mutex

    renderCondition_.notify_all();
  }
  
  void App::eventDispatch(Event& e) {
    //EventDispatcher dispatcher{e};
    
    // LAYER EVENT FNs
    // for (LayerStack::reverse_iterator ritr = layerStack_.rbegin();
    //      ritr != layerStack_.rend() - 1; 
    //      ++ritr) {
    //   (*ritr)->onEvent(e);
    //   if (e.wasHandled()) {
    //     break;
    //   }
    // }
    // (*layerStack_.begin())->onEvent(e);

    for (auto& layer : boost::adaptors::reverse(layerStack_)) {
      layer->onEvent(e);
      //FGE_DEBUG_ENG("{0}: {1}", layer->name(), e);
      if (e.wasHandled() && layer != *layerStack_.begin()) {
        (*layerStack_.begin())->onEvent(e); // engine layer should always run
        break;
      }
    }
  }
}