#include "MqttConnector.hpp"

MqttConnector::MqttConnector()
    :logger_("MqttConnector")
	, DFLT_ADDRESS("213.222.211.83")
	, QOS(1)
	, MAX_BUFFERED_MSGS(120)
	, PERSIST_DIR("data-persist")
    {}

MqttConnector::~MqttConnector()
    {}

int MqttConnector::publish(std::string topic, std::string message)
{
    std::string address = DFLT_ADDRESS;

    const auto PERIOD = seconds(5);

	mqtt::async_client cli(address, "", MAX_BUFFERED_MSGS, PERSIST_DIR);

	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(MAX_BUFFERED_MSGS * PERIOD);
	connOpts.set_clean_session(true);
	connOpts.set_automatic_reconnect(true);

	// Create a topic object. This is a conventience since we will
	// repeatedly publish messages with the same parameters.
	mqtt::topic top(cli, topic, QOS, true);

	try {
		// Connect to the MQTT broker
		logger_ << INFO << "Connecting to server '" << address << "'..." << ENDL;
		cli.connect(connOpts)->wait();
		logger_ << INFO << "Connecting OK" << ENDL;
		
		logger_ << INFO << message << ENDL;

		// Publish to the topic
		top.publish(std::move(message));

		// Disconnect
		logger_ << INFO << "\nDisconnecting..." << ENDL;
		cli.disconnect()->wait();
		logger_ << INFO << "Disconnecting OK" << ENDL;
	}
	catch (const mqtt::exception& exc) {
		logger_ << ERROR << exc.what() << ENDL;
		return 1;
	}
}