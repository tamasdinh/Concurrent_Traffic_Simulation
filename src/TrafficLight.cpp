#include <iostream>
#include <random>
#include <chrono>
#include "TrafficLight.h"

template <typename T>
T MessageQueue<T>::receive() {
    // (DONE) TODO FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait()
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 

    std::unique_lock<std::mutex> uLock(_msgMutex);
    _msgCondVar.wait(uLock, [this]{ return !_queue.empty(); });

    T msg = std::move(_queue.back());
    return msg;
}

template <typename T>
void MessageQueue<T>::send(T &&msg) {
    // (DONE) TODO FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex>
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.

    std::lock_guard<std::mutex> gLock(_msgMutex);
    _queue.push_back(std::move(msg));
    _msgCondVar.notify_one();
}



TrafficLight::TrafficLight() {
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen() {
    // (DONE) TODO FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        TrafficLightPhase _trafficLightPhaseMsg = _trafficLightMsgQueue.receive();
        if (_trafficLightPhaseMsg == green)
            break;
    }
}

TrafficLightPhase TrafficLight::getCurrentPhase() {
    return _currentPhase;
}


void TrafficLight::simulate()
{
    // (DONE)TODO FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class.
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // (DONE) TODO FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles
    // and toggles the current phase of the traffic light between red and green and sends an update method
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds.
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles.

    std::chrono::time_point<std::chrono::system_clock> cycleStart = std::chrono::system_clock::now();
    unsigned short int cycleDuration;
    std::random_device fluxCapacitor;
    std::uniform_int_distribution switchCycle(4'000, 6'000);
    long timeSinceStart;

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::mt19937_64 randomGen(fluxCapacitor());
        cycleDuration = switchCycle(randomGen);
        std::this_thread::sleep_for(std::chrono::milliseconds(cycleDuration));
        timeSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - cycleStart).count();
        if (timeSinceStart >= cycleDuration) {
            _currentPhase = (_currentPhase == red) ? green : red;

            // (DONE) TODO: send an update method to the message queue using move semantics
            _trafficLightMsgQueue.send(std::move(_currentPhase));

        cycleStart = std::chrono::system_clock::now();
        }
    }
}

