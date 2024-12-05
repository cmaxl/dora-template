#include "dora.h"

void sendEvents()
{
  static elapsedMillis eventsAt1_25Hz;
  if (eventsAt1_25Hz > 800) {
    eventsAt1_25Hz = 0;

    StaticJsonDocument<JSON_BUFFER_SIZE> doc;
    JsonObject obj = doc.to<JsonObject>();

    obj["foo"] = "bar";
    events.send(doc.as<String>().c_str(), "state", millis());

    // obj.clear(); // only needed if other data is sent
  }

}