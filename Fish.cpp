#include "Fish.h"

Fish::Fish()
{
    //ctor
}

Fish::~Fish()
{
    //dtor
}

size_t Fish::getX() {
    return this->_x;
}
size_t Fish::getY() {
    return this->_y;
}

//Возвращает количество рыбы в клетке
uint8_t Fish::getFish() {
    return this->_fish_count;
}


bool Fish::getAvailable() {
    if(this->_state == FISHPOINT_ST::UNACTIVE) {
        return true;
    }

    if(this->_state == FISHPOINT_ST::ACTIVE) {
        return true;
    }

    if(this->_state == FISHPOINT_ST::LOCK) {
        return false;
    }
    return true;
}

void Fish::generateFish(ui tick) {
    this->_fish_count = GENERATE_FISH_COUNT_LOW + rand()%(GENERATE_FISH_COUNT_HIGH - GENERATE_FISH_COUNT_LOW);
    this->_local_tick = tick;
    this->_state = FISHPOINT_ST::ACTIVE;
}

void Fish::changeState(ui tick) {
    ui time_activation = GENERATE_FISH_TIMER_LOW + rand()%(GENERATE_FISH_TIMER_HIGH + GENERATE_FISH_TIMER_LOW);
    if(tick - this->_local_tick < time_activation && this->_fish_count <=0) {
        this->_state = FISHPOINT_ST::LOCK;
        this->_fish_count = 0;
    }
    
    else if (tick - this->_local_tick < time_activation && this->_fish_count > 0) {
        this->_state = FISHPOINT_ST::ACTIVE;
    }
    
    else if (tick - this->_local_tick >= time_activation) {
        this->_state = FISHPOINT_ST::UNACTIVE;
    }
}

void Fish::try_lock(ui counter) {
    if(this->_state == FISHPOINT_ST::ACTIVE) {
        ui time_activation = GENERATE_FISH_TIMER_LOW + rand()%(GENERATE_FISH_TIMER_HIGH + GENERATE_FISH_TIMER_LOW);
        if(counter - this->_local_tick < time_activation && this->_fish_count <= 0) {
            this->_state = FISHPOINT_ST::LOCK;
            this->_fish_count = 0;
        }
    }
}


void Fish::try_unlock(ui counter) {
    if(this->_state == FISHPOINT_ST::LOCK) {
        ui time_activation = GENERATE_FISH_TIMER_LOW + rand()%(GENERATE_FISH_TIMER_HIGH + GENERATE_FISH_TIMER_LOW);
        if(counter - this->_local_tick > time_activation) {
            this->_state = FISHPOINT_ST::UNACTIVE;
        }
    }
}


FISHPOINT_ST Fish::getState() {
    return this->_state;
}

void Fish::killFish(ui fish_count) {
    this->_fish_count -= fish_count;
}


void Fish::setPoint (size_t x, size_t y) {
    this->_x = x;
    this->_y = y;

}
