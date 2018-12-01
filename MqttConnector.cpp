#include "MqttConnector.hpp"

MqttConnector::MqttConnector()
    :logger_("MqttConnector")
    , DFLT_ADDRESS("213.222.211.83")
	, QOS(1)
	, MAX_BUFFERED_MSGS(120)
	, PERSIST_DIR("data-persist")
	, cli(DFLT_ADDRESS, "", MAX_BUFFERED_MSGS, PERSIST_DIR)
{
	const auto PERIOD = seconds(5);

	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(MAX_BUFFERED_MSGS * PERIOD);
	connOpts.set_clean_session(true);
	connOpts.set_automatic_reconnect(true);

	try
	{
		// Connect to the MQTT broker
		logger_ << DEBUG << "Connecting to server '" << DFLT_ADDRESS << "'..." << ENDL;
		cli.connect(connOpts)->wait();
		logger_ << INFO << "Connecting OK" << ENDL;
	}
	catch (const mqtt::exception& exc) {
		logger_ << ERROR << exc.what() << ENDL;
	}
}

MqttConnector::~MqttConnector()
{
	// Disconnect
	try
	{
		logger_ << INFO << "Disconnecting..." << ENDL;
		cli.disconnect()->wait();
		logger_ << INFO << "Disconnecting OK" << ENDL;
	}
	catch (const mqtt::exception& exc) {
		logger_ << ERROR << exc.what() << ENDL;
	}
}

int MqttConnector::publish(std::string topic, std::string message)
{
	logger_ << INFO << message << ENDL;
	// Publish to the topic
	// Create a topic object. This is a conventience since we will
	// repeatedly publish messages with the same parameters.
	try
	{
		mqtt::topic top(cli, topic, QOS, true);
		top.publish(std::move(message));
	}
	catch (const mqtt::exception& exc) {
		logger_ << ERROR << exc.what() << ENDL;
		return 1;
	}
}