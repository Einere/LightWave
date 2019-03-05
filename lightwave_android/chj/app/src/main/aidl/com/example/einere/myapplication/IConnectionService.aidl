// IConnectionService.aidl
package com.example.einere.myapplication;

// Declare any non-default types here with import statements

interface IConnectionService {
    /**
     * Demonstrates some basic types that you can use as parameters
     * and return values in AIDL.
     */
    int getStatus();
    void setSocket(String ip, int port);
    void connect();
    void disconnect();
    void send(String packet);
    void receive();
}
