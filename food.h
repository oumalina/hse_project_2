#pragma once

class Food {
    public:
        Food();
        void expire();
        void move(float, float);
        void update(float time);

        static constexpr int exp_time_interval = 30.0f;
    private:
        float x, y;
        float last_update_time;
};