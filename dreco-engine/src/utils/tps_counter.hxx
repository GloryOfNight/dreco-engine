#pragma once

namespace dreco
{
class tps_counter
{
public:
	tps_counter() : tick_counter{0}, tps{0}, tps_timer(1.0f), was_updated(false)
    {
    }

	void Tick(const float& _dt) 
    {
        ++tick_counter;
        tps_timer -= _dt;
        
        if (tps_timer < 0.0f) 
        {
            tps = tick_counter;
            tick_counter = 0;
            tps_timer = 1.0f + (tps_timer * -1);

            was_updated = true;
        }
        else if (was_updated) 
        {
            was_updated = false;
        }
    }

    unsigned short int Get() const 
    {
        return tps;
    }

    bool IsUpdated() const 
    {
        return was_updated;
    }

private:
	unsigned short int tick_counter;

    unsigned short int tps;
    
    float tps_timer;

    bool was_updated;
};
}	 // namespace dreco