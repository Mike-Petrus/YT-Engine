#include "src/Core/Engine.h"
#include "src/Timer/Timer.h"

int main(int argc, char* args[]){
    
    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->IsRunning()){
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->Clean();

    return 0;
}