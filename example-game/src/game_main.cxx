#include "../../dreco-engine/src/core/engine.hxx"

int main() 
{       
    dreco::engine* engine = new dreco::engine();

    auto engine_properties = dreco::engine_properties();
    engine_properties.window_title = "Example Game";

    const auto init_res = engine->Init(engine_properties);
    
    if (init_res == dreco::INIT_SUCCESS) 
    {
        engine->StartMainLoop();
    }

    delete engine;
    
    return 0; 
}