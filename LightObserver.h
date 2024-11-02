#ifndef LIGHTOBSERVER_H
#define LIGHTOBSERVER_H

class Light;

class LightObserver {
public:
    virtual void updateLight(const Light& light) = 0;
};

#endif
