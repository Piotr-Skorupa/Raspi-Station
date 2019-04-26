#pragma once

#include <cstdlib>
#include <cstring>
#include <chrono>
#include <thread>
#include <ctime>
#include <iostream>
#include <string>
#include <random>
#include "src/mqtt/async_client.h"
#include "Logger.hpp"
#include "Camera.hpp"

using namespace std;
using namespace std::chrono;

namespace camera        // classes and variables for mqtt camera subscribing
{

const int	QOS = 1;
const int	N_RETRY_ATTEMPTS = 5;
const std::string SERVER_ADDRESS("********");
const std::string CLIENT_ID("camera_subcribe");
const std::string TOPIC("SENSORS/CAMERA_ON_OFF");


class action_listener : public virtual mqtt::iaction_listener
{
public:
    std::string name_;
    Logger logger_;

    action_listener(const char* name)
        : name_(name)
        , logger_("action_listener") 
        {}

    void on_failure(const mqtt::token& tok) override {
        logger_  << DEBUG << name_ << " failure" << ENDL;
        if (tok.get_message_id() != 0)
            logger_ << DEBUG << " for token: [" << tok.get_message_id() << "]" << ENDL;
    }

    void on_success(const mqtt::token& tok) override {
        logger_ << DEBUG << name_ << " success" << ENDL;
        if (tok.get_message_id() != 0)
            logger_ << DEBUG << " for token: [" << tok.get_message_id() << "]" << ENDL;
        auto top = tok.get_topics();
        if (top && !top->empty())
            logger_ << DEBUG << "\ttoken topic: '" << (*top)[0] << "', ..." << ENDL;
    }
};

class callback : public virtual mqtt::callback,
                    public virtual mqtt::iaction_listener

{
    Logger logger_;
    // Counter for the number of connection retries
    int nretry_;
    // The MQTT client
    mqtt::async_client& cli_;
    // Options to use if we need to reconnect
    mqtt::connect_options& connOpts_;
    // An action listener to display the result of actions.
    action_listener subListener_;

    // This deomonstrates manually reconnecting to the broker by calling
    // connect() again. This is a possibility for an application that keeps
    // a copy of it's original connect_options, or if the app wants to
    // reconnect with different options.
    // Another way this can be done manually, if using the same options, is
    // to just call the async_client::reconnect() method.
    void reconnect() {
        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
        try {
            cli_.connect(connOpts_, nullptr, *this);
        }
        catch (const mqtt::exception& exc) {
            logger_ << ERROR << exc.what() << ENDL;
            exit(1);
        }
    }

    // Re-connection failure
    void on_failure(const mqtt::token& tok) override {
        logger_ << ERROR << "Connection failed" << ENDL;
        if (++nretry_ > N_RETRY_ATTEMPTS)
            exit(1);
        reconnect();
    }

    // Re-connection success
    void on_success(const mqtt::token& tok) override {
        cli_.subscribe(TOPIC, QOS, nullptr, subListener_);
    }

    // Callback for when the connection is lost.
    // This will initiate the attempt to manually reconnect.
    void connection_lost(const std::string& cause) override {
        logger_ << ERROR << "Connection lost: ";
        if (!cause.empty())
            logger_ << cause << ENDL;
        else
            logger_ << "unknown reason" << ENDL;
        logger_ << "Reconnecting..." << ENDL;
        nretry_ = 0;
        reconnect();
    }

    // Callback for when a message arrives.
    void message_arrived(mqtt::const_message_ptr msg) override {
        logger_ << DEBUG << "Message arrived";
        logger_ << "{ topic: '" << msg->get_topic() << "', ";
        logger_ << "payload: '" << msg->to_string() << "' }" << ENDL;
        if (msg->to_string() == "ON"){
            logger_ << INFO << "Camera is ON" << ENDL;
            Camera::isRecording = true;
        }
        else if (msg->to_string() == "OFF"){
            logger_ << INFO << "Camera is OFF" << ENDL;
            Camera::isRecording = false;
        }
        else{
            logger_ << INFO << "Bad message. Nothing to do..." << ENDL;
        }
    }

    void delivery_complete(mqtt::delivery_token_ptr token) override {}

public:
    callback(mqtt::async_client& cli, mqtt::connect_options& connOpts)
        : logger_("callback")
        , nretry_(0)
        , cli_(cli)
        , connOpts_(connOpts)
        , subListener_("Subscription")
        {}
};

} // CAMERA NAMESPACE --- > END

class MqttConnector
{
public:
    MqttConnector();
    ~MqttConnector();
    int publish(std::string topic, std::string message);

private:
    void subscribeCamera();

    Logger logger_;
    const std::string DFLT_ADDRESS;
    const int QOS;
    const int MAX_BUFFERED_MSGS;  // 120 * 5sec => 10min off-line buffering
    const std::string PERSIST_DIR;
    mqtt::async_client cli;
    std::thread subscribeThread;
};
