#include <raspicom/raspcommands.h>
#include <ArduinoJson.h>

std::string SyncCommand::toJsonString(){
  DynamicJsonDocument json_doc(64);
  json_doc["cmd"] = "sync";
  json_doc["data"] = "none";
  std::string json_string;
  serializeJson(json_doc, json_string);
  return json_string;
}

std::string AckCommand::toJsonString(){
  DynamicJsonDocument json_doc(64);
  json_doc["cmd"] = "ack";
  json_doc["data"] = "none";
  std::string json_string;
  serializeJson(json_doc, json_string);
  return json_string;
}

std::string ShutDownCommand::toJsonString(){
  DynamicJsonDocument json_doc(64);
  json_doc["cmd"] = "shutdown";
  json_doc["data"] = "none";
  std::string json_string;
  serializeJson(json_doc, json_string);
  return json_string;
}

TransferDumpCommand::TransferDumpCommand(std::string dump) : _dump(dump) {}

std::string TransferDumpCommand::toJsonString(){
    DynamicJsonDocument json_doc(1024);
    DynamicJsonDocument dump_doc(1024);
    deserializeJson(dump_doc,_dump);
    json_doc["cmd"] = "dump";
    json_doc["data"] = dump_doc.as<JsonObject>();
    std::string json_string;
    serializeJson(json_doc, json_string);
    return json_string;
}