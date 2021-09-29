#include <raspicom/raspcommands.h>
#include <libraries/ArduinoJson.h>

RaspCommand* RaspCommand::fromJsonString(std::string json){
  DynamicJsonDocument json_doc(1024);
  deserializeJson(json_doc,json);

  if(json_doc["cmd"] == "sync")
    return new SyncCommand();
  else if (json_doc["cmd"] == "ack")
    return new AckCommand();
  else if (json_doc["cmd"] == "shutdown")
    return new ShutDownCommand();
  else if (json_doc["cmd"] == "dump"){
    std::string dump_string;
    serializeJson(json_doc["data"], dump_string);
    return new TransferDumpCommand(dump_string);
  } else {
    return new RaspCommand();
  }  
}

std::string RaspCommand::toJsonString(){
  DynamicJsonDocument json_doc(64);
  JsonObject obj = json_doc.to<JsonObject>();
  std::string json_string;
  serializeJson(obj,json_string);
  return json_string;
}

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