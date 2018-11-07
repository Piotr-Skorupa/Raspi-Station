#include "MqttConnector.hpp"

MqttConnector::MqttConnector()
    :logger_("MqttConnector")
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

		char tmbuf[32];
		unsigned step = 0; // maybe i can 

		// The time at which to reads the next sample, starting now
		auto tm = steady_clock::now();

		while (true) {
			// Pace the samples to the desired rate
			this_thread::sleep_until(tm);

			// Get a timestamp and format as a string
			time_t t = system_clock::to_time_t(system_clock::now());
			strftime(tmbuf, sizeof(tmbuf), "%F %T", localtime(&t));

			// Create the payload as a text CSV string
			string payload = to_string(++step) + "," + message;
			logger_ << INFO << payload << ENDL;

			// Publish to the topic
			top.publish(std::move(payload));

			tm += PERIOD;
		}

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