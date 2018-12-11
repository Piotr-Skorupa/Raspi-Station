#include "MqttConnector.hpp"

MqttConnector::MqttConnector()
	:logger_("MqttConnector")
	, DFLT_ADDRESS("213.222.211.83")
	, QOS(1)
	, MAX_BUFFERED_MSGS(120)
	, PERSIST_DIR("data-persist")
	, cli(DFLT_ADDRESS, "", MAX_BUFFERED_MSGS, PERSIST_DIR)
{
	subscribeThread = std::thread(&MqttConnector::subscribeCamera, this);

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
	if (subscribeThread.joinable())
	{
		subscribeThread.join();
		logger_ << INFO << "Subscribe thread successfuly joined!" << ENDL;
	}else
	{
		logger_ << ERROR << "Subscribe thread still working. Try send SIGTERM or SIGINT signal to application" << ENDL;
	}

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
	// Publish to the topic
	// Create a topic object. This is a conventience since we will
	// repeatedly publish messages with the same parameters.
	try
	{
		mqtt::topic top(cli, topic, QOS, true);
		top.publish(std::move(message));
		logger_ << INFO << topic << " message has been sent" <<ENDL;
	}
	catch (const mqtt::exception& exc) {
		logger_ << ERROR << exc.what() << ENDL;
		return 1;
	}
}

void MqttConnector::subscribeCamera()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	Logger logger("MqttCameraSubscriber");
	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(true);

	mqtt::async_client client(camera::SERVER_ADDRESS, camera::CLIENT_ID);

	camera::callback cb(client, connOpts);
	client.set_callback(cb);

	// Start the connection for camera.
	// When completed, the callback will subscribe to topic.

	try {
		logger << DEBUG << "Connecting to the MQTT server by subscribe thread (camera)... " << ENDL;
		client.connect(connOpts, nullptr, cb);
	}
	catch (const mqtt::exception&) {
		logger << ERROR << "Unable to connect to MQTT server (camera)" << ENDL;
		return;
	}

	// keeping thread alive until program exits.

	while (true)
		{}

	// Disconnect

	try {
		logger << INFO << "Disconnecting from the MQTT server... (camera)" << ENDL;
		client.disconnect()->wait();
		logger << INFO << "OK" << ENDL;
	}
	catch (const mqtt::exception& exc) {
		logger << ERROR << exc.what() << ENDL;
		return;
	}
}
